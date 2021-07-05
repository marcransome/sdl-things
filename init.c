/* MIT License

  Copyright (c) 2021 Marc Ransome

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE. */

#include <stdlib.h>
#include <SDL2/SDL.h>

#include "init.h"
#include "types.h"

extern game g;

static SDL_Window * create_window(void);
static SDL_Renderer * create_renderer(void);

void
initialise(void) {
    memset(&g, 0, sizeof(g));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failed to initialise: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if ((g.window = create_window()) == NULL) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if ((g.renderer = create_renderer()) == NULL) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

void
cleanup(void) {
    SDL_Quit();
}

static SDL_Window *
create_window(void) {
    return SDL_CreateWindow("Game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0);
}

static SDL_Renderer *
create_renderer(void) {
    return SDL_CreateRenderer(g.window, 1, SDL_RENDERER_ACCELERATED);
}
