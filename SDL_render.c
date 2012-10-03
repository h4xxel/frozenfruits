#include <SDL_mixer.h>

#ifdef HAVE_GLES
	#include "SDL_render_GLES.c"
#else
	#include "SDL_render_OGL.c"
#endif

void soundInit() {
	
	/*if(Mix_Init(MIX_INIT_OGG)&MIX_INIT_OGG!=MIX_INIT_OGG) {
		printf("Mix_Init: Failed to init required ogg support!\n");
		printf("Mix_Init: %s\n", Mix_GetError());
		printf("Will run without music\n");
		MUSIC_OK=0;
	}*/
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024)) {
		printf("Mix_OpenAudio: Failed to open audio device!\n");
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		printf("Will run without music\n");
		printf("Will run without sound\n");
		MUSIC_OK=0;
		SOUND_OK=0;
	}
}

void inputPoll() {

	while (SDL_PollEvent(&input.event)) {
		if (input.event.type == SDL_KEYDOWN) {
			switch (input.event.key.keysym.sym) {
				case KEYMAP_UP:
					input.key |= KEY_UP;
					break;
				case KEYMAP_DOWN:
					input.key |= KEY_DOWN;
					break;
				case KEYMAP_LEFT:
					input.key |= KEY_LEFT;
					break;
				case KEYMAP_RIGHT:
					input.key |= KEY_RIGHT;
					break;
				case KEYMAP_Y:
					input.key |= KEY_Y;
					break;
				case KEYMAP_X:
					input.key |= KEY_X;
					break;
				case KEYMAP_A:
					input.key |= KEY_A;
					break;
				case KEYMAP_B:
					input.key |= KEY_B;
					break;
				case KEYMAP_START:
				case KEYMAP_SELECT:
					input.key |= KEY_START;
					break;
				default:
					break;
			}
		} else if (input.event.type == SDL_KEYUP) {
			switch (input.event.key.keysym.sym) {
				case KEYMAP_UP:
					input.key |= KEY_UP;
					input.key ^= KEY_UP;
					break;
				case KEYMAP_DOWN:
					input.key |= KEY_DOWN;
					input.key ^= KEY_DOWN;
					break;
				case KEYMAP_LEFT:
					input.key |= KEY_LEFT;
					input.key ^= KEY_LEFT;
					break;
				case KEYMAP_RIGHT:
					input.key |= KEY_RIGHT;
					input.key ^= KEY_RIGHT;
					break;
				case KEYMAP_Y:
					input.key |= KEY_Y;
					input.key ^= KEY_Y;
					break;
				case KEYMAP_X:
					input.key |= KEY_X;
					input.key ^= KEY_X;
					break;
				case KEYMAP_A:
					input.key |= KEY_A;
					input.key ^= KEY_A;
					break;
				case KEYMAP_B:
					input.key |= KEY_B;
					input.key ^= KEY_B;
					return;
				case KEYMAP_START:
				case KEYMAP_SELECT:
					input.key |= KEY_START;
					input.key ^= KEY_START;
					return;
				default:
					break;
			}
		} else if (input.event.type == SDL_QUIT)
			killGame = true;
	}
	
	return;
}