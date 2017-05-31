#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <android/log.h>
#include <android/native_activity.h>

#define MY_LOG_TAG "main.c"
#define MY_LOG_LEVEL_VERBOSE 1
#define MY_LOG_LEVEL_DEBUG 2
#define MY_LOG_LEVEL_INFO 3
#define MY_LOG_LEVEL_WARNING 4
#define MY_LOG_LEVEL_ERROR 5
#define MY_LOG_LEVEL_FATAL 6
#define MY_LOG_LEVEL_SILENT 7

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, MY_LOG_TAG, __VA_ARGS__)

#define RENDERER_WIDTH 320
#define RENDERER_HEIGHT 240

#include "SDL.h"


typedef struct Sprite
{
	SDL_Texture* texture;
	Uint16 w;
	Uint16 h;
} Sprite;

/* Adapted from SDL's testspriteminimal.c */
Sprite LoadSprite(const char* file, SDL_Renderer* renderer)
{
	Sprite result;
	result.texture = NULL;
	result.w = 0;
	result.h = 0;

    SDL_Surface* temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(file);
    if (temp == NULL)
	{
        fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
        return result;
    }
    result.w = temp->w;
    result.h = temp->h;

    /* Create texture from the image */
    result.texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!result.texture) {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return result;
    }
    SDL_FreeSurface(temp);

    return result;
}

void drawImage(SDL_Window* window, SDL_Renderer* renderer, const Sprite sprite)
{
	Uint8 done = 0;
	SDL_Event event;
	while(!done)
	{
			/* Check for events */
			while(SDL_PollEvent(&event))
			{
					if( event.type == SDL_QUIT ||
							event.type == SDL_KEYDOWN ||
							event.type == SDL_FINGERDOWN )
					{
							done = 1;
					}
			}

			/* Draw a gray background */
			SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
			SDL_RenderClear(renderer);

			int w, h;
			SDL_GetWindowSize(window, &w, &h);
			SDL_Rect destRect = {w/2 - sprite.w/2, h/2 - sprite.h/2, sprite.w, sprite.h};
			/* Blit the sprite onto the screen */
			SDL_RenderCopy(renderer, sprite.texture, NULL, &destRect);

			/* Update the screen! */
			SDL_RenderPresent(renderer);
			SDL_Delay(10);
	}
}

void drawCircle(SDL_Renderer* renderer, int x_center, int y_center, int r) {
	Uint8 done = 0;
	SDL_Event event;
	while(!done)
	{
			/* Check for events */
			while(SDL_PollEvent(&event))
			{
					if( event.type == SDL_QUIT ||
							event.type == SDL_KEYDOWN ||
							event.type == SDL_FINGERDOWN )
					{
							done = 1;
					}
			}

			/* Draw a gray background */
			SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
			SDL_RenderClear(renderer);

			int x = 0;
		  int y = r;
		  int m = 5 - (4 * r);

			// Draw a grey background
			SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
			SDL_RenderClear(renderer);

			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
			while (x <= y) {
					SDL_RenderDrawPoint(renderer, x_center + x, y_center + y);
					SDL_RenderDrawPoint(renderer, x_center + y, y_center + x);
					SDL_RenderDrawPoint(renderer, x_center - y, y_center + x);
					SDL_RenderDrawPoint(renderer, x_center - x, y_center + y);
					SDL_RenderDrawPoint(renderer, x_center - x, y_center - y);
					SDL_RenderDrawPoint(renderer, x_center - y, y_center - x);
					SDL_RenderDrawPoint(renderer, x_center + y, y_center - x);
					SDL_RenderDrawPoint(renderer, x_center + x, y_center - y);

					if (m > 0) {
						y--;
						m -= 8 * y;
					}
					x++;
					m += (8 * x) + 4;
			}

			/* Update the screen! */
			SDL_RenderPresent(renderer);
			SDL_Delay(10);
	}
}

void drawChessboard(SDL_Renderer* renderer) {
	Uint8 done = 0;
	SDL_Event event;
	while(!done)
	{
			/* Check for events */
			while(SDL_PollEvent(&event))
			{
					if( event.type == SDL_QUIT ||
							event.type == SDL_KEYDOWN ||
							event.type == SDL_FINGERDOWN )
					{
							done = 1;
					}
			}

			/* Draw a gray background */
			SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
			SDL_RenderClear(renderer);

			int row = 0;
			int column = 0;
			int x = 0;

			SDL_Rect rectangle;
			SDL_Rect drawArea;

			// Get the size of the drawing surface.
			SDL_RenderGetViewport(renderer, &drawArea);

			int rowMax = 8;
			for (; row < rowMax; ++row) {
				column = row % 2;
				x = column;
				for (; column < 4 + (row % 2); ++column) {
					SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
					rectangle.w = drawArea.w / rowMax;
					rectangle.h = drawArea.h / rowMax;
					rectangle.x = x * rectangle.w;
					rectangle.y = row * rectangle.h;
					x += 2;
					SDL_RenderFillRect(renderer, &rectangle);

					SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
					SDL_RenderDrawRect(renderer, &rectangle);
				}
			}

			/* Update the screen! */
			SDL_RenderPresent(renderer);
			SDL_Delay(10);
	}
}

void drawMovingSquare(SDL_Renderer* renderer, int dimen) {
	Uint8 done = 0, moved = 0;
	SDL_Event event;

	SDL_Rect square;
	square.x = RENDERER_WIDTH / 2;
	square.y = RENDERER_HEIGHT / 2;
	square.w = dimen;
	square.h = dimen;

	// Draw a grey background
	SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
  SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &square);
	SDL_RenderPresent(renderer);

	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_FINGERMOTION) {
				moved = 1;
			}
		}

		if (moved) {
			square.x = event.tfinger.x * (float) RENDERER_WIDTH;
			square.y = event.tfinger.y * (float) RENDERER_HEIGHT;
			SDL_RenderFillRect(renderer, &square);
			SDL_RenderPresent(renderer);
			SDL_Delay(10);
			moved = 0;
		}
	}
}

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;

	if(SDL_CreateWindowAndRenderer(RENDERER_WIDTH, RENDERER_HEIGHT, 0, &window, &renderer) < 0)
	    exit(2);

	Sprite sprite = LoadSprite("image.bmp", renderer);
	if(sprite.texture == NULL) {
		exit(2);
	}

	// Draw an image
	//drawImage(window, renderer, sprite);

	// Draw a circle.
	//drawCircle(renderer, RENDERER_WIDTH / 2, RENDERER_HEIGHT / 2, 50);

	// Draw a chessboard.
	//drawChessboard(renderer);

	// Draw a moving square.
	drawMovingSquare(renderer, 10);

	exit(0);
}
