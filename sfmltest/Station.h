
#pragma once
#include "The Station.h"
class explosion;
class Station
{
public:
    int h,w, cx, cy;
    Station();
    sf::RenderWindow App;
    sf::Image guii;
    sf::Image dli,dri,dti,dbi;
    sf::Texture player, bgt, dleftt, drightt,dtopt,dbottomt,  guit, fltilt,invt,t0,selectinvt,explot,bossrt,bosst,lodin,timin,mainmen,start,optionz,exit,paus,optionp,menup,exitp,endscr,optionsmain;
    sf::Texture progt;
    bool isUnsized, unLoaded;
    sf::SoundBuffer shots,explos;
    sf::Font arial;
    std::vector<sf::Sound> blasts;
    std::vector<explosion> exp;
    //Room sect[10][10];
    bool cheatsEnabled,soundEnabled;
    void inventory(CMob& target);
    ///void changeRoom(Room& currentroom, int dir);
    void explode(int x, int y);
    void toggleCheatsEnabled();
    void toggleSoundEnabled();
    bool mainmenu();
    sf::Music menusic;
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
