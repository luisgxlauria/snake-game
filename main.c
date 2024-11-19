#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "keyboard.h"
#include "screen.h"
#include "timer.h"
#include "score.h"

#define COLUNAS 40
#define LINHAS 19
#define MAX_SCORES 5
#define INCREMENTO_VELOCIDADE 5
#define NUM_OBSTACULOS 5
#define VELOCIDADE_MINIMA 20

typedef struct {
    int x, y;
} Coordenada;

typedef struct {
    Coordenada *posicao;
    int tamanho;
    int capacidade;
    int velocidade;
} Cobra;

typedef struct {
    Coordenada posicao;
} Food;

Cobra cobra;
Food food;
Coordenada obstaculos[NUM_OBSTACULOS];
int sair = 0, fimDoJogo = 0, pausado = 0;
int direcaox = 1, direcaoy = 0;
int scores[MAX_SCORES];
int tipoComida;

void initializeGame();
void generateObstacles();
void generateFood();

void initializeGame() {
    screenHideCursor();
    keyboardInit();
    timerInit(55);
    loadScores(scores);

    cobra.tamanho = 1;
    cobra.capacidade = 10;
    cobra.velocidade = 55;
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
void generateObstacles() {
    for (int i = 0; i < NUM_OBSTACULOS; i++) {
        int valid;
        do {
            valid = 1;
            obstaculos[i].x = rand() % COLUNAS;
            obstaculos[i].y = rand() % LINHAS;

            if (obstaculos[i].x == cobra.posicao[0].x && obstaculos[i].y == cobra.posicao[0].y) {
                valid = 0;
            }
        } while (!valid);
    }
}

void generateFood() {
    int valid;
    do {
        valid = 1;
        food.posicao.x = rand() % COLUNAS;
        food.posicao.y = rand() % LINHAS;
        tipoComida = rand() % 3;

        for (int i = 0; i < cobra.tamanho; i++) {
            if (cobra.posicao[i].x == food.posicao.x && cobra.posicao[i].y == food.posicao.y) {
                valid = 0;
                break;
            }
        }

        for (int i = 0; i < NUM_OBSTACULOS; i++) {
            if (obstaculos[i].x == food.posicao.x && obstaculos[i].y == food.posicao.y) {
                valid = 0;
                break;
            }
        }
    } while (valid == 0);
}

void drawBorders();
void showScoreAndHints();

void drawBorders() {
    screenClear();
    printf("\u250c");
    for (int i = 0; i < COLUNAS; i++)
        printf("\u2500");
    printf("\u2510\n");
    for (int j = 0; j < LINHAS; j++) {
        printf("\u2502");
        for (int i = 0; i < COLUNAS; i++)
            printf(" ");
        printf("\u2502\n");
    }
    printf("\u2514");
    for (int i = 0; i < COLUNAS; i++)
        printf("\u2500");
    printf("\u2518\n");

    showScoreAndHints();
}

void showScoreAndHints() {
    screenGotoxy(0, LINHAS + 1);
    if (pausado) {
        printf("Jogo Pausado. Pressione 'P' para continuar.");
    } else {
        printf("Pontuação: %d | Use 'WASD' para mover, 'Q' para sair, 'P' para pausar", cobra.tamanho - 1);
    }
}

void drawFood();
void drawGame();

void drawFood() {
    screenGotoxy(food.posicao.x, food.posicao.y);
    switch (tipoComida) {
        case 0:
            screenSetColor(RED, BLACK);
            printf("\u2665");
            break;
        case 1:
            screenSetColor(YELLOW, BLACK);
            printf("\u2666");
            break;
        case 2:
            screenSetColor(MAGENTA, BLACK);
            printf("\u2663");
            break;
    }
}

void drawGame() {
    drawFood();

    screenGotoxy(cobra.posicao[cobra.tamanho - 1].x, cobra.posicao[cobra.tamanho - 1].y);
    printf(" ");

    screenSetColor(LIGHTGREEN, BLACK);
    screenGotoxy(cobra.posicao[0].x, cobra.posicao[0].y);
    printf("\u25a0");

    screenSetColor(GREEN, BLACK);
    for (int i = 1; i < cobra.tamanho; i++) {
        screenGotoxy(cobra.posicao[i].x, cobra.posicao[i].y);
        printf("\u2592");
    }

    screenSetNormal();
    screenUpdate();
}