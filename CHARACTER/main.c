#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>
#include "header.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

moves c;
movese e;
SDL_Surface *screen;

SDL_Surface* safe_load(const char* filename, int w, int h) {
    SDL_Surface* loaded = IMG_Load(filename);
    if (!loaded) {
        loaded = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0,0,0,0);
        SDL_FillRect(loaded, NULL, SDL_MapRGB(loaded->format, 255,0,255));
    }
    return loaded;
}

//////

int main() {
//////start new test

///////end new test




    int running = 1;
    int sui = 0;
    srand(time(NULL));
    ///////////
    Interface interface;
    chargerInterface(&interface);
    //int selected = afficherMenuSelectionPersonnage(screen, &interface);
    
    


	//printf("Selected character: %d\n", selected);
    //Initialize speeds
    GameSpeed speed = {
        .characterSpeed = 5,
        .character2Speed = 5
        
    };

    // Load assets
    c.standing = safe_load("character.png", 64, 64);
    c.sprint1 = safe_load("Run1.png", 64, 64);
    c.sprint2 = safe_load("Run2.png", 64, 64);
    c.sprint3 = safe_load("Run3.png", 64, 64);
    c.sprint4 = safe_load("Run4.png", 64, 64);
    c.sprint5 = safe_load("Run5.png", 64, 64);
    c.sprint1_left = safe_load("runl1.png", 64, 64);
    c.sprint2_left = safe_load("runl2.png", 64, 64);
    c.sprint3_left = safe_load("runl3.png", 64, 64);
    c.sprint4_left = safe_load("runl4.png", 64, 64);
    c.sprint5_left = safe_load("runl5.png", 64, 64);
    c.attack11 = safe_load("attack1.1.png", 64, 64);
    c.attack12 = safe_load("attack1.2.png", 64, 64);
    c.attack13 = safe_load("attack1.3.png", 64, 64);
    c.attack14 = safe_load("attack1.4.png", 64, 64);
    c.attack21 = safe_load("Attack_2.1.png", 64, 64);
    c.attack22 = safe_load("Attack_2.2.png", 64, 64);
    c.attack23 = safe_load("Attack_2.3.png", 64, 64);
    
    SDL_Surface *ballImage = safe_load("ball.png", 32, 32);
    
    SDL_Surface *background = safe_load("backround.png", 1536, 1024);
    
        e.standinge = safe_load("idle.png", 64, 64);
    e.sprint1e = safe_load("sprint1.png", 64, 64);
    e.sprint2e = safe_load("sprint2.png", 64, 64);
    e.sprint3e = safe_load("sprint3.png", 64, 64);
    e.sprint4e = safe_load("sprint4.png", 64, 64);
    e.sprint5e = safe_load("sprint1.png", 64, 64);
    e.sprint1_lefte = safe_load("sprintleft1.png", 64, 64);
    e.sprint2_lefte = safe_load("sprintl2.png", 64, 64);
    e.sprint3_lefte = safe_load("sprintl3.png", 64, 64);
    e.sprint4_lefte = safe_load("sprintl4.png", 64, 64);
    e.sprint5_lefte = safe_load("sprintleft1.png", 64, 64);
    e.attack11e = safe_load("att11.png", 64, 64);
    e.attack12e = safe_load("att12.png", 64, 64);
    e.attack13e = safe_load("att11.png", 64, 64);
    e.attack14e = safe_load("att12.png", 64, 64);
    e.attack21e = safe_load("att3.1.png", 64, 64);
    e.attack22e = safe_load("att3.2.png", 64, 64);
    
    
    GameAssets assets;
    initSDL();
    screen = SDL_SetVideoMode(1536, 1024, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
    TTF_Font *font = TTF_OpenFont("arial.ttf", 24);
    int selected = afficherMenuSelectionPersonnage(screen, &interface);
    // Initialize game objects
    Character character = {
        .image = c.standing,
        .position = {000, 000, 0, 0},
        .velocityY = 0,
        .onGround = 1,
        .moveLeft = 0,
        .moveRight = 0,
        .moveUp = 0,
        .att1 = 0,
        .att2 = 0,
        .currentFrame = 0,
        .lastFrameTime = 0,
        .health = 100
    };
     Character2 character2 = {
        .imagee = e.standinge,
        .positione = {400, 1500, 0, 0},
        .velocityYe = 0,
        .onGrounde = 1,
        .moveLefte = 0,
        .moveRighte = 0,
        .moveUpe = 0,
        .att1e = 0,
        .att2e = 0,
        .currentFramee = 0,
        .lastFrameTime = 0,
        .healthe = 100
    };
    
    character.position.w = character.image->w;
    character.position.h = character.image->h;
    character2.positione.w = character2.imagee->w;
    character2.positione.h = character2.imagee->h;
    Ball ball = {
        .image = ballImage,
        .position = {0, 0, ballImage->w, ballImage->h},
        .velocityX = 10,
        .active = 0
    };

    

    GameState gameState = {
        .startTime = SDL_GetTicks(),
        .gameTime = 0,
        .gameOver = 0
    };

    int backgroundX = 0;
    while (running && (character.health > 0|| character2.healthe >0)) {
        gameState.gameTime = (SDL_GetTicks() - gameState.startTime) / 1000;
        
        handleEvents(&sui, &running, &character, &character2, &ball, &speed);
        updateCharacter(&character, &c, speed.characterSpeed);
        updateBall(&ball);
        if(selected==3){ updateCharacter2(&character2, &e, speed.character2Speed,&sui,screen);}
        

        render(screen, background, &character, &character2, &ball, 
              &backgroundX, &gameState, font, &assets);
        
        SDL_Delay(16);
    }

    // Cleanup
    SDL_FreeSurface(background);
    SDL_FreeSurface(ballImage);
    TTF_CloseFont(font);
    cleanupSDL();
    return 0;
 }
