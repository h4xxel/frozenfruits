LDFLAGS += -lSDL_mixer -lSDL -lz -L.
SRC = sgputil.c CilloMain_neutral.cpp
TARGET = -o ../bin/frozenfruits

default:
	$(CXX) $(CFLAGS) -w -g -O0 $(TARGET) $(SRC) `sdl-config --cflags` `sdl-config --libs` $(LDFLAGS) -lGL

pandora:
	$(CC) $(CFLAGS) -o bin/frozenfruits $(SRC) $(LDFLAGS) -lGLES_CM -lEGL -X11


clean:
	rm -Rf bin
