#include "Character.h"

#define n 16
#define m 6

void Character::DealDamage(int modifier) {
    this->health -= modifier;
    //int a=this->health;
}

void Character::Heal(int modifier) {
    this->health += modifier;
    if (health > maxhp)
        health = maxhp;
}

void Character::ModifySpeed(int modifier) {
    this->speed += modifier;
}

void Character::ModifyDamage(int modifier) {
    this->damage -= modifier;
}

void Character::ModifyArmor(int modifier) {
    this->armor += modifier;
}

Character::Character() {
    this->red = false;
    this->speed = 5;
    this->armor = 0;
    this->health = 100;

    this->shtdelay = 200;
    this->shtspeed = 10;
    this->invincible = false;
    maxhp = 100;
    item o(0, 0, 20);

    o.quant = 1;

    weaponiter = 0;
    this->damage = o.getEffectNum();


    int a = o.getEffectNum();
    this->damage = a;

    damage = a;

    //this->damage=100;
    addItem(o);


}

void Character::rotatexy_internal(float mouseX, float mouseY) {
    ///taking mouse coords for arguments
    float deltax, deltay, angle;///double variables for calculation
    deltax = getPosition().x - mouseX;///delta n = objects position n - mouse pos n
    deltay = getPosition().y - mouseY;
    angle = (std::atan2(deltay, deltax)) * 180 / PI - 90;/// trigonometry with arc tangent taking 2
    orient = angle;/// orient is a class angle variable
    setRotation(angle);///set rotation to object's sf::Sprite
    //return this->orient;
}

void Character::rotate2mouse(Station &game) {
    float a, b;
    a = getPosition().x - sf::Mouse::getPosition(game.App).x;
    b = getPosition().y - sf::Mouse::getPosition(game.App).y;
    orient = std::atan2(b, a) * 180 / PI;
    setRotation(orient - 90);
}

bool Character::shoot(std::vector<Projectile> &proj, float mx, float my) {
    if (this->health <= 0)
        return false;

    //for(int unsigned i=1; i<=proj.size(); i++)
    if (this->delay.getElapsedTime().asMilliseconds() < this->shtdelay)
        return false;

    Projectile a;


    //a.delay.restart();


    a.type = inv[weaponiter].getId();
    a.setorig(this);
    a.damage = damage;

    a.rotatexy(mx, my);
    this->delay.restart();
    proj.push_back(a);
    return true;
    /*Projectile *a;

    a = new Projectile;
    a->delay.restart();
    a->setorig(this);

    a->rotatexy_internal(mx,my);
    a->delay.restart();
    proj.push_back(*a);

    delete a;*/
}

bool Character::shoot(std::vector<Projectile> &proj, int mx, int my, bool ignore) {
    Projectile a;
    //a.delay.restart();
    a.type = inv[weaponiter].getId();
    a.setorig(this);

    a.rotatexy(mx, my);
    this->delay.restart();
    proj.push_back(a);
    return true;
    /*Projectile *a;

    a = new Projectile;
    a->delay.restart();
    a->setorig(this);

    a->rotatexy_internal(mx,my);
    a->delay.restart();
    proj.push_back(*a);

    delete a;*/
}

void Character::rotatexy(sf::Vector2f vector2f) {
    rotatexy_internal(vector2f.x, vector2f.y);
}


void enemy::rotatexy_internal(float mouseX, float mouseY) {
    float deltax, deltay, angle;                     ///double variables for calculation
    deltax = this->getPosition().x - mouseX;                              ///delta n = objects position n - mouse pos n
    deltay = this->getPosition().y - mouseY;
    angle = (std::atan2(deltay, deltax)) * 180 / PI - 90;         /// trigonometry with arc tangent taking 2
    this->orient = angle + 90;                          /// orient is a class angle variable
    this->setRotation(angle);                     ///set rotation to object's sf::Sprite
}

