#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int exercitos;
    int dono;              // 1 = jogador, 2 = inimigo
} Territorio;

// ------------ FUNCOES ------------- //

Territorio* criarTerritorios(int qtd) {
    Territorio* t = (Territorio*) malloc(qtd * sizeof(Territorio));

    if (!t) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    return t;
}

void inicializarTerritorios(Territorio* t, int qtd) {
    for (int i = 0; i < qtd; i++) {
        sprintf(t[i].nome, "Territorio_%d", i + 1);
        t[i].exercitos = 5 + (rand() % 10);
        t[i].dono = (i % 2 == 0) ? 1 : 2; // alterna: um do jogador, outro do inimigo
    }
}

void mostrarMapa(Territorio* t, int qtd) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %s | Exercitos: %d | Dono: %s\n",
            i,
            t[i].nome,
            t[i].exercitos,
            (t[i].dono == 1) ? "Jogador" : "Inimigo");
    }
}

void atacar(Territorio* t, int origem, int alvo) {
    if (t[origem].dono != 1) {
        printf("Voce so pode atacar a partir de territorios seus!\n");
        return;
    }

    if (t[alvo].dono == 1) {
        printf("Nao pode atacar seu proprio territorio!\n");
        return;
    }

    printf("\nAtaque iniciado!\n");

    if (t[origem].exercitos <= 1) {
        printf("Territorio de origem nao tem exercitos suficientes!\n");
        return;
    }

    int forcaJogador = (rand() % t[origem].exercitos);
    int forcaInimigo = (rand() % t[alvo].exercitos);

    printf("Forca do ataque: %d\n", forcaJogador);
    printf("Forca da defesa: %d\n", forcaInimigo);

    if (forcaJogador > forcaInimigo) {
        printf("Voce conquistou o territorio %s!\n", t[alvo].nome);
        t[alvo].dono = 1;
        t[alvo].exercitos = forcaJogador - forcaInimigo + 1;
    } else {
        printf("Ataque falhou! Voce perdeu tropas.\n");
        t[origem].exercitos -= (forcaInimigo - forcaJogador);
        if (t[origem].exercitos < 1)
            t[origem].exercitos = 1;
    }
}

int verificarVitoria(Territorio* t, int qtd) {
    for (int i = 0; i < qtd; i++) {
        if (t[i].dono == 2)
            return 0; // ainda ha territorios inimigos
    }
    return 1; // vitoria
}

// ------------ PROGRAMA PRINCIPAL ------------- //

int main() {
    int qtd = 6;
    Territorio* mapa = criarTerritorios(qtd);

    inicializarTerritorios(mapa, qtd);

    int opcao, o, a;

    while (1) {
        mostrarMapa(mapa, qtd);

        if (verificarVitoria(mapa, qtd)) {
            printf("\n=======================\n");
            printf(" PARABENS! VOCE VENCEU!\n");
            printf("=======================\n");
            break;
        }

        printf("\n1 - Atacar\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 0)
            break;

        printf("Origem (Indice): ");
        scanf("%d", &o);
        printf("Alvo (Indice): ");
        scanf("%d", &a);

        if (o < 0 || o >= qtd || a < 0 || a >= qtd) {
            printf("Indices invalidos!\n");
            continue;
        }

        atacar(mapa, o, a);
    }

    free(mapa);
    return 0;
}
