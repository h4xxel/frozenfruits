LDFLAGS += -lSDL_mixer -lSDL -lz -L.
SRC = sgputil.c CilloMain_neutral.cpp
TARGET = -o ../bin/frozenfruits
CFLAGS += -I/usr/include/SDL/

default:
	$(CXX) $(CFLAGS) -w -O0 $(TARGET) $(SRC) `sdl-config --cflags` `sdl-config --libs` $(LDFLAGS) -lGL

pandora:
	$(CXX) $(CFLAGS) $(TARGET) $(SRC) $(LDFLAGS) -lGLES_CM -lEGL -lX11

maemo:
	$(CXX) $(CFLAGS) $(TARGET) $(SRC) $(LDFLAGS) -w -DMAEMO -DHAVE_GLES `sdl-config --cflags --libs` -lSDL_gles -lEGL -lGLES_CM -lX11


clean:
	rm -Rf bin
