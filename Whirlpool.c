#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/provider.h>

void hash_whirlpool(const char *message) {
    // we tell openssl to look in the current folder for the dlls
    OSSL_PROVIDER_set_default_search_path(NULL, "."); 

    // we load the legacy and default providers
    OSSL_PROVIDER *legacy = OSSL_PROVIDER_load(NULL, "legacy");
    OSSL_PROVIDER *deflt = OSSL_PROVIDER_load(NULL, "default");

    if (legacy == NULL) {
        printf("Failed to load Legacy provider from current folder.\n");
        return;
    }

    // we create a new digest context
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    unsigned char hash[64];
    unsigned int hash_len;

    // we initialize whirlpool through EVP_DigestInit_ex
    if (EVP_DigestInit_ex(mdctx, EVP_whirlpool(), NULL) != 1) {
        printf("Could not initialize Whirlpool algorithm.\n");
        return;
    }
    
    //we process the message using EVP_DigestUpdate
    EVP_DigestUpdate(mdctx, message, strlen(message));

    //we finalize the result with EVP_DigestFinal_ex
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);

    // we clean up the context memory
    EVP_MD_CTX_free(mdctx);

    // we unload the providers to free resources
    OSSL_PROVIDER_unload(legacy);
    OSSL_PROVIDER_unload(deflt);

    printf("Whirlpool: ");
    for(unsigned int i = 0; i < hash_len; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    //we call the hash function for the string "abc"
    hash_whirlpool("abc");
    return 0;
}
