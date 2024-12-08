#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_STRINGS 100
#define MAX_PONTOS 100
#define MAX_LENGTH 50

typedef struct {
    double x, y;
} Ponto;

int main() {
    FILE *fp_in = fopen("L0Q2.in", "r");
    FILE *fp_out = fopen("L0Q2.out", "w");

    if (!fp_in || !fp_out) {
        printf("Erro ao abrir os arquivos!\n");
        return 1;
    }

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

        fprintf(fp_out, "str:");
        for (int i = 0; i < stringCount; i++) fprintf(fp_out, "%s ", strings[i]);
        fprintf(fp_out, "int:");
        for (int i = 0; i < intCount; i++) fprintf(fp_out, "%d ", integers[i]);
        fprintf(fp_out, "float:");
        for (int i = 0; i < floatCount; i++) fprintf(fp_out, "%.2lf ", floats[i]);
        fprintf(fp_out, "p:");
        for (int i = 0; i < pointCount; i++) fprintf(fp_out, "(%.2lf,%.2lf) ", pontos[i].x, pontos[i].y);
        fprintf(fp_out, "\n");
    }

    fclose(fp_in);
    fclose(fp_out);

    printf("Verifique o arquivo L0Q2.out.\n");
    return 0;
}
