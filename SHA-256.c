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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        // Fallback to "abc" if no file argument is provided
        hash_sha256("abc"); 
    } else {
        // This will hash "testfile.txt" when called by the engine
        hash_sha256(argv[1]); 
    }
    return 0;
}

