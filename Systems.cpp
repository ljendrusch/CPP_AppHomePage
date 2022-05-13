
#include "SysSet.h"


System::System()
{
    init();
}

void System::init()
{
    window.create(sf::VideoMode(W_WIDTH, W_HEIGHT), "", sf::Style::Close);
    window.setPosition({ (int)(sf::VideoMode::getDesktopMode().width - W_WIDTH) / 2, (int)(sf::VideoMode::getDesktopMode().height - W_HEIGHT) / 2 });
    window.setFramerateLimit(60);

    font.loadFromFile("resources\\fonts\\micross.ttf");
    textures_setup();

    potxt.loadFromFile("resources\\textures\\phone_outline.png");
    phone_outline.setTexture(potxt);
    phone_outline.setScale(0.5f, 0.5f);
    phone_outline.setOrigin(phone_outline.getGlobalBounds().width, phone_outline.getGlobalBounds().height);
    phone_outline.setPosition(round(W_WIDTH / 2.f), round(W_HEIGHT / 2.f));

    l_scaff.setSize({ 100.f, W_HEIGHT });
    l_scaff.setPosition(0.f, 0.f);
    l_scaff.setFillColor(C_DARK);
    r_scaff.setSize({ 100.f, W_HEIGHT });
    r_scaff.setOrigin(100.f, 0.f);
    r_scaff.setPosition(W_WIDTH, W_HEIGHT);
    r_scaff.setFillColor(C_DARK);

    screens_setup();

    current_screen = S_HOME;
    current_len = HOME_LEN;
    last_screen.push(S_HOME);
    last_len.push(HOME_LEN);
    search_str = "";
    selected_entity = NULL;
}

void System::run()
{
    //loop
    //    check input
    //    update "gamestate"
    //    clear, update view
    //    display view to window

    while (window.isOpen())
    {
        event_handler();
        do_funcs();
        draw();
        window.display();
    }
}

void System::event_handler()
{
    while (window.pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape) window.close();
            else if (ev.key.code == sf::Keyboard::F1) { current_screen = S_HOME;   current_len = HOME_LEN; }
            else if (ev.key.code == sf::Keyboard::F2) { current_screen = S_MENU;   current_len = MENU_LEN; }
            else if (ev.key.code == sf::Keyboard::F3) { current_screen = S_FAVS;   current_len = FAVS_LEN; }
            else if (ev.key.code == sf::Keyboard::F4) { current_screen = S_FEED;   current_len = FEED_LEN; }
            else if (ev.key.code == sf::Keyboard::F5) { current_screen = S_SINGLE; current_len = SINGLE_LEN; }
            else if (ev.key.code == sf::Keyboard::F6) { current_screen = S_UNIMP;  current_len = UNIMP_LEN; }
            break;
        case sf::Event::TextEntered:
            text_event();
            break;
        case sf::Event::MouseButtonPressed:
            mouse_event();
            break;
        default:
            break;
        }
    }
}

void System::text_event()
{
    if (memcmp(selected_entity->type, "searchbar", 10) != 0) return;

    if (ev.text.unicode == '\b')
    {
        if (search_str.size() > 0)
        {
            search_str.pop_back();
            selected_entity->menu[2].text->setString(search_str);
        }
    }
    else if (ev.text.unicode < 128 && search_str.size() < 32)
    {
        search_str += static_cast<char>(ev.text.unicode);
        selected_entity->menu[2].text->setString(search_str);
    }
}

void System::mouse_event()
{
    if (ev.mouseButton.button != sf::Mouse::Left) return;

    sf::Vector2i p(ev.mouseButton.x, ev.mouseButton.y);
    std::cout << "clicked " << p.x << "/" << p.y;

    if (p.x < 280 || p.x > 744 || p.y < 52 || p.y > 1014)
    {
        std::cout << ", out of bounds\n";
        selected_entity = NULL;
        return;
    }

    for (int i = current_len - 1; i >= 0; i--)
    {
        Entity* e = current_screen + i;
        if (e->menu && e->menu_is_up)
        {
            for (int j = e->menu_len - 1; j >= 0; j--)
            {
                if (e->menu[j].contains(p))
                {
                    std::cout << ", " << e->menu[j].type << "\n";
                    selected_entity = e->menu + j;
                    if (e->menu[j].func >= 0) active_funcs[e->menu[j].func] = true;
                    return;
                }
            }
        }
        if (e->is_alive && e->contains(p))
        {
            std::cout << ", " << e->type << "\n";
            selected_entity = e;
            if (e->func >= 0) active_funcs[e->func] = true;
            return;
        }
    }

    std::cout << "\n";
    selected_entity = NULL;
}

void System::draw()
{
    window.clear(C_DARK);

    for (int i = 0; i < current_len; i++)
    {
        Entity* e = current_screen + i;
        if (e->menu && e->menu_is_up) for (int j = 0; j < e->menu_len; j++) if (e->menu[j].is_alive) e->menu[j].draw(window);
        if (e->is_alive) e->draw(window);
    }

    window.draw(phone_outline);
    window.draw(l_scaff);
    window.draw(r_scaff);
}