// example:
// declaration of a window class

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <vector>

class window {
    int x_size;
    int y_size;
    int scale;
   
    SDL_Window   *sdl_win;
    SDL_Renderer *sdl_renderer;

    std::vector< std::vector<bool> > pixels;
   
public:
    window(int x_size, int y_size, int scale);
    void draw(int x, int y);
    void clear();
    void redraw();
    void mainloop();
};

#endif // WINDOW_HPP
