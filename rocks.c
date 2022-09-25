#include "gamelib.h"
#include "rocks.h"
#include "objects.h"

// Procura por determinada rocha para mover ela quando necessario
void search_rock(int x, int y, int move) {
    ROCK_T *aux_rock = rocks;

    while (aux_rock != NULL) {
        if ((aux_rock->x == x) && aux_rock->y == y) {
            aux_rock->x += move;
            return;
        }

        aux_rock = aux_rock->next;
    }
}

// Remove uma rocha ou diamante
void remove_rock(int x, int y) {
    ROCK_T *aux_rock = rocks, *aux_next;
    int i, j;

    while (aux_rock != NULL) {
        aux_next = aux_rock->next;

        if (aux_next != NULL) {
            if ((aux_next->x == x) && (aux_next->y == y)) {
                j = (aux_next->x) / (BLOCK_H * SPRITES_SCALE);
                i = (aux_next->y - BLOCK_W * SPRITES_SCALE) / (BLOCK_W * SPRITES_SCALE);
                game_tab[i][j].sprite = empty_s;
                aux_rock->next = aux_next->next;
                aux_next->next = NULL;
                free(aux_next);
                return;
            }
        }
        if ((aux_rock->x == x) && (aux_rock->y == y)) {
            if (aux_rock->next == NULL) {
                j = (aux_rock->x) / (BLOCK_H * SPRITES_SCALE);
                i = (aux_rock->y - BLOCK_W * SPRITES_SCALE) / (BLOCK_W * SPRITES_SCALE);
                game_tab[i][j].sprite = empty_s;
                free(aux_rock);
                return;
            }
            else {
                j = (aux_rock->x) / (BLOCK_H * SPRITES_SCALE);
                i = (aux_rock->y - BLOCK_W * SPRITES_SCALE) / (BLOCK_W * SPRITES_SCALE);
                game_tab[i][j].sprite = empty_s;
                rocks = aux_next;
                free(aux_rock);
                return;
            }
        }
        aux_rock = aux_rock->next;
    }
}

// Cria e inicializa uma rocha ou diamante
ROCK_T *create_rock(int x, int y, int type) {
    ROCK_T *aux_rock = (ROCK_T *)malloc(sizeof(ROCK_T));

    if (!aux_rock) {
        perror("Erro: Memória insuficiente");
        exit(1);
    }

    aux_rock->x = x;
    aux_rock->y = y;
    aux_rock->falling = false;
    aux_rock->type = type;
    aux_rock->img = 0;
    aux_rock->next = NULL;

    return aux_rock;
}

// Insere uma rocha ou diamante na lista
void insert_rock(int x, int y, int type) {

    if (rocks == NULL) {
        rocks = create_rock(x, y, type);
        return;
    }

    ROCK_T *aux_rock;
    aux_rock = rocks;

    while (aux_rock->next != NULL)
        aux_rock = aux_rock->next;

    aux_rock->next = create_rock(x, y, type);
}

// Retorna para qual lado a pedra deve cair ou nao
int falling_by_side(int i, int j) {
    if ((game_tab[i][j + 1].sprite == empty_s) && (game_tab[i + 1][j + 1].sprite == empty_s)) {
        if ((game_tab[i + 1][j].sprite == rock_s) || (game_tab[i + 1][j].sprite == wall_s) || (game_tab[i + 1][j].sprite == diamond_s))
            return RIGHT;
    }
    else if ((game_tab[i][j - 1].sprite == empty_s) && (game_tab[i + 1][j - 1].sprite == empty_s)) {
        if ((game_tab[i + 1][j].sprite == rock_s) || (game_tab[i + 1][j].sprite == wall_s) || (game_tab[i + 1][j].sprite == diamond_s))
            return LEFT;
    }

    // Se nao precisa cair, retorna ESC
    return ESC;
}

