#include "gamelib.h"
#include "game_view_lib.h"
#include "gamestate.h"

// Desenha a barra com as informacoes do jogador
void print_score() {
    al_draw_scaled_bitmap(sprites.diamond[0], 0, 0, BLOCK_W, BLOCK_H, 32, 0, BLOCK_W * SPRITES_SCALE, BLOCK_H * SPRITES_SCALE, 0);
    al_draw_textf(font_bar, al_map_rgb(255,255,255), 45, 0, ALLEGRO_ALIGN_LEFT, "%d", miner.num_diamonds);
    al_draw_textf(font_bar, al_map_rgb(255,255,255), 250, 0, ALLEGRO_ALIGN_LEFT, "%.5d", miner.points);

    int i;
    for (i = 0; i < miner.lives; i++) {
        al_draw_scaled_bitmap(heart, 0, 0, BLOCK_W, BLOCK_H, 140 + i* BLOCK_W * SPRITES_SCALE, 0, BLOCK_W * SPRITES_SCALE, BLOCK_H * SPRITES_SCALE, 0);
    }
 
}

// Desenha a tela com os scores
void print_final_score() {
    int i;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_filled_rectangle(250, 40, 700, 105, al_map_rgb(82,66,157));
    al_draw_textf(font, al_map_rgb(255,255,255), 470, 60, ALLEGRO_ALIGN_CENTER, "CLIQUE NA TECLA ENTER PARA REINICIAR O JOGO");
    al_draw_rectangle(350, 150, 590, 180, al_map_rgb(82,66,157), 0);
    al_draw_textf(font, al_map_rgb(255,255,255), 470, 155, ALLEGRO_ALIGN_CENTER, "TOP 5 SCORES");
    for (i = 0; (i < top_5[0].size) && (i < 5); i++) {
        al_draw_textf(font, al_map_rgb(255,255,255), 450, 200 + i*25, ALLEGRO_ALIGN_CENTER, "%s", top_5[i].name);
        al_draw_textf(font, al_map_rgb(255,255,255), 550, 200 + i*25, ALLEGRO_ALIGN_CENTER, "%d", top_5[i].score);
    }
    
    al_draw_textf(font, al_map_rgb(255,255,255), 470, 400, ALLEGRO_ALIGN_CENTER, "SEU SCORE");
    al_draw_textf(font, al_map_rgb(255,255,255), 470, 420, ALLEGRO_ALIGN_CENTER, "%d", miner.points);

}

// Desenha a tela inicial
void print_start_game() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_filled_rectangle(250, 40, 690, 130, al_map_rgb(82,66,157));
    al_draw_textf(font, al_map_rgb(0,0,0), 470, 60, ALLEGRO_ALIGN_CENTER, "ESCREVA ABAIXO O SEU USER (SEM ESPAÇO) E ");
    al_draw_textf(font, al_map_rgb(0,0,0), 470, 90, ALLEGRO_ALIGN_CENTER, "PRESSIONE ENTER PARA INICIAR O JOGO");
    al_draw_rectangle(300, 150, 640, 190, al_map_rgb(82,66,157), 0);
    al_draw_text(font, al_map_rgb(255,255,255), 470, 160, ALLEGRO_ALIGN_CENTER, username);
    al_draw_textf(font, al_map_rgb(255,247,0), 470, 220, ALLEGRO_ALIGN_CENTER, "Para ler informações sobre como jogar, após iniciar o jogo,");
    al_draw_textf(font, al_map_rgb(255,247,0), 470, 240, ALLEGRO_ALIGN_CENTER, "pressione a tecla h ou F1");
    al_draw_bitmap(boulderdash_img, 300, 300, 0);
}

