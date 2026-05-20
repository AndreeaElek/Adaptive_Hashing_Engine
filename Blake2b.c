#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

void hash_blake2(const char *message) {
    // we setup the message digest context
    EVP_MD_CTX *mdctx;
    unsigned char hash[64]; // BLAKE2b-512 produces 64 bytes
    unsigned int hash_len;

    // we create a new context using EVP_MD_CTX_new
    mdctx = EVP_MD_CTX_new();
    
    // we initialize the context with the blake2b algorithm
    if (EVP_DigestInit_ex(mdctx, EVP_blake2b512(), NULL) != 1) {
        printf("Could not initialize BLAKE2b.\n");
        return;
    }
    
     // we update the context with the message data using EVP_DigestUpdate
    EVP_DigestUpdate(mdctx, message, strlen(message));

     // we calculate the final hash with EVP_DigestFinal_ex
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);

    // we free the allocated context memory with EVP_MD_CTX_free
    EVP_MD_CTX_free(mdctx);

    printf("BLAKE2b-512: ");
    for(unsigned int i = 0; i < hash_len; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    //we call the hash function for the string "abc"
    hash_blake2("abc");
    return 0;
}
