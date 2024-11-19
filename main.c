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

