#ifndef __GAME_VIEW_LIB__
#define __GAME_VIEW_LIB__

#include "gamestate.h"

extern char* strdup(const char*);

// Desenha a barra com as informacoes do jogador
void print_score();

// Desenha a tela com os scores
void print_final_score();

// Desenha a tela inicial
void print_start_game();

// Desenha a tela de instrucoes
void print_instructions();

// Algoritmo de ordenacao, escolhido por se tratar de um vetor pequeno
void insertion_sort(USER_T **top_5, int size);

// Salva o score em um arquivo
void save_score();

// Le o nome do usuario
void get_user(ALLEGRO_EVENT event);

#endif