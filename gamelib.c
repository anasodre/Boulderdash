#include "gamelib.h"

// Aloca os elementos do mapa do jogo
GAME_T **allocate_objects() {
    int i;
    GAME_T **aux_game = (GAME_T **)malloc((GAME_MAX_H) * sizeof(GAME_T *));

    if (!(*aux_game)) {
        perror("Erro: Memória insuficiente");
        exit(1);
    }

    for (i = 0; i < GAME_MAX_H; i++) {
        aux_game[i] = (GAME_T *)malloc((GAME_MAX_W) * sizeof(GAME_T));
    }

    return aux_game;
}

// Testa se conseguiu iniciar as configuracoes do Allegro
void init(bool test, const char *description) {
    if (test)
        return;

    printf("Erro: Não foi possível inicializar %s\n", description);
    exit(1);
}

// Inicializa o Allegro e configuracoes basicas
// como teclado, timer e fila de eventos
void init_conf() {

    // Inicializa o allegro e o teclado
    init(al_init(), "allegro");
    init(al_install_keyboard(), "keyboard");

    // Inicializa o timer
    timer = al_create_timer(1.0 / FPS);
    init(timer, "timer");

    // Inicializa o timer do jogador
    frameTimer = al_create_timer(1.0 / frameFPS);
    init(frameTimer, "frameTimer");

    // Inicializa o timer da rocha
    rockTimer = al_create_timer(1.0 / rockFPS);
    init(rockTimer, "rockTimer");

    // Inicializa a fila de eventos
    queue = al_create_event_queue();
    init(queue, "queue");
}

// Inicializa o display
void init_display() {
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    // Cria uma janela DISP_W x DISP_H
    disp = al_create_display(DISP_W, DISP_H);
    init(disp, "display");

    buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    init(buffer, "bitmap buffer");

    init(al_init_primitives_addon(), "primitives");
}

// Inicializa as fontes do jogo
void init_font() {

    al_init_font_addon();

    init(al_init_ttf_addon(), "allegro_ttf");

    font = al_load_font("./resources/RobotoMono-VariableFont_wght.ttf", 15, 0);

    font_bar = al_create_builtin_font();

    init(font_bar, "font_bar");
    init(font, "font");
}

// Inicializa o audio do jogo
void init_audio() {
    init(al_install_audio(), "audio");
    init(al_init_acodec_addon(), "audio codecs");
    init(al_reserve_samples(16), "reserve samples");

    select_item = al_load_sample("./resources/select.wav");
    init(select_item, "select_item");

    get_diamonds = al_load_sample("./resources/get_diamonds.wav");
    init(get_diamonds, "get_diamonds");

    explosion = al_load_sample("./resources/explosion.wav");
    init(explosion, "explosion");
}

// Permite a reacao aos eventos de teclado e display
void register_events() {
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_timer_event_source(frameTimer));
    al_register_event_source(queue, al_get_timer_event_source(rockTimer));

    al_start_timer(timer);
    al_start_timer(frameTimer);
    al_start_timer(rockTimer);
}

// Seleciona a parte da imagem a ser cortada
ALLEGRO_BITMAP *select_sprite(ALLEGRO_BITMAP *img, int x, int y, int w, int h) {

    ALLEGRO_BITMAP *sprite = al_create_sub_bitmap(img, x, y, w, h);
    init(sprite, "select sprite");
    return sprite;
}

