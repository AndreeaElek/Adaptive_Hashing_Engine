#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

void hash_sha3(const char *message) {
    EVP_MD_CTX *mdctx;
    unsigned char hash[32];
    unsigned int hash_len;

    // we allocate a new message digest context
    mdctx = EVP_MD_CTX_new();

    // we initialize sha3-256 using EVP_DigestInit_ex
    EVP_DigestInit_ex(mdctx, EVP_sha3_256(), NULL);

    // we upload the message into the algorithm with EVP_DigestUpdate
    EVP_DigestUpdate(mdctx, message, strlen(message));

    // we extract the final digest with EVP_DigestFinal_ex
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);

    // we clean up the context memory
    EVP_MD_CTX_free(mdctx);

    printf("SHA3-256: ");
    for(unsigned int i = 0; i < hash_len; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // Fallback to "abc" if no file argument is provided
        hash_sha3("abc"); 
    } else {
        // This will hash "testfile.txt" when called by the engine
        hash_sha3(argv[1]); 
    }
    return 0;
}

