
#include "SysSet.h"


void System::textures_setup()
{
	sf::Texture map; map.loadFromFile("resources\\textures\\map.png");
	textures["map"] = map;

	sf::Texture ph_style; ph_style.loadFromFile("resources\\textures\\ph_style.png");
	textures["ph_style"] = ph_style;

	sf::Texture ratingbar; ratingbar.loadFromFile("resources\\textures\\ratingbar.png");
	textures["ratingbar"] = ratingbar;

	sf::Texture menutab; menutab.loadFromFile("resources\\textures\\menutab.png");
	textures["menutab"] = menutab;

	sf::Texture mn_profile; mn_profile.loadFromFile("resources\\textures\\mn_profile.png");
	textures["mn_profile"] = mn_profile;

	sf::Texture mn_advsearch; mn_advsearch.loadFromFile("resources\\textures\\mn_advsearch.png");
	textures["mn_advsearch"] = mn_advsearch;

	sf::Texture mn_upload; mn_upload.loadFromFile("resources\\textures\\mn_upload.png");
	textures["mn_upload"] = mn_upload;

	sf::Texture mn_favs; mn_favs.loadFromFile("resources\\textures\\mn_favs.png");
	textures["mn_favs"] = mn_favs;

	sf::Texture mn_config; mn_config.loadFromFile("resources\\textures\\mn_config.png");
	textures["mn_config"] = mn_config;
}

void System::screens_setup()
{
	screens = new Entity*[N_SCREENS];

	home_setup();
	menu_setup();
	//favorites_setup();
	//feed_setup();
	//single_setup();
	unimp_setup();
}

void System::home_setup()
{
	Entity* home = new Entity[HOME_LEN];
	S_HOME = home;
	S_HOME[0] = Entity("map", 0.5f, 0.5f, 1.05f, 1.05f, true, true);        { S_HOME[0].init_img(textures["map"], 1.4f, 1.45f, C_LGRAY); }
	S_HOME[1] = Entity("searchbar", 0.5f, 0.08f, 0.84f, 0.06f, true, true); { S_HOME[1].init_box(sf::Color::Transparent); S_HOME[1].func = F_CURSOR_FLICKER; }
	S_HOME[1].init_menu(true, 4);
	{
		S_HOME[1].menu[0] = Entity("sb_backdrop", 0.5f, 0.08f, 0.84f, 0.06f, true, false); { S_HOME[1].menu[0].init_box(sf::Color::Black); }
		S_HOME[1].menu[1] = Entity("sb_writespace", 0.5f, 0.08f, 0.8f, 0.045f, true, false); { S_HOME[1].menu[1].init_box(C_GRAY); }
		S_HOME[1].menu[2] = Entity("sb_ctext", 0.16f, 0.08f, 0.9f, 0.1f, true, false); { S_HOME[1].menu[2].init_ctext("search...", font, 24, -2, sf::Color::Black); }
		S_HOME[1].menu[3] = Entity("sb_underline", 0.5f, 0.097f, 0.7f, 0.002f, true, false); { S_HOME[1].menu[3].init_box(sf::Color::Black); }
	}
	S_HOME[2] = Entity("ph_styles", 0.8f, 0.8f, 0.25f, 0.07f, false, true); { S_HOME[2].init_box(C_GRAY); S_HOME[2].init_text("� Style", font, 30, 2); S_HOME[2].func = F_RAISE_PH_STYLES; }
	S_HOME[2].init_menu(true, 6);
	{
		S_HOME[2].menu[0] = Entity("ph_style0", 0.225f, 0.66f, 0.22f, 0.105f, true, true); { S_HOME[2].menu[0].init_img(textures["ph_style"], .45f, .45f, C_LGRAY); S_HOME[2].menu[0].init_text("Street", font, 22, -2); }
		S_HOME[2].menu[1] = Entity("ph_style1", 0.5f, 0.66f, 0.22f, 0.105f, true, true);   { S_HOME[2].menu[1].init_img(textures["ph_style"], .45f, .45f, C_LGRAY); S_HOME[2].menu[1].init_text("Landscape", font, 20, -2); }
		S_HOME[2].menu[2] = Entity("ph_style2", 0.775f, 0.66f, 0.22f, 0.105f, true, true); { S_HOME[2].menu[2].init_img(textures["ph_style"], .45f, .45f, C_LGRAY); S_HOME[2].menu[2].init_text("Food", font, 22, -2); }
		S_HOME[2].menu[3] = Entity("ph_style3", 0.225f, 0.79f, 0.22f, 0.105f, true, true); { S_HOME[2].menu[3].init_img(textures["ph_style"], .45f, .45f, C_LGRAY); S_HOME[2].menu[3].init_text("Art", font, 22, -2); }
		S_HOME[2].menu[4] = Entity("ph_style4", 0.5f, 0.79f, 0.22f, 0.105f, true, true);   { S_HOME[2].menu[4].init_img(textures["ph_style"], .45f, .45f, C_LGRAY); S_HOME[2].menu[4].init_text("Adventure", font, 20, -2); }
		S_HOME[2].menu[5] = Entity("ph_style5", 0.775f, 0.79f, 0.22f, 0.105f, true, true); { S_HOME[2].menu[5].init_img(textures["ph_style"], .45f, .45f, C_LGRAY); S_HOME[2].menu[5].init_text("Nature", font, 22, -2); }
		for (int i = 0; i < 6; i++) S_HOME[2].menu[i].func = F_LOWER_PH_STYLES;
	}
	S_HOME[3] = Entity("ltext", 0.19f, 0.875f, 0.235f, 0.035f, false, false);  { S_HOME[3].init_box(C_GRAY);  S_HOME[3].init_text("Low Rating", font, 20, 2); }
	S_HOME[4] = Entity("rtext", 0.81f, 0.875f, 0.235f, 0.035f, false, false);  { S_HOME[4].init_box(C_GRAY); S_HOME[4].init_text("High Rating", font, 20, 2); }
	S_HOME[5] = Entity("ratingbar", 0.5f, 0.85f, 0.8f, 0.08f, false, false);  { S_HOME[5].init_img(textures["ratingbar"], .9f, 1.6f); }
	S_HOME[6] = Entity("menutab", 0.5f, 0.97f, 0.22f, 0.08f, true, true);     { S_HOME[6].init_img(textures["menutab"], .08f, .06f); S_HOME[6].func = F_OPEN_MENU; }
}

