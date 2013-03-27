LDFLAGS += -lSDL_mixer -lSDL -lz -L.
SRC = sgputil.c CilloMain_neutral.cpp
TARGET = -o ../bin/frozenfruits
CFLAGS += -I/usr/include/SDL/ -g -O0

default:
	$(CXX) $(CFLAGS) -w -O0 $(TARGET) $(SRC) `sdl-config --cflags` `sdl-config --libs` $(LDFLAGS) -lGL

pandora:
	$(CXX) $(CFLAGS) $(TARGET) $(SRC) $(LDFLAGS) -lGLES_CM -lEGL -lX11

maemo:
	$(CXX) $(CFLAGS) $(TARGET) $(SRC) $(LDFLAGS) -w -O2 -DMAEMO -DHAVE_GLES `sdl-config --cflags --libs` -lSDL_gles -lEGL -lGLES_CM -lX11

rpi:
	$(CXX) $(CFLAGS) $(TARGET) $(SRC) $(LDFLAGS) -w -O2 -DRPI -DHAVE_GLES -lEGL -lGLES_CM -lX11 -DHAVE_LIBOPENMAX=2 -DOMX -DOMX_SKIP64BIT \
		-ftree-vectorize -pipe -DUSE_EXTERNAL_OMX -DHAVE_LIBBCM_HOST -DUSE_EXTERNAL_LIBBCM_HOST -DUSE_VCHIQ_ARM -Wno-psabi \
		-I$(SDKSTAGE)/opt/vc/include/ -I$(SDKSTAGE)/opt/vc/include/interface/vcos/pthreads -I$(SDKSTAGE)/opt/vc/include/interface/vmcs_host/linux \
		`sdl-config --cflags --libs` -L$(SDKSTAGE)/opt/vc/lib -lGLESv2 -lEGL -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lrt
		

clean:
	rm -Rf bin
