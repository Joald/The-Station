#include "The Station.h"
using namespace std;
Station::Station()
{
    this->soundEnabled=true;
    if(sf::VideoMode::getDesktopMode().width==1920 && sf::VideoMode::getDesktopMode().height==1080)
    {
        this->w=1920;
        this->h=1080;
        App.create(sf::VideoMode(w,h), "The Station",sf::Style::Fullscreen);
        this->isUnsized=false;
        this->bgt.loadFromFile("bg.png");
        this->player.loadFromFile("player.png");
        this->progt.loadFromFile("podprog.png");
        this->guii.loadFromFile("gui.png");
        this->explot.loadFromFile("explosn.png");
        this->guit.loadFromImage(this->guii);
        this->arial.loadFromFile("arial.ttf");
        this->t0.loadFromFile("items.png");
        this->shots.loadFromFile("pew.wav");
        this->bossrt.loadFromFile("bossroom.png");
        this->bosst.loadFromFile("boss.png");
        this->lodin.loadFromFile("loading.png");
        this->timin.loadFromFile("timing.png");
        this->cx=5;
        this->cy=5;
        this->cheatsEnabled=false;
        this->invt.loadFromFile("invent.png");
        this->selectinvt.loadFromFile("select.png");
        this->dti.loadFromFile("doorup.png");
        this->dtopt.loadFromImage(this->dti);
        this->dbi.loadFromFile("doorbot.png");
        this->dli.loadFromFile("doorleft.png");
        this->dri.loadFromFile("doorright.png");
        this->drightt.loadFromImage(this->dri);
        this->dleftt.loadFromImage(this->dli);
        this->dbottomt.loadFromImage(this->dbi);
        this->start.loadFromFile("newgame.png");
        this->mainmen.loadFromFile("title.png");
        this->exit.loadFromFile("exit.png");
        this->optionz.loadFromFile("options.png");
        this->paus.loadFromFile("pause.png");
        this->optionp.loadFromFile("optionp.png");
        this->exitp.loadFromFile("exitp.png");
        this->menup.loadFromFile("menup.png");
        this->endscr.loadFromFile("endscreen.png");
        this->optionsmain.loadFromFile("optionsmain.png");
    }
    else
    {
        w=1024;
        h=576;
        App.create(sf::VideoMode(w,h), "The Station"/*,sf::Style::Fullscreen*/);

        this->isUnsized=true;
        this->bgt.loadFromFile("xbg.png");
        this->player.loadFromFile("player.png");

        this->progt.loadFromFile("xpodprog.png");
        this->guii.loadFromFile("xgui.png");
        this->explot.loadFromFile("explosn.png");
        this->guit.loadFromImage(this->guii);
        this->arial.loadFromFile("arial.ttf");
        this->t0.loadFromFile("xitems.png");
        this->shots.loadFromFile("pew.wav");
        this->bossrt.loadFromFile("xbossroom.png");
        this->bosst.loadFromFile("xboss.png");
        this->lodin.loadFromFile("xloading.png");
        this->timin.loadFromFile("xtiming.png");
        this->cx=5;
        this->cy=5;
        this->cheatsEnabled=false;
        this->invt.loadFromFile("xinvent.png");
        this->selectinvt.loadFromFile("xselect.png");
        this->dti.loadFromFile("xdoorup.png");
        this->dtopt.loadFromImage(this->dti);
        this->dbi.loadFromFile("xdoorbot.png");
        this->dli.loadFromFile("xdoorleft.png");
        this->dri.loadFromFile("xdoorright.png");
        this->drightt.loadFromImage(this->dri);
        this->dleftt.loadFromImage(this->dli);
        this->dbottomt.loadFromImage(this->dbi);

        this->start.loadFromFile("newgame.png");
        this->mainmen.loadFromFile("xtitle.png");
        this->exit.loadFromFile("exit.png");
        this->optionz.loadFromFile("options.png");
        this->paus.loadFromFile("xpause.png");
        this->optionp.loadFromFile("optionp.png");
        this->exitp.loadFromFile("exitp.png");
        this->menup.loadFromFile("menup.png");
        this->endscr.loadFromFile("xendscreen.png");
        this->optionsmain.loadFromFile("xoptionsmain.png");
    }

    this->explos.loadFromFile("xplosion.wav");
}




