#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "application.hpp"
#include "cursor.hpp"
#include "cat.hpp"
#include "token.hpp"
#include "cross.hpp"
#include "nought.hpp"
#include "board.hpp"
#include "logic.hpp"

int main() {
    Application main_application;
    SDL_Renderer* main_renderer = main_application.m_renderer;
    Cursor cursor(main_renderer);
    Cat cat(main_renderer);

    int running = 1;
    
    while (running) {
        uint32_t animation_speed = SDL_GetTicks() / 175;
        int idx = animation_speed % CAT_ANIMATION_FRAMES;
        main_application.prepare_Scene();
        main_application.handle_Input();
        main_application.handle_Turn();
        cat.set_Animation_State(idx);
        main_application.blit_Texture(0, 0);
        main_application.draw_Tokens();
        cat.blit_Texture(cat.get_x_Pos(), cat.get_y_Pos());
        //nought1.blit_Texture(100, 100);
        //cross1.blit_Texture(200, 200);
        cursor.blit_Texture(main_application.get_Cursor_x_Pos(), main_application.get_Cursor_y_Pos());
        main_application.present_Scene();
        SDL_Delay(16);
        //SDL_Delay(1000);
    }
    return 0;
}