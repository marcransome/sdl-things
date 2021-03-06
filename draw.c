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
#include <SDL2/SDL_image.h>

#include "draw.h"
#include "types.h"
#include "entity.h"

extern game g;

void
prepare_scene(void) {
    SDL_SetRenderDrawColor(g.renderer, 77, 165, 255, 255);
    SDL_RenderClear(g.renderer);
}

void
present_scene(void) {
    SDL_RenderPresent(g.renderer);
}

SDL_Texture *
load_texture(char *filename) {
    SDL_Texture *texture;

    if ((texture = IMG_LoadTexture(g.renderer, filename)) == NULL) {
        fprintf(stderr, "Unable to load texture: %s", filename);
        exit(EXIT_FAILURE);
    }

    return texture;
}

void
draw_entity(entity *e) {
    SDL_Rect target;
    target.x = e->x;
    target.y = e->y;

    if (SDL_QueryTexture(e->texture, NULL, NULL, &target.w, &target.h) < 0) {
        fprintf(stderr, "Unable to query texture: %s", SDL_GetError());
    }

    if (SDL_RenderCopy(g.renderer, e->texture, NULL, &target) > 0) {
        fprintf(stderr, "Unable to copy texture: %s", SDL_GetError());
    }
}