bool inRect(int px,int py,int top,int left,int width,int height)
{
    return (px>left && px<left+width && py>top && py<top+height);
}
void Station::inventory(CMob& target)
{
    sf::Sprite invbg;
    sf::Sprite weapon,gui;
    gui.setTexture(guit);
    sf::Texture wt;
    wt.loadFromFile("weapon.png");
    sf::IntRect weaprects[6];
    for(int i=0; i<6; i++)
    {
        weaprects[i].height=79;
        weaprects[i].width=224;
        weaprects[i].left=0;
        weaprects[i].top=i*79;
    }


    weapon.setTexture(wt);

    weapon.setPosition(w/100,h/32);
    invbg.setTexture(invt);
    invbg.setPosition(0,0);
    sf::Sprite a[5][3];
    sf::Text infotext;
    sf::Sprite select;
    select.setTexture(selectinvt);
    int q=w*5/100;
    q=86;
    int z=h*295/1000;
    z=302;
    int p=w*192/1000;
    p=371;
    int o=h*234/1000;
    o=259;
    a[0][0].setPosition(q,z);
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<3; j++)
        {
            a[i][j].setTexture(t0);
            if(!i && !j)
                continue;
            a[i][j].setPosition(q+i*p,z+j*o);
        }
    }
    bool isset[5][3]= {false};
    sf::IntRect rects[5][3];
    rects[0][0].top=0;
    rects[0][0].left=0;
    rects[0][0].width=t0.getSize().x/5;
    rects[0][0].height=t0.getSize().y/3;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(!i && !j)
                continue;
            rects[i][j].width=t0.getSize().x/5;
            rects[i][j].height=t0.getSize().y/3;
            if(!i)
            {
                rects[i][j].left=0;
            }
            else
            {
                rects[i][j].left=rects[i-1][j].left+rects[i][j].width;
            }
            if(!j)
            {
                rects[i][j].top=0;
            }
            else
            {
                rects[i][j].top=rects[i][j-1].top+rects[i][j].height;
            }
        }
    }

    sf::RectangleShape tooltip(sf::Vector2f(350,125));
    sf::Text title,desc,flavor;
    tooltip.setFillColor(sf::Color::Black);
    title.setFont(arial);
    title.setStyle(sf::Text::Bold );
    flavor.setStyle(sf::Text::Italic);
    desc.setFont(arial);
    flavor.setFont(arial);
    title.setCharacterSize(20);
    desc.setCharacterSize(15);
    flavor.setCharacterSize(10);
    title.setColor(sf::Color::White);
    desc.setColor(sf::Color::White);
    flavor.setColor(sf::Color::White);


    sf::Text hpbar;

    hpbar.setColor(sf::Color::White);
    hpbar.setPosition(w*255/1000,h*25/1000);
    hpbar.setFont(arial);

    while(true)
    {
        bool throwed=false;
        bool click=false;
        sf::Event event;
        while (App.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                App.close();
                break;
            case sf::Event::MouseButtonPressed:
                click = true;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Tab)
                {
                    return;
                }
                if(event.key.code ==sf::Keyboard::R)
                    throwed=false;
            default:
                break;
            }
        }

        App.draw(gui);
        weapon.setTextureRect(weaprects[target.inv[target.weaponiter].getId()]);
        App.draw(weapon);
        sf::String hptext;
        ostringstream convert;
        convert<<target.health;
        hptext=convert.str();
        convert.str(std::string());
        hpbar.setString(hptext);
        App.draw(hpbar);
        bool mouseOver=false;
        App.draw(invbg);
        for(int j=0; j<5; j++)
        {
            for(int k=0; k<3; k++)
            {
                isset[j][k]=false;

            }
        }
        ///Code here starts
        for(int i=0; i<target.inv.size(); i++)
        {
            switch(target.inv[i].getId())
            {
            case 0:/// DEFAULT GUN
                for(int k=0; k<3; k++)
                {
                    for(int j=0; j<5; j++)
                    {
                        if(!isset[j][k])
                        {

                            if(inRect(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y,a[j][k].getPosition().y,a[j][k].getPosition().x,rects[j][k].width,rects[j][k].height))
                            {
                                if(click)
                                {
                                    target.useItem(i);
                                }
                                if(throwed)
                                    target.deleteItem(i,1);
                                int l=q+j*p;
                                int t=z+k*o;
                                select.setPosition(l,t);
                                App.draw(select);

                                mouseOver=true;
                                isset[j][k]=true;
                                a[j][k].setTextureRect(rects[0][0]);
                                App.draw(a[j][k]);

                                tooltip.setPosition(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);
                                string option="";
                                if(target.weaponiter==i)
                                {
                                    option=" (Currently equipped)";
                                }
                                title.setString ("Training Gun"+option);
                                title.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+10);
                                desc.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+40);
                                flavor.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+100);
                                ostringstream strem;
                                strem<<"Standard Training Equipment. Damage: "<<target.inv[i].getEffectNum()<<" HP.";
                                desc.setString (strem.str());
                                flavor.setString ("Honestly, who would want THAT?");
                            }
                            else
                            {
                                isset[j][k]=true;
                                a[j][k].setTextureRect(rects[0][0]);
                                App.draw(a[j][k]);
                            }
                            if(target.inv[i].quant>1)
                            {
                                sf::Text quanttext;
                                quanttext.setCharacterSize(40);
                                quanttext.setColor(sf::Color::White);
                                quanttext.setFont(arial);
                                quanttext.setPosition(q+j*p+230,z+k*o+170);
                                ostringstream strem;
                                strem<<target.inv[i].quant;
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
                for(int k=0; k<3; k++)
                {
                    for(int j=0; j<5; j++)
                    {
                        if(!isset[j][k])
                        {

                            if(inRect(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y,a[j][k].getPosition().y,a[j][k].getPosition().x,rects[j][k].width,rects[j][k].height))
                            {
                                /// if selected
                                if(click)
                                {
                                    target.useItem(i);
                                }
                                if(throwed)
                                    target.deleteItem(i,1);
                                int l=q+j*p;
                                int t=z+k*o;
                                select.setPosition(l,t);
                                App.draw(select);

                                mouseOver=true;
                                isset[j][k]=true;
                                a[j][k].setTextureRect(rects[2][0]);
                                App.draw(a[j][k]);

                                tooltip.setPosition(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);
                                string option="";
                                if(target.weaponiter==i)
                                {
                                    option=" (Currently equipped)";
                                }
                                title.setString ("Basic Rifle"+option);
                                title.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+10);
                                desc.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+40);
                                flavor.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+100);
                                ostringstream strem;
                                strem<<"Standard Patrol Equipment. Damage: "<<target.inv[i].getEffectNum()<<" HP.";
                                desc.setString (strem.str());
                                flavor.setString ("Not the greatest, but will do.");
                            }
                            else
                            {
                                isset[j][k]=true;
                                a[j][k].setTextureRect(rects[2][0]);
                                App.draw(a[j][k]);
                            }
                            if(target.inv[i].quant>1)
                            {
                                sf::Text quanttext;
                                quanttext.setCharacterSize(40);
                                quanttext.setColor(sf::Color::White);
                                quanttext.setFont(arial);
                                quanttext.setPosition(q+j*p+230,z+k*o+170);
                                ostringstream strem;
                                strem<<target.inv[i].quant;
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
                for(int k=0; k<3; k++)
                {
                    for(int j=0; j<5; j++)
                    {
                        if(!isset[j][k])
                        {

                            if(inRect(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y,a[j][k].getPosition().y,a[j][k].getPosition().x,rects[j][k].width,rects[j][k].height))
                            {
                                /// if selected
                                if(click)
                                {
                                    target.useItem(i);
                                }
                                if(throwed)
                                    target.deleteItem(i,1);
                                int l=q+j*p;
                                int t=z+k*o;
                                select.setPosition(l,t);
                                App.draw(select);

                                mouseOver=true;
                                isset[j][k]=true;
                                a[j][k].setTextureRect(rects[3][0]);
                                App.draw(a[j][k]);

                                tooltip.setPosition(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);
                                string option="";
                                if(target.weaponiter==i)
                                {
                                    option=" (Currently equipped)";
                                }
                                title.setString ("Rare Rifle"+option);
                                title.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+10);
                                desc.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+40);
                                flavor.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+100);
                                ostringstream strem;
                                strem<<"Reserved for the best soldiers. Damage: "<<target.inv[i].getEffectNum()<<" HP.";
                                desc.setString (strem.str());
                                flavor.setString ("Pretty hard to come by these days.");
                            }
                            else
                            {
                                isset[j][k]=true;
                                a[j][k].setTextureRect(rects[3][0]);
                                App.draw(a[j][k]);
                            }
                            if(target.inv[i].quant>1)
                            {
                                sf::Text quanttext;
                                quanttext.setCharacterSize(40);
                                quanttext.setColor(sf::Color::White);
                                quanttext.setFont(arial);
                                quanttext.setPosition(q+j*p+230,z+k*o+170);
                                ostringstream strem;
                                strem<<target.inv[i].quant;
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
                for(int k=0; k<3; k++)
                {
                    for(int j=0; j<5; j++)
                    {
                        if(!isset[j][k])
                        {

                            if(inRect(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y,a[j][k].getPosition().y,a[j][k].getPosition().x,rects[j][k].width,rects[j][k].height))
                            {
                                /// if selected
                                if(click)
                                {
                                    target.useItem(i);
                                }
                                if(throwed)
                                    target.deleteItem(i,1);
                                int l=q+j*p;
                                int t=z+k*o;
                                select.setPosition(l,t);
                                App.draw(select);

                                mouseOver=true;
                                isset[j][k]=true;
                                a[j][k].setTextureRect(rects[4][0]);
                                App.draw(a[j][k]);

                                tooltip.setPosition(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);
                                string option="";
                                if(target.weaponiter==i)
                                {
                                    option=" (Currently equipped)";
                                }
                                title.setString ("Mini RPG"+option);
                                title.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+10);
                                desc.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+40);
                                flavor.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+100);
                                ostringstream strem;
                                strem<<"Explodes on hit. Damage: "<<target.inv[i].getEffectNum()<<" HP.";
                                desc.setString (strem.str());
                                flavor.setString ("Now with EXPLOSIONS!!!");
                            }
                            else
                            {
                                isset[j][k]=true;
                                a[j][k].setTextureRect(rects[4][0]);
                                App.draw(a[j][k]);
                            }
                            if(target.inv[i].quant>1)
                            {
                                sf::Text quanttext;
                                quanttext.setCharacterSize(40);
                                quanttext.setColor(sf::Color::White);
                                quanttext.setFont(arial);
                                quanttext.setPosition(q+j*p+230,z+k*o+170);
                                ostringstream strem;
                                strem<<target.inv[i].quant;
                                quanttext.setString(strem.str());
                                App.draw(quanttext);
                            }

                            goto contWeapon4;
                        }

                    }
                }
contWeapon4:
            case 4:/// fiff GUN
                for(int k=0; k<3; k++)
                {
                    for(int j=0; j<5; j++)
                    {
                        if(!isset[j][k])
                        {

                            if(inRect(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y,a[j][k].getPosition().y,a[j][k].getPosition().x,rects[j][k].width,rects[j][k].height))
                            {
                                /// if selected
                                if(click)
                                {
                                    target.useItem(i);
                                }
                                if(throwed)
                                    target.deleteItem(i,1);
                                int l=q+j*p;
                                int t=z+k*o;
                                select.setPosition(l,t);
                                App.draw(select);

                                mouseOver=true;
                                isset[j][k]=true;
                                a[j][k].setTextureRect(rects[0][1]);
                                App.draw(a[j][k]);

                                tooltip.setPosition(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);
                                string option="";
                                if(target.weaponiter==i)
                                {
                                    option=" (Currently equipped)";
                                }
                                title.setString ("Big RPG"+option);
                                title.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+10);
                                desc.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+40);
                                flavor.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+100);
                                ostringstream strem;
                                strem<<"Most powerful rifle in the game. Damage: "<<target.inv[i].getEffectNum()<<" HP.";
                                desc.setString (strem.str());
                                flavor.setString ("The Ultimate Badassery");
                            }
                            else
                            {
                                isset[j][k]=true;
                                a[j][k].setTextureRect(rects[0][1]);
                                App.draw(a[j][k]);
                            }
                            if(target.inv[i].quant>1)
                            {
                                sf::Text quanttext;
                                quanttext.setCharacterSize(40);
                                quanttext.setColor(sf::Color::White);
                                quanttext.setFont(arial);
                                quanttext.setPosition(q+j*p+230,z+k*o+170);
                                ostringstream strem;
                                strem<<target.inv[i].quant;
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
                for(int k=0; k<3; k++)
                {
                    for(int j=0; j<5; j++)
                    {
                        if(!isset[j][k])
                        {
                            if(inRect(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y,a[j][k].getPosition().y,a[j][k].getPosition().x,rects[j][k].width,rects[j][k].height))
                            {
                                if(click)
                                {
                                    target.useItem(i);
                                }
                                if(throwed)
                                    target.deleteItem(i,1);
                                int l=q+j*p;
                                int t=z+k*o;
                                select.setPosition(l,t);
                                App.draw(select);

                                mouseOver=true;
                                isset[j][k]=true;
                                a[j][k].setTextureRect(rects[1][0]);
                                App.draw(a[j][k]);

                                tooltip.setPosition(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);
                                title.setString ("Standard Medkit");
                                title.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+10);
                                desc.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+40);
                                flavor.setPosition(sf::Mouse::getPosition().x+10,sf::Mouse::getPosition().y+100);
                                ostringstream strem;
                                strem<<"Standard Training Equipment. Heals for "<<target.inv[i].getEffectNum()<<" HP.";
                                desc.setString (strem.str());
                                flavor.setString ("Use it wisely.");
                            }
                            else
                            {
                                isset[j][k]=true;
                                a[j][k].setTextureRect(rects[1][0]);
                                App.draw(a[j][k]);
                            }
                            if(target.inv[i].quant>1)
                            {
                                sf::Text quanttext;
                                quanttext.setCharacterSize(40);
                                quanttext.setColor(sf::Color::White);
                                quanttext.setFont(arial);
                                quanttext.setPosition(q+j*p+230,z+k*o+170);
                                ostringstream strem;
                                strem<<target.inv[i].quant;
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

            continue;
        }
        ///Code here ends
        /*for(int i=0; i<5; i++)
        {
            for(int j=0; j<3; j++)
            {
                App.draw(a[i][j]);
            }
        }*/
        if(mouseOver)
        {
            App.draw(tooltip);
            App.draw(title);
            App.draw(desc);
            App.draw(flavor);
        }
        App.display();
    }
}



void Station::explode(int x,int y)
{
    explosion a(x,y);
    a.s.setTexture(this->explot);
    this->exp.push_back(a);
    if(!soundEnabled)
        return;
    sf::Sound b;
    b.setBuffer(explos);
    this->blasts.push_back(b);
    this->blasts[this->blasts.size()-1].play();
}

void Station::endapp()
{
    ///maybe some outro
    App.close();
}
void Station::intro()
{
    ///something
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("intro.wav"))
        return;
    sf::Sound intr;
    intr.setBuffer(buffer);
    intr.play();
    sf::Texture intrt;
    if (!intrt.loadFromFile("timing.png"))
        return;
    sf::Sprite tim;
    tim.setTexture(intrt);
    sf::Text tet;
    tet.setPosition(this->w*74/100,this->h*44/100);
    sf::Font games;
    games.loadFromFile("games.ttf");
    tet.setFont(games);
    tet.setCharacterSize(100);
    tet.setColor(sf::Color::White);
    //int b=700;
    int state=0;
    int ox=50;
    sf::Time as;
    as=sf::milliseconds(14);
    while(true)
    {
        sf::Event event;
        while (App.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                App.close();
                return;
                break;
            default:
                break;
            }
        }
        if(ox==50)
        {
            switch(state)
            {
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
            ox=0;
        }
        ox++;

        App.draw(tim);
        App.draw(tet);
        App.display();
        sf::sleep(as);
    }



}
int Station::pause()
{

    menusic.openFromFile("mainmenu.wav");
    menusic.setLoop(true);
    menusic.play();
    sf::Sprite pau,opt,ext,men;
    men.setTexture(this->menup);
    opt.setTexture(this->optionp);
    pau.setTexture(this->paus);
    ext.setTexture(this->exitp);
    if(this->isUnsized)
    {
        men.setScale(8/15.f,8/15.f);
        opt.setScale(8/15.f,8/15.f);
        ext.setScale(8/15.f,8/15.f);
    }
    int lef =w*2980/10000;
    int righ=w*655/1000;
    int top1=h*3650/10000;
    int top2=h*5050/10000;
    int top3=h*6465/10000;
    int bot1=h*500/1000;
    int bot2=h*600/1000;
    int bot3=h*750/1000;
    ext.setPosition(lef+2,top1);
    opt.setPosition(lef+1,top2);
    men.setPosition(lef,top3);
    while(true)
    {
        sf::Event event;
        bool click=false;
        while (App.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                App.close();
                break;
            case sf::Event::MouseButtonPressed:
                click = true;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Tab)
                {
                    menusic.stop();
                    return 1;
                }
                if(event.key.code == sf::Keyboard::Escape)
                {
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
        if(sf::Mouse::getPosition().x>lef && sf::Mouse::getPosition().x<righ && sf::Mouse::getPosition().y>top1 && sf::Mouse::getPosition().y<bot1)
        {
            if(click)
            {
                menusic.stop();
                return 2;
            }
            App.draw(ext);
        }
        if(sf::Mouse::getPosition().x>lef && sf::Mouse::getPosition().x<righ && sf::Mouse::getPosition().y>top2 && sf::Mouse::getPosition().y<bot2)
        {
            if(click)
            {
                options(1);
            }
            App.draw(opt);
        }
        if(sf::Mouse::getPosition().x>lef && sf::Mouse::getPosition().x<righ && sf::Mouse::getPosition().y>top3 && sf::Mouse::getPosition().y<bot3)
        {
            if(click)
            {

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
void Station::toggleCheatsEnabled()
{
    if(!cheatsEnabled)
        cheatsEnabled=true;
    else
        cheatsEnabled=false;
}
void Station::toggleSoundEnabled()
{
    if(!soundEnabled){
        soundEnabled=true;
        menusic.setVolume(100);
        menusic.play();
    }
    else{
        soundEnabled=false;
        menusic.pause();
        menusic.setVolume(0);
        blasts.clear();
    }
}
void Station::options(int source )///0 - main, 1 - pause
{
    /*if(source==0)
    {*/
        ///mainmenu
        sf::Sprite bg(this->optionsmain);

        sf::Sprite men, strt, optns,ext;
        men.setTexture(this->mainmen);
        strt.setTexture(this->start);
        optns.setTexture(this->optionz);
        ext.setTexture(this->exit);
        int lef =w*2705/10000;
        int righ=w*655/1000;
        int top1=h*3851/10000;
        int top2=h*5904/10000;
        int top3=h*7811/10000;
        int bot1=h*500/1000;
        int bot2=h*700/1000;
        int bot3=h*950/1000;
        strt.setPosition(lef,top1);
        optns.setPosition(lef,top2);
        ext.setPosition(lef,top3);
        sf::Text a,b,c;
        sf::Font games;
        games.loadFromFile("games.ttf");
        a.setFont(games);
        b.setFont(games);
        c.setFont(games);
        a.setCharacterSize(50);
        b.setCharacterSize(50);
        c.setCharacterSize(50);
        a.setPosition(lef*1.3,top1*1.1);
        b.setPosition(lef*1.3,top2*1.1);
        c.setPosition(lef*1.3,top3*1.1);

        c.setString("BACK");
        while(true)
        {
            sf::Event event;
            bool click=false;
            while (App.pollEvent(event))
            {
                switch (event.type)
                {
                case sf::Event::Closed:
                    App.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    click = true;
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Tab)
                    {

                        return;
                    }

                default:
                    break;
                }
            }
            App.clear();
            App.draw(bg);
            sf::String czits;
            if(cheatsEnabled)
                czits="Cheats are ON";
            else
                czits="Cheats are OFF";
            sf::String saunds;
            if(soundEnabled)
                saunds="Sounds are ON";
            else
                saunds="Sounds are OFF";
            a.setString(czits);
            b.setString(saunds);App.draw(a); App.draw(b);App.draw(c);
            if(sf::Mouse::getPosition().x>lef && sf::Mouse::getPosition().x<righ && sf::Mouse::getPosition().y>top1 && sf::Mouse::getPosition().y<bot1)
            {
                if(click)
                {
                    toggleCheatsEnabled();
                }

            }
            if(sf::Mouse::getPosition().x>lef && sf::Mouse::getPosition().x<righ && sf::Mouse::getPosition().y>top2 && sf::Mouse::getPosition().y<bot2)
            {
                if(click)
                {
                    toggleSoundEnabled();
                }

            }
            if(sf::Mouse::getPosition().x>lef && sf::Mouse::getPosition().x<righ && sf::Mouse::getPosition().y>top3 && sf::Mouse::getPosition().y<bot3)
            {
                if(click)
                {
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
bool Station::mainmenu()
{

    menusic.openFromFile("mainmenu.wav");
    menusic.setLoop(true);
    menusic.play();
    sf::Sprite men, strt, optns,ext;
    men.setTexture(this->mainmen);
    strt.setTexture(this->start);
    optns.setTexture(this->optionz);
    ext.setTexture(this->exit);
    if(this->isUnsized)
    {
        strt.setScale(8/15.f,8/15.f);
        optns.setScale(8/15.f,8/15.f);
        ext.setScale(8/15.f,8/15.f);
    }
    int lef =w*2705/10000;
    int righ=w*655/1000;
    int top1=h*2851/10000;
    int top2=h*4704/10000;
    int top3=h*6511/10000;
    int bot1=h*400/1000;
    int bot2=h*600/1000;
    int bot3=h*800/1000;
    strt.setPosition(lef,top1);
    optns.setPosition(lef,top2);
    ext.setPosition(lef,top3);
    while(true)
    {
        sf::Event event;
        bool click=false;
        while (App.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                App.close();
                break;
            case sf::Event::MouseButtonPressed:
                click = true;
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Tab)
                {
                    menusic.stop();
                    return 0;
                }

            default:
                break;
            }
        }
        App.clear();
        App.draw(men);
        if(sf::Mouse::getPosition().x>lef && sf::Mouse::getPosition().x<righ && sf::Mouse::getPosition().y>top1 && sf::Mouse::getPosition().y<bot1)
        {
            if(click)
            {
                goto startgame;
            }
            App.draw(strt);
        }
        if(sf::Mouse::getPosition().x>lef && sf::Mouse::getPosition().x<righ && sf::Mouse::getPosition().y>top2 && sf::Mouse::getPosition().y<bot2)
        {
            if(click)
            {
                options(0);
                click=false;
            }
            App.draw(optns);
        }
        if(sf::Mouse::getPosition().x>lef && sf::Mouse::getPosition().x<righ && sf::Mouse::getPosition().y>top3 && sf::Mouse::getPosition().y<bot3)
        {
            if(click)
            {
                menusic.stop();
                return 0;
            }
            App.draw(ext);
        }
        App.display();
    }
startgame:
    menusic.stop();
    return 1;
}
//void Station::
