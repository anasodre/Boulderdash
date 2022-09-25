#ifndef __OBJECTS__
#define __OBJECTS__
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

typedef struct SPRITES_T {
    ALLEGRO_BITMAP *_sheet;

    ALLEGRO_BITMAP *miner[10];
    ALLEGRO_BITMAP *diamond[2];

    ALLEGRO_BITMAP *dirt;
    ALLEGRO_BITMAP *rock;
    ALLEGRO_BITMAP *wall;
    ALLEGRO_BITMAP *steelWall;

    ALLEGRO_BITMAP *firefly[2];
    ALLEGRO_BITMAP *butterfly[2];
    ALLEGRO_BITMAP *exit;

} SPRITES_T;

typedef struct MINER_T {
    int x, y; // coordenadas do miner
    int velocity;
    bool alive;
    int lives;
    int points, num_diamonds;
    int img;
    int power;
} MINER_T;

typedef enum {
    diamond_s,
    dirt_s,
    rock_s,
    wall_s,
    steelWall_s,
    firefly_s,
    butterfly_s,
    exit_s,
    empty_s,
    player_s
} Elements_t;

typedef struct GAME_T {
    Elements_t sprite;
    int x, y;
} GAME_T;

typedef struct ROCK_T {
    int x, y;
    bool falling;
    int type;
    int img;
    struct ROCK_T *next;
} ROCK_T;

typedef struct FLYING_T {
    int x, y;
    int type;
    int dir;
    int img;
    struct FLYING_T *next;
} FLYING_T;

#endif