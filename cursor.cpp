#include "cursor.hpp"

Cursor::Cursor() {}

Cursor::Cursor(SDL_Renderer* sdl_Renderer) {
    m_renderer = sdl_Renderer;
    m_texture = load_Texture(CURSOR_SPRITE_PATH);
}

Cursor::~Cursor() {}

void Cursor::blit_Texture(int x_pos, int y_pos) {
    SDL_Rect destination;
    destination.x = x_pos;
    destination.y = y_pos;

    if (SDL_QueryTexture(m_texture, NULL, NULL, &destination.w, &destination.h) < 0) {
        printf("Failed to query texture of entity: %s", SDL_GetError());
        std::cout << "Texture is: " << m_texture << std::endl;
    }

    if (SDL_RenderCopy(m_renderer, m_texture, NULL, &destination) < 0) {
        printf("Failed to render copy of entity: %s", SDL_GetError());
    }

}

SDL_Texture* Cursor::load_Texture(std::string filename) {
    SDL_Texture* texture;
    std::cout << "Loading cursor texture" << std::endl;
    texture = IMG_LoadTexture(m_renderer, CURSOR_SPRITE_PATH);
    return texture;
}

int Cursor::get_x_Pos() {
    return m_x_pos;
}

int Cursor::get_y_Pos() {
    return m_y_pos;
}

void Cursor::set_x_Pos(int x_pos) {
    m_x_pos = x_pos;
}

void Cursor::set_y_Pos(int y_pos) {
    m_y_pos = y_pos;
}