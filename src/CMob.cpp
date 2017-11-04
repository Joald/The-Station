#include "The Station.h"

#define n 16
#define m 6



using namespace std;
void CMob::DealDamage(int modifier)
{
    this->health-=modifier;
    //int a=this->health;
}
void CMob::Heal(int modifier)
{
    this->health+=modifier;
    if(health>maxhp)
        health=maxhp;
}
void CMob::ModifySpeed(int modifier)
{
    this->speed+=modifier;
}
void CMob::ModifyDamage(int modifier)
{
    this->damage-=modifier;
}
void CMob::ModifyArmor(int modifier)
{
    this->armor+=modifier;
}

CMob::CMob()
{
    this->red=false;
    this->isplayer=true;
    this->speed=5;
    this->armor=0;
    this->health=100;

    this->shtdelay=200;
    this->shtspeed=10;
    this->invincible=false;
    maxhp=100;
    item o(0,0,20);

    o.quant=1;

    weaponiter=0;
    this->damage=o.getEffectNum();


    int a=o.getEffectNum();
    this->damage=a;

    damage=a;

    //this->damage=100;
    addItem(o);
    this->isboss=false;


}

void CMob::rotatexy(int mx,int my)///taking mouse coords for arguments
{
    double deltax,deltay,angle;///double variables for calculation
    deltax=this->x-mx;///delta n = objects position n - mouse pos n
    deltay=this->y-my;
    angle=(atan2(deltay,deltax))*180/PI-90;/// trigonometry with arc tangent taking 2
    this->orient=angle;/// orient is a class angle variable
    this->C.setRotation(angle);///set rotation to object's sf::Sprite
    //return this->orient;
}

void CMob::rotate2mouse(Station& game)
{
    double a,b;
    a=this->x-sf::Mouse::getPosition(game.App).x;
    b=this->y-sf::Mouse::getPosition(game.App).y;
    this->orient=atan2(b,a)*180/PI;
    this->C.setRotation(this->orient-90);
}
bool CMob::shoot(vector<projectile> &proj,int mx,int my)
{
    if(this->health<=0)
        return false;

    //for(int unsigned i=1; i<=proj.size(); i++)
    if(this->delay.getElapsedTime().asMilliseconds()<this->shtdelay)
        return false;

    projectile a;


    //a.delay.restart();


    a.type=inv[weaponiter].getId();
    a.setorig(this);
    a.damage=damage;

    a.rotatexy(mx,my);
    this->delay.restart();
    proj.push_back(a);
    return true;
    /*projectile *a;

    a = new projectile;
    a->delay.restart();
    a->setorig(this);

    a->rotatexy(mx,my);
    a->delay.restart();
    proj.push_back(*a);

    delete a;*/
}
bool CMob::shoot(vector<projectile> &proj,int mx,int my,bool ignore)
{


    projectile a;


    //a.delay.restart();


    a.type=inv[weaponiter].getId();
    a.setorig(this);

    a.rotatexy(mx,my);
    this->delay.restart();
    proj.push_back(a);
    return true;
    /*projectile *a;

    a = new projectile;
    a->delay.restart();
    a->setorig(this);

    a->rotatexy(mx,my);
    a->delay.restart();
    proj.push_back(*a);

    delete a;*/
}
void enemy::rotatexy(int mx,int my)
{
    double deltax,deltay,angle;                     ///double variables for calculation
    deltax=this->x-mx;                              ///delta n = objects position n - mouse pos n
    deltay=this->y-my;
    angle=(atan2(deltay,deltax))*180/PI-90;         /// trigonometry with arc tangent taking 2
    this->orient=angle+90;                          /// orient is a class angle variable
    this->C.setRotation(angle);                     ///set rotation to object's sf::Sprite


}
enemy::enemy()
{
    this->damage=0;
    this->ax=0;
    this->ay=0;
    this->shtdelay=500;
    this->destroystate=0;
    this->C.setOrigin(25,25);
    this->isplayer=false;
    inv.erase(inv.begin(),inv.end());
    addItem(0,0,5,1);
}
void CMob::toggleInvincible()
{
    if(this->invincible)
        this->invincible=false;
    else
        this->invincible=true;
}
bool CMob::canWalkDown(tile floortile[n][m],Station & game)
{
    int ox=this->x;
    int oy=this->y;

int fixh=291;
if(game.isUnsized)
{

    fixh=155;
}
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(!floortile[i][j].walkable && ox>floortile[i][j].x && ox<floortile[i][j].x+100 && oy+15>floortile[i][j].y && oy<floortile[i][j].y+104)
                return false;
        }
    }
    if(this->y>game.h-fixh+fixh*2/6)
        return false;
    else
        return true;

}
bool CMob::canWalkUp(tile floortile[16][6],Station & game)
{
    int ox=this->x;
    int oy=this->y;
int fixw=170;
int fixh=291;
if(game.isUnsized)
{
    fixw=91;
    fixh=155;
}
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(!floortile[i][j].walkable && ox>floortile[i][j].x && ox<floortile[i][j].x+100 && oy>floortile[i][j].y && oy-15<floortile[i][j].y+104)
                return false;
        }
    }
    if(this->y-15<fixh)
        return false;
    else
        return true;

}
bool CMob::canWalkRight(tile floortile[n][m],Station & game)
{
    int ox=this->x;
    int oy=this->y;
int fixw=170;
int fixh=291;
if(game.isUnsized)
{
    fixw=91;
    fixh=155;
}
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(!floortile[i][j].walkable && ox+15>floortile[i][j].x && ox<floortile[i][j].x+100 && oy>floortile[i][j].y && oy<floortile[i][j].y+104)
                return false;
        }
    }
    if( this->x>game.w-fixw-fixw/10)
        return false;
    else
        return true;

}
bool CMob::canWalkLeft(tile floortile[n][m],Station & game)
{
    int ox=this->x;
    int oy=this->y;
int fixw=170;
int fixh=291;
if(game.isUnsized)
{
    fixw=91;
    fixh=155;
}
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(!floortile[i][j].walkable && ox>floortile[i][j].x && ox-15<floortile[i][j].x+100 && oy>floortile[i][j].y && oy<floortile[i][j].y+104)
                return false;
        }
    }

    if(this->x<fixw)
        return false;
    else
        return true;
}


