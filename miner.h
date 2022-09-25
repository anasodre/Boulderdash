#ifndef __MINER__
#define __MINER__

// Inicializa o minerador
void init_miner(int x, int y);

// Checa se um elemento type esta na mesma posicao que o minerador
int check_collisions_miner(int type);

// Move o jogador para a direita
void move_miner_right();

// Move o jogador para a esquerda
void move_miner_left();

// Move o jogador para cima
void move_miner_up();

// Move o jogador para baixo
void move_miner_down();

// Atualiza a posicao do jogador
void update_miner();

// Retorna se naquela posicao o minerador tambem esta ocupando
// independente do tipo
int collision_miner(int i, int j);

// Verifica se o minerador esta nos arredores de um elemento
void check_sides(int i, int j);

// Reinicia o minerador
void reinit_miner();

#endif