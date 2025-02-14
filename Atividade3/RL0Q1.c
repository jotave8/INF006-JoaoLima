#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int valor;
    int indice;  // Índice do número na entrada
    struct No *esq, *dir;
} No;

No* novoNo(int valor, int indice) {
    No* no = (No*)malloc(sizeof(No));
    no->valor = valor;
    no->indice = indice;
    no->esq = no->dir = NULL;
    return no;
}

int inserir(No** raiz, int valor, int indice, int altura) {
    if (*raiz == NULL) {
        *raiz = novoNo(valor, indice);
        return altura;
    }

    // Diferenciar valores duplicados pelo índice
    if (valor < (*raiz)->valor || (valor == (*raiz)->valor && indice < (*raiz)->indice)) {
        return inserir(&((*raiz)->esq), valor, indice, altura + 1);
    } else if (valor > (*raiz)->valor || (valor == (*raiz)->valor && indice > (*raiz)->indice)) {
        return inserir(&((*raiz)->dir), valor, indice, altura + 1);
    }

    return altura; // Caso o valor já esteja na árvore, mantemos a altura
}

No* maximo(No* raiz) {
    if (raiz == NULL) return NULL;
    while (raiz->dir != NULL) {
        raiz = raiz->dir;
    }
    return raiz;
}

int alturaMaxima(No* raiz) {
    if (raiz == NULL) return -1;
    int esq = alturaMaxima(raiz->esq);
    int dir = alturaMaxima(raiz->dir);
    return (esq > dir ? esq : dir) + 1;
}

No* predecessor(No* raiz, int valor, int indice, No* pred) {
    if (raiz == NULL) return pred;
    
    if (valor > raiz->valor || (valor == raiz->valor && indice > raiz->indice)) {
        return predecessor(raiz->dir, valor, indice, raiz);
    } else {
        return predecessor(raiz->esq, valor, indice, pred);
    }
}

void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

FILE* abrirArquivoEntrada(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }
    return fp;
}

FILE* abrirArquivoSaida(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "w");
    if (fp == NULL) {
        printf("Erro ao criar o arquivo de saída: %s\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }
    return fp;
}

void processarArquivo(FILE *entrada, FILE *saida) {
    char linha[1024];
    int valores[1000]; // Array auxiliar para armazenar os valores
    int qtdValores;

    while (fgets(linha, sizeof(linha), entrada)) {
        No* raiz = NULL;
        int numero, i = 0;
        char *ptr = linha;

        qtdValores = 0;
        
        // Primeiro, armazenamos os valores no array
        while (sscanf(ptr, "%d", &numero) == 1) {
            valores[qtdValores++] = numero;
            ptr = strchr(ptr, ' ');
            if (!ptr) break;
            ptr++;
        }

        // Agora, inserimos na árvore usando o índice correto
        for (i = 0; i < qtdValores; i++) {
            int altura = inserir(&raiz, valores[i], i, 0);
            fprintf(saida, "%d ", altura);
        }

        No* maxNo = maximo(raiz);
        int hMax = alturaMaxima(raiz);
        No* predNo = NULL;
        
        if (maxNo != NULL) {
            predNo = predecessor(raiz, maxNo->valor, maxNo->indice, NULL);
        }

        if (maxNo != NULL) {
            fprintf(saida, "max %d alt %d pred ", maxNo->valor, hMax);
        }

        if (predNo != NULL) {
            fprintf(saida, "%d\n", predNo->valor);
        } else {
            fprintf(saida, "NaN\n");
        }

        liberarArvore(raiz);
    }
}

int main() {
    FILE *entrada = abrirArquivoEntrada("L2Q1.in");
    FILE *saida = abrirArquivoSaida("L2Q1.out");

    processarArquivo(entrada, saida);

    fclose(entrada);
    fclose(saida);

    printf("Arquivo de saída gerado: L2Q1.out\n");
    return EXIT_SUCCESS;
}


/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int valor;
    struct No *esq, *dir;
} No;

No* novoNo(int valor) {
    No* no = (No*)malloc(sizeof(No));
    no->valor = valor;
    no->esq = no->dir = NULL;
    return no;
}

int inserir(No** raiz, int valor, int altura) {
    if (*raiz == NULL) {
        *raiz = novoNo(valor);
        return altura;
    }
    if (valor < (*raiz)->valor) {
        return inserir(&((*raiz)->esq), valor, altura + 1);
    } else {
        return inserir(&((*raiz)->dir), valor, altura + 1);
    }
}

No* maximo(No* raiz) {
    if (raiz == NULL) return NULL;
    while (raiz->dir != NULL) {
        raiz = raiz->dir;
    }
    return raiz;
}

int alturaMaxima(No* raiz) {
    if (raiz == NULL) return -1;
    int esq = alturaMaxima(raiz->esq);
    int dir = alturaMaxima(raiz->dir);
    return (esq > dir ? esq : dir) + 1;
}

No* predecessor(No* raiz, int valor, No* pred) {
    if (raiz == NULL) return pred;
    if (valor > raiz->valor) {
        return predecessor(raiz->dir, valor, raiz);
    } else {
        return predecessor(raiz->esq, valor, pred);
    }
}

void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

FILE* abrirArquivoEntrada(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de entrada: %s\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }
    return fp;
}

FILE* abrirArquivoSaida(char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "w");
    if (fp == NULL) {
        printf("Erro ao criar o arquivo de saída: %s\n", nomeArquivo);
        exit(EXIT_FAILURE);
    }
    return fp;
}

void processarArquivo(FILE *entrada, FILE *saida) {
    char linha[1024];
    while (fgets(linha, sizeof(linha), entrada)) {
        No* raiz = NULL;
        int numero;
        char *ptr = linha;

        while (sscanf(ptr, "%d", &numero) == 1) {
            int altura = inserir(&raiz, numero, 0);
            fprintf(saida, "%d ", altura);
            ptr = strchr(ptr, ' ');
            if (!ptr) break;
            ptr++;
        }

        No* maxNo = maximo(raiz);
        int hMax = alturaMaxima(raiz);
        No* predNo = NULL;
        
        if (maxNo != NULL) {
            predNo = predecessor(raiz, maxNo->valor, NULL);
        }

        if (maxNo != NULL) {
            fprintf(saida, "max %d alt %d pred ", maxNo->valor, hMax);
        }

        if (predNo != NULL) {
            fprintf(saida, "%d\n", predNo->valor);
        } else {
            fprintf(saida, "NaN\n");
        }

        liberarArvore(raiz);
    }
}

int main() {
    FILE *entrada = abrirArquivoEntrada("L2Q1.in");
    FILE *saida = abrirArquivoSaida("L2Q1.out");

    processarArquivo(entrada, saida);

    fclose(entrada);
    fclose(saida);

    printf("Arquivo de saída gerado: L2Q1.out\n");
    return EXIT_SUCCESS;
}*/