#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 1000
#define MAX_NOME 50

typedef struct ItemPilha {
    char *valor;
    struct ItemPilha *abaixo;
} ItemPilha;

typedef struct Pilha {
    ItemPilha *topo;
} Pilha;

// Inicializa a pilha
Pilha* iniciarPilha() {
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    pilha->topo = NULL;
    return pilha;
}

// Empilha um valor
void push(Pilha *pilha, const char *valor, FILE *saida) {
    ItemPilha *novo = (ItemPilha *)malloc(sizeof(ItemPilha));
    novo->valor = strdup(valor); // Copia o valor para a pilha
    novo->abaixo = pilha->topo;
    pilha->topo = novo;
    fprintf(saida, "push-%s ", valor);
}

// Desempilha um valor e conta consecutivos
int pop(Pilha *pilha) {
    if (pilha->topo == NULL) return 0;

    ItemPilha *removido = pilha->topo;
    pilha->topo = pilha->topo->abaixo;
    free(removido->valor);
    free(removido);

    return 1;
}

// Função de comparação para ordenar strings
int compararStrings(const char *a, const char *b) {
    return strcmp(a, b);
}

// Insere ordenadamente na pilha
void ordenarEInserir(Pilha *pilha, const char *novoNome, FILE *saida) {
    Pilha *temporaria = iniciarPilha();
    int contadorPops = 0;

    // Remove os elementos até encontrar a posição correta
    while (pilha->topo != NULL && compararStrings(pilha->topo->valor, novoNome) > 0) {
        push(temporaria, pilha->topo->valor, saida);
        contadorPops += pop(pilha);
    }

    // Registra os pops em sequência, se existirem
    if (contadorPops > 0) {
        fprintf(saida, "%dx-pop ", contadorPops);
    }

    // Insere o novo elemento na posição correta
    push(pilha, novoNome, saida);

    // Reinsere os elementos removidos na ordem correta
    contadorPops = 0;
    while (temporaria->topo != NULL) {
        push(pilha, temporaria->topo->valor, saida);
        contadorPops += pop(temporaria);
    }

    free(temporaria);

    // Registra os pops ao restaurar a pilha
    if (contadorPops > 0) {
        fprintf(saida, "%dx-pop ", contadorPops);
    }
}

// Processa o arquivo de entrada
void processarEntrada(char *linha, FILE *entrada, FILE *saida) {
    Pilha *pilha = iniciarPilha();

    while (fgets(linha, MAX_LINHA, entrada) != NULL) {
        char *token = strtok(linha, " \n");
        while (token != NULL) {
            ordenarEInserir(pilha, token, saida);
            token = strtok(NULL, " \n");
        }
        fprintf(saida, "\n"); // Nova linha após processar cada linha de entrada
    }

    // Limpa a pilha após o processamento
    while (pilha->topo != NULL) {
        pop(pilha);
    }

    free(pilha);
}

int main() {
    FILE *entrada = fopen("L1Q2.in", "r");
    FILE *saida = fopen("L1Q2.out", "w");

    if (!entrada || !saida) {
        fprintf(stderr, "Erro ao abrir os arquivos.\n");
        return 1;
    }

    char linha[MAX_LINHA];
    processarEntrada(linha, entrada, saida);

    fclose(entrada);
    fclose(saida);
    printf("Processamento concluído. Verifique o arquivo L1Q2.out.\n");

    return 0;
}
