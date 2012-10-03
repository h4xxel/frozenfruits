CC = gcc		## We need to compile the tools for the host, not the target
CFLAGS = -O2 -Wall
SNSBBFZSRC = sgputil.c snsbbfz-helper.c

default:
	$(CC) $(CFLAGS) makerawtexture.c -o mkrawtexture -lSDL_image -lSDL
	$(CC) $(CFLAGS) $(SNSBBFZSRC) -o mksnsbbfz -lz

clean:
	rm -Rf mkrawtexture
	rm -Rf mksnsbbfz
