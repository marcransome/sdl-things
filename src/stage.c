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

#include <SDL2/SDL.h>

#include "stage.h"

Stage *
stage_new(void *instance, StageInterface *interface) {
    SDL_assert(instance != NULL);
    SDL_assert(interface != NULL);
    SDL_assert(interface->init != NULL);
    SDL_assert(interface->destroy != NULL);
    SDL_assert(interface->perform_logic != NULL);
    SDL_assert(interface->render_scene != NULL);

    Stage *stage = (Stage *)calloc(1, sizeof(Stage));
    stage->instance = instance;
    stage->interface = interface;
    return stage;
}

void
stage_init(Stage *stage) {
    SDL_assert(stage != NULL);

    stage->interface->init(stage->instance);
}

void
stage_destroy(Stage *stage) {
    SDL_assert(stage != NULL);

    stage->interface->destroy(stage->instance);
}

void
stage_perform_logic(Stage *stage) {
    SDL_assert(stage != NULL);

    stage->interface->perform_logic(stage->instance);
}

void
stage_render_scene(Stage *stage) {
    SDL_assert(stage != NULL);

    stage->interface->render_scene(stage->instance);
}
