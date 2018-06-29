#include <SFML/Audio.hpp>
#include <cmath>
#include <sstream>
#include "Models/Menu.h"
#include "FloorTile.h"
#include "Room.h"
#include "GameState.h"
#include "TileDrop.h"
#include "Explosion.h"

#define n 16
#define m 6
#define PI 3.1415926

/**
00 01 02 03 04
05 06 07 08 09
10 11 12 13 14
15 16 17 18 19
20 21 22 23 24
*/

int currentpos;
bool vis[25];
int viscount;
namespace {

    sf::Vector3f to3D(sf::Vector2f toConvert) {
        return {toConvert.x, toConvert.y, 0};
    }

    double dist(int x1, int y1, int x2, int y2) {
        return std::sqrt(abs(x1 - x2) * abs(x1 - x2) + abs(y1 - y2) * abs(y1 - y2)) / 100;
    }

    int square2x(FloorTile floortile[n][m], double x_f) {
        int x = static_cast<int>(x_f);
        for (int i = 0; i < n; i++) {
            if ((floortile[i][0].x < x and floortile[i][0].x + 100 > x) or floortile[i][0].x == x)
                return i;
        }
        return 0;
    }

    int square2y(FloorTile floortile[n][m], double y_f) {
        int y = static_cast<int>(y_f);
        for (int i = 0; i < m; i++) {
            if ((floortile[0][i].y < y and floortile[0][i].y + 104 > y) or floortile[i][0].y == y)
                return i;
        }
        return 0;
    }


