#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <memory>
#include <SFML/Graphics.hpp>

#define W_WIDTH 1024
#define W_HEIGHT 1024

#define V_WIDTH 462
#define V_HEIGHT 958

#define LEFT_BOUND ((W_WIDTH - V_WIDTH) / 2.f)
#define TOP_BOUND ((W_HEIGHT - V_HEIGHT) / 2.f + 40)

#define X(x) round(LEFT_BOUND + (V_WIDTH * (x)))
#define Y(y) round(TOP_BOUND + (V_HEIGHT * (y)))
#define W(w) round(V_WIDTH * (w))
#define H(h) round(V_HEIGHT * (h))

#define C_DARK (sf::Color(26, 43, 86, 255))
#define C_MEDIUM (sf::Color(39, 65, 129, 255))
#define C_LIGHT (sf::Color(52, 86, 172, 255))
#define C_GRAY (sf::Color(100, 100, 100, 255))
#define C_LGRAY (sf::Color(220, 220, 220, 255))

#define N_SCREENS 6
#define S_HOME (screens[0])
#define S_MENU (screens[1])
#define S_FAVS (screens[2])
#define S_FEED (screens[3])
#define S_SINGLE (screens[4])
#define S_UNIMP (screens[5])

#define HOME_LEN 12
#define MENU_LEN 12
#define FAVS_LEN 12
#define FEED_LEN 12
#define SINGLE_LEN 12
#define UNIMP_LEN 4

#define FPS_LEN 26
#define AF(n) if (active_funcs[n]) active_funcs[n] =

#define F_BACK 0
#define F_CURSOR_FLICKER 1
#define F_RAISE_PH_STYLES 2
#define F_SLIDE_PH_STYLES_OPEN 3
#define F_LOWER_PH_STYLES 4
#define F_SLIDE_PH_STYLES_CLOSED 5
#define F_OPEN_MENU 6
#define F_MENU_SLIDE 7
#define F_CLOSE_MENU 8
#define F_RAISE_PROFILE 9
#define F_SLIDE_PROFILE 10
#define F_LOWER_PROFILE 11
#define F_RAISE_ADVSEARCH 12
#define F_SLIDE_ADVSEARCH 13
#define F_LOWER_ADVSEARCH 14
#define F_RAISE_UPLOAD 15
#define F_SLIDE_UPLOAD 16
#define F_LOWER_UPLOAD 17
#define F_RAISE_FAVS 18
#define F_SLIDE_FAVS 19
#define F_LOWER_FAVS 20
#define F_RAISE_CONFIG 21
#define F_SLIDE_CONFIG 22
#define F_LOWER_CONFIG 23
#define F_UNIMP 24
#define F_CLOSE 25