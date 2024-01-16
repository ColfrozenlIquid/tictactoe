#include "token.hpp"

Token::Token() {}

Token::Token(SDL_Renderer* sdl_Renderer) {
    // m_renderer = sdl_Renderer;
}

Token::~Token(){}

int Token::get_Random_Int_Range(int a, int b) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(a, b);
    int random_number = distribution(generator);
    return random_number;
}

int Token::get_x_Pos() {
    return m_x_pos;
}

int Token::get_y_Pos() {
    return m_y_pos;
}

void Token::set_x_Pos(int x_pos) {
    m_x_pos = x_pos;
}

void Token::set_y_Pos(int y_pos) {
    m_y_pos = y_pos;
}