#include "Station.h"

namespace {
    bool inRect(float px, float py, float top, float left, float width, float height) {
        return (px > left && px < left + width && py > top && py < top + height);
    }
} //namespace
    
Station::Station() {
    ImagePool::initialize();
    this->soundEnabled = true;
    this->backgroundTexture.loadFromImage(ImagePool::getImageById(ImageID::BACKGROUND));
    this->bossRoomTexture.loadFromImage(ImagePool::getImageById(ImageID::BOSSROOM));
    this->bossTexture.loadFromImage(ImagePool::getImageById(ImageID::BOSS));
    this->doorBottomTexture.loadFromImage(ImagePool::getImageById(ImageID::DOORBOT));
    this->doorLeftTexture.loadFromImage(ImagePool::getImageById(ImageID::DOORLEFT));
    this->timingGamesLogoTexture.loadFromImage(ImagePool::getImageById(ImageID::TIMING));
    this->doorRightTexture.loadFromImage(ImagePool::getImageById(ImageID::DOORRIGHT));
    this->doorTopTexture.loadFromImage(ImagePool::getImageById(ImageID::DOORUP));
    this->endScreenTexture.loadFromImage(ImagePool::getImageById(ImageID::ENDSCREEN));
    this->exitTexture.loadFromImage(ImagePool::getImageById(ImageID::EXIT));
    this->pauseExitTexture.loadFromImage(ImagePool::getImageById(ImageID::EXITP));
    this->explosionTexture.loadFromImage(ImagePool::getImageById(ImageID::EXPLOSION));
    this->floorTileTexture.loadFromImage(ImagePool::getImageById(ImageID::FLOOR_TILE_TEXTURE));
    this->guiTexture.loadFromImage(ImagePool::getImageById(ImageID::GUI));
    this->inventoryTexture.loadFromImage(ImagePool::getImageById(ImageID::INVENT));
    this->loadingTexture.loadFromImage(ImagePool::getImageById(ImageID::LOADING));
    this->mainMenuTexture.loadFromImage(ImagePool::getImageById(ImageID::TITLE));
    this->pauseMenuTexture.loadFromImage(ImagePool::getImageById(ImageID::MENUP));
    this->optionsButtonPauseMenuTexture.loadFromImage(ImagePool::getImageById(ImageID::OPTIONP));
    this->optionsMenuBackgroundTexture.loadFromImage(ImagePool::getImageById(ImageID::OPTIONSMAIN));
    this->optionsButtonMainMenuTexture.loadFromImage(ImagePool::getImageById(ImageID::OPTIONS));
    this->pauseMenuBackgroundTexture.loadFromImage(ImagePool::getImageById(ImageID::PAUSE));
    this->playerTexture.loadFromImage(ImagePool::getImageById(ImageID::PLAYER));
    this->subliminalImageTexture.loadFromImage(ImagePool::getImageById(ImageID::SUBLIMINAL));
    this->newGameTexture.loadFromImage(ImagePool::getImageById(ImageID::NEWGAME));
    this->selectionTexture.loadFromImage(ImagePool::getImageById(ImageID::SELECT));
    this->width = 1920;
    this->height = 1080;
    App.create(sf::VideoMode(width, height), "The Station", sf::Style::Fullscreen);
    this->isUnsized = false;

    this->guiTexture.loadFromImage(this->guii);
    this->arial.loadFromFile("../fonts/arial.ttf");
    this->shots.loadFromFile("../sounds/pew.wav");
    this->cx = 5;
    this->cy = 5;
    this->cheatsEnabled = false;

    this->explos.loadFromFile("../sounds/xplosion.wav");
}