void System::menu_setup()
{
	Entity* menu = new Entity[MENU_LEN];
	S_MENU = menu;
	S_MENU[0] = Entity("background", 0.5f, 0.5f, 1.f, 1.f, true, true);    { S_MENU[0].menu_bg(); S_MENU[0].func = F_CLOSE_MENU; }
	S_MENU[1] = Entity("mn_profile", 0.15f, 0.93f, 0.16f, 0.07f, false, false);	S_MENU[1].init_menu(false, 4);
	{
		S_MENU[1].menu[0] = Entity("mp_back", 0.28f, 0.81f, 0.4f, 0.22f, true, true); { S_MENU[1].menu[0].init_box(sf::Color::Black); }
		S_MENU[1].menu[1] = Entity("mp_profile", 0.28f, 0.74f, 0.34f, 0.05f, true, true); { S_MENU[1].menu[1].init_box(C_GRAY); S_MENU[1].menu[1].init_text("� Profile", font, 22, 2, C_LGRAY); }
		S_MENU[1].menu[2] = Entity("mp_content", 0.28f, 0.8f, 0.34f, 0.05f, true, true); { S_MENU[1].menu[2].init_box(C_GRAY); S_MENU[1].menu[2].init_text("� My Content", font, 22, 2, C_LGRAY); }
		S_MENU[1].menu[3] = Entity("mp_pgrer", 0.28f, 0.86f, 0.34f, 0.05f, true, true); { S_MENU[1].menu[3].init_box(C_GRAY); S_MENU[1].menu[3].init_text(" � Become a\n  Photographer", font, 22, 2, C_LGRAY); }
	}
	S_MENU[2] = Entity("mn_advsearch", 0.325f, 0.93f, 0.16f, 0.07f, false, false); S_MENU[2].init_menu(false, 5);
	{
		S_MENU[2].menu[0] = Entity("ma_back",       0.5f, 0.88f, 0.7f, 0.18f, true, true); { S_MENU[2].menu[0].init_box(sf::Color::Black); S_MENU[2].menu[0].init_text("Search by...", font, 22, -60, C_LGRAY); }
		S_MENU[2].menu[1] = Entity("ma_searchbar",  0.5f, 0.835f,  0.56f, 0.002f, true, true); { S_MENU[2].menu[1].init_box(C_LGRAY); }//use functions from home searchbar?
		S_MENU[2].menu[2] = Entity("ma_locale",     0.26f, 0.87f, 0.2f, 0.04f, true, true); { S_MENU[2].menu[2].init_box(C_GRAY); S_MENU[2].menu[2].init_text("Locale", font, 20, 2, C_LGRAY); }
		S_MENU[2].menu[3] = Entity("ma_pgrer",      0.5f, 0.87f, 0.238f, 0.04f, true, true); { S_MENU[2].menu[3].init_box(C_GRAY); S_MENU[2].menu[3].init_text("Photographer", font, 18, 4, C_LGRAY); }
		S_MENU[2].menu[4] = Entity("ma_collection", 0.74f, 0.87f, 0.2f, 0.04f, true, true); { S_MENU[2].menu[4].init_box(C_GRAY); S_MENU[2].menu[4].init_text("Collection", font, 20, 2, C_LGRAY); }
	}
	S_MENU[3] = Entity("mn_upload", 0.5f, 0.93f, 0.16f, 0.07f, false, false); S_MENU[3].init_menu(false, 5);
	{
		S_MENU[3].menu[0] = Entity("mu_back",      0.5f, 0.884f, 0.64f, 0.18f, true, true); { S_MENU[3].menu[0].init_box(sf::Color::Black); }
		S_MENU[3].menu[1] = Entity("mu_upload",    0.5f, 0.83f, 0.28f, 0.054f, true, true); { S_MENU[3].menu[1].init_box(C_GRAY); S_MENU[3].menu[1].init_text("Upload From", font, 20, 2, C_LGRAY); }
		S_MENU[3].menu[2] = Entity("mu_fromfiles", 0.28f, 0.865f, 0.2f, 0.04f, true, true); { S_MENU[3].menu[2].init_box(C_GRAY); S_MENU[3].menu[2].init_text("Files", font, 20, 2, C_LGRAY); }
		S_MENU[3].menu[3] = Entity("mu_fromdrive", 0.5f, 0.865f, 0.2f, 0.04f, true, true); { S_MENU[3].menu[3].init_box(C_GRAY); S_MENU[3].menu[3].init_text("Drive", font, 20, 2, C_LGRAY); }
		S_MENU[3].menu[4] = Entity("mu_fromcloud", 0.72f, 0.865f, 0.2f, 0.04f, true, true); { S_MENU[3].menu[4].init_box(C_GRAY); S_MENU[3].menu[4].init_text("Cloud", font, 20, 2, C_LGRAY); }
	}
	S_MENU[4] = Entity("mn_favs", 0.675f, 0.93f, 0.16f, 0.07f, false, false); S_MENU[4].init_menu(false, 6);
	{
		S_MENU[4].menu[0] = Entity("mf_back",     0.76f, 0.75f, 0.4f, 0.28f, true, true); { S_MENU[4].menu[0].init_box(sf::Color::Black); S_MENU[4].menu[0].init_text("Favorites", font, 22, -110, C_LGRAY); }
		S_MENU[4].menu[1] = Entity("mf_view",     0.76f, 0.68f, 0.3f, 0.04f, true, true); { S_MENU[4].menu[1].init_box(C_GRAY); S_MENU[4].menu[1].init_text("View", font, 20, 2, C_LGRAY); }
		S_MENU[4].menu[2] = Entity("mf_addphoto", 0.76f, 0.725f, 0.3f, 0.04f, true, true); { S_MENU[4].menu[2].init_box(C_GRAY); S_MENU[4].menu[2].init_text("Add Photo", font, 20, 2, C_LGRAY); }
		S_MENU[4].menu[3] = Entity("mf_addpgrer", 0.76f, 0.77f, 0.3f, 0.04f, true, true); { S_MENU[4].menu[3].init_box(C_GRAY); S_MENU[4].menu[3].init_text("Photographer", font, 20, 2, C_LGRAY); }
		S_MENU[4].menu[4] = Entity("mf_addloc",   0.76f, 0.815f, 0.3f, 0.04f, true, true); { S_MENU[4].menu[4].init_box(C_GRAY); S_MENU[4].menu[4].init_text("Locale", font, 20, 2, C_LGRAY); }
		S_MENU[4].menu[5] = Entity("mf_addcoll",  0.76f, 0.86f, 0.3f, 0.04f, true, true); { S_MENU[4].menu[5].init_box(C_GRAY); S_MENU[4].menu[5].init_text("Collection", font, 20, 2, C_LGRAY); }
	}
	S_MENU[5] = Entity("mn_config", 0.85f, 0.93f, 0.16f, 0.07f, false, false); S_MENU[5].init_menu(false, 4);
	{
		S_MENU[5].menu[0] = Entity("mc_back", 0.87f, 0.83f, 0.34f, 0.18f, true, true);    { S_MENU[5].menu[0].init_box(sf::Color::Black); }
		S_MENU[5].menu[1] = Entity("mc_config", 0.85f, 0.77f, 0.25f, 0.038f, true, true); { S_MENU[5].menu[1].init_box(C_GRAY); S_MENU[5].menu[1].init_text("� Config", font, 22, 2, C_LGRAY); S_MENU[5].menu[1].func = F_UNIMP; }
		S_MENU[5].menu[2] = Entity("mc_logout", 0.85f, 0.815f, 0.25f, 0.038f, true, true);  { S_MENU[5].menu[2].init_box(C_GRAY); S_MENU[5].menu[2].init_text(" � Logout", font, 22, 2, C_LGRAY); S_MENU[5].menu[2].func = F_CLOSE; }
		S_MENU[5].menu[3] = Entity("mc_terms", 0.85f, 0.86f, 0.25f, 0.038f, true, true);  { S_MENU[5].menu[3].init_box(C_GRAY); S_MENU[5].menu[3].init_text("� Legal", font, 22, 2, C_LGRAY); S_MENU[5].menu[3].func = F_UNIMP; }
	}
	S_MENU[6] = Entity("scaffold", 0.5f, 0.94f, 1.f, 0.1f, true, true); { S_MENU[6].init_img(textures["ph_style"], 2.8f, .36f, C_LGRAY); }
	S_MENU[7] = Entity("profile_icon", 0.15f, 0.93f, 0.16f, 0.07f, true, true); { S_MENU[7].init_img(textures["mn_profile"], .35f, .35f, sf::Color::Black); S_MENU[7].func = F_RAISE_PROFILE; }
	S_MENU[8] = Entity("advsearch_icon", 0.325f, 0.93f, 0.16f, 0.07f, true, true); { S_MENU[8].init_img(textures["mn_advsearch"], .35f, .35f, sf::Color::Black); S_MENU[8].func = F_RAISE_ADVSEARCH; }
	S_MENU[9] = Entity("upload_icon", 0.5f, 0.93f, 0.16f, 0.07f, true, true); { S_MENU[9].init_img(textures["mn_upload"], .35f, .35f, sf::Color::Black); S_MENU[9].func = F_RAISE_UPLOAD; }
	S_MENU[10] = Entity("favs_icon", 0.675f, 0.93f, 0.16f, 0.07f, true, true); { S_MENU[10].init_img(textures["mn_favs"], .35f, .35f, sf::Color::Black); S_MENU[10].func = F_RAISE_FAVS; }
	S_MENU[11] = Entity("config_icon", 0.85f, 0.93f, 0.16f, 0.07f, true, true); { S_MENU[11].init_img(textures["mn_config"], .35f, .35f, sf::Color::Black); S_MENU[11].func = F_RAISE_CONFIG; }
}

