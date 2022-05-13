
#include "Entities.h"


Entity::Entity()
{
	type = NULL; x = y = w = h = 0.f;
	is_alive = false; is_clicky = false; func = -1;
	menu_is_up = false; menu_len = 0; menu = NULL;
	box = NULL; img = NULL; text = NULL;
}

Entity::Entity(const char* type, float _x, float _y, float _w, float _h, bool is_alive, bool is_clicky) : type(type), is_alive(is_alive), is_clicky(is_clicky)
{
	func = -1;
	menu_is_up = false; menu_len = 0; menu = NULL;
	box = NULL; img = NULL; text = NULL;

	x = X(_x);
	y = Y(_y);
	w = W(_w);
	h = H(_h);

	std::cout << type << " x/y, w/h :: " << x << "/" << y << ", " << w << "/" << h << std::endl;
}

void Entity::init_menu(bool start_up, int l)
{
	menu_is_up = start_up;
	menu_len = l;
	menu = new Entity[l];
}

void Entity::init_box()
{
	box = std::make_shared<sf::RectangleShape>(sf::Vector2f(w, h));
	box->setOrigin(w / 2.f, h / 2.f);
	box->setPosition({ x, y });
	box->setFillColor(C_LIGHT);
}

void Entity::init_box(sf::Color fill_color)
{
	box = std::make_shared<sf::RectangleShape>(sf::Vector2f(w, h));
	box->setOrigin(w / 2.f, h / 2.f);
	box->setPosition({ x, y });
	box->setFillColor(fill_color);
}

void Entity::init_text(const char* str, sf::Font& font, unsigned int pt, int vert_offset)
{
	text = std::make_shared<sf::Text>(str, font, pt);
	text->setFillColor(sf::Color::Black);
	text->setOutlineColor(sf::Color::Black);
	text->setOrigin({ text->getGlobalBounds().width / 2.f + text->getLocalBounds().left, text->getGlobalBounds().height / 2.f + text->getLocalBounds().top - vert_offset});
	text->setPosition({ x, y });
}

void Entity::init_text(const char* str, sf::Font& font, unsigned int pt, int vert_offset, sf::Color font_color)
{
	text = std::make_shared<sf::Text>(str, font, pt);
	text->setFillColor(font_color);
	text->setOutlineColor(font_color);
	text->setOrigin({ text->getGlobalBounds().width / 2.f + text->getLocalBounds().left, text->getGlobalBounds().height / 2.f + text->getLocalBounds().top - vert_offset});
	text->setPosition({ x, y });
}

void Entity::init_ctext(const char* str, sf::Font& font, unsigned int pt, int vert_offset, sf::Color font_color)
{
	text = std::make_shared<sf::Text>(str, font, pt);
	text->setFillColor(font_color);
	text->setOutlineColor(font_color);
	text->setOrigin({ text->getGlobalBounds().left + text->getLocalBounds().left, text->getGlobalBounds().height / 2.f + text->getLocalBounds().top - vert_offset });
	text->setPosition({ x, y });
}

void Entity::init_img(sf::Texture& tx, float w_scale, float h_scale)
{
	img = std::make_shared<sf::Sprite>(tx);
	img->setOrigin({ img->getGlobalBounds().width / 2.f, img->getGlobalBounds().height / 2.f });
	img->setPosition({ x, y });
	img->setScale(w_scale, h_scale);
}

void Entity::init_img(sf::Texture& tx, float w_scale, float h_scale, sf::Color shade)
{
	img = std::make_shared<sf::Sprite>(tx);
	img->setColor(shade);
	img->setOrigin({ img->getGlobalBounds().width / 2.f, img->getGlobalBounds().height / 2.f });
	img->setPosition({ x, y });
	img->setScale(w_scale, h_scale);
}

void Entity::menu_bg()
{
	img = std::make_shared<sf::Sprite>();
}

void Entity::draw(sf::RenderWindow& window)
{
	if (box)  window.draw(*(box));
	if (img)  window.draw(*(img));
	if (text) window.draw(*(text));
}

bool Entity::contains(sf::Vector2i& p)
{
	if (!is_clicky) return false;

	return p.x >= (x - w/2) && p.x <= (x + w/2) && p.y >= (y - h/2) && p.y <= (y + h/2);
}

sf::Vector2f Entity::move(sf::Vector2f& offset)
{
	if (!(text || img || box)) return sf::Vector2f(0.f, 0.f);

	sf::Vector2f r; sf::Vector2f orig(x, y);
	if (text) { r = text->getPosition() + offset; text->setPosition(r); }
	if (img)  { r = img->getPosition() + offset; img->setPosition(r); }
	if (box)  { r = box->getPosition() + offset; box->setPosition(r); }
	return r - orig;
}

void Entity::set_pos(sf::Vector2f pos)
{
	if (text) text->setPosition(pos);
	if (img)  img->setPosition(pos);
	if (box)  box->setPosition(pos);
}

void Entity::reset_pos()
{
	if (text) text->setPosition({ x, y });
	if (img)  img->setPosition({ x, y });
	if (box)  box->setPosition({ x, y });
}