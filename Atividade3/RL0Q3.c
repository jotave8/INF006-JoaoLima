#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do nó da árvore
typedef struct No {
    int valor;
    struct No *esq, *dir;
} No;

// Função para criar um novo nó
No* novoNo(int valor) {
    No* no = (No*)malloc(sizeof(No));
    no->valor = valor;
    no->esq = no->dir = NULL;
    return no;
}

// Função para inserir um valor na árvore
No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        return novoNo(valor);
    }
    if (valor < raiz->valor) {
        raiz->esq = inserir(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = inserir(raiz->dir, valor);
    }
    return raiz;
}

// Função para encontrar o nó com o menor valor (usado na remoção)
No* encontrarMinimo(No* raiz) {
    while (raiz->esq != NULL) {
        raiz = raiz->esq;
    }
    return raiz;
}

// Função para remover um valor da árvore
No* remover(No* raiz, int valor) {
    if (raiz == NULL) {
        return NULL; 
    }
    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        No* temp = encontrarMinimo(raiz->dir);
        raiz->valor = temp->valor;
        raiz->dir = remover(raiz->dir, temp->valor);
    }
    return raiz;
}

// Função para verificar se um valor existe na árvore
int existe(No* raiz, int valor) {
    if (raiz == NULL) {
        return 0;
    }
    if (valor < raiz->valor) {
        return existe(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        return existe(raiz->dir, valor);
    } else {
        return 1;
    }
}

// Função para calcular a altura de um nó
int altura(No* raiz) {
    if (raiz == NULL) {
        return -1;
    }
    int esq = altura(raiz->esq);
    int dir = altura(raiz->dir);
    return (esq > dir ? esq : dir) + 1;
}

// Função para percorrer a árvore em ordem e imprimir os valores e alturas
void inOrder(No* raiz, FILE* saida) {
    if (raiz != NULL) {
        inOrder(raiz->esq, saida);
        fprintf(saida, "%d (%d) ", raiz->valor, altura(raiz));
        inOrder(raiz->dir, saida);
    }
}

// Função para liberar a memória da árvore
void liberarArvore(No* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

// Função principal
int main() {
    FILE *entrada = fopen("L2Q3.in", "r");
    FILE *saida = fopen("L2Q3.out", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return EXIT_FAILURE;
    }

    No* raiz = NULL; // Árvore única para todas as operações
    char linha[1024];

    while (fgets(linha, sizeof(linha), entrada)) {
        char *ptr = linha;
        char operacao;
        int valor;

        while (*ptr) { // Percorre a linha inteira corretamente
            while (*ptr == ' ') ptr++; // Ignora espaços
            if (sscanf(ptr, "%c %d", &operacao, &valor) != 2) break;

            if (operacao == 'a') {
                raiz = inserir(raiz, valor);
            } else if (operacao == 'r') {
                if (existe(raiz, valor)) {
                    raiz = remover(raiz, valor);
                } else {
                    raiz = inserir(raiz, valor); // Se não existe, adiciona
                }
            }

            while (*ptr && *ptr != ' ') ptr++; // Avança para o próximo número
            while (*ptr == ' ') ptr++; // Pula espaços extras
        }

        inOrder(raiz, saida);
        fprintf(saida, "\n");
    }

    fclose(entrada);
    fclose(saida);
    liberarArvore(raiz);
    printf("Arquivo de saída gerado: L2Q3.out\n");
    return EXIT_SUCCESS;
}