// Guarda as imagens usadas no jogo
void init_sprites() {
    sprites._sheet = al_load_bitmap("./resources/sprites.png");
    init(sprites._sheet, "sprites");

    sprites.miner[0] = select_sprite(sprites._sheet, 0, 1, BLOCK_W, BLOCK_H);    // frente
    sprites.miner[1] = select_sprite(sprites._sheet, 32, 65, BLOCK_W, BLOCK_H);  //frente andando
    sprites.miner[2] = select_sprite(sprites._sheet, 32, 33, BLOCK_W, BLOCK_H);  // tras
    sprites.miner[3] = select_sprite(sprites._sheet, 32, 97, BLOCK_W, BLOCK_H);  // tras andando
    sprites.miner[4] = select_sprite(sprites._sheet, 66, 129, BLOCK_W, BLOCK_H); // esquerda 1
    sprites.miner[5] = select_sprite(sprites._sheet, 97, 129, BLOCK_W, BLOCK_H); // esquerda 2
    sprites.miner[6] = select_sprite(sprites._sheet, 64, 160, BLOCK_W, BLOCK_H); // direita 1
    sprites.miner[7] = select_sprite(sprites._sheet, 97, 160, BLOCK_W, BLOCK_H); // direita 2
    sprites.miner[8] = select_sprite(sprites._sheet, 94, 0, BLOCK_W, BLOCK_H);   // desconfigurado 1
    sprites.miner[9] = select_sprite(sprites._sheet, 64, 0, BLOCK_W, BLOCK_H);   // desconfigurado 2
    sprites.diamond[0] = select_sprite(sprites._sheet, 0, 320, BLOCK_W, BLOCK_H);
    sprites.diamond[1] = select_sprite(sprites._sheet, 64, 320, BLOCK_W, BLOCK_H);

    sprites.dirt = select_sprite(sprites._sheet, 32, 224, BLOCK_W, BLOCK_H);
    sprites.rock = select_sprite(sprites._sheet, 0, 224, BLOCK_W, BLOCK_H);

    sprites.wall = select_sprite(sprites._sheet, 96, 192, BLOCK_W, BLOCK_H);
    sprites.steelWall = select_sprite(sprites._sheet, 32, 192, BLOCK_W, BLOCK_H);

    sprites.firefly[0] = select_sprite(sprites._sheet, 0, 288, BLOCK_W, BLOCK_H);
    sprites.firefly[1] = select_sprite(sprites._sheet, 160, 288, BLOCK_W, BLOCK_H);
    sprites.butterfly[0] = select_sprite(sprites._sheet, 0, 352, BLOCK_W, BLOCK_H);
    sprites.butterfly[1] = select_sprite(sprites._sheet, 95, 352, BLOCK_W, BLOCK_H);
    sprites.exit = select_sprite(sprites._sheet, 64, 192, BLOCK_W, BLOCK_H);

    ALLEGRO_BITMAP *heart_img = al_load_bitmap("./resources/heart.png");
    init(heart_img, "heart");

    heart = select_sprite(heart_img, 2, 4, BLOCK_W, BLOCK_H);

    ALLEGRO_BITMAP *boulderdash_header = al_load_bitmap("./resources/boulder_dash.png");
    init(boulderdash_header, "boulderdash_img");

    boulderdash_img = select_sprite(boulderdash_header, 0, 6, 349, 179);
}

// Atualiza o vetor com as teclas que foram pressionadas
int update_keyboard(int key_code, bool value) {

    int code;
    switch (key_code) {
    case ALLEGRO_KEY_RIGHT:
        keys[RIGHT] = value;
        code = RIGHT;
        break;
    case ALLEGRO_KEY_LEFT:
        keys[LEFT] = value;
        code = LEFT;
        break;
    case ALLEGRO_KEY_UP:
        keys[UP] = value;
        code = UP;
        break;
    case ALLEGRO_KEY_DOWN:
        keys[DOWN] = value;
        code = DOWN;
        break;
    case ALLEGRO_KEY_LCTRL:
        keys[CTRL] = value;
        code = CTRL;
        break;
    case ALLEGRO_KEY_RCTRL:
        keys[CTRL] = value;
        code = CTRL;
        break;
    case ALLEGRO_KEY_ENTER:
        keys[ENTER] = value;
        code = ENTER;
        break;
    case ALLEGRO_KEY_ESCAPE:
        keys[ESC] = value;
        code = ESC;
        break;
    }
    if (!value)
        miner.img = 0;
    return code;
}

// Le um inteiro do arquivo passado como parametro
int read_int(FILE *fp) {
    int num, ret;

    ret = fscanf(fp, "%d", &num);

    // Se encontrar o final do arq, retorna um valor
    // que nao esta no enum definido
    if (ret == EOF)
        return 11;

    if (ret <= 0) {
        fgetc(fp);
    }

    return num;
}

// Inicia o mapa
void init_tab() {

    game_tab = allocate_objects();
    FILE *fp = fopen("./resources/FirstLevel.txt", "r+");

    // Verifica se conseguiu abrir o arquivo
    if (!fp) {
        perror("Erro ao abrir arquivo\n");
        exit(1);
    }

    int i, j;
    int type, num_rocks = 0;

    for (i = 0; i < GAME_MAX_H; i++) {
        for (j = 0; j < GAME_MAX_W; j++) {
            type = read_int(fp);
            if (type == 11)
                return;
            if (type == rock_s)
                num_rocks++;

            game_tab[i][j].sprite = type;
            game_tab[i][j].x = j * BLOCK_W * SPRITES_SCALE;
            game_tab[i][j].y = i * BLOCK_H * SPRITES_SCALE + BLOCK_W * SPRITES_SCALE;

            if (type == player_s)
                init_miner(game_tab[i][j].x, game_tab[i][j].y);
            if (type == rock_s)
                insert_rock(game_tab[i][j].x, game_tab[i][j].y, type);
            if (type == diamond_s)
                insert_rock(game_tab[i][j].x, game_tab[i][j].y, type);
            if (type == firefly_s)
                insert_flying(game_tab[i][j].x, game_tab[i][j].y, type);
            if (type == butterfly_s)
                insert_flying(game_tab[i][j].x, game_tab[i][j].y, type);
        }
    }

    fclose(fp);
}

