
#include "SysSet.h"


void System::do_funcs()
{
    AF(0) back();
    AF(1) cursor_flicker();
    AF(2) raise_ph_styles();
    AF(3) slide_ph_styles_open();
    AF(4) lower_ph_styles();
    AF(5) slide_ph_styles_closed();
    AF(6) open_menu();
    AF(7) menu_slide();
    AF(8) close_menu();
    AF(9) raise_profile();
    AF(10) slide_profile();
    AF(11) lower_profile();
    AF(12) raise_advsearch();
    AF(13) slide_advsearch();
    AF(14) lower_advsearch();
    AF(15) raise_upload();
    AF(16) slide_upload();
    AF(17) lower_upload();
    AF(18) raise_favs();
    AF(19) slide_favs();
    AF(20) lower_favs();
    AF(21) raise_config();
    AF(22) slide_config();
    AF(23) lower_config();
    AF(24) unimp();
    AF(25) close();
}

//all
bool System::back()
{
    current_screen = last_screen.top(); last_screen.pop();
    current_len = last_len.top(); last_len.pop();

    return false;
}

//home screen
bool System::cursor_flicker()
{
    if (memcmp(selected_entity->type, "searchbar", 10) != 0)
    {
        S_HOME[1].menu[2].text->setString(search_str);
        return false;
    }

    if (((run_time.getElapsedTime().asMilliseconds() / 100) % 10) < 5)
        S_HOME[1].menu[2].text->setString(search_str);
    else
        S_HOME[1].menu[2].text->setString(search_str + "|");

    return true;
}

bool System::raise_ph_styles()
{
    S_HOME[2].menu_is_up = true;
    S_HOME[2].is_alive = false;
    for (int i = 0; i < 6; i++) fin[i] = false;
    for (int i = 0; i < S_HOME[2].menu_len; i++) S_HOME[2].menu[i].is_alive = true;

    active_funcs[F_SLIDE_PH_STYLES_OPEN] = true;

    return false;
}

bool System::slide_ph_styles_open()
{
    if (fin[0] && fin[1] && fin[2] && fin[3] && fin[4] && fin[5])
    {
        S_HOME[3].is_alive = false;
        S_HOME[4].is_alive = false;
        S_HOME[5].is_alive = false;
        return false;
    }

    for (int i = 0; i < S_HOME[2].menu_len; i++)
    {
        if (fin[i]) continue;

        float ray_x = S_HOME[2].menu[i].x - S_HOME[2].menu[i].img->getPosition().x;
        float ray_y = S_HOME[2].menu[i].y - S_HOME[2].menu[i].img->getPosition().y;

        if (ray_x > 0 || ray_y > 0)
        {
            S_HOME[2].menu[i].set_pos(sf::Vector2f(S_HOME[2].menu[i].x, S_HOME[2].menu[i].y));
            fin[i] = true;
            continue;
        }

        sf::Vector2f trans(ray_x, ray_y);
        trans /= (sqrt(ray_x * ray_x + ray_y * ray_y));
        trans *= ph_dists[i];

        S_HOME[2].menu[i].move(trans);
    }

    return true;
}

bool System::lower_ph_styles()
{
    S_HOME[3].is_alive = true;
    S_HOME[4].is_alive = true;
    S_HOME[5].is_alive = true;
    for (int i = 0; i < 6; i++) fin[i] = false;

    active_funcs[F_SLIDE_PH_STYLES_CLOSED] = true;

    return false;
}

bool System::slide_ph_styles_closed()
{
    if (fin[0] && fin[1] && fin[2] && fin[3] && fin[4] && fin[5])
    {
        for (int i = 0; i < 6; i++) S_HOME[2].menu[i].set_pos(S_HOME[2].box->getPosition());

        S_HOME[2].menu_is_up = false;
        S_HOME[2].is_alive = true;
        return false;
    }

    for (int i = 0; i < S_HOME[2].menu_len; i++)
    {
        if (!S_HOME[2].menu[i].is_alive) continue;

        float ray_x = S_HOME[2].x - S_HOME[2].menu[i].img->getPosition().x;
        float ray_y = S_HOME[2].y - S_HOME[2].menu[i].img->getPosition().y;

        if (ray_x < 0 || ray_y < 0)
        {
            S_HOME[2].menu[i].is_alive = false;
            fin[i] = true;
            continue;
        }

        sf::Vector2f trans(ray_x, ray_y);
        trans /= (sqrt(ray_x * ray_x + ray_y * ray_y));
        trans *= ph_dists[i];

        S_HOME[2].menu[i].move(trans);
    }

    return true;
}

