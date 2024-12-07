#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define MAX_PONTOS 100

// Estrutura para representar um ponto
typedef struct {
    double x, y;
} Ponto;

// Função para calcular a distância da origem
double distanciaOrigem(Ponto p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

// Função para calcular a distância total (somatório das distâncias entre pontos consecutivos)
double calcularDistanciaTotal(Ponto pontos[], int n) {
    double soma = 0;
    for (int i = 0; i < n - 1; i++) {
        double dx = pontos[i + 1].x - pontos[i].x;
        double dy = pontos[i + 1].y - pontos[i].y;
        soma += sqrt(dx * dx + dy * dy); 
    }
    return soma;
}

// Função para calcular a "shortcut", a distância entre o primeiro e o último ponto
double calcularShortcut(Ponto pontos[], int n) {
    double dx = pontos[n - 1].x - pontos[0].x;
    double dy = pontos[n - 1].y - pontos[0].y;
    return sqrt(dx * dx + dy * dy);
}

// Função para processar cada linha do arquivo de entrada
void processar_entrada(FILE *fp_in, FILE *fp_out) {
    char line[255];
    const char comma[] = ",";
    char *slice;

    // Lê cada linha do arquivo de entrada
    while (fgets(line, sizeof(line), fp_in) != NULL) {
        Ponto pontos[MAX_PONTOS];
        int n = 0;

        // Tokeniza a linha e armazena os pontos
        slice = strtok(line, comma);
        while (slice != NULL && n < MAX_PONTOS) {
            sscanf(slice, "%lf", &pontos[n].x);
            slice = strtok(NULL, comma);
            sscanf(slice, "%lf", &pontos[n].y);
            slice = strtok(NULL, comma);
            n++;
        }

        // Calcular distâncias
        double distanciaTotal = calcularDistanciaTotal(pontos, n);
        double shortcut = calcularShortcut(pontos, n);

        // Escreve a saída no arquivo
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

    // Leitura e processamento do arquivo de entrada
    char line[255];
    while (fgets(line, sizeof(line), arquivoEntrada) != NULL) {
        // Aqui você processaria cada linha de dados conforme a lógica do seu programa
        // Exemplo de leitura dos pontos, calculando distâncias, etc.
        printf("Linha lida: %s", line); // Exemplo de como manipular a linha
        // Escreve o resultado no arquivo de saída
        fprintf(arquivoSaida, "Resultado para a linha: %s", line);  // Apenas um exemplo
    }

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    printf("Processamento concluído. Arquivo de saída gerado: L0Q1.out\n");
    return EXIT_SUCCESS;
}