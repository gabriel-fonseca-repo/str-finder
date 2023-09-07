#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MAIN_STRING_SIZE 1500
#define MAX_STRING_SIZE 50
#define STRING_QUANTITY 4

// Função que conta a ocorrência de uma string alvo na string fonte
void *count_str(const char *substring, const char *str, int *cnt) {
    int len_substr = strlen(substring);
    for (int j = 0; str[j] != '\0'; j++) {
        if (strncmp(&str[j], substring, len_substr) == 0) {
            (*cnt)++;
        }
    }
}

// Função que remove espaços em branco de uma string
void rm_ws(char *str) {
    int len = strlen(str);
    int i, j = 0;

    for (i = 0; i < len; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' &&
            str[i] != '\r' && str[i] != '\f' && str[i] != '\v') {
            str[j++] = str[i];
        }
    }

    str[j] = '\0';
}

// Função para ler a string fonte (onde as strings serão procuradas)
// e o array de strings alvo (as strings que serão procuradas)
void get_str_from_file(const char *f_name, char *str,
                       char str_arr[][MAX_STRING_SIZE], int *n_str) {
    char line[MAX_MAIN_STRING_SIZE];
    FILE *f;

    f = fopen(f_name, "r");

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
    rm_ws(str);

    while (fgets(line, sizeof(line), f)) {
        if (strcmp(line, "\n") == 0) {
            continue;
        }
        rm_ws(line);
        strcpy(str_arr[(*n_str)], line);
        (*n_str)++;
    }

    fclose(f);
}

int main() {
    char str[MAX_MAIN_STRING_SIZE];
    char str_arr[STRING_QUANTITY][MAX_STRING_SIZE];
    int n_str = 0;

    clock_t start_time, end_time;
    double cpu_time_used;

    get_str_from_file("texto.txt", str, str_arr, &n_str);

    printf("String Principal:\n%s\n\n", str);

    printf("Strings a serem encontradas:\n");
    for (int i = 0; i < n_str; i++) {
        printf("%s\n", str_arr[i]);
    }
    printf("\n");

    start_time = clock();

    int *ocorrencias = malloc(n_str * sizeof(int *));

    for (int i = 0; i < n_str; i++) {
        ocorrencias[i] = 0;
        count_str(str_arr[i], str, &ocorrencias[i]);
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Serial (Sem threading)\n");
    for (int i = 0; i < n_str; i++) {
        printf("'%s' ocorre %d vezes.\n", str_arr[i], ocorrencias[i]);
    }
    printf("\n");

    printf("Tempo de execução: %f segundos\n", cpu_time_used);

    free(ocorrencias);
    exit(0);
}
