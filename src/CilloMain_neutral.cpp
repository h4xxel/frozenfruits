//FROZEN FRUITS
//v1.4

///////////////////////////////
// noch zu ändern:
//
// 7. Bomb-Bug : mit 1 bomb 2 tiles weg
// 20. MUSIC_LOADING zu langsam ?

int		tiles_per_frame = 0;
int		FRAMERATE=50;

float	GAMESPEED=15.0;

#define			FALSE			0
#define			TRUE			1

#define			byte			char
#define			BOOL			bool
#define			boolean			bool
#define			FLOAT			float
#define			BYTE			char
#define			VOID			void
#define			DWORD			int

void killGamePl0x();
void saveGames();

const char *music[]={
	"music/techrain.ogg",
	"music/techno4.ogg",
	"music/ansarecieva.ogg",
	"music/techno6.ogg",
	"music/stacid.ogg",
	"music/max.ogg",
	"music/ugot2.ogg",
	"music/chinite2.ogg",
	"music/techno8.ogg",
	"music/dunno.ogg",
	"music/upii.ogg",
};

int music_current=0;

//-----------------------------------------------------------------------------
// File: CilloMain.CPP
//
// Desc: Ein Spielchen
//
// Copyright (c) 1995-1999 Karli Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
//-----------------------------------------------------------------------------
// Include files
//-----------------------------------------------------------------------------
/*#include <windows.h>
#include <ddraw.h>
#include <dinput.h>*/
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "sgputil.h"

#include <SDL_mixer.h>

/*#include "ddutil.h"
#include "resource.h"*/

#include <fstream>
//#include <direct.h>
/*
#include "DSUtil.h"
#include <dsound.h>

#include <dmusicc.h>
#include <dmusici.h>

#include "dmusic_myUtil.h"
#include "color16bit.h"

#include <shellapi.h>
*/

/****
 ** Stuff used by the SDL/OpenGL conversion
 ****/

void *assets;

Mix_Music *mix_music=NULL;

bool	killGame=false;
#include "SDL_render.h"
INPUT	input;
VIDEO	video;
unsigned int frametime;

#include "SDL_render.c"
//-----------------------------------------------------------------------------
// Local definitions
//-----------------------------------------------------------------------------
#define NAME                "Frozen Fruits"
#define TITLE               "Frozen Fruits"

#define	WERBESCREEN			2		//0=keine 1=mit Demo 2=mit Link
#define CD_VERSION			false
#define DISPLAY_800x600		false

//-----------------------------------------------------------------------------
// Default settings
//-----------------------------------------------------------------------------
#define TIMER_ID            1
#define TIMER_RATE          1000

//-----------------------------------------------------------------------------
// Global data
//-----------------------------------------------------------------------------
//HWND	window;

int GEHE_ZU_SITE=0;		//0=keine 1=webpage
/*
LPDIRECTDRAW7               g_pDD = NULL;        // DirectDraw object
LPDIRECTDRAWSURFACE7        frontSurface = NULL;// DirectDraw primary surface

BOOL                        g_bActive = FALSE;   // Is application active?
LPDIRECTDRAWSURFACE7		tileSurface = NULL; // Surface mit Tiles
LPDIRECTDRAWSURFACE7		background = NULL;  // Surface mit Backgroundtiles
//LPDIRECTDRAWSURFACE7        titelbild = NULL;   // Titel1
LPDIRECTDRAWSURFACE7		skullimage = NULL;  // Skull Titelgrafik
LPDIRECTDRAWSURFACE7		splashscreen = NULL; // crystal int.

LPDIRECTDRAWSURFACE7        backSurface = NULL;   // DirectDraw back surface

LPDIRECTDRAWSURFACE7		gameSurface = NULL; // Spielfeld Grafik
LPDIRECTDRAWSURFACE7		gameSurface1 = NULL; // Spielfeld Grafik
LPDIRECTDRAWSURFACE7		gameSurface2 = NULL; // Spielfeld Grafik
LPDIRECTDRAWSURFACE7		gameSurface3 = NULL; // Spielfeld Grafik
LPDIRECTDRAWSURFACE7		gameSurface4 = NULL; // Spielfeld Grafik

*/

TEXTURE				tileSurface;
TEXTURE				background;
TEXTURE				skullimage;
//TEXTURE				titelbild;

/*
// Musikdaten
IDirectMusicSegment *pSegment;
IDirectMusicSegment *track[12];
IDirectMusicSegmentState *pSegState;
IDirectMusicPerformance* pPerf;
IDirectMusicLoader* pLoader;
int actMusic=0;*/

// Sounddaten
//LPDIRECTSOUND dsound                = NULL;
Mix_Chunk *colorswitch	   	    = NULL;
Mix_Chunk *titelmelodie			= NULL;
Mix_Chunk *explosionflyer			= NULL;
Mix_Chunk *explosionbig			= NULL;
Mix_Chunk *explosionfeind			= NULL;
Mix_Chunk *bouncesound			= NULL;
Mix_Chunk *coolmann				= NULL;
Mix_Chunk *coolfrau				= NULL;
Mix_Chunk *tschirp				= NULL;
Mix_Chunk *flushsound				= NULL;
Mix_Chunk *woosh					= NULL;
Mix_Chunk *bleep1					= NULL;
Mix_Chunk *bleep10				= NULL;

/*
// Input
IDirectInput*	            dinpt = NULL;
IDirectInputDevice*			Mouse = NULL;
LPDIRECTINPUTDEVICE			Keyboard = NULL;
DIMOUSESTATE				dims;      // DirectInput mouse state structure

// Menufarben (hintergrund)
HBRUSH bakcol=CreateSolidBrush(RGB(170,150,230));
HBRUSH bakcol2=CreateSolidBrush(RGB(255,255,255));
HBRUSH bakrahmen=CreateSolidBrush(RGB(80,80,130));
*/

// ------------------
// Prozeduren
//void PlayPosSound(SoundObject *sound,float xpos);
void clScreen();


//-----------------------------------------------------------------------------
// Local data
//-----------------------------------------------------------------------------
static char                 szFrontMsg[] = "Front buffer (F12 to quit)";
static char                 szBackMsg[] = "Back buffer (F12 to quit)";

int		BakTil=3;	// background tile
int		BakX=0;		// 99x90 Backgroundtile Offset
int		BakY=0;

int mausrad=0;

int flipzaehler,timezaehler,fps;
int tick,lasttick;

int frmtick,frmlast;
float framespeed;

int collast=0;

class	Spritelist {
public:
	Spritelist();
	int typ;
	int	til;
	bool kill;
	int	sizex;
	int sizey;
	float x;
	float y;
	int offsetx;
	int offsety;
	float a;
	float b;
	float c;
	float d;
	float e;
	float f;
	Spritelist*	next;
	Spritelist* prev;
};


Spritelist::Spritelist() {
	typ=1;til=10;offsetx=0;offsety=0;kill=FALSE;
	sizex=33;sizey=30;x=100;y=100;a=0;b=0;c=0;d=0;e=0;f=0;
}


Spritelist*		sprites;
Spritelist*		menusprites;
Spritelist*		werbesprites;


