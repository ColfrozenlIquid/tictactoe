#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include "defines.hpp"
#include "cursor.hpp"
#include "board.hpp"
#include "logic.hpp"

#define MAIN_BACKGROUND_PATH "./sprites/board.bmp"

class Application {

    public:

        enum TURN {
            PLAYER,
            COMPUTER
        };

        Application();
        ~Application();

        void handle_Input();
        void handle_Turn();
        void prepare_Scene();
        void present_Scene();

        void draw_Cursor();
        void draw_Tokens();
        void draw_Crosses();
        void draw_Noughts();

        SDL_Renderer* get_SDL_Renderer();

        SDL_Renderer* m_renderer;
        SDL_Window* m_window;

        void blit_Texture(int x_pos, int y_pos);

        int get_Cursor_x_Pos();
        int get_Cursor_y_Pos();

    private:
        Board m_board;
        TURN m_current_turn;

        void check_Field_Click(int x_pos, int y_pos);

        int m_cursor_x_pos;
        int m_cursor_y_pos;

        SDL_Texture* m_texture;

        void init_SDL();
        void init_SDL_Image();
        void init_SDL_Fonts();
        SDL_Texture* load_Texture(std::string filename);

        void handle_Mouse_Input();
        void handle_Mouse_Button_Up(SDL_MouseButtonEvent* mouse_button_event);
        void handle_Mouse_Button_Down(SDL_MouseButtonEvent* mouse_button_event);
        void handle_Key_Up(SDL_KeyboardEvent* keyboard_event);
        void handle_Key_Down(SDL_KeyboardEvent* keyboard_event);
};