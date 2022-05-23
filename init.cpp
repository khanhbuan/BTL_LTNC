#include "init.h"
#include "load_img.h"
#include<iostream>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include<SDL.h>
using namespace std;

int BACK_STEP;
bool main_back, game_lose, re_play, check, random_check, buff, was_collision, random_stone, hard;
int random_val1, random_val2;
SDL_Rect space, start_banner, welcome_banner, help_banner;
SDL_Rect instruct_banner, back_banner, point_banner, back_press, rect_shield, pause_rect, pause_screen, getback_screen;
SDL_Rect char_rect[2], trap_rect, stone_rect, mode[2];
SDL_Texture *character[3], *trap[4];

void logSDLError(std::ostream& os, const std::string &msg, bool fatal) {
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	//SDL_FlushEvents();
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}

void waitUntilKeyPressed() {
    SDL_Event Test_event;
    while(true) {
        SDL_PollEvent(&Test_event);
        if((Test_event.type == SDL_QUIT || Test_event.type == SDL_KEYDOWN)) return;
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

    //Khi chay trong moi truong binh thuong (khong chay tren may ao)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //Khi chay o may ao
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void clear_renderer(SDL_Renderer* &renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
}

void set_side(SDL_Rect &rect, int x, int y, int h, int w) {
    rect.x = x;
    rect.y = y;
    rect.h = h;
    rect.w = w;
}

string add(string &s, string &s2) {
    string s3 = "";
    while(s.length() < s2.length()) s = "0" + s;
    while(s2.length() < s.length()) s2 = "0" + s2;
    int num, div = 0;
    for(int i = s.length() - 1 ; i >= 0 ; i--) {
        num = (s[i] - '0') + (s2[i] - '0') + div;
        s3 = (char)(num % 10 + '0') + s3;;
        div = num / 10;
    }
    if(div != 0) s3 = (char)(div + '0') + s3;
    return s3;
}

int convert(string &s) {
    int num = 0, div = 1;
    int n = s.length();
    for(int i = n - 1 ; i >= 0 ; i--) {
        num += (s[i] - '0')* div;
        div *= 10;
    }
    return num;
}

void trap_run(int &BACK_STEP, SDL_Rect &rect, SDL_Renderer* &renderer, SDL_Texture* &character, bool &random_check) {
    rect.x -= BACK_STEP;
    SDL_RenderCopy(renderer, character, NULL, &rect);
    if(rect.x <= BACK_STEP) {
        rect.x = SCREEN_WIDTH - rect.w;
        random_check = true;
    }
}

void setTexture(SDL_Renderer* &renderer, SDL_Texture* character[5], SDL_Texture* trap[5]) {
    string head = "dino", tail = ".png";
    for(int i = 0 ; i <= 1 ; i++) character[i] = loadTexture(head + char(i + 1 + '0') + tail, renderer);

    head = "cactus", tail = ".png";
    for(int i = 0 ; i <= 2 ; i++) trap[i] = loadTexture(head + (char)(i + '0') + tail, renderer);
}

void draw_ground(SDL_Renderer* &renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT/2 + height, SCREEN_WIDTH, SCREEN_HEIGHT/2 + height);
}

void falling_stone(SDL_Renderer* &renderer, SDL_Rect &stone_rect, SDL_Texture* &stone, bool &random_stone) {
    stone_rect.x -= 2;
    stone_rect.y += 1;
    SDL_RenderCopy(renderer, stone, NULL, &stone_rect);
    if(stone_rect.y >= SCREEN_HEIGHT/2 + height - stone_rect.h/2) {
        random_stone = true;
        stone_rect.x = rand() % 300 + 300;
        cout << stone_rect.x << endl;
        stone_rect.y = 0;
    }
}

void create() {
    set_side(space, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
    set_side(start_banner, 7*SCREEN_WIDTH/16, 7*SCREEN_HEIGHT/16, SCREEN_HEIGHT/10, SCREEN_WIDTH/8);
    set_side(welcome_banner, SCREEN_WIDTH/4, SCREEN_HEIGHT/8, SCREEN_HEIGHT/7, SCREEN_WIDTH/2);
    set_side(help_banner, 7*SCREEN_WIDTH/16, 9*SCREEN_HEIGHT/16, SCREEN_HEIGHT/10, SCREEN_WIDTH/8);
    set_side(instruct_banner, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH);
    set_side(back_banner, 0, 0, 50, 50);
    set_side(point_banner, 2*SCREEN_WIDTH/3, 100, 20, 100);
    set_side(pause_rect, 0, 0, 20, 20);
    set_side(pause_screen, 7*SCREEN_WIDTH/16, 7*SCREEN_HEIGHT/16, SCREEN_HEIGHT/10, SCREEN_WIDTH/8);
    set_side(getback_screen, 7*SCREEN_WIDTH/16, 9*SCREEN_HEIGHT/16, SCREEN_HEIGHT/10, SCREEN_WIDTH/8);
    set_side(stone_rect, 500, 0, 20, 20);
    set_side(mode[0], 7*SCREEN_WIDTH/16, 7*SCREEN_HEIGHT/16, SCREEN_HEIGHT/10, SCREEN_WIDTH/8);
    set_side(mode[1], 7*SCREEN_WIDTH/16, 9*SCREEN_HEIGHT/16, SCREEN_HEIGHT/10, SCREEN_WIDTH/8);
}

void update_point(SDL_Renderer* &renderer, TTF_Font* &gFont2, string &s, string &s2, SDL_Texture* &point, int &BACK_STEP) {
    s = add(s, s2);
    point = loadText(gFont2, renderer, "Your score: " + s, black);
    if(convert(s) % 1000 == 0 && convert(s) != 0) BACK_STEP = 12 * BACK_STEP / 10;
}

void random_trap(SDL_Renderer* &renderer, SDL_Rect &trap_rect, SDL_Texture* trap[3]) {
    if(random_check == true) {
        random_val1 = rand() % 6;
        random_check = false;
    }
    if(random_val1 == 0 || random_val1 == 1) SDL_RenderCopy(renderer, trap[0], NULL, &trap_rect);
    else if(random_val1 == 2 || random_val1 == 3) SDL_RenderCopy(renderer, trap[1], NULL, &trap_rect);
    else SDL_RenderCopy(renderer, trap[2], NULL, &rect_shield);
}

void set_bool() {
    re_play = false;
    main_back = false;
    game_lose = false;
    random_check = true;
    buff = false;
    was_collision = false;
    random_stone = true;
    hard = false;
}
