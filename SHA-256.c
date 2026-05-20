#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_sha256(const char *string) {
    //we define the fixed output size
    unsigned char hash[SHA256_DIGEST_LENGTH];

    // we perform the hash in a single step using the SHA-256 function
    SHA256((unsigned char*)string, strlen(string), hash);

    printf("SHA-256: ");
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

int main() {
    //we call the hash function for the string "abc"
    hash_sha256("abc"); 
    return 0;
}

