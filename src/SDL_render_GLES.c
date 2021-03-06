#include "SDL_render.h"

#define		ERR_OOPS_GENERIC 	-1
#define		ERR_NONE		0


int videoInitGL(int w, int h) {
	glEnable(GL_TEXTURE_2D);
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	return ERR_NONE;
}


int videoInit() {	
	EGLint configs_avail = 0;
	SDL_SysWMinfo sysinfo;
	EGLint contextParams[] = {EGL_CONTEXT_CLIENT_VERSION, 1, EGL_NONE};
	
	#ifdef RPI
	bcm_host_init();
	#endif
	
	/* here goes SDL init code */
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_WM_SetIcon(SDL_LoadBMP("icon.bmp"), NULL);
	SDL_WM_SetCaption("Frozen Fruits", "Frozen Fruits");
	
	if (!(video.XDisplay = XOpenDisplay(NULL))) {
		fprintf(stderr, "videoInit(): Fatal error: Unable to get a display assets from X\n");
		return ERR_OOPS_GENERIC;
	}
	
	#ifdef RPI
	static EGL_DISPMANX_WINDOW_T nativewindow;
	DISPMANX_ELEMENT_HANDLE_T dispman_element;
	DISPMANX_DISPLAY_HANDLE_T dispman_display;
	DISPMANX_UPDATE_HANDLE_T dispman_update;
	VC_RECT_T dst_rect;
	VC_RECT_T src_rect;
	
	if (!(video.eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY))) {
	#else
	if (!(video.eglDisplay = eglGetDisplay((EGLNativeDisplayType) video.XDisplay))) {
	#endif
		fprintf(stderr, "videoInit(): Fatal error: Unable to get a display assets from EGL\n");
		return ERR_OOPS_GENERIC;
	}
	
	if (!eglInitialize(video.eglDisplay, NULL, NULL)) {
		fprintf(stderr, "videoInit(): Fatal error: Unable to initialize EGL\n");
		return ERR_OOPS_GENERIC;
	}
	#ifdef RPI
	if ((video.screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE)) == NULL) {
	#else
	if ((video.screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE | SDL_FULLSCREEN)) == NULL) {
	#endif
		fprintf(stderr, "videoInit(): Fatal error: Unable to set up a window for SDL\n");
		return ERR_OOPS_GENERIC;
	}
	
	if (eglChooseConfig(video.eglDisplay, egl_config_attrib, &video.eglConfig, 1, &configs_avail) != EGL_TRUE)  {
		fprintf(stderr, "videoInit(): Fatal error: Unable to find a config for EGL (%i)\n", configs_avail);
		return ERR_OOPS_GENERIC;
	}
	
	SDL_VERSION(&sysinfo.version);
	if (SDL_GetWMInfo(&sysinfo) <= 0) {
		fprintf(stderr, "videoInit(): Fatal error: Unable to get window assets\n");
		return ERR_OOPS_GENERIC;
	}
	
	#ifdef RPI
	dst_rect.x = 0;
	dst_rect.y = 0;
	dst_rect.width = 640;
	dst_rect.height = 480;

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.width = 640 << 16;
	src_rect.height = 480 << 16;

	dispman_display = vc_dispmanx_display_open(0 /* LCD */);
	dispman_update = vc_dispmanx_update_start(0);
	 
	dispman_element = vc_dispmanx_element_add(dispman_update, dispman_display, 0/*layer*/, &dst_rect, 0/*src*/, &src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha*/, 0/*clamp*/, (DISPMANX_TRANSFORM_T) 0);
	nativewindow.element = dispman_element;
	nativewindow.width = 640;
	nativewindow.height = 480;
	vc_dispmanx_update_submit_sync(dispman_update);
	
	if ((video.eglSurface = eglCreateWindowSurface(video.eglDisplay, video.eglConfig, &nativewindow, 0)) == EGL_NO_SURFACE) {
	#else
	if ((video.eglSurface = eglCreateWindowSurface(video.eglDisplay, video.eglConfig, (EGLNativeWindowType) sysinfo.info.x11.window, 0)) == EGL_NO_SURFACE) {
	#endif
		fprintf(stderr, "videoInit(): Fatal error: Unable to create a EGL surface\n");
		return ERR_OOPS_GENERIC;
	}
	
	eglBindAPI(EGL_OPENGL_ES_API);
	if ((video.eglContext = eglCreateContext(video.eglDisplay, video.eglConfig, NULL, NULL)) == EGL_NO_CONTEXT) {
		fprintf(stderr, "videoInit(): Fatal error: Unable to create a EGL context\n");
		return ERR_OOPS_GENERIC;
	}
	
	if (eglMakeCurrent(video.eglDisplay, video.eglSurface, video.eglSurface, video.eglContext) == EGL_FALSE) {
		fprintf(stderr, "videoInit(): Fatal error: Unable to make the EGL context current\n");
		return ERR_OOPS_GENERIC;
	}
	
	videoInitGL(640, 480);

	#ifdef PANDORA
		if ((video.fbdev = open("/dev/fb0", O_RDONLY)) < 0)
			fprintf(stderr, "videoInit(): Unable to open framebuffer device for Vsync\n");
	#endif

	input.key = 0;
	
	#ifdef RPI
	SDL_WM_GrabInput(SDL_GRAB_ON);
	#endif
	
	return ERR_NONE;
}



