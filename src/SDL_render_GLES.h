#ifndef		__VIDEO_GLES_H__
#define		__VIDEO_GLES_H__


#define COLOURDEPTH_RED_SIZE  		5
#define COLOURDEPTH_GREEN_SIZE 		6
#define COLOURDEPTH_BLUE_SIZE 		5
#define COLOURDEPTH_DEPTH_SIZE		16


#define		SCREEN_GRAN_W		2.0f/640
#define		SCREEN_GRAN_H		2.0f/480


#include	<X11/Xutil.h>
#include	<GLES/egl.h>
#include	<EGL/egl.h>
#include	<GLES/gl.h>
#include	<SDL/SDL.h>
#include	<SDL/SDL_syswm.h>

#ifdef PANDORA
	#include <fcntl.h>
	#include <sys/ioctl.h>
	#include <stdint.h>
	#define	FBIO_WAITFORSYNC	_IOW('F', 0x20, uint32_t)
#endif


#define		KEY_LEFT		0x1
#define		KEY_RIGHT		0x2
#define		KEY_UP			0x4
#define		KEY_DOWN		0x8
#define		KEY_X			0x10
#define		KEY_Y			0x20
#define		KEY_A			0x40
#define		KEY_B			0x80
#define		KEY_START		0x100


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


static const EGLint egl_config_attrib[] = {
	#ifdef PANDORA
	EGL_RED_SIZE,			COLOURDEPTH_RED_SIZE,
	EGL_GREEN_SIZE,			COLOURDEPTH_GREEN_SIZE,
	EGL_BLUE_SIZE,			COLOURDEPTH_BLUE_SIZE,
	EGL_DEPTH_SIZE,			COLOURDEPTH_DEPTH_SIZE,
	#endif
	EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
	EGL_RENDERABLE_TYPE,		EGL_OPENGL_ES_BIT,
//	EGL_BIND_TO_TEXTURE_RGBA,	EGL_TRUE,
	EGL_NONE
};


typedef struct {
	Display				*XDisplay;
	EGLConfig			eglConfig;
	EGLContext			eglContext;
	EGLSurface			eglSurface;
	EGLDisplay			eglDisplay;
	SDL_Surface			*screen;
	int				fbdev;
} VIDEO;

int videoInit();
int videoLoop();
void videoDestroy();


#endif
