#pragma once
#include "Defines.h"


class Entity {
public:
	const char* type;
	float x; float y;
	float w; float h;
	bool is_alive;
	bool is_clicky;
	int func;

	bool menu_is_up;
	int menu_len;
	Entity* menu;

	std::shared_ptr<sf::RectangleShape> box;
	std::shared_ptr<sf::Sprite> img;
	std::shared_ptr<sf::Text> text;

	Entity();
	Entity(const char*, float, float, float, float, bool, bool);

	void init_menu(bool,int);
	void init_box();
	void init_box(sf::Color);
	void init_text(const char*, sf::Font&, unsigned int, int);
	void init_text(const char*, sf::Font&, unsigned int, int, sf::Color);
	void init_ctext(const char*, sf::Font&, unsigned int, int, sf::Color);

	void init_img(sf::Texture&, float, float);
	void init_img(sf::Texture&, float, float, sf::Color);
	void menu_bg();

	void draw(sf::RenderWindow&);
	bool contains(sf::Vector2i&);
	sf::Vector2f move(sf::Vector2f&);
	void set_pos(sf::Vector2f);
	void reset_pos();
};