enemy::enemy() {
    this->damage = 0;
    this->ax = 0;
    this->ay = 0;
    this->shtdelay = 500;
    this->destroystate = 0;
    this->setOrigin(25, 25);
    inv.erase(inv.begin(), inv.end());
    addItem(0, 0, 5, 1);
}

void Character::toggleInvincible() {
    invincible = !invincible;
}

bool Character::canWalkDown(FloorTile floortile[n][m], Station &game) {
    auto ox = static_cast<int>(getPosition().x);
    auto oy = static_cast<int>(getPosition().y);

    int fixh = 291;
    if (game.isUnsized) {
        fixh = 155;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!floortile[i][j].walkable && ox > floortile[i][j].x && ox < floortile[i][j].x + 100 &&
                oy + 15 > floortile[i][j].y && oy < floortile[i][j].y + 104)
                return false;
        }
    }
    return getPosition().y > game.height - fixh + fixh * 2 / 6 == 0;

}

bool Character::canWalkUp(FloorTile floortile[16][6], Station &game) {
    auto ox = static_cast<int>(getPosition().x);
    auto oy = static_cast<int>(getPosition().y);
    int fixw = 170;
    int fixh = 291;
    if (game.isUnsized) {
        fixw = 91;
        fixh = 155;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!floortile[i][j].walkable && ox > floortile[i][j].x && ox < floortile[i][j].x + 100 &&
                oy > floortile[i][j].y && oy - 15 < floortile[i][j].y + 104)
                return false;
        }
    }
    return getPosition().y - 15 >= fixh;
}

bool Character::canWalkRight(FloorTile floortile[n][m], Station &game) {
    auto ox = static_cast<int>(getPosition().x);
    auto oy = static_cast<int>(getPosition().y);
    int fixw = 170;
    int fixh = 291;
    if (game.isUnsized) {
        fixw = 91;
        fixh = 155;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!floortile[i][j].walkable && ox + 15 > floortile[i][j].x && ox < floortile[i][j].x + 100 &&
                oy > floortile[i][j].y && oy < floortile[i][j].y + 104)
                return false;
        }
    }
    return getPosition().x <= game.width - fixw - fixw / 10;

}

bool Character::canWalkLeft(FloorTile floortile[n][m], Station &game) {
    auto ox = static_cast<int>(getPosition().x);
    auto oy = static_cast<int>(getPosition().y);
    int fixw = 170;
    int fixh = 291;
    if (game.isUnsized) {
        fixw = 91;
        fixh = 155;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!floortile[i][j].walkable && ox > floortile[i][j].x && ox - 15 < floortile[i][j].x + 100 &&
                oy > floortile[i][j].y && oy < floortile[i][j].y + 104)
                return false;
        }
    }

    return getPosition().x >= fixw;
}


///sprawdzanie wrogow


bool enemy::canWalkDown(FloorTile floortile[n][m], Station &game) {
    int a, b;
    int fixw = 170;
    int fixh = 291;
    if (game.isUnsized) {
        fixw = 91;
        fixh = 155;
    }
    a = (x_int() - fixw) / 100;
    b = (y_int() - fixh) / 104;
    return floortile[a][b].walkable && getPosition().y + 25 < floortile[a][b].y - 104 && getPosition().x <= game.height - fixh + fixh * 2 / 5;
}

bool enemy::canWalkUp(FloorTile floortile[n][m], Station &game) {
    int a, b;
    int fixw = 170;
    int fixh = 291;
    if (game.isUnsized) {
        fixw = 91;
        fixh = 155;
    }
    a = (y_int() - fixw) / 100;
    b = (y_int() - fixh) / 104;
    return floortile[a][b - 1].walkable && y_int() - 25 > floortile[a][b - 1].y + 104 && y_int() >= fixh;

}

