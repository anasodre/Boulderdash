#ifndef __GAMESTATE__
#define __GAMESTATE__

#include <string.h>

char username[50];
USER_T *top_5;

// Inicializa as configuracoes do alegro para o jogo
void state_init();

// Inicia os elementos do jogo
void state_serve();

// Inicia o jogo
void state_play();

// Prepara o fim do jogo, quando o jogador ganha ou perde
void state_over();

// Destroi os elementos do Allegro e do jogo quando fecha a janela
void state_close();

#endif