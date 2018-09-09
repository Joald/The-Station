#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Models/GameObject.h"
#include "Events/EventManager.h"
#include "Character.h"

class Explosion;

class GameState : public GameObject {
public:
    unsigned int height, width, cx, cy;

    GameState();

    sf::RenderWindow window;
    sf::Image guii;
    sf::Image dli, dri, dti, dbi;
    sf::Texture playerTexture, backgroundTexture, doorLeftTexture, doorRightTexture, doorTopTexture, doorBottomTexture, guiTexture, floorTileTexture, inventoryTexture, t0, selectionTexture, explosionTexture, bossRoomTexture, bossTexture, loadingTexture, timingGamesLogoTexture, mainMenuTexture, newGameTexture, optionsButtonMainMenuTexture, exitTexture, pauseMenuBackgroundTexture, optionsButtonPauseMenuTexture, pauseMenuTexture, pauseExitTexture, endScreenTexture, optionsMenuBackgroundTexture;
    sf::Texture subliminalImageTexture;
    bool isUnsized, unLoaded;
    sf::SoundBuffer shots, explos;
    sf::Font arial;
    std::vector <sf::Sound> blasts;
    std::vector <Explosion> exp;
    //Room sect[10][10];
    bool cheatsEnabled, soundEnabled;

    void inventory(Character &target);

    ///void changeRoom(Room& currentroom, int dir);
    void explode(float x, float y);

    void toggleCheatsEnabled();

    void toggleSoundEnabled();

    bool mainMenu();

    sf::Music menuMusic;

    int pause();

    void options(int source);

    void intro();

    void endapp();
};


/**#pragma once
#include "The Station.h"
class explosion;
class Station
{
public:
    int h,w, cx, cy;
    Station();
    sf::RenderWindow App;
    sf::Image guii;
    sf::Texture player, bgt,   guit, fltilt,invt,t0,selectinvt,explot,bossrt,bosst;
    sf::Texture progt;
    bool isUnsized;
    sf::SoundBuffer shots;
    sf::Font arial;
    std::vector<explosion> exp;
    //Room sect[10][10];
    bool cheatsEnabled;
    void inventory(CMob& target);
    void changeRoom(Room& currentroom, int dir);
    void explode(int x, int y);
    bool mainmenu();
    int pause();
    void options(int source);
    void intro();
    void endapp();
};
*/