void System::favorites_setup()
{
	Entity* favs = new Entity[FAVS_LEN];
	S_FAVS = favs;
	//S_FAVS[0]  = Entity("map", 0.5f, 0.5f, 1.f, 1.f);           { S_FAVS[0].init_box(); S_FAVS[0].init_img(textures["map"]); }
	//S_FAVS[1]  = Entity("searchbar", 0.5f, 0.08f, 0.9f, 0.1f) ; { S_FAVS[1].init_box(); S_FAVS[1].box->setFillColor(C_LIGHT); S_FAVS[1].init_text("stuff", font, 32); }
	//S_FAVS[2]  = Entity("ph_style", 0.2f, 0.7f, 0.2f, 0.15f);   { S_FAVS[2].init_box(); }
	//S_FAVS[3]  = Entity("ph_style", 0.5f, 0.7f, 0.2f, 0.15f);   { S_FAVS[3].init_box(); }
	//S_FAVS[4]  = Entity("ph_style", 0.8f, 0.7f, 0.2f, 0.15f);   { S_FAVS[4].init_box(); }
	//S_FAVS[5]  = Entity("ph_style", 0.2f, 0.82f, 0.2f, 0.15f);  { S_FAVS[5].init_box(); }
	//S_FAVS[6]  = Entity("ph_style", 0.5f, 0.82f, 0.2f, 0.15f);  { S_FAVS[6].init_box(); }
	//S_FAVS[7]  = Entity("ph_style", 0.8f, 0.82f, 0.2f, 0.15f);  { S_FAVS[7].init_box(); }
	//S_FAVS[8]  = Entity("ratingbar", 0.5f, 0.85f, 0.8f, 0.08f); { S_FAVS[8].init_box(); }
	//S_FAVS[9]  = Entity("text", 0.1f, 0.9f, 0.2f, 0.1f);        { S_FAVS[9].init_text("Low\nRating", font, 24); }
	//S_FAVS[10] = Entity("text", 0.9f, 0.9f, 0.2f, 0.1f);        { S_FAVS[10].init_text("High\nRating", font, 24); }
	//S_FAVS[11] = Entity("menutab", 0.5f, 0.95f, 0.2f, 0.1f);    { S_FAVS[11].init_box(); }
}