bool System::open_menu()
{
    last_screen.push(current_screen);
    last_len.push(current_len);

    sf::Texture t; t.create(window.getSize().x, window.getSize().y); t.update(window);
    textures["last_screen"] = t;

    S_MENU[0].img->setTexture(textures["last_screen"]);
    S_MENU[0].img->setColor(C_GRAY);

    current_screen = S_MENU;
    current_len = MENU_LEN;

    lower_profile();
    lower_advsearch();
    lower_upload();
    lower_favs();
    lower_config();

    for (int i = 6; i < MENU_LEN; i++)
    {
        sf::Vector2f trans(S_MENU[i].x, S_MENU[i].y + 80.f);
        S_MENU[i].set_pos(trans);
    }

    active_funcs[F_MENU_SLIDE] = true;

    return false;
}

bool System::menu_slide()
{
    sf::Vector2f trans(0.f, -6.f);

    for (int i = 6; i < MENU_LEN; i++)
    {
        sf::Vector2f dif = S_MENU[i].move(trans);
        
        if (dif.y < 0)
        {
            for (int j = 6; j < MENU_LEN; j++)
            {
                S_MENU[j].reset_pos();
            }
            return false;
        }
    }

    return true;
}

bool System::close_menu()
{
    current_screen = last_screen.top(); last_screen.pop();
    current_len = last_len.top(); last_len.pop();
    
    return false;
}


//menu screen
bool System::raise_profile()
{
    lower_advsearch();
    lower_upload();
    lower_favs();
    lower_config();

    S_MENU[1].menu_is_up = true;
    S_MENU[1 + 6].img->setColor(C_LGRAY);

    active_funcs[F_SLIDE_PROFILE] = true;

    return false;
}

bool System::slide_profile()
{
    sf::Vector2f trans(0.f, -6.f);

    for (int i = 0; i < S_MENU[1].menu_len; i++)
    {
        sf::Vector2f dif = S_MENU[1].menu[i].move(trans);

        if (dif.y < 0)
        {
            for (int j = 0; j < S_MENU[1].menu_len; j++)
            {
                S_MENU[1].menu[j].reset_pos();
            }
            return false;
        }
    }

    return true;
}

bool System::lower_profile()
{
    S_MENU[1].menu_is_up = false;
    S_MENU[1 + 6].img->setColor(sf::Color::Black);

    for (int i = 0; i < S_MENU[1].menu_len; i++)
    {
        sf::Vector2f trans(S_MENU[1].menu[i].x, S_MENU[1].menu[i].y + 120.f);
        S_MENU[1].menu[i].set_pos(trans);
    }

    return false;
}


bool System::raise_advsearch()
{
    lower_profile();
    lower_upload();
    lower_favs();
    lower_config();

    S_MENU[2].menu_is_up = true;
    S_MENU[2 + 6].img->setColor(C_LGRAY);

    active_funcs[F_SLIDE_ADVSEARCH] = true;

    return false;
}


bool System::slide_advsearch()
{
    sf::Vector2f trans(0.f, -6.f);

    for (int i = 0; i < S_MENU[2].menu_len; i++)
    {
        sf::Vector2f dif = S_MENU[2].menu[i].move(trans);

        if (dif.y < 0)
        {
            for (int j = 0; j < S_MENU[2].menu_len; j++)
            {
                S_MENU[2].menu[j].reset_pos();
            }
            return false;
        }
    }

    return true;
}