void Station::inventory(Character &target) {
    sf::Sprite invbg;
    sf::Sprite weapon, gui;
    gui.setTexture(guiTexture);
    sf::Texture wt;
    sf::IntRect weaprects[6];
    for (int i = 0; i < 6; i++) {
        weaprects[i].height = 79;
        weaprects[i].width = 224;
        weaprects[i].left = 0;
        weaprects[i].top = i * 79;
    }


    weapon.setTexture(wt);

    weapon.setPosition(width / 100, height / 32);
    invbg.setTexture(inventoryTexture);
    invbg.setPosition(0, 0);
    sf::Sprite a[5][3];
    sf::Text infotext;
    sf::Sprite select;
    select.setTexture(selectionTexture);
    int q = width * 5 / 100;
    q = 86;
    int z = height * 295 / 1000;
    z = 302;
    int p = width * 192 / 1000;
    p = 371;
    int o = height * 234 / 1000;
    o = 259;
    a[0][0].setPosition(q, z);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            a[i][j].setTexture(t0);
            if (!i && !j)
                continue;
            a[i][j].setPosition(q + i * p, z + j * o);
        }
    }
    bool isset[5][3] = {false};
    sf::IntRect rects[5][3];
    rects[0][0].top = 0;
    rects[0][0].left = 0;
    rects[0][0].width = t0.getSize().x / 5;
    rects[0][0].height = t0.getSize().y / 3;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (!i && !j)
                continue;
            rects[i][j].width = t0.getSize().x / 5;
            rects[i][j].height = t0.getSize().y / 3;
            if (!i) {
                rects[i][j].left = 0;
            } else {
                rects[i][j].left = rects[i - 1][j].left + rects[i][j].width;
            }
            if (!j) {
                rects[i][j].top = 0;
            } else {
                rects[i][j].top = rects[i][j - 1].top + rects[i][j].height;
            }
        }
    }

    sf::RectangleShape tooltip(sf::Vector2f(350, 125));
    sf::Text title, desc, flavor;
    tooltip.setFillColor(sf::Color::Black);
    title.setFont(arial);
    title.setStyle(sf::Text::Bold);
    flavor.setStyle(sf::Text::Italic);
    desc.setFont(arial);
    flavor.setFont(arial);
    title.setCharacterSize(20);
    desc.setCharacterSize(15);
    flavor.setCharacterSize(10);
    title.setFillColor(sf::Color::White);
    desc.setFillColor(sf::Color::White);
    flavor.setFillColor(sf::Color::White);


    sf::Text hpbar;

    hpbar.setFillColor(sf::Color::White);
    hpbar.setPosition(width * 255 / 1000, height * 25 / 1000);
    hpbar.setFont(arial);

    while (true) {
        bool throwed = false;
        bool click = false;
        sf::Event event;
        while (App.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    App.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    click = true;
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Tab) {
                        return;
                    }
                    if (event.key.code == sf::Keyboard::R)
                        throwed = false;
                default:
                    break;
            }
        }

        App.draw(gui);
        weapon.setTextureRect(weaprects[target.inv[target.weaponiter].getId()]);
        App.draw(weapon);
        sf::String hptext;
        std::ostringstream convert;
        convert << target.health;
        hptext = convert.str();
        convert.str(std::string());
        hpbar.setString(hptext);
        App.draw(hpbar);
        bool mouseOver = false;
        App.draw(invbg);
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 3; k++) {
                isset[j][k] = false;

            }
        }
        ///Code here starts
        for (int i = 0; i < target.inv.size(); i++) {
            switch (target.inv[i].getId()) {
                case 0:/// DEFAULT GUN
                    for (int k = 0; k < 3; k++) {
                        for (int j = 0; j < 5; j++) {
                            if (!isset[j][k]) {

                                if (inRect(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y,
                                           a[j][k].getPosition().y, a[j][k].getPosition().x, rects[j][k].width,
                                           rects[j][k].height)) {
                                    if (click) {
                                        target.useItem(i);
                                    }
                                    if (throwed)
                                        target.deleteItem(i, 1);
                                    int l = q + j * p;
                                    int t = z + k * o;
                                    select.setPosition(l, t);
                                    App.draw(select);

                                    mouseOver = true;
                                    isset[j][k] = true;
                                    a[j][k].setTextureRect(rects[0][0]);
                                    App.draw(a[j][k]);

                                    tooltip.setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
                                    std::string option;
                                    if (target.weaponiter == i) {
                                        option = " (Currently equipped)";
                                    }
                                    title.setString("Training Gun" + option);
                                    title.setPosition(sf::Mouse::getPosition().x + 10, sf::Mouse::getPosition().y + 10);
                                    desc.setPosition(sf::Mouse::getPosition().x + 10, sf::Mouse::getPosition().y + 40);
                                    flavor.setPosition(sf::Mouse::getPosition().x + 10,
                                                       sf::Mouse::getPosition().y + 100);
                                    std::ostringstream strem;
                                    strem << "Standard Training Equipment. Damage: " << target.inv[i].getEffectNum()
                                          << " HP.";
                                    desc.setString(strem.str());
                                    flavor.setString("Honestly, who would want THAT?");
                                } else {
                                    isset[j][k] = true;
                                    a[j][k].setTextureRect(rects[0][0]);
                                    App.draw(a[j][k]);
                                }
                                if (target.inv[i].quant > 1) {
                                    sf::Text quanttext;
                                    quanttext.setCharacterSize(40);
                                    quanttext.setFillColor(sf::Color::White);
                                    quanttext.setFont(arial);
                                    quanttext.setPosition(q + j * p + 230, z + k * o + 170);
                                    std::ostringstream strem;
                                    strem << target.inv[i].quant;
                                    quanttext.setString(strem.str());
                                    App.draw(quanttext);
                                }
                                goto contWeapon;
                            }

                        }
                    }
                contWeapon:
                    break;
                case 1:/// BETTER GUN
                    for (int k = 0; k < 3; k++) {
                        for (int j = 0; j < 5; j++) {
                            if (!isset[j][k]) {

                                if (inRect(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y,
                                           a[j][k].getPosition().y, a[j][k].getPosition().x, rects[j][k].width,
                                           rects[j][k].height)) {
                                    /// if selected
                                    if (click) {
                                        target.useItem(i);
                                    }
                                    if (throwed)
                                        target.deleteItem(i, 1);
                                    int l = q + j * p;
                                    int t = z + k * o;
                                    select.setPosition(l, t);
                                    App.draw(select);

                                    mouseOver = true;
                                    isset[j][k] = true;
                                    a[j][k].setTextureRect(rects[2][0]);
                                    App.draw(a[j][k]);

                                    tooltip.setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
                                    std::string option;
                                    if (target.weaponiter == i) {
                                        option = " (Currently equipped)";
                                    }
                                    title.setString("Basic Rifle" + option);
                                    title.setPosition(sf::Mouse::getPosition().x + 10, sf::Mouse::getPosition().y + 10);
                                    desc.setPosition(sf::Mouse::getPosition().x + 10, sf::Mouse::getPosition().y + 40);
                                    flavor.setPosition(sf::Mouse::getPosition().x + 10,
                                                       sf::Mouse::getPosition().y + 100);
                                    std::ostringstream strem;
                                    strem << "Standard Patrol Equipment. Damage: " << target.inv[i].getEffectNum()
                                          << " HP.";
                                    desc.setString(strem.str());
                                    flavor.setString("Not the greatest, but will do.");
                                } else {
                                    isset[j][k] = true;
                                    a[j][k].setTextureRect(rects[2][0]);
                                    App.draw(a[j][k]);
                                }
                                if (target.inv[i].quant > 1) {
                                    sf::Text quanttext;
                                    quanttext.setCharacterSize(40);
                                    quanttext.setFillColor(sf::Color::White);
                                    quanttext.setFont(arial);
                                    quanttext.setPosition(q + j * p + 230, z + k * o + 170);
                                    std::ostringstream strem;
                                    strem << target.inv[i].quant;
                                    quanttext.setString(strem.str());
                                    App.draw(quanttext);
                                }

                                goto contWeapon2;
                            }

                        }
                    }
                contWeapon2:
                    break;
                case 2:/// ferd GUN
                    for (int k = 0; k < 3; k++) {
                        for (int j = 0; j < 5; j++) {
                            if (!isset[j][k]) {

                                if (inRect(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y,
                                           a[j][k].getPosition().y, a[j][k].getPosition().x, rects[j][k].width,
                                           rects[j][k].height)) {
                                    /// if selected
                                    if (click) {
                                        target.useItem(i);
                                    }
                                    if (throwed)
                                        target.deleteItem(i, 1);
                                    int l = q + j * p;
                                    int t = z + k * o;
                                    select.setPosition(l, t);
                                    App.draw(select);

                                    mouseOver = true;
                                    isset[j][k] = true;
                                    a[j][k].setTextureRect(rects[3][0]);
                                    App.draw(a[j][k]);

                                    tooltip.setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
                                    std::string option;
                                    if (target.weaponiter == i) {
                                        option = " (Currently equipped)";
                                    }
                                    title.setString("Rare Rifle" + option);
                                    title.setPosition(sf::Mouse::getPosition().x + 10, sf::Mouse::getPosition().y + 10);
                                    desc.setPosition(sf::Mouse::getPosition().x + 10, sf::Mouse::getPosition().y + 40);
                                    flavor.setPosition(sf::Mouse::getPosition().x + 10,
                                                       sf::Mouse::getPosition().y + 100);
                                    std::ostringstream strem;
                                    strem << "Reserved for the best soldiers. Damage: " << target.inv[i].getEffectNum()
                                          << " HP.";
                                    desc.setString(strem.str());
                                    flavor.setString("Pretty hard to come by these days.");
                                } else {
                                    isset[j][k] = true;
                                    a[j][k].setTextureRect(rects[3][0]);
                                    App.draw(a[j][k]);
                                }
                                if (target.inv[i].quant > 1) {
                                    sf::Text quanttext;
                                    quanttext.setCharacterSize(40);
                                    quanttext.setFillColor(sf::Color::White);
                                    quanttext.setFont(arial);
                                    quanttext.setPosition(q + j * p + 230, z + k * o + 170);
                                    std::ostringstream strem;
                                    strem << target.inv[i].quant;
                                    quanttext.setString(strem.str());
                                    App.draw(quanttext);
                                }

                                goto contWeapon3;
                            }

                        }
                    }
                contWeapon3:
                    break;
                case 3:/// forf GUN
                    for (int k = 0; k < 3; k++) {
                        for (int j = 0; j < 5; j++) {
                            if (!isset[j][k]) {

                                if (inRect(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y,
                                           a[j][k].getPosition().y, a[j][k].getPosition().x, rects[j][k].width,
                                           rects[j][k].height)) {
                                    /// if selected
                                    if (click) {
                                        target.useItem(i);
                                    }
                                    if (throwed)
                                        target.deleteItem(i, 1);
                                    int l = q + j * p;
                                    int t = z + k * o;
                                    select.setPosition(l, t);
                                    App.draw(select);

                                    mouseOver = true;
                                    isset[j][k] = true;
                                    a[j][k].setTextureRect(rects[4][0]);
                                    App.draw(a[j][k]);

                                    tooltip.setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
                                    std::string option;
                                    if (target.weaponiter == i) {
                                        option = " (Currently equipped)";
                                    }
                                    title.setString("Mini RPG" + option);
                                    title.setPosition(sf::Mouse::getPosition().x + 10, sf::Mouse::getPosition().y + 10);
                                    desc.setPosition(sf::Mouse::getPosition().x + 10, sf::Mouse::getPosition().y + 40);
                                    flavor.setPosition(sf::Mouse::getPosition().x + 10,
                                                       sf::Mouse::getPosition().y + 100);
                                    std::ostringstream strem;
                                    strem << "Explodes on hit. Damage: " << target.inv[i].getEffectNum() << " HP.";
                                    desc.setString(strem.str());
                                    flavor.setString("Now with EXPLOSIONS!!!");
                                } else {
                                    isset[j][k] = true;
                                    a[j][k].setTextureRect(rects[4][0]);
                                    App.draw(a[j][k]);
                                }
                                if (target.inv[i].quant > 1) {
                                    sf::Text quanttext;
                                    quanttext.setCharacterSize(40);
                                    quanttext.setFillColor(sf::Color::White);
                                    quanttext.setFont(arial);
                                    quanttext.setPosition(q + j * p + 230, z + k * o + 170);
                                    std::ostringstream strem;
                                    strem << target.inv[i].quant;
                                    quanttext.setString(strem.str());
                                    App.draw(quanttext);
                                }

                                goto contWeapon4;
                            }

                        }
                    }
                contWeapon4:
                case 4:/// fiff GUN
                    for (int k = 0; k < 3; k++) {
                        for (int j = 0; j < 5; j++) {
                            if (!isset[j][k]) {

                                if (inRect(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y,
                                           a[j][k].getPosition().y, a[j][k].getPosition().x, rects[j][k].width,
                                           rects[j][k].height)) {
                                    /// if selected
                                    if (click) {
                                        target.useItem(i);
                                    }
                                    if (throwed)
                                        target.deleteItem(i, 1);
                                    int l = q + j * p;
                                    int t = z + k * o;
                                    select.setPosition(l, t);
                                    App.draw(select);

                                    mouseOver = true;
                                    isset[j][k] = true;
                                    a[j][k].setTextureRect(rects[0][1]);
                                    App.draw(a[j][k]);

                                    tooltip.setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
                                    std::string option;
                                    if (target.weaponiter == i) {
                                        option = " (Currently equipped)";
                                    }
                                    title.setString("Big RPG" + option);
                                    title.setPosition(sf::Mouse::getPosition().x + 10, sf::Mouse::getPosition().y + 10);
                                    desc.setPosition(sf::Mouse::getPosition().x + 10, sf::Mouse::getPosition().y + 40);
                                    flavor.setPosition(sf::Mouse::getPosition().x + 10,
                                                       sf::Mouse::getPosition().y + 100);
                                    std::ostringstream strem;
                                    strem << "Most powerful rifle in the game. Damage: " << target.inv[i].getEffectNum()
                                          << " HP.";
                                    desc.setString(strem.str());
                                    flavor.setString("The Ultimate Badassery");
                                } else {
                                    isset[j][k] = true;
                                    a[j][k].setTextureRect(rects[0][1]);
                                    App.draw(a[j][k]);
                                }
                                if (target.inv[i].quant > 1) {
                                    sf::Text quanttext;
                                    quanttext.setCharacterSize(40);
                                    quanttext.setFillColor(sf::Color::White);
                                    quanttext.setFont(arial);
                                    quanttext.setPosition(q + j * p + 230, z + k * o + 170);
                                    std::ostringstream strem;
                                    strem << target.inv[i].quant;
                                    quanttext.setString(strem.str());
                                    App.draw(quanttext);
                                }

                                goto contWeapon5;
                            }

                        }
                    }
                contWeapon5:
                    break;
                case 100:/// STANDARD MEDKIT
                    for (int k = 0; k < 3; k++) {
                        for (int j = 0; j < 5; j++) {
                            if (!isset[j][k]) {
                                if (inRect(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y,
                                           a[j][k].getPosition().y, a[j][k].getPosition().x, rects[j][k].width,
                                           rects[j][k].height)) {
                                    if (click) {
                                        target.useItem(i);
                                    }
                                    if (throwed)
                                        target.deleteItem(i, 1);
                                    int l = q + j * p;
                                    int t = z + k * o;
                                    select.setPosition(l, t);
                                    App.draw(select);

                                    mouseOver = true;
                                    isset[j][k] = true;
                                    a[j][k].setTextureRect(rects[1][0]);
                                    App.draw(a[j][k]);

                                    tooltip.setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
                                    title.setString("Standard Medkit");
                                    title.setPosition(sf::Mouse::getPosition().x + 10, sf::Mouse::getPosition().y + 10);
                                    desc.setPosition(sf::Mouse::getPosition().x + 10, sf::Mouse::getPosition().y + 40);
                                    flavor.setPosition(sf::Mouse::getPosition().x + 10,
                                                       sf::Mouse::getPosition().y + 100);
                                    std::ostringstream strem;
                                    strem << "Standard Training Equipment. Heals for " << target.inv[i].getEffectNum()
                                          << " HP.";
                                    desc.setString(strem.str());
                                    flavor.setString("Use it wisely.");
                                } else {
                                    isset[j][k] = true;
                                    a[j][k].setTextureRect(rects[1][0]);
                                    App.draw(a[j][k]);
                                }
                                if (target.inv[i].quant > 1) {
                                    sf::Text quanttext;
                                    quanttext.setCharacterSize(40);
                                    quanttext.setFillColor(sf::Color::White);
                                    quanttext.setFont(arial);
                                    quanttext.setPosition(q + j * p + 230, z + k * o + 170);
                                    std::ostringstream strem;
                                    strem << target.inv[i].quant;
                                    quanttext.setString(strem.str());
                                    App.draw(quanttext);
                                }

                                goto contMedkit;
                            }

                        }
                    }
                contMedkit:
                    break;
                default:
                    break;
            }
        }
        ///Code here ends
        /*for(int i=0; i<5; i++)
        {
            for(int j=0; j<3; j++)
            {
                App.draw(a[i][j]);
            }
        }*/
        if (mouseOver) {
            App.draw(tooltip);
            App.draw(title);
            App.draw(desc);
            App.draw(flavor);
        }
        App.display();
    }
}


