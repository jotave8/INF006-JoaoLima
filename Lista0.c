#include <stdio.h>
#include <math.h>

// Estrutura para representar um ponto no espaço
typedef struct {
    double x, y;
} Ponto;

// Função para calcular a distância de um ponto até a origem (0, 0)
double distanciaOrigem(Ponto p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

// Função para ordenar os pontos pela distância até a origem
void ordenarPontos(Ponto pontos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (distanciaOrigem(pontos[j]) > distanciaOrigem(pontos[j + 1])) {
                Ponto temp = pontos[j];
                pontos[j] = pontos[j + 1];
                pontos[j + 1] = temp;
            }
        }
    }
}

// Função para calcular a distância total entre pontos consecutivos
double calcularDistanciaTotal(Ponto pontos[], int n) {
    double soma = 0.0;
    for (int i = 0; i < n - 1; i++) {
        double dx = pontos[i + 1].x - pontos[i].x;
        double dy = pontos[i + 1].y - pontos[i].y;
        soma += sqrt(dx * dx + dy * dy);
    }
    return soma;
}

// Função para calcular a distância direta entre o primeiro e o último ponto
double calcularShortcut(Ponto pontos[], int n) {
    double dx = pontos[n - 1].x - pontos[0].x;
    double dy = pontos[n - 1].y - pontos[0].y;
    return sqrt(dx * dx + dy * dy);
}

// Função para realizar os testes com pontos pré-definidos
void testarPrograma() {
    Ponto pontos[] = {
        {-2, -1},
        {4, 2}, 
        {4, 0},
        {2, 2},
        {8, 6}
    };
    int n = 5;

    // Calcula as distâncias
    double distanciaTotal = calcularDistanciaTotal(pontos, n);
    double shortcut = calcularShortcut(pontos, n);

    // Ordena os pontos pela distância até a origem
    ordenarPontos(pontos, n);

    // Exibe os pontos ordenados
    printf("points ");
    for (int i = 0; i < n; i++) {
        if (pontos[i].x == (int)pontos[i].x) {
            printf("(%d, ", (int)pontos[i].x);
        } else {
            printf("(%.2lf, ", pontos[i].x);
        }

        if (pontos[i].y == (int)pontos[i].y) {
            printf("%d) ", (int)pontos[i].y);
        } else {
            printf("%.2lf) ", pontos[i].y);
        }
    }

    // Exibe as distâncias
    printf("distance %.2lf shortcut %.2lf\n", distanciaTotal, shortcut);
}

// Função principal
int main() {
    testarPrograma();
    return 0;
}
