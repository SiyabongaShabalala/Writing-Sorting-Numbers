#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_NUMBERS 1000


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_NUMBERS 1000

// Comparison function for ascending order
int compare_asc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Comparison function for descending order
int compare_desc(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

// Function to read numbers from CSV
int read_numbers_from_csv(const char filename, int numbers[], int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    *count = 0;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *token = strtok(line, ",");
        while (token != NULL && *count < MAX_NUMBERS) {
            numbers[*count] = atoi(token); // Convert string to integer
            (*count)++;
            token = strtok(NULL, ",");
        }
    }

    fclose(file);
    return 0;
}

// Function to write numbers to a file
void write_numbers_to_file(const char filename, int numbers[], int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file %s for writing\n", filename);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d", numbers[i]);
        if (i < count - 1) {
            fprintf(file, ",");
        }
    }

    fclose(file);
}

int main() {
    char input_filename[256], output_filename[256];
    int numbers[MAX_NUMBERS];
    int count;
    int order;

    // Step 1: Get input and output file names from the user
    printf("Enter input CSV file name: ");
    scanf("%s", input_filename);

    printf("Enter output file name: ");
    scanf("%s", output_filename);

    // Step 2: Read numbers from CSV file
    if (read_numbers_from_csv(input_filename, numbers, &count) != 0) {
        return 1;
    }

    // Step 3: Ask the user for sorting order
    printf("Enter 1 for ascending order, 2 for descending order: ");
    scanf("%d", &order);

    // Step 4: Sort the numbers based on user's choice
    if (order == 1) {
        qsort(numbers, count, sizeof(int), compare_asc);
    } else if (order == 2) {
        qsort(numbers, count, sizeof(int), compare_desc);
    } else {
        printf("Invalid option for sorting order\n");
        return 1;
    }

    // Step 5: Write sorted numbers to output file
    write_numbers_to_file(output_filename, numbers, count);

    printf("Sorted numbers written to %s\n", output_filename);

    return 0;
}



