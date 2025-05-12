
#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
}

void cleanupSDL() {
    TTF_Quit();
    SDL_Quit();
}

void handleEvents(int *sui, int *running, Character *character, Character2 *character2, Ball *ball, GameSpeed *speed) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) *running = 0;
        else if (event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_LEFT: character->moveLeft = 1; break;
                case SDLK_RIGHT: character->moveRight = 1; break;
                case SDLK_s: character->att1 = 1; break;
                case SDLK_d: character->att2 = 1; break;
                case SDLK_UP: character->moveUp = 1; break;
                case SDLK_j: character2->moveLefte = 1; break;
                case SDLK_k: character2->moveRighte = 1; break;
                case SDLK_t: character2->att1e = 1; break;
                case SDLK_y: character2->att2e = 1; break;
                case SDLK_o: character2->moveUpe = 1; break;
                case SDLK_x: 
                    if (!ball->active) {
                        ball->active = 1;
                        ball->position.x = character->position.x + character->position.w;
                        ball->position.y = character->position.y + character->position.h/2;
                    }
               case SDLK_p: *sui = 1; break;
               case SDLK_m: 
                    if (!ball->active) {
                        ball->active = 1;
                        ball->position.x = character2->positione.x + character2->positione.w;
                        ball->position.y = character2->positione.y + character2->positione.h/2;
                    }
                    break;
                case SDLK_PLUS: case SDLK_KP_PLUS:  
                    speed->characterSpeed = (speed->characterSpeed < 25) ? speed->characterSpeed + 2 : 25;
                    speed->character2Speed = (speed->character2Speed < 25) ? speed->character2Speed + 2 : 25; 
                    break;
                case SDLK_MINUS: case SDLK_KP_MINUS: 
                    speed->characterSpeed = (speed->characterSpeed > 1) ? speed->characterSpeed - 1 : 1; 
                    speed->character2Speed = (speed->character2Speed > 1) ? speed->character2Speed - 1 : 1; 
                    break;
                case SDLK_0: case SDLK_KP0: 
                    speed->characterSpeed = 5;
                    speed->character2Speed = 5;
                     
                    break;
            }
        }
        else if (event.type == SDL_KEYUP) {
            switch(event.key.keysym.sym) {
                case SDLK_LEFT: character->moveLeft = 0; break;
                case SDLK_RIGHT: character->moveRight = 0; break;
                case SDLK_UP: character->moveUp = 0; break;
                case SDLK_s: character->att1 = 0; break;
                case SDLK_d: character->att2 = 0; break;
                case SDLK_j: character2->moveLefte = 0; break;
                case SDLK_k: character2->moveRighte = 0; break;
                case SDLK_o: character2->moveUpe = 0; break;
                case SDLK_t: character2->att1e = 0; break;
                case SDLK_y: character2->att2e = 0; break;
                

            }
        }
    }
}

void updateCharacter(Character *character, moves *c, int characterSpeed) {
    if (character->moveLeft) {
        character->position.x -= characterSpeed;
        if (character->position.x < 0) character->position.x = 0;
    }
    if (character->moveRight) {
        character->position.x += characterSpeed;
        if (character->position.x + character->position.w > 1400) {
            character->position.x = 1400 - character->position.w;
        }
    }

    if (character->moveUp && character->onGround) {
        character->velocityY = -25;
        character->onGround = 0;
    }
    character->velocityY += 1;
    character->position.y += character->velocityY;

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime > character->lastFrameTime + 100) {
        character->currentFrame = (character->currentFrame + 1) % 5;
        character->lastFrameTime = currentTime;
    }

    if (character->moveRight) {
        switch(character->currentFrame) {
            case 0: character->image = c->sprint1; break;
            case 1: character->image = c->sprint2; break;
            case 2: character->image = c->sprint3; break;
            case 3: character->image = c->sprint4; break;
            case 4: character->image = c->sprint5; break;
        }
    }
    else if (character->moveLeft) {
        switch(character->currentFrame) {
            case 0: character->image = c->sprint1_left; break;
            case 1: character->image = c->sprint2_left; break;
            case 2: character->image = c->sprint3_left; break;
            case 3: character->image = c->sprint4_left; break;
            case 4: character->image = c->sprint5_left; break;
        }}
        else if (character->att1) {
        switch(character->currentFrame) {
            case 0: character->image = c->attack11; break;
            case 1: character->image = c->attack12; break;
            case 2: character->image = c->attack13; break;
            case 3: character->image = c->attack14; break;
            
        }
    }
        else if (character->att2) {
        switch(character->currentFrame) {
            case 0: character->image = c->attack21; break;
            case 1: character->image = c->attack22; break;
            case 2: character->image = c->attack23; break;
           
            
        }
    }
    else {
        character->image = c->standing;
    }

    if (character->position.y >= 400) {
        character->position.y = 400;
        character->velocityY = 0;
        character->onGround = 1;
    }
}