void Station::explode(float x, float y) {
    Explosion a(x, y);
    a.s.setTexture(this->explosionTexture);
    this->exp.push_back(a);
    if (!soundEnabled)
        return;
    sf::Sound b;
    b.setBuffer(explos);
    this->blasts.push_back(b);
    this->blasts[this->blasts.size() - 1].play();
}

void Station::endapp() {
    ///maybe some outro
    App.close();
}

void Station::intro() {
    ///something
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../sounds/intro.wav"))
        return;
    sf::Sound intr;
    intr.setBuffer(buffer);
    intr.play();
    sf::Texture intrt;
    if (!intrt.loadFromFile("../img/timing.png"))
        return;
    sf::Sprite tim;
    tim.setTexture(intrt);
    sf::Text tet;
    tet.setPosition(this->width * 74 / 100, this->height * 44 / 100);
    sf::Font games;
    games.loadFromFile("../fonts/games.ttf");
    tet.setFont(games);
    tet.setCharacterSize(100);
    tet.setFillColor(sf::Color::White);
    //int b=700;
    int state = 0;
    int ox = 50;
    sf::Time as;
    as = sf::milliseconds(14);
    while (true) {
        sf::Event event;
        while (App.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    App.close();
                    return;
                    break;
                default:
                    break;
            }
        }
        if (ox == 50) {
            switch (state) {
                case 0:
                    tet.setString("G");
                    break;
                case 1:
                    tet.setString("Ga");
                    break;
                case 2:
                    tet.setString("Gam");
                    break;
                case 3:
                    tet.setString("Game");
                    break;
                case 4:
                    tet.setString("Games");
                    break;
                case 7:
                    return;
                default:
                    break;
            }
            state++;
            ox = 0;
        }
        ox++;

        App.draw(tim);
        App.draw(tet);
        App.display();
        sf::sleep(as);
    }


}

