#include <stdio.h>
#include <stdlib.h>
#include "gamelib.h"
#include "gamestate.h"
 
// programa principal do jogo
int main () {
  state = START;
  for (;;)
    switch (state) {
      case START: 
        state_init();
        break;
      case SERVING: 
        state_serve();
        break;
      case PLAYING:
        state_play();
        break;
      case OVER:
        state_over();
        break;
      case ENDGAME: 
        state_close();
        return 0;
        break;
      default:
        break;
    }
  return 0;
}