void updateBall(Ball *ball) {
    if (ball->active) {
        ball->position.x += ball->velocityX;
        if (ball->position.x > 1536) {
            ball->active = 0;
        }
    }
}

void updateCharacter2(Character2 *character2, movese *e, int character2Speed, int *sui, SDL_Surface *screen) {
    SDL_BlitSurface(character2->imagee, NULL, screen, &character2->positione);

    if (character2->moveLefte) {
        character2->positione.x -= character2Speed;
        if (character2->positione.x < 0) character2->positione.x = 0;
    }
    if (character2->moveRighte) {
        character2->positione.x += character2Speed;
        if (character2->positione.x + character2->positione.w > 1536) {
            character2->positione.x = 1536 - character2->positione.w;
        }
    }

    if (character2->moveUpe && character2->onGrounde) {
        character2->velocityYe = -25;
        character2->onGrounde = 0;
    }
    character2->velocityYe += 1;
    character2->positione.y += character2->velocityYe;

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime > character2->lastFrameTime + 100) {
        character2->currentFramee = (character2->currentFramee + 1) % 5;
        character2->lastFrameTime = currentTime;
    }

    if (character2->moveRighte) {
        switch(character2->currentFramee) {
            case 0: character2->imagee = e->sprint1e; break;
            case 1: character2->imagee = e->sprint2e; break;
            case 2: character2->imagee = e->sprint3e; break;
            case 3: character2->imagee = e->sprint4e; break;
            case 4: character2->imagee = e->sprint5e; break;
        }
    }
    else if (character2->moveLefte) {
        switch(character2->currentFramee) {
            case 0: character2->imagee = e->sprint1_lefte; break;
            case 1: character2->imagee = e->sprint2_lefte; break;
            case 2: character2->imagee = e->sprint3_lefte; break;
            case 3: character2->imagee = e->sprint4_lefte; break;
            case 4: character2->imagee = e->sprint5_lefte; break;
        }}
        else if (character2->att1e) {
        switch(character2->currentFramee) {
            case 0: character2->imagee = e->attack11e; break;
            case 1: character2->imagee = e->attack12e; break;
            case 2: character2->imagee = e->attack13e; break;
            case 3: character2->imagee = e->attack14e; break;
            
        }
    }
        else if (character2->att2e) {
        switch(character2->currentFramee) {
            case 0: character2->imagee = e->attack21e; break;
            case 1: character2->imagee = e->attack22e; break;
            
            
        }
    }
    else {
           character2->imagee = e->standinge;
    }

    if (character2->positione.y >= 800) {
        character2->positione.y = 800;
        character2->velocityYe = 0;
        character2->onGrounde = 1;
    }
}
  


void renderHUD(SDL_Surface *screen, Character *character,Character2 *character2,GameState *gameState, TTF_Font *font) {
    SDL_Color white = {255, 255, 255};
    char healthText[32], timeText[32], healtheText[32];
    
    sprintf(healthText, "Health: %d", character->health);
    sprintf(timeText, "Score: %d", gameState->gameTime);
    sprintf(healtheText, "Healthe: %d", character2->healthe);

    SDL_Surface *healthSurface = TTF_RenderText_Solid(font, healthText, white);
    SDL_Surface *timeSurface = TTF_RenderText_Solid(font, timeText, white);
    SDL_Surface *healtheSurface = TTF_RenderText_Solid(font, healtheText, white);

    SDL_Rect healthPos = {10, 10, 0, 0};
    SDL_Rect timePos = {10, 70, 0, 0};
    SDL_Rect healthePos = {10, 40, 0, 0};

    SDL_BlitSurface(healthSurface, NULL, screen, &healthPos);
    SDL_BlitSurface(timeSurface, NULL, screen, &timePos);
    SDL_BlitSurface(healtheSurface, NULL, screen, &healthePos);
    
    SDL_FreeSurface(healthSurface);
    SDL_FreeSurface(timeSurface);
    SDL_FreeSurface(healtheSurface);
}

void render(SDL_Surface *screen, SDL_Surface *background, Character *character,Character2 *character2,  
           Ball *ball, int *backgroundX, 
           GameState *gameState, TTF_Font *font, GameAssets *assets) {
    // Clear screen
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    
    
    
    
    SDL_Rect srcRect = { *backgroundX, 0, 1536, 1024 };
    SDL_Rect destRect = { 0, 0, 1536, 1024 };
    SDL_BlitSurface(background, &srcRect, screen, &destRect);
    // Render objects
    if (ball->active) SDL_BlitSurface(ball->image, NULL, screen, &ball->position);
    
    SDL_BlitSurface(character->image, NULL, screen, &character->position);
    SDL_BlitSurface(character2->imagee, NULL, screen, &character2->positione);
    
    // HUD
    renderHUD(screen, character,character2, gameState, font);
    
    SDL_Flip(screen);
}
////////////////////////////////////////////////




