#include "game_continue.h"
#include<iostream>
#include<SDL.h>
using namespace std;

bool check_game_continue(SDL_Rect a1, SDL_Rect a2) {
    if(a1.x > a2.x) swap(a1, a2);
    else if(a1.x == a2.x) {
        if(a1.y > a2.y) swap(a1, a2);
    }
    if(a1.x <= a2.x && a2.x <= a1.x + a1.w) {
        if(a1.y <= a2.y && a2.y <= a1.y + a1.h) {
            return false;
        }
    }
    return true;
}
