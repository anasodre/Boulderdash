#include "gamelib.h"
#include "miner.h"

// Inicializa o minerador
void init_miner(int x, int y) {

    miner.x = x;
    miner.y = y;
    miner.velocity = 8;
    miner.alive = true;
    miner.lives = 3;
    miner.points = 0;
    miner.num_diamonds = 0;
    miner.img = 0;
    miner.power = 1;
}

// Checa se um elemento type esta na mesma posicao que o minerador
int check_collisions_miner(int type) {
    int i, j;
    j = (miner.x) / (BLOCK_H * SPRITES_SCALE);
    i = (miner.y - BLOCK_W * SPRITES_SCALE) / (BLOCK_W * SPRITES_SCALE);

    if ((game_tab[i][j].sprite == type) && (miner.x == game_tab[i][j].x) && (miner.y == game_tab[i][j].y)) {
        return 1;
    }
    return 0;
}

// Move o jogador para a direita
void move_miner_right() {
    miner.x += miner.velocity;

    int i, j, push = 0;

    // Verifica se ele chegou na saida
    if (check_collisions_miner(exit_s)) {
        state = OVER;
        return;
    }

    // Verifica se ha uma rocha na posicao que quer chegar
    push = check_collisions_miner(rock_s);

    // Checa se pegou um diamante
    if (check_collisions_miner(diamond_s)) {
        miner.points += 30;
        miner.num_diamonds++;
        remove_rock(miner.x, miner.y);
        al_play_sample(get_diamonds, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }

    // Checa se encontrou uma barreira
    if (check_collisions_miner(steelWall_s) || check_collisions_miner(wall_s) || check_collisions_miner(rock_s))
        miner.x -= miner.velocity;

    j = (miner.x) / (BLOCK_H * SPRITES_SCALE);
    i = (miner.y - BLOCK_W * SPRITES_SCALE) / (BLOCK_W * SPRITES_SCALE);

    // Faz o caminho
    if (game_tab[i][j - 1].sprite == player_s) {
        game_tab[i][j - 1].sprite = empty_s;
        game_tab[i][j].sprite = player_s;
    }

    // Verifica se pode empurrar se houver alguma rocha na direita
    if ((push) && (game_tab[i][j + 2].sprite == empty_s)) {
        search_rock(game_tab[i][j + 1].x, game_tab[i][j + 1].y, BLOCK_W * SPRITES_SCALE);
        game_tab[i][j + 2].sprite = rock_s;
        game_tab[i][j + 1].sprite = player_s;
        miner.x += miner.velocity;
        game_tab[i][j].sprite = empty_s;
    }

    // Atualiza a imagem
    if (miner.img == 6)
        miner.img = 7;
    else
        miner.img = 6;
}

// Move o jogador para a esquerda
void move_miner_left() {
    miner.x -= miner.velocity;

    int i, j, push;

    // Verifica se ele chegou na saida
    if (check_collisions_miner(exit_s)) {
        state = OVER;
        return;
    }

    // Verifica se ha uma rocha na posicao que quer chegar
    push = check_collisions_miner(rock_s);

    // Checa se pegou um diamante
    if (check_collisions_miner(diamond_s)) {
        miner.points += 30;
        miner.num_diamonds++;
        remove_rock(miner.x, miner.y);
        al_play_sample(get_diamonds, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }

    // Checa se encontrou uma barreira
    if (check_collisions_miner(steelWall_s) || check_collisions_miner(wall_s) || check_collisions_miner(rock_s))
        miner.x += miner.velocity;

    j = (miner.x) / (BLOCK_H * SPRITES_SCALE);
    i = (miner.y - BLOCK_W * SPRITES_SCALE) / (BLOCK_W * SPRITES_SCALE);

    // Faz o caminho
    if (game_tab[i][j + 1].sprite == player_s) {
        game_tab[i][j + 1].sprite = empty_s;
        game_tab[i][j].sprite = player_s;
    }

    // Verifica se pode empurrar se houver alguma rocha na esquerda
    if ((push) && (game_tab[i][j - 2].sprite == empty_s)) {
        search_rock(game_tab[i][j - 1].x, game_tab[i][j - 1].y, -BLOCK_W * SPRITES_SCALE);
        game_tab[i][j - 2].sprite = rock_s;
        game_tab[i][j - 1].sprite = player_s;
        miner.x -= miner.velocity;
        game_tab[i][j].sprite = empty_s;
    }

    // Atualiza a imagem
    if (miner.img == 4)
        miner.img = 5;
    else
        miner.img = 4;
}

// Move o jogador para cima
void move_miner_up() {
    miner.y -= miner.velocity;

    int i, j;

    // Verifica se ele chegou na saida
    if (check_collisions_miner(exit_s)) {
        state = OVER;
        return;
    }

    // Checa se pegou um diamante
    if (check_collisions_miner(diamond_s)) {
        miner.points += 30;
        miner.num_diamonds++;
        remove_rock(miner.x, miner.y);
        al_play_sample(get_diamonds, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }

    // Checa se encontrou uma barreira
    if (check_collisions_miner(steelWall_s) || check_collisions_miner(wall_s) || check_collisions_miner(rock_s))
        miner.y += miner.velocity;

    j = (miner.x) / (BLOCK_H * SPRITES_SCALE);
    i = (miner.y - BLOCK_W * SPRITES_SCALE) / (BLOCK_W * SPRITES_SCALE);

    // Faz o caminho
    if (game_tab[i + 1][j].sprite == player_s)
        game_tab[i + 1][j].sprite = empty_s;
    game_tab[i][j].sprite = player_s;

    // Atualiza a imagem
    if (miner.img == 2)
        miner.img = 3;
    else
        miner.img = 2;
}

// Move o jogador para baixo
void move_miner_down() {
    miner.y += miner.velocity;

    int i, j;

    // Verifica se ele chegou na saida
    if (check_collisions_miner(exit_s)) {
        state = OVER;
        return;
    }
    
    // Checa se pegou um diamante
    if (check_collisions_miner(diamond_s)) {
        miner.points += 30;
        miner.num_diamonds++;
        remove_rock(miner.x, miner.y);
        al_play_sample(get_diamonds, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }

    // Checa se encontrou uma barreira
    if (check_collisions_miner(steelWall_s) || check_collisions_miner(wall_s) || check_collisions_miner(rock_s))
        miner.y -= miner.velocity;

    j = (miner.x) / (BLOCK_H * SPRITES_SCALE);
    i = (miner.y - BLOCK_W * SPRITES_SCALE) / (BLOCK_W * SPRITES_SCALE);

    // Faz o caminho
    if (game_tab[i - 1][j].sprite == player_s)
        game_tab[i - 1][j].sprite = empty_s;
    game_tab[i][j].sprite = player_s;

    // Atualiza a imagem
    if (miner.img == 0)
        miner.img = 1;
    else
        miner.img = 0;
}

// Atualiza os movimentos do minerador
void update_miner() {

    // Movimenta o minerador de acordo com as setas do teclado
    if (keys[LEFT])
        move_miner_left();
    if (keys[RIGHT])
        move_miner_right();
    if (keys[UP])
        move_miner_up();
    if (keys[DOWN])
        move_miner_down();
    if (keys[CTRL] && keys[ENTER] && miner.power) {
        miner.power = 0;
        if (miner.lives < 3)
            miner.lives++;
    }
}

// Retorna se naquela posicao o minerador tambem esta ocupando
int collision_miner(int i, int j) {
    if ((game_tab[i][j].x == miner.x) && (game_tab[i][j].y == miner.y))
        return 1;
    return 0;
}

// Verifica se o minerador esta nos arredores de um elemento
void check_sides(int i, int j) {

    if (collision_miner(i, j)) {
        miner.alive = false;
        miner.lives--;
        return;
    }
    if (collision_miner(i + 1, j)) {
        miner.alive = false;
        miner.lives--;
        return;
    }
    if (collision_miner(i - 1, j)) {
        miner.alive = false;
        miner.lives--;
        return;
    }
    if (collision_miner(i, j + 1)) {
        miner.alive = false;
        miner.lives--;
        return;
    }
    if (collision_miner(i, j - 1)) {
        miner.alive = false;
        miner.lives--;
        return;
    }
}

// Reinicia o minerador
void reinit_miner() {
    miner.alive = true;
    miner.power = 1;
    int i, j;
    j = (miner.x) / (BLOCK_H * SPRITES_SCALE);
    i = (miner.y - BLOCK_W * SPRITES_SCALE) / (BLOCK_W * SPRITES_SCALE);
    game_tab[i][j].sprite = empty_s;

    miner.x = 8;
    miner.y = 16;

    j = (miner.x) / (BLOCK_H * SPRITES_SCALE);
    i = (miner.y - BLOCK_W * SPRITES_SCALE) / (BLOCK_W * SPRITES_SCALE);
    game_tab[i][j].sprite = player_s;
}