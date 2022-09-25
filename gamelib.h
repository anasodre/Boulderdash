#ifndef __GAMELIB__
#define __GAMELIB__

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "objects.h"
#include "miner.h"
#include "rocks.h"
#include "flying.h"

#define FPS 60.0
#define frameFPS 10.0
#define rockFPS 5.0

#define BUFFER_W 320
#define BUFFER_H 192

#define DISP_SCALE 3
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)

#define SPRITES_SCALE 0.25

#define KEY_SEEN 1
#define KEY_RELEASED 2

#define BLOCK_W 32
#define BLOCK_H 32

#define MINER_MAX_X (BUFFER_W - 2 * BLOCK_W * SPRITES_SCALE)
#define MINER_MAX_Y (BUFFER_H - 3 * BLOCK_H * SPRITES_SCALE)

#define GAME_MAX_W 40
#define GAME_MAX_H 22

#define MAX_NUM_WALL 80

// estados possiveis do jogo Boulder Dash
typedef enum {
    START,   // inicia a tela
    SERVING, // inicia cada elemento
    PLAYING, // jogando
    OVER,    // jogo acaba
    ENDGAME  // finaliza os elementos
} State_t;

typedef enum {
    RIGHT,
    LEFT,
    UP,
    DOWN,
    CTRL,
    ENTER,
    ESC
} Directions_t;

typedef struct USER_T {
    int score, size;
    char *name;
} USER_T;

ALLEGRO_TIMER *timer;
ALLEGRO_TIMER *frameTimer;
ALLEGRO_TIMER *rockTimer;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_DISPLAY *disp;
ALLEGRO_BITMAP *buffer;
ALLEGRO_BITMAP *heart;
ALLEGRO_BITMAP *boulderdash_img;
ALLEGRO_FONT *font;
ALLEGRO_FONT *font_bar;
ALLEGRO_SAMPLE *select_item;
ALLEGRO_SAMPLE *get_diamonds;
ALLEGRO_SAMPLE *explosion;
ALLEGRO_EVENT event;

State_t state;
SPRITES_T sprites;
MINER_T miner;
ROCK_T *rocks;
FLYING_T *flying;
struct GAME_T **game_tab;

bool keys[7];

// Aloca os elementos do mapa do jogo
GAME_T **allocate_objects();

// Testa se conseguiu iniciar as configuracoes do Allegro
void init(bool test, const char *description);

// Inicializa o Allegro e configuracoes basicas
// como teclado, timer e fila de eventos
void init_conf();

// Inicializa o display
void init_display();

// Inicializa a fonte do jogo
void init_font();

// Inicializa o audio do jogo
void init_audio();

// Permite a reacao aos eventos de teclado e display
void register_events();

// Seleciona a parte da imagem a ser cortada
ALLEGRO_BITMAP *select_sprite(ALLEGRO_BITMAP *img, int x, int y, int w, int h);

// Guarda as imagens usadas no jogo
void init_sprites();

// Atualiza o vetor com as teclas que foram pressionadas
int update_keyboard(int key_code, bool value);

// Le um inteiro do arquivo passado como parametro
int read_int(FILE *fp);

// Inicia o mapa
void init_tab();

// Prepara os elementos para serem desenhados na tela
void draw_tab();

// Libera os elementos alocados
void free_objects();

#endif