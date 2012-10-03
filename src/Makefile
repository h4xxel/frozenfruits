LDFLAGS += -lSDL_mixer -lSDL -lz -L.
SRC = sgputil.c CilloMain_neutral.cpp
TARGET = -o ../bin/frozenfruits
CFLAGS += -I/usr/include/SDL/

default:
	$(CXX) $(CFLAGS) -w -g -O0 $(TARGET) $(SRC) `sdl-config --cflags` `sdl-config --libs` $(LDFLAGS) -lGL

pandora:
	$(CC) $(CFLAGS) $(TARGET) $(SRC) $(LDFLAGS) -lGLES_CM -lEGL -lX11


clean:
	rm -Rf bin
