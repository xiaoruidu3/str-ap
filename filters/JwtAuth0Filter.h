#pragma once
#include <drogon/HttpFilter.h>
#include <unordered_map>
#include <iosfwd>
#include "Base64Url.h"


class JwtAuth0Filter : public drogon::HttpFilter<JwtAuth0Filter>
{
    struct JwkKey
    {
        std::string n;
        std::string e;
    };

    std::string auth0Domain_;
    std::string auth0Audience_;
    std::string authh0Issuer_;
    std::unordered_map<std::string, JwkKey> jwksCache_;

public:
    JwtAuth0Filter();
    void doFilter(const drogon::HttpRequestPtr& req,
                  drogon::FilterCallback&& fcb,
                  drogon::FilterChainCallback&& fccb) override;

private:
    void loadJWKS();
};
