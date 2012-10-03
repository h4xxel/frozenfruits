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
	glEnable(GL_TEXTURE_2D);
	
	return ERR_NONE;
}


int videoInit() {	
	
	/* here goes SDL init code */
	SDL_Init(SDL_INIT_EVERYTHING);
	
	if ((video.screen = SDL_SetVideoMode(640, 480, 16, SDL_OPENGL)) == NULL) {
		fprintf(stderr, "videoInit(): Fatal error: Unable to set up a window for SDL\n");
		return ERR_OOPS_GENERIC;
	}
		
	SDL_WM_SetCaption("Frozen fruits", NULL);
	videoInitGL(640, 480);
	
	return ERR_NONE;
}



int videoLoop() {	
//	inputPoll(m);
	
		
	
	SDL_GL_SwapBuffers();
}


TEXTURE videoLoadTexture(const char *fname, int number) {
	void *handle, *texdata;
	unsigned int *data, crap;
	TEXTURE textex;
	unsigned int textest;
	
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &textest);
	fprintf(stderr, "GLError: %i\n", glGetError());
	fprintf(stderr, "Debug: %i\n", textest);
	//FILE *fp;
	
	handle = snsbbfzOpen(fname);
	if (handle == NULL) {
		fprintf(stderr, "Error: Unable to open %s\n", fname);
		return textex;
	}
	
	data = (unsigned int *) snsbbfzGetData(handle, number, &crap);
	snsbbfzClose(handle);
	if (data == NULL) {
		fprintf(stderr, "Unable to get data entry #%i from file %s\n", number, fname);
		return textex;
	}
	
	if (data == NULL)
		fprintf(stderr, "Uh oh, we got a null-pointer!\n");
		
	textex.wc = 1.0f/data[0];
	textex.hc = 1.0f/data[1];
	texdata = &data[2];
	
	fprintf(stderr, "Image size is %i×%i\n", data[0], data[1]);
	
	//if (number == 1) {
	//	fp = fopen("texdebug.bin", "w");
	//	fwrite(texdata, data[0]*data[1]*4, 1, fp);
	//	fclose(fp);
	//}
	
	//glGenTextures(1, &textex.tex);
	textex.tex = textest;
	fprintf(stderr, "Texture: %i\n", textex.tex);
	glBindTexture(GL_TEXTURE_2D, textex.tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data[0], data[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, texdata);
	free(data);
	
	fprintf(stderr, "Texture: %i\n", textex.tex);
	
	return textex;
}


void videoBlit(TEXTURE textex, RECT *src, int x, int y) {
	int i;
	float coords[8];
	float texcoords[8];

	tiles_per_frame++;
		
	coords[0] = (SCREEN_GRAN_W) * x - 1.0f;
	coords[1] = 1.0f - (SCREEN_GRAN_H) * y;
	coords[2] = (SCREEN_GRAN_W) * (src->right-src->left+x) - 1.0f;
	coords[3] = 1.0f - (SCREEN_GRAN_H) * y;
	coords[4] = (SCREEN_GRAN_W) * (src->right-src->left+x) - 1.0f;
	coords[5] = 1.0f - (SCREEN_GRAN_H) * (src->bottom-src->top+y);
	coords[6] = (SCREEN_GRAN_W) * x - 1.0f;
	coords[7] = 1.0f - (SCREEN_GRAN_H) * (src->bottom-src->top+y);
	
	texcoords[0] = textex.wc * src->left;
	texcoords[1] = textex.hc * src->top;
	texcoords[2] = textex.wc * src->right;
	texcoords[3] = textex.hc * src->top;
	texcoords[4] = textex.wc * src->right;
	texcoords[5] = textex.hc * src->bottom;
	texcoords[6] = textex.wc * src->left;
	texcoords[7] = textex.hc * src->bottom;

	
/*	for (i = 0; i < 8; i++)
		fprintf(stderr, "%f, \n", coords[i]);
	fprintf(stderr, "\n");*/
	
	glBindTexture(GL_TEXTURE_2D, textex.tex);
			
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
	SDL_GL_SwapBuffers();
	
	return;
}


void videoClearScreen() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	return;
}

