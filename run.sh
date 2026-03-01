cc -o ./game ./src/game.c `sdl2-config --cflags --libs` -lm -lSDL2_image 
./game -ex r 