bool System::lower_advsearch()
{
    S_MENU[2].menu_is_up = false;
    S_MENU[2 + 6].img->setColor(sf::Color::Black);

    for (int i = 0; i < S_MENU[2].menu_len; i++)
    {
        sf::Vector2f trans(S_MENU[2].menu[i].x, S_MENU[2].menu[i].y + 120.f);
        S_MENU[2].menu[i].set_pos(trans);
    }

    return false;
}

bool System::raise_upload()
{
    lower_profile();
    lower_advsearch();
    lower_favs();
    lower_config();

    S_MENU[3].menu_is_up = true;
    S_MENU[3 + 6].img->setColor(C_LGRAY);

    active_funcs[F_SLIDE_UPLOAD] = true;

    return false;
}

bool System::slide_upload()
{
    sf::Vector2f trans(0.f, -6.f);

    for (int i = 0; i < S_MENU[3].menu_len; i++)
    {
        sf::Vector2f dif = S_MENU[3].menu[i].move(trans);

        if (dif.y < 0)
        {
            for (int j = 0; j < S_MENU[3].menu_len; j++)
            {
                S_MENU[3].menu[j].reset_pos();
            }
            return false;
        }
    }

    return true;
}

bool System::lower_upload()
{
    S_MENU[3].menu_is_up = false;
    S_MENU[3 + 6].img->setColor(sf::Color::Black);

    for (int i = 0; i < S_MENU[3].menu_len; i++)
    {
        sf::Vector2f trans(S_MENU[3].menu[i].x, S_MENU[3].menu[i].y + 120.f);
        S_MENU[3].menu[i].set_pos(trans);
    }

    return false;
}

bool System::raise_favs()
{
    lower_profile();
    lower_advsearch();
    lower_upload();
    lower_config();

    S_MENU[4].menu_is_up = true;
    S_MENU[4 + 6].img->setColor(C_LGRAY);

    active_funcs[F_SLIDE_FAVS] = true;

    return false;
}

bool System::slide_favs()
{
    sf::Vector2f trans(0.f, -6.f);

    for (int i = 0; i < S_MENU[4].menu_len; i++)
    {
        sf::Vector2f dif = S_MENU[4].menu[i].move(trans);

        if (dif.y < 0)
        {
            for (int j = 0; j < S_MENU[4].menu_len; j++)
            {
                S_MENU[4].menu[j].reset_pos();
            }
            return false;
        }
    }

    return true;
}

bool System::lower_favs()
{
    S_MENU[4].menu_is_up = false;
    S_MENU[4 + 6].img->setColor(sf::Color::Black);

    for (int i = 0; i < S_MENU[4].menu_len; i++)
    {
        sf::Vector2f trans(S_MENU[4].menu[i].x, S_MENU[4].menu[i].y + 120.f);
        S_MENU[4].menu[i].set_pos(trans);
    }

    return false;
}

bool System::raise_config()
{
    lower_profile();
    lower_advsearch();
    lower_upload();
    lower_favs();

    S_MENU[5].menu_is_up = true;
    S_MENU[5 + 6].img->setColor(C_LGRAY);

    active_funcs[F_SLIDE_CONFIG] = true;

    return false;
}

bool System::slide_config()
{
    sf::Vector2f trans(0.f, -6.f);

    for (int i = 0; i < S_MENU[5].menu_len; i++)
    {
        sf::Vector2f dif = S_MENU[5].menu[i].move(trans);

        if (dif.y < 0)
        {
            for (int j = 0; j < S_MENU[5].menu_len; j++)
            {
                S_MENU[5].menu[j].reset_pos();
            }
            return false;
        }
    }

    return true;
}

bool System::lower_config()
{
    S_MENU[5].menu_is_up = false;
    S_MENU[5 + 6].img->setColor(sf::Color::Black);

    for (int i = 0; i < S_MENU[5].menu_len; i++)
    {
        sf::Vector2f trans(S_MENU[5].menu[i].x, S_MENU[5].menu[i].y + 120.f);
        S_MENU[5].menu[i].set_pos(trans);
    }

    return false;
}

bool System::unimp()
{
    last_screen.push(current_screen);
    last_len.push(current_len);
    current_screen = S_UNIMP;
    current_len = UNIMP_LEN;

    return false;
}

bool System::close()
{
    window.close();

    return false;
}
