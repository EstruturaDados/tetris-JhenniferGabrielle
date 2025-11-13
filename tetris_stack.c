#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5  // tamanho fixo da fila

// Estrutura que representa uma peça do Tetris
typedef struct {
    char nome;  // tipo da peça ('I', 'O', 'T', 'L')
    int id;     // identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca pecas[TAM_FILA];
    int frente, tras, qtd;
} Fila;

// Inicializa a fila vazia
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->qtd = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->qtd == TAM_FILA;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->qtd == 0;
}

// Gera uma nova peça aleatória
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Insere nova peça no final da fila (enqueue)
void enfileirar(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia! Não é possível adicionar nova peça.\n");
        return;
    }
    f->tras = (f->tras + 1) % TAM_FILA;
    f->pecas[f->tras] = p;
    f->qtd++;
}

// Remove a peça da frente da fila (dequeue)
void desenfileirar(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia! Nenhuma peça para jogar.\n");
        return;
    }
    printf("Peça jogada: [%c %d]\n", f->pecas[f->frente].nome, f->pecas[f->frente].id);
    f->frente = (f->frente + 1) % TAM_FILA;
    f->qtd--;
}

// Mostra o estado atual da fila
void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }

    printf("\nFila de peças:\n");
    int i, idx;
    for (i = 0; i < f->qtd; i++) {
        idx = (f->frente + i) % TAM_FILA;
        printf("[%c %d] ", f->pecas[idx].nome, f->pecas[idx].id);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    Fila fila;
    inicializarFila(&fila);

    int opcao, id = 0;

    // Inicializa com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca(id++));
    }

    do {
        exibirFila(&fila);
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                desenfileirar(&fila);
                break;
            case 2:
                enfileirar(&fila, gerarPeca(id++));
                break;
            case 0:
                printf("Encerrando o jogo.\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