int Station::pause() {

    menusic.openFromFile("../sounds/mainmenu.wav");
    menusic.setLoop(true);
    menusic.play();
    sf::Sprite pau, opt, ext, men;
    men.setTexture(this->pauseMenuTexture);
    opt.setTexture(this->optionsButtonPauseMenuTexture);
    pau.setTexture(this->pauseMenuBackgroundTexture);
    ext.setTexture(this->pauseExitTexture);
    if (this->isUnsized) {
        men.setScale(8 / 15.f, 8 / 15.f);
        opt.setScale(8 / 15.f, 8 / 15.f);
        ext.setScale(8 / 15.f, 8 / 15.f);
    }
    int lef = width * 2980 / 10000;
    int righ = width * 655 / 1000;
    int top1 = height * 3650 / 10000;
    int top2 = height * 5050 / 10000;
    int top3 = height * 6465 / 10000;
    int bot1 = height * 500 / 1000;
    int bot2 = height * 600 / 1000;
    int bot3 = height * 750 / 1000;
    ext.setPosition(lef + 2, top1);
    opt.setPosition(lef + 1, top2);
    men.setPosition(lef, top3);
    while (true) {
        sf::Event event;
        bool click = false;
        while (App.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    App.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    click = true;
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Tab) {
                        menusic.stop();
                        return 1;
                    }
                    if (event.key.code == sf::Keyboard::Escape) {
                        menusic.stop();
                        return 1;
                    }
                    break;
                default:
                    break;
            }
        }
        App.clear();
        App.draw(pau);
        if (sf::Mouse::getPosition().x > lef && sf::Mouse::getPosition().x < righ &&
            sf::Mouse::getPosition().y > top1 && sf::Mouse::getPosition().y < bot1) {
            if (click) {
                menusic.stop();
                return 2;
            }
            App.draw(ext);
        }
        if (sf::Mouse::getPosition().x > lef && sf::Mouse::getPosition().x < righ &&
            sf::Mouse::getPosition().y > top2 && sf::Mouse::getPosition().y < bot2) {
            if (click) {
                options(1);
            }
            App.draw(opt);
        }
        if (sf::Mouse::getPosition().x > lef && sf::Mouse::getPosition().x < righ &&
            sf::Mouse::getPosition().y > top3 && sf::Mouse::getPosition().y < bot3) {
            if (click) {

                menusic.stop();
                return 0;
            }
            App.draw(men);

        }

        App.display();
    }

    menusic.stop();
    return 1;
}

