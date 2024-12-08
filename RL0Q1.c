#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define MAX_PONTOS 100

typedef struct {
    double x, y;
} Ponto;

double calcularDistanciaTotal(Ponto pontos[], int n) {
    double soma = 0;
    for (int i = 0; i < n - 1; i++) {
        double dx = pontos[i + 1].x - pontos[i].x;
        double dy = pontos[i + 1].y - pontos[i].y;
        soma += sqrt(dx * dx + dy * dy);
    }
    return soma;
}

double calcularShortcut(Ponto pontos[], int n) {
    double dx = pontos[n - 1].x - pontos[0].x;
    double dy = pontos[n - 1].y - pontos[0].y;
    return sqrt(dx * dx + dy * dy);
}

void processarEntrada(FILE *fp_in, FILE *fp_out) {
    char line[1024];
    const char *format = " (%lf,%lf)";

    while (fgets(line, sizeof(line), fp_in) != NULL) {
        Ponto pontos[MAX_PONTOS];
        int n = 0;
        char *ptr = strstr(line, "points");
        if (!ptr) continue;
        ptr += 6;

        while (sscanf(ptr, format, &pontos[n].x, &pontos[n].y) == 2) {
            n++;
            if (n >= MAX_PONTOS) break;
            ptr = strchr(ptr, ')') + 1;
        }

        double distanciaTotal = calcularDistanciaTotal(pontos, n);
        double shortcut = calcularShortcut(pontos, n);
        fprintf(fp_out, "points ");
        for (int i = 0; i < n; i++) {
            if (pontos[i].x == (int)pontos[i].x) {
                fprintf(fp_out, "(%d, ", (int)pontos[i].x);
            } else {
                fprintf(fp_out, "(%.2lf, ", pontos[i].x);
            }

            if (pontos[i].y == (int)pontos[i].y) {
                fprintf(fp_out, "%d) ", (int)pontos[i].y);
            } else {
                fprintf(fp_out, "%.2lf) ", pontos[i].y);
            }
        }
        fprintf(fp_out, "distance %.2lf shortcut %.2lf\n", distanciaTotal, shortcut);
    }
}

FILE* abrirArquivoEntrada(char *nomeArquivo) {
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

FILE* abrirArquivoSaida(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "w");

    if (fp == NULL) {
        printf("Erro ao criar o arquivo de saída: %s\n", nomeArquivo);
        return NULL;
    }
    return fp;
}

int main() {
    FILE *arquivoEntrada = abrirArquivoEntrada("L0Q1.in");
    if (arquivoEntrada == NULL) {
        return EXIT_FAILURE;
    }

    FILE *arquivoSaida = abrirArquivoSaida("L0Q1.out");
    if (arquivoSaida == NULL) {
        fclose(arquivoEntrada);
        return EXIT_FAILURE;
    }

    processarEntrada(arquivoEntrada, arquivoSaida);
    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    printf("Arquivo de saída gerado: L0Q1.out\n");
    return EXIT_SUCCESS;
}