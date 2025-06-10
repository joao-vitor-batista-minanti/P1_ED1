CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude

EXECUTAVEL = bin/jogo

OBJS = build/main.o build/log.o

all: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJS)
	$(CC) $(OBJS) -o $(EXECUTAVEL)

build/main.o: main.c include/utils/log.h include/game/game1.h include/game/game2.h
	mkdir -p build
	mkdir -p bin
	$(CC) $(CFLAGS) -c main.c -o build/main.o

build/log.o: src/utils/log.c include/utils/log.h
	mkdir -p build
	$(CC) $(CFLAGS) -c src/utils/log.c -o build/log.o

# build/game1.o: src/game/game1.c include/game/game1.h
# 	mkdir -p build
# 	$(CC) $(CFLAGS) -c src/game/game1.c -o build/game1.o

# build/game2.o: src/game/game2.c include/game/game2.h
# 	mkdir -p build
# 	$(CC) $(CFLAGS) -c src/game/game2.c -o build/game2.o

clean:
	rm -f build/*.o $(EXECUTAVEL)
