#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

#define CURSOR_SPRITE_PATH "./sprites/cursor_200.bmp"

class Cursor {
    public:
        Cursor();
        Cursor(SDL_Renderer* sdl_Renderer);
        ~Cursor();

        void blit_Texture(int x_pos, int y_pos);

        int get_x_Pos();
        int get_y_Pos();

        void set_x_Pos(int x_pos);
        void set_y_Pos(int y_pos);
    
    private:
        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;
        int m_x_pos;
        int m_y_pos;

        SDL_Texture* load_Texture(std::string filename);
};