#include "JwtAuth0Filter.h"
#include <jwt-cpp/jwt.h>
#include <drogon/drogon.h>
#include <json/json.h>

JwtAuth0Filter::JwtAuth0Filter()
{
    auto& conf = drogon::app().getCustomConfig();
    auth0Domain_ = conf["auth0"]["domain"].asString();
    auth0Audience_ = conf["auth0"]["audience"].asString();
    authh0Issuer_ = conf["auth0"]["issuer"].asString();
}


void JwtAuth0Filter::doFilter(const drogon::HttpRequestPtr& req,
                              drogon::FilterCallback&& fcb,
                              drogon::FilterChainCallback&& fccb)
{
    auto authHeader = req->getHeader("Authorization");
    if (authHeader.find("Bearer ") != 0)
    {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k401Unauthorized);
        resp->setBody("Missing or invalid Authorization header");
        fcb(resp);
        return;
    }
    auto token = authHeader.substr(7);

    try
    {
        auto decoded = jwt::decode(token);

        // ✅ Verify audience
        bool audienceOk = false;
        for (auto& aud : decoded.get_audience())
        {
            if (aud == auth0Audience_) audienceOk = true;
        }
        if (!audienceOk) throw std::runtime_error("Invalid audience");

        // ✅ Verify issuer
        if (decoded.get_issuer() != authh0Issuer_)
            throw std::runtime_error("Invalid issuer");

        // Verify signature with Auth0 JWKS (for production)
        /*
        * Each JWT header has a kid (Key ID).
        * It tells us which RSA key (from Auth0’s JWKS) was used to sign the token.
         */
        std::string kid = decoded.get_key_id();
        /*
        * Checks if we already cached Auth0’s keys.
        * If not, fetch https://YOUR_DOMAIN/.well-known/jwks.json.
        * This JWKS contains Auth0’s public RSA keys.
         */
        if (jwksCache_.find(kid) == jwksCache_.end())
        {
            loadJWKS();
        }

        /*
        * After refreshing JWKS, if we still don’t find this kid → token is invalid.
        * This prevents attackers from using a token signed with an unknown/old key.
         */
        if (jwksCache_.find(kid) == jwksCache_.end())
        {
            throw std::runtime_error("No matching key in JWKS");
        }

        /*
        *   Extracts the modulus (n) and exponent (e) for this key.
        *   Converts them into a real RSA PEM public key using OpenSSL.
        *   This gives us the exact public key Auth0 used to sign the JWT.
         */
        auto jwk = jwksCache_[kid];
        std::string pubKeyPem = buildRSAPublicKey(jwk.n, jwk.e);

        /*
         *   Creates an RS256 algorithm object configured with that RSA public key.
         *   This object will check signatures made with the corresponding private key (which only Auth0 has).
         */
        auto algo = jwt::algorithm::rs256(pubKeyPem, "", "", "");

        /*Builds a verifier with three checks:
        *Signature check (with algo)
        *   Ensures the JWT was signed with Auth0’s private key.
        *   Prevents forgery.

        *Issuer check
        *   Confirms the token came from your Auth0 tenant (iss claim).

        *Audience check
        *   Confirms the token was meant for your API (aud claim).
         */
        auto verifier = jwt::verify()
                        .allow_algorithm(algo)
                        .with_issuer(authh0Issuer_)
                        .with_audience(auth0Audience_);

        verifier.verify(decoded);


        // 4️⃣ Store subject for controller
        req->attributes()->insert("sub", decoded.get_subject());
        fccb();
    }
    catch (const std::exception& e)
    {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k401Unauthorized);
        resp->setBody(std::string("Invalid token: ") + e.what());
        fcb(resp);
    }
}

void JwtAuth0Filter::loadJWKS()
{
    auto client = drogon::HttpClient::newHttpClient("https://" + auth0Domain_);
    auto req = drogon::HttpRequest::newHttpRequest();
    req->setPath("/.well-known/jwks.json");

    auto [result, resp] = client->sendRequest(req);
    if (result != drogon::ReqResult::Ok || !resp)
    {
        throw std::runtime_error("Failed to fetch JWKS");
    }

    Json::Value json;
    Json::CharReaderBuilder rb;
    std::string errs;

    std::string body(resp->getBody());
    std::istringstream s(body);
    if (!Json::parseFromStream(rb, s, &json, &errs))
    {
        throw std::runtime_error("Failed to parse JWKS");
    }

    for (auto& key : json["keys"])
    {
        std::string kid = key["kid"].asString();
        std::string n = key["n"].asString();
        std::string e = key["e"].asString();
        jwksCache_[kid] = {n, e};
    }
}
