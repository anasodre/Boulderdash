# Configura o compilador
CC = gcc

# Gera warnings detalhadas ao compilar
CFLAGS = -Wall -std=c99

LDLIBS = `pkg-config allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_audio-5 allegro_image-5 allegro_acodec-5 --libs --cflags`

# objetos a serem compilados
objs = boulderdash.o gamelib.o gamestate.o game_view_lib.o flying.o rocks.o miner.o

out = game

# Regra principal
all: boulderdash

# Regras de ligacao
boulderdash: $(objs)

# Regras de compilacao
boulderdash.o: boulderdash.c gamelib.h gamestate.h
gamelib.o: gamelib.c gamelib.h gamestate.h miner.h rocks.h flying.h
gamestate.o: gamestate.c gamestate.h gamelib.h game_view_lib.h
game_view_lib.o: game_view_lib.c game_view_lib.h gamelib.h gamestate.h
flying.o: flying.c flying.h gamelib.h
rocks.o: rocks.c rocks.h gamelib.h
miner.o: miner.c miner.h gamelib.h

# Remove arquivos temporarios
clean:
	-rm -f *~ $(objs)

# Remove todos os arquivos do programa sem ser o codigo fonte
purge: clean
	-rm -f boulderdash
