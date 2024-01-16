#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "defines.hpp"

#define CAT_SPRITE_PATH "./sprites/cat_anim_400.bmp"

#define CAT_START_X_POS (SCREEN_WIDTH - 256 - 50)
#define CAT_START_Y_POS 80
#define CAT_ANIMATION_FRAMES 6
#define CAT_SPRITE_SIZE 256

class Cat {
    public:
        Cat();
        Cat(SDL_Renderer* sdl_renderer);
        ~Cat();
        void blit_Texture(int x_pos, int y_pos);
        void set_Animation_State(int state);

        int get_x_Pos();
        int get_y_Pos();

    private:
        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;
        int m_current_anim_state;
        int m_x_pos;
        int m_y_pos;

        SDL_Texture* load_Texture();
};