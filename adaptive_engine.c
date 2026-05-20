#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
     char name[20];
    int security;
    int speed;
    int throughput;
    int consistency;
} HashOption;

void run_adaptive_engine(int s, int ss, int tl, int co, char* filename) {
    HashOption options[5];
    int count = 0;

    // --- DYNAMIC CSV READING ---
    FILE *file = fopen("hash_params.csv", "r");
    if (!file) {
        printf("Error: Could not find hash_params.csv\n");
        return;
    }

    char line[1024];
    fgets(line, 1024, file); // Skip header row

    while (fgets(line, 1024, file) && count < 5) {
        char *token = strtok(line, ",");
        strcpy(options[count].name, token);
        options[count].security = atoi(strtok(NULL, ","));
        options[count].speed = atoi(strtok(NULL, ","));
        options[count].throughput = atoi(strtok(NULL, ","));
        options[count].consistency = atoi(strtok(NULL, ","));
        count++;
    }
    fclose(file);


    // --- ADAPTIVE DECISION LOGIC ---
    int best_index = 0;
    float max_score = 0;

    for (int i = 0; i < count; i++) {
        // Weighted formula 
         float score = (options[i].security * s) + 
                      (options[i].speed * ss) +  
                      (options[i].throughput * tl) + 
                      (options[i].consistency * co);
        
        if (score > max_score) {
            max_score = score;
            best_index = i;
        }
    }

    printf("\n>>> ENGINE DECISION: Selected %s\n", options[best_index].name);
    printf(">>> REASON: Calculated optimal weight of %.1f\n", max_score);

    // CALL EXTERNAL EXECUTABLE
    char command[128];
    sprintf(command, "%s.exe %s", options[best_index].name, filename);
    system(command);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./engine <file_to_hash>\n");
        return 1;
    }

    int s, ss, ef, tl, co;
    printf("ADAPTIVE HASHING ENGINE \n");
    printf("- Security: "); scanf("%d", &s);
    printf("- Speed:  "); scanf("%d", &ss);
    printf("- Throughput : "); scanf("%d", &tl);
    printf("- Consistency: "); scanf("%d", &co);

    run_adaptive_engine(s, ss, tl, co, argv[1]);

    return 0;
}
