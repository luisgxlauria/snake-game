#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "keyboard.h"
#include "screen.h"
#include "timer.h"
#include "score.h"
#include <time.h>

#define COLUNAS 40
#define LINHAS 19
#define MAX_SCORES 5
#define NUM_OBSTACULOS 5
#define VELOCIDADE_INICIAL 55
#define VELOCIDADE_MINIMA 20
#define INCREMENTO_VELOCIDADE 5
#define NUM_COMIDAS 3  // Normal, Especial, Venenosa


typedef struct {
    int x, y;
} Coordenada;

typedef struct {
    Coordenada *posicao;
    int tamanho;
    int capacidade;
} Cobra;

typedef enum {
    COMIDA_NORMAL,
    COMIDA_ESPECIAL,
    COMIDA_VENENOSA
} TipoComida;

typedef struct {
    Coordenada posicao;
    TipoComida tipo;
} Food;

Cobra cobra;
Food foods[NUM_COMIDAS];
Food food;
Coordenada obstaculos[NUM_OBSTACULOS];
int sair = 0;
int fimDoJogo = 0;
int direcaox = 1, direcaoy = 0;
int scores[MAX_SCORES];
int velocidade = VELOCIDADE_INICIAL;


/* Declaração das funções */
void initializeGame();
void drawGame();
void updateGame();
void generateFood();
///void saveScore(int score);
///void loadScores();
///void displayScores();
void drawBorders();
void generateObstacles();
void drawObstacles();

void generateObstacles() {
    for (int i = 0; i < NUM_OBSTACULOS; i++) {
        int valid;
        do {
            valid = 1;
            obstaculos[i].x = rand() % COLUNAS;
            obstaculos[i].y = rand() % LINHAS;

            // Verificar se o obstáculo não está na cobra ou na comida
            if (obstaculos[i].x == cobra.posicao[0].x && obstaculos[i].y == cobra.posicao[0].y) {
                valid = 0;
            } else if (obstaculos[i].x == food.posicao.x && obstaculos[i].y == food.posicao.y) {
                valid = 0;
            } else {
                for (int j = 0; j < cobra.tamanho; j++) {
                    if (obstaculos[i].x == cobra.posicao[j].x && obstaculos[i].y == cobra.posicao[j].y) {
                        valid = 0;
                        break;
                    }
                }
                for (int j = 0; j < i; j++) {
                    if (obstaculos[i].x == obstaculos[j].x && obstaculos[i].y == obstaculos[j].y) {
                        valid = 0;
                        break;
                    }
                }
            }
        } while (!valid);
    }
}

void generateFood() {
    for (int f = 0; f < NUM_COMIDAS; f++) {
        int valid;
        int attempts = 0;
        do {
            valid = 1;
            foods[f].posicao.x = rand() % COLUNAS;
            foods[f].posicao.y = rand() % LINHAS;
            foods[f].tipo = rand() % 3;

            // Verificar se a posição coincide com a cobra
            for (int i = 0; i < cobra.tamanho; i++) {
                if (cobra.posicao[i].x == foods[f].posicao.x && cobra.posicao[i].y == foods[f].posicao.y) {
                    valid = 0;
                    break;
                }
            }

            // Verificar se a posição coincide com os obstáculos
            if (valid) {
                for (int i = 0; i < NUM_OBSTACULOS; i++) {
                    if (obstaculos[i].x == foods[f].posicao.x && obstaculos[i].y == foods[f].posicao.y) {
                        valid = 0;
                        break;
                    }
                }
            }

            // Verificar se a posição coincide com outras comidas já geradas
            if (valid) {
                for (int i = 0; i < f; i++) {
                    if (foods[i].posicao.x == foods[f].posicao.x && foods[i].posicao.y == foods[f].posicao.y) {
                        valid = 0;
                        break;
                    }
                }
            }

            attempts++;
            if (attempts > 1000) {
                printf("Erro: Não foi possível gerar comida após 1000 tentativas.\n");
                exit(EXIT_FAILURE);
            }

        } while (!valid);
    }
}


