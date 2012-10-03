

default:
	$(CXX) $(CFLAGS) -w -g -O0 -o frozenfruits CilloMain_neutral.cpp sgputil.c -L. -lz -lGL -lSDL `sdl-config --cflags` `sdl-config --libs` -lSDL_mixer

clean:
	rm -Rf frozenfruits
