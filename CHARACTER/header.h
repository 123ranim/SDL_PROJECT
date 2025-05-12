
#ifndef HEADER_H
#define HEADER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

typedef struct {
    SDL_Surface *standing;
    SDL_Surface *sprint1;
    SDL_Surface *sprint2;
    SDL_Surface *sprint3;
    SDL_Surface *sprint4;
    SDL_Surface *sprint5;
    SDL_Surface *sprint1_left;
    SDL_Surface *sprint2_left;
    SDL_Surface *sprint3_left;
    SDL_Surface *sprint4_left;
    SDL_Surface *sprint5_left;
    SDL_Surface *attack11;
    SDL_Surface *attack12;
    SDL_Surface *attack13;
    SDL_Surface *attack14;
    SDL_Surface *attack21;
    SDL_Surface *attack22;
    SDL_Surface *attack23;
    SDL_Surface *attack24;
} moves;
typedef struct {
    SDL_Surface *standinge;
    SDL_Surface *sprint1e;
    SDL_Surface *sprint2e;
    SDL_Surface *sprint3e;
    SDL_Surface *sprint4e;
    SDL_Surface *sprint5e;
    SDL_Surface *sprint1_lefte;
    SDL_Surface *sprint2_lefte;
    SDL_Surface *sprint3_lefte;
    SDL_Surface *sprint4_lefte;
    SDL_Surface *sprint5_lefte;
    SDL_Surface *attack11e;
    SDL_Surface *attack12e;
    SDL_Surface *attack13e;
    SDL_Surface *attack14e;
    SDL_Surface *attack21e;
    SDL_Surface *attack22e;
    SDL_Surface *attack23e;
    SDL_Surface *attack24e;
} movese;
typedef struct {
    SDL_Surface *image;
    SDL_Rect position;
    int velocityY;
    int onGround;
    int moveLeft;
    int moveRight;
    int att1;
    int att2;
    int moveUp;
    int currentFrame;
    Uint32 lastFrameTime;
    int health;
    
} Character;

typedef struct {
    SDL_Surface *image;
    SDL_Rect position;
    int velocityX;
    int active;
    int test;
} Ball;

typedef struct {
    SDL_Surface *imagee;
    SDL_Rect positione;
    int velocityYe;
    int onGrounde;
    int moveLefte;
    int moveRighte;
    int att1e;
    int att2e;
    int moveUpe;
    int currentFramee;
    Uint32 lastFrameTime;
    int healthe;
    
} Character2;

typedef struct {
    Uint32 startTime;
    int gameTime;
    int gameOver;
} GameState;

typedef struct {
    int characterSpeed;
    int character2Speed;
    
} GameSpeed;

typedef struct {
    // Placeholder for game assets
} GameAssets;
typedef struct
{
    SDL_Surface *Background, *SelectionPersonnage, *SelectionMode, *BoutonChoose[2], *BoutonSingleplayer, *BoutonMultiplayer;
    SDL_Rect posBoutonChoose[2] ,pBoutonSingleplayer,pBoutonMultiplayer;

}Interface;

void initSDL();
void cleanupSDL();
void handleEvents(int *sui, int *running, Character *character, Character2 *character2, Ball *ball, GameSpeed *speed);
void updateCharacter(Character *character, moves *c, int characterSpeed);
void updateBall(Ball *ball);

void updateCharacter2(Character2 *character2, movese *e, int character2Speed,int *sui,SDL_Surface *screen);
void renderHUD(SDL_Surface *screen, Character *character, Character2 *character2,GameState *gameState, TTF_Font *font);
void render(SDL_Surface *screen, SDL_Surface *background, Character *character, Character2 *character2,
           Ball *ball,  int *backgroundX, 
           GameState *gameState, TTF_Font *font, GameAssets *assets);
int chargerInterface(Interface *Interface);
int afficherMenuSelectionPersonnage(SDL_Surface *screen, Interface *Interface);

//test de taha
int testing_taha(SDL_Surface *screen);

#endif
