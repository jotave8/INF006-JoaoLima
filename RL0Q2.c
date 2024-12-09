#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

#define MAX_STRINGS 100
#define MAX_PONTOS 100
#define MAX_LENGTH 50

typedef struct {
    double x, y;
} Ponto;

int comparaDoubles(const void *a, const void *b) {
    double diff = *(double *)a - *(double *)b;
    return (diff > 0) - (diff < 0);
}

int comparaInteiros(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int comparaStrings(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int compararPontos(const void *a, const void *b) {
    Ponto *pontoA = (Ponto *)a;
    Ponto *pontoB = (Ponto *)b;

    double absX1 = fabs(pontoA->x);
    double absY1 = fabs(pontoA->y);
    double absX2 = fabs(pontoB->x);
    double absY2 = fabs(pontoB->y);

    if (absX1 < absX2) return -1;
    if (absX1 > absX2) return 1;
    if (absY1 < absY2) return -1;
    if (absY1 > absY2) return 1;

    return 0;
}

void entradaQ2(FILE *fp_in, FILE *fp_out) {
    char line[1024];

    while (fgets(line, sizeof(line), fp_in)) {
        char strings[MAX_STRINGS][MAX_LENGTH];
        int integers[MAX_PONTOS], intCount = 0;
        double floats[MAX_PONTOS];
        int floatCount = 0, stringCount = 0, pointCount = 0;
        Ponto pontos[MAX_PONTOS];

        char *token = strtok(line, " ");
        while (token) {
            if (sscanf(token, "(%lf,%lf)", &pontos[pointCount].x, &pontos[pointCount].y) == 2) {
                if (pointCount < MAX_PONTOS) {
                    pointCount++;
                }
            } else if (strchr(token, '.')) {
                if (floatCount < MAX_PONTOS) {
                    floats[floatCount++] = atof(token);
                }
            } else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
                if (intCount < MAX_PONTOS) {
                    integers[intCount++] = atoi(token);
                }
            } else {
                if (stringCount < MAX_STRINGS) {
                    strncpy(strings[stringCount++], token, MAX_LENGTH - 1);
                    strings[stringCount - 1][MAX_LENGTH - 1] = '\0';
                }
            }
            token = strtok(NULL, " ");
        }

        qsort(strings, stringCount, MAX_LENGTH, comparaStrings);
        qsort(integers, intCount, sizeof(int), comparaInteiros);
        qsort(floats, floatCount, sizeof(double), comparaDoubles);
        qsort(pontos, pointCount, sizeof(Ponto), compararPontos);

        fprintf(fp_out, "str:");
        for (int i = 0; i < stringCount; i++) {
            fprintf(fp_out, "%s%s", strings[i], (i < stringCount - 1) ? " " : "");
        }

        fprintf(fp_out, " int:");
        for (int i = 0; i < intCount; i++) {
            fprintf(fp_out, "%d%s", integers[i], (i < intCount - 1) ? " " : "");
        }

        fprintf(fp_out, " float:");
        for (int i = 0; i < floatCount; i++) {
            fprintf(fp_out, "%.2lf%s", floats[i], (i < floatCount - 1) ? " " : "");
        }

        fprintf(fp_out, " p:");
        for (int i = 0; i < pointCount; i++) {
            if ((int)pontos[i].x == pontos[i].x) {
                fprintf(fp_out, "(%.0f", pontos[i].x);
            } else {
                fprintf(fp_out, "(%.1f", pontos[i].x);
            }
            if ((int)pontos[i].y == pontos[i].y) {
                fprintf(fp_out, ",%.0f)", pontos[i].y);
            } else {
                fprintf(fp_out, ",%.1f)", pontos[i].y);
            }

            if (i < pointCount - 1) {
                fprintf(fp_out, " ");
            }
        }
        fprintf(fp_out, "\n");
    }
}

FILE* entrada(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Erro ao abrir o arquivo de entrada: %s\n", nomeArquivo);
            printf("O arquivo está sendo buscado no diretório: %s\n", cwd);
        } else {
            printf("Erro ao obter o diretório atual de trabalho.\n");
        }
        return NULL;
    }
    return fp;
}

FILE* saida(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "w");
    if (fp == NULL) {
        printf("Erro ao criar o arquivo de saída: %s\n", nomeArquivo);
        return NULL;
    }
    return fp;
}

int main() {
    FILE *arquivoEntrada = entrada("L0Q2.in");
    if (arquivoEntrada == NULL) {
        return EXIT_FAILURE;
    }
    FILE *arquivoSaida = saida("L0Q2.out");
    if (arquivoSaida == NULL) {
        fclose(arquivoEntrada);
        return EXIT_FAILURE;
    }
    entradaQ2(arquivoEntrada, arquivoSaida);
    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    printf("Arquivo de saída gerado: L0Q2.out\n");
    return EXIT_SUCCESS;
}
