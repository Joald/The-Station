#include "sfmltest/The Station.h"


#define n 16
#define m 6



/**
00 01 02 03 04
05 06 07 08 09
10 11 12 13 14
15 16 17 18 19
20 21 22 23 24
*/
using namespace std;
int currentpos;
bool vis[25];
int viscount;
/*double dist(int x1,int y1,int x2,int y2)
{
    return sqrt(abs(x1-x2)*abs(x1-x2)+abs(y1-y2)*abs(y1-y2))/100;
}*/
int square2x(tile floortile[n][m],int x)
{
    for(int i=0; i<n; i++)
    {
        if((floortile[i][0].x<x  &&  floortile[i][0].x+100>x) || floortile[i][0].x==x)
            return i;
    }
    return 0;
}
int square2y(tile floortile[n][m],int y)
{
    for(int i=0; i<m; i++)
    {
        if((floortile[0][i].y<y  &&  floortile[0][i].y+104>y) ||  floortile[i][0].y==y)
            return i;
    }
    return 0;
}
void changeRoom(Room&currentroom, int dir, vector<Room> section)///0 - up, 1 - right, 2 - down, 3 - left
{
    if(currentpos==2  &&  dir==0)
    {
        ///BOSSROOM SPAWN
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
            {
                currentroom.floortile[i][j].walkable=true;

            }
        }
        currentroom.type=1;
        currentpos=-1;
        return;
    }
    currentroom.type=0;
    int a;
    switch(dir)
    {
    case 0:
        if(currentpos<5)
            return;
        a=-5;
        break;
    case 1:
        if(currentpos==24)
            return;
        a=1;
        break;
    case 2:
        if(currentpos>19)
            return;
        a=5;
        break;
    case 3:
        if(!currentpos ||  currentpos==5 ||  currentpos==10 ||  currentpos==15 ||  currentpos==20)
            return;
        a=-1;
        break;
    default:
        break;
    }
    currentroom.dbottom=section[currentpos+a].dbottom;
    currentroom.dtop=section[currentpos+a].dtop;
    currentroom.dleft=section[currentpos+a].dleft;
    currentroom.dright=section[currentpos+a].dright;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {

            currentroom.floortile[i][j].x=section[currentpos+a].floortile[i][j].x;
            currentroom.floortile[i][j].y=section[currentpos+a].floortile[i][j].y;
            currentroom.floortile[i][j].type=section[currentpos+a].floortile[i][j].type;
            if(section[currentpos+a].floortile[i][j].walkable)
                currentroom.floortile[i][j].walkable=true;
            else
                currentroom.floortile[i][j].walkable=false;
            if(currentroom.floortile[i][j].type==0)
                currentroom.floortile[i][j].sprite.setTexture(currentroom.floort);
            if(currentroom.floortile[i][j].type==1)
                currentroom.floortile[i][j].sprite.setTexture(currentroom.chestt);
        }
    }

    section[currentpos].enem.erase(section[currentpos].enem.begin(),section[currentpos].enem.end());

    while(currentroom.enem.size())
    {
        section[currentpos].enem.push_back(currentroom.enem[currentroom.enem.size()-1]);
        currentroom.enem.erase(currentroom.enem.end());
    }
    for(int unsigned i=0; i<section[currentpos+a].enem.size(); i++)
    {
        currentroom.enem.push_back(section[currentpos+a].enem[i]);
    }
    while(currentroom.drops.size())
    {
        section[currentpos].drops.push_back(currentroom.drops[currentroom.drops.size()-1]);
        currentroom.drops.erase(currentroom.drops.end());
    }
    for(int unsigned i=0; i<section[currentpos+a].drops.size(); i++)
    {
        currentroom.drops.push_back(section[currentpos+a].drops[i]);
    }
    currentroom.proj.erase(currentroom.proj.begin(),currentroom.proj.end());
    currentpos+=a;
    if(!vis[currentpos]) ///MOB SPAWNING
    {
        vis[currentpos]=true;
        int t=viscount/5;
        ///int b=viscount;
        int u=rand()%5+5;
        int c=0;
        for(int j=0; j<n; j++)
        {
            for( int k=0; k<m; k++)
            {
                int d=rand()%10;
                if(currentroom.floortile[j][k].walkable  &&  !d )
                {
                    c++;
                    currentroom.spawn_enemy(currentroom.floortile[j][k].x+50,currentroom.floortile[j][k].y+52,t);
                }
                if(c==u)
                    goto lolz;
            }
        }
lolz:

        viscount++;
    }
}

