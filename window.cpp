// window.cpp, modified by Chris Smeele to use SDL as a graphics
// backend for portability.

#include "window.hpp"
#include <iostream>
#include <stdexcept>

static const int COLOR_BG[3] = { 0x00, 0x00, 0x00 };
static const int COLOR_FG[3] = { 0xff, 0xff, 0xff };

window::window(int x_size, int y_size, int scale):
    x_size(x_size), y_size(y_size), scale(scale), pixels(y_size) {

    // Initialize pixel grid.
    for (auto &row : pixels)
        row.resize(x_size, false);

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error(std::string("SDL Init error: ") + SDL_GetError());

    sdl_win = SDL_CreateWindow(
        "LCD Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        x_size * scale,
        y_size * scale,
        SDL_WINDOW_SHOWN
    );

    if (!sdl_win)
        throw std::runtime_error(std::string("SDL CreateWindow error: ") + SDL_GetError());

    sdl_renderer = SDL_CreateRenderer(
        sdl_win,
        -1,
        0 // Renderer flags. With 0 SDL should use acceleration when
          // available and fall back to software rendering otherwise.
    );

    if (!sdl_renderer)
        throw std::runtime_error(std::string("SDL_CreateRenderer error: ") + SDL_GetError());
}

static void put_pixel(SDL_Renderer *r, int x, int y, int scale){
    SDL_Rect rect = {
        x * scale,
        y * scale,
        scale, // Width.
        scale  // Height.
    };
    if (scale >= 5) {
        rect.w--; // Provide a bit of pixel spacing for large scales.
        rect.h--;
    }
    SDL_RenderFillRect(r, &rect);
}

void window::clear(){
    for (auto &row : pixels)
        row.assign(x_size, false);
}

void window::draw(int x, int y){
    if ((size_t)y < pixels.size() && (size_t)x < pixels[y].size())
        pixels[y][x] = true;
}

void window::redraw() {
    // Clear the buffer.
    SDL_SetRenderDrawColor(sdl_renderer, COLOR_BG[0], COLOR_BG[1], COLOR_BG[2], 255);
    SDL_RenderClear(sdl_renderer);
    SDL_SetRenderDrawColor(sdl_renderer, COLOR_FG[0], COLOR_FG[1], COLOR_FG[2], 255);

    // Draw the pixel grid.
    int y = 0;
    for (auto row : pixels) {
        int x = 0;
        for (bool cell : row) {
            if (cell)
                put_pixel(sdl_renderer, x, y, scale);
            x++;
        }
        y++;
    }

    // Flip.
    SDL_RenderPresent(sdl_renderer);
}

void window::mainloop() {
        SDL_Event e;
        while (SDL_PollEvent (&e)) {
            if (
                    e.type == SDL_QUIT
                || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
            ) {
                SDL_Quit();
                return;
            }
        }

        redraw();

        // Aim for slightly less than 60 frames per second.
        SDL_Delay(1000 / 60);
}
