#include "gamelib.h"
#include "flying.h"

// Cria um elemento voador e o inicializa
FLYING_T *create_flying(int x, int y, int type) {
    FLYING_T *aux_flying = (FLYING_T *)malloc(sizeof(FLYING_T));

    if (!aux_flying) {
        perror("Erro: Memória insuficiente");
        exit(1);
    }

    aux_flying->x = x;
    aux_flying->y = y;
    aux_flying->type = type;
    aux_flying->dir = LEFT;
    aux_flying->img = 0;
    aux_flying->next = NULL;

    return aux_flying;
}

// Insere um novo elemento voador
void insert_flying(int x, int y, int type) {
    if (flying == NULL) {
        flying = create_flying(x, y, type);
        return;
    }

    FLYING_T *aux_flying;
    aux_flying = flying;

    while (aux_flying->next != NULL)
        aux_flying = aux_flying->next;

    aux_flying->next = create_flying(x, y, type);
}

// Atualiza o elemento voador e suas posicoes
void update_flying() {
    FLYING_T *aux_flying = flying;

    int i, j;

    // Para isso, ele segue a ordem esquerda, cima, direita, em baixo
    while (aux_flying != NULL) {
        j = (aux_flying->x) / (BLOCK_H * SPRITES_SCALE);
        i = (aux_flying->y - BLOCK_W * SPRITES_SCALE) / (BLOCK_W * SPRITES_SCALE);
        check_sides(i, j);
        switch (aux_flying->dir)
        {
        case (LEFT):

            if (game_tab[i + 1][j].sprite == empty_s) {
                game_tab[i + 1][j].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->dir = DOWN;
                aux_flying->y += BLOCK_H * SPRITES_SCALE;
            }
            else if (game_tab[i][j - 1].sprite == empty_s) {
                game_tab[i][j - 1].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->x -= BLOCK_W * SPRITES_SCALE;
                aux_flying->dir = LEFT;
            }
            else if (game_tab[i - 1][j].sprite == empty_s) {
                game_tab[i - 1][j].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->y -= BLOCK_H * SPRITES_SCALE;
                aux_flying->dir = UP;
            }
            else if (game_tab[i][j + 1].sprite == empty_s) {
                game_tab[i][j + 1].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->x += BLOCK_W * SPRITES_SCALE;
                aux_flying->dir = RIGHT;
            }
            break;
        case (UP):

            if (game_tab[i][j - 1].sprite == empty_s) {
                game_tab[i][j - 1].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->x -= BLOCK_W * SPRITES_SCALE;
                aux_flying->dir = LEFT;
            }
            else if (game_tab[i - 1][j].sprite == empty_s) {
                game_tab[i - 1][j].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->y -= BLOCK_H * SPRITES_SCALE;
                aux_flying->dir = UP;
            }
            else if (game_tab[i][j + 1].sprite == empty_s) {
                game_tab[i][j + 1].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->x += BLOCK_W * SPRITES_SCALE;
                aux_flying->dir = RIGHT;
            }
            else if (game_tab[i + 1][j].sprite == empty_s) {
                game_tab[i + 1][j].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->dir = DOWN;
                aux_flying->y += BLOCK_H * SPRITES_SCALE;
            }
            break;
        case (RIGHT):

            if (game_tab[i - 1][j].sprite == empty_s) {
                game_tab[i - 1][j].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->y -= BLOCK_H * SPRITES_SCALE;
                aux_flying->dir = UP;
            }
            else if (game_tab[i][j + 1].sprite == empty_s) {
                game_tab[i][j + 1].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->x += BLOCK_W * SPRITES_SCALE;
                aux_flying->dir = RIGHT;
            }
            else if (game_tab[i + 1][j].sprite == empty_s) {
                game_tab[i + 1][j].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->dir = DOWN;
                aux_flying->y += BLOCK_H * SPRITES_SCALE;
            }
            else if (game_tab[i][j - 1].sprite == empty_s) {
                game_tab[i][j - 1].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->x -= BLOCK_W * SPRITES_SCALE;
                aux_flying->dir = LEFT;
            }
            break;
        case (DOWN):

            if (game_tab[i][j + 1].sprite == empty_s) {
                game_tab[i][j + 1].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->x += BLOCK_W * SPRITES_SCALE;
                aux_flying->dir = RIGHT;
            }
            else if (game_tab[i + 1][j].sprite == empty_s) {
                game_tab[i + 1][j].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->dir = DOWN;
                aux_flying->y += BLOCK_H * SPRITES_SCALE;
            }
            else if (game_tab[i][j - 1].sprite == empty_s) {
                game_tab[i][j - 1].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->x -= BLOCK_W * SPRITES_SCALE;
                aux_flying->dir = LEFT;
            }
            else if (game_tab[i - 1][j].sprite == empty_s) {
                game_tab[i - 1][j].sprite = aux_flying->type;
                game_tab[i][j].sprite = empty_s;
                aux_flying->y -= BLOCK_H * SPRITES_SCALE;
                aux_flying->dir = UP;
            }
            break;
        }
        aux_flying = aux_flying->next;
    }
}

// Explode a borboleta
void explode_butterfly(int x, int y) {
    FLYING_T *aux_butterfly = flying, *aux_next;
    int i, j;

    // Se uma pedra chocar com a borboleta ela se transforma em varios diamantes
    while (aux_butterfly != NULL) {
        aux_next = aux_butterfly->next;
        if (aux_next != NULL) {
            if ((aux_next->x == x) && (aux_next->y == y)) {
                j = (aux_next->x) / (BLOCK_H * SPRITES_SCALE);
                i = (aux_next->y - BLOCK_W * SPRITES_SCALE) / (BLOCK_W * SPRITES_SCALE);
                game_tab[i][j].sprite = empty_s;
                fill_with_diamonds(i, j);
                aux_butterfly->next = aux_next->next;
                free(aux_next);
                return;
            }
        }
        if ((aux_butterfly->x == x) && (aux_butterfly->y == y)) {
            if (aux_butterfly->next == NULL) {
                j = (aux_butterfly->x) / (BLOCK_H * SPRITES_SCALE);
                i = (aux_butterfly->y - BLOCK_W * SPRITES_SCALE) / (BLOCK_W * SPRITES_SCALE);
                game_tab[i][j].sprite = empty_s;
                fill_with_diamonds(i, j);
                free(aux_butterfly);
                return;
            }
            else {
                j = (aux_butterfly->x) / (BLOCK_H * SPRITES_SCALE);
                i = (aux_butterfly->y - BLOCK_W * SPRITES_SCALE) / (BLOCK_W * SPRITES_SCALE);
                game_tab[i][j].sprite = empty_s;
                fill_with_diamonds(i, j);
                flying = aux_next;
                free(aux_butterfly);
                return;
            }
        }
        aux_butterfly = aux_butterfly->next;
    }
}