#include <SDL.h>
#include <stdio.h>
// "-I<DriveLetter>:\<MinGW_LIBRARIES>\include\SDL2 -L<DriveLetter>:\<MinGW_LIBRARIES>\lib"
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init();
bool loadMedia();
void close();

//Main loop flag
bool quit = false;

//Event handler
SDL_Event e;

int main( int argc, char* args[] ) {
	if (!init()){

	} else {
		if (!loadMedia()){
		} else {
            SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
			SDL_UpdateWindowSurface( gWindow );
		}
	}

	while( !quit ){
		while( SDL_PollEvent( &e ) != 0 ){
			//User requests quit
			if( e.type == SDL_QUIT ){
				quit = true;
			}
			
            SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
			SDL_UpdateWindowSurface( gWindow );
		}
	}

	close();

	return 0;
}

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    } else {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        } else {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

bool loadMedia(){
    //Loading success flag
    bool success = true;

    //Load splash image
    gHelloWorld = SDL_LoadBMP( "assets/game_test.bmp" );
    if( gHelloWorld == NULL ){
        printf( "Unable to load image %s! SDL Error: %s\n", "assets/game_test.bmp", SDL_GetError() );
        success = false;
    }

    return success;
}

void close(){
    //Deallocate surface
    SDL_FreeSurface( gHelloWorld );
    gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

