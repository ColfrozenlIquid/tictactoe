#pragma once
#include <vector>
#include <memory>
#include <array>
#include "cross.hpp"
#include "nought.hpp"
#include "defines.hpp"

#define BOARD_SIZE 9
#define ROWS 3
#define COLUMNS 3
#define FIELD_SIZE 64

typedef struct Field {
    int x_pos;
    int y_pos;
} Field;

class Board {
    public:
        Board();
        Board(SDL_Renderer* sdl_renderer);
        ~Board();

        Field get_Field(int index);
        int get_Field_Width();
        int get_Field_Height();
        int get_Board_State(int i, int j);

        void set_Board_State(int state, int i, int j);
        auto get_Board_State_Array();

        std::vector<Cross*> get_Cross_Vector();
        std::vector<Nought*> get_Nought_Vector();
        
        void generate_Cross(int x_pos, int y_pos);
        void generate_Nought(int x_pos, int y_pos);
        void print_Cross_Vector_Size();

        void print_Board();
        
    private:

        std::vector<Cross*> m_cross_vector;
        std::vector<Nought*> m_nought_vector;
        SDL_Renderer* m_renderer;

        int m_field_width = FIELD_SIZE;
        int m_field_height = FIELD_SIZE;
        int m_sprite_index_array[BOARD_SIZE];

        int m_board_state[ROWS][COLUMNS] = {
                {0,0,0}, 
                {0,0,0}, 
                {0,0,0}
            };
        
        //std::array<std::array<int, COLUMNS>, ROWS> m_board_state = {{0,0,0}, {0,0,0}, {0,0,0}};

        Field m_fields[BOARD_SIZE] = {
                {135, 344},
                {234, 340},
                {328, 341},
                {128, 456},
                {234, 451},
                {328, 450},
                {133, 563},
                {232, 563},
                {333, 555}
            };

        int get_Random_Int_Range(int a, int b);
        void generate_Random_Sprite_Array();
};