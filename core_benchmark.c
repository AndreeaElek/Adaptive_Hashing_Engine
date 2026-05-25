#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>           
#include <openssl/evp.h>

#define BUFFER_SIZE 4096
#define ITERATIONS 100

typedef struct {
    const char *name;
    const EVP_MD *(*md_func)(void);
} AlgoConfig;

// Function to calculate pure cryptographic time for a single file run
double run_hash_test(const EVP_MD *md, const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) return -1.0;

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;

    // --- WINDOWS NATIVE HIGH-PRECISION TIMER CORES ---
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency); // Gets internal CPU crystal frequency
    QueryPerformanceCounter(&start);       // Benchmark start hardware stamp

    EVP_DigestInit_ex(mdctx, md, NULL);
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        EVP_DigestUpdate(mdctx, buffer, bytes_read);
    }
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);
    
    QueryPerformanceCounter(&end);         // Benchmark stop hardware stamp
    // -------------------------------------------------

    fclose(file);
    EVP_MD_CTX_free(mdctx);

    // Compute duration precisely in milliseconds
    return (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;
}

int main() {
    AlgoConfig algos[] = {
        {"SHA-256", EVP_sha256},
        {"SHA-3", EVP_sha3_256},
        {"Whirlpool", EVP_whirlpool},
        {"Blake2b", EVP_blake2b512},
        {"RIPEMD", EVP_ripemd160}
    };
    int algo_count = sizeof(algos) / sizeof(algos[0]);

    const char *files[] = {"../data/small.dat", "../data/medium.dat", "../data/large.dat"};
    double sizes[] = {0.001, 10.0, 100.0};
    int file_count = 3;

    system("mkdir ..\\results 2>nul");

    FILE *csv = fopen("../results/performance_results.csv", "w");
    if (!csv) {
        perror("Failed to create results file");
        return 1;
    }

    fprintf(csv, "Algorithm,FileSize_MB,Iteration,Time_ms,Throughput_MBs\n");
    printf("Starting True Core Hashing Analysis (Windows Native Runner)...\n");

    for (int a = 0; a < algo_count; a++) {
        printf("Benchmarking %s...\n", algos[a].name);
        const EVP_MD *md = algos[a].md_func();

        for (int f = 0; f < file_count; f++) {
            for (int i = 1; i <= ITERATIONS; i++) {
                double time_ms = run_hash_test(md, files[f]);
                
                if (time_ms < 0) {
                    printf("Error reading file target %s\n", files[f]);
                    continue;
                }

                double throughput = sizes[f] / (time_ms / 1000.0);
                fprintf(csv, "%s,%.3f,%d,%.4f,%.2f\n", 
                        algos[a].name, sizes[f], i, time_ms, throughput);
            }
        }
    }

    fclose(csv);
    printf("Analysis done! Results saved to results/performance_results.csv\n");
    return 0;
}
