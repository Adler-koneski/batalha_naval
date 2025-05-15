#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5
#define NAVIOS 3

char jogador[TAM][TAM];
char maquina[TAM][TAM];
char visivelMaquina[TAM][TAM];

// Funções
void iniciarTabuleiros();
void mostrarTabuleiro(char tabuleiro[TAM][TAM]);
void mostrarJogo();
void posicionarNavios(char tabuleiro[TAM][TAM]);
void menu();
void jogar();
int verificarFim(char tabuleiro[TAM][TAM]);
void limparBuffer();

int main() {
    menu();
    return 0;
}

void menu() {
    int opcao;

    do {
        printf("\n=== BATALHA NAVAL ===\n");
        printf("1 - Iniciar Jogo\n");
        printf("2 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                jogar();
                break;
            case 2:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 2);
}

void jogar() {
    int linha, coluna;
    int turno = 0;

    srand(time(NULL));
    iniciarTabuleiros();
    posicionarNavios(jogador);
    posicionarNavios(maquina);

    while (1) {
        mostrarJogo();

        if (turno % 2 == 0) {
            // Jogador ataca
            printf("\n--- Sua vez ---\n");
            do {
                printf("Digite linha (0 a %d): ", TAM - 1);
                scanf("%d", &linha);
                printf("Digite coluna (0 a %d): ", TAM - 1);
                scanf("%d", &coluna);
                limparBuffer();
            } while (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM);

            if (maquina[linha][coluna] == 'N') {
                printf("ACERTOU!\n");
                visivelMaquina[linha][coluna] = 'X';
                maquina[linha][coluna] = 'X';
            } else if (visivelMaquina[linha][coluna] == '~') {
                printf("AGUA!\n");
                visivelMaquina[linha][coluna] = 'O';
            } else {
                printf("Posição já atacada.\n");
                turno--;
            }
        } else {
            // Máquina ataca
            linha = rand() % TAM;
            coluna = rand() % TAM;
            printf("\n--- Vez da Máquina ---\n");
            printf("Maquina atacou (%d,%d)\n", linha, coluna);

            if (jogador[linha][coluna] == 'N') {
                printf("Maquina ACERTOU!\n");
                jogador[linha][coluna] = 'X';
            } else if (jogador[linha][coluna] == '~') {
                printf("Maquina errou.\n");
                jogador[linha][coluna] = 'O';
            }
        }

        if (verificarFim(maquina)) {
            printf("\n*** Você venceu! ***\n");
            break;
        }
        if (verificarFim(jogador)) {
            printf("\n*** A máquina venceu! ***\n");
            break;
        }

        turno++;
    }
}

void iniciarTabuleiros() {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            jogador[i][j] = '~';
            maquina[i][j] = '~';
            visivelMaquina[i][j] = '~';
        }
    }
}

void mostrarTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void mostrarJogo() {
    printf("\nSEU TABULEIRO:\n");
    mostrarTabuleiro(jogador);
    printf("\nTABULEIRO DO INIMIGO:\n");
    mostrarTabuleiro(visivelMaquina);
}

void posicionarNavios(char tabuleiro[TAM][TAM]) {
    int navios = 0;
    int linha, coluna;

    while (navios < NAVIOS) {
        linha = rand() % TAM;
        coluna = rand() % TAM;

        if (tabuleiro[linha][coluna] == '~') {
            tabuleiro[linha][coluna] = 'N';
            navios++;
        }
    }
}

int verificarFim(char tabuleiro[TAM][TAM]) {
    int i, j;

    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 'N') {
                return 0;
            }
        }
    }

    return 1;
}

void limparBuffer() {
    while (getchar() != '\n');
}