void Station::toggleCheatsEnabled() {
    cheatsEnabled = !cheatsEnabled;
}

void Station::toggleSoundEnabled() {
    if (!soundEnabled) {
        soundEnabled = true;
        menusic.setVolume(100);
        menusic.play();
    } else {
        soundEnabled = false;
        menusic.pause();
        menusic.setVolume(0);
        blasts.clear();
    }
}

void Station::options(int source) {
    ///0 - main, 1 - pause
    /*if(source==0)
    {*/
    ///mainmenu
    sf::Sprite bg(this->optionsMenuBackgroundTexture);

    sf::Sprite men, strt, optns, ext;
    men.setTexture(this->mainMenuTexture);
    strt.setTexture(this->newGameTexture);
    optns.setTexture(this->optionsButtonMainMenuTexture);
    ext.setTexture(this->exitTexture);
    int lef = width * 2705 / 10000;
    int righ = width * 655 / 1000;
    int top1 = height * 3851 / 10000;
    int top2 = height * 5904 / 10000;
    int top3 = height * 7811 / 10000;
    int bot1 = height * 500 / 1000;
    int bot2 = height * 700 / 1000;
    int bot3 = height * 950 / 1000;
    strt.setPosition(lef, top1);
    optns.setPosition(lef, top2);
    ext.setPosition(lef, top3);
    sf::Text a, b, c;
    sf::Font games;
    games.loadFromFile("../fonts/games.ttf");
    a.setFont(games);
    b.setFont(games);
    c.setFont(games);
    a.setCharacterSize(50);
    b.setCharacterSize(50);
    c.setCharacterSize(50);
    a.setPosition(lef * 1.3, top1 * 1.1);
    b.setPosition(lef * 1.3, top2 * 1.1);
    c.setPosition(lef * 1.3, top3 * 1.1);

    c.setString("BACK");
    while (true) {
        sf::Event event;
        bool click = false;
        while (App.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    App.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    click = true;
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Tab) {

                        return;
                    }

                default:
                    break;
            }
        }
        App.clear();
        App.draw(bg);
        sf::String czits;
        if (cheatsEnabled)
            czits = "Cheats are ON";
        else
            czits = "Cheats are OFF";
        sf::String saunds;
        if (soundEnabled)
            saunds = "Sounds are ON";
        else
            saunds = "Sounds are OFF";
        a.setString(czits);
        b.setString(saunds);
        App.draw(a);
        App.draw(b);
        App.draw(c);
        if (sf::Mouse::getPosition().x > lef && sf::Mouse::getPosition().x < righ &&
            sf::Mouse::getPosition().y > top1 && sf::Mouse::getPosition().y < bot1) {
            if (click) {
                toggleCheatsEnabled();
            }

        }
        if (sf::Mouse::getPosition().x > lef && sf::Mouse::getPosition().x < righ &&
            sf::Mouse::getPosition().y > top2 && sf::Mouse::getPosition().y < bot2) {
            if (click) {
                toggleSoundEnabled();
            }

        }
        if (sf::Mouse::getPosition().x > lef && sf::Mouse::getPosition().x < righ &&
            sf::Mouse::getPosition().y > top3 && sf::Mouse::getPosition().y < bot3) {
            if (click) {
                /**sf::Time time=sf::milliseconds(1000);
                sf::sleep(time);*/
                return;
            }

        }
        App.display();
    }
    /*}
    else
    {
        ///pausemenu
    }*/
}

