#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LISTAS 100
#define MAX_NUMEROS 100

typedef struct {
    int numeros[MAX_NUMEROS];
    int tamanho;
    int soma;
} Lista;

void ordenarArray(int *array, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void ordenarListas(Lista *listas, int quantidade) {
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - i - 1; j++) {
            if (listas[j].soma > listas[j + 1].soma) {
                Lista temp = listas[j];
                listas[j] = listas[j + 1];
                listas[j + 1] = temp;
            }
        }
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
    FILE *entrada = abrirArquivoEntrada("L1Q1.in");
    if (!entrada) return 1;

    FILE *saida = abrirArquivoSaida("L1Q1.out");
    if (!saida) {
        fclose(entrada);
        return 1;
    }

    Lista listas[MAX_LISTAS];
    int quantidadeListas = 0;

    char linha[1024];
    while (fgets(linha, sizeof(linha), entrada)) {
        char *ptr = strstr(linha, "start");
        while (ptr) {
            listas[quantidadeListas].tamanho = 0;
            listas[quantidadeListas].soma = 0;
            ptr += 5;

            int numero;
            while (sscanf(ptr, "%d", &numero) == 1) {
                listas[quantidadeListas].numeros[listas[quantidadeListas].tamanho++] = numero;
                listas[quantidadeListas].soma += numero;
                ptr = strchr(ptr, ' ');
                if (!ptr) break;
                ptr++;
            }

            quantidadeListas++;
            ptr = strstr(ptr, "start");
        }
    }

    for (int i = 0; i < quantidadeListas; i++) {
        ordenarArray(listas[i].numeros, listas[i].tamanho);
    }

    ordenarListas(listas, quantidadeListas);

    for (int i = 0; i < quantidadeListas; i++) {
        fprintf(saida, "start");
        for (int j = 0; j < listas[i].tamanho; j++) {
            fprintf(saida, " %d", listas[i].numeros[j]);
        }
        fprintf(saida, "\n");
    }

    fclose(entrada);
    fclose(saida);

    printf("Arquivo de saída gerado: L1Q1.out\n");
    return 0;
}