void initializeGame() {
    srand(time(NULL));
    screenHideCursor();
    keyboardInit();
    timerInit(velocidade);
    loadScores(scores);

    cobra.tamanho = 1;
    cobra.capacidade = 10;
    cobra.posicao = (Coordenada *)malloc(cobra.capacidade * sizeof(Coordenada));
    if (cobra.posicao == NULL) {
        printf("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    cobra.posicao[0].x = COLUNAS / 2;
    cobra.posicao[0].y = LINHAS / 2;

    generateObstacles();
    generateFood();
}

void drawBorders() {
    screenClear();
    printf("┌");
    for (int i = 0; i < COLUNAS; i++)
        printf("─");
    printf("┐\n");
    for (int j = 0; j < LINHAS; j++) {
        printf("│");
        for (int i = 0; i < COLUNAS; i++)
            printf(" ");
        printf("│\n");
    }

    printf("└");
    for (int i = 0; i < COLUNAS; i++)
        printf("─");
    printf("┘");
}

void drawObstacles() {
    for (int i = 0; i < NUM_OBSTACULOS; i++) {
        screenGotoxy(obstaculos[i].x + 1, obstaculos[i].y + 1);
        screenSetColor(BLUE, BLACK);
        printf("█");
    }
    screenSetNormal();
}

void drawGame() {
    // Desenhar a comida
    for (int f = 0; f < NUM_COMIDAS; f++) {
        screenGotoxy(foods[f].posicao.x + 1, foods[f].posicao.y + 1);
        switch (foods[f].tipo) {
            case COMIDA_NORMAL:
                screenSetColor(RED, BLACK);
                printf("❤");
                break;
            case COMIDA_ESPECIAL:
                screenSetColor(YELLOW, BLACK);
                printf("★");
                break;
            case COMIDA_VENENOSA:
                screenSetColor(MAGENTA, BLACK);
                printf("☠");
                break;
        }
        screenSetNormal();
    }
    

    // Desenhar os obstáculos
    drawObstacles();

    // Desenhar a cobra
    for (int i = 0; i < cobra.tamanho; i++) {
        screenGotoxy(cobra.posicao[i].x + 1, cobra.posicao[i].y + 1);
        if (i == 0)
            printf("▓"); // Cabeça
        else
            printf("▒"); // Corpo
    }

    screenUpdate();
}

void updateGame() {
    if (fimDoJogo == 1) return;

    int newX = cobra.posicao[0].x + direcaox;
    int newY = cobra.posicao[0].y + direcaoy;

    // Verificar colisão com as paredes
    if (newX < 0 || newX >= COLUNAS || newY < 0 || newY >= LINHAS) {
        fimDoJogo = 1;
        return;
    }

    // Verificar colisão com obstáculos
    for (int i = 0; i < NUM_OBSTACULOS; i++) {
        if (obstaculos[i].x == newX && obstaculos[i].y == newY) {
            fimDoJogo = 1;
            return;
        }
    }

    // Verificar colisão com o próprio corpo
    for (int i = 1; i < cobra.tamanho; i++) {
        if (cobra.posicao[i].x == newX && cobra.posicao[i].y == newY) {
            fimDoJogo = 1;
            return;
        }
    }

    int comeuComida = 0;

    // Verificar colisão com as comidas
    for (int f = 0; f < NUM_COMIDAS; f++) {
        if (foods[f].posicao.x == newX && foods[f].posicao.y == newY) {
            // Ajustar tamanho da cobra com base no tipo de comida
            switch (foods[f].tipo) {
                case COMIDA_NORMAL:
                    cobra.tamanho++;
                    break;
                case COMIDA_ESPECIAL:
                    cobra.tamanho += 2;
                    break;
                case COMIDA_VENENOSA:
                    cobra.tamanho--;
                    if (cobra.tamanho < 1) {
                        fimDoJogo = 1;
                        return;
                    }
                    break;
            }

            // Gerenciar capacidade e realocação de memória
            if (cobra.tamanho > cobra.capacidade) {
                cobra.capacidade *= 2;
                Coordenada *novaPosicao = (Coordenada *)realloc(cobra.posicao, cobra.capacidade * sizeof(Coordenada));
                if (novaPosicao == NULL) {
                    printf("Erro ao realocar memória");
                    exit(EXIT_FAILURE);
                }
                cobra.posicao = novaPosicao;
            }

            // Regenerar a comida consumida
            int valid;
            int attempts = 0;
            do {
                valid = 1;
                foods[f].posicao.x = rand() % COLUNAS;
                foods[f].posicao.y = rand() % LINHAS;
                foods[f].tipo = rand() % 3;

                // Verificar se a posição não está ocupada
                for (int i = 0; i < cobra.tamanho; i++) {
                    if (cobra.posicao[i].x == foods[f].posicao.x && cobra.posicao[i].y == foods[f].posicao.y) {
                        valid = 0;
                        break;
                    }
                }

                for (int i = 0; i < NUM_OBSTACULOS; i++) {
                    if (obstaculos[i].x == foods[f].posicao.x && obstaculos[i].y == foods[f].posicao.y) {
                        valid = 0;
                        break;
                    }
                }

                // Verificar se a posição não coincide com outras comidas
                if (valid) {
                    for (int i = 0; i < NUM_COMIDAS; i++) {
                        if (i != f && foods[i].posicao.x == foods[f].posicao.x && foods[i].posicao.y == foods[f].posicao.y) {
                            valid = 0;
                            break;
                        }
                    }
                }

                attempts++;
                if (attempts > 1000) {
                    printf("Erro: Não foi possível regenerar comida após 1000 tentativas.\n");
                    exit(EXIT_FAILURE);
                }

            } while (!valid);

            // Ajustar velocidade
            if (velocidade > VELOCIDADE_MINIMA) {
                velocidade -= INCREMENTO_VELOCIDADE;
                timerInit(velocidade);
            }

            comeuComida = 1;
            break;
        }
    }

    if (!comeuComida) {
        // Apagar a cauda
        screenGotoxy(cobra.posicao[cobra.tamanho - 1].x + 1, cobra.posicao[cobra.tamanho - 1].y + 1);
        printf(" ");
    }

    // Mover a cobra
    for (int i = cobra.tamanho - 1; i > 0; i--) {
        cobra.posicao[i] = cobra.posicao[i - 1];
    }

    cobra.posicao[0].x = newX;
    cobra.posicao[0].y = newY;
}






int main() {
    initializeGame();
    drawBorders();
    drawGame();
    while (!sair) {
        if (timerTimeOver()) {
            if (keyhit()) {
                int tecla = readch();
                if (tecla == 27 || tecla == 'q') {
                    sair = 1;
                } else if (tecla == 'w' && direcaoy != 1) {
                    direcaox = 0;
                    direcaoy = -1;
                } else if (tecla == 'a' && direcaox != 1) {
                    direcaox = -1;
                    direcaoy = 0;
                } else if (tecla == 's' && direcaoy != -1) {
                    direcaox = 0;
                    direcaoy = 1;
                } else if (tecla == 'd' && direcaox != -1) {
                    direcaox = 1;
                    direcaoy = 0;
                }
            }

            updateGame();
            drawGame();

            if (fimDoJogo) {
                screenGotoxy(COLUNAS / 2 - 5, LINHAS / 2);
                printf("Fim do Jogo! Pontuação: %d ponto(s)", cobra.tamanho - 1);
                screenUpdate();
                getchar();

                saveScore(scores, cobra.tamanho - 1);
                displayScores(scores);

                free(cobra.posicao);
                screenShowCursor();
                keyboardDestroy();
                timerDestroy();
                return 0;
            }
        }
    }

    free(cobra.posicao);
    screenShowCursor();
    keyboardDestroy();
    timerDestroy();
    return 0;
}
