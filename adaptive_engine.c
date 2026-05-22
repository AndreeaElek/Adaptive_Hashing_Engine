#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int security;
    int speed;
    int throughput;
    int consistency;
    char domain1[50];
    char domain2[50];
    char domain3[50];
} HashOption;

void run_adaptive_engine(int s, int ss, int tl, int co, int chosen_domain_idx, char* filename) {
    HashOption options[5];
    int count = 0;

    // Mapping index 1-10 to the exact string names used in the CSV file
    const char* domain_map[] = {
        "", // 0 index unused to align with 1-10 choice
        "Blockchain_And_Distributed_Ledgers",
        "Public_Key_Infrastructure_And_TLS",
        "Firmware_And_Software_Integrity",
        "Hardware_Security_Modules_And_Embedded",
        "Military_And_Defense_Communications",
        "Cloud_Storage_And_File_Systems",
        "Network_Security_Protocols",
        "Cryptocurrency_And_Privacy_Tokens",
        "Enterprise_Data_Archiving",
        "Database_Encryption_And_Storage"
    };

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
        
        token = strtok(NULL, ",");
        if(token) strcpy(options[count].domain1, token);
        
        token = strtok(NULL, ",");
        if(token) strcpy(options[count].domain2, token);
        
        token = strtok(NULL, ",\n\r"); // account for line endings on the last column
        if(token) strcpy(options[count].domain3, token);

        count++;
    }
    fclose(file);

    // --- ADAPTIVE DECISION LOGIC ---
    int best_index = 0;
    float max_score = 0;

    const char* target_domain = domain_map[chosen_domain_idx];

    for (int i = 0; i < count; i++) {
        // Calculate Domain Score based on priority matches
        int domain_score = 0;
        if (strcmp(options[i].domain1, target_domain) == 0) {
            domain_score = 100;
        } else if (strcmp(options[i].domain2, target_domain) == 0) {
            domain_score = 50;
        } else if (strcmp(options[i].domain3, target_domain) == 0) {
            domain_score = 30;
        } else {
            domain_score = 0;
        }

        float score = (options[i].security * s) +
                      (options[i].speed * ss) +
                      (options[i].throughput * tl) +
                      (options[i].consistency * co) +
                      domain_score;

        if (score > max_score) {
            max_score = score;
            best_index = i;
        }
    }

    printf("\n>>> ENGINE DECISION: Selected %s\n", options[best_index].name);
    printf(">>> Calculated optimal weight of %.1f\n", max_score);

    // --- CALL EXTERNAL EXECUTABLE ---
    char command[128];
    sprintf(command, "%s.exe %s", options[best_index].name, filename);
    system(command);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./engine <file_to_hash>\n");
        return 1;
    }

    int s, ss, tl, co;
    int domain_choice;

    printf("ADAPTIVE HASHING ENGINE\n");
    printf("- Security: "); scanf("%d", &s);
    printf("- Speed: "); scanf("%d", &ss);
    printf("- Throughput: "); scanf("%d", &tl);
    printf("- Consistency: "); scanf("%d", &co);

    // Domain Menu Display
    printf("\nSelect Target Domain (1-10):\n");
    printf("1. Blockchain & Distributed Ledgers\n");
    printf("2. Public Key Infrastructure & TLS\n");
    printf("3. Firmware & Software Integrity\n");
    printf("4. Hardware Security Modules & Embedded\n");
    printf("5. Military & Defense Communications\n");
    printf("6. Cloud Storage & File Systems\n");
    printf("7. Network Security Protocols\n");
    printf("8. Cryptocurrency & Privacy Tokens\n");
    printf("9. Enterprise Data_Archiving\n");
    printf("10. Database Encryption & Storage\n");
    printf("- Choice: ");
    scanf("%d", &domain_choice);

    if (domain_choice < 1 || domain_choice > 10) {
        printf("Invalid domain choice. Defaulting to 1.\n");
        domain_choice = 1;
    }

    run_adaptive_engine(s, ss, tl, co, domain_choice, argv[1]);

    return 0;
}