// Enche os arredores de diamante
void fill_with_diamonds(int i, int j) {
    if (game_tab[i][j].sprite == empty_s) {
        insert_rock(game_tab[i][j].x, game_tab[i][j].y, diamond_s);
        game_tab[i][j].sprite = diamond_s;
    }
    if (game_tab[i][j + 1].sprite == empty_s) {
        insert_rock(game_tab[i][j + 1].x, game_tab[i][j + 1].y, diamond_s);
        game_tab[i][j + 1].sprite = diamond_s;
    }
    if (game_tab[i][j - 1].sprite == empty_s) {
        insert_rock(game_tab[i][j - 1].x, game_tab[i][j - 1].y, diamond_s);
        game_tab[i][j - 1].sprite = diamond_s;
    }
    if (game_tab[i + 1][j].sprite == empty_s) {
        insert_rock(game_tab[i + 1][j].x, game_tab[i + 1][j].y, diamond_s);
        game_tab[i + 1][j].sprite = diamond_s;
    }
    if (game_tab[i - 1][j].sprite == rock_s) {
        remove_rock(game_tab[i - 1][j].x, game_tab[i - 1][j].y);
        insert_rock(game_tab[i - 1][j].x, game_tab[i - 1][j].y, diamond_s);
        game_tab[i - 1][j].sprite = diamond_s;
    }
    if (game_tab[i + 1][j + 1].sprite == empty_s) {
        insert_rock(game_tab[i + 1][j + 1].x, game_tab[i + 1][j + 1].y, diamond_s);
        game_tab[i + 1][j + 1].sprite = diamond_s;
    }
    if (game_tab[i + 1][j - 1].sprite == empty_s) {
        insert_rock(game_tab[i + 1][j - 1].x, game_tab[i + 1][j - 1].y, diamond_s);
        game_tab[i + 1][j - 1].sprite = diamond_s;
    }
}

// Atualiza a posicao da rocha
void update_rock() {
    ROCK_T *aux_rock = rocks;
    Directions_t direction;

    int i, j;

    while (aux_rock != NULL) {
        j = (aux_rock->x) / (BLOCK_H * SPRITES_SCALE);
        i = (aux_rock->y - BLOCK_W * SPRITES_SCALE) / (BLOCK_W * SPRITES_SCALE);

        direction = falling_by_side(i, j);
        if (game_tab[i + 1][j].sprite == empty_s) {
            aux_rock->falling = true;
        }
        if (game_tab[i + 1][j].sprite == butterfly_s) {
            explode_butterfly(game_tab[i + 1][j].x, game_tab[i + 1][j].y);
        }
        if ((aux_rock->falling) && (aux_rock->type == rock_s) && (game_tab[i + 1][j].sprite == player_s)) {
            miner.alive = false;
            miner.lives--;
            game_tab[i + 1][j].sprite = empty_s;
            return;
        }
        if ((aux_rock->falling) && ((game_tab[i + 1][j].sprite == steelWall_s) || (game_tab[i + 1][j].sprite == wall_s) || (game_tab[i + 1][j].sprite == rock_s) || (game_tab[i + 1][j].sprite == dirt_s) || (game_tab[i + 1][j].sprite == diamond_s) || (game_tab[i + 1][j].sprite == firefly_s))) {
            aux_rock->falling = false;
        }

        if (aux_rock->falling) {
            game_tab[i][j].sprite = empty_s;
            game_tab[i + 1][j].sprite = aux_rock->type;
            aux_rock->y += BLOCK_H * SPRITES_SCALE;
        }
        if (direction == LEFT) {
            game_tab[i][j - 1].sprite = aux_rock->type;
            game_tab[i][j].sprite = empty_s;
            aux_rock->x = aux_rock->x - BLOCK_H * SPRITES_SCALE;
        }
        else if (direction == RIGHT) {
            game_tab[i][j + 1].sprite = aux_rock->type;
            game_tab[i][j].sprite = empty_s;
            aux_rock->x = aux_rock->x + BLOCK_H * SPRITES_SCALE;
        }

        aux_rock = aux_rock->next;
    }
}