// Prepara os elementos para serem desenhados na tela
void draw_tab() {
    int i, j;

    for (i = 0; i < GAME_MAX_H; i++) {
        for (j = 0; j < GAME_MAX_W; j++) {
            switch (game_tab[i][j].sprite) {
            case steelWall_s:
                al_draw_scaled_bitmap(sprites.steelWall, 0, 0, BLOCK_W, BLOCK_H, game_tab[i][j].x, game_tab[i][j].y, BLOCK_W * SPRITES_SCALE, BLOCK_H * SPRITES_SCALE, 0);
                break;
            case dirt_s:
                al_draw_scaled_bitmap(sprites.dirt, 0, 0, BLOCK_W, BLOCK_H, game_tab[i][j].x, game_tab[i][j].y, BLOCK_W * SPRITES_SCALE, BLOCK_H * SPRITES_SCALE, 0);
                break;
            case diamond_s:
                al_draw_scaled_bitmap(sprites.diamond[rocks->img], 0, 0, BLOCK_W, BLOCK_H, game_tab[i][j].x, game_tab[i][j].y, BLOCK_W * SPRITES_SCALE, BLOCK_H * SPRITES_SCALE, 0);
                rocks->img = !(rocks->img);
                break;
            case rock_s:
                al_draw_scaled_bitmap(sprites.rock, 0, 0, BLOCK_W, BLOCK_H, game_tab[i][j].x, game_tab[i][j].y, BLOCK_W * SPRITES_SCALE, BLOCK_H * SPRITES_SCALE, 0);
                break;
            case wall_s:
                al_draw_scaled_bitmap(sprites.wall, 0, 0, BLOCK_W, BLOCK_H, game_tab[i][j].x, game_tab[i][j].y, BLOCK_W * SPRITES_SCALE, BLOCK_H * SPRITES_SCALE, 0);
                break;
            case firefly_s:
                al_draw_scaled_bitmap(sprites.firefly[flying->img], 0, 0, BLOCK_W, BLOCK_H, game_tab[i][j].x, game_tab[i][j].y, BLOCK_W * SPRITES_SCALE, BLOCK_H * SPRITES_SCALE, 0);
                flying->img = !(flying->img);
                break;
            case butterfly_s:
                al_draw_scaled_bitmap(sprites.butterfly[flying->img], 0, 0, BLOCK_W, BLOCK_H, game_tab[i][j].x, game_tab[i][j].y, BLOCK_W * SPRITES_SCALE, BLOCK_H * SPRITES_SCALE, 0);
                flying->img = !(flying->img);
                break;
            case exit_s:
                al_draw_scaled_bitmap(sprites.exit, 0, 0, BLOCK_W, BLOCK_H, game_tab[i][j].x, game_tab[i][j].y, BLOCK_W * SPRITES_SCALE, BLOCK_H * SPRITES_SCALE, 0);
                break;
            case player_s:
                al_draw_scaled_bitmap(sprites.miner[miner.img], 0, 0, BLOCK_W, BLOCK_H, game_tab[i][j].x, game_tab[i][j].y, BLOCK_W * SPRITES_SCALE, BLOCK_H * SPRITES_SCALE, 0);
                break;
            case empty_s:
                break;
            }
        }
    }
}

// Libera os elementos alocados
void free_objects() {
    int i;

    // Libera o espaco alocado para a matriz
    for (i = 0; i < GAME_MAX_H; i++) {
        free(game_tab[i]);
    }
    free(game_tab);
    game_tab = NULL;

    // Libera o espaco alocado para as rochas e os diamantes
    ROCK_T *no, *ptr_aux;
    
    no = rocks;
    while (no != NULL) {
        ptr_aux = no;
        no = no->next;

        free(ptr_aux);
        ptr_aux = NULL;
    }
    free(no);
    no = NULL;

    // Libera o espaco alocado para os elementos que voam
    FLYING_T *no_f, *ptr_f;
    no_f = flying;

    while (no_f != NULL) {
        ptr_f = no_f;
        no_f = no_f->next;

        free(ptr_f);
        ptr_f = NULL;
    }
    free(no_f);
    flying = NULL;
}