void System::feed_setup()
{
	Entity* feed = new Entity[FEED_LEN];
	S_FEED = feed;
	//S_FEED[0]  = Entity("map", 0.5f, 0.5f, 1.f, 1.f);           { S_FEED[0].init_box(); S_FEED[0].init_img(textures["map"]); }
	//S_FEED[1]  = Entity("searchbar", 0.5f, 0.08f, 0.9f, 0.1f);  { S_FEED[1].init_box(); S_FEED[1].box->setFillColor(C_LIGHT); S_FEED[1].init_text("stuff", font, 32); }
	//S_FEED[2]  = Entity("ph_style", 0.2f, 0.7f, 0.2f, 0.15f);   { S_FEED[2].init_box(); }
	//S_FEED[3]  = Entity("ph_style", 0.5f, 0.7f, 0.2f, 0.15f);   { S_FEED[3].init_box(); }
	//S_FEED[4]  = Entity("ph_style", 0.8f, 0.7f, 0.2f, 0.15f);   { S_FEED[4].init_box(); }
	//S_FEED[5]  = Entity("ph_style", 0.2f, 0.82f, 0.2f, 0.15f);  { S_FEED[5].init_box(); }
	//S_FEED[6]  = Entity("ph_style", 0.5f, 0.82f, 0.2f, 0.15f);  { S_FEED[6].init_box(); }
	//S_FEED[7]  = Entity("ph_style", 0.8f, 0.82f, 0.2f, 0.15f);  { S_FEED[7].init_box(); }
	//S_FEED[8]  = Entity("ratingbar", 0.5f, 0.85f, 0.8f, 0.08f); { S_FEED[8].init_box(); }
	//S_FEED[9]  = Entity("text", 0.1f, 0.9f, 0.2f, 0.1f);        { S_FEED[9].init_text("Low\nRating", font, 24); }
	//S_FEED[10] = Entity("text", 0.9f, 0.9f, 0.2f, 0.1f);        { S_FEED[10].init_text("High\nRating", font, 24); }
	//S_FEED[11] = Entity("menutab", 0.5f, 0.95f, 0.2f, 0.1f);    { S_FEED[11].init_box(); }
}