bool enemy::canWalkRight(FloorTile floortile[n][m], Station &game) {
    int a, b;
    int fixw = 170;
    int fixh = 291;
    if (game.isUnsized) {
        fixw = 91;
        fixh = 155;
    }
    a = (x_int() - fixw) / 100;
    b = (y_int() - fixh) / 104;
    return floortile[a + 1][b].walkable && x_int() + 25 < floortile[a + 1][b].x && x_int() <= game.width - fixw - fixw / 20;
}

bool enemy::canWalkLeft(FloorTile floortile[n][m], Station &game) {
    int a, b;
    int fixw = 170;
    int fixh = 291;
    if (game.isUnsized) {
        fixw = 91;
        fixh = 155;
    }
    a = (x_int() - fixw) / 100;
    b = (y_int() - fixh) / 104;
    return floortile[a - 1][b].walkable && x_int() - 25 > floortile[a - 1][b].x + 100 && x_int() - 25 >= fixw;

}

int check(int x, int y, int x1, int y1, int x2, int y2) {
    return (y - y1) * (x2 - x1) - (y2 - y1) * (x - x1);//(y1-y2)*x + (x1-x2)*y + (x2*y1-x1*y2);
}

int squarex(FloorTile floortile[n][m], int x) {
    for (int i = 0; i < n; i++) {
        if ((floortile[i][0].x < x && floortile[i][0].x + 100 > x) || floortile[i][0].x == x)
            return i;
    }
    return 0;
}

int squarey(FloorTile floortile[n][m], int y) {
    for (int i = 0; i < m; i++) {
        if ((floortile[0][i].y < y && floortile[0][i].y + 104 > y) || floortile[0][1].y == y)
            return i;
    }
    return 0;
}

