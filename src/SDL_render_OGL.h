#ifndef		__VIDEO_GLES_H__
#define		__VIDEO_GLES_H__


#define COLOURDEPTH_RED_SIZE  		5
#define COLOURDEPTH_GREEN_SIZE 		6
#define COLOURDEPTH_BLUE_SIZE 		5
#define COLOURDEPTH_DEPTH_SIZE		16


#define		SCREEN_GRAN_W		2.0f/640 
#define		SCREEN_GRAN_H		2.0f/480 



#define		KEY_LEFT		0x1
#define		KEY_RIGHT		0x2
#define		KEY_UP			0x4
#define		KEY_DOWN		0x8
#define		KEY_X			0x10
#define		KEY_Y			0x20
#define		KEY_A			0x40
#define		KEY_B			0x80
#define		KEY_START		0x100



#include	<X11/Xutil.h>
#include	<SDL/SDL.h>
#include	<SDL/SDL_opengl.h>
#include	"sgputil.h"

typedef struct {
	float				wc;
	float				hc;
	unsigned int			tex;
} TEXTURE;


typedef struct {
	int				top;
	int				bottom;
	int				left;
	int				right;
} RECT;


typedef struct {
	SDL_Event			event;
	unsigned int			key;
} INPUT;


typedef struct {
	SDL_Surface			*screen;
} VIDEO;

int videoInit();
int videoLoop();


#endif