int afficherMenuSelectionPersonnage(SDL_Surface *screen, Interface *Interface)
{
    
    int SelectionBouton1 = 0, SelectionBouton2 = 0, continuer2 = 1;
    int choixMode = 0;
    SDL_Rect positionimgmenup;
    SDL_Event event;

    // Set image positions
    positionimgmenup.x = 100;
    positionimgmenup.y = 100;

    Interface->BoutonSingleplayer = IMG_Load("p1.png");
    Interface->BoutonMultiplayer = IMG_Load("p2.png");

    // Set button positions
    Interface->pBoutonSingleplayer.x = 500;
    Interface->pBoutonSingleplayer.y = 500;
    Interface->pBoutonMultiplayer.x = 900;
    Interface->pBoutonMultiplayer.y = 500;

    while (continuer2) {
        // Clear the screen
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

        // Draw menu elements
        SDL_BlitSurface(Interface->SelectionMode, NULL, screen, &positionimgmenup);
        SDL_BlitSurface(Interface->BoutonSingleplayer, NULL, screen, &Interface->pBoutonSingleplayer);
        SDL_BlitSurface(Interface->BoutonMultiplayer, NULL, screen, &Interface->pBoutonMultiplayer);

        SDL_Flip(screen);  // Refresh screen in SDL

        // Listen for events
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            return 0; // Exit game
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x;
            int y = event.button.y;

            // Check if click is inside Singleplayer button
            if (x >= 500 && x <= 650 && y >= 500 && y <= 600) {  
                choixMode = 1;  // Singleplayer selected
                continuer2 = 0; // Exit loop
            }
            // Check if click is inside Multiplayer button
            else if (x >= 900 && x <= 1050 && y >= 500 && y <= 600) {  
                choixMode = 2;  // Multiplayer selected
		return 3;
                continuer2 = 0; // Exit loop
            }
        }
    }
    

	 
   


    if (choixMode==1){
    Interface->posBoutonChoose[0].x=500;
    Interface->posBoutonChoose[0].y=750;
    Interface->posBoutonChoose[1].x=Interface->posBoutonChoose[0].x+450;
    Interface->posBoutonChoose[1].y=Interface->posBoutonChoose[0].y;



    
   
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    
    SDL_BlitSurface(Interface->SelectionPersonnage, NULL, screen, &positionimgmenup);
    SDL_BlitSurface(Interface->BoutonChoose[SelectionBouton1], NULL, screen, &Interface->posBoutonChoose[0]);
    SDL_BlitSurface(Interface->BoutonChoose[SelectionBouton2], NULL, screen, &Interface->posBoutonChoose[1]);


    

    
    SDL_Flip(screen);

    SDL_Event event;
    int continuer = 1;
    int choixPersonnage = 0;
   while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
            if ((event.button.x >= Interface->posBoutonChoose[0].x) &&
                        (event.button.x < Interface->posBoutonChoose[0].x + Interface->BoutonChoose[0]->w) &&
                        (event.button.y >= Interface->posBoutonChoose[0].y) &&
                        (event.button.y < Interface->posBoutonChoose[0].y + Interface->BoutonChoose[0]->h))
                        {
                            choixPersonnage=1;
                            continuer=0;
                        }
                        if ((event.button.x >= Interface->posBoutonChoose[1].x) &&
                        (event.button.x < Interface->posBoutonChoose[1].x + Interface->BoutonChoose[0]->w) &&
                        (event.button.y >= Interface->posBoutonChoose[1].y) &&
                        (event.button.y < Interface->posBoutonChoose[1].y + Interface->BoutonChoose[0]->h))
                        {
                            choixPersonnage=2;
                            continuer=0;
                        }
            break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_u: //choix perso 1
                        choixPersonnage = 1;
                        continuer=0;
                        break;
                    case SDLK_t: // choix 2 charctr
                        choixPersonnage = 2;
			 continuer=0;
                        
                        break;
                }
                break;
        }
    }
	return choixPersonnage;
    }
    SDL_FreeSurface(Interface->SelectionPersonnage);
}

int chargerInterface(Interface *Interface)
{
   
    Interface->SelectionPersonnage=IMG_Load("Player Select Interface.png");
    Interface->SelectionMode=IMG_Load("Gaia_Selection_2.png");
    Interface->BoutonChoose[0]=IMG_Load("Gaia_Choose_Button.png");
    Interface->BoutonChoose[1]=IMG_Load("Gaia_Choose_Button_2.png");
		
    

}

int testing_ad(SDL_Surface *screen){
    
	while (1) {
        // Clear the screen
        
	if (screen != NULL) printf("jaww");}
return 1;
}







