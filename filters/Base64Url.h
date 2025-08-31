#pragma once

#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <jwt-cpp/jwt.h>
#include <string>
#include <vector>

// Decode Base64URL -> binary
std::vector<unsigned char> base64UrlDecode(const std::string& input)
{
    std::string b64 = input;
    // Replace URL-safe chars
    std::replace(b64.begin(), b64.end(), '-', '+');
    std::replace(b64.begin(), b64.end(), '_', '/');
    // Pad with '='
    while (b64.size() % 4) b64.push_back('=');

    BIO *bio, *b64f;
    BUF_MEM* bufferPtr;
    bio = BIO_new_mem_buf(b64.data(), b64.size());
    b64f = BIO_new(BIO_f_base64());
    BIO_set_flags(b64f, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_push(b64f, bio);

    std::vector<unsigned char> out(b64.size());
    int len = BIO_read(bio, out.data(), b64.size());
    out.resize(len);

    BIO_free_all(bio);
    return out;
}

// Build PEM public key from n, e
std::string buildRSAPublicKey(const std::string& n_b64, const std::string& e_b64)
{
    auto n_bin = base64UrlDecode(n_b64);
    auto e_bin = base64UrlDecode(e_b64);

    BIGNUM* n = BN_bin2bn(n_bin.data(), n_bin.size(), NULL);
    BIGNUM* e = BN_bin2bn(e_bin.data(), e_bin.size(), NULL);

    RSA* rsa = RSA_new();
#if OPENSSL_VERSION_NUMBER < 0x10100000L
    rsa->n = n;
    rsa->e = e;
#else
    RSA_set0_key(rsa, n, e, NULL);
#endif

    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSA_PUBKEY(bio, rsa);

    char* pem_data;
    long pem_len = BIO_get_mem_data(bio, &pem_data);
    std::string pem(pem_data, pem_len);

    BIO_free(bio);
    RSA_free(rsa);

    return pem;
}