int videoLoop() {	
//	inputPoll(m);
	
		
	
	eglSwapBuffers(video.eglDisplay, video.eglSurface);
}


TEXTURE videoLoadTexture(void *assets, int number) {
	void *texdata;
	unsigned int *data, crap;
	TEXTURE tex;
	unsigned int textest;

	data = (unsigned int *) snsbbfzGetData(assets, number, &crap);
	if (data == NULL) {
		fprintf(stderr, "Unable to get data entry #%i from assets\n", number);
		return tex;
	}
	
	tex.wc = 1.0f/data[0];
	tex.hc = 1.0f/data[1];
	texdata = &data[2];
	
	glGenTextures(1, &tex.tex);
	glBindTexture(GL_TEXTURE_2D, tex.tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data[0], data[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, texdata);
	free(data);
	
	return tex;
}


void videoBlit(TEXTURE tex, RECT *src, int x, int y) {
	float coords[8];
	float texcoords[8];
	
	//x += 80;	
	coords[0] = (SCREEN_GRAN_W) * x - 1.0f;
	coords[1] = 1.0f - (SCREEN_GRAN_H) * y;
	coords[2] = (SCREEN_GRAN_W) * (src->right-src->left+x) - 1.0f;
	coords[3] = 1.0f - (SCREEN_GRAN_H) * y;
	coords[4] = (SCREEN_GRAN_W) * (src->right-src->left+x) - 1.0f;
	coords[5] = 1.0f - (SCREEN_GRAN_H) * (src->bottom-src->top+y);
	coords[6] = (SCREEN_GRAN_W) * x - 1.0f;
	coords[7] = 1.0f - (SCREEN_GRAN_H) * (src->bottom-src->top+y);
	
	texcoords[0] = tex.wc * src->left;
	texcoords[1] = tex.hc * src->top;
	texcoords[2] = tex.wc * src->right;
	texcoords[3] = tex.hc * src->top;
	texcoords[4] = tex.wc * src->right;
	texcoords[5] = tex.hc * src->bottom;
	texcoords[6] = tex.wc * src->left;
	texcoords[7] = tex.hc * src->bottom;
	
	

	glBindTexture(GL_TEXTURE_2D, tex.tex);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, /*(void *)*/ coords);
	glTexCoordPointer(2, GL_FLOAT, 0, /*(void *)*/ texcoords);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	
	
	return;
}


void videoSwapBuffers() {
	#ifdef PANDORA
		int n;
		if (video.fbdev >= 0) {
			n = 0;
			ioctl(video.fbdev, FBIO_WAITFORSYNC, &n);
		}
	#endif

	eglSwapBuffers(video.eglDisplay, video.eglSurface);
	
	glClear(GL_COLOR_BUFFER_BIT);
	return;
}


void videoClearScreen() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	return;
}


void videoDestroy() {
	if (video.eglSurface || video.eglContext || video.eglDisplay) {
		eglMakeCurrent(video.eglDisplay, NULL, NULL, EGL_NO_CONTEXT);
		eglDestroyContext(video.eglDisplay, video.eglContext);
		eglDestroySurface(video.eglDisplay, video.eglSurface);
		eglTerminate(video.eglDisplay);
	}

	return;
}