void System::single_setup()
{
	Entity* single = new Entity[SINGLE_LEN];
	S_SINGLE = single;
	//S_SINGLE[0]  = Entity("map", 0.5f, 0.5f, 1.f, 1.f);           { S_SINGLE[0].init_box(); S_SINGLE[0].init_img(textures["map"]); }
	//S_SINGLE[1]  = Entity("searchbar", 0.5f, 0.08f, 0.9f, 0.1f);  { S_SINGLE[1].init_box(); S_SINGLE[1].box->setFillColor(C_LIGHT); S_SINGLE[1].init_text("stuff", font, 32); }
	//S_SINGLE[2]  = Entity("ph_style", 0.2f, 0.7f, 0.2f, 0.15f);   { S_SINGLE[2].init_box(); }
	//S_SINGLE[3]  = Entity("ph_style", 0.5f, 0.7f, 0.2f, 0.15f);   { S_SINGLE[3].init_box(); }
	//S_SINGLE[4]  = Entity("ph_style", 0.8f, 0.7f, 0.2f, 0.15f);   { S_SINGLE[4].init_box(); }
	//S_SINGLE[5]  = Entity("ph_style", 0.2f, 0.82f, 0.2f, 0.15f);  { S_SINGLE[5].init_box(); }
	//S_SINGLE[6]  = Entity("ph_style", 0.5f, 0.82f, 0.2f, 0.15f);  { S_SINGLE[6].init_box(); }
	//S_SINGLE[7]  = Entity("ph_style", 0.8f, 0.82f, 0.2f, 0.15f);  { S_SINGLE[7].init_box(); }
	//S_SINGLE[8]  = Entity("ratingbar", 0.5f, 0.85f, 0.8f, 0.08f); { S_SINGLE[8].init_box(); }
	//S_SINGLE[9]  = Entity("text", 0.1f, 0.9f, 0.2f, 0.1f);        { S_SINGLE[9].init_text("Low\nRating", font, 24); }
	//S_SINGLE[10] = Entity("text", 0.9f, 0.9f, 0.2f, 0.1f);        { S_SINGLE[10].init_text("High\nRating", font, 24); }
	//S_SINGLE[11] = Entity("menutab", 0.5f, 0.95f, 0.2f, 0.1f);    { S_SINGLE[11].init_box(); }
}

void System::unimp_setup()
{
	Entity* unimp = new Entity[UNIMP_LEN];
	S_UNIMP = unimp;
	S_UNIMP[0] = Entity("backdrop", 0.5f, 0.5f, 1.f, 1.2f, true, false);     { S_UNIMP[0].init_box(C_GRAY); }
	S_UNIMP[1] = Entity("back", 0.2f, 0.08f, 0.33f, 0.05f, true, true);      { S_UNIMP[1].init_box(C_LGRAY); S_UNIMP[1].init_text("<<< BACK", font, 30, -2, sf::Color::Red); S_UNIMP[1].func = F_BACK; }
	S_UNIMP[2] = Entity("unimp_text", 0.5f, 0.5f, 0.2f, 0.15f, true, false); { S_UNIMP[2].init_text("Page Not Yet\nImplemented", font, 40, -4, C_LGRAY); }
	S_UNIMP[3] = Entity("menutab", 0.5f, 0.97f, 0.22f, 0.08f, true, true);   { S_UNIMP[3].init_img(textures["menutab"], .08f, .06f); S_UNIMP[3].func = F_OPEN_MENU; }
}