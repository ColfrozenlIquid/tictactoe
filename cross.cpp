#include "cross.hpp"

Cross::Cross() {}

Cross::Cross(SDL_Renderer* sdl_renderer) {
    m_renderer = sdl_renderer;
    m_sprite_index = get_Random_Int_Range(0, CROSS_SPRITE_COUNT-1);
    m_texture = load_Texture(m_sprite_index);
}

Cross::~Cross() {}

void Cross::blit_Texture() {
    SDL_Rect destination;
    destination.x = m_x_pos;
    destination.y = m_y_pos;

    if (SDL_QueryTexture(m_texture, NULL, NULL, &destination.w, &destination.h) < 0) {
        printf("Failed to query texture of entity: %s", SDL_GetError());
        std::cout << "Texture is: " << m_texture << std::endl;
    }

    if (SDL_RenderCopy(m_renderer, m_texture, NULL, &destination) < 0) {
        printf("Failed to render copy of entity: %s", SDL_GetError());
    }    
}

SDL_Texture* Cross::load_Texture(int index) {
    SDL_Texture* texture;
    std::string filepath = CROSS_SPRITE_PATH + std::to_string(index) + ".bmp";
    if ((texture = IMG_LoadTexture(m_renderer, filepath.c_str())) == NULL) {
        std::cout << SDL_GetError() << ::std::endl;
    }
    return texture;
}

int Cross::get_x_Pos() {
    return m_x_pos;
}

int Cross::get_y_Pos() {
    return m_y_pos;
}