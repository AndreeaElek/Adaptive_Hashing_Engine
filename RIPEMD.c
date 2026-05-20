#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/provider.h>

void hash_ripemd160(const char *message) {
    //we specify path for legacy provider loading
    OSSL_PROVIDER_set_default_search_path(NULL, "."); 
    OSSL_PROVIDER *legacy = OSSL_PROVIDER_load(NULL, "legacy");
    OSSL_PROVIDER *deflt = OSSL_PROVIDER_load(NULL, "default");

    //we create context for the digest
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    unsigned char hash[20]; // RIPEMD-160 produces 160 bits (20 bytes)
    unsigned int hash_len;

    // we initialize the RIPEMD-160 algorithm
    if (EVP_DigestInit_ex(mdctx, EVP_ripemd160(), NULL) != 1) {
        printf("Could not initialize RIPEMD-160. Check if legacy.dll is present.\n");
        return;
    }
    
    // hash the input string using EVP_DigestUpdate
    EVP_DigestUpdate(mdctx, message, strlen(message));

    // store final result with EVP_DigestFinal_ex
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);

    // dispose of the context with EVP_MD_CTX_free
    EVP_MD_CTX_free(mdctx);

    // release providers from memory
    OSSL_PROVIDER_unload(legacy);
    OSSL_PROVIDER_unload(deflt);

    printf("RIPEMD-160: ");
    for(unsigned int i = 0; i < hash_len; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    //we call the hash function for the string "abc"
    hash_ripemd160("abc");
    return 0;
}
