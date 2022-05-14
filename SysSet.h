#pragma once
#include "Entities.h"


class System {
public:
	//drawspace
	sf::RenderWindow window;
	Entity** screens;
	sf::Texture potxt;
	sf::Sprite phone_outline;
	sf::RectangleShape l_scaff;
	sf::RectangleShape r_scaff;

	//events
	sf::Event ev;
	bool active_funcs[FPS_LEN];
	bool fin[6];
	float ph_dists[6];
	sf::Clock run_time;
	std::stack<Entity*> last_screen;
	std::stack<int> last_len;
	Entity* current_screen;
	int current_len;
	Entity* selected_entity;
	std::string search_str;
	bool cursor_on;

	//loaded assets
	sf::Font font;
	std::map<const char*, sf::Texture> textures;

	System();

	void run();

private:
	void init();

	void textures_setup();

	void screens_setup();
	void home_setup();
	void menu_setup();
	void favorites_setup();
	void feed_setup();
	void single_setup();
	void unimp_setup();

	void event_handler();
	void text_event();
	void mouse_event();

	void do_funcs();
	//all
	bool back();
	//home screen
	bool cursor_flicker();
	bool raise_ph_styles();
	bool slide_ph_styles_open();
	bool lower_ph_styles();
	bool slide_ph_styles_closed();
	bool open_menu();
	bool menu_slide();
	bool close_menu();
	//menu screen
	bool raise_profile();
	bool slide_profile();
	bool lower_profile();
	bool raise_advsearch();
	bool slide_advsearch();
	bool lower_advsearch();
	bool raise_upload();
	bool slide_upload();
	bool lower_upload();
	bool raise_favs();
	bool slide_favs();
	bool lower_favs();
	bool raise_config();
	bool slide_config();
	bool lower_config();
	bool unimp();
	bool close();

	void draw();
};
