


default:
	$(CXX) $(CFLAGS) -g -O0 -o frozenfruits CilloMain_neutral.cpp sgputil.c -L. -lz -lGL -lSDL
