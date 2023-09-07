#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAIN_STRING_SIZE 1500
#define MAX_STRING_SIZE 50
#define STRING_QUANTITY 4

void get_str_from_file(const char *f_name, char *str,
                       char str_arr[][MAX_MAIN_STRING_SIZE], int *n_str) {
    char line[MAX_MAIN_STRING_SIZE];
    FILE *f;

    f = fopen(f_name, "r, ccs=UTF-8");

    uint8_t bom[6];
    if (fread(bom, 1, 6, f) != 6) {
        perror("Erro ao ler a BOM");
        fclose(f);
        return;
    }

    if (bom[0] != 0xEF || bom[1] != 0xBB || bom[2] != 0xBF) {
        fseek(f, 0, SEEK_SET);
    }

    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    while (fgets(line, sizeof(line), f)) {
        if (strcmp(line, "\n") == 0) {
            break;
        }
        strcat(str, line);
    }

    while (fgets(line, sizeof(line), f)) {
        if (strcmp(line, "\n") == 0) {
            continue;
        }
        strcpy(str_arr[(*n_str)], line);
        (*n_str)++;
    }

    fclose(f);
}

int main() {
    char str[MAX_MAIN_STRING_SIZE];
    char str_arr[MAX_MAIN_STRING_SIZE][MAX_MAIN_STRING_SIZE];
    int n_str = 0;

    get_str_from_file("texto.txt", str, str_arr, &n_str);

    printf("String Principal: %s\n", str);

    printf("Strings a serem encontradas:\n");
    for (int i = 0; i < n_str; i++) {
        printf("%s", str_arr[i]);
    }

    return 0;
}