#pragma once
#include "token.hpp"

class Cross : public Token {
    public:
        Cross();
        Cross(SDL_Renderer* sdl_renderer);
        ~Cross();

        void blit_Texture();

        int get_x_Pos();
        int get_y_Pos();

    private:
        SDL_Texture* load_Texture(int index);
        int m_sprite_index;
        SDL_Renderer* m_renderer;
};