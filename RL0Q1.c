#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_PONTOS 100
#define MAX_STRINGS 100
#define MAX_LENGTH 100

typedef struct {
    double x, y;
} Ponto;

// Funções da Questão 1
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

void processarQuestao1(FILE *fp_in, FILE *fp_out) {
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
            fprintf(fp_out, "(%.2lf, %.2lf) ", pontos[i].x, pontos[i].y);
        }
        fprintf(fp_out, "distance %.2lf shortcut %.2lf\n", distanciaTotal, shortcut);
    }
}

// Funções da Questão 2
double distanciaEuclidiana(Ponto p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

void processarQuestao2(FILE *fp_in, FILE *fp_out) {
    char line[1024];

    while (fgets(line, sizeof(line), fp_in) != NULL) {
        char strings[MAX_STRINGS][MAX_LENGTH];
        int integers[MAX_PONTOS], intCount = 0;
        double floats[MAX_PONTOS]; 
        int floatCount = 0;
        Ponto pontos[MAX_PONTOS];
        int stringCount = 0, pointCount = 0;

        char *token = strtok(line, " ");
        while (token) {
            // Verifica se o token é um ponto (exemplo: "(x,y)")
            if (sscanf(token, "(%lf,%lf)", &pontos[pointCount].x, &pontos[pointCount].y) == 2) {
                pointCount++;
            }
            // Verifica se é um número com ponto decimal (float)
            else if (strchr(token, '.')) {
                floats[floatCount++] = atof(token);
            }
            // Verifica se é um número inteiro
            else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
                integers[intCount++] = atoi(token);
            }
            // Caso contrário, trata como string
            else {
                strcpy(strings[stringCount++], token);
            }
            // Avança para o próximo token
            token = strtok(NULL, " ");
        }

        // Saída formatada
        fprintf(fp_out, "str:");
        for (int i = 0; i < stringCount; i++) {
            fprintf(fp_out, "%s ", strings[i]);
        }
        fprintf(fp_out, "int:");
        for (int i = 0; i < intCount; i++) {
            fprintf(fp_out, "%d ", integers[i]);
        }
        fprintf(fp_out, "float:");
        for (int i = 0; i < floatCount; i++) {
            fprintf(fp_out, "%.2lf ", floats[i]);
        }
        fprintf(fp_out, "p:");
        for (int i = 0; i < pointCount; i++) {
            fprintf(fp_out, "(%.2lf,%.2lf) ", pontos[i].x, pontos[i].y);
        }
        fprintf(fp_out, "\n");
    }
}


// Funções auxiliares para arquivos
FILE* abrirArquivoEntrada(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", nomeArquivo);
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

// Menu principal
int main() {
    int opcao;
    printf("Selecione a questão a ser executada:\n");
    printf("1 - Questão 1 (Distâncias e atalhos)\n");
    printf("2 - Questão 2 (Ordenação de strings, inteiros, floats e pontos)\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    FILE *arquivoEntrada, *arquivoSaida;

    if (opcao == 1) {
        arquivoEntrada = abrirArquivoEntrada("L0Q1.in");
        arquivoSaida = abrirArquivoSaida("L0Q1.out");
        if (arquivoEntrada && arquivoSaida) {
            processarQuestao1(arquivoEntrada, arquivoSaida);
        }
    } else if (opcao == 2) {
        arquivoEntrada = abrirArquivoEntrada("L0Q2.in");
        arquivoSaida = abrirArquivoSaida("L0Q2.out");
        if (arquivoEntrada && arquivoSaida) {
            processarQuestao2(arquivoEntrada, arquivoSaida);
        }
    } else {
        printf("Opção inválida!\n");
        return EXIT_FAILURE;
    }

    if (arquivoEntrada) fclose(arquivoEntrada);
    if (arquivoSaida) fclose(arquivoSaida);

    printf("Processamento concluído. Verifique o arquivo de saída correspondente.\n");
    return EXIT_SUCCESS;
}