    void changeRoom(Room &currentroom, int dir, std::vector<Room> section)///0 - up, 1 - right, 2 - down, 3 - left
    {
        if (currentpos == 2 and dir == 0) {
            ///BOSSROOM SPAWN
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    currentroom.floortile[i][j].walkable = true;

                }
            }
            currentroom.type = 1;
            currentpos = -1;
            return;
        }
        currentroom.type = 0;
        int a = 0;
        switch (dir) {
            case 0:
                if (currentpos < 5)
                    return;
                a = -5;
                break;
            case 1:
                if (currentpos == 24)
                    return;
                a = 1;
                break;
            case 2:
                if (currentpos > 19)
                    return;
                a = 5;
                break;
            case 3:
                if (!currentpos or currentpos == 5 or currentpos == 10 or currentpos == 15 or currentpos == 20)
                    return;
                a = -1;
                break;
            default:
                break;
        }
        currentroom.dbottom = section[currentpos + a].dbottom;
        currentroom.dtop = section[currentpos + a].dtop;
        currentroom.dleft = section[currentpos + a].dleft;
        currentroom.dright = section[currentpos + a].dright;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                currentroom.floortile[i][j].x = section[currentpos + a].floortile[i][j].x;
                currentroom.floortile[i][j].y = section[currentpos + a].floortile[i][j].y;
                currentroom.floortile[i][j].type = section[currentpos + a].floortile[i][j].type;
                currentroom.floortile[i][j].walkable = section[currentpos + a].floortile[i][j].walkable;
                if (currentroom.floortile[i][j].type == 0)
                    currentroom.floortile[i][j].sprite.setTexture(currentroom.floort);
                if (currentroom.floortile[i][j].type == 1)
                    currentroom.floortile[i][j].sprite.setTexture(currentroom.chestt);
            }
        }

        section[currentpos].enem.erase(section[currentpos].enem.begin(), section[currentpos].enem.end());

        while (!currentroom.enem.empty()) {
            section[currentpos].enem.push_back(currentroom.enem[currentroom.enem.size() - 1]);
            currentroom.enem.erase(currentroom.enem.end());
        }
        for (const auto &i : section[currentpos + a].enem) {
            currentroom.enem.push_back(i);
        }
        while (!currentroom.drops.empty()) {
            section[currentpos].drops.push_back(currentroom.drops[currentroom.drops.size() - 1]);
            currentroom.drops.erase(currentroom.drops.end());
        }
        for (const auto &drop : section[currentpos + a].drops) {
            currentroom.drops.push_back(drop);
        }
        currentroom.proj.erase(currentroom.proj.begin(), currentroom.proj.end());
        currentpos += a;
        if (!vis[currentpos]) ///MOB SPAWNING
        {
            vis[currentpos] = true;
            int t = viscount / 5;
            ///int b=viscount;
            int u = rand() % 5 + 5;
            int c = 0;
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < m; k++) {
                    int d = rand() % 10;
                    if (currentroom.floortile[j][k].walkable and !d) {
                        c++;
                        currentroom.spawn_enemy(currentroom.floortile[j][k].x + 50, currentroom.floortile[j][k].y + 52,
                                                t);
                    }
                    if (c == u)
                        goto lolz;
                }
            }
            lolz:

            viscount++;
        }
    }
} //namespace
int main_old() {
    GameState game;


    Menu menu(GameOption("Cheats", OptionState::OFF));





    /*if(2==game.pause())
    {
        game.window.close();
        return 0;
    }*/
    srand(time(0));
    int fixw = 170;
    int fixh = 291;
    if (game.isUnsized) {
        fixw = 91;
        fixh = 155;
    }
    sf::Sprite loadin;
    loadin.setTexture(game.loadingTexture);



    ///game.intro();//<<<<<<<<<<<<<<<<<<<<<<<

    if (game.unLoaded or !game.mainMenu()) {
        game.window.close();
        return 0;
    }

    game.blasts.clear();
    game.exp.clear();
    respawn:
    viscount = 0;
    currentpos = 0;
    for (bool &vi : vis) {
        vi = false;
    }
    //bool bossopen=false;
    sf::Sprite prog, bossroom;


    bossroom.setTexture(game.bossRoomTexture);

    prog.setTexture(game.subliminalImageTexture);


    sf::IntRect smals[6];
    int its = 0;
    /*for(int k=0; k<3; k++)
    {*/
    for (int j = 0; j < 6; j++) {
        its++;
        smals[its].height = 47;
        smals[its].width = 60;
        smals[its].top = 0 * smals[its].height;
        smals[its].left = j * smals[its].width;
    }
    smals[6].top = smals[6].height;
    smals[6].left = 0;
    //}

    sf::IntRect shotcolors[6];
    for (int i = 0; i < 6; i++) {
        shotcolors[i].height = 15;
        shotcolors[i].width = 3;
        shotcolors[i].top = 0;
        shotcolors[i].left = i * 3;
    }
    sf::IntRect exprecto[9];
    for (int i = 0; i < 9; i++) {
        exprecto[i].height = 21;
        exprecto[i].width = 21;
        exprecto[i].top = 0;
        exprecto[i].left = i * 20;
    }


    currentpos = 12;
    vis[currentpos] = true;
    viscount = 1;

    // game.window.setMouseCursorVisible(false);
    sf::Music lodin;
    lodin.openFromFile("../sounds/loop.wav");
    if (game.soundEnabled)
        lodin.play();
    game.window.draw(loadin);
    game.window.display();


    //uniform_int_distribution<int> a(0,1);
    Character playa;
    boss mainboss;
    playa.addItem(4, 0, 100, 1);
    playa.addItem(100, 1, 40, 1);
    /*playa.addItem(0,0,41);*/


    playa.setOrigin(game.playerTexture.getSize().y / 2, game.playerTexture.getSize().y * 35 / 50);
    playa.setPosition(game.width / 2, game.height / 2);
    mainboss.setPosition(game.width / 2, game.height / 2);
    mainboss.setTexture(game.bossTexture);

    std::vector <Room> section;
    for (int i = 0; i < 25; i++) {
        section.emplace_back(game);
    }
    for (int i = 0; i < 5; i++) {
        section[i].dtop = false;
    }
    for (int i = 0; i < 21; i += 5)
        section[i].dleft = false;
    for (int i = 20; i < 25; i++)
        section[i].dbottom = false;
    for (int i = 4; i < 25; i += 5)
        section[i].dright = false;

    sf::Sprite weapon, endScreen;
    endScreen.setTexture(game.endScreenTexture);
    endScreen.setPosition(0, 0);
    sf::Text endText;
    endText.setFont(game.arial);
    endText.setCharacterSize(100);
    endText.setFillColor(sf::Color::Cyan);


    sf::Texture wt;
    wt.loadFromFile("../img/weapon.png");
    if (game.isUnsized) {
        weapon.scale(wt.getSize().x * 1024.f / 1920.f, wt.getSize().x * 576.f / 1080.f);
    }
    sf::IntRect weaponRects[6];
    for (int i = 0; i < 6; i++) {
        weaponRects[i].height = 79;
        weaponRects[i].width = 224;
        weaponRects[i].left = 0;
        weaponRects[i].top = i * 79;
    }

    weapon.setTexture(wt);

    weapon.setPosition(game.width / 100.f, game.height / 32.f);
    sf::Sprite bg, gui;
    sf::IntRect r1(0, 0, 50, 50);
    sf::IntRect r2(0, 50, 50, 50);
    sf::IntRect r3(50, 0, 50, 50);
    sf::IntRect r4(50, 50, 50, 50);

    sf::Clock bossClock;
    sf::Color frame;
    sf::Text debug;
    sf::Text hpbar;
    debug.setFillColor(sf::Color::White);
    debug.setPosition(0, game.height * 97 / 100);
    hpbar.setFillColor(sf::Color::White);
    hpbar.setPosition(game.width * 255 / 1000, game.height * 25 / 1000);
    int mx, my;
    sf::String debugString;
    sf::String hpText;
    std::string mxs, mys, angs;
    Room currentroom(game);

    //currentroom.changeTo( section[5][5], section[5][5].floortile);
    //currentroom.loadroom(game.width,game.height);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            //currentroom.floortile[i][j].changeTo(ox.floortile[i][j]);
            currentroom.floortile[i][j].x = section[12].floortile[i][j].x;
            currentroom.floortile[i][j].y = section[12].floortile[i][j].y;
            currentroom.floortile[i][j].type = section[12].floortile[i][j].type;
            currentroom.floortile[i][j].walkable = section[12].floortile[i][j].walkable;
            if (currentroom.floortile[i][j].type == 0)
                currentroom.floortile[i][j].sprite.setTexture(currentroom.floort);
            if (currentroom.floortile[i][j].type == 1)
                currentroom.floortile[i][j].sprite.setTexture(currentroom.chestt);
        }
    }
    sf::Sprite db(game.doorBottomTexture);
    sf::Sprite dt(game.doorTopTexture);
    sf::Sprite dr(game.doorRightTexture);
    sf::Sprite dl(game.doorLeftTexture);
    sf::Sound sound;
    sf::Clock manualSpawnTimer;
    bg.setTexture(game.backgroundTexture);
    gui.setTexture(game.guiTexture);
    playa.setTexture(game.playerTexture);
    debug.setFont(game.arial);
    hpbar.setFont(game.arial);
    game.window.setFramerateLimit(70);
    sf::Color dor(111, 111, 111);
    int co = 0;
    lodin.pause();
    bool bossopen = false;
    int gameended = 0;

    sf::Music battle;
    battle.openFromFile("../sounds/battle.wav");
    battle.setLoop(true);
    if (game.soundEnabled) {
        battle.play();
    }
    while (game.window.isOpen()) {
    ///**************************************************************************************************************************GAME LOOP OPEN
        co++;
        sf::Event event;
        while (game.window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    game.window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (gameended) {
                        if (!game.soundEnabled)
                            battle.pause();
                        if (!game.mainMenu()) {
                            game.endapp();
                            return 0;
                        } else {
                            goto respawn;
                        }
                    }
                    if (event.key.code == sf::Keyboard::Escape and !gameended) {
                        if (!game.soundEnabled)
                            battle.pause();
                        int pauseReturnCode = game.pause();
                        if (!pauseReturnCode) {
                            if (!game.mainMenu()) {
                                game.endapp();
                                return 0;
                            } else {
                                goto respawn;
                            }
                        } else if (pauseReturnCode == 2) {
                            game.endapp();
                            continue;
                        } else if (game.soundEnabled)
                            battle.play();
                    }
                    if (event.key.code == sf::Keyboard::E and !gameended) {
                        game.inventory(playa);
                    }
                    if (game.cheatsEnabled) {
                        if (event.key.code == sf::Keyboard::Up and currentroom.type != 1 and currentpos != 2) {
                            changeRoom(currentroom, 0, section);
                        }
                        if (event.key.code == sf::Keyboard::Down and currentroom.type != 1) {
                            changeRoom(currentroom, 2, section);
                        }
                        if (event.key.code == sf::Keyboard::Left and currentroom.type != 1) {
                            changeRoom(currentroom, 3, section);
                        }
                        if (event.key.code == sf::Keyboard::Right and currentroom.type != 1) {
                            changeRoom(currentroom, 1, section);
                        }
                        if (event.key.code == sf::Keyboard::I) {
                            playa.toggleInvincible();
                        }
                        if (event.key.code == sf::Keyboard::Q and currentroom.type != 1 and !currentroom.enem.empty()) {
                            game.inventory(currentroom.enem[0]);
                        }
                        if (event.key.code == sf::Keyboard::P and currentroom.type != 1) {
                            viscount = 25;
                        }
                        if (event.key.code == sf::Keyboard::K and currentroom.type != 1) {
                            currentroom.enem.erase(currentroom.enem.begin(), currentroom.enem.end());
                        }
                    }
                default:
                    break;
            }
        }
        if (!gameended and viscount == 25 and currentroom.type != 1 and !bossopen) {
            int numberOfVisitedRooms = 0;
            for (int i = 0; i < 25; i++) {
                if (!section[i].enem.empty())
                    break;
                numberOfVisitedRooms++;
            }
            if (numberOfVisitedRooms == 25) {
                bossopen = true;
                section[2].dtop = true;
            }
        }


        if (!gameended)
            weapon.setTextureRect(weaponRects[playa.inv[playa.weaponiter].getId()]);

        ///WALKING PLAYER
        if (!gameended) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and (playa.canWalkUp(currentroom.floortile, game)))
                playa.move(0, -playa.speed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and currentroom.dtop and
                game.dti.getPixel(static_cast<unsigned int>(playa.getPosition().x),
                                  static_cast<unsigned int>(playa.getPosition().y - 15)) == dor and
                currentroom.type != 1) {
                changeRoom(currentroom, 0, section);
                playa.move(0, 580);
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and playa.canWalkDown(currentroom.floortile, game))
                playa.move(0, playa.speed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and currentroom.dbottom and
                (game.dbi.getPixel(static_cast<unsigned int>(playa.getPosition().x),
                                   static_cast<unsigned int>(playa.getPosition().y + 20)) == dor) and
                currentroom.type != 1) {
                changeRoom(currentroom, 2, section);
                playa.move(0, -580);
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and (playa.canWalkLeft(currentroom.floortile, game)))
                playa.move(-playa.speed, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and currentroom.dleft and
                game.dli.getPixel(static_cast<unsigned int>(playa.getPosition().x - 15),
                                  static_cast<unsigned int>(playa.getPosition().y)) == dor and currentroom.type != 1) {
                changeRoom(currentroom, 3, section);
                playa.move(0, 1500);
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and (playa.canWalkRight(currentroom.floortile, game)))
                playa.move(playa.speed, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and currentroom.dright and
                game.dri.getPixel(static_cast<unsigned int>(playa.getPosition().x + 20),
                                  static_cast<unsigned int>(playa.getPosition().y)) == dor and currentroom.type != 1) {
                changeRoom(currentroom, 1, section);
                playa.move(0, 1500);
            }


            if (playa.health <= 0) {
                gameended = 1;
            }

            ///MOUSE ROTAtION
            playa.rotatexy(sf::Mouse::getPosition(game.window));

            ///Debug Mouse Text
            /*ostringstream convert;
            convert<<currenttile.first;
            mxs=convert.str();
            convert.str(std::string());
            convert<<currenttile.second;
            mys=convert.str();
            convert.str(std::string());
            convert<<playa.orient;
            angs=convert.str();
            convert.str(std::string());
            debugString+=mxs+", "+mys+", angle: "+angs;
            debug.setString(debugString);*/
            ///debugs.clear();
            /*if(currentroom.dbottom)
                debugString+="bot, ";
            if(currentroom.dtop)
                debugString+="top, ";
            if(currentroom.dleft)
                debugString+="left, ";
            if(currentroom.dright)
                debugString+="right, ";*/
            std::ostringstream convert;
            /**convert<<square2x(currentroom.floortile,playa.x);
            debugs+=convert.str();
            debugs+=", ";
            convert.str(std::string());
            convert<<square2y(currentroom.floortile,playa.y);
            debugs+=convert.str();
            debugs+=", ";
            convert.str(std::string());
            debug.setString(debugs);*/
            ///Debug Mouse Text End   IF UNCOMMENTING, DRAWING IS COMMENTED TOO

            ///HP TEXT
            //ostringstream convert;
            convert << playa.health;
            hpText = convert.str();
            convert.str(std::string());
            hpbar.setString(hpText);

            ///MANUAL SPAWNING
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) and currentroom.type != 1 and game.cheatsEnabled) {
                if (manualSpawnTimer.getElapsedTime().asSeconds() > 1) {
                    currentroom.spawn_enemy(mx, my, 0);
                    currentroom.enem[currentroom.enem.size() - 1].rotatexy(playa.getPosition());
                    manualSpawnTimer.restart();
                }
            }

            ///SHOOTING
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (playa.shoot(currentroom.proj, mx, my)) {
                    currentroom.proj[currentroom.proj.size() - 1].C.setTexture(currentroom.sht);
                    currentroom.proj[currentroom.proj.size() - 1].C.setTextureRect(
                            shotcolors[currentroom.proj[currentroom.proj.size() - 1].type]);

                    if (game.soundEnabled) {
                        sound.setBuffer(game.shots);
                        sound.setPosition(playa.getPosition().x, playa.getPosition().y, 0);
                        sound.play();
                    }
                }
            }


            ///DRAW BACKGROUND AND BOSS HANDLING
            if (currentroom.type != 1)
                game.window.draw(bg);
            else {


                if (mainboss.health <= 0) {
                    if (mainboss.destroystate == 0)
                        bossClock.restart();
                    mainboss.destroystate++;
                    if (co == 2 or co == 4)
                        game.explode(mainboss.getPosition().x - 50 + rand() % 100 - 50,
                                     mainboss.getPosition().y + rand() % 100 - 50);
                    if (bossClock.getElapsedTime().asSeconds() > 4) {
                        gameended = 2;
                        ///game.endscreen();
                    }
                }
                if (mainboss.shoot(currentroom.proj, 0, 0))///boss shooting
                {
                    currentroom.proj[currentroom.proj.size() - 1].C.setTexture(currentroom.sht);
                    currentroom.proj[currentroom.proj.size() - 1].C.setTextureRect(
                            shotcolors[currentroom.proj[currentroom.proj.size() - 1].type]);
                    if (game.soundEnabled) {
                        sound.setBuffer(game.shots);
                        sound.setPosition(to3D(mainboss.getPosition()));
                        sound.play();
                    }
                    mainboss.shoot(currentroom.proj, 0, game.height, true);

                    currentroom.proj[currentroom.proj.size() - 1].C.setTexture(currentroom.sht);
                    currentroom.proj[currentroom.proj.size() - 1].C.setTextureRect(
                            shotcolors[currentroom.proj[currentroom.proj.size() - 1].type]);
                    if (game.soundEnabled) {
                        sound.setBuffer(game.shots);
                        sound.setPosition(to3D(mainboss.getPosition()));
                        sound.play();
                    }
                    mainboss.shoot(currentroom.proj, game.width, game.height, true);


                    currentroom.proj[currentroom.proj.size() - 1].C.setTexture(currentroom.sht);
                    currentroom.proj[currentroom.proj.size() - 1].C.setTextureRect(
                            shotcolors[currentroom.proj[currentroom.proj.size() - 1].type]);
                    if (game.soundEnabled) {
                        sound.setBuffer(game.shots);
                        sound.setPosition(to3D(mainboss.getPosition()));
                        sound.play();

                    }
                    mainboss.shoot(currentroom.proj, game.width, 0, true);
                    currentroom.proj[currentroom.proj.size() - 1].C.setTexture(currentroom.sht);
                    currentroom.proj[currentroom.proj.size() - 1].C.setTextureRect(
                            shotcolors[currentroom.proj[currentroom.proj.size() - 1].type]);
                    if (game.soundEnabled) {
                        sound.setBuffer(game.shots);
                        sound.setPosition(to3D(mainboss.getPosition()));
                        sound.play();
                    }
                    if (rand() % 10 > 8) {
                        currentroom.spawn_enemy(mainboss.getPosition().x + rand() % 500 - 250,
                                                mainboss.getPosition().y + rand() % 500 - 250, 4);
                    }
                }
                game.window.draw(bossroom);
                game.window.draw(mainboss);
            }
        }

        ///DRAW FLOOR
        if (currentroom.type != 1) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    game.window.draw(currentroom.floortile[i][j].sprite);
                }
            }
        }


        if (!gameended) {
            ///PROJECTILE HANDLING
            for (int unsigned i = 0; i < currentroom.proj.size(); ++i) {
                if (currentroom.proj[i].canWalk(currentroom.floortile, game)) {
                    currentroom.proj[i].y += currentroom.proj[i].ay;
                    currentroom.proj[i].x -= currentroom.proj[i].ax;
                } else {
                    if (currentroom.proj[i].type > 2) {
                        game.explode(currentroom.proj[i].x, currentroom.proj[i].y);
                    }
                    currentroom.proj.erase(currentroom.proj.begin() + i);
                    continue;
                }


                currentroom.proj[i].C.setPosition(currentroom.proj[i].x, currentroom.proj[i].y);
                game.window.draw(currentroom.proj[i].C);
                if (std::sqrt(((currentroom.proj[i].x - playa.getPosition().x) *
                               (currentroom.proj[i].x - playa.getPosition().x)) +
                              ((currentroom.proj[i].y - playa.getPosition().y) *
                               (currentroom.proj[i].y - playa.getPosition().y))) < 15 &&
                    currentroom.proj[i].orig != &playa && !playa.invincible and !playa.red) {
                    playa.setColor(sf::Color(255, 0, 0));
                    hpbar.setFillColor(sf::Color(255, 0, 0));
                    playa.red = true;

                    playa.move(3, 3);
                    playa.ifshot.restart();
                    playa.DealDamage(currentroom.proj[i].damage);

                    if (currentroom.proj[i].type > 2) {
                        game.explode(currentroom.proj[i].x, currentroom.proj[i].y);
                    }
                    currentroom.proj.erase(currentroom.proj.begin() + i);
                }
                if (currentroom.type == 1) {
                    mainboss.move(0, -50);
                    if (sqrt(((currentroom.proj[i].x - mainboss.getPosition().x) *
                              (currentroom.proj[i].x - mainboss.getPosition().x)) +
                             ((currentroom.proj[i].y - mainboss.getPosition().y) *
                              (currentroom.proj[i].y - mainboss.getPosition().y))) < 150 &&
                        currentroom.proj[i].orig == &playa && !mainboss.invincible and !mainboss.red) {
                        mainboss.setColor(sf::Color(255, 0, 0));

                        mainboss.red = true;

                        mainboss.move(3, 3);
                        mainboss.ifshot.restart();
                        mainboss.DealDamage(currentroom.proj[i].damage);

                        if (currentroom.proj[i].type > 2) {
                            game.explode(currentroom.proj[i].x, currentroom.proj[i].y);
                        }
                        currentroom.proj.erase(currentroom.proj.begin() + i);
                    }
                    mainboss.move(0, 50);
                }
                if (currentroom.proj[i].x > game.width || !currentroom.proj[i].x ||
                    currentroom.proj[i].y > game.height ||
                    !currentroom.proj[i].y) {

                    if (currentroom.proj[i].type > 2) {
                        game.explode(currentroom.proj[i].x, currentroom.proj[i].y);
                    }
                    currentroom.proj.erase(currentroom.proj.begin() + i);
                }
            }

            ///ENEMIES HANDLING
            for (int unsigned i = 0; i < currentroom.enem.size(); ++i) {

                if (currentroom.enem[i].canSee(currentroom.floortile, playa.getPosition())) {
                    /*int mox=0,moy=0;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                        moy=-25*dist(playa.x,playa.y,currentroom.enem[i].x,currentroom.enem[i].y);
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                        moy=25*dist(playa.x,playa.y,currentroom.enem[i].x,currentroom.enem[i].y);
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        mox=-25*dist(playa.x,playa.y,currentroom.enem[i].x,currentroom.enem[i].y);
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                        mox=25*dist(playa.x,playa.y,currentroom.enem[i].x,currentroom.enem[i].y);*/
                    currentroom.enem[i].rotatexy(playa.getPosition());///ROTATING ENEMIES
                    if (currentroom.enem[i].shoot(currentroom.proj, playa.getPosition())) {
                        currentroom.proj[currentroom.proj.size() - 1].C.setTexture(currentroom.sht);
                        currentroom.proj[currentroom.proj.size() - 1].C.setTextureRect(
                                shotcolors[currentroom.proj[currentroom.proj.size() - 1].type]);
                        if (game.soundEnabled) {
                            sound.setBuffer(game.shots);
                            sound.setPosition(to3D(currentroom.enem[i].getPosition()));
                            sound.play();
                        }
                    }
                    currentroom.enem[i].ay =
                            std::sin(currentroom.enem[i].orient * PI / 180) *
                            currentroom.enem[i].speed;///GIVING 'EM DELTA Y
                    if (!currentroom.enem[i].canWalkDown(currentroom.floortile, game) and currentroom.enem[i].ay < 0)
                        currentroom.enem[i].ay = 0;
                    ///CHECKING  IF THEY CAN WALK THIS WAY
                    if (!currentroom.enem[i].canWalkUp(currentroom.floortile, game) and currentroom.enem[i].ay > 0)
                        currentroom.enem[i].ay = 0;

                    currentroom.enem[i].ax =
                            std::cos(currentroom.enem[i].orient * PI / 180) *
                            currentroom.enem[i].speed;///GIVING 'EM DELTA X
                    if (!currentroom.enem[i].canWalkRight(currentroom.floortile, game) and currentroom.enem[i].ax < 0)
                        currentroom.enem[i].ax = 0;
                    ///CHECKING  IF THEY CAN WALK THIS WAY
                    if (!currentroom.enem[i].canWalkLeft(currentroom.floortile, game) and currentroom.enem[i].ax > 0)
                        currentroom.enem[i].ax = 0;

                    if (currentroom.enem[i].ay != 0 or currentroom.enem[i].ax != 0) {
                        for (int unsigned j = 0; j < currentroom.enem.size(); ++j) {
                            if (j == i)
                                continue;
                            if (sqrt(((currentroom.enem[j].getPosition().x - (currentroom.enem[i].getPosition().x)) *
                                      (currentroom.enem[j].getPosition().x - (currentroom.enem[i].getPosition().x))) +
                                     ((currentroom.enem[j].getPosition().y - (currentroom.enem[i].getPosition().y)) *
                                      (currentroom.enem[j].getPosition().y - (currentroom.enem[i].getPosition().y)))) <
                                30) {
                                currentroom.enem[i].ax = 0;
                                currentroom.enem[i].ay = 0;
                            }

                        }
                    }


                    if (currentroom.enem[i].getPosition().x - playa.getPosition().x > 100 ||
                        playa.getPosition().x - currentroom.enem[i].getPosition().x > 100 ||
                        currentroom.enem[i].getPosition().y - playa.getPosition().y > 100 ||
                        playa.getPosition().y - currentroom.enem[i].getPosition().y > 100) {
                        currentroom.enem[i].move(-currentroom.enem[i].ax, 0);

                        currentroom.enem[i].move(0, -currentroom.enem[i].ay);
                    }
                } else {
                    int dir = currentroom.enem[i].returnpath(currentroom.floortile, playa.getPosition());
                    if (dir != 4) {
                        int a = square2x(currentroom.floortile, currentroom.enem[i].getPosition().x);
                        int b = square2y(currentroom.floortile, currentroom.enem[i].getPosition().y);
                        if (!dir)
                            b--;
                        else if (dir == 1)
                            a++;
                        else if (dir == 2)
                            b++;
                        else if (dir == 3)
                            a--;

                        currentroom.enem[i].rotatexy(sf::Vector2f(currentroom.floortile[a][b].x + 50,
                                                                  currentroom.floortile[a][b].y + 52));
                        currentroom.enem[i].ay =
                                std::sin(currentroom.enem[i].orient * PI / 180) * currentroom.enem[i].speed;
                        currentroom.enem[i].ax =
                                std::cos(currentroom.enem[i].orient * PI / 180) * currentroom.enem[i].speed;
                        currentroom.enem[i].move(-currentroom.enem[i].ax, -currentroom.enem[i].ay);
                    }
                }


                game.window.draw(
                        currentroom.enem[i]);///DRAWING EM (HAS TO BE HERE SINCE FURTHER IT WOULD GET SHUTDOWN WHEN DEAD AND NO ANIMATION WOULD PLAY
                if (currentroom.enem[i].health < 0) {
                    currentroom.enem[i].setColor(sf::Color(255, 255, 255));///DEATH ANIMATION START
                    if (!currentroom.enem[i].destroystate) {
                        currentroom.enem[i].destroyClock.restart();
                    }
                    currentroom.enem[i].destroystate++;
                    if (currentroom.enem[i].destroystate > 10 && currentroom.enem[i].destroystate < 20)
                        currentroom.enem[i].setTextureRect(r2);
                    if (currentroom.enem[i].destroystate > 20 && currentroom.enem[i].destroystate < 30)
                        currentroom.enem[i].setTextureRect(r3);
                    if (currentroom.enem[i].destroystate > 30 && currentroom.enem[i].destroystate < 40)
                        currentroom.enem[i].setTextureRect(r4);///DEATH ANIMATION END

                    if (currentroom.enem[i].destroystate > 40 && currentroom.enem[i].getTextureRect() == r4)  ///DYING
                    {
                        currentroom.spawnTiledrop(currentroom.enem[i]);
                        currentroom.enem.erase(currentroom.enem.begin() + i);
                    }
                    continue;
                }

                /*if(currentroom.enem[i].x<currentroom.enemyt.getSize().x)
                    currentroom.enem[i].x=currentroom.enemyt.getSize().x;
                if(currentroom.enem[i].x+currentroom.enemyt.getSize().x>game.width)
                    currentroom.enem[i].x=game.width-currentroom.enemyt.getSize().x;
                if(currentroom.enem[i].y<currentroom.enemyt.getSize().y)
                    currentroom.enem[i].y=currentroom.enemyt.getSize().y;
                if(currentroom.enem[i].y+currentroom.enemyt.getSize().y>game.height)
                    currentroom.enem[i].y=game.height-currentroom.enemyt.getSize().y;*////COLISSIONS WITH FRAMES - USELESS
                for (int unsigned j = 0; j < currentroom.proj.size(); ++j) {
                    if (!currentroom.enem[i].destroystate and
                        sqrt(((currentroom.proj[j].x - (currentroom.enem[i].getPosition().x)) *
                              (currentroom.proj[j].x - (currentroom.enem[i].getPosition().x))) +
                             ((currentroom.proj[j].y - (currentroom.enem[i].getPosition().y)) *
                              (currentroom.proj[j].y - (currentroom.enem[i].getPosition().y)))) < 15 &&
                        currentroom.proj[j].orig == &playa) {
                        currentroom.enem[i].setColor(sf::Color(255, 0, 0));
                        currentroom.enem[i].red = true;
                        currentroom.enem[i].ifshot.restart();
                        currentroom.enem[i].DealDamage(currentroom.proj[j].damage);
                        if (currentroom.proj[i].type > 2) {
                            game.explode(currentroom.proj[i].x + currentroom.enem[i].ax,
                                         currentroom.proj[i].y + currentroom.enem[i].ay);
                        }
                        currentroom.proj.erase(currentroom.proj.begin() + j);

                    }
                }
                if (currentroom.enem[i].ifshot.getElapsedTime().asMilliseconds() > 70 && currentroom.enem[i].red) {
                    currentroom.enem[i].red = false;
                    currentroom.enem[i].setColor(sf::Color(255, 255, 255));
                }
                currentroom.enem[i].setPosition(currentroom.enem[i].getPosition());
            }
            ///ENEMIES HANDLING END

            ///PLAYER TURNING RED
            if (playa.ifshot.getElapsedTime().asMilliseconds() > 70 && playa.red) {
                playa.red = false;
                playa.setColor(sf::Color(255, 255, 255));
                playa.move(-3, -3);
                hpbar.setFillColor(sf::Color(255, 255, 255));
            }
            ///boss turning red
            if (mainboss.ifshot.getElapsedTime().asMilliseconds() > 70 && mainboss.red) {
                mainboss.red = false;
                mainboss.setColor(sf::Color(255, 255, 255));
                mainboss.move(-3, -3);
            }
        }
        ///DRAWING
        if (currentroom.type != 1)
            game.window.draw(gui);

        game.window.draw(hpbar);
        game.window.draw(weapon);

        if (currentroom.type != 1) {
            if (currentroom.dbottom)
                game.window.draw(db);
            if (currentroom.dtop)
                game.window.draw(dt);
            if (currentroom.dleft)
                game.window.draw(dl);
            if (currentroom.dright)
                game.window.draw(dr);
        }

        game.window.draw(playa);

        for (int unsigned i = 0; i < currentroom.drops.size(); i++) ///TILEDROP HANDLING
        {
            if (sqrt(((currentroom.drops[i].s.getPosition().x + 30 - playa.getPosition().x) *
                      (currentroom.drops[i].s.getPosition().x + 30 - playa.getPosition().x)) +
                     ((currentroom.drops[i].s.getPosition().y + 23 - playa.getPosition().y) *
                      (currentroom.drops[i].s.getPosition().y + 23 - playa.getPosition().y))) < 50) {
                playa.addItem(currentroom.drops[i].collect());
                currentroom.drops.erase(currentroom.drops.begin() + i);
                continue;
            }
            int id;
            switch (currentroom.drops[i].collect().getId()) {
                case 0:
                    id = 1;
                    break;
                case 1:
                    id = 3;
                    break;
                case 2:
                    id = 4;
                    break;
                case 3:
                    id = 5;
                    break;
                case 4:
                    id = 6;
                    break;
                case 100:
                    id = 2;
                    break;
                default:
                    id = 0;
                    break;
            }
            currentroom.drops[i].s.setTextureRect(smals[id]);
            game.window.draw(currentroom.drops[i].s);
        }


        if (co == 5)/// ESPLOSIVO HANDLING
        {
            co = 0;
            for (int unsigned i = 0; i < game.exp.size(); i++) {
                game.exp[i].advance();
                if (!game.exp[i].alive)
                    game.exp.erase(game.exp.begin() + i);
                else {
                    game.exp[i].s.setTextureRect(exprecto[game.exp[i].state]);
                    game.window.draw(game.exp[i].s);
                }
            }
        } else {
            for (int unsigned i = 0; i < game.exp.size(); i++) {
                game.exp[i].s.setTextureRect(exprecto[game.exp[i].state]);
                game.window.draw(game.exp[i].s);
            }
        }

        ///game.App.draw(debug);///DISPLAYS DEBUG TEXT


        switch (gameended) {
            case 0:
                break;
            case 1:
                ///u died
                game.window.draw(endScreen);
                endText.setString("You died.");
                endText.setPosition(game.width * 400 / 1000, game.height * 400 / 1000);
                game.window.draw(endText);
                sound.stop();
                game.blasts.clear();
                break;
            case 2:
                ///u won
                game.window.draw(endScreen);
                endText.setString("You won.");
                endText.setPosition(game.width * 400 / 1000, game.height * 400 / 1000);
                game.window.draw(endText);
                sound.stop();
                game.blasts.clear();
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                break;
        }
        if (!rand() % 2000) {
            game.window.draw(prog);
        }
        game.window.display();///UPDATE SCREEN


    }

    return 0;
}