bool enemy::canSee(FloorTile floortile[n][m], float x2_f, float y2_f) {
    if (this->destroystate)
        return false;


    auto x1 = static_cast<int>(getPosition().x);
    auto y1 = static_cast<int>(getPosition().y);

    auto x2 = static_cast<int>(x2_f);
    auto y2 = static_cast<int>(y2_f);
    //int x1p=x1,x2p=x2,y1p=y1,y2p=y2;//faktyczne koordynaty
    //int playx=x2,playy=y2,enex=x1,eney=y1;
    x1 = squarex(floortile, x1);
    x2 = squarex(floortile, x2);
    y1 = squarey(floortile, y1);
    y2 = squarey(floortile, y2);
    /*long double len = max(abs(x2-x1), abs(y2-y1));
    for (int i = 0; i<len; i++)
    {
        //# interpolate between (x1,y1) && (x2,y2)
        long double t = float(i)/len;
        //# at t=0.0 we get (x1,y1); at t=1.0 we get (x2,y2)
        int ox = round(x1 * (1.0-t) + x2 * t);
        int oy = round(y1 * (1.0-t) + y2 * t);
        // now check FloorTile (x,y)
        if(!floortile[ox][oy].walkable)
            return false;
    }
    return true;*/
    ///          _
    /**vector<tile>v;            1 2 3 /   \
    bool sc=false;*/          ///4 p 5 | p |
    int pos = 0;///                6 7 8 \ _ /
    if (!pos) {
        if (x1 == x2)
            return true;
        if (x1 < x2 && y1 < y2)
            pos = 1;
        else if (x1 == x2 && y1 < y2)
            pos = 2;
        else if (x1 > x2 && y1 < y2)
            pos = 3;
        else if (x1 < x2 && y1 == y2)
            pos = 4;
        else if (x1 > x2 && y1 == y2)
            pos = 5;
        else if (x1 < x2 && y1 > y2)
            pos = 6;
        else if (x1 == x2 && y1 > y2)
            pos = 7;
        else if (x1 > x2 && y1 > y2)
            pos = 8;
    }
    if (pos == 2) {
        for (int i = y1; i < y2 + 1; i++) {
            if (!floortile[x1][i].walkable)
                return false;
        }
        return true;
    }
    if (pos == 4) {
        for (int i = x1; i < x2 + 1; i++) {
            if (!floortile[i][y1].walkable)
                return false;
        }
        return true;
    }
    if (pos == 5) {
        for (int i = x2; i < x1 + 1; i++) {
            if (!floortile[i][y1].walkable)
                return false;
        }
        return true;
    }
    if (pos == 7) {
        for (int i = y2; i < y1 + 1; i++) {
            if (!floortile[x1][i].walkable)
                return false;
        }
        return true;
    }
    int kx, ky;
    if (x1 <= x2)
        kx = 1;
    else
        kx = -1; //okre�lamy krok X od x1 do x2
    if (y1 < y2)
        ky = 1;
    else
        ky = -1; //okre�lamy krok Y od y1 do y2
    int dx = abs(x2 - x1); //odleg�o�� pomi�dzy x1 i x2
    int dy = abs(y2 - y1); //odleg�o�� pomi�dzy y1 i y2

    if (dx > dy) //, id� do kroku K16	; //dla k�t�w > 45� wykonujemy wersj� algorytmu z przestawionymi wsp�rz�dnymi
    {
        double e = dx / 2; //obliczamy warto�� pocz�tkow� wyra�enia b��du
        for (int i = 0; i < dx; i++) // razy kroki K09...K14	; //rysujemy pozosta�e piksele w p�tli
        {
            x1 = x1 + kx; //przesuwamy si� w odpowiedni� stron� w kierunku szybkim
            e = e - dy; //obliczamy wyra�enie b��du
            if (e < 0) //, id� do kroku K14	; //je�li wyra�enie b��du jest nieujemne, pomijamy ruch w kierunku wolnym
            {
                y1 = y1 + ky; //przesuwamy si� w odpowiedni� stron� w kierunku wolnym
                e = e + dx;
            } //obliczamy nowe wyra�enie b��du
            if (!floortile[x1][y1].walkable) //kolejny piksel odcinka
                return false;
        }
    } else {
        double e = dy / 2; //wersja algorytmu Bresenhama ze zamienionymi wsp�rz�dnymi x i y
        for (int i = 0; i < dy; i++) // razy kroki K18...K23
        {
            y1 = y1 + ky;
            e = e - dx;
            if (e < 0) {
                x1 = x1 + kx;
                e = e + dy;
            }
            if (!floortile[x1][y1].walkable)
                return false;
        }
    }
    return true;
    /*
    switch(pos)
    {
    case 1:
        for(int i=x1; i<x2; i++)
        {
            for(int j=y1; j<y2; j++)
            {
                if(!floortile[i][j].walkable)
                {
                    ///                               x y  x y
                    int e=floortile[i][j].x;    ///e c  q c
                    int c=floortile[i][j].y;
                    int q=floortile[i][j].x+100;///e z  q z
                    int z=floortile[i][j].y+104;
                    //int a =check(enex,eney,q,c,e,z);
                    //if(!a && atan2(playx-enex,playy-eney)>atan2(playx-e,playy-z) && atan2(playx-enex,playy-eney)<atan2(playx-q,playy-c))
                    return false;
                    int a,b,c,d;
                    a=check(floortile[i][j].x,floortile[i][j].y,x1p,y1p,x2p,y2p);
                    b=check(floortile[i][j].x+100,floortile[i][j].y,x1p,y1p,x2p,y2p);
                    c=check(floortile[i][j].x,floortile[i][j].y+104,x1p,y1p,x2p,y2p);
                    d=check(floortile[i][j].x+100,floortile[i][j].y+104,x1p,y1p,x2p,y2p);
                    if(a==0)
                        continue;
                    if(b==0)
                        continue;
                    if(c==0)
                        continue;
                    if(d==0)
                        continue;
                    if(a<0 && b<0 && c<0 && d<0)
                        continue;
                    if(a>0 && b>0 && c>0 && d>0)
                        continue;
                    return false;//return LineIntersectsSquare(x1p,y1p,x2p,y2p,floortile[i][j].x,floortile[i][j].y,floortile[i][j].x+100,floortile[i][j].y+104);

                }
            }
        }
        break;
    case 2:
        for(int i=y1; i<y2; i++)
        {
            if(!floortile[x1][i].walkable)
                return false;
        }
        break;
    case 3:
        for(int i=x2; i<x1; i++)
        {
            for(int j=y1; j<y2; j++)
            {
                if(!floortile[i][j].walkable)
                {
                    int a,b,c,d;
                    a=check(floortile[i][j].x,floortile[i][j].y,x1p,y1p,x2p,y2p);
                    b=check(floortile[i][j].x+100,floortile[i][j].y,x1p,y1p,x2p,y2p);
                    c=check(floortile[i][j].x,floortile[i][j].y+104,x1p,y1p,x2p,y2p);
                    d=check(floortile[i][j].x+100,floortile[i][j].y+104,x1p,y1p,x2p,y2p);
                    if(a==0)
                        continue;
                    if(b==0)
                        continue;
                    if(c==0)
                        continue;
                    if(d==0)
                        continue;
                    if(a<0 && b<0 && c<0 && d<0)
                        continue;
                    if(a>0 && b>0 && c>0 && d>0)
                        continue;
                    return false;return LineIntersectsSquare(x1p,y1p,x2p,y2p,floortile[i][j].x,floortile[i][j].y,floortile[i][j].x+100,floortile[i][j].y+104);
                }
            }
        }
        break;
    case 4:
        for(int i=x1; i<x2; i++)
        {
            if(!floortile[i][y1].walkable)
                return false;
        }
        break;
    case 5:
        for(int i=x2; i<x1; i++)
        {
            if(!floortile[i][y1].walkable)
                return false;
        }
        break;
    case 6:
        for(int i=x1; i<x2; i++)
        {
            for(int j=y2; j<y1; j++)
            {
                if(!floortile[i][j].walkable)
                {
                    int a,b,c,d;
                    a=check(floortile[i][j].x,floortile[i][j].y,x1p,y1p,x2p,y2p);
                    b=check(floortile[i][j].x+100,floortile[i][j].y,x1p,y1p,x2p,y2p);
                    c=check(floortile[i][j].x,floortile[i][j].y+104,x1p,y1p,x2p,y2p);
                    d=check(floortile[i][j].x+100,floortile[i][j].y+104,x1p,y1p,x2p,y2p);
                    if(a==0)
                        continue;
                    if(b==0)
                        continue;
                    if(c==0)
                        continue;
                    if(d==0)
                        continue;
                    if(a<0 && b<0 && c<0 && d<0)
                        continue;
                    if(a>0 && b>0 && c>0 && d>0)
                        continue;
                    return false;//return LineIntersectsSquare(x1p,y1p,x2p,y2p,floortile[i][j].x,floortile[i][j].y,floortile[i][j].x+100,floortile[i][j].y+104);
                }
            }
        }
        break;
    case 7:
        for(int i=y2; i<y1; i++)
        {
            if(!floortile[x1][i].walkable)
                return false;
        }
        break;
    case 8:
        for(int i=x2; i<x1; i++)
        {
            for(int j=y2; j<y1; j++)
            {
                if(!floortile[i][j].walkable)
                {
                    int a,b,c,d;
                    a=check(floortile[i][j].x,floortile[i][j].y,x1p,y1p,x2p,y2p);
                    b=check(floortile[i][j].x+100,floortile[i][j].y,x1p,y1p,x2p,y2p);
                    c=check(floortile[i][j].x,floortile[i][j].y+104,x1p,y1p,x2p,y2p);
                    d=check(floortile[i][j].x+100,floortile[i][j].y+104,x1p,y1p,x2p,y2p);
                    if(a==0)
                        continue;
                    if(b==0)
                        continue;
                    if(c==0)
                        continue;
                    if(d==0)
                        continue;
                    if(a<0 && b<0 && c<0 && d<0)
                        continue;
                    if(a>0 && b>0 && c>0 && d>0)
                        continue;
                    return false;//return LineIntersectsSquare(x1p,y1p,x2p,y2p,floortile[i][j].x,floortile[i][j].y,floortile[i][j].x+100,floortile[i][j].y+104);
                }
            }
        }
        break;
    }
    return true;

    ///old one |
    ///        V


    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(!floortile[i][j].walkable)
            {
                int a,b,c,d;
                a=check(floortile[i][j].x,floortile[i][j].y,x1p,y1p,x2p,y2p);
                b=check(floortile[i][j].x+100,floortile[i][j].y,x1p,y1p,x2p,y2p);
                c=check(floortile[i][j].x,floortile[i][j].y+104,x1p,y1p,x2p,y2p);
                d=check(floortile[i][j].x+100,floortile[i][j].y+104,x1p,y1p,x2p,y2p);
                if(a==0)
                    continue;
                if(b==0)
                    continue;
                if(c==0)
                    continue;
                if(d==0)
                    continue;
                if(a<0 && b<0 && c<0 && d<0)
                    continue;
                if(a>0 && b>0 && c>0 && d>0)
                    continue;


                if (x1 > squarex(floortile,floortile[i][j].x+100) && x2 > squarex(floortile,floortile[i][j].x+100))///, no intersection (line is to right of rectangle).
                    continue;
                if (x1 < squarex(floortile,floortile[i][j].x) && x2 < squarex(floortile,floortile[i][j].x))///, no intersection (line is to left of rectangle).
                    continue;
                if (y1 > squarey(floortile, floortile[i][j].y+104) && y2 > squarey(floortile, floortile[i][j].y+104))///, no intersection (line is above rectangle).
                    continue;
                if (y1 < squarey(floortile, floortile[i][j].y) && y2 < squarey(floortile, floortile[i][j].y))///, no intersection (line is below rectangle).
                    continue;

                return false;

            }
        }
    }
    return true;*/
}

