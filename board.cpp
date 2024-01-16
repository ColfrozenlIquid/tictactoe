#include "board.hpp"

Board::Board() {}

Board::Board(SDL_Renderer* sdl_renderer) {
    m_renderer = sdl_renderer;
    generate_Random_Sprite_Array();
}

Board::~Board() {}

Field Board::get_Field(int index) {
    return m_fields[index];
}

void Board::set_Board_State(int state, int i, int j) {
    m_board_state[i][j] = state;
}

auto Board::get_Board_State_Array() {
    return m_board_state;
}

void Board::generate_Random_Sprite_Array() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        m_sprite_index_array[i] = get_Random_Int_Range(0, SPRITE_COUNT-1);
    }
}

std::vector<Cross*> Board::get_Cross_Vector() {
    return m_cross_vector;
}

std::vector<Nought*> Board::get_Nought_Vector() {
    return m_nought_vector;
}

void Board::print_Board() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            std::cout << m_board_state[i][j] << ", ";
        }
        std::cout << std::endl;
    }
}

void Board::generate_Cross(int x_pos, int y_pos) {
    Cross* cross = new Cross(m_renderer);
    std::cout << "New cross m_renderer address is: " << m_renderer << std::endl;
    cross->set_x_Pos(x_pos);
    cross->set_y_Pos(y_pos);
    m_cross_vector.push_back(cross);
}

void Board::generate_Nought(int x_pos, int y_pos) {
    Nought* nought = new Nought(m_renderer);
    std::cout << "New nought m_renderer address is: " << m_renderer << std::endl;
    nought->set_x_Pos(x_pos);
    nought->set_y_Pos(y_pos);
    m_nought_vector.push_back(nought);
}

void Board::print_Cross_Vector_Size() {
    std::cout << "Cross vector size is: " << m_cross_vector.size() << std::endl;
}

int Board::get_Board_State(int i, int j) {
    return m_board_state[i][j];
}


int Board::get_Random_Int_Range(int a, int b) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(a, b);
    int random_number = distribution(generator);
    return random_number;
}

int Board::get_Field_Width(){
    return m_field_width;
}

int Board::get_Field_Height() {
    return m_field_height;
}
