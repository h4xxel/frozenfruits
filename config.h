#ifndef CONFIG_H
#define CONFIG_H

#ifdef PANDORA
	//movement
	#define KEYMAP_UP SDLK_UP
	#define KEYMAP_DOWN SDLK_DOWN
	#define KEYMAP_LEFT SDLK_LEFT
	#define KEYMAP_RIGHT SDLK_RIGHT
	//action keys
	#define KEYMAP_X SDLK_PAGEDOWN
	#define KEYMAP_Y SDLK_PAGEUP
	#define KEYMAP_A SDLK_HOME
	#define KEYMAP_B SDLK_END
	//menu keys
	#define KEYMAP_START SDLK_RALT
	#define KEYMAP_SELECT SDLK_LALT
#else
	//movement
	#define KEYMAP_UP SDLK_UP
	#define KEYMAP_DOWN SDLK_DOWN
	#define KEYMAP_LEFT SDLK_LEFT
	#define KEYMAP_RIGHT SDLK_RIGHT
	//action keys
	#define KEYMAP_X SDLK_SPACE
	#define KEYMAP_Y SDLK_DELETE
	#define KEYMAP_A SDLK_RETURN
	#define KEYMAP_B SDLK_F1
	//menu keys
	#define KEYMAP_START SDLK_ESCAPE
	#define KEYMAP_SELECT SDLK_F10
#endif

int MUSIC_OK=1;
int SOUND_OK=1;
int MUSIC_ON=1;
int SOUND_ON=1;

#endif