// Desenha a tela de instrucoes
void print_instructions() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_textf(font, al_map_rgb(255,255,255), 160, 10, ALLEGRO_ALIGN_CENTER, "INSTRUÇÕES");
    al_draw_textf(font_bar, al_map_rgb(255,247,0), 160, 40, ALLEGRO_ALIGN_CENTER, "Boulder Dash é um jogo criado");
    al_draw_textf(font_bar, al_map_rgb(255,247,0), 160, 50, ALLEGRO_ALIGN_CENTER, "por Peter Liepa em 1983.");
    al_draw_textf(font_bar, al_map_rgb(255,247,0), 160, 60, ALLEGRO_ALIGN_CENTER, "É jogado com as setas e ");
    al_draw_textf(font_bar, al_map_rgb(255,247,0), 160, 70, ALLEGRO_ALIGN_CENTER, "e se deve ter cuidado com");
    al_draw_textf(font_bar, al_map_rgb(255,247,0), 160, 80, ALLEGRO_ALIGN_CENTER, "as borboletas e vagalumes.");
    al_draw_textf(font_bar, al_map_rgb(255,247,0), 160, 100, ALLEGRO_ALIGN_CENTER, "Dica: Se uma pedra cair numa");
    al_draw_textf(font_bar, al_map_rgb(255,247,0), 160, 110, ALLEGRO_ALIGN_CENTER, "borboleta ela se transforma");
    al_draw_textf(font_bar, al_map_rgb(255,247,0), 160, 120, ALLEGRO_ALIGN_CENTER, "em diamantes.");
    al_draw_textf(font_bar, al_map_rgb(255,247,0), 160, 140, ALLEGRO_ALIGN_CENTER, "Easter Egg: CTRL + ENTER");
    al_draw_textf(font_bar, al_map_rgb(255,247,0), 160, 150, ALLEGRO_ALIGN_CENTER, "para ter mais uma vida, válido uma vez");
    al_draw_textf(font_bar, al_map_rgb(255,247,0), 160, 170, ALLEGRO_ALIGN_CENTER, "Clique na tecla ENTER para voltar");
}

// Algoritmo de ordenacao, escolhido por se tratar de um vetor pequeno
void insertion_sort(USER_T **top_5, int size){
	
    int user_score, k, n;
    char *user_name;

    // Ordena o vetor
    for(n = 1; n < size; n++){
	    user_score = (*top_5)[n].score;
        user_name = (*top_5)[n].name;
	    k = n-1;

        // Se o item comparado for maior, o desloca para direita
	    while(user_score > (*top_5)[k].score && k >= 0){
	    	(*top_5)[k+1].score = (*top_5)[k].score;
            (*top_5)[k+1].name = (*top_5)[k].name;
	    	k--;
	    }

	    (*top_5)[k+1].score = user_score;
	    (*top_5)[k+1].name = user_name;
    }
}

// Salva o score em um arquivo
void save_score() {
    FILE *fp, *fp_write;

    fp = fopen("./resources/score.txt","r+");
    bool read_file = true;

    if (!fp) {
        read_file = false;
        fp_write = fopen("./resources/score.txt","w");
        if (!fp_write) {
            perror("Erro na escrita do arquivo score.txt");
            exit(1);
        }
    }

    int ret, i = 0, aux_score;
    char aux_user[50];
    
    top_5 = malloc(6*sizeof(USER_T));
    if (!top_5)
        return;

    if (!read_file) {
        top_5[i].size = i+1;
        top_5[i].name = username;
        top_5[i].score = miner.points;
        fprintf(fp_write, "%s %d", username, miner.points);
        fclose(fp_write);
    }
    else  {
        top_5[i].name = username;
        top_5[i].score = miner.points;
        i++;

        ret = fscanf(fp, "%s %d", aux_user, &aux_score);
        
        
        while ((ret != EOF) && (i < 6)) {
            top_5[i].name = strdup(aux_user);
            top_5[i].score = aux_score;
            i++;
            ret = fscanf(fp, "%s %d", aux_user, &aux_score);
        }
        top_5[0].size = i;
        insertion_sort(&top_5, i);

        fclose(fp);
        fp = fopen("./resources/score.txt","w");
        if (!fp) {
            perror("Não foi possível escrever no arquivo score.txt");
            exit(1);
        }

        for (i = 0; (i < top_5[0].size) && (i < 5); i++) {
            fprintf(fp, "%s %d\n", top_5[i].name, top_5[i].score);
        }
        fclose(fp);
    }
}

// Le o nome do usuario
void get_user(ALLEGRO_EVENT event) {
    if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
    if (strlen(username) <= 50) {
        char temp[] = {event.keyboard.unichar, '\0'};
        strcat(username, temp);
    }

    if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(username) != 0)
      if (strlen(username) - 2 >= 0)
        username[strlen(username) - 2] = '\0';
  }
}