int CALLBACK WinMain(
  _In_  HINSTANCE hInstance,
  _In_  HINSTANCE hPrevInstance,
  _In_  LPSTR lpCmdLine,
  _In_  int nCmdShow
)
{


    Station game;
    /*if(2==game.pause())
    {
        game.App.close();
        return 0;
    }*/
    srand(time(0));
int fixw=170;
int fixh=291;
if(game.isUnsized)
{
    fixw=91;
    fixh=155;
}
    sf::Sprite loadin;
    loadin.setTexture(game.lodin);



    ///game.intro();//<<<<<<<<<<<<<<<<<<<<<<<

    if(game.unLoaded ||  !game.mainmenu())
    {
        game.App.close();
        return 0;
    }

    game.blasts.clear();
    game.exp.clear();
respawn:
    viscount=0;
    currentpos=0;
    for(int i=0; i<25; i++)
    {
        vis[i]=0;
    }
    //bool bossopen=false;
    sf::Sprite prog,bossroom;


    bossroom.setTexture(game.bossrt);

    prog.setTexture(game.progt);




    sf::IntRect smals[6];
    int its=0;
    /*for(int k=0; k<3; k++)
    {*/
    for(int j=0; j<6; j++)
    {
        its++;
        smals[its].height=47;
        smals[its].width=60;
        smals[its].top=0*smals[its].height;
        smals[its].left=j*smals[its].width;
    }
    smals[6].top=smals[6].height;
    smals[6].left=0;
    //}

    sf::IntRect shotcolors[6];
    for(int i=0; i<6; i++)
    {
        shotcolors[i].height=15;
        shotcolors[i].width=3;
        shotcolors[i].top=0;
        shotcolors[i].left=i*3;
    }
    sf::IntRect exprecto[9];
    for(int i=0; i<9; i++)
    {
        exprecto[i].height=21;
        exprecto[i].width=21;
        exprecto[i].top=0;
        exprecto[i].left=i*20;
    }


    currentpos=12;
    vis[currentpos]=1;
    viscount=1;

    // game.App.setMouseCursorVisible(false);
    sf::Music lodin;
    lodin.openFromFile("loop.wav");
    if(game.soundEnabled)
        lodin.play();
    game.App.draw(loadin);
    game.App.display();


    //uniform_int_distribution<int> a(0,1);
    CMob playa;
    boss mainboss;
    playa.addItem(4,0,100,1);
    playa.addItem(100,1,40,1);
    /*playa.addItem(0,0,41);*/


    playa.C.setOrigin(game.player.getSize().y/2,game.player.getSize().y*35/50);
    playa.x=game.w/2;
    playa.y=game.h/2;
    mainboss.x=game.w/2;
    mainboss.y=game.h/2;
    playa.C.setPosition(playa.x,playa.y);
    mainboss.C.setPosition(playa.x,playa.y);
    mainboss.C.setTexture(game.bosst);

    vector<Room> section;
    for(int i=0; i<25; i++)
    {
        Room newroom(game);
        section.push_back(newroom);
    }
    for(int i=0; i<5; i++)
    {
        section[i].dtop=false;
    }
    for(int i=0; i<21; i+=5)
        section[i].dleft=false;
    for(int i=20; i<25; i++)
        section[i].dbottom=false;
    for(int i=4; i<25; i+=5)
        section[i].dright=false;

    sf::Sprite weapon,endscreen;
    endscreen.setTexture(game.endscr);
    endscreen.setPosition(0,0);
    sf::Text endtext;
    endtext.setFont(game.arial);
    endtext.setCharacterSize(100);
    endtext.setColor(sf::Color::Cyan);

    sf::Texture wt;
    wt.loadFromFile("weapon.png");
    if(game.isUnsized)
        weapon.scale(wt.getSize().x*1024/1920,wt.getSize().x*576/1080);
    sf::IntRect weaprects[6];
    for(int i=0; i<6; i++)
    {
        weaprects[i].height=79;
        weaprects[i].width=224;
        weaprects[i].left=0;
        weaprects[i].top=i*79;
    }

    weapon.setTexture(wt);

    weapon.setPosition(game.w/100,game.h/32);
    sf::Sprite bg, gui;
    sf::IntRect r1(0, 0, 50,50);
    sf::IntRect r2(0, 50, 50,50);
    sf::IntRect r3(50, 0,50,50);
    sf::IntRect r4(50, 50,50,50);

    sf::Clock bossclock;
    sf::Color frame;
    sf::Text debug;
    sf::Text hpbar;
    debug.setColor(sf::Color::White);
    debug.setPosition(0,game.h*97/100);
    hpbar.setColor(sf::Color::White);
    hpbar.setPosition(game.w*255/1000,game.h*25/1000);
    int mx,my;
    sf::String debugs;
    sf::String hptext;
    string mxs,mys,angs;
    Room currentroom(game);

    //currentroom.changeTo( section[5][5], section[5][5].floortile);
    //currentroom.loadroom(game.w,game.h);

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            //currentroom.floortile[i][j].changeTo(ox.floortile[i][j]);
            currentroom.floortile[i][j].x=section[12].floortile[i][j].x;
            currentroom.floortile[i][j].y=section[12].floortile[i][j].y;
            currentroom.floortile[i][j].type=section[12].floortile[i][j].type;
            if(section[12].floortile[i][j].walkable)
                currentroom.floortile[i][j].walkable=true;
            else
                currentroom.floortile[i][j].walkable=false;
            if(currentroom.floortile[i][j].type==0)
                currentroom.floortile[i][j].sprite.setTexture(currentroom.floort);
            if(currentroom.floortile[i][j].type==1)
                currentroom.floortile[i][j].sprite.setTexture(currentroom.chestt);
        }
    }
    sf::Sprite db(game.dbottomt);
    sf::Sprite dt(game.dtopt);
    sf::Sprite dr(game.drightt);
    sf::Sprite dl(game.dleftt);
    sf::Sound sound;
    sf::Clock manualspawntimer;
    bg.setTexture(game.bgt);
    gui.setTexture(game.guit);
    playa.C.setTexture(game.player);
    debug.setFont(game.arial);
    hpbar.setFont(game.arial);
    game.App.setFramerateLimit(70);
    sf::Color dor(111,111,111);
    int co=0;
    lodin.pause();
    bool bossopen=false;
    int gameended=0;

    sf::Music battle;
    battle.openFromFile("battle.wav");
    battle.setLoop(true);
    if(game.soundEnabled)
        battle.play();
    while (game.App.isOpen())///**************************************************************************************************************************GAME LOOP OPEN
    {
        co++;
        sf::Event event;
        while (game.App.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                game.App.close();
                break;
            case sf::Event::KeyPressed:
                if(gameended)
                {
                    if(!game.soundEnabled)
                        battle.pause();
                    if(!game.mainmenu())
                    {
                        game.endapp();
                        return 0;
                    }
                    else
                    {
                        goto respawn;
                    }
                }
                if(event.key.code == sf::Keyboard::Escape  &&  !gameended)
                {
                    if(!game.soundEnabled)
                        battle.pause();
                    int asda=game.pause();
                    if(!asda)
                    {
                        if(!game.mainmenu())
                        {
                            game.endapp();
                            return 0;
                        }
                        else
                        {
                            goto respawn;
                        }
                    }
                    else if(asda==2)
                    {
                        game.endapp();
                        continue;
                    }
                    else if(game.soundEnabled)
                        battle.play();
                }
                if (event.key.code == sf::Keyboard::E  &&  !gameended)
                {
                    game.inventory(playa);
                }
                if(game.cheatsEnabled)
                {
                    if (event.key.code == sf::Keyboard::Up  &&  currentroom.type!=1  &&  currentpos!=2)
                    {
                        changeRoom(currentroom,0,section);
                    }
                    if (event.key.code == sf::Keyboard::Down  &&  currentroom.type!=1)
                    {
                        changeRoom(currentroom,2,section);
                    }
                    if (event.key.code == sf::Keyboard::Left  &&  currentroom.type!=1)
                    {
                        changeRoom(currentroom,3,section);
                    }
                    if (event.key.code == sf::Keyboard::Right  &&  currentroom.type!=1)
                    {
                        changeRoom(currentroom,1,section);
                    }
                    if (event.key.code == sf::Keyboard::I)
                    {
                        playa.toggleInvincible();
                    }
                    if (event.key.code == sf::Keyboard::Q  &&  currentroom.type!=1  &&  currentroom.enem.size())
                    {
                        game.inventory(currentroom.enem[0]);
                    }
                    if (event.key.code == sf::Keyboard::P  &&  currentroom.type!=1)
                    {
                        viscount=25;
                    }
                    if (event.key.code == sf::Keyboard::K  &&  currentroom.type!=1)
                    {
                        currentroom.enem.erase(currentroom.enem.begin(),currentroom.enem.end());
                    }
                }
            default:
                break;
            }
        }
        if( !gameended  &&  viscount==25  &&  currentroom.type!=1  &&  bossopen==false )
        {
            int anum=0;
            for(int i=0; i<25; i++)
            {
                if(!section[i].enem.empty())
                    break;
                anum++;
            }
            if(anum==25)
            {
                bossopen=true;
                section[2].dtop=true;
            }
        }


        if(!gameended)
            weapon.setTextureRect(weaprects[playa.inv[playa.weaponiter].getId()]);

        ///WALKING PLAYER
        if(!gameended)
        {
            if (sf::Keyboard::isKeyPressed ( sf::Keyboard::W )  &&  (playa.canWalkUp(currentroom.floortile,game) ))
                playa.y-=playa.speed;
            if(sf::Keyboard::isKeyPressed ( sf::Keyboard::W )  &&  currentroom.dtop  &&  game.dti.getPixel(playa.x,playa.y-15)==dor  &&  currentroom.type!=1)
            {
                changeRoom(currentroom,0,section);
                playa.y+=580;
            }


            if (sf::Keyboard::isKeyPressed ( sf::Keyboard::S )  &&  playa.canWalkDown(currentroom.floortile,game  ))
                playa.y+=playa.speed;
            if(sf::Keyboard::isKeyPressed ( sf::Keyboard::S ) &&  currentroom.dbottom  &&  (game.dbi.getPixel(playa.x,playa.y+20)==dor)  &&  currentroom.type!=1)
            {
                changeRoom(currentroom,2,section);
                playa.y-=580;
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)  &&  (playa.canWalkLeft(currentroom.floortile,game)))
                playa.x-=playa.speed;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)  &&  currentroom.dleft  &&  game.dli.getPixel(playa.x-15,playa.y)==dor  &&  currentroom.type!=1)
            {
                changeRoom(currentroom,3,section);
                playa.x+=1500;
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)  &&  (playa.canWalkRight(currentroom.floortile,game) ))
                playa.x+=playa.speed;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)  &&  currentroom.dright  &&  game.dri.getPixel(playa.x+20,playa.y)==dor  &&  currentroom.type!=1)
            {
                changeRoom(currentroom,1,section);
                playa.x-=1500;
            }


            if(playa.health<=0)
            {
                gameended=1;
            }

            ///MOUSE ROTAtION
            mx=sf::Mouse::getPosition(game.App).x;
            my=sf::Mouse::getPosition(game.App).y;
            playa.rotatexy(mx,my);

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
            debugs+=mxs+", "+mys+", angle: "+angs;
            debug.setString(debugs);*/
            ///debugs.clear();
            /*if(currentroom.dbottom)
                debugs+="bot, ";
            if(currentroom.dtop)
                debugs+="top, ";
            if(currentroom.dleft)
                debugs+="left, ";
            if(currentroom.dright)
                debugs+="right, ";*/
            ostringstream convert;
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
            convert<<playa.health;
            hptext=convert.str();
            convert.str(std::string());
            hpbar.setString(hptext);

            ///MANUAL SPAWNING
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right)  &&  currentroom.type!=1  &&  game.cheatsEnabled)
            {
                if(manualspawntimer.getElapsedTime().asSeconds()>1)
                {
                    currentroom.spawn_enemy(mx,my,0);
                    currentroom.enem[currentroom.enem.size()-1].rotatexy(playa.x,playa.y);
                    manualspawntimer.restart();
                }
            }

            playa.C.setPosition(playa.x,playa.y);///zmiana pozycji gracza

            ///SHOOTING
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(playa.shoot(currentroom.proj,mx,my))
                {
                    currentroom.proj[currentroom.proj.size()-1].C.setTexture(currentroom.sht);
                    currentroom.proj[currentroom.proj.size()-1].C.setTextureRect(shotcolors[currentroom.proj[currentroom.proj.size()-1].type]);

                    if(game.soundEnabled)
                    {
                        sound.setBuffer(game.shots);
                        sound.setPosition(playa.x,playa.y,0);
                        sound.play();
                    }
                }
            }


            ///DRAW BACKGROUND  &&  BOSS HANDLING
            if(currentroom.type!=1)
                game.App.draw(bg);
            else
            {


                if(mainboss.health<=0 )
                {
                    if( mainboss.destroystate==0)
                        bossclock.restart();
                    mainboss.destroystate++;
                    if(co==2 ||  co==4)
                        game.explode(mainboss.x-50+rand()%100-50,mainboss.y+rand()%100-50);
                    if(bossclock.getElapsedTime().asSeconds()>4)
                    {
                        gameended=2;
                        ///game.endscreen();
                    }
                }
                if(mainboss.shoot(currentroom.proj,0,0))///boss shooting
                {
                    currentroom.proj[currentroom.proj.size()-1].C.setTexture(currentroom.sht);
                    currentroom.proj[currentroom.proj.size()-1].C.setTextureRect(shotcolors[currentroom.proj[currentroom.proj.size()-1].type]);
                    if(game.soundEnabled)
                    {
                        sound.setBuffer(game.shots);
                        sound.setPosition(mainboss.x,mainboss.y,0);
                        sound.play();
                    }
                    mainboss.shoot(currentroom.proj,0,game.h,true);

                    currentroom.proj[currentroom.proj.size()-1].C.setTexture(currentroom.sht);
                    currentroom.proj[currentroom.proj.size()-1].C.setTextureRect(shotcolors[currentroom.proj[currentroom.proj.size()-1].type]);
                    if(game.soundEnabled)
                    {
                        sound.setBuffer(game.shots);
                        sound.setPosition(mainboss.x,mainboss.y,0);
                        sound.play();
                    }
                    mainboss.shoot(currentroom.proj,game.w,game.h,true);


                    currentroom.proj[currentroom.proj.size()-1].C.setTexture(currentroom.sht);
                    currentroom.proj[currentroom.proj.size()-1].C.setTextureRect(shotcolors[currentroom.proj[currentroom.proj.size()-1].type]);
                    if(game.soundEnabled)
                    {
                        sound.setBuffer(game.shots);
                        sound.setPosition(mainboss.x,mainboss.y,0);
                        sound.play();

                    }
                    mainboss.shoot(currentroom.proj,game.w,0,true);
                    currentroom.proj[currentroom.proj.size()-1].C.setTexture(currentroom.sht);
                    currentroom.proj[currentroom.proj.size()-1].C.setTextureRect(shotcolors[currentroom.proj[currentroom.proj.size()-1].type]);
                    if(game.soundEnabled)
                    {
                        sound.setBuffer(game.shots);
                        sound.setPosition(mainboss.x,mainboss.y,0);
                        sound.play();
                    }
                    if(rand()%10>8)
                    {
                        currentroom.spawn_enemy(mainboss.x+rand()%500-250,mainboss.y+rand()%500-250,4);
                    }
                }
                game.App.draw(bossroom);
                game.App.draw(mainboss.C);
            }
        }

        ///DRAW FLOOR
        if(currentroom.type!=1)
        {
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<m; j++)
                {
                    game.App.draw(currentroom.floortile[i][j].sprite);
                }
            }
        }



        if(!gameended)
        {
            ///PROJECTILE HANDLING
            for(int unsigned i=0; i<currentroom.proj.size(); ++i)
            {
                if(currentroom.proj[i].canWalk(currentroom.floortile,game))
                {
                    currentroom.proj[i].y+=currentroom.proj[i].ay;
                    currentroom.proj[i].x-=currentroom.proj[i].ax;
                }
                else
                {
                    if(currentroom.proj[i].type>2)
                    {
                        game.explode(currentroom.proj[i].x,currentroom.proj[i].y);
                    }
                    currentroom.proj.erase(currentroom.proj.begin()+i);
                    continue;
                }



                currentroom.proj[i].C.setPosition(currentroom.proj[i].x,currentroom.proj[i].y);
                game.App.draw(currentroom.proj[i].C);
                if(sqrt( ((currentroom.proj[i].x - playa.x)  *  (currentroom.proj[i].x - playa.x))  +  ((currentroom.proj[i].y - playa.y)  *  (currentroom.proj[i].y - playa.y))) <15  &&  currentroom.proj[i].orig!=&playa && !playa.invincible  &&  !playa.red)
                {
                    playa.C.setColor(sf::Color(255, 0, 0));
                    hpbar.setColor(sf::Color(255,0,0));
                    playa.red=true;

                    playa.C.move(3,3);
                    playa.ifshot.restart();
                    playa.DealDamage(currentroom.proj[i].damage);

                    if(currentroom.proj[i].type>2)
                    {
                        game.explode(currentroom.proj[i].x,currentroom.proj[i].y);
                    }
                    currentroom.proj.erase(currentroom.proj.begin()+i);
                }
                if(currentroom.type==1)
                {
                    mainboss.y-=50;
                    if(sqrt( ((currentroom.proj[i].x - mainboss.x)  *  (currentroom.proj[i].x - mainboss.x))  +  ((currentroom.proj[i].y - mainboss.y)  *  (currentroom.proj[i].y - mainboss.y))) <150  &&  currentroom.proj[i].orig==&playa && !mainboss.invincible  &&  !mainboss.red)
                    {
                        mainboss.C.setColor(sf::Color(255, 0, 0));

                        mainboss.red=true;

                        mainboss.C.move(3,3);
                        mainboss.ifshot.restart();
                        mainboss.DealDamage(currentroom.proj[i].damage);

                        if(currentroom.proj[i].type>2)
                        {
                            game.explode(currentroom.proj[i].x,currentroom.proj[i].y);
                        }
                        currentroom.proj.erase(currentroom.proj.begin()+i);
                    }
                    mainboss.y+=50;
                }
                if(currentroom.proj[i].x>game.w||!currentroom.proj[i].x||currentroom.proj[i].y>game.h||!currentroom.proj[i].y)
                {

                    if(currentroom.proj[i].type>2)
                    {
                        game.explode(currentroom.proj[i].x,currentroom.proj[i].y);
                    }
                    currentroom.proj.erase(currentroom.proj.begin()+i);
                }
            }

            ///ENEMIES HANDLING
            for(int unsigned i=0; i<currentroom.enem.size(); ++i)
            {

                if(currentroom.enem[i].canSee(currentroom.floortile,playa.x,playa.y))
                {
                    /*int mox=0,moy=0;
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                        moy=-25*dist(playa.x,playa.y,currentroom.enem[i].x,currentroom.enem[i].y);
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                        moy=25*dist(playa.x,playa.y,currentroom.enem[i].x,currentroom.enem[i].y);
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        mox=-25*dist(playa.x,playa.y,currentroom.enem[i].x,currentroom.enem[i].y);
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                        mox=25*dist(playa.x,playa.y,currentroom.enem[i].x,currentroom.enem[i].y);*/
                    currentroom.enem[i].rotatexy(playa.x/*+mox*/,playa.y/*+moy*/);///ROTATING ENEMIES
                    if(currentroom.enem[i].shoot( currentroom.proj,playa.x/*+mox*/,playa.y/*+moy*/))
                    {
                        currentroom.proj[currentroom.proj.size()-1].C.setTexture(currentroom.sht);
                        currentroom.proj[currentroom.proj.size()-1].C.setTextureRect(shotcolors[currentroom.proj[currentroom.proj.size()-1].type]);
                        if(game.soundEnabled)
                        {
                            sound.setBuffer(game.shots);
                            sound.setPosition(currentroom.enem[i].x,currentroom.enem[i].y,0);
                            sound.play();
                        }
                    }
                    currentroom.enem[i].ay=sin(currentroom.enem[i].orient*PI/180)*currentroom.enem[i].speed;///GIVING 'EM DELTA Y
                    if(!currentroom.enem[i].canWalkDown(currentroom.floortile,game)  &&  currentroom.enem[i].ay<0)
                        currentroom.enem[i].ay=0;
                    ///CHECKING  IF THEY CAN WALK THIS WAY
                    if(!currentroom.enem[i].canWalkUp(currentroom.floortile,game)  &&  currentroom.enem[i].ay>0)
                        currentroom.enem[i].ay=0;

                    currentroom.enem[i].ax=cos(currentroom.enem[i].orient*PI/180)*currentroom.enem[i].speed;///GIVING 'EM DELTA X
                    if(!currentroom.enem[i].canWalkRight(currentroom.floortile,game)  &&  currentroom.enem[i].ax<0)
                        currentroom.enem[i].ax=0;
                    ///CHECKING  IF THEY CAN WALK THIS WAY
                    if(!currentroom.enem[i].canWalkLeft(currentroom.floortile,game)  &&  currentroom.enem[i].ax>0)
                        currentroom.enem[i].ax=0;

                    if(currentroom.enem[i].ay ||  currentroom.enem[i].ax)
                    {
                        for(int unsigned j=0; j<currentroom.enem.size(); ++j)
                        {
                            if(j==i)
                                continue;
                            if(sqrt(((currentroom.enem[j].x - (currentroom.enem[i].x))  *  (currentroom.enem[j].x - (currentroom.enem[i].x)))  +  ((currentroom.enem[j].y - (currentroom.enem[i].y))  *  (currentroom.enem[j].y - (currentroom.enem[i].y)))) <30)
                            {
                                currentroom.enem[i].ax=0;
                                currentroom.enem[i].ay=0;
                            }

                        }
                    }


                    if(currentroom.enem[i].x-playa.x>100||playa.x-currentroom.enem[i].x>100||currentroom.enem[i].y-playa.y>100||playa.y-currentroom.enem[i].y>100 )///MOVING ENEMIES - IMPLEMENT AI HERE
                    {
                        currentroom.enem[i].x-=currentroom.enem[i].ax;

                        currentroom.enem[i].y-=currentroom.enem[i].ay;
                    }
                }
                else
                {
                    int dir=currentroom.enem[i].returnpath(currentroom.floortile,playa.x,playa.y);
                    if(dir!=4)
                    {
                        int a=square2x(currentroom.floortile,currentroom.enem[i].x);
                        int b=square2y(currentroom.floortile,currentroom.enem[i].y);
                        if(!dir)
                            b--;
                        else if(dir==1)
                            a++;
                        else if(dir==2)
                            b++;
                        else if(dir==3)
                            a--;

                        currentroom.enem[i].rotatexy(currentroom.floortile[a][b].x+50,currentroom.floortile[a][b].y+52);
                        currentroom.enem[i].ay=sin(currentroom.enem[i].orient*PI/180)*currentroom.enem[i].speed;
                        currentroom.enem[i].ax=cos(currentroom.enem[i].orient*PI/180)*currentroom.enem[i].speed;
                        currentroom.enem[i].x-=currentroom.enem[i].ax;
                        currentroom.enem[i].y-=currentroom.enem[i].ay;
                    }
                }



                game.App.draw(currentroom.enem[i].C);///DRAWING EM (HAS TO B HERE SINCE FURTHER IT WOULD GET SHUTDOWN WHEN DEAD AND NO ANIMATION WOULD PLAY
                if(currentroom.enem[i].health<0)
                {
                    currentroom.enem[i].C.setColor(sf::Color(255,255,255));///DEATH ANIMATION START
                    if(!currentroom.enem[i].destroystate)
                    {
                        currentroom.enem[i].destroyclock.restart();
                    }
                    currentroom.enem[i].destroystate++;
                    if(currentroom.enem[i].destroystate>10&&currentroom.enem[i].destroystate<20)
                        currentroom.enem[i].C.setTextureRect(r2);
                    if(currentroom.enem[i].destroystate>20&&currentroom.enem[i].destroystate<30)
                        currentroom.enem[i].C.setTextureRect(r3);
                    if(currentroom.enem[i].destroystate>30&&currentroom.enem[i].destroystate<40)
                        currentroom.enem[i].C.setTextureRect(r4);///DEATH ANIMATION END

                    if(currentroom.enem[i].destroystate>40&&currentroom.enem[i].C.getTextureRect()==r4)  ///DYING
                    {
                        currentroom.spawnTiledrop(currentroom.enem[i]);
                        currentroom.enem.erase(currentroom.enem.begin()+i);
                    }
                    continue;
                }

                /*if(currentroom.enem[i].x<currentroom.enemyt.getSize().x)
                    currentroom.enem[i].x=currentroom.enemyt.getSize().x;
                if(currentroom.enem[i].x+currentroom.enemyt.getSize().x>game.w)
                    currentroom.enem[i].x=game.w-currentroom.enemyt.getSize().x;
                if(currentroom.enem[i].y<currentroom.enemyt.getSize().y)
                    currentroom.enem[i].y=currentroom.enemyt.getSize().y;
                if(currentroom.enem[i].y+currentroom.enemyt.getSize().y>game.h)
                    currentroom.enem[i].y=game.h-currentroom.enemyt.getSize().y;*////COLISSIONS WITH FRAMES - USELESS
                for(int unsigned j=0; j<currentroom.proj.size(); ++j)
                {
                    if(!currentroom.enem[i].destroystate  &&  sqrt( ((currentroom.proj[j].x - (currentroom.enem[i].x))  *  (currentroom.proj[j].x - (currentroom.enem[i].x)))  +  ((currentroom.proj[j].y - (currentroom.enem[i].y))  *  (currentroom.proj[j].y - (currentroom.enem[i].y)))) <15  &&  currentroom.proj[j].orig==&playa)
                    {
                        currentroom.enem[i].C.setColor(sf::Color(255, 0, 0));
                        currentroom.enem[i].red=true;
                        currentroom.enem[i].ifshot.restart();
                        currentroom.enem[i].DealDamage(currentroom.proj[j].damage);
                        if(currentroom.proj[i].type>2)
                        {
                            game.explode(currentroom.proj[i].x+currentroom.enem[i].ax,currentroom.proj[i].y+currentroom.enem[i].ay);
                        }
                        currentroom.proj.erase(currentroom.proj.begin()+j);

                    }
                }
                if(currentroom.enem[i].ifshot.getElapsedTime().asMilliseconds()>70&&currentroom.enem[i].red)
                {
                    currentroom.enem[i].red=false;
                    currentroom.enem[i].C.setColor(sf::Color(255,255,255));
                }


                currentroom.enem[i].C.setPosition(currentroom.enem[i].x,currentroom.enem[i].y);


            }
            ///ENEMIES HANDLING END

            ///PLAYER TURNING RED
            if(playa.ifshot.getElapsedTime().asMilliseconds()>70&&playa.red)
            {
                playa.red=false;
                playa.C.setColor(sf::Color(255,255,255));
                playa.C.move(-3,-3);
                hpbar.setColor(sf::Color(255,255,255));
            }
            ///boss turning red
            if(mainboss.ifshot.getElapsedTime().asMilliseconds()>70&&mainboss.red)
            {
                mainboss.red=false;
                mainboss.C.setColor(sf::Color(255,255,255));
                mainboss.C.move(-3,-3);

            }
        }
        ///DRAWING
        if( currentroom.type!=1)
            game.App.draw(gui);

        game.App.draw(hpbar);
        game.App.draw(weapon);

        if(currentroom.type!=1)
        {
            if(currentroom.dbottom)
                game.App.draw(db);
            if(currentroom.dtop)
                game.App.draw(dt);
            if(currentroom.dleft)
                game.App.draw(dl);
            if(currentroom.dright)
                game.App.draw(dr);
        }

        game.App.draw(playa.C);

        for(int unsigned i=0; i<currentroom.drops.size(); i++) ///TILEDROP HANDLING
        {
            if(sqrt( ((currentroom.drops[i].s.getPosition().x+30 - playa.x)  *  (currentroom.drops[i].s.getPosition().x+30 - playa.x))  +  ((currentroom.drops[i].s.getPosition().y+23 - playa.y)  *  (currentroom.drops[i].s.getPosition().y+23 - playa.y))) <50 )
            {
                playa.addItem(currentroom.drops[i].collect());
                currentroom.drops.erase(currentroom.drops.begin()+i);
                continue;
            }
            int id;
            switch(currentroom.drops[i].collect().getId())
            {
            case 0:
                id=1;
                break;
            case 1:
                id=3;
                break;
            case 2:
                id=4;
                break;
            case 3:
                id=5;
                break;
            case 4:
                id=6;
                break;
            case 100:
                id=2;
                break;
            default:
                id=0;
                break;
            }
            currentroom.drops[i].s.setTextureRect(smals[id]);
            game.App.draw(currentroom.drops[i].s);
        }



        if(co==5)/// ESPLOSIVO HANDLING
        {
            co=0;
            for(int unsigned i=0; i<game.exp.size(); i++)
            {
                game.exp[i].handle();
                if(!game.exp[i].alive)
                    game.exp.erase(game.exp.begin()+i);
                else
                {
                    game.exp[i].s.setTextureRect(exprecto[game.exp[i].state]);
                    game.App.draw(game.exp[i].s);
                }
            }
        }
        else
        {
            for(int unsigned i=0; i<game.exp.size(); i++)
            {
                game.exp[i].s.setTextureRect(exprecto[game.exp[i].state]);
                game.App.draw(game.exp[i].s);
            }
        }

        ///game.App.draw(debug);///DISPLAYS DEBUG TEXT


        switch(gameended)
        {
        case 0:
            break;
        case 1:
            ///u died
            game.App.draw(endscreen);
            endtext.setString("You died.");
            endtext.setPosition(game.w*400/1000,game.h*400/1000);
            game.App.draw(endtext);
            sound.stop();
            game.blasts.clear();
            break;
        case 2:
            ///u won
            game.App.draw(endscreen);
            endtext.setString("You won.");
            endtext.setPosition(game.w*400/1000,game.h*400/1000);
            game.App.draw(endtext);
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
        if(!rand()%2000)
        {
            game.App.draw(prog);
        }
        game.App.display();///UPDATE SCREEN


    }

    return 0;
}
/// ZABAWA Z OPENGL:
/*game.App.setVerticalSyncEnabled(true);
    // Set the color and depth clear values
    glClearDepth(1.f);
    glClearColor(0, 0, 0, 0);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
sf::Clock Clock;
    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluPerspective(90, 1, 1, 500);
pair<pair<int,int>,int>rands[8];
        for(int i=0;i<8;i++)
        {
            rands[i].first.first=rand()%255;
            rands[i].first.second=rand()%255;
            rands[i].second=rand()%255;
        }
gluPerspective(45, 1.333, 0.1, 1000);
int xort=2;
    while(xort==2)
    {
        if(sf::Keyboard::isKeyPressed ( sf::Keyboard::Space ))
            xort=1;
        if(sf::Keyboard::isKeyPressed ( sf::Keyboard::Escape ))
            xort=0;

        game.App.pushGLStates();
        game.App.draw(loadin);
        game.App.popGLStates();
        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //
        // Apply some transformations
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, -200);
        //glRotatef(Clock.getElapsedTime().asMilliseconds() * 0.1, 1, 0, 0);
        glRotatef(Clock.getElapsedTime().asMilliseconds() * 0.1, 0, 1, 0);
        //glRotatef(Clock.getElapsedTime().asMilliseconds() * 9, 0, 0, 1);

        // Draw a cube
        int a=5;
        int b=5;
        int c=0;
        glBegin(GL_TRIANGLES);

            glColor3ub(rands[c].first.first, rands[c].first.second,rands[c].second);
            glVertex3f(-5*a, 0, -5*a);
            glVertex3f(5*a,  0, -5*a);
            glVertex3f( 0,  10*b,0);
c++;
            glColor3ub(rands[c].first.first, rands[c].first.second,rands[c].second);
            glVertex3f(0,  10*b, 0);
            glVertex3f(-5*a, 0, 5*a);
            glVertex3f( 5*a, 0, 5*a);
c++;
            glColor3ub(rands[c].first.first, rands[c].first.second,rands[c].second);
            glVertex3f(0,  10*b, 0);
            glVertex3f(-5*a, 0, 5*a);
            glVertex3f(-5*a, 0, -5*a);
c++;
            glColor3ub(rands[c].first.first, rands[c].first.second,rands[c].second);
            glVertex3f(0,  10*b, 0);
            glVertex3f( 5*a, 0, 5*a);
            glVertex3f(5*a,  0, -5*a);///end of upper part
            b=-5;c++;
            glColor3ub(rands[c].first.first, rands[c].first.second,rands[c].second);
            glVertex3f(-5*a, 0, -5*a);
            glVertex3f(5*a,  0, -5*a);
            glVertex3f( 0,  10*b,0);
c++;
            glColor3ub(rands[c].first.first, rands[c].first.second,rands[c].second);
            glVertex3f(0,  10*b, 0);
            glVertex3f(-5*a, 0, 5*a);
            glVertex3f( 5*a, 0, 5*a);
c++;
            glColor3ub(rands[c].first.first, rands[c].first.second,rands[c].second);
            glVertex3f(0,  10*b, 0);
            glVertex3f(-5*a, 0, 5*a);
            glVertex3f(-5*a, 0, -5*a);
c++;
            glColor3ub(rands[c].first.first, rands[c].first.second,rands[c].second);
            glVertex3f(0,  10*b, 0);
            glVertex3f( 5*a, 0, 5*a);
            glVertex3f(5*a,  0, -5*a);
        glEnd();

        // Finally, display the rendered frame on screen
        game.App.display();
    }
    if(xort==0)
    {
        game.App.close();
        return 0;
    }*/