// Game data
int spielfeld[26][22];
char allelevels[481*39];
int blocks;
int teleportx[5],teleporty[5];
float spielerx,spielery,speedx,speedy,altspeedx,altspeedy;
float rohrx;
float xwerte[3];
float bounce=0;
int spielercol,altcol;
int actlevel=1;
int oldlevel=1;
int returnx=-1;
int returny=-1;
BOOL eis;
BOOL bomb;
int viertel=1; // welcher Bildschirmteil wird angezeigt
int scrx,scry; // "Kamera"position
int startcounter=0;
int Sterne=0; //wieviele Sterne schon gefunden
int actstern=-1;
int sternx[35]={12,13,15,16,18,6,7,8,3,4,5,6,4,5,14,15,17,18,19,20,21,22,3,4,5,6,7,8,14,15,16,17,19,20,21};
int sterny[35]={3,3,3,3,3,8,8,8,16,16,16,16,4,4,5,5,6,5,4,3,2,1,2,2,2,2,2,2,3,3,3,3,3,3,3};
byte sterne[35]={1,0,1,1,0,1,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int maplevels[39]={1,2,3,4,
				   14,15,16,17,18,11,12,13,5,6,7,8, 
				   9,10,19,20,21,22,23,24,25,26,
					27,28,29,30,31,32,33,34,35,36,37,38,39};

int namelevels[39]={0,0,0,0,
					8,5,0,0,12,2,5,			// 5-11
					14,8,15,4,6,0,11,5,1,3,   //12-21  
					13,5,6,2,12,0,		  //22-27
					6,8,2,10,4,6,9,	  //28-34 
					4,15,7,6,15};		  //35-39 

int savegames[35*5];
int actgame=4;


// Menudata
BOOL	restart=FALSE;
bool	splashscr=FALSE;
bool	splashend=FALSE;
bool	Menu=FALSE;	//in-game menu
bool	MenuType=TRUE; //in-game TRUE=normal FALSE=nach tod
bool	MainMenu=TRUE;
bool	Maininit=FALSE;
bool	showinfo=FALSE;
//int		savegame[4]={1,1,1,1};
bool	GamesLoaded=FALSE;
bool	geschafft=FALSE;
bool	hoechsterLevel=FALSE;
byte	spacewait=0;
bool	moveroom=FALSE;
bool	colreset=true;
bool	killed=false;
bool	f12kill=false;
bool	nomenupress=false;

bool	werbunggezeichnet=false;
bool	werbungaus=false;



//--------------------------------------------


void killGamePl0x() {
	/* Stub so far */
	Mix_CloseAudio();
	saveGames();

	#ifdef HAVE_GLES
		videoDestroy();
	#endif
	/*#ifndef MAEMO
	while(Mix_Init(0))
		Mix_Quit();
	#endif*/
	SDL_Quit();
}


// add Sprite
void addSprite(Spritelist* newspr) {
	Spritelist*	sp;
	Spritelist* vor;
	BOOL foundend=FALSE;
	sp=sprites;
	vor=sprites;

	if (sprites==NULL) {
		sprites=newspr;
		newspr->next=NULL;
		newspr->prev=NULL;}
	else
	{
		do {
			if (sp->next==NULL) foundend=TRUE;
			else {vor=sp;sp=sp->next;}
		} while (!foundend);
		sp->next=newspr;
		newspr->next=NULL;
		newspr->prev=sp;
		sp->prev=vor;
	}
}
// delete Sprite
void delSprite(Spritelist* delspr) {
	Spritelist* sp;
	sp=sprites;
	BOOL done=FALSE;
	while (!done) {
		if (delspr==sp) {
			if (sp->prev==NULL) { // 1.List Element
				sprites=sp->next;
				sp->next->prev=NULL; }
			else if (sp->next==NULL) {  // letztes Element
				sp->prev->next=NULL; }
			else {  // allgem. Element
				sp->prev->next=sp->next;
				sp->next->prev=sp->prev;
			}
		done=TRUE;
		}
		sp=sp->next;
		if (sp==NULL) done=TRUE;
	}
}

// Starexplosion
void starExplo(float x,float y) {
	Spritelist*	star;	//links oben
	float angle;
	int i;
	for (i=0;i<=7;i++) {
		star = new(Spritelist);
		star->typ=6;
		star->x=spielerx-10;
		star->y=spielery-8;
		star->til=87;
		star->sizex=33;
		star->sizey=30;
		star->a=i/1.25f; // winkel
		star->b=0; // entfernung vom mittelpunkt
		star->c=star->x;
		star->d=star->y;
		star->e=0; //anim
		star->next=NULL;
		star->prev=NULL;
		addSprite(star);
	}
}

// Spiele WAV-Sounds
void PlayPannedSnd(Mix_Chunk* chunk, float pan ) {
	if (SOUND_OK && SOUND_ON) {
		//DSUtil_PlayPannedSound(pSound,pan);
		Mix_PlayChannel(-1, chunk, 0);
	}
}
void PlayVolFreqSound(Mix_Chunk* chunk, FLOAT fScreenXPos,FLOAT volume,FLOAT freq) {
	if (SOUND_OK && SOUND_ON) {
		//DSUtil_PlayPanVolFreqSound(pSound,fScreenXPos,volume,freq);
		Mix_PlayChannel(-1, chunk, 0);
	}
}
//------------------

void initViertel() {
	viertel=1;
	int spx,spy;
	int tolx=30;
	int toly=20;
	spx=spielerx-33-10;
	spy=spielery-30-10;
	if (spy>240-tolx/2) viertel+=2;	// 1 2
	if (spx>320-toly/2) viertel+=1;	// 3 4
	switch (viertel) {
	case 1:	scrx=0;
			scry=0;
			break;
	case 2:	scrx=160;
			scry=0;
			break;
	case 3:	scrx=0;
			scry=120;
			break;
	case 4:	scrx=160;
			scry=120;
			break;
	}

}

// Savegames für CD Version
void loadGames_CD() {

	std::ifstream InFile;

	char filena[]="C:/WINDOWS/savegame_f1.dat";
	char file[35*5];
	int i;
	for (i=0;i<=(35*5)-1;i++) {
		file[i]=(char)1;
	}
	InFile.open(filena,std::ios::binary);
	InFile.read(file,35*5);
	InFile.close();
	for (i=0;i<=(35*5)-1;i++) {
		savegames[i]=(int)file[i];
		if (savegames[i]>1 || savegames[i]<0) savegames[i]=1;
	}
}
// Savegames laden
void loadGames() {
	if (CD_VERSION) {
		loadGames_CD();
		return;
	}

	FILE *fp;
	char filena[]="savegame.dat";
	char file[35*5];
	char bools[2];
	int i;
	for (i=0;i<=(35*5)-1;i++)
		file[i]=(char)1;
	for (i=0;i<2;i++)
		bools[i] = 1;

	if ((fp = fopen(filena, "rb")) == NULL);
	else {
		fread(file, 35, 5, fp);
		fread((void *) &GAMESPEED, 4, 1, fp);
		fread((void *) bools, 2, 1, fp);
		fclose(fp);
	}
	for (i=0;i<=(35*5)-1;i++) {
		savegames[i]=(int)file[i];
		if (savegames[i]>1 || savegames[i]<0) savegames[i]=1;
	}
	MUSIC_ON = bools[0];
	SOUND_ON = bools[1];
}

// Spielstände speichern, CD version
void saveGames_CD() {
	char filena[]="C:/WINDOWS/savegame_f1.dat";
	//char filena[]="%WINDIR%\savegame_f1.dat";
	std::ofstream OutFile(filena,std::ios::binary);
	char file[35*5];
	int i;
	for (i=0;i<=(35*5)-1;i++) {
		file[i]=(char)savegames[i];
		if (savegames[i]>1 || savegames[i]<0) savegames[i]=1;
	}	
	OutFile.write(file,35*5);
	OutFile.close();
}

// Spielstände speichern
void saveGames() {
	if (CD_VERSION) {
		saveGames_CD();
		return;
	}
	char filena[]="savegame.dat";
	FILE *fp;

	if ((fp = fopen(filena, "wb")) == NULL) {
		fprintf(stderr, "save failed\n");
		return;
	}
	char file[35*5];
	char bools[2];
	int i;
	bools[0] = MUSIC_ON;
	bools[1] = SOUND_ON;

	for (i=0;i<=(35*5)-1;i++) {
		file[i]=(char)savegames[i];
		if (savegames[i]>1 || savegames[i]<0) savegames[i]=1;
	}
	fwrite(file, 35, 5, fp);
	fwrite(&GAMESPEED, 4, 1, fp);
	fwrite(bools, 2, 1, fp);
	fclose(fp);
}

// Zähle Anz.Sterne des Savegames Nr.x
int countStars(int nr) {
	int anz=0;
	nr=nr-1;
	for(int i=0;i<=34;i++) {
		if (savegames[nr*35+i]==0) anz+=1;
	}
	return anz;
}
// game % completed
int percStars(int nr) {
	float proz=(((float)countStars(nr))/35.0f)*100.0f;
	return (int)proz;
}
// spielstand löschen
void clearGame(int nr) {
	for(int i=0;i<=34;i++) {
		savegames[nr*35+i]=1;
	}
	saveGames();
}
// gewählten spielstand übernehmen
void copyGame(int nr) {
	nr=nr-1;
	for(int i=0;i<=34;i++) {
		sterne[i]=savegames[nr*35+i];
	}
}

// lade Levels
void loadLevels() {
/*
	HMODULE hMod=NULL; // Lade Leveldaten aus Ressourcen
    HRSRC   hResInfo;
    HGLOBAL hResData;*/
    void*   pLevels;
	char*	pLVDat;
	int sz;
//    hResInfo = FindResource( hMod, "LEVELS", TEXT("LVL") );
//	if (hResInfo==NULL) showinfo=true;
//	hResData = LoadResource( hMod, hResInfo);
//	pLevels = LockResource( hResData);
	pLVDat = (char *) snsbbfzGetData(assets, 0, (unsigned int *) &sz);
	
	for (int i=1;i<=481*39;i++) {
		allelevels[i-1]=*pLVDat++;
	}

	//letzten Level leichter machen
	allelevels[481*38+9+4*24]=34;
	allelevels[481*38+9+9*24]=34;
	allelevels[481*38+19+9*24]=34;
	allelevels[481*38+15+11*24]=34;
	allelevels[481*38+19+15*24]=34;
	allelevels[481*38+17+15*24]=34;
	allelevels[481*38+17+14*24]=34;
	allelevels[481*38+15+13*24]=34;
	allelevels[481*38+5+15*24]=34;

}

// Tiles setzen  26x22
void initSpielfeld() {
	
	int x,y;
	int t=0;
	int til;
	BOOL enough=FALSE;

	for (t=0;t<=34;t++) {
		sterne[t]=savegames[actgame*35+t];
	}
	
	Sterne=countStars(actgame+1);

	x=1;
	y=1;

	

	int actlevel2=maplevels[actlevel-1];
	char file[481];		//Level laden (aus Speicher)
	int ct=0;
	for (x=1;x<=481;x++) {
		file[x-1]=allelevels[(actlevel2-1)*481+x-1];
	}

	for (y=1;y<=20;y++) {
		for (x=1;x<=24;x++) {
			spielfeld[x][y]=file[ct];
			if (spielfeld[x][y]<0) spielfeld[x][y]+=256;
			ct++;
		}
	}
	BakTil=file[ct++];

	blocks=0;

	
	if (actlevel<5 && returnx ==-1) {
		if (actlevel==1 && oldlevel<=actlevel) spielfeld[11][18]=36;
		else if (actlevel==1 && oldlevel>actlevel) spielfeld[24][18]=36;
		else if (actlevel==2 && oldlevel<=actlevel) spielfeld[2][18]=36;
		else if (actlevel==2 && oldlevel>actlevel) spielfeld[24][13]=36;
		else if (actlevel==3 && oldlevel<=actlevel) spielfeld[2][13]=36;
		else if (actlevel==3 && oldlevel>actlevel) spielfeld[24][18]=36;
		else if (actlevel==4 && oldlevel<=actlevel) spielfeld[2][18]=36;
		else if (actlevel==4 && oldlevel>actlevel) spielfeld[24][18]=36;

	}
	if (returnx !=-1 && actlevel<5) spielfeld[returnx][returny+1]=36;
	

	// Sterne in Röhren?
	if (actlevel<4) {
		int min=0;
		int max=0;
		int i=0;
		if (actlevel==1) {min=0;max=11;}
		if (actlevel==2) {min=12;max=21;}
		if (actlevel==3) {min=22;max=34;}
		for (i=min;i<=max;i++) {
			if (sterne[i]==1) spielfeld[sternx[i]][sterny[i]]=101;
			else spielfeld[sternx[i]][sterny[i]]=102;
		}
	}

	// Level analysieren
	bool spielerda=false;
	for (y=0;y<=21;y++) {	//Spieler suchen
		for (x=0;x<=25;x++) {
			til=spielfeld[x][y];
			if (til>=35 && til<=40) spielerda=true;
		}
	}
	if (!spielerda) {
		for (y=0;y<=21;y++) {
			for (x=0;x<=25;x++) {
				if (spielfeld[x][y]==34) {
					spielfeld[x][y]=35;
					x=100;y=100;
				}
			}	
		}
	}
	for (y=0;y<=21;y++) {
		for (x=0;x<=25;x++) {
			til=spielfeld[x][y];
			if (til>=35 && til<=40) {
				spielerx=x*33-33;
				spielery=y*30-30;
				spielercol=til-35;
				altcol=spielercol;
				sprites=new(Spritelist);
				sprites->typ=0;
				sprites->x=spielerx;
				sprites->y=spielery;
				sprites->til=til;
				sprites->sizex=33;
				sprites->sizey=30;
				sprites->a=0; //todescounter
				sprites->b=0; //teleportcounter
				sprites->c=0; //teleporttile
				sprites->next=NULL;
				sprites->prev=NULL;
				spielfeld[x][y]=34;
			}
		}
	}

	if (actlevel<5 && returnx ==-1) {
		if (actlevel==1 && oldlevel<=actlevel) spielfeld[11][18]=83;
		else if (actlevel==1 && oldlevel>actlevel) spielfeld[24][18]=83;
		else if (actlevel==2 && oldlevel<=actlevel) spielfeld[2][18]=83;
		else if (actlevel==2 && oldlevel>actlevel) spielfeld[24][13]=83;
		else if (actlevel==3 && oldlevel<=actlevel) spielfeld[2][13]=83;
		else if (actlevel==3 && oldlevel>actlevel) spielfeld[24][18]=83;
		else if (actlevel==4 && oldlevel<=actlevel) spielfeld[2][18]=spielfeld[3][18];
		else if (actlevel==4 && oldlevel>actlevel) spielfeld[24][18]=34;
	}
	if (returnx !=-1 && actlevel<5) spielfeld[returnx][returny+1]=83;	

	if (actlevel==2) { spielfeld[4][5]=spielfeld[4][6];spielfeld[5][5]=spielfeld[4][6]; }

	Spritelist* spr;
	for (y=0;y<=21;y++) {
		for (x=0;x<=25;x++) {
			til=spielfeld[x][y];
			if (til>=46 && til<=50) { // Teleporter
				spr=new(Spritelist);
				spr->typ=3;
				spr->x=x*33-33;
				spr->y=y*30-30;
				spr->a=rand()%30;
				spr->til=til;
				spr->sizex=33;
				spr->sizey=30;
				spr->next=NULL;
				spr->prev=NULL;
				addSprite(spr);
			}
			else if (til>=51 && til<=55) {  //Teleporterziele
				teleportx[til-51]=x*33-33+7;teleporty[til-51]=y*30-30+5;
			}
			else if (til==42) { //Zeppelin rechts
					spr = new(Spritelist);
					spr->typ=1;
					spr->x=x*33-33;
					spr->y=y*30-30;
					spr->til=42;
					spr->kill=TRUE;
					spr->sizex=44;
					spr->sizey=30;
					spr->next=NULL;
					spr->prev=NULL;
					addSprite(spr);
					spielfeld[x][y]=34;
			}
			else if (til==44) { //Zeppelin links
					spr = new(Spritelist);
					spr->typ=1;
					spr->kill=TRUE;
					spr->x=x*33-33;
					spr->y=y*30-30;
					spr->til=44;
					spr->sizex=44;
					spr->sizey=30;
					spr->next=NULL;
					spr->prev=NULL;
					addSprite(spr);
					spielfeld[x][y]=34;
			}
			else if (til==58) { //Tortenschädl-Tür
					spr = new(Spritelist);
					spr->typ=4;
					spr->x=x*33-33;
					spr->y=y*30-30;
					spr->til=65;
					spr->kill=TRUE;
					spr->sizex=33;
					spr->sizey=30;
					spr->a=0;
					spr->b=spr->x;
					spr->c=spr->y-30;
					spr->d=3;
					spr->e=spr->x;
					spr->f=spr->y;
					spr->next=NULL;
					spr->prev=NULL;
					addSprite(spr);
					//spielfeld[x][y]=34;
			}
			else if (til>=73 && til <=77) { //Funke
					spr = new(Spritelist);
					spr->typ=5;
					spr->x=x*33-33;
					spr->y=y*30-30;
					spr->kill=TRUE;
					spr->til=73;
					spr->sizex=33;
					spr->sizey=30;
					spr->a=0;
					spr->b=spr->x;
					spr->c=spr->y;
					spr->d=0;		// til=73 -> d=0
					spr->next=NULL;
					spr->prev=NULL;
					
					if (til>73) spr->d=til-73;

					addSprite(spr);
					spielfeld[x][y]=34;
			}
			else if (til>=21 && til<=27) blocks+=1;
		}
	}	

	BakTil=BakTil%16;
	BakY=BakTil/4;
	BakX=BakTil-(BakY*4);
	BakY*=90;
	BakX*=99;

  	speedx=0;
	speedy=1;
	bounce=0;
	eis=FALSE;
	bomb=FALSE;

	flipzaehler=0;
	timezaehler=0;
	fps=0;
	// init sprites
	tick=0;
	lasttick=0;

	initViertel();

	frmtick=SDL_GetTicks();
	frmlast=frmtick;

	xwerte[0]=0;xwerte[1]=0;xwerte[2]=0;

	spacewait=3;

	
}


/////////////////////////
// Tile zeichnen
void blitTile(int x,int y,int tile, int dex, int dey) {
	//achtung fulkod
	RECT tilerect;
	int tilx,tily;
	int wall=-1;
	int BY,BX;
	tily=tile/14;
	tilx=tile-(tily*14);
//	DDSetColorKey(tileSurface,RGB(255,255,0)); //transparenz

	if (tile==13) {tilx=13;tily=0;}
	if (tile>=85 && tile<=100) {wall=tile-85;tile=34;}
	if (tile>=46 && tile<=50) tile=34;

	// Gamesurface 1-4 aussuchen
//	gameSurface=gameSurface1;
	//dex=scrx;dey=scry;
	#if 0
	if (x>=12 && y<10) {/*gameSurface=gameSurface2;*/dex=-396;}
	else if (x<12 && y>=10) {/*gameSurface=gameSurface3;*/dey=-300;}
	else if (x>=12 && y>=10) {/*gameSurface=gameSurface4;*/dex=-396;dey=-300;}
	#endif
	
	if (tile!=34) {  // tile zeichnen
		tilerect.top=tily*30;
		tilerect.bottom=tily*30+30;
		tilerect.left=tilx*33;
		tilerect.right=tilx*33+33;
		videoBlit(tileSurface, &tilerect, x*33-dex, y*30-dey);
/*		gameSurface->BltFast(
		x*33+dex, y*30+dey,  // Upper left xy of destination
		tileSurface,			// Source surface
		&tilerect,				// Source rectangle
		DDBLTFAST_SRCCOLORKEY);*/
	}
	else	// hintergrund zeichnen
	{
		dex*=-1; dey*=-1; //fuck yeah
		if (wall==-1) {
			x=x*33;
			y=y*30;
			tilx=x%99;
			tily=y%90;
			tilerect.top=tily+BakY;
			tilerect.bottom=tily+30+BakY;
			tilerect.left=tilx+BakX;
			tilerect.right=tilx+33+BakX;
			videoBlit(background, &tilerect, x+dex, y+dey);
//			gameSurface->BltFast(x+dex,y+dey,background,&tilerect,DDBLTFAST_WAIT);
		}
		else {
			BY=wall/4;
			BX=wall-(BY*4);
			BY*=90;
			BX*=99;
			x=x*33;
			y=y*30;
			tilx=x%99;
			tily=y%90;
			tilerect.top=tily+BY;
			tilerect.bottom=tily+30+BY;
			tilerect.left=tilx+BX;
			tilerect.right=tilx+33+BX;
			videoBlit(background, &tilerect, x+dex, y+dey);
//			gameSurface->BltFast(x+dex,y+dey,background,&tilerect,DDBLTFAST_WAIT);
		}
	}
}




/////////////////////////
// Tile zeichnen
void blitTile2(int x,int y,int tile) {
	RECT tilerect;
	int tilx,tily;
	tily=tile/14;
	tilx=tile-(tily*14);
//	DDSetColorKey(tileSurface,RGB(255,255,0)); //transparenz

	if (tile==13) {tilx=13;tily=0;}
	if (tile>=46 && tile<=50) tile=34;

	if (tile!=34) {  // tile zeichnen
		tilerect.top=tily*30;
		tilerect.bottom=tily*30+30;
		tilerect.left=tilx*33;
		tilerect.right=tilx*33+33;
		videoBlit(tileSurface, &tilerect, x, y);
/*		backSurface->BltFast(
		x, y,  // Upper left xy of destination
		tileSurface,			// Source surface
		&tilerect,				// Source rectangle
		DDBLTFAST_SRCCOLORKEY);*/
	}
}


// KLOBUS Grafik
void blitKlobus() {
	RECT rect;
	static float x=100.0f;
	static float y=60.0f;
	static float dy=-1.0f;
	static float dx=1.0f;
	static bool updir=true;

	x=x+dx*framespeed*2;
	
	if (updir) dy=-(y-7)/20.0f;
	else dy=(y-7)/20.0f;

	if (x<15.0f) {
		dx=1.0f;
	}
	if (x>320.0f) {
		dx=-1.0f;
	}

	y=y+dy*framespeed*2;
	if (y<10.0f) {dy=1.0f;updir=false;}
	if (y>65.0f && dy>0.0f) {dy=-dy;updir=true;}

//	DDSetColorKey(tileSurface,RGB(255,255,0)); //transparenz
		rect.top=270;
		rect.bottom=323;
		rect.left=0;
		rect.right=296;
		videoBlit(tileSurface, &rect, x, y);
/*		backSurface->BltFast(
		(int)x,(int)y,  // Upper left xy of destination
		tileSurface,			// Source surface
		&rect,				// Source rectangle
		DDBLTFAST_SRCCOLORKEY);*/
}



// highlight selected savegame
void blitSelected(int x,int y,bool color) {
	RECT r;
/*	HRESULT ddrval;
	DDPIXELFORMAT ddpf;*/
	r.top=y;
	r.bottom=y+13;
	r.left=x-5;
	r.right=x+172;

//	DDBLTFX ddbltfx; 
//	ddbltfx.dwSize = sizeof(ddbltfx); 
//	RGB16 rgb16;
//	ddrval=GetRGB16 (backSurface,&rgb16);
//	if (!color) ddbltfx.dwFillColor = GetColor (120,210,120,&rgb16);
//	else ddbltfx.dwFillColor = GetColor (210,110,110,&rgb16);
/*	ddrval = backSurface->Blt( 
		&r,        // Destination
		NULL,        // No source surface
		NULL,        // No source rectangle
		DDBLT_COLORFILL, &ddbltfx); */
}

////////////////////
// zeichne character
void blitChar(char ch,int x,int y) {
	if (ch==' ') return;
	int c=0;
	RECT r;
	r.top=420;
	r.bottom=434;
	if ( (int)ch>=(int)'a' && (int)ch<=(int)'z' ) {
		c=(int)ch-(int)'a';
	}
	if ( (int)ch>=(int)'0' && (int)ch<=(int)'9' ) {
		c=26+(int)ch-(int)'0';
	}
	if (ch=='-') c=36;
	if (ch=='.') c=37;
	if (ch==',') c=38;
	if (ch=='%') c=39;
	if (ch=='(') c=40;
	if (ch==')') c=41;
	if (ch=='M') c=42;
	if (ch=='W') c=43;
	if (ch=='B') c=44;
	if (ch=='C') c=45;
	if (ch=='D') c=46;
	if (ch=='S') c=47;
	if (ch=='T') c=48;
	r.left=c*10;
	r.right=r.left+10;
	if (c>45) {
		r.left=(c-46)*10;
		r.right=r.left+10;
		r.top+=14;
		r.bottom+=14;
	}
	videoBlit(tileSurface, &r, x, y);
/*	backSurface->BltFast(
							x, y,  // Upper left xy of destination
							tileSurface,
							&r,				// Source rectangle
							DDBLTFAST_SRCCOLORKEY);*/
}

// Zeichne einen String
void blitString(char* st,bool first) {
	static int x=10;
	static int y=20;
	if (first) {x=10;y=20;}
	char c=' ';
	int ct=0;
	while ((int)c!=0) {
		c=st[ct++];
		if ((int)c!=0) {
			blitChar(c,x,y);x=x+10;
			if (c=='m') {blitChar('M',x,y);x=x+5;}
			if (c=='w') {blitChar('W',x,y);x=x+5;}
		}
	}
	x=10;
	y=y+20;
}
void blitString(char* st,int px,int py,int mode) {
	char c=' ';
	int ct=0;
	if (mode==1) blitChar('B',px-10,py);
	if (mode==2) blitChar('C',px-10,py);
	if (mode==3) blitChar('D',px-10,py);
	while ((int)c!=0) {
		c=st[ct++];
		if ((int)c!=0) {
			if (mode==1) blitChar('B',px,py);
			if (mode==2) blitChar('C',px,py);
			if (mode==3) blitChar('D',px,py);
			blitChar(c,px,py);px=px+10;
			if (c=='m') {
				if (mode==1) blitChar('B',px,py);
				if (mode==2) blitChar('C',px,py);
				if (mode==3) blitChar('D',px,py);
				blitChar('M',px,py);px=px+5;}
			if (c=='w') {
				if (mode==1) blitChar('B',px,py);
				if (mode==2) blitChar('C',px,py);
				if (mode==3) blitChar('D',px,py);
				blitChar('W',px,py);px=px+5;}
		}
	}
	if (mode==1) blitChar('B',px,py);
	if (mode==2) blitChar('C',px,py);
	if (mode==3) blitChar('D',px,py);
}





// Zeichne Game Instructions
void blitInstructions() {
	blitString("game instructions",TRUE);
	blitString("-----------------",FALSE);
	blitString("",FALSE);
	blitString("smash all fruits",FALSE);
	blitString("",FALSE);
	blitString("dont touch skulls, if you have the same color",FALSE);
	blitString("",FALSE);
	blitString("",FALSE);
	blitString("        never hit a wooden skull",FALSE);
	blitTile2(340,162,14);
	blitString("use color switches to change your color",FALSE);
	blitString("",FALSE);
	blitString("",FALSE);
	blitString("take a bomb to destroy all kind of blocks",FALSE);
	blitTile2(175,70,21);blitTile2(215,70,22);blitTile2(255,70,23);blitTile2(294,70,24);
	blitTile2(335,70,25);blitTile2(375,70,26);
	blitTile2(50,136,15);blitTile2(90,136,16);blitTile2(130,136,17);blitTile2(170,136,18);
	blitTile2(210,136,19);blitTile2(250,136,20);
	blitTile2(200,216,28);blitTile2(240,216,29);blitTile2(280,216,30);blitTile2(320,216,31);
	blitTile2(360,216,32);blitTile2(400,216,33);
	blitTile2(436,260,56);
	#ifdef PANDORA
	blitString("",FALSE);
	blitString("                          game control",FALSE);
	blitString("                          ------------",FALSE);
	blitString("              use the d-pad to move the ball left or right",FALSE);
	blitString("                thrust - (x)    delete savegame - (y)",FALSE);
	blitString("                 back to menu - start",FALSE);
	#elif defined(MAEMO)
	blitString("",FALSE);
	blitString("                          game control",FALSE);
	blitString("                          ------------",FALSE);
	blitString("        use the wasd-keys to move the ball left or right",FALSE);
	blitString("            thrust - space    delete savegame - backspace",FALSE);
	blitString("                 back to menu - m",FALSE);
	#else
	blitString("",FALSE);
	blitString("                          game control",FALSE);
	blitString("                          ------------",FALSE);
	blitString("        use the arrow keys to move the ball left or right",FALSE);
	blitString("            thrust - space    delete savegame - del",FALSE);
	blitString("                 back to menu - escape",FALSE);
	#endif


}

////////////////////
// zeichne eine Zahl
void blitNumber(int za,int x,int y,bool nullstellen,bool klammer,int mod) {
	nullstellen=!nullstellen;
	char c;
	int z=za;
	bool notnull=false;
	if (klammer) {
		if (mod==1) blitChar('B',x,y);
		if (mod==2) blitChar('C',x,y);
		if (mod==3) blitChar('D',x,y);
		blitChar('(',x,y);x=x+8;}
	c=z/100+'0';
	if (c!='0') notnull=TRUE;
	if ( (nullstellen && notnull) || !nullstellen) {
		if (mod==1) blitChar('B',x,y);
		if (mod==2) blitChar('C',x,y);
		if (mod==3) blitChar('D',x,y);
		blitChar(c,x,y);x=x+10;}
	z=za%100;
	c=z/10+'0';
	if (c!='0') notnull=TRUE;
	if ( (nullstellen && notnull) || !nullstellen) {
		if (mod==1) blitChar('B',x,y);
		if (mod==2) blitChar('C',x,y);
		if (mod==3) blitChar('D',x,y);
		blitChar(c,x,y);x=x+10;}
	z=za%10;
	c=z+'0';
	if (mod==1) blitChar('B',x,y);
	if (mod==2) blitChar('C',x,y);
	if (mod==3) blitChar('D',x,y);
	blitChar(c,x,y);
	x=x+10;
	if (klammer) {
		if (mod==1) blitChar('B',x,y);
		if (mod==2) blitChar('C',x,y);
		if (mod==3) blitChar('D',x,y);
		blitChar('%',x,y);x=x+10;
		if (mod==1) blitChar('B',x,y);
		if (mod==2) blitChar('C',x,y);
		if (mod==3) blitChar('D',x,y);
		blitChar(')',x,y);x=x+10;}
	if (mod==1) blitChar('B',x,y);
	if (mod==2) blitChar('C',x,y);
	if (mod==3) blitChar('D',x,y);
}


/////////////////////////
// Titelname zeichnen
void blitMenuText(int x1,int y1,int x2,int y2,int dx,int dy,bool underline) {
	RECT r;

	if (underline) {  //aktives Menüelement
//		HRESULT ddrval;
		r.top=y1-1;
		r.bottom=y2+1;
		r.left=x1-5;
		r.right=x2+5;

		r.top=dy-1;
		r.bottom=r.top+(y2-y1)+2;
		r.left=dx-5;
		r.right=r.left+(x2-x1)+10;

		/*DDBLTFX ddbltfx; 
		ddbltfx.dwSize = sizeof(ddbltfx); 
		RGB16 rgb16;
		ddrval=GetRGB16 (backSurface,&rgb16);
		ddbltfx.dwFillColor = GetColor (220,200,120,&rgb16);
		ddrval = backSurface->Blt( 
		&r,        // Destination
		NULL,        // No source surface
		NULL,        // No source rectangle
		DDBLT_COLORFILL, &ddbltfx);*/
	}

	r.left=x1;
	r.top=y1;
	r.right=x2;
	r.bottom=y2;
//	videoBlit(titelbild, &r, dx, dy);
/*	backSurface->BltFast(
							dx, dy,  // Upper left xy of destination
							titelbild,			// Source surface
							&r,				// Source rectangle
							DDBLTFAST_SRCCOLORKEY);*/
}

void blitName() {
/*
	//DDSetColorKey(titelbild,RGB(255,255,0)); //transparenz
	videoBlit(titelbild, 
	backSurface->BltFast(
							100, 60,  // Upper left xy of destination
							titelbild,			// Source surface
							NULL,				// Source rectangle
							DDBLTFAST_SRCCOLORKEY);*/
}

// zeichne Schädl(titel)
void blitSkull() {
	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = 165;
	r.bottom = 150;
	videoBlit(skullimage, &r, 385, 5*30);
/*	gameSurface2->BltFast(
							0, 5*30,  // Upper left xy of destination
							skullimage,			// Source surface
							NULL,				// Source rectangle
							DDBLTFAST_WAIT);*/
}

//zeichne Titeltext: theres neumann...
void blitScrollString(char* st,int x,int y,float scy) {
	int sy=y+(int)scy;
	if (sy>153 && sy<288) blitString(st,x,sy,0);
}
void blitTitex() {
	static float scrolly=120;
	char author[]="ndsl lngfw";
	
	author[0]='n';
	author[1]='d';
	author[2]='s';
	author[3]='l';
	author[4]=' ';
	author[5]='l';
	author[6]='n';
	author[7]='g';
	author[8]='f';
	author[9]='w';

	author[0]-=3;
	author[1]-=3;
	author[2]-=1;
	author[5]-=4;
	author[6]+=1;
	author[7]-=1;
	author[8]-=1;
	author[9]-=5;
	
	scrolly=scrolly-0.5f*framespeed;
	if (scrolly<-400.0f) scrolly=150.0f;
	blitScrollString("blueskied.com",394,130,scrolly);
	blitScrollString("productions",414,147,scrolly);
	blitScrollString("presents",430,170,scrolly);
	blitScrollString("frozen fruits",398,210,scrolly);
	blitScrollString("written by",415,250,scrolly);
	blitScrollString(author,420,270,scrolly);
	blitScrollString("in 2000-2007",415,290,scrolly);
	blitScrollString("ported by",420,330,scrolly);
	blitScrollString("steven arnow",415,350,scrolly);
	blitScrollString("in 2011",440,370,scrolly);
	blitScrollString("visit",408,440,scrolly);
	blitScrollString("website",408,460,scrolly);
	blitScrollString("for more",408,480,scrolly);
	blitScrollString("free games",408,500,scrolly);

	blitString("v1.4",10,400,0);

}


// blitSpielfeld
void blitSpielfeld() {
	int x,y;
	for (y=1;y<=20;y++) {
		for (x=1;x<=24;x++) {
			blitTile(x-1,y-1,spielfeld[x][y], scrx, scry);			
		}
	}
}

// getTile
int getTile(int x,int y) {
	if (y<0 || x<0) return 0;
	if (x<0) x=0;
	return spielfeld[1+x/33][1+y/30];
}

// MainMenu Hintergrund
void initMainMenu() {
	int x,y;
	int ct=0;
	// Menu Background
	for (y=1;y<=18;y++) {
		for (x=1;x<=24;x++) {
			spielfeld[x][y]=137;
		}
	}
	for (y=6;y<=11;y++) {
		for (x=6;x<=10;x++) {
			spielfeld[x][y]=122;
		}
	}
	for (x=6;x<=10;x++) {
		spielfeld[x][5]=149;
		spielfeld[x][12]=150;
	}
	for (y=6;y<=11;y++) {
		spielfeld[5][y]=138;
		spielfeld[11][y]=139;
	}
	spielfeld[5][5]=151;
	spielfeld[11][5]=152;
	spielfeld[5][12]=153;
	spielfeld[11][12]=195;
	//---------------

	for (x=0;x<=19;x++) { //crystal interactive
		spielfeld[x+1][15]=x+154;
		spielfeld[x+1][16]=x+174;
	}
	spielfeld[0][15]=154;
	spielfeld[0][16]=154;
	blitSpielfeld();
	blitSkull();
	Maininit=TRUE;
}

/////////////////////////////////////////////
// smash a Block
void killColorblock(int x,int y,float pan) {

	if (pan==99.0f) {
		pan=0.0f;
		if (x<spielerx-140) pan=-1.0f;
		else if (x>spielerx+150) pan=1.0f;
	}

	int	rnd=0;
	x=1+x/33;
	y=1+y/30;

	if (spielfeld[x][y]==59) PlayPannedSnd(flushsound,pan);
	else PlayPannedSnd(explosionflyer,pan);

	if (spielfeld[x][y]>=21 && spielfeld[x][y]<=27) {
		blocks-=1;
		if (blocks==0) {sprites->a=100;	// Level geschafft
						rnd=rand()%100;
						geschafft=TRUE;
						starExplo(x*33-33,y*30-30);
						if (rnd>85) PlayPannedSnd(tschirp,0.0f);	
						else if (rnd>42) PlayPannedSnd(coolmann,0.0f);
						else PlayPannedSnd(coolfrau,0.0f);
						if (actstern!=-1) {
							savegames[actgame*35+actstern]=0;
							saveGames();}
						}
	}
	Spritelist*	blok;	//links oben
	blok = new(Spritelist);
	blok->typ=2;
	blok->x=x*33-33;
	blok->y=y*30-30;
	blok->til=spielfeld[x][y];
	blok->sizex=16;
	blok->sizey=15;
	blok->a=-1;
	blok->b=-3;
	blok->next=NULL;
	blok->prev=NULL;
	addSprite(blok);

	blok = new(Spritelist);	//rechts oben
	blok->typ=2;
	blok->x=x*33-18;
	blok->y=y*30-30;
	blok->offsetx=17;
	blok->til=spielfeld[x][y];
	blok->sizex=16;
	blok->sizey=15;
	blok->a=1;
	blok->b=-3;
	blok->next=NULL;
	blok->prev=NULL;
	addSprite(blok); 

	blok = new(Spritelist); //links unten
	blok->typ=2;
	blok->x=x*33-33;
	blok->y=y*30-15;
	blok->offsety=15;
	blok->til=spielfeld[x][y];
	blok->sizex=16;
	blok->sizey=15;
	blok->a=-1;
	blok->b=-2;
	blok->c=0.1;
	blok->next=NULL;
	blok->prev=NULL;
	addSprite(blok); 

	blok = new(Spritelist); //rechts unten
	blok->typ=2;
	blok->x=x*33-18;
	blok->y=y*30-15;
	blok->offsetx=17;
	blok->offsety=15;
	blok->til=spielfeld[x][y];
	blok->sizex=16;
	blok->sizey=15;
	blok->a=1;
	blok->b=-2;
	blok->c=0.1;
	blok->next=NULL;
	blok->prev=NULL;
	addSprite(blok); 

	spielfeld[x][y]=34;
	blitTile(x-1,y-1,34, scrx, scry);
}

// Zerstöre Startür
bool killStarDoor(int lx,int ly,int sterne) {
int x,y;
int muss[7]={3,5,10,18,24,32,35};
	if (Sterne>=muss[sterne-104]) {
		x=1+lx/33;
		y=1+ly/30;
		killColorblock(lx,ly,0.0f);
		killColorblock(lx,ly-30,0.0f);
		killColorblock(lx,ly+30,0.0f);
		spielfeld[x][y]=83;
		blitTile(x-1,y-1,83, scrx, scry);
		spielfeld[x][y-1]=83;
		blitTile(x-1,y-2,83, scrx, scry);
		spielfeld[x][y+1]=83;
		blitTile(x-1,y,83, scrx, scry);
		starExplo(lx,ly);
		return TRUE;
	}
	return FALSE;
}


// prallt Sprite von Tile ab ?
bool reflex(int t) {
	bool abprall=TRUE;
	if (t==34 || t==83 || t==84 || t==58 || (t>=46 && t<=55) || (t>=81 && t<=82)) abprall=FALSE;
	return abprall;
}
// Sprites bewegen
void moveSprites() {
	Spritelist* sp;
	sp=sprites;
	int typ,tmp,tl,ti,te,tt;
	float x,y,oldspeed,oldx,oldy;
	float pan;
	BOOL test;
	do {
		if (sp!=NULL)
		{
			typ=sp->typ;

			switch (typ) {

			case 0:  //Spieler
				sp->x=spielerx;
				sp->y=spielery;
				if (sp->a==0 && sp->b==0) sp->til=spielercol+35;
				break;
			case 1:	//Zeppelin
				if (sp->til==42) {	//rechts
					sp->x+=1*framespeed;
					if (reflex(getTile(sp->x+44,sp->y+15))) sp->til=44;
				}
				else {
					sp->x-=1*framespeed;
					if (reflex(getTile(sp->x,sp->y+15))) sp->til=42;
				}
				break;
			case 2: //smashed block
				if (sp->b < 5) sp->b+=(0.2+sp->c)*framespeed;
				sp->x+=sp->a*framespeed;
				sp->y+=sp->b*framespeed;
				if (sp->x<-15 || sp->x>800 || sp->y>600) delSprite(sp);
				break;
			case 3: //teleporter
				sp->a+=1.0*framespeed;
				if (sp->a>=30) sp->a=0;
				break;
			case 4: //Tortenschädl
				sp->a+=1;
				if (sp->a>=3) { //animation
					sp->a=0;
					sp->til+=1;
					if (sp->til>=72) sp->til=65;
				}

				x=sp->x;y=sp->y;
				test=FALSE;
				
				if (x>=sp->b+33 || x<=sp->b-33 || y>=sp->c+30) {	
						ti=getTile(x-16,y+15);	  //l
						tl=getTile(x+33+16,y+15); //r
						te=getTile(x+16,y+30+15); //u							
						switch ((int)sp->d) {
							case 1: // check rechts
								if (!reflex(te)) sp->d=3;
								else {
									if (reflex(tl)) {sp->d=2;x=sp->b+33;
													if (reflex(ti)) sp->d=5;
													if ((ti>=13 && ti<=27)||(ti==56)) killColorblock(x-16,y+15,99.0f);
													}
									if ((tl>=13 && tl<=27)||(tl==56)) killColorblock(x+48,y+15,99.0f);
								}
								sp->b+=33;
								break;
							case 2: // check links
								if (!reflex(te)) sp->d=4;
								else {
									if (reflex(ti)) {sp->d=1;x=sp->b-33;
										if (reflex(tl)) sp->d=5;
										if ((tl>=13 && tl<=27)||(tl==56)) killColorblock(x+48,y+15,99.0f);}
									if ((ti>=13 && ti<=27)||(ti==56)) killColorblock(x-16,y+15,99.0f);
								}
								sp->b-=33;
								break;
							case 3: // check fall
							case 4:
								if (reflex(te)) {sp->d-=2;y=sp->c+30;
									if (sp->d==1) sp->b-=33;
									else sp->b+=33;
								}
								
								if (y>=539 && reflex(te)) {
									tmp=spielfeld[1+((int)x+16)/33][1+((int)y+15)/30];
									spielfeld[1+((int)x+16)/33][1+((int)y+15)/30]=sp->til;
									killColorblock((int)x+16,(int)y+15,99.0f);
									spielfeld[1+((int)x+16)/33][1+((int)y+15)/30]=tmp;
									x=sp->e;
									y=sp->f;
									sp->a=0;
									sp->d=3;
									sp->b=x;
									sp->c=y-60;
									sp->til=65;
								}
								
								sp->c+=30;
								break;
							}
				}
     				switch ((int)sp->d) {	// bewege Totenkopf
						case 1:	//rechts
							x+=framespeed*2.0f;
							break;
						case 2: //links
							x-=framespeed*2.0f;
							break;
						case 3: //unten
						case 4:
							y+=framespeed*2.0f;
							break;
						case 5:  // Skull zw. 2 Blöcken
							ti=getTile(x-16,y+15);	  //l
							tl=getTile(x+33+16,y+15); //r
							te=getTile(x+16,y+30+15); //u
							if (!reflex(te)) sp->d=3;
							else {
								if (reflex(tl)) {
									if ((tl>=13 && tl<=27)||(tl==56)) killColorblock(x+48,y+15,99.0f);
									if (reflex(ti)) {
										if ((ti>=13 && ti<=27)||(ti==56)) killColorblock(x-16,y+15,99.0f);	
									}
									else sp->d=2;
								}
								else sp->d=1;
							}
							break;
					}
				
				sp->x=x;sp->y=y;
				break;
				
			case 5:  //Funke
				sp->a+=1;
				if (sp->a>=10) { // animation
					sp->a=0;
					sp->til+=1;
					if (sp->til>=80) sp->til=73;
				}
	
				test=FALSE;
				x=sp->x;y=sp->y;
				
				  switch ((int)sp->d) {
							case 1:	//rechts
								x+=framespeed;
								break;
							case 2: //unten
								y+=framespeed;
								break;
							case 3: //links
								x-=framespeed;
								break;
							case 4: //oben
								y-=framespeed;
								break;
					}
						// checken ob Wand im Weg
				  if (sp->d!=0) {
						if (x>=sp->b+33 || x<=sp->b-33 || y>=sp->c+30 || y<=sp->c-30) {

							ti=getTile(x-16,y+15);	  //l
							tl=getTile(x+33+16,y+15); //r
							te=getTile(x+16,y+30+15); //u
							tmp=getTile(x+16,y-15);	  //o

							switch ((int)sp->d) {
								case 1:
									tt=getTile(x-16,y-15);
									if (!reflex(tl) && reflex(tmp)) {sp->d=1;sp->b+=33;x=sp->b;}
									else if (!reflex(tmp) && !reflex(tt) && !reflex(tl)) {sp->d=1;sp->b+=33;x=sp->b;}
									else if (!reflex(tmp) && reflex(tt)) {sp->d=4;sp->b+=33;x=sp->b;}
									else if (reflex(tl) && !reflex(te)) {sp->d=2;sp->b+=33;x=sp->b;}
									else if (reflex(tl) && reflex(tmp) && !reflex(te)) {sp->d=2;sp->b+=33;x=sp->b;}
									else if (reflex(tl) && reflex(tmp) && reflex(te) && !reflex(ti)) {sp->d=3;sp->b+=33;x=sp->b;}
									else {sp->d=0;sp->b+=33;x=sp->b;}
									break;
								case 2:
									tt=getTile(x+33+16,y-15);
									if (!reflex(te) && reflex(tl)) {sp->d=2;sp->c+=30;y=sp->c;}
									else if (!reflex(tl) && !reflex(tt) && !reflex(te)) {sp->d=2;sp->c+=30;y=sp->c;}
									else if (!reflex(tl) && reflex(tt)) {sp->d=1;sp->c+=30;y=sp->c;}
									else if (reflex(te) && !reflex(ti)) {sp->d=3;sp->c+=30;y=sp->c;}
									else if (reflex(te) && reflex(tl) && !reflex(ti)) {sp->d=3;sp->c+=30;y=sp->c;}
									else if (reflex(ti) && reflex(tl) && reflex(te) && !reflex(tmp)) {sp->d=4;sp->c+=30;y=sp->c;}
									else {sp->d=0;sp->c+=30;y=sp->c;}
									break;
								case 3:
									tt=getTile(x+33+16,y+30+15);
									if (!reflex(ti) && reflex(te)) {sp->d=3;sp->b-=33;x=sp->b;}
									else if (!reflex(te) && !reflex(tt) && !reflex(ti)) {sp->d=3;sp->b-=33;x=sp->b;}
									else if (!reflex(te) && reflex(tt)) {sp->d=2;sp->b-=33;x=sp->b;}
									else if (reflex(ti) && !reflex(tmp)) {sp->d=4;sp->b-=33;x=sp->b;}
									else if (reflex(ti) && reflex(te) && !reflex(tmp)) {sp->d=4;sp->b-=33;x=sp->b;}
									else if (reflex(ti) && reflex(te) && reflex(tmp) && !reflex(tl)) {sp->d=1;sp->b-=33;x=sp->b;}
									else {sp->d=0;sp->b-=33;x=sp->b;}
									break;
								case 4:
									tt=getTile(x-16,y+30+15);
									if (!reflex(tmp) && reflex(ti)) {sp->d=4;sp->c-=30;y=sp->c;}
									else if (!reflex(ti) && !reflex(tt) && !reflex(tmp)) {sp->d=4;sp->c-=30;y=sp->c;}
									else if (!reflex(ti) && reflex(tt)) {sp->d=3;sp->c-=30;y=sp->c;}
									else if (reflex(tmp) && !reflex(tl)) {sp->d=1;sp->c-=30;y=sp->c;}
									else if (reflex(ti) && reflex(tmp) && !reflex(tl)) {sp->d=1;sp->c-=30;y=sp->c;}
									else if (reflex(ti) && reflex(tl) && reflex(tmp) && !reflex(te)) {sp->d=2;sp->c-=30;y=sp->c;}
									else {sp->d=0;sp->c-=30;y=sp->c;}
									break;


							}
							// test ob neben wasser = tod
							test=FALSE;
							if (tl==59) {killColorblock(x+48,y+15,99.0f);test=TRUE;}
							if (ti==59) {killColorblock(x-16,y+15,99.0f);test=TRUE;}
							if (te==59) {killColorblock(x+16,y+45,99.0f);test=TRUE;}
							if (tmp==59) {killColorblock(x+16,y-15,99.0f);test=TRUE;}
							
						}
	
					
					sp->x=x;
					sp->y=y;

					// Funke tot?
					if (test) {
						tmp=spielfeld[1+((int)x+16)/33][1+((int)y+15)/30];
						spielfeld[1+((int)x+16)/33][1+((int)y+15)/30]=sp->til;
						killColorblock((int)x+16,(int)y+15,99.0f);
						spielfeld[1+((int)x+16)/33][1+((int)y+15)/30]=tmp;
						delSprite(sp);
						pan=0.0f;
						if (x<spielerx-140) pan=-1.0f;
						else if (x>spielerx+150) pan=1.0f;
						PlayPannedSnd(explosionfeind,pan);
					}

					break;
				  }
				  else
						{
					  		ti=getTile(x-16,y+15);	  //l
							tl=getTile(x+33+16,y+15); //r
							te=getTile(x+16,y+30+15); //u
							tmp=getTile(x+16,y-15);	  //o
							sp->b=x;sp->c=y;
							if (!reflex(tl)) sp->d=1;
							else if (!reflex(te)) sp->d=2;
							else if (!reflex(ti)) sp->d=3;
							else if (!reflex(tmp)) sp->d=4;
							break;
						}
			case 6:  //Starexplosion
				sp->x=sp->c-sinf(sp->a)*sp->b;
				sp->y=sp->d+cosf(sp->a)*sp->b;
				sp->a+=framespeed/25.0f; //100
				sp->b+=framespeed/1.0f;
				sp->e+=framespeed/5.0f;
				if (int(sp->e)>7) sp->e-=8.0f;
				sp->til=87+(int)sp->e;
				if (sp->b>150) delSprite(sp);
				break;
			}
		}
		sp=sp->next;
	} while (sp!=NULL);
}
// Sprites zeichnen
void blitSprites(int scrollx,int scrolly,Spritelist *spriteptr) {

	if (Menu) return;
	int tile;
	RECT r;

//	DDSetColorKey(tileSurface,RGB(255,255,0)); //transparenz

	int tilx,tily;
	int cutx,cuty,tely;
	int sx,sy,hx,hy;
	while (spriteptr!=NULL) {
		tile=spriteptr->til;
		tily=tile/14;
		tilx=tile-(tily*14);
		if (tile==13) {tilx=13;tily=0;}
		r.top=tily*30+spriteptr->offsety;
		r.bottom=r.top+spriteptr->sizey;
		r.left=tilx*33+spriteptr->offsetx;
		r.right=r.left+spriteptr->sizex;
		
		cutx=0;
		cuty=0;

		tely=0;
		if (tile>=46 && tile<=50) tely=spriteptr->a;


		sx=spriteptr->x-scrollx;
		sy=spriteptr->y-scrolly;
		hx=spriteptr->sizex;
		hy=spriteptr->sizey;

		// am bildschirmrand cutten
		if (sy+hy>480) //unten
			r.bottom-=(sy+hy)-480;
		if (sy<0) {	//oben
			cuty=-sy;
			r.top+=cuty; }
		if (sx+hx>632)  //rechts
			r.right-=(sx+hx)-632;
		if (sx<0) { //links
			cutx=-sx;
			r.left+=cutx; }


		r.top+=tely;
		r.bottom+=tely;
		
		videoBlit(tileSurface, &r, spriteptr->x+cutx-scrollx, spriteptr->y+cuty-scrolly);
/*		backSurface->BltFast(
		spriteptr->x+cutx-scrollx,spriteptr->y+cuty-scrolly,  // Upper left xy of destination
		tileSurface,			// Source surface
		&r,				// Source rectangle
		DDBLTFAST_SRCCOLORKEY);
*/
		spriteptr=spriteptr->next;
	}
}

// Spielerexplosion
void exploBall(int teleport) {
int x,y;
int e=0;

Spritelist* blok;
	for (x=1;x<=3;x++) {
		for (y=1;y<=3;y++) {
			blok = new(Spritelist);
			blok->typ=2;
			blok->x=sprites->x+x*5;
			blok->y=sprites->y+y*5;;
			blok->til=sprites->til; //normale Explosion
			if (teleport>=0) {
				switch (teleport) {
				case 0: e=3;break;
				case 1: e=1;break;
				case 2: e=4;break;
				case 3: e=5;break;
				case 4: e=0;break;
				}
				blok->til=e+35; //TeleportExplosion
			}
			blok->sizex=5;
			blok->sizey=5;
			blok->a=-2+x;
			blok->b=-5+y;
			blok->c=y/20;
			blok->offsetx=-3+x*5;
			blok->offsety=-3+y*5;
			blok->next=NULL;
			blok->prev=NULL;
			addSprite(blok);
			}
		}

}

// Wohin fliegt Ball ?
void checkCollision() {
	int up,down,links,rechts,mitte;
	int lx,ly,rx,ry;
	bool bombed;
	bool soundflag;
	float soundpan;
	int soundfreq;

	bombed=bomb;
	up=getTile(spielerx+10,spielery+2);
	down=getTile(spielerx+9,spielery+17);
	lx=spielerx+2;ly=spielery+9;
	links=getTile(lx,ly);
	rx=spielerx+17;ry=spielery+10;
	rechts=getTile(rx,ry);
	mitte=getTile(spielerx+10,spielery+9);
	
	soundflag=FALSE;
	if (!reflex(links)) {lx=spielerx+4;ly=spielery+8;links=getTile(lx,ly);} //y+5
	if (!reflex(links)) {lx=spielerx+4;ly=spielery+11;links=getTile(lx,ly);} //y+14
	if (reflex(links)) {
		if (bounce==0 || speedx<0) soundflag=TRUE;
		bounce=1;
		soundpan=-1.0f;
		soundfreq=links;
		speedx=1;
		eis=FALSE;bomb=FALSE;if (links<13||links>=83) bomb=bombed;
		spielercol=altcol;
	}
	if (!reflex(rechts)) {rx=spielerx+15;ry=spielery+8;rechts=getTile(rx,ry);} //y+5
	if (!reflex(rechts)) {rx=spielerx+15;ry=spielery+11;rechts=getTile(rx,ry);} //y+14
	if (reflex(rechts)) {
		if (bounce==0 || speedx>0) soundflag=TRUE;
		bounce=1;
		soundpan=1.0f;
		soundfreq=rechts;
		speedx=-1;
		eis=FALSE;bomb=FALSE;if (rechts<13||rechts>=83) bomb=bombed;
		spielercol=altcol;
	}
	if (reflex(down)) {if (speedy>0) soundflag=TRUE;
					   speedy=-1;eis=FALSE;bomb=FALSE;spielercol=altcol;
					   soundpan=0.0f;
					   soundfreq=down;
					   if (down<13||down>=83) bomb=bombed;}

	if (reflex(up)) {if (speedy<0) soundflag=TRUE;
					 speedy=1;eis=FALSE;bomb=FALSE;spielercol=altcol;
					 soundpan=0.0f;
					 soundfreq=up;
					 if (up<13||up>=83) bomb=bombed;}

	// Richtungspfeile
	if (up==81 || down==81 || rechts==81 || links==81) {
		if (speedy>-1) speedy=-1;
	}
	if (up==82 || down==82 || rechts==82 || links==82) {
		if (speedy<1) speedy=1;
	}
	if (soundflag) PlayVolFreqSound(bouncesound,soundpan,-1000,(soundfreq%50)*400);
	
	soundflag=FALSE;
	// Colorchange testen (tiles# 28-33)
	if (links>=28 && links<=33) {
		if (!bombed) {spielercol=links-28;altcol=spielercol;soundflag=TRUE;soundpan=-1.0f;}
		else {bomb=FALSE;killColorblock(lx,ly,-1.0f);bombed=FALSE;}
	}
	if (rechts>=28 && rechts<=33) {
		if (!bombed) {spielercol=rechts-28;altcol=spielercol;soundflag=TRUE;soundpan=1.0f;}
		else {bomb=FALSE;killColorblock(rx,ry,1.0f);bombed=FALSE;}
	}
	if (up>=28 && up<=33) {
		if (!bombed) {spielercol=up-28;altcol=spielercol;soundflag=TRUE;}
		else {bomb=FALSE;killColorblock(spielerx+10,spielery+2,0.0f);bombed=FALSE;soundpan=0.0f;}
	}
	if (down>=28 && down<=33) {
		if (!bombed) {spielercol=down-28;altcol=spielercol;soundflag=TRUE;}
		else {bomb=FALSE;killColorblock(spielerx+9,spielery+17,0.0f);bombed=FALSE;soundpan=0.0f;}
	}
	if (soundflag) PlayVolFreqSound(colorswitch,soundpan,-1500,0); 

	// Colorblocks + Graublock (# 21-27 + 13)
	if ((up>=21 && up<=27)||up==13) {
		if (spielercol==up-21 || up==27 || bombed) {killColorblock(spielerx+10,spielery+2,0.0f);bombed=FALSE;}
	}
	if ((down>=21 && down<=27)||down==13) {
		if (spielercol==down-21 || down==27 || bombed) {killColorblock(spielerx+9,spielery+17,0.0f);bombed=FALSE;}
	}
	if ((rechts>=21 && rechts<=27)||rechts==13) {
		if (spielercol==rechts-21 || rechts==27 || bombed) {killColorblock(rx,ry,1.0f);bombed=FALSE;}
	}
	if ((links>=21 && links<=27)||links==13) {
		if (spielercol==links-21 || links==27 || bombed) {killColorblock(lx,ly,-1.0f);bombed=FALSE;}
	}

	soundflag=FALSE;
	soundpan=0.0f;
	//Totenkopf
	if (up>=14 && up<=20) {
		if (bombed || up==14 || up==spielercol+15) {
			killColorblock(spielerx+10,spielery+2,0.0f);
			bombed=FALSE;
			exploBall(-1);
			sprites->a=1;
			soundflag=TRUE;
		}
	}
	if (down>=14 && down<=20) {
		if (bombed || down==14 || down==spielercol+15) {
			killColorblock(spielerx+9,spielery+17,0.0f);
			exploBall(-1);
			sprites->a=1;
			bombed=FALSE;
			soundflag=TRUE;
		}
	}
	if (rechts>=14 && rechts<=20) {
		if (bombed || rechts==14 || rechts==spielercol+15) {
			killColorblock(rx,ry,1.0f);
			exploBall(-1);
			sprites->a=1;
			bombed=FALSE;
			soundflag=TRUE;
		}
	}
	if (links>=14 && links<=20) {
		if (bombed || links==14 || links==spielercol+15) {
			killColorblock(lx,ly,-1.0f);
			exploBall(-1);
			sprites->a=1;
			bombed=FALSE;
			soundflag=TRUE;
		}
	}
	if (soundflag) PlayPannedSnd(explosionbig,soundpan);

	
	
		// Eisblock
	if (up==57 || down==57 || links==57 || rechts==57) {
		eis=TRUE;
		altcol=spielercol;
		spielercol=6;
		bounce=99;
	}
	else {  // Bombe

		if (up==56) {killColorblock(spielerx+10,spielery+2,0.0f);bomb=TRUE;altcol=spielercol;}
		if (down==56) {killColorblock(spielerx+9,spielery+17,0.0f);bomb=TRUE;altcol=spielercol;}
		if (rechts==56) {killColorblock(rx,ry,1.0f);bomb=TRUE;altcol=spielercol;}
		if (links==56) {killColorblock(lx,ly,-1.0f);bomb=TRUE;altcol=spielercol;}		
	}

	// Teleporter
	if (mitte>=46 && mitte<=50) {
		exploBall(mitte-46);
		sprites->c=mitte-46;
		spielerx=teleportx[mitte-46];spielery=teleporty[mitte-46];
		sprites->b=1;
		PlayPannedSnd(woosh,0.0f);
	}

	// Sterntür
	soundflag=FALSE;
	if (links>=104 && links<=110) soundflag=killStarDoor(lx,ly,links);
	if (rechts>=104 && rechts<=110) soundflag=killStarDoor(rx,ry,rechts);


	// Level Röhre
	if (up==101 || up==102) {
		sprites->a=2000;
		rohrx=(int)((spielerx+10)/33)*33+8;
	}

}



// Kollision mit Feind ?
void nmeCollision() {
	Spritelist* s;
	int x,y,ex,ey,tmp;
	bool hit=FALSE;
	s=sprites->next;
	x=sprites->x+10;
	y=sprites->y+9;
	while (s!=NULL) {
		if (s->kill==TRUE) {
			ex=s->x;
			ey=s->y;
			if (x>=ex && x<=ex+s->sizex && y>=ey && y<=ey+s->sizey) {
				sprites->a=1;
				hit=TRUE;
			}
		}
		s=s->next;
	}
	if (hit) {
		exploBall(-1);
		PlayPannedSnd(explosionbig,0.0f);
	}
}

// Spieler Tod
void killSpieler(int dx,int dy) {
	sprites->a+=framespeed;
	sprites->til=34;
	if (sprites->a>=2000) { // in Rohr verschwinden
		int an;
		if (rohrx>spielerx) spielerx+=framespeed;
		if (rohrx<spielerx) spielerx-=framespeed;
		an=(sprites->a-2000.0f)/3.0f;
		if ((int)an>5) {int x=spielerx+10;int y=spielery-4;
						an=5;oldlevel=actlevel;
						x=1+x/33;
						y=1+y/30;
							returnx=-1;
							returny=-1;
							int min=0;
							int max=0;
							int i=0;
							bool found=FALSE;
							if (actlevel==1) {min=0;max=11;}
							if (actlevel==2) {min=12;max=21;}
							if (actlevel==3) {min=22;max=34;}
							for (i=min;i<=max;i++) {
								if (sternx[i]==x && sterny[i]==y) {oldlevel=actlevel;actlevel=5+i;found=TRUE;
																	returnx=x;returny=y;actstern=-1;
																	if (sterne[i]==1) actstern=i;
								}
							}
							if (!found) {oldlevel=actlevel;actlevel=5;}
						initSpielfeld();blitSpielfeld();
						spacewait=3;
						}

		if (spacewait!=3) sprites->til=111+an;
	}
	else if (sprites->a>=100) { //lv geschafft
		if (sprites->a>=230) {
			actlevel=oldlevel;
			initSpielfeld();blitSpielfeld();
		}
	}
	else if (sprites->a>=80) {  // zeige Menu
		/*int a,b;
		for (b=7;b<=9;b++) {
			for (a=6;a<=11;a++) {
				blitTile(a+dx/33,b+dy/30,122, 0, 0);
			}
		}
		for (a=7;a<=11;a++) {
			blitTile(a+dx/33,6+dy/30,149, 0, 0);
			blitTile(a+dx/33,10+dy/30,150, 0, 0);
		}
		for (b=7;b<=9;b++) {
			blitTile(6+dx/33,b+dy/30,138, 0, 0);
			blitTile(12+dx/33,b+dy/30,139, 0, 0);
		}
		blitTile(6+dx/33,6+dy/30,151, 0, 0);
		blitTile(12+dx/33,6+dy/30,152, 0, 0);
		blitTile(6+dx/33,10+dy/30,153, 0, 0);
		blitTile(12+dx/33,10+dy/30,195, 0, 0);	*/	
		MenuType=FALSE;Menu=TRUE;}//{initSpielfeld();blitSpielfeld();}
}

// Teleport
void teleportSpieler() {
	sprites->b+=1;
	sprites->til=34;
	speedx=0;
	if (sprites->b>=30) {exploBall(sprites->c);sprites->b=0;}
}

//-------------------------
// Spieler Bewegung
void moveSpieler(int dx,int dy) {
	static int nullcount=0;
//	static float xwerte[3];
	static int xwertcount=0;
	static int thrust;
	int		i;
//	HRESULT hr;
	BOOL	gestoppt;
	BOOL	richtungswechsel=FALSE;
	int		richtung=0;

//------------KEYBOARD
//  BYTE    diks[256];   // DirectInput keyboard state buffer 

//  Keyboard->GetDeviceState( sizeof(diks), &diks );


/*  for( i = 0; i < 256; i++ ) 
  {
      if( diks[i] & 0x80 ) fps=i;
  }*/
  float dix=0;

//--------------------------

	if (startcounter<4) {startcounter+=1;dix=0;}
	if (bounce==0) {
		if (input.key & KEY_LEFT) {speedx-=0.5f*framespeed;dix=-1;}
		if (input.key & KEY_RIGHT) {speedx+=0.5f*framespeed;dix=1;}
/*		if ((diks[203] & 0x80)||(diks[75] & 0x80)) {speedx-=0.5f*framespeed;dix=-1;}
		if ((diks[205] & 0x80)||(diks[77] & 0x80)) {speedx+=0.5f*framespeed;dix=1;}*/
		richtungswechsel=FALSE;
		
		if (dix>0) {
			if (richtung==-1) richtungswechsel=TRUE;
			if (gestoppt|richtungswechsel) {
				for (i=0;i<=2;i++) xwerte[i]=dix;
			}
			xwertcount=(xwertcount+1)%3;
			xwerte[xwertcount]=dix;
			nullcount=0;
			richtung=1;
			gestoppt=FALSE;}
		if (dix<0) {
			if (richtung==1) richtungswechsel=TRUE;
			if (gestoppt|richtungswechsel) {
				for (i=0;i<=2;i++) xwerte[i]=dix;
			}
			xwertcount=(xwertcount+1)%3;
			xwerte[xwertcount]=dix;
			nullcount=0;
			richtung=-1;
			gestoppt=FALSE;}
	
		if (dix==0) {
			nullcount++;
			if (nullcount>=3) {
				for (i=0;i<=2;i++) xwerte[i]=0;
				speedx=0;
				gestoppt=TRUE;
				richtung=0;
				if (speedx>0) speedx/=4;
				if (speedx<0) speedx/=4;
			}
		}
	}
	else {
		if (!eis) {
			bounce+=framespeed;
			if (bounce>=20) bounce=0;
		}
	}

	if (speedx<-3) speedx=-3;
	if (speedx>3) speedx=3;
	if (!eis) {
		thrust=1;
		if (input.key & KEY_X) thrust = 2;
//		if ((diks[57] & 0x80) ||(diks[42] & 0x80) || (diks[54] & 0x80)) thrust=2;
	}

	spielerx=spielerx+speedx*framespeed;
	spielery=spielery+speedy*thrust*framespeed;

	checkCollision();
	nmeCollision();

	if (bomb) spielercol=rand()%6;

//	if ((diks[47] & 0x80)) PlayPannedSnd(tschirp,0.0f);

	if (!nomenupress) {
		if (input.key & KEY_START) {	// ESC/Return gedrückt->zeige Menü
			/*int x,y;
			for (y=7;y<=10;y++) {
				for (x=6;x<=11;x++) {
					blitTile(x+dx/33,y+dy/30,122, 0, 0);
				}
			}
			for (x=7;x<=11;x++) {
				blitTile(x+dx/33,6+dy/30,149, 0, 0);
				blitTile(x+dx/33,11+dy/30,150, 0, 0);
			}
			for (y=7;y<=10;y++) {
				blitTile(6+dx/33,y+dy/30,138, 0, 0);
				blitTile(12+dx/33,y+dy/30,139, 0, 0);
			}
			blitTile(6+dx/33,6+dy/30,151, 0, 0);
			blitTile(12+dx/33,6+dy/30,152, 0, 0);
			blitTile(6+dx/33,11+dy/30,153, 0, 0);
			blitTile(12+dx/33,11+dy/30,195, 0, 0);*/
			MenuType=TRUE;
			Menu=TRUE;
		}
	} else {
		if (!(input.key & KEY_START)) {
			nomenupress=false;
		}
	}

	mausrad=0;
}


// Flip the surfaces
void FlipScreen( void )
{
	#ifndef PANDORA
		SDL_Delay((20 - (SDL_GetTicks() - frametime) <= 20) ? 20 - (SDL_GetTicks() - frametime) : 0);
		frametime = SDL_GetTicks();
	#endif
	videoSwapBuffers();
	videoClearScreen();
/*    HRESULT     ddrval;
	bool drawn=FALSE;

	
    while(!drawn)
    {
        ddrval = frontSurface->Flip(NULL,0);
        
		if( ddrval == DD_OK )
        {
            drawn=TRUE;;
        }
        else if( ddrval == DDERR_SURFACELOST )
        {
			drawn=TRUE;
		}
        else if( ddrval == DDERR_WASSTILLDRAWING )
        {
            drawn=FALSE;
        }
    }*/

}

//schwarzen Balken rechts zeichnen
void clScreen() {
	videoClearScreen();
	/*
//	DDBLTFX                     ddbltfx;	
	ZeroMemory(&ddbltfx, sizeof(ddbltfx));
	ddbltfx.dwSize = sizeof(ddbltfx);
	ddbltfx.dwFillColor = 0;
	RECT r;
	r.top=0;
	r.bottom=480;
	r.left=632;
	r.right=640;
/*	backSurface->Blt( 
	&r,        // Destination
	NULL,        // No source surface
	NULL,        // No source rectangle
	DDBLT_COLORFILL, &ddbltfx);
	FlipScreen();
	backSurface->Blt( 
	&r,        // Destination
	NULL,        // No source surface
	NULL,        // No source rectangle
	DDBLT_COLORFILL, &ddbltfx);*/
}

/////////////////////////////////
// Spiel Menue

// INGAME MENU
void drawMenu(int rx,int ry) {
	
	static int newselect=0;
	int i;
	BYTE    diks[256];
	static bool keypressed=true;

	if (!MenuType && newselect==0) newselect=1;

	int ox=218-rx%33;
	int oy=196-ry%30;
	int a=0;
	if (!MenuType) {a=1;oy-=20;}
	bool chosen=FALSE;
	int mod=0;
	
	// Menu Background
	int x, y, k=(int)(!MenuType);
	/*for (y=1;y<=18;y++) {
		for (x=1;x<=24;x++) {
			blitTile2(x*33, y*30, 137);
		}
	}*/
	for (y=7;y<=10-k;y++) {
		for (x=7;x<=11;x++) {
			blitTile2(x*33, y*30, 122);
		}
	}
	for (x=7;x<=11;x++) {
		blitTile2(x*33, 6*30, 149);
		blitTile2(x*33, (11-k)*30, 150);
	}
	for (y=7;y<=10-k;y++) {
		blitTile2(6*33, y*30, 138);
		blitTile2(12*33, y*30, 139);
	}
	blitTile2(6*33, 6*30, 151);
	blitTile2(12*33, 6*30, 152);
	blitTile2(6*33, (11-k)*30, 153);
	blitTile2(12*33, (11-k)*30, 195);
	//---------------
	for (i=a;i<=6;i++) {
		chosen=FALSE;
		mod=0;
		if (newselect==i) {chosen=TRUE;mod=1;}
		switch (i) {
		case 0: {
				blitString("continue game",0+ox,0+oy,mod);
				break;
				}
		case 1: {
				blitString("restart level",0+ox,20+oy,mod);
				break;
				}
		case 2: {
				blitString("leave level",0+ox,40+oy,mod);
				break;
				}
		case 3: {
				blitString("gamespeed",0+ox,60+oy,mod);
				blitNumber((int)100-((int)GAMESPEED-5)*2,105+ox,60+oy,FALSE,TRUE,mod);
				break;
				}
		case 4: {
				blitString("music",0+ox,80+oy,mod);
				if (!MUSIC_OK) blitString("error",65+ox,80+oy,mod);
				else {
					if (MUSIC_ON) blitString("on",65+ox,80+oy,mod);
					else blitString("off",65+ox,80+oy,mod);
				}				
				break;
				}
		case 5: {
				blitString("sound",0+ox,100+oy,mod);
				if (!SOUND_OK) blitString("error",60+ox,100+oy,mod);
				else {
					if (SOUND_ON) blitString("on",60+ox,100+oy,mod);
					else blitString("off",60+ox,100+oy,mod);
				}
				break;
				}
		case 6: {
				blitString("back to main menu",0+ox,120+oy,mod);
				break;
				}
		}	
	}	
	int soundtyp=0;
//	Keyboard->GetDeviceState( sizeof(diks), &diks );
	if (!keypressed) {
		if (newselect==0) {	//continue game
			if (input.key & KEY_A) {
				Menu=FALSE;MainMenu=FALSE;Maininit=FALSE;blitSpielfeld();
				newselect=15;
				keypressed=true;
				soundtyp=1;
				nomenupress=true;
			}
		}
		if (newselect==1) {	//restart level
			if (input.key & KEY_A) { 
				restart=TRUE;
				Menu=FALSE;MainMenu=FALSE;Maininit=FALSE;
				newselect=15;
				keypressed=true;
				soundtyp=1;

			}
		}
		bool leavgam=false;
		if (newselect==2) { //leave level
			if (input.key & KEY_A) { 
				if (actlevel>4) {
					actlevel=oldlevel;
					Menu=FALSE;MainMenu=FALSE;Maininit=FALSE;
					newselect=15;
					keypressed=true;
					soundtyp=1;
					initSpielfeld();blitSpielfeld();
				} else {
					leavgam=true;
				}
			}
		}
		if (newselect==3) { // Gamespeed
			if((input.key & KEY_RIGHT) && GAMESPEED>5 ) {GAMESPEED-=1;keypressed=true;soundtyp=1;}
			if((input.key & KEY_LEFT) && GAMESPEED<55 ) {GAMESPEED+=1;keypressed=true;soundtyp=1;}
		}
		if (newselect==4) { //music on/off
			if((input.key & KEY_A) && SOUND_OK) {MUSIC_ON=!MUSIC_ON;keypressed=true;soundtyp=1;}
/*			else if( (diks[203] & 0x80) && MUSIC_OK ) {MUSIC_ON=!MUSIC_ON;keypressed=true;soundtyp=1;}
			else if( (diks[75] & 0x80) && MUSIC_OK ) {MUSIC_ON=!MUSIC_ON;keypressed=true;soundtyp=1;}
			else if( (diks[77] & 0x80) && MUSIC_OK ) {MUSIC_ON=!MUSIC_ON;keypressed=true;soundtyp=1;}
			else if ( diks[28] & 0x80 || diks[156] & 0x80 || diks[42] & 0x80 || diks[54] & 0x80 || diks[57] & 0x80) {
				if (MUSIC_OK) {MUSIC_ON=!MUSIC_ON;keypressed=true;soundtyp=1;}
			}*/
		}
		if (newselect==5) { //sound on/off
			if( (input.key & KEY_A) && SOUND_OK) {SOUND_ON=!SOUND_ON;keypressed=true;soundtyp=1;}
/*			else if( (diks[203] & 0x80) && SOUND_OK ) {SOUND_ON=!SOUND_ON;keypressed=true;soundtyp=1;}
			else if( (diks[75] & 0x80) && SOUND_OK ) {SOUND_ON=!SOUND_ON;keypressed=true;soundtyp=1;}
			else if( (diks[77] & 0x80) && SOUND_OK ) {SOUND_ON=!SOUND_ON;keypressed=true;soundtyp=1;}
			else if ( diks[28] & 0x80 || diks[156] & 0x80 || diks[42] & 0x80 || diks[54] & 0x80 || diks[57] & 0x80) {
				if (SOUND_OK) {SOUND_ON=!SOUND_ON;keypressed=true;soundtyp=1;}
			}
*/		}
		if (newselect==6 || leavgam) { //back to main menu
			if (input.key & KEY_A) { 
				{Menu=FALSE;MainMenu=TRUE;Maininit=FALSE;blitSpielfeld();keypressed=true;
				newselect=15;returnx=-1;oldlevel=-1;soundtyp=1;}
			}
		}
		if(input.key & KEY_UP) {newselect-=1;keypressed=true;soundtyp=2;}
		if(input.key & KEY_DOWN) {newselect+=1;keypressed=true;soundtyp=2;}
		if (newselect<0) newselect=6;
		if (newselect==0 && !MenuType) newselect=6;
		if (newselect>6 && newselect!=15) newselect=0;
		if (newselect==15) newselect=0;
	}
	else { //keypressed==true
		if (input.key == 0)
			keypressed=false;
	}
	if (soundtyp==1) PlayPannedSnd(bleep10,0.0f);
	if (soundtyp==2) PlayPannedSnd(bleep1,0.0f);
}


// MAIN MENU
void drawMainMenu(int rx,int ry) {

	static int menuselect=0;
	static bool mauspress=TRUE;
	
	static int newselect=1;
	static bool keypressed=true;

	static int gameselect=0;
	static bool gamedelete=FALSE;

	int lx,ly,lev,i;
	
//	BYTE    diks[256];   // DirectInput keyboard state buffer 

	int soundtyp=0;

	if (!showinfo) {
				int ox=151;
				int oy=130;
				bool chosen=FALSE;
				int mod=0;
				char* st;
				for (i=0;i<=10;i++) {
					chosen=FALSE;
					mod=0;
					if (newselect==i+1) {chosen=TRUE;mod=1;}
					
					switch (i) {
					case 0: {
							blitString("start game",0+ox,0+oy,mod);
							break;
							}
					case 1: {
							if (gameselect==0 && newselect!=2) mod=2;
							if (gamedelete && gameselect==0) mod=3;
							blitString("save game 1",0+ox,20+oy,mod);
							blitNumber(percStars(1),117+ox,20+oy,FALSE,TRUE,mod);
							break;
							}
					case 2: {
							if (gameselect==1 && newselect!=3) mod=2;
							if (gamedelete && gameselect==1) mod=3;
							blitString("save game 2",0+ox,40+oy,mod);
							blitNumber(percStars(2),117+ox,40+oy,FALSE,TRUE,mod);
							break;
							}
					case 3: {
							if (gameselect==2 && newselect!=4) mod=2;
							if (gamedelete && gameselect==2) mod=3;
							blitString("save game 3",0+ox,60+oy,mod);
							blitNumber(percStars(3),117+ox,60+oy,FALSE,TRUE,mod);
							break;
							}
					case 4: {
							if (gameselect==3 && newselect!=5) mod=2;
							if (gamedelete && gameselect==3) mod=3;
							blitString("save game 4",0+ox,80+oy,mod);
							blitNumber(percStars(4),117+ox,80+oy,FALSE,TRUE,mod);
							break;
							}
					case 5: {
							if (gameselect==4 && newselect!=6) mod=2;
							if (gamedelete && gameselect==4) mod=3;
							blitString("save game 5",0+ox,100+oy,mod);
							blitNumber(percStars(5),117+ox,100+oy,FALSE,TRUE,mod);
							break;
							}
					case 6: {
							blitString("gamespeed",0+ox,120+oy,mod);
							blitNumber((int)100-((int)GAMESPEED-5)*2,105+ox,120+oy,FALSE,TRUE,mod);
							break;
							}
					case 7: {
							blitString("music",0+ox,140+oy,mod);
							if (!MUSIC_OK) blitString("error",64+ox,140+oy,mod);
							else {
								if (MUSIC_ON) blitString("on",64+ox,140+oy,mod);
								else blitString("off",64+ox,140+oy,mod);
							}
							break;
							}
					case 8: {
							blitString("sound",0+ox,160+oy,mod);
							if (!SOUND_OK) blitString("error",60+ox,160+oy,mod);
							else {
								if (SOUND_ON) blitString("on",60+ox,160+oy,mod);
								else blitString("off",60+ox,160+oy,mod);
							}
							break;
							}
					case 9: {
							blitString("instructions",0+ox,180+oy,mod);
							break;
							}
					case 10: {
							blitString("quit game",0+ox,200+oy,mod);
							break;
							}


					}
				}
	blitKlobus();
	}
	else {
		blitInstructions();
	}


	// Menüsteuerung über Cursortasten
/*	Keyboard->GetDeviceState( sizeof(diks), &diks );
*/
	if (!showinfo) {
			if (!keypressed) {
				if (newselect==1) {	//start game
					if (input.key & KEY_A) { 
						restart=TRUE;
						Menu=FALSE;MainMenu=FALSE;Maininit=FALSE;
						actlevel=1;
						showinfo=FALSE;
						keypressed=true;
						actgame=gameselect;
						copyGame(actgame);
						soundtyp=1;
						colreset=true;
					}
				}
				if (newselect>=2 && newselect<=6) {
					if (input.key & KEY_Y) { //delete
						if (gamedelete) { //lösche savegame
							clearGame(newselect-2);
							gamedelete=FALSE;
							keypressed=true;
							soundtyp=3;
						}
						else {
							gamedelete=TRUE;
							gameselect=newselect-2;
							keypressed=true;
							soundtyp=1;
						}
					}
				}
				if(input.key & KEY_UP) {newselect-=1;keypressed=true;gamedelete=FALSE;soundtyp=2;}
				if(input.key & KEY_DOWN) {newselect+=1;keypressed=true;gamedelete=FALSE;soundtyp=2;}
				if (newselect==7) {
					if((input.key & KEY_RIGHT) && GAMESPEED>5 ) {GAMESPEED-=1;keypressed=true;soundtyp=1;}
					if( (input.key & KEY_LEFT) && GAMESPEED<55 ) {GAMESPEED+=1;keypressed=true;soundtyp=1;}
				}
				if (newselect==8) {
					if( (input.key & KEY_A) && MUSIC_OK ) {MUSIC_ON=!MUSIC_ON;keypressed=true;soundtyp=1;}
				}
				if (newselect==9) {
					if( (input.key & KEY_A) && SOUND_OK ) {SOUND_ON=!SOUND_ON;keypressed=true;soundtyp=1;}
				}
				if (newselect==10) { //instructions
					if (input.key & KEY_A) {
						int x,y;			
						for (y=5;y<=12;y++) {
							for (x=5;x<=11;x++) {
								spielfeld[x][y]=spielfeld[x+1][y-1];
							}
						}
						for (x=13;x<=17;x++) {
								for (y=6;y<=10;y++) {
									spielfeld[x][y]=spielfeld[18][10];
								}
						}
						blitSpielfeld();
						showinfo=TRUE;
						keypressed=true;
						soundtyp=1;
					}
				}
				if (newselect==11) { //end game
					if (input.key & KEY_A) {
						killGame=true;
					}
				}
			}
			else {
				if (input.key == 0) keypressed=false;
			}
			if (newselect<1) newselect=11;
			if (newselect>11) newselect=1;

			if (input.key & KEY_A) {
				if (newselect >=2 && newselect <=6 && !keypressed) {gameselect=newselect-2;soundtyp=1;keypressed=true;}
			}
	blitSkull();
	} else { //show instructions
			if (!keypressed) {
					 if (input.key != 0) {
						 keypressed=true;showinfo=false;
						 int x,y;
					 		// Menu Background
							for (y=6;y<=11;y++) {
								for (x=6;x<=10;x++) {
									spielfeld[x][y]=122;
								}
							}
							for (x=6;x<=10;x++) {
								spielfeld[x][5]=149;
								spielfeld[x][12]=150;
							}
							for (y=6;y<=11;y++) {
								spielfeld[5][y]=138;
								spielfeld[11][y]=139;
							}
							spielfeld[5][5]=151;
							spielfeld[11][5]=152;
							spielfeld[5][12]=153;
							spielfeld[11][12]=195;

							blitSpielfeld();
							blitSkull();
							soundtyp=1;
							//---------------
					 }
			}
			else if (input.key == 0) keypressed=false;
	}
	
	//blitSkull();
	
	// spiele menubeeps
	if (soundtyp==1) PlayPannedSnd(bleep10,0.0f);
	if (soundtyp==2) PlayPannedSnd(bleep1,0.0f);
	if (soundtyp==3) PlayPannedSnd(explosionfeind,0.0f);
}

/*
void drawFps(LPDIRECTDRAWSURFACE7 ptr,int ox,int oy) {
	HDC hdc;

	char s[]="fps: 0000";
	char t[]="speed: 000";
	int z;
	tick=GetTickCount();
	z=fps;
	s[5]=fps/1000+'0';
	z=fps%1000;
	s[6]=z/100+'0';
	z=fps%100;
	s[7]=z/10+'0';
	z=fps%10;
	s[8]=z+'0';
	ptr->GetDC(&hdc); 
	SetBkColor(hdc, RGB(70, 70, 100)); 
	SetTextColor(hdc, RGB(255,255,0)); 
	TextOut(hdc, 5+ox, 5+oy, s, lstrlen(s));

	//gamespeed
	z=(int)GAMESPEED;
	t[7]=z/100+'0';
	z=(int)GAMESPEED%100;
	t[8]=z/10+'0';
	z=(int)GAMESPEED%10;
	t[9]=z+'0';
	TextOut(hdc, 100+ox, 5+oy, t, lstrlen(t));
	ptr->ReleaseDC(hdc);
}*/


// Spacetaste muß gedrückt werden
void waitforSpace() {
	BYTE    diks[256];
//	Keyboard->GetDeviceState( sizeof(diks), &diks );
	if (spacewait==3 && (input.key & KEY_X)) spacewait=2;
	else if (spacewait==2 && (input.key & KEY_X)) spacewait=1;
	else if (spacewait==1 && (input.key ^ KEY_X)) spacewait=0;
}

// push SPACE or SHIFT ! zeichnen
void blitSpacewait(int sx,int sy) {
	RECT r;
	static float oy=0.0f;
	static float orr=1.0f;
	r.left=5*33;
	r.right=9*33+30;
	r.top=8*30;
	r.bottom=8*30+28;
	int x,y;
	oy=oy+framespeed*orr*0.5f;
	if (oy<-3.0f) orr=1.0f;
	if (oy>3.0f) orr=-1.0f;
	x=spielerx-sx-63;
	y=spielery-sy-30+(int)oy;
	if (x<0) x=0;
	if (x>467) x=467;
	if (y<0) y=0;
	videoBlit(tileSurface, &r, x, y);
//	backSurface->BltFast(x,y,tileSurface,&r,DDBLTFAST_SRCCOLORKEY);
}



// spiel die musik (0-11)
void checkMusic() {
	/*static DWORD stoptime=-1;
	bool playing=false;
	if (pPerf->IsPlaying(pSegment, NULL) == S_OK) playing=true;
	if (playing) stoptime=0;
//	if ( (!MUSIC_OK || !MUSIC_ON) && playing) {pPerf->Stop(pSegment,pSegState,0,0);stoptime=-1;playing=false;}
	if (!MUSIC_OK || !MUSIC_ON) stoptime=-1;
	char* lied;
//	HRESULT hret;
	if (MUSIC_OK && MUSIC_ON) {
		if (!playing) {
//			DWORD nowtime=GetTickCount();
			if (stoptime==0) stoptime=nowtime;
			if ( ((nowtime-stoptime)>5500) || stoptime==-1) {
				actMusic++;
				if (actMusic>10) actMusic=0;
				switch (actMusic) {
					case 0:
						lied="TRACK01";
					break;
					case 1:
						lied="TRACK02";
					break;
					case 2:
						lied="TRACK03";
					break;
					case 3:
						lied="TRACK04";
					break;
					case 4:
						lied="TRACK05";
					break;
					case 5:
						lied="TRACK06";
					break;
					case 6:
						lied="TRACK07";
					break;
					case 7:
						lied="TRACK08";
					break;
					case 8:
						lied="TRACK09";
					break;
					case 9:
						lied="TRACK10";
					break;
					case 10:
						lied="TRACK11";
					break;
				}
				int tries=0;
				hret=false;
				while (!hret && tries<12) {
//					hret=LoadMidi2(NULL,pLoader,lied,(void**)&pSegment);
					tries++;
				}
				if (pSegment) {
					stoptime=0;
					pSegment->SetParam(GUID_StandardMIDIFile,-1,0,0,(void*)pPerf);
					pSegment->SetParam(GUID_Download,-1,0,0,(void*)pPerf);
					pPerf->PlaySegment(pSegment,0,0,&pSegState);
				}	
			}//time>...
		}//isPlaying
	}*/
	if(MUSIC_ON) {
		if(Mix_PausedMusic()) {
			Mix_ResumeMusic();
		}
		if(!Mix_PlayingMusic()) {
			if(mix_music!=NULL) {
				Mix_FreeMusic(mix_music);
				mix_music=NULL;
			}
			mix_music=Mix_LoadMUS(music[music_current]);
			Mix_PlayMusic(mix_music, 1);
			music_current=music_current>=sizeof(music)/sizeof(char *)-1?0:music_current+1;
		}
		
	} else if(Mix_PlayingMusic()&&!Mix_PausedMusic()) {
		Mix_PauseMusic();
	}
}


// Restore alle Surfaces
void restoreAll() {
/*	HRESULT hRet;
	g_pDD->RestoreAllSurfaces();
	hRet = DDReLoadBitmap(tileSurface,"TILEMAP");
	hRet = DDReLoadBitmap(background,"BACKGROUND");
	hRet = DDReLoadBitmap(skullimage,"SKULL");
	if (hRet==DD_OK) clScreen();

	// Keyboard erzeugen
    hRet = dinpt->CreateDevice(GUID_SysKeyboard, &Keyboard, NULL );
    hRet = Keyboard->SetDataFormat( &c_dfDIKeyboard );
    hRet = Keyboard->SetCooperativeLevel( window, 
                                     DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
    Keyboard->Acquire();
*/}
void checkSurfaces() {
/*	if (tileSurface->IsLost() == DDERR_SURFACELOST) restoreAll();
	else if (background->IsLost() == DDERR_SURFACELOST) restoreAll();
	else if (skullimage->IsLost() == DDERR_SURFACELOST) restoreAll();*/
}


//-------------------------------------
//Aufräumarbeiten
//-------------------------------------
static void
ReleaseAllObjects(void)
{
 /*   if (g_pDD != NULL)
    {
        if (frontSurface != NULL && frontSurface->IsLost()==DD_OK)
        {
            frontSurface->Release();
            frontSurface = NULL;
        }
        if (splashscreen != NULL && splashscreen->IsLost()==DD_OK)
        {
            splashscreen->Release();
            splashscreen = NULL;
        }
        if (skullimage != NULL && skullimage->IsLost()==DD_OK)
        {
            skullimage->Release();
            skullimage = NULL;
        }
        if (titelbild != NULL && titelbild->IsLost()==DD_OK)
        {
            titelbild->Release();
            titelbild = NULL;
        }
        if (tileSurface != NULL && tileSurface->IsLost()==DD_OK)
        {
            tileSurface->Release();
            tileSurface = NULL;
        }
        if (background != NULL && background->IsLost()==DD_OK)
        {
            background->Release();
            background = NULL;
        }
        if (gameSurface != NULL && gameSurface->IsLost()==DD_OK)
        {
            gameSurface->Release();
            gameSurface = NULL;
        }
        if (gameSurface1 != NULL && gameSurface1->IsLost()==DD_OK)
        {
            gameSurface1->Release();
            gameSurface1 = NULL;
        }
        if (gameSurface2 != NULL && gameSurface2->IsLost()==DD_OK)
        {
            gameSurface2->Release();
            gameSurface2 = NULL;
        }
        if (gameSurface3 != NULL && gameSurface3->IsLost()==DD_OK)
        {
            gameSurface3->Release();
            gameSurface3 = NULL;
        }
        if (gameSurface4 != NULL && gameSurface4->IsLost()==DD_OK)
        {
            gameSurface4->Release();
            gameSurface4 = NULL;
        }
    }*/
}
VOID DestroySound()
{
 /*   if( dsound )
    {
        DSUtil_DestroySound( colorswitch );
        DSUtil_DestroySound( explosionflyer );
        DSUtil_DestroySound( explosionbig );
        DSUtil_DestroySound( explosionfeind );
        DSUtil_DestroySound( bouncesound );
        DSUtil_DestroySound( coolmann );
        DSUtil_DestroySound( coolfrau );
        DSUtil_DestroySound( tschirp );
        DSUtil_DestroySound( flushsound );
        DSUtil_DestroySound( woosh );
        DSUtil_DestroySound( bleep1 );
        DSUtil_DestroySound( bleep10 );
        dsound->Release();
		delete dsound;
    }
*/}
void DestroyMusic() {

/*    if (pSegment) pSegment->Release();
    if (pPerf) {
		pPerf->CloseDown();
		pPerf->Release();
	}
    if (pLoader) pLoader->Release();
    CoUninitialize();
*/}
void killApplication() {

	killed=true;

	DestroySound();

//	if (GEHE_ZU_SITE==1) ShellExecute(NULL, "open", "iexplore", "http://www.blueskied.com", NULL, SW_SHOWNORMAL);

	ReleaseAllObjects();

/*	Mouse->Release();
	Keyboard->Release();
	dinpt->Release();	*/
}

void showSplashscreen() {
	/*static DWORD zeitl=-1;
	static int xwid=0;
	static bool fuksuk=true;

	if (zeitl==-1) zeitl=GetTickCount();
	DWORD timjez=GetTickCount();
	DWORD dauerwurst=timjez-zeitl;
	if (dauerwurst>20) {
	

		if (splashend) {
			if (fuksuk) {xwid+=1;fuksuk=false;}
			DDBLTFX                     ddbltfx;	
			ZeroMemory(&ddbltfx, sizeof(ddbltfx));
			ddbltfx.dwSize = sizeof(ddbltfx);
			ddbltfx.dwFillColor = 0;
			RECT r;
			xwid=xwid-1;
			if (xwid<1 || xwid>1000) splashscr=false;
			int x,y;
			for (x=0;x<=15;x++) {
				for (y=0;y<=11;y++) {
					r.top=y*40+20-xwid;
					r.bottom=r.top+1;
					r.left=x*40+20-xwid;
					r.right=x*40+20+xwid+1;
					if (r.right>640) r.right=640;
					backSurface->Blt(&r, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
					r.top=y*40+20+xwid;
					r.bottom=r.top+1;
					backSurface->Blt(&r, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
					r.top=y*40+20-xwid;
					r.bottom=y*40+20+xwid;
					r.left=x*40+20-xwid;
					r.right=r.left+1;	
					if (r.right>640) r.right=640;
					backSurface->Blt(&r, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
					r.left=x*40+20+xwid;
					r.right=r.left+1;		
					if (r.right>640) r.right=640;
					backSurface->Blt(&r, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
				}
			}			
		} else {
			xwid=xwid+1;
			if (xwid>20) xwid=20;
			RECT r;
			int x,y;
			for (x=0;x<=15;x++) {
				for (y=0;y<=11;y++) {
					r.top=y*40+20-xwid;
					r.bottom=y*40+20+xwid;
					r.left=x*40+20-xwid;
					r.right=x*40+20+xwid;		
					backSurface->BltFast(r.left,r.top,splashscreen,&r,DDBLTFAST_WAIT);
				}
			}
		}
		zeitl=GetTickCount();
	}*/

}

// WERBESCREEN
void werbeschleife() {

	/*RECT r;
	if (!werbunggezeichnet) {		// Zeichne Werbescreen

		backSurface->BltFast(0,0,splashscreen,NULL,DDBLTFAST_WAIT);

		werbesprites=new Spritelist();
		werbesprites->til=86;
		werbesprites->x=100;
		werbesprites->y=100;
		werbesprites->sizex=12;
		werbesprites->sizey=20;
		werbesprites->next=NULL;
		werbunggezeichnet=true;
	}

	// ESC ?
	BYTE    diks[256];
	Keyboard->GetDeviceState( sizeof(diks), &diks );
	if ((diks[1] & 0x80)) {werbungaus=true;killGame=true;}
	if (f12kill) {werbungaus=true;killGame=true;}

	// Mauspointer steuern
	if (!werbungaus) {
		static int oldmx=-1;
		static int oldmy=-1;
		Mouse->GetDeviceState(sizeof(DIMOUSESTATE),&dims);

		if (oldmx!=-1) {
			r.top=100;
			r.left=380;
			r.right=r.left+12;
			r.bottom=r.top+20;
			backSurface->BltFast(oldmx,oldmy,	// Hintergrund wiederherstellen
					gameSurface4,
					&r,
					DDBLTFAST_WAIT
					);			
		}
		werbesprites->x+=dims.lX;
		werbesprites->y+=dims.lY;
		if (werbesprites->x>620) werbesprites->x=620;
		if (werbesprites->x<0) werbesprites->x=0;
		if (werbesprites->y>460) werbesprites->y=460;
		if (werbesprites->y<0) werbesprites->y=0;
		r.top=werbesprites->y;
		r.bottom=r.top+20;
		r.left=werbesprites->x;
		r.right=r.left+12;
		oldmy=r.top;
		oldmx=r.left;
		gameSurface4->BltFast(380,100,		// Hintergrund speichern
					backSurface,
					&r,
					DDBLTFAST_WAIT
					);

		if (dims.rgbButtons[0] & 0x80) {
			int maax,maay;
			maax=werbesprites->x;
			maay=werbesprites->y;
			if (maax>137 && maax<137+156) {
				if (maay>124 && maay<124+120) werbungaus=true;	//Spiel starten
				if (maay>258 && maay<258+120) {
							werbungaus=true;	//Demo od. Link
							killGame=true;
							GEHE_ZU_SITE=1;
				}
			}
		}
	}
	if (werbungaus) {
		splashscr=false;
		DDBLTFX                     ddbltfx;	
		ZeroMemory(&ddbltfx, sizeof(ddbltfx));
		ddbltfx.dwSize = sizeof(ddbltfx);
		ddbltfx.dwFillColor = 0;
		backSurface->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
		FlipScreen();
		backSurface->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
	}*/
}


//-------------------------------------
// HAUPTSCHLEIFE des Spiels
//-------------------------------------
void cilloMain() {

/*	if (splashscr) {
		if (WERBESCREEN >0 && !werbungaus) werbeschleife();
		else {
			BYTE    diks[256];
			Keyboard->GetDeviceState( sizeof(diks), &diks );
			int i;
			for (i=0;i<=255;i++) {
				if ((diks[i] & 0x80)) splashend=true;
			}

			showSplashscreen();
		}
	}
	else {*/

		if (killed) return;
		
		inputPoll();
		
		framespeed=(frmtick-frmlast)/GAMESPEED;
		if (framespeed>3) framespeed=3;
		frmlast=frmtick;
		frmtick=SDL_GetTicks();

		if (MainMenu || Menu) moveroom=FALSE;

		if (spacewait>0 && moveroom) spacewait=0;

		if (!GamesLoaded) {loadGames();GamesLoaded=TRUE;}

		if (restart) {initSpielfeld();blitSpielfeld();Menu=FALSE;restart=FALSE;}

		if (MainMenu && !Maininit) initMainMenu();

		RECT	r,r1,r2,r3,r4;
		//HRESULT hRet;
		float frmTime,newTime;

		static float menuscrx,menuscry;

		static int rax=0;
		static int ray=0;
		static int ratil=123;

		int spx;
		int spy;
		int i;
		spx=spielerx-33-10;
		spy=spielery-30-10;

		int tolx=30;
		int toly=20;

		viertel=1;
		if (spy>240-tolx/2) viertel+=2;	// 1 2
		if (spx>320-toly/2) viertel+=1;	// 3 4

		if (!Menu && !MainMenu) {
			switch (viertel) {
			case 1:
					if (scrx>0) scrx-=2;
					if (scry>0) scry-=2;
					break;
			case 2:
					if (scrx<160) scrx+=2;
					if (scry>0) scry-=2;
					break;
			case 3:
					if (scrx>0) scrx-=2;
					if (scry<120) scry+=2;
					break;
			case 4:
					if (scrx<160) scrx+=2;
					if (scry<120) scry+=2;
					break;
			}
		}
		else startcounter=0;
		
		// zeichne Menu-Farbhintergrund
		DWORD colnow=SDL_GetTicks();
		if (colreset) {colreset=false;collast=0;}

		if (MainMenu) {
			scry=0;
			scrx=13;
			if (colnow-collast>3500) { //nur alle 3.5 sek. wechsel
				scry=0;
				scrx=13;

				bool diago=false;
				int rxx=rax;
				int ryy=ray;
				while (!diago) {
					if (!(!showinfo && rxx>=4 && rxx<=10 && ryy>=4 && ryy<=11)) {
						if (!(!showinfo && rxx>=12 && rxx<=16 && ryy>=5 && ryy<=9)) {
							spielfeld[rxx+1][ryy+1]=ratil;
							blitTile(rxx,ryy,ratil, 0, 0);
						}
					}
					rxx--;
					ryy++;
					if (rxx<0) diago=true;
					else if (ryy>13) diago=true;
				}
				if (ray==0) {
					rax=rax+1;
					if (rax>=20) {ray=1;rax=19;}
				} else {
					ray=ray+1;
					if (ray>=14) {rax=0;ray=0;collast=SDL_GetTicks();
						ratil+=1;
						if (ratil==126) ratil=135;
						if (ratil>137) ratil=123;
					}
				}
			}
		}
		
		r.top=scry;
		r.left=scrx;
		r.right=scrx+640;
		r.bottom=scry+480;

		if (!Menu && !MainMenu) {
			if (sprites->a==0 && sprites->b==0 && spacewait==0) moveSpieler(r.left,r.top);
			if (sprites->a>0) killSpieler(r.left,r.top);
			if (sprites->b>0) teleportSpieler();
			if (spacewait==0) moveSprites();  // optimieren!!!!
		}

		r1.left=r.left;
		r1.right=396;
		r1.top=r.top;
		r1.bottom=300;

		r1.left=r.left;
		r1.right=396;
		r1.top=r.top;
		r1.bottom=300;
		r2.left=0;
		r2.right=r.left+236; //234
		r2.top=r.top;
		r2.bottom=300;

		r3.left=r1.left;
		r3.right=r1.right;
		r3.top=0;
		r3.bottom=180+r1.top;

		r4.left=r2.left;
		r4.right=r2.right;
		r4.top=r3.top;
		r4.bottom=r3.bottom;

/*		backSurface->BltFast(0,0,gameSurface1,&r1,DDBLTFAST_WAIT);
		backSurface->BltFast(396-r.left,0,gameSurface2,&r2,DDBLTFAST_WAIT);
		backSurface->BltFast(0,300-r1.top,gameSurface3,&r3,DDBLTFAST_WAIT);
		backSurface->BltFast(396-r.left,300-r1.top,gameSurface4,&r4,DDBLTFAST_WAIT);*/
		if (spacewait>0) blitSpacewait(r.left,r.top); // push SPACE or SHIFT !

		if (!MainMenu) blitSprites(r.left,r.top,sprites);
		
		if (actlevel<5 &&!MainMenu) {
			int numb=Sterne;
			if (numb<10) {
				blitString("  ",18,10,1);
				blitString("  ",18,12,1);
			} else {
				blitString("   ",18,10,1);
				blitString("   ",18,12,1);
			}
			blitString("ST",10,10,0); //zeichne Anzahl Sterne
			blitNumber(numb,32,13,FALSE,FALSE,0);
		}

		if (Menu) {
			drawMenu(0, 0);
		}
		else if (MainMenu) {
			drawMainMenu(0,0);
			if (!showinfo) blitTitex();
		}
//	}

//	if (WERBESCREEN >0 && !werbungaus) blitSprites(0,0,werbesprites);
	
/*	r4.top = 0;
	r4.left = 0;
	r4.bottom = 12;
	r4.right = 512;*/
//	videoClearScreen();
//	fprintf(stderr, "Tiles this frame: %i\n", tiles_per_frame);
	tiles_per_frame = 0;
//	videoBlit(tileSurface, &r4, 0, 0);
	FlipScreen();
	checkSurfaces();

//	if (splashscr) backSurface->BltFast(0,0,frontSurface,NULL,DDBLTFAST_WAIT);


	if (!splashscr) {
		//in anderen Raum gefahren ?
		if (actlevel<5 && !Menu && !MainMenu) {
			if (spielerx<0) {moveroom=TRUE;returnx=-1;oldlevel=actlevel;actlevel-=1;initSpielfeld();blitSpielfeld();}
			if (spielerx>770) {moveroom=TRUE;returnx=-1;oldlevel=actlevel;actlevel+=1;initSpielfeld();blitSpielfeld();}	
		}

		if (spacewait>0) waitforSpace();

		flipzaehler+=1;

		if(MUSIC_OK) checkMusic(); //spielt midi noch?

		BYTE    diks[256];
//		Keyboard->GetDeviceState( sizeof(diks), &diks ); 
//		if ((diks[56] & 0x80) && (diks[62] & 0x80)) killGame=true;
//		if (f12kill) killGame=true;
//		if (killGame) PostMessage(window, WM_CLOSE, 0, 0);

	}
}



//-----------------------------------------------------------------------------
// Name: InitFail()
// Desc: This function is called if an initialization function fails
//-----------------------------------------------------------------------------
/*HRESULT
InitFail(HWND hWnd, HRESULT hRet, LPCTSTR szError,...)
{
    char                        szBuff[128];
    va_list                     vl;

    va_start(vl, szError);
    vsprintf(szBuff, szError, vl);
    ReleaseAllObjects();
    MessageBox(hWnd, szBuff, TITLE, MB_OK);
    DestroyWindow(hWnd);
    va_end(vl);
    return hRet;
}*/




//-----------------------------------------------------------------------------
// Name: UpdateFrame()
// Desc: Displays the proper text for the page
//-----------------------------------------------------------------------------
static void
UpdateFrame()
{
	if (killGame) {
		killGamePl0x();
		exit(0);
	}
	cilloMain();
	blitSpielfeld();
}





//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The Main Window Procedure
//-----------------------------------------------------------------------------
int
WindowProc()
{
/*    HRESULT                     hRet;

    switch (message)
    {
        case WM_ACTIVATE:
            // Pause if minimized
            g_bActive = !((BOOL)HIWORD(wParam));
            return 0L;

        case WM_DESTROY:
            // Clean up and close the app
			killApplication();
            PostQuitMessage(0);
			DestroyMusic();
			if (g_pDD) g_pDD->Release();	//release ddraw object
			g_pDD = NULL;

            return 0L;
			break;

			
        case WM_KEYDOWN:
            // assets any non-accelerated key commands
            switch (wParam)
            {
                case VK_F12:
					f12kill=true;
                    return 0L;
					break;
				
            }
            break;
		
        case WM_SETCURSOR:
            // Turn off the cursor since this is a full-screen app
            SetCursor(NULL);
            return TRUE;
			break;

        //case WM_TIMER:
            // Update and flip surfaces
			/*
			timezaehler+=1;
			//fps=flipzaehler;
			//flipzaehler=0;
            if (g_bActive && TIMER_ID == wParam)
            {
					break;   
            }*/ /*
        //    break;
		//
    }
    return DefWindowProc(hWnd, message, wParam, lParam);*/
	return 0;
}




//-----------------------------------------------------------------------------
// Name: InitializeSound()
//-----------------------------------------------------------------------------
void InitializeSound(  )
{/*
	SOUND_OK=true;
    if( FAILED( DirectSoundCreate( NULL, &dsound, NULL ) ) ) SOUND_OK=false;

	if (SOUND_OK) {
		if( FAILED( dsound->SetCooperativeLevel( hWnd, DSSCL_NORMAL ) ) )
		{
			dsound->Release();
			dsound = NULL;
			SOUND_OK=false;
		}
	}*/
	if (SOUND_OK) {
		Mix_Chunk **sounds[]={
			&colorswitch,
			&explosionflyer,
			&explosionbig,
			&explosionfeind,
			&bouncesound,
			&coolmann,
			&coolfrau,
			&tschirp,
			&flushsound,
			&woosh,
			&bleep1,
			&bleep10,
		};
		int i;
		unsigned int len;
		void *p;
		for(i=0; i<sizeof(sounds)/sizeof(void *); i++) {
			p=snsbbfzGetData(assets, 4+i, &len);
			*sounds[i]=Mix_LoadWAV_RW(SDL_RWFromConstMem(p, len), 1);
		}
	}
}


//-----------------------------------------------------------------------------
// Name: InitApp()
// Desc: Do work required for every instance of the application:
//          Create the window, initialize data
//-----------------------------------------------------------------------------
int InitApp()
{
    /*HWND                        hWnd;
    WNDCLASS                    wc;
    DDSURFACEDESC2              ddsd;
    DDSCAPS2                    ddscaps;
    HRESULT                     hRet;

	DDSURFACEDESC2              tiledescr;
	DDSURFACEDESC2              bakdescr;

    // Set up and register window class
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH )GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NAME;
    wc.lpszClassName = NAME;
    RegisterClass(&wc);

    // Create a window
    hWnd = CreateWindowEx(WS_EX_TOPMOST,
                          NAME,
                          TITLE,
                          WS_POPUP,
                          0,
                          0,
                          GetSystemMetrics(SM_CXSCREEN),
                          GetSystemMetrics(SM_CYSCREEN),
                          NULL,
                          NULL,
                          hInstance,
                          NULL);
    if (!hWnd)
        return FALSE;
	window=hWnd;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    SetFocus(hWnd);

    ///////////////////////////////////////////////////////////////////////////
    // Create the main DirectDraw object
    ///////////////////////////////////////////////////////////////////////////
    hRet = DirectDrawCreateEx(NULL, (VOID**)&g_pDD, IID_IDirectDraw7, NULL);
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, "DirectDrawCreateEx FAILED");

    // Get exclusive mode
    hRet = g_pDD->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, "SetCooperativeLevel FAILED");

    // Set the video mode
	hRet=DD_FALSE;
	if (!DISPLAY_800x600) {
		hRet = g_pDD->SetDisplayMode(640,480, 16, 0, 0);			//16
		if (hRet != DD_OK) {
			hRet = g_pDD->SetDisplayMode(640,480, 32, 0, 0);		//24
			if (hRet != DD_OK) {
				hRet = g_pDD->SetDisplayMode(640,480, 24, 0, 0);	//8
			}
		}
	}
    if (hRet != DD_OK) {
	    hRet = g_pDD->SetDisplayMode(800,600, 16, 0, 0);
		if (hRet != DD_OK) {
			hRet = g_pDD->SetDisplayMode(800,600, 32, 0, 0);
			if (hRet != DD_OK) {
				hRet = g_pDD->SetDisplayMode(800,600, 24, 0, 0);
			}
		}
	}
	if (hRet!=DD_OK) return InitFail(hWnd, hRet, "SetDisplayMode FAILED");

    // Create the primary surface with 1 back buffer
    ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.dwBackBufferCount = 1;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP |
                          DDSCAPS_COMPLEX;

    hRet = g_pDD->CreateSurface(&ddsd, &frontSurface, NULL);
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, "create frontSurface FAILED");


    // Get a pointer to the back buffer
    ZeroMemory(&ddscaps, sizeof(ddscaps));
    ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
    hRet = frontSurface->GetAttachedSurface(&ddscaps, &backSurface);
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, "GetAttachedSurface FAILED");

	// erzeuge & lade TileSurface
	ZeroMemory(&tiledescr,sizeof(tiledescr));
	tiledescr.dwSize=sizeof(tiledescr);
	tiledescr.dwFlags = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
	tiledescr.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	tiledescr.dwWidth=463; //33x14
	tiledescr.dwHeight=449;  //448
	hRet = g_pDD->CreateSurface(&tiledescr,&tileSurface,NULL);
	if (hRet!=DD_OK)
		return InitFail(hWnd,hRet,"create TileSurface FAILED");
	hRet = DDReLoadBitmap(tileSurface,"TILEMAP");
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, "DDReLoadBitmap tilemap FAILED");

	// erzeuge & lade background
	ZeroMemory(&bakdescr,sizeof(bakdescr));
	bakdescr.dwSize=sizeof(bakdescr);
	bakdescr.dwFlags = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
	bakdescr.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	bakdescr.dwWidth=99*4;
	bakdescr.dwHeight=90*4;					//&background
	hRet = g_pDD->CreateSurface(&bakdescr,&background,NULL);
	if (hRet!=DD_OK)
		return InitFail(hWnd,hRet,"create background FAILED");
	hRet = DDReLoadBitmap(background,"BACKGROUND");
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, "DDReLoadBitmap background FAILED");

	// erzeuge gameSurface
	ZeroMemory(&bakdescr,sizeof(bakdescr));
	bakdescr.dwSize=sizeof(bakdescr);
	bakdescr.dwFlags = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
	bakdescr.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	//if (!widevideo) bakdescr.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	bakdescr.dwWidth=396;
	bakdescr.dwHeight=300;
	hRet = g_pDD->CreateSurface(&bakdescr,&gameSurface1,NULL);
	if (hRet!=DD_OK)
		return InitFail(hWnd,hRet,"create gameSurface1 FAILED");
	hRet = g_pDD->CreateSurface(&bakdescr,&gameSurface2,NULL);
	if (hRet!=DD_OK)
		return InitFail(hWnd,hRet,"create gameSurface2 FAILED");
	hRet = g_pDD->CreateSurface(&bakdescr,&gameSurface3,NULL);
	if (hRet!=DD_OK)
		return InitFail(hWnd,hRet,"create gameSurface3 FAILED");
	hRet = g_pDD->CreateSurface(&bakdescr,&gameSurface4,NULL);
	if (hRet!=DD_OK)
		return InitFail(hWnd,hRet,"create gameSurface4 FAILED");

	DDBLTFX                     ddbltfx;	
	ZeroMemory(&ddbltfx, sizeof(ddbltfx));
	ddbltfx.dwSize = sizeof(ddbltfx);
    ddbltfx.dwFillColor = 0;
    gameSurface1->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
    gameSurface2->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
	gameSurface3->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
	gameSurface4->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
	backSurface->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);

	// erzeuge & lade SKULL-bild
	ZeroMemory(&bakdescr,sizeof(bakdescr));
	bakdescr.dwSize=sizeof(bakdescr);
	bakdescr.dwFlags = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
	bakdescr.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	bakdescr.dwWidth=165;
	bakdescr.dwHeight=150;				
	hRet = g_pDD->CreateSurface(&bakdescr,&skullimage,NULL);
	if (hRet!=DD_OK)
		return InitFail(hWnd,hRet,"create skullimage FAILED");
	hRet = DDReLoadBitmap(skullimage,"SKULL");
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, "DDReLoadBitmap SKULL FAILED");

	// erzeuge & lade splashscreen
	ZeroMemory(&bakdescr,sizeof(bakdescr));
	bakdescr.dwSize=sizeof(bakdescr);
	bakdescr.dwFlags = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
	bakdescr.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	bakdescr.dwWidth=640;
	bakdescr.dwHeight=480;				
	hRet = g_pDD->CreateSurface(&bakdescr,&splashscreen,NULL);
	if (hRet!=DD_OK)
		return InitFail(hWnd,hRet,"create splashscreen FAILED");
	hRet = DDReLoadBitmap(splashscreen,"SPLASHSCREEN");
    if (hRet != DD_OK)
        return InitFail(hWnd, hRet, "DDReLoadBitmap splashscr. FAILED");
*/
	
	// MenuSprites initialisieren
	menusprites=new(Spritelist);
	menusprites->typ=6;
	menusprites->x=300;
	menusprites->y=200;
	menusprites->til=86;
	menusprites->sizex=33;
	menusprites->sizey=30;
	menusprites->next=NULL;
	menusprites->prev=NULL;

/*	// Input erzeugen	
	hRet = DirectInputCreate(hInstance,DIRECTINPUT_VERSION,&dinpt,NULL);
    if (hRet!=DI_OK) { 
		return InitFail(hWnd,hRet,"dinput FAILED");
	}
	
	// MAUS
	hRet = dinpt->CreateDevice(GUID_SysMouse,&Mouse,NULL);
	if (hRet!=DI_OK) {
	    return InitFail(hWnd,hRet,"creating Mouse Device failed");
	}
	hRet = Mouse->SetDataFormat(&c_dfDIMouse);
    if ( FAILED(hRet) ) 
	    return InitFail(hWnd,hRet,"setting Mouse Device failed");
    hRet = Mouse->SetCooperativeLevel(hWnd, 
                                        DISCL_EXCLUSIVE | DISCL_FOREGROUND);
    if (FAILED(hRet) ) 
	    return InitFail(hWnd,hRet,"Mouse Level failed");

	Mouse->Acquire();
	

	// Keyboard erzeugen
    hRet = dinpt->CreateDevice(GUID_SysKeyboard, &Keyboard, NULL );
    if( FAILED(hRet) ) 
        return InitFail(hWnd,hRet,"creating Keyboard Device failed");
    hRet = Keyboard->SetDataFormat( &c_dfDIKeyboard );
    if( FAILED(hRet) ) 
        return InitFail(hWnd,hRet,"SetDataFormat Keyboard failed");
    hRet = Keyboard->SetCooperativeLevel( hWnd, 
                                     DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
    if( FAILED(hRet) ) 
        return InitFail(hWnd,hRet,"SetCoop.Level Keyboard failed");
    Keyboard->Acquire();

	// Soundsystem init
	InitializeSound(hWnd);

	
	//-----------------------------------------------
	// DirectMusic für Midi-Files
	if (FAILED(CoInitialize(NULL)))
	{
		MUSIC_OK=false;
	} 
	//Create the performance
	if (MUSIC_OK) {
		if (FAILED(CoCreateInstance (
						CLSID_DirectMusicPerformance,NULL,CLSCTX_INPROC,
						IID_IDirectMusicPerformance2,(void **)&pPerf
			)))
		{
			MUSIC_OK=false;
		}
	}
	if (MUSIC_OK) {
		pPerf->Init(NULL,NULL,NULL);
		if (pPerf==NULL) MUSIC_OK=false;
		if (FAILED(pPerf->AddPort(NULL))) MUSIC_OK=false;
	}
	
	
	//Create Loader & load MIDI file
	if (MUSIC_OK) {
		if (FAILED(CoCreateInstance(
							CLSID_DirectMusicLoader,NULL,CLSCTX_INPROC,
							IID_IDirectMusicLoader,(void **)&pLoader
			)))
		{
			MUSIC_OK=false;
		}
	}

	pSegment=NULL;
*/
	// Level laden  (levels.dat);
	loadLevels();

	// Spielfeld
	initSpielfeld();
	blitSpielfeld();
		
    return 0;
}




//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: Initialization, message loop
//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
//    MSG                         msg;
	
	assets=snsbbfzOpen("assets.bin");
	videoInit();
	soundInit();
	InitializeSound();
	tileSurface = videoLoadTexture(assets, 1);
	background = videoLoadTexture(assets, 2);
	skullimage = videoLoadTexture(assets, 3);
	frametime = SDL_GetTicks();
	if(InitApp() != 0)
		return FALSE;

	while(1) {
		/*      if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
		      {
			  if( !GetMessage( &msg, NULL, 0, 0 ) )
			  {
			      return msg.wParam;
			  }
			  else {
			      TranslateMessage(&msg);
			      DispatchMessage(&msg);
			  }
		      }
		      else if ( TRUE )
		*/
          UpdateFrame();
	  /*    
	      else
	      {
		  WaitMessage();
	      }*/
	}

}

