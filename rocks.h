#ifndef __ROCKS__
#define __ROCKS__

// Procura por determinada rocha para mover ela quando necessario
void search_rock(int x, int y, int move);

// Remove uma rocha ou diamante
void remove_rock(int x, int y);

// Cria e inicializa uma rocha ou diamante
ROCK_T *create_rock(int x, int y, int type);

// Insere uma rocha ou diamante na lista
void insert_rock(int x, int y, int type);

// Retorna para qual lado a pedra deve cair ou nao
int falling_by_side(int i, int j);

// Enche os arredores de diamante
void fill_with_diamonds(int i, int j);

// Atualiza a posicao da rocha
void update_rock();

#endif