///sprawdzanie wrogow


bool enemy::canWalkDown(tile floortile[n][m],Station & game)
{
    int a,b;
int fixw=170;
int fixh=291;
if(game.isUnsized)
{
    fixw=91;
    fixh=155;
}
    a = ( this->x - fixw ) / 100;
    b = ( this->y - fixh ) / 104;
    if(!floortile[a][b].walkable  &&  this->y+25 >= floortile[a][b].y-104)
        return false;
    else if(this->y>game.h-fixh+fixh*2/5)
        return false;
    else
        return true;

}
bool enemy::canWalkUp(tile floortile[n][m],Station & game)
{
    int a,b;
int fixw=170;
int fixh=291;
if(game.isUnsized)
{
    fixw=91;
    fixh=155;
}
    a = ( this->x - fixw ) / 100;
    b = ( this->y - fixh ) / 104;
    if(!floortile[a][b-1].walkable  &&  this->y-25  <= floortile[a][b-1].y+104)
        return false;
    else if(this->y<fixh)
        return false;
    else
        return true;

}
bool enemy::canWalkRight(tile floortile[n][m],Station & game)
{
    int a,b;
int fixw=170;
int fixh=291;
if(game.isUnsized)
{
    fixw=91;
    fixh=155;
}
    a = ( this->x - fixw ) / 100;
    b = ( this->y - fixh ) / 104;
    if(!floortile[a+1][b].walkable  &&  this->x+25  >= floortile[a+1][b].x)
        return false;
    else if(this->x>game.w-fixw-fixw/20)
        return false;
    else
        return true;

}
bool enemy::canWalkLeft(tile floortile[n][m],Station & game)
{
    int a,b;
int fixw=170;
int fixh=291;
if(game.isUnsized)
{
    fixw=91;
    fixh=155;
}
    a = ( this->x - fixw ) / 100;
    b = ( this->y - fixh ) / 104;
    if(!floortile[a-1][b].walkable  &&  this->x-25  <= floortile[a-1][b].x+100)
        return false;
    else if(this->x-25<fixw)
        return false;
    else
        return true;
}
int check(int x,int y, int x1, int y1,int x2, int y2)
{
    return (y-y1)*(x2-x1)-(y2-y1)*(x-x1);//(y1-y2)*x + (x1-x2)*y + (x2*y1-x1*y2);
}
int squarex(tile floortile[n][m],int x)
{
    for(int i=0; i<n; i++)
    {
        if((floortile[i][0].x<x && floortile[i][0].x+100>x) || floortile[i][0].x==x)
            return i;
    }
    return 0;
}
int squarey(tile floortile[n][m],int y)
{
    for(int i=0; i<m; i++)
    {
        if((floortile[0][i].y<y && floortile[0][i].y+104>y) || floortile[0][1].y==y)
            return i;
    }
    return 0;
}
bool enemy::canSee(tile floortile[n][m],int x2, int y2)
{
    if(this->destroystate)
        return false;


    int x1=floor(this->x);
    int y1=floor(this->y);
    //int x1p=x1,x2p=x2,y1p=y1,y2p=y2;//faktyczne koordynaty
    //int playx=x2,playy=y2,enex=x1,eney=y1;
    x1=squarex(floortile,x1);
    x2=squarex(floortile,x2);
    y1=squarey(floortile,y1);
    y2=squarey(floortile,y2);
    /*long double len = max(abs(x2-x1), abs(y2-y1));
    for (int i = 0; i<len; i++)
    {
        //# interpolate between (x1,y1) && (x2,y2)
        long double t = float(i)/len;
        //# at t=0.0 we get (x1,y1); at t=1.0 we get (x2,y2)
        int ox = round(x1 * (1.0-t) + x2 * t);
        int oy = round(y1 * (1.0-t) + y2 * t);
        // now check tile (x,y)
        if(!floortile[ox][oy].walkable)
            return false;
    }
    return true;*/
    ///          _
    /**vector<tile>v;            1 2 3 /   \
    bool sc=false;*/          ///4 p 5 | p |
    int pos=0;///                6 7 8 \ _ /
    if(!pos)
    {
        if(x1==x2)
            return true;
        if(x1<x2 && y1<y2)
            pos=1;
        else if(x1==x2 && y1<y2)
            pos=2;
        else if(x1>x2 && y1<y2)
            pos=3;
        else if(x1<x2 && y1==y2)
            pos=4;
        else if(x1>x2 && y1==y2)
            pos=5;
        else if(x1<x2 && y1>y2)
            pos=6;
        else if(x1==x2 && y1>y2)
            pos=7;
        else if(x1>x2 && y1>y2)
            pos=8;
    }
    if(pos==2)
    {
        for(int i=y1; i<y2+1; i++)
        {
            if(!floortile[x1][i].walkable)
                return false;
        }
        return true;
    }
    if(pos==4)
    {
        for(int i=x1; i<x2+1; i++)
        {
            if(!floortile[i][y1].walkable)
                return false;
        }
        return true;
    }
    if(pos==5)
    {
        for(int i=x2; i<x1+1; i++)
        {
            if(!floortile[i][y1].walkable)
                return false;
        }
        return true;
    }
    if(pos==7)
    {
        for(int i=y2; i<y1+1; i++)
        {
            if(!floortile[x1][i].walkable)
                return false;
        }
        return true;
    }
    int kx,ky;
    if( x1 <= x2)
        kx = 1;
    else
        kx = -1	; //okreœlamy krok X od x1 do x2
    if( y1 < y2)
        ky = 1;
    else
        ky = -1	; //okreœlamy krok Y od y1 do y2
    int dx = abs(x2 - x1)	; //odleg³oœæ pomiêdzy x1 i x2
    int dy = abs(y2 - y1)	; //odleg³oœæ pomiêdzy y1 i y2

    if( dx > dy) //, idŸ do kroku K16	; //dla k¹tów > 45° wykonujemy wersjê algorytmu z przestawionymi wspó³rzêdnymi
    {
        double e = dx / 2	; //obliczamy wartoœæ pocz¹tkow¹ wyra¿enia b³êdu
        for(int i=0; i< dx; i++) // razy kroki K09...K14	; //rysujemy pozosta³e piksele w pêtli
        {
            x1 = x1 + kx; //przesuwamy siê w odpowiedni¹ stronê w kierunku szybkim
            e = e - dy; //obliczamy wyra¿enie b³êdu
            if (e < 0) //, idŸ do kroku K14	; //jeœli wyra¿enie b³êdu jest nieujemne, pomijamy ruch w kierunku wolnym
            {
                y1 = y1 + ky; //przesuwamy siê w odpowiedni¹ stronê w kierunku wolnym
                e = e + dx	;
            } //obliczamy nowe wyra¿enie b³êdu
            if(!floortile[x1][y1].walkable) //kolejny piksel odcinka
                return false;
        }
    }
    else
    {
        double e = dy / 2	; //wersja algorytmu Bresenhama ze zamienionymi wspó³rzêdnymi x i y
        for(int i=0; i<dy; i++) // razy kroki K18...K23
        {
            y1 = y1 + ky;
            e = e - dx;
            if(e < 0)
            {
                x1 = x1 + kx;
                e = e + dy;
            }
            if(!floortile[x1][y1].walkable)
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
int enemy::returnpath(tile floortile[n][m],int ox, int oy)
{
    ///ox,oy - player coords
    ///ex,ey - mob coords
    ///zamienic floortilea na graf/// teraz nie - dzialam na ft
    //vector <int> v[n*m+5];
    int ex=squarex(floortile,floor(this->x))+1,ey=squarey(floortile,floor(this->y))+1;
    oy=squarey(floortile,floor(double(oy)))+1;
    ox=squarex(floortile,floor(double(ox)))+1;

    bool vis[n+2][m+2];
    pair<int,int> start(ex,ey);
    pair<int,int> fin(ox,oy);
    char uppers[n+2][m+2];
    bool tab[n+2][m+2];
    for(int i=0; i<n+2; i++)
    {
        for(int j=0; j<m+2; j++)
        {
            vis[i][j]=false;
            if(i==0 || j==0 || i==n+1 || j==m+1 || !floortile[i-1][j-1].walkable)
                tab[i][j]=false;
            else
                tab[i][j]=true;

        }
    }
    queue<pair<int,int> > a;

    vis[start.first][start.second]=true;
    //floortile[start.first][start.second].sprite.setColor(sf::Color::Yellow);
    uppers[start.first][start.second]='n';
    a.push(start);
    while(!a.empty())
    {
        pair<int,int> c=a.front();
        pair<int,int> q=c;

        a.pop();
        pair<int,int>lef(q.first-1,q.second);
        c=lef;
        /*if(tab[c.first][c.second])
            floortile[c.first][c.second].sprite.setColor(sf::Color::Yellow);*/
        if(!vis[c.first][c.second] && tab[c.first][c.second])
        {
            vis[c.first][c.second]=true;
            uppers[c.first][c.second]='l';
            a.push(c);
        }
        pair<int,int>righ(q.first+1,q.second);
        c=righ;
        if(!vis[c.first][c.second] && tab[c.first][c.second])
        {
            vis[c.first][c.second]=true;
            uppers[c.first][c.second]='r';
            a.push(c);
        }
        pair<int,int>up(q.first,q.second-1);
        c=up;
        if(!vis[c.first][c.second] && tab[c.first][c.second])
        {
            vis[c.first][c.second]=true;
            uppers[c.first][c.second]='u';
            a.push(c);
        }
        pair<int,int>dow(q.first,q.second+1);
        c=dow;
        if(!vis[c.first][c.second] && tab[c.first][c.second])
        {
            vis[c.first][c.second]=true;
            uppers[c.first][c.second]='d';
            a.push(c);
        }
    }
    if(!vis[fin.first][fin.second])
        return 4;
    while(fin!=start)
    {

        if(uppers[fin.first][fin.second]=='u')
        {
            if(uppers[fin.first][fin.second+1]=='n')
                return 0;
            fin.second++;
            continue;
        }
        if(uppers[fin.first][fin.second]=='r')
        {
            if(uppers[fin.first-1][fin.second]=='n')
                return 1;
            fin.first--;
            continue;
        }
        if(uppers[fin.first][fin.second]=='d')
        {
            if(uppers[fin.first][fin.second-1]=='n')
                return 2;
            fin.second--;
            continue;
        }
        if(uppers[fin.first][fin.second]=='l')
        {
            if(uppers[fin.first+1][fin.second]=='n')
                return 3;
            fin.first++;
            continue;
        }
        //return 4;


    }

    return 4;
}

void CMob::addItem(item a)
{
    for(int unsigned i=0; i<inv.size(); i++)
    {
        if(inv[i].getId()==a.getId() && inv[i].getEffectNum()==a.getEffectNum() && inv[i].getType()==a.getType())
        {
            inv[i].quant+=a.quant;
            return;
        }
    }
    inv.push_back(a);
}
void CMob::addItem(int id,int type,int effect, int quantity)
{
    for(int unsigned i=0; i<inv.size(); i++)
    {
        if(inv[i].getId()==id && inv[i].getEffectNum()==effect && inv[i].getType()==type)
        {
            inv[i].quant+=quantity;
            return;
        }
    }
    item a(id,type,effect);
    a.quant=quantity;
    inv.push_back(a);
}
void CMob::useItem(int iter)
{
    if(iter+1>inv.size())
        return;
    if(inv[iter].getType()==0)
    {
        ///code for weapon here
        weaponiter=iter;
        this->damage=inv[weaponiter].getEffectNum();
        return;
    }
    if(inv[iter].getType()==1)
    {
        ///medkit
        if(health==maxhp)
            return;
        this->Heal(inv[iter].getEffectNum());
        if(inv[iter].quant>1)
            inv[iter].quant--;
        else
        {
            inv.erase(inv.begin()+iter);
            if(weaponiter>iter)
                weaponiter--;
        }

        return;
    }
    if(inv[iter].getType()==2)
    {
        ///dmg buff
        return;
    }
    if(inv[iter].getType()==3)
    {
        ///maxhp buff
        return;
    }
    if(inv[iter].getType()==4)
    {
        ///
        return;
    }
    if(inv[iter].getType()==5)
    {
        ///
        return;
    }
}
void CMob::deleteItem(int iter,int quant)
{
    if(inv[iter].quant>1)
        inv[iter].quant--;
    else
        inv.erase(inv.begin()+iter);
}

boss::boss()
{
    this->C.setOrigin(284,260);
    isboss=true;
    this->shtdelay=150;
    this->health=2000;
    inv.erase(inv.begin(),inv.end());
    addItem(5,0,30,1);
    useItem(0);
}
