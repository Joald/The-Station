#include "../include/Room.h"

#define fixw 170
#define fixh 291

#define w 1920
#define h 1080

Room::Room(Station &game) {
    this->chest_max = 15;
    this->floort.loadFromFile("../img/floor_tile.png");
    ///this->dti.loadFromFile("doorup.png");
    ///this->dtopt.loadFromImage(this->dti);
    ///this->dbi.loadFromFile("doorbot.png");
    ///this->dli.loadFromFile("doorleft.png");
    ///this->dri.loadFromFile("doorright.png");
    ///this->drightt.loadFromImage(this->dri);
    ///this->dleftt.loadFromImage(this->dli);
    ///this->dbottomt.loadFromImage(this->dbi);
    this->enemyt.loadFromFile("../img/enemy.png");
    this->chestt.loadFromFile("../img/chest.png");
    this->sht.loadFromFile("../img/shot.png");

    this->dropst.loadFromFile("../img/items_small.png");
    this->dbottom = true;
    this->dtop = true;
    this->dleft = true;
    this->dright = true;
    this->chestcount = 0;
    this->isempty = true;
    this->type = 0;
    //srand(time(0));
    int los;
    los = rand() % 100;
    if (los > 10)
        this->floortile[0][0].sprite.setTexture(this->floort);
    else
        this->floortile[0][0].sprite.setTexture(this->chestt);
    this->floortile[0][0].sprite.setPosition(fixw * w / 1920, fixh * h / 1080);
    this->floortile[0][0].x = fixw * w / 1920;
    this->floortile[0][0].y = fixh * h / 1080;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sf::Time t1 = sf::milliseconds(5);
            sf::sleep(t1);
            this->floortile[i][j].walkable = true;
            los = rand() % 100;
            if (!this->floortile[i - 1][j].walkable || !this->floortile[i][j - 1].walkable ||
                !this->floortile[i][j + 1].walkable || !this->floortile[i + 1][j].walkable)
                los /= 2;
            if (((i == 7 || i == 8) && (j == 0 || j == m - 1)) || ((i == 0 || i == n - 1) && j == 2) ||
                ((i == 7 || i == 8) && j == 2))
                los = 100;
            if (los < 10 && this->chestcount < this->chest_max) {
                this->floortile[i][j].sprite.setTexture(this->chestt);
                this->floortile[i][j].walkable = false;
                this->floortile[i][j].type = 1;
                this->chestcount++;
            } else {
                this->floortile[i][j].sprite.setTexture(this->floort);
                this->floortile[i][j].walkable = true;
                this->floortile[i][j].type = 0;
            }
            if (i || j) {
                if (!i) {
                    this->floortile[i][j].sprite.setPosition(fixw * w / 1920,
                                                             this->floortile[i][j - 1].y + this->floort.getSize().y);
                    this->floortile[i][j].x = fixw * w / 1920;
                    this->floortile[i][j].y = this->floortile[i][j - 1].y + this->floort.getSize().y;
                    continue;
                }
                if (!j) {
                    this->floortile[i][j].sprite.setPosition(this->floortile[i - 1][j].x + this->floort.getSize().x,
                                                             fixh * h / 1080);
                    this->floortile[i][j].x = this->floortile[i - 1][j].x + this->floort.getSize().x;
                    this->floortile[i][j].y = fixh * h / 1080;
                    continue;
                } else {
                    this->floortile[i][j].sprite.setPosition(this->floortile[i - 1][j].x + this->floort.getSize().x,
                                                             this->floortile[i][j - 1].y + this->floort.getSize().y);
                    this->floortile[i][j].x = this->floortile[i - 1][j].x + this->floort.getSize().x;
                    this->floortile[i][j].y = this->floortile[i][j - 1].y + this->floort.getSize().y;
                }
            }
        }
    }
    sf::Time t1 = sf::milliseconds(15);
    sf::sleep(t1);
}

void Room::spawn_enemy(int x, int y, int typ) {
    sf::IntRect r1(0, 0, 50, 50);
    enemy a;
    a.x = x;
    a.y = y;
    a.C.setTexture(this->enemyt);
    a.C.setTextureRect(r1);
    a.T = this->enemyt;
    a.type = typ;
    a.inv.erase(a.inv.begin(), a.inv.end());
    a.addItem(typ, 0, 5 * typ + 5, 1);
    for (int i = 0; i < a.inv.size(); i++)
        a.useItem(i);
    /*a.damage=5*type+5;
    if(a.damage<5)
        a.damage=5;*/
    this->enem.push_back(a);
    ///int op=this->enem[this->enem.size()-1].inv[a.weaponiter].getEffectNum();
    ///int od=this->enem[this->enem.size()-1].inv[a.weaponiter].getId();
}

void Room::spawnTiledrop(enemy &source) {
    if (rand() % 3)
        return;
    int c = rand() % 2;
    int d;
    if (!c) {
        d = source.type;
    } else {
        d = 100;
    }
    item p(d, c, 20 + (source.type + 1) * 10);
    TileDrop a(source.x, source.y, p);
    a.s.setTexture(this->dropst);
    drops.push_back(a);
}
/*
void Room::changeTo (const Room& ox,FloorTile floortil[n][m])
{
    this->floort.loadFromFile("floor_tile.png");
    this->doorTopTexture.loadFromFile("doorup.png");
    this->doorBottomTexture.loadFromFile("doorbot.png");
    this->doorLeftTexture.loadFromFile("doorleft.png");
    this->doorRightTexture.loadFromFile("doorright.png");
    this->enemyt.loadFromFile("enemy.png");
    this->chestt.loadFromFile("chest.png");
    this->sht.loadFromFile("shot.png");
    this->chestcount=x.chestcount;
    this->chest_max=x.chest_max;
    this->dleft=x.dleft;
    this->dbottom=x.dbottom;
    this->dright=x.dright;
    this->dtop=x.dtop;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            //this->floortile[i][j].changeTo(ox.floortile[i][j]);
            int a=floortil[i][j].x;
            this->floortile[i][j].x=a;
            this->floortile[i][j].y=floortil[i][j].y;
            if(floortil[i][j].walkable)
                this->floortile[i][j].walkable=true;
            else
                this->floortile[i][j].walkable=false;
            if(this->floortile[i][j].type==0)
                this->floortile[i][j].sprite.setTexture(this->floort);
            if(this->floortile[i][j].type==1)
                this->floortile[i][j].sprite.setTexture(this->chestt);
        }
    }
    this->isempty=x.isempty;



}*/
