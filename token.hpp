#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <random>

#define CROSS_SPRITE_PATH "./sprites/cross_"
#define NOUGHT_SPRITE_PATH "./sprites/nought_"

#define CROSS_SPRITE_COUNT 4
#define NOUGHT_SPRITE_COUNT 4

class Token {
    public:
        Token();
        Token(SDL_Renderer* sdl_Renderer);
        ~Token();

        int get_x_Pos();
        int get_y_Pos();

        void set_x_Pos(int x_pos);
        void set_y_Pos(int y_pos);

    protected:
        SDL_Texture* m_texture;
        int m_x_pos;
        int m_y_pos;

        int get_Random_Int_Range(int a, int b);
    
    private:
};