int enemy::returnpath(FloorTile floortile[n][m], float ox, float oy) {
    ///ox,oy - player coords
    ///ex,ey - mob coords
    ///zamienic floortilea na graf/// teraz nie - dzialam na ft
    //vector <int> v[n*m+5];
    int ex = squarex(floortile, static_cast<int>(getPosition().x)) + 1;
    int ey = squarey(floortile, static_cast<int>(getPosition().y)) + 1;
    oy = squarey(floortile, static_cast<int>(oy)) + 1;
    ox = squarex(floortile, static_cast<int>(ox)) + 1;

    bool vis[n + 2][m + 2];
    std::pair<int, int> start(ex, ey);
    std::pair<int, int> fin(static_cast<const int &>(ox), static_cast<const int &>(oy));
    char uppers[n + 2][m + 2];
    bool tab[n + 2][m + 2];
    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < m + 2; j++) {
            vis[i][j] = false;
            tab[i][j] = !(i == 0 || j == 0 || i == n + 1 || j == m + 1 || !floortile[i - 1][j - 1].walkable);

        }
    }
    std::queue <std::pair<int, int>> queue;

    vis[start.first][start.second] = true;
    //floortile[newGameTexture.first][newGameTexture.second].sprite.setColor(sf::Color::Yellow);
    uppers[start.first][start.second] = 'n';
    queue.push(start);
    while (!queue.empty()) {
        auto &c = queue.front();
        auto& q = c;

        queue.pop();
        auto left = std::pair<int, int>(q.first - 1, q.second);

        if (!vis[left.first][left.second] && tab[left.first][left.second]) {
            vis[left.first][left.second] = true;
            uppers[left.first][left.second] = 'l';
            queue.push(left);
        }
        std::pair<int, int> right(q.first + 1, q.second);

        if (!vis[right.first][right.second] && tab[right.first][right.second]) {
            vis[right.first][right.second] = true;
            uppers[right.first][right.second] = 'r';
            queue.push(right);
        }
        std::pair<int, int> up(q.first, q.second - 1);

        if (!vis[up.first][up.second] && tab[up.first][up.second]) {
            vis[up.first][up.second] = true;
            uppers[up.first][up.second] = 'u';
            queue.push(up);
        }
        std::pair<int, int> down(q.first, q.second + 1);
        if (!vis[down.first][down.second] && tab[down.first][down.second]) {
            vis[down.first][down.second] = true;
            uppers[down.first][down.second] = 'd';
            queue.push(down);
        }
    }
    if (!vis[fin.first][fin.second])
        return 4;
    while (fin != start) {

        if (uppers[fin.first][fin.second] == 'u') {
            if (uppers[fin.first][fin.second + 1] == 'n')
                return 0;
            fin.second++;
            continue;
        }
        if (uppers[fin.first][fin.second] == 'r') {
            if (uppers[fin.first - 1][fin.second] == 'n')
                return 1;
            fin.first--;
            continue;
        }
        if (uppers[fin.first][fin.second] == 'd') {
            if (uppers[fin.first][fin.second - 1] == 'n')
                return 2;
            fin.second--;
            continue;
        }
        if (uppers[fin.first][fin.second] == 'l') {
            if (uppers[fin.first + 1][fin.second] == 'n')
                return 3;
            fin.first++;
            continue;
        }

    }

    return 4;
}

