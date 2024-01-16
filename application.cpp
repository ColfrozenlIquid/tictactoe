#include "application.hpp"

Application::Application() {
    init_SDL();
    init_SDL_Image();
    init_SDL_Fonts();
    m_texture = load_Texture(MAIN_BACKGROUND_PATH);
    std::cout << "Current main renderer address: " << m_renderer << std::endl;
    m_board = Board(m_renderer);
    m_current_turn = TURN::PLAYER;
    //m_cursor = Cursor(m_renderer);
}

Application::~Application() {}


void Application::draw_Cursor() {
    //m_cursor.blit_Texture(m_cursor.get_x_Pos(), m_cursor.get_y_Pos());
}

void Application::draw_Tokens() {
    draw_Crosses();
    draw_Noughts();
}

void Application::draw_Crosses() {
    for (auto cross : m_board.get_Cross_Vector()) {
        cross->blit_Texture();
    }
}

void Application::draw_Noughts() {
    for (auto nought : m_board.get_Nought_Vector()) {
        nought->blit_Texture();
    }
}

void Application::init_SDL_Image() {
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
        printf("Failed to initialise SDL_Image: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
}

void Application::init_SDL_Fonts() {
    if (TTF_Init() < 0) {
        printf("Failed to initialise SDL_Fonts: %s\n", SDL_GetError());
        TTF_Quit();
        exit(1);
    }
}

void Application::init_SDL() {
    int renderer_Flags = SDL_RENDERER_ACCELERATED;
    int window_Flags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialise. SDL Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    m_window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, window_Flags);

    if (!m_window) {
        printf("failed to open %d x %d SDL window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    m_renderer = SDL_CreateRenderer(m_window, -1, renderer_Flags);

    SDL_ShowCursor(SDL_DISABLE);

    if (!m_renderer) {
        printf("Failed to create SDL renderer: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
}

void Application::handle_Mouse_Input() {
    SDL_GetMouseState(&m_cursor_x_pos, &m_cursor_y_pos);
}

void Application::handle_Input() {
    SDL_Event event;
    
    handle_Mouse_Input();

    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                handle_Key_Down(&event.key);
                break;
            case SDL_KEYUP:
                handle_Key_Up(&event.key);
                break;
            case SDL_MOUSEBUTTONDOWN:
                handle_Mouse_Button_Down(&event.button);
                break;
            case SDL_MOUSEBUTTONUP:
                handle_Mouse_Button_Up(&event.button);
                break;
            default:
                break;
        }
    }
}

void Application::prepare_Scene() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void Application::present_Scene() {
    SDL_RenderPresent(m_renderer);
}

SDL_Texture* Application::load_Texture(std::string filename) {
    SDL_Texture* texture;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", filename.c_str());
    texture = IMG_LoadTexture(m_renderer, filename.c_str());
    return texture;
}

void Application::blit_Texture(int x_pos, int y_pos) {
    SDL_Rect destination;
    destination.x = x_pos;
    destination.y = y_pos;

    if (SDL_QueryTexture(m_texture, NULL, NULL, &destination.w, &destination.h) < 0) {
        printf("Failed to query texture: %s", SDL_GetError());
    }

    if (SDL_RenderCopy(m_renderer, m_texture, NULL, &destination) < 0) {
        printf("Failed to render copy: %s", SDL_GetError());
    }
}

SDL_Renderer* Application::get_SDL_Renderer() {
    return this->m_renderer;
}

void Application::check_Field_Click(int x_pos, int y_pos) {
    if (m_current_turn != TURN::PLAYER) {
        return;
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        int x_left = m_board.get_Field(i).x_pos;
        int y_top = m_board.get_Field(i).y_pos;
        int x_right = x_left + m_board.get_Field_Width();
        int y_bottom = y_top + m_board.get_Field_Height();
        if (x_left <= x_pos && x_pos <= x_right) {
            if (y_top <= y_pos && y_pos <= y_bottom) {
                std::cout << "Clicked on field number: " << i << std::endl;
                m_board.generate_Cross(m_board.get_Field(i).x_pos, m_board.get_Field(i).y_pos);
                m_board.set_Board_State(PLAYER_STATE, i/3, i%3);
                m_current_turn = TURN::COMPUTER;
            }
        }
    }
}

void Application::handle_Turn() {
    if (m_current_turn == TURN::PLAYER) {
        return;
    }
    if (m_current_turn == TURN::COMPUTER) {
        int current_arr[ROWS][COLUMNS];
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLUMNS; j++) {
                current_arr[i][j] = m_board.get_Board_State(i, j);
            }
        }
        Move bestmove1 = calculate_Best_Move(current_arr);
        std::cout << "Best move is: " << bestmove1.col << ", " << bestmove1.row << std::endl;
        m_board.generate_Nought(m_board.get_Field((bestmove1.row * ROWS) + bestmove1.col).x_pos, m_board.get_Field((bestmove1.row * ROWS) + bestmove1.col).y_pos);
        m_board.set_Board_State(OPPONENT_STATE, bestmove1.col, bestmove1.row);
        m_board.print_Board();
        m_current_turn = TURN::PLAYER;
    }
}

void Application::handle_Mouse_Button_Up(SDL_MouseButtonEvent* mouse_button_event) {

}

void Application::handle_Mouse_Button_Down(SDL_MouseButtonEvent* mouse_button_event) {
    if (mouse_button_event->button == SDL_BUTTON_LEFT) {
        std::cout << "Pressed left mouse button" << std::endl;
        std::cout << "Pressed at coordinate: (" << mouse_button_event->x << ", " << mouse_button_event->y << ")" << std::endl;
        check_Field_Click(mouse_button_event->x, mouse_button_event->y);
    }
    if (mouse_button_event->button == SDL_BUTTON_RIGHT) {
        std::cout << "Pressed right mouse button" << std::endl;
    }
}

void Application::handle_Key_Down(SDL_KeyboardEvent* keyboard_event) {
    
}

void Application::handle_Key_Up(SDL_KeyboardEvent* keyboard_event) {
    
}

int Application::get_Cursor_x_Pos() {
    return this->m_cursor_x_pos;
}

int Application::get_Cursor_y_Pos() {
    return this->m_cursor_y_pos;
}