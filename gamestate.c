#include "gamelib.h"
#include "gamestate.h"
#include "game_view_lib.h"

// Inicializa as configuracoes do alegro para o jogo
void state_init() {

    init_conf();

    init_display();

    init_font();

    init_audio();

    register_events();
    
    init(al_init_image_addon(), "image");
    init_sprites();
    
    state = SERVING;
    
}

// Inicia os elementos do jogo
void state_serve() {

    int i;
    for (i = 0; i < 7; i++) {
        keys[i] = false;
    }
    rocks = NULL;

    init_tab();
    bool done = false;
    bool redraw = true;

    strcpy(username,"");

    al_start_timer(timer);
    while (1) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
            break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    done = true;
                    state = ENDGAME;
                }
                if(event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    state = PLAYING;
                    done = true;
                }
            break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                state = ENDGAME;
                done = true;
            break;
        }

        if (done)
            break;
        
        get_user(event);
        
        if (redraw && al_is_event_queue_empty(queue)) {
            print_start_game();


            al_flip_display();

            redraw = false;
        }
    }
    if (!strcmp(username,""))
        strcat(username,"Usuário");

}

// Inicia o jogo
void state_play() {
    bool done = false;
    bool redraw = true;
    bool instructions = false;
    int key_pressed;

    while (1) {
        al_wait_for_event(queue, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_KEY_DOWN:
            
                key_pressed = update_keyboard(event.keyboard.keycode, true);
                
                if (key_pressed == ESC)
                    done = true;
                    
                if((event.keyboard.keycode == ALLEGRO_KEY_H) || (event.keyboard.keycode == ALLEGRO_KEY_F1)) {
                    instructions = true;
                }
                if ((instructions) && (event.keyboard.keycode == ALLEGRO_KEY_ENTER))
                    instructions = false;
            break;
            case ALLEGRO_EVENT_KEY_UP:

                update_keyboard(event.keyboard.keycode, false);
            break;
            case ALLEGRO_EVENT_TIMER:
                if (event.timer.source == frameTimer) {

                    update_miner();
                    
                }
                else if (event.timer.source == rockTimer) {
                    update_rock();
                    
                    update_flying();

                    if (!(miner.alive)) {
                        al_play_sample(explosion, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                        if (miner.lives > 0) {
                            reinit_miner();
                        }
                        else 
                            state = OVER;
                    }
                        
                }
                redraw = true;
            break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                state = ENDGAME;
                break;
        }
        
        if (state == OVER) {
            return;
        }
        if (done) {
            state = ENDGAME;
            return;
        }

        if (redraw && al_is_event_queue_empty(queue)) {
            al_set_target_bitmap(buffer);
            al_clear_to_color(al_map_rgb(0, 0, 0));

            if (instructions)
                print_instructions();
            else {
                print_score();
                draw_tab();
            }
            
            al_set_target_backbuffer(disp);
            al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

            al_flip_display();

            redraw = false;
        }
    }
}

// Prepara o fim do jogo, quando o jogador ganha ou perde
void state_over() {

    save_score();

    bool done = false;
    bool redraw = true;

    while (1) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
            break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    done = true;
                    state = ENDGAME;
                }
                if(event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    state = SERVING;
                    free_objects();
                    free(top_5);
                    done = true;
                }
            break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                state = ENDGAME;
                free(top_5);
                done = true;
            break;
        }
        
        if (done) {
            break;
        }
        
        if (redraw && al_is_event_queue_empty(queue)) {
            print_final_score();

            al_flip_display();

            redraw = false;
        }
    }
}

// Destroi os elementos do Allegro e do jogo quando fecha a janela
void state_close() {

    al_destroy_font(font);
    al_destroy_font(font_bar);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_timer(frameTimer);
    al_destroy_timer(rockTimer);
    al_destroy_sample(select_item);
    al_destroy_sample(get_diamonds);
    al_destroy_sample(explosion);
    al_destroy_event_queue(queue);
    free_objects();
    al_destroy_bitmap(heart);
    al_destroy_bitmap(boulderdash_img);
    al_destroy_bitmap(sprites._sheet);
    al_destroy_bitmap(sprites.miner[0]);
    al_destroy_bitmap(sprites.miner[1]);
    al_destroy_bitmap(sprites.miner[2]);
    al_destroy_bitmap(sprites.miner[3]);
    al_destroy_bitmap(sprites.miner[4]);
    al_destroy_bitmap(sprites.miner[5]);
    al_destroy_bitmap(sprites.miner[6]);
    al_destroy_bitmap(sprites.miner[7]);
    al_destroy_bitmap(sprites.miner[8]);
    al_destroy_bitmap(sprites.miner[9]);
    al_destroy_bitmap(sprites.diamond[0]);
    al_destroy_bitmap(sprites.diamond[1]);
    al_destroy_bitmap(sprites.dirt);
    al_destroy_bitmap(sprites.rock);
    al_destroy_bitmap(sprites.wall);
    al_destroy_bitmap(sprites.steelWall);
    al_destroy_bitmap(sprites.firefly[0]);
    al_destroy_bitmap(sprites.firefly[1]);
    al_destroy_bitmap(sprites.butterfly[0]);
    al_destroy_bitmap(sprites.butterfly[1]);
    al_destroy_bitmap(sprites.exit);
    
    
}