bool enemy::canSee(FloorTile floortile[n][m], sf::Vector2f vector2f) {
    return canSee(floortile, vector2f.x, vector2f.y);
}

int enemy::returnpath(FloorTile floortile[n][m], sf::Vector2f vector2f) {
    return returnpath(floortile, vector2f.x, vector2f.y);
}

void Character::addItem(item a) {
    for (auto &i : inv) {
        if (i.getId() == a.getId() && i.getEffectNum() == a.getEffectNum() &&
                i.getType() == a.getType()) {
            i.quant += a.quant;
            return;
        }
    }
    inv.push_back(a);
}

void Character::addItem(int id, int type, int effect, int quantity) {
    for (auto &i : inv) {
        if (i.getId() == id && i.getEffectNum() == effect && i.getType() == type) {
            i.quant += quantity;
            return;
        }
    }
    item a(id, type, effect);
    a.quant = quantity;
    inv.push_back(a);
}

void Character::useItem(int iter) {
    if (iter + 1 > inv.size()) {
        return;
    }
    if (inv[iter].getType() == 0) {
        ///code for weapon here
        weaponiter = iter;
        this->damage = inv[weaponiter].getEffectNum();
        return;
    }
    if (inv[iter].getType() == 1) {
        ///medkit
        if (health == maxhp)
            return;
        this->Heal(inv[iter].getEffectNum());
        if (inv[iter].quant > 1)
            inv[iter].quant--;
        else {
            inv.erase(inv.begin() + iter);
            if (weaponiter > iter)
                weaponiter--;
        }

        return;
    }
    if (inv[iter].getType() == 2) {
        ///dmg buff
        return;
    }
    if (inv[iter].getType() == 3) {
        ///maxhp buff
        return;
    }
    if (inv[iter].getType() == 4) {
        ///
        return;
    }
    if (inv[iter].getType() == 5) {
        ///
        return;
    }
}

void Character::deleteItem(int iter, int quant) {
    if (inv[iter].quant > 1)
        inv[iter].quant--;
    else
        inv.erase(inv.begin() + iter);
}

bool Character::shoot(std::vector<Projectile> &proj, sf::Vector2f vector2f) {
    return shoot(proj, vector2f.x, vector2f.y);
}

void Character::rotatexy(sf::Vector2i vector2i) {
    rotatexy_internal(vector2i.x, vector2i.y);
}

boss::boss() {
    setOrigin(284, 260);
    this->shtdelay = 150;
    this->health = 2000;
    inv.erase(inv.begin(), inv.end());
    addItem(5, 0, 30, 1);
    useItem(0);
}