bool Station::mainmenu() {

    menusic.openFromFile("../sounds/mainmenu.wav");
    menusic.setLoop(true);
    menusic.play();
    sf::Sprite men, strt, optns, ext;
    men.setTexture(this->mainMenuTexture);
    strt.setTexture(this->newGameTexture);
    optns.setTexture(this->optionsButtonMainMenuTexture);
    ext.setTexture(this->exitTexture);
    if (this->isUnsized) {
        strt.setScale(8 / 15.f, 8 / 15.f);
        optns.setScale(8 / 15.f, 8 / 15.f);
        ext.setScale(8 / 15.f, 8 / 15.f);
    }
    int lef = width * 2705 / 10000;
    int righ = width * 655 / 1000;
    int top1 = height * 2851 / 10000;
    int top2 = height * 4704 / 10000;
    int top3 = height * 6511 / 10000;
    int bot1 = height * 400 / 1000;
    int bot2 = height * 600 / 1000;
    int bot3 = height * 800 / 1000;
    strt.setPosition(lef, top1);
    optns.setPosition(lef, top2);
    ext.setPosition(lef, top3);
    while (true) {
        sf::Event event;
        bool click = false;
        while (App.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    App.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    click = true;
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Tab) {
                        menusic.stop();
                        return 0;
                    }

                default:
                    break;
            }
        }
        App.clear();
        App.draw(men);
        if (sf::Mouse::getPosition().x > lef && sf::Mouse::getPosition().x < righ &&
            sf::Mouse::getPosition().y > top1 && sf::Mouse::getPosition().y < bot1) {
            if (click) {
                goto startgame;
            }
            App.draw(strt);
        }
        if (sf::Mouse::getPosition().x > lef && sf::Mouse::getPosition().x < righ &&
            sf::Mouse::getPosition().y > top2 && sf::Mouse::getPosition().y < bot2) {
            if (click) {
                options(0);
                click = false;
            }
            App.draw(optns);
        }
        if (sf::Mouse::getPosition().x > lef && sf::Mouse::getPosition().x < righ &&
            sf::Mouse::getPosition().y > top3 && sf::Mouse::getPosition().y < bot3) {
            if (click) {
                menusic.stop();
                return false;
            }
            App.draw(ext);
        }
        App.display();
    }
    startgame:
    menusic.stop();
    return true;
}

