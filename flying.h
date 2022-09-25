#ifndef __FLYING__
#define __FLYING__

#include "gamelib.h"

// Cria um elemento voador e o inicializa
FLYING_T *create_flying(int x, int y, int type);

// Insere um novo elemento voador
void insert_flying(int x, int y, int type);

// Atualiza o elemento voador e suas posicoes
void update_flying();

// Explode a borboleta
void explode_butterfly(int x, int y);

#endif