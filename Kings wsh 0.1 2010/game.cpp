#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "graphics.h"
using namespace std;
struct coords
{
    int x,y;
};
struct characteristics
{
    int power;
    int maxhp;
    int speed;
    int reakcia;
    int regeneracia;
};
struct object
{
    characteristics plus;
    int type;
    int coast;
    int imageHandle;
    int imageHandleId;
};
void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }
void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* записываем знак */
         n = -n;          /* делаем n положительным числом */
     i = 0;
     do {       /* генерируем цифры в обратном порядке */
         s[i++] = n % 10 + '0';   /* берем следующую цифру */
     } while ((n /= 10) > 0);     /* удаляем */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }
char* intstroka(int x)
{
    char* str=new char[10];
    itoa(x,str);
    return str;

}
double Distance (coords a, coords b)
{
    return sqrt(double((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y)));
}
int* arrAdd(int* pMas, int*n, int pos, int zna4)
{
    int* pTemp=new int[*n+1];
    int j=0;
    for (int i=0; i<*n; i++)
    {
        if (i!=pos)
        {
            pTemp[j]=pMas[i];
            j++;
        }
        else
        {
            j++;
            pTemp[j]=pMas[i];
            j++;
        }
    }
    pTemp[pos]=zna4;
    delete[]pMas;
    (*n)++;
    return pTemp;
}
class table
{
private:
    coords** kletki;
    coords** contentCoords;
    int** content;
    int contentColor;
    int solidColor;
    int k50,k100;
    int** handleMas;
public:
    coords xy;
    int height, width;
    int cols, lines;
    table(int x, int y, int visota, int shirina,int stolb ,int stroki, int textColor,int tableColor)
    {
        xy.x=x;
        xy.y=y;
        solidColor=tableColor;
        //if(height>0)
        //{
        height=visota;
        //}
        //else
        //{
        //    height=0;
        //}
        //if(width>0)
        //{
        width=shirina;
        //}
        //else
        //{
        //    width=0;
        //}
        //if(stolb>0)
        //{
        cols=stolb;
        //}
        //else
        //{
        //    cols=0;
        //}
        //if(stroki>0)
        //{
        lines=stroki;
        //}
        //else
        //{
        //    lines=0;
        //}
        ////cout<<xy.x<<" "<<xy.y<<" "<<lines<<" "<<cols;
        k50=SgLoadImage("50castle.bmp");

        SgSetImageColorKey(k50,sgRGB(255,246,0));
        k100=SgLoadImage("100castle.bmp");
        ////cout<<k50<<" "<<k100<<endl;
        SgSetImageColorKey(k100,sgRGB(255,246,0));
        kletki=new coords*[cols];
        for(int i=0;i<cols;i++)
        {
            kletki[i]=new coords[cols];
        }
        for(int i=0;i<cols;i++)
        {
            for(int j=0;j<lines;j++)
            {
                kletki[i][j].x=xy.x+width*i;
                kletki[i][j].y=xy.y+height*j;
            }
        }

        contentCoords=new coords*[cols];
        for(int i=0;i<cols;i++)
        {
            contentCoords[i]=new coords[cols];
        }
        for(int i=0;i<cols;i++)
        {
            for(int j=0;j<lines;j++)
            {
                contentCoords[i][j].x=0;
                contentCoords[i][j].y=0;
                // //cout<<contentCoords[i][j].x<<" "<<contentCoords[i][j].y<<endl;
            }
        }
        content=new int*[cols];
        for(int i=0;i<cols;i++)
        {
            content[i]=new int[lines];
        }
        for(int i=0;i<cols;i++)
        {
            for(int j=0;j<lines;j++)
            {
                content[i][j]=0;
            }
        }
        contentColor=textColor;
        handleMas=new int*[cols];
        for(int i=0;i<cols;i++)
        {
            handleMas[i]=new int[lines];
        }
        for(int i=0;i<cols;i++)
        {
            for(int j=0;j<lines;j++)
            {
                handleMas[i][j]=0;
            }
        }
    }
    ~table()
    {
        for(int i=0;i<cols;i++)
        {
            delete[] kletki[i];
            delete[] contentCoords[i];
            delete[] content[i];
            delete[] handleMas[i];
        }
        delete[] handleMas;
        delete[] kletki;
        delete[] contentCoords;
        delete[] content;
    }
    void drawTable()
    {
        SgSelectPen(1,solidColor);
        coords start, end;
        start.x=xy.x;
        start.y=xy.y;
        end.x=xy.x+width*cols;
        end.y=xy.y+height*lines;
        for(int i=0;i<=lines;i++)
        {
            SgLine(start.x, start.y,end.x,start.y);
            start.y+=height;
        }
        start.y=xy.y;
        for(int i=0;i<=cols;i++)
        {
            SgLine(start.x,start.y,start.x,end.y);
            start.x+=width;
        }
    }
    void drawContent()
    {
        for(int i=0;i<cols;i++)
        {
            for(int j=0;j<lines;j++)
            {

                if(content[i][j]!=0)
                {
                    if(content[i][j]<=50)
                        SgDrawImage(k50,kletki[i][j].x,kletki[i][j].y);

                    else
                        SgDrawImage(k100,kletki[i][j].x,kletki[i][j].y);

                    // SgDrawText(kletki[i][j].x+contentCoords[i][j].y,kletki[i][j].y+contentCoords[i][j].x,intstroka(content[i][j]),contentColor);
                }
            }
        }
    }
    coords hover()
    {
        coords c;
        SgGetCursorPos(c.x,c.y);
        c.x-=xy.x;
        c.y-=xy.y;
        coords ret;
        ret.x=-1;
        ret.y=-1;
        while(c.x>0)
        {
            c.x-=width;
            ret.x++;
        }
        while(c.y>0)
        {
            c.y-=height;
            ret.y++;
        }
        if(ret.x>cols-1 || ret.y>lines-1 || ret.x<0 || ret.y<0)
        {
            ret.x=-1;
            ret.y=-1;
        }

        return ret;
    }
    bool active(coords &activeKletkaCoords)
    {
        coords c;
        SgGetCursorPos(c.x,c.y);
        bool a=false;
        if(c.x>xy.x && c.x<xy.x+width*cols && c.y>xy.y && c.y<xy.y+height*lines)
        {
            a=true;
        }
        if(SgIsKeyDown(VK_LBUTTON) && a)
        {

            activeKletkaCoords=getKletkiByCoords(c);
            return true;
        }
        else
        {
            activeKletkaCoords.x=-1;
            activeKletkaCoords.y=-1;
            return false;
        }
    }
    coords getKletkiByCoords(coords c)
    {
        c.x-=xy.x;
        c.y-=xy.y;
        coords ret;
        ret.x=-1;
        ret.y=-1;
        while(c.x>0)
        {
            c.x-=width;
            ret.x++;
        }
        while(c.y>0)
        {
            c.y-=height;
            ret.y++;
        }
        if(ret.x>cols-1 || ret.y>lines-1 || ret.x<0 || ret.y<0)
        {
            ret.x=-1;
            ret.y=-1;
        }
        return ret;
    }
    void overline(coords x, int lineWidth, int lineColor)
    {

        coords ret=getKletkiByCoords(x);
        if(ret.x!=-1 || ret.y!=-1)
        {
            SgSelectPen(lineWidth,lineColor);                                                                                      
            SgLine(kletki[ret.x][ret.y].x,kletki[ret.x][ret.y].y,kletki[ret.x][ret.y].x+width,kletki[ret.x][ret.y].y);          
            SgLine(kletki[ret.x][ret.y].x,kletki[ret.x][ret.y].y+height,kletki[ret.x][ret.y].x+width,kletki[ret.x][ret.y].y+height);
            SgLine(kletki[ret.x][ret.y].x+width,kletki[ret.x][ret.y].y,kletki[ret.x][ret.y].x+width,kletki[ret.x][ret.y].y+height); 
            SgLine(kletki[ret.x][ret.y].x,kletki[ret.x][ret.y].y,kletki[ret.x][ret.y].x,kletki[ret.x][ret.y].y+height);             
        }
    }
    void overline(coords x, int lineWidth, int lineColor,bool a)
    {

        coords ret=x;
        if(ret.x!=-1 || ret.y!=-1)
        {
            SgSelectPen(lineWidth,lineColor);                                                                                      
            SgLine(kletki[ret.x][ret.y].x,kletki[ret.x][ret.y].y,kletki[ret.x][ret.y].x+width,kletki[ret.x][ret.y].y);          
            SgLine(kletki[ret.x][ret.y].x,kletki[ret.x][ret.y].y+height,kletki[ret.x][ret.y].x+width,kletki[ret.x][ret.y].y+height);
            SgLine(kletki[ret.x][ret.y].x+width,kletki[ret.x][ret.y].y,kletki[ret.x][ret.y].x+width,kletki[ret.x][ret.y].y+height); 
            SgLine(kletki[ret.x][ret.y].x,kletki[ret.x][ret.y].y,kletki[ret.x][ret.y].x,kletki[ret.x][ret.y].y+height);             
        }
    }
    coords getKletkiCoords(int xKletka, int yKletka)
    {   
        if(   xKletka>=0 && yKletka>=0)
            return kletki[xKletka][yKletka];
        else
        {
            coords x;
            x.x=-100;
            x.y=-100;
            return x;
        }
    }
    void setContent(coords x,int cont,int paddingLeft=0, int paddingTop=0)
    {
        //if(x.x>0 && x.y>0 && x.x<cols && x.y<lines)
        //{
        content[x.x][x.y]=cont;
        contentCoords[x.x][x.y].x=paddingLeft;
        contentCoords[x.x][x.y].y=paddingTop;
        //}
    }
    int getConent(coords x)
    {
        return content[x.x][x.y];
    }
    void setImage(int handle, int x, int y)
    {
        if(x>=0 && y>=0 && x<cols && y<lines)
            handleMas[x][y]=handle;
    }
    void drawImages()
    {
        for(int i=0;i<cols;i++)
        {
            for(int j=0;j<lines;j++)
            {

                if(content[i][j]!=0)
                {
                    SgDrawImage(content[i][j],kletki[i][j].x+contentCoords[i][j].y,kletki[i][j].y+contentCoords[i][j].x);
                }
            }
        }
    }
};
class button
{
private:
    coords crd;
    int but;
    int hover;
    int active;
    int width, height;
    char* text;
    int paddingTop;
    int paddingLeft;

public:
    bool just;
    button(coords c,int butHandle,const char* butText,int paddingT=0,int paddingL=0, int activeHandle=0,int hoverHandle=0)
    {
        //if(c.x>=0)
        //{
        crd.x=c.x;
        //}
        //else
        //{

        //}
        //if(c.y>=0)
        //{
        crd.y=c.y;
        //}
        //else
        //{
        //crd.y=0;
        //}
        //if(butHandle!=0)
        //{
        but=butHandle;
        SgGetImageSizes(but,width,height);
        //}
        //else 
        //{
        // but=0;
        //}
        //if(hoverHandle!=0)
        //{
        hover=hoverHandle;
        //}
        //else 
        //{
        //   hover=0;
        //}
        //if(activeHandle!=0)
        //{
        active=activeHandle;
        //}
        //else
        //{
        // active=0;
        //}
        int slen=strlen(butText);
        text=new char[slen+1];
        strcpy(text,butText);
        paddingLeft=paddingL;
        paddingTop=paddingT;
        just=false;

    }
    button()
    {

    }
    bool drawButton()
    {
        coords c;
        bool a=false;
        SgGetCursorPos(c.x,c.y);

        if(c.x>crd.x && c.x<crd.x+width && c.y>crd.y && c.y<crd.y+height)
        {
            a=true;
        }

        ////cout<<a<<" ";
        if(a && SgIsKeyDown(VK_LBUTTON) && but!=0 && active!=0)
        {
            SgDrawImage(active,crd.x,crd.y);
        }
        else if(a && hover!=0)
        {
            SgDrawImage(hover,crd.x,crd.y);
        }
        else
        {	
            SgDrawImage(but,crd.x,crd.y);
        }
        SgDrawText(paddingLeft+crd.x,paddingTop+crd.y,text);

        if(a)
        {
            if(SgIsKeyDown(VK_LBUTTON))
            {   
                //just=true;
                return true;
            }
        }
        //if(!SgIsKeyDown(VK_LBUTTON)) //&& just)
        //{
        //just=false;

        //}
        /*       else
        {*/
        //just=false;
        return false;
        //}



    }

    bool drawButtonUnDown()
    {
        coords c;
        bool a=false;
        SgGetCursorPos(c.x,c.y);

        if(c.x>crd.x && c.x<crd.x+width && c.y>crd.y && c.y<crd.y+height)
        {
            a=true;
        }

        ////cout<<a<<" ";
        if(a && SgIsKeyDown(VK_LBUTTON) && but!=0 && active!=0)
        {
            SgDrawImage(active,crd.x,crd.y);
        }
        else if(a && hover!=0)
        {
            SgDrawImage(hover,crd.x,crd.y);
        }
        else
        {	
            SgDrawImage(but,crd.x,crd.y);
        }
        SgDrawText(paddingLeft+crd.x,paddingTop+crd.y,text);

        if(a)
        {
            if(SgIsKeyDown(VK_LBUTTON))
            {   
                just=true;

            }
        }
        else
        {
            just=false;
        }
        if(!SgIsKeyDown(VK_LBUTTON) && just && a)
        {
            just=false;
            return true;
        }
        //just=false;
        return false;



    }
    ~button()
    {
        delete[] text;
    }
};
class player
{
private:
    int id;

    int speed;
    int maxHp;
    int regen;
    int kill;
    int dohod;
public:
    ////для записи в файл
    coords crd;
    int world;
    int icoHandle;
    coords impire[200];
    int impireCounter;
    characteristics har; 
    int money;
    int hod;
    bool ifHod;
    int hp;
    object box[10];
    player(int playerId,coords playerCrd,int playerWorld,int ico)
    {
        id=playerId;
        crd=playerCrd;
        if(playerWorld>0)
        {
            world=playerWorld;
        }
        icoHandle=ico;
        har.maxhp=100;
        har.power=10;
        har.reakcia=10;
        har.speed=5;
        har.regeneracia=har.maxhp/10;
        hod=har.speed*12;
        hp=har.maxhp;
        money=1000000;
        dohod=100;
        impireCounter=1;
        //impire=new coords[1];
        impire[0].x=0;
        impire[0].y=0;
        for(int i=1;i<200;i++)
        {
            impire[i].x=-1;
            impire[i].y=-1;
        }
        for(int i=0;i<10;i++)
        {
            box[i].coast=0;
            box[i].plus.maxhp=0;
            box[i].plus.power=0;
            box[i].plus.reakcia=0;
            box[i].plus.regeneracia=0;
            box[i].plus.speed=0;
            box[i].type=0;
            box[i].imageHandle=0;
            box[i].imageHandleId=-1;
        }
    }
    coords* arrAdd(coords* pMas, int*n, int pos, coords zna4)
{
    coords* pTemp=new coords[*n+1];
    int j=0;
    for (int i=0; i<*n; i++)
    {
        if (i!=pos)
        {
            pTemp[j].x=pMas[i].x;
            pTemp[j].y=pMas[i].y;
            j++;
        }
        else
        {
            j++;
            pTemp[j].x=pMas[i].x;
            pTemp[j].y=pMas[i].y;
            j++;
        }
    }
    pTemp[pos].x=zna4.x;
    pTemp[pos].y=zna4.y;
    delete[]pMas;
    (*n)++;
    return pTemp;
}
    void moovePlayer(coords kletki, table &world)
    {
        coords p=world.getKletkiByCoords(crd);
        double n=Distance(p,kletki);
        ////cout<<n<<" ";
        kletki=world.getKletkiCoords(kletki.x,kletki.y);
        if(n<=har.speed && hod>0)
        {
            if(crd.x>kletki.x)
            {
                crd.x-=speed;
            }
            if(crd.x<kletki.x)
            {
                crd.x+=speed;
            }

            if(crd.y>kletki.y)
            {
                crd.y-=speed;
            }
            if(crd.y<kletki.y)
            {
                crd.y+=speed;
            }
            hod--;
        }



        ////cout<<hod;
        ////cout<<crd.x<<" "<<crd.y<<endl;
    }
    void showHodChange()
    {
        RECT a;
        SgSelectPen(1,SgRGB(0,0,0));
        a.top=0;
        a.left=1220;
        if(har.speed<=10)
        {
            a.bottom=hod*3;
        }
        else if(har.speed<=20)
        {
            a.bottom=hod;
        }
        else
        {
            a.bottom=hod*0.8;
        }
        if(a.bottom>163)
        {
            a.bottom=163;
        }
        a.right=1250;

        SgSelectBrush(BRUSH_SOLID,sgRGB(255,0,0));
        SgRectangle(a.left,a.top,a.right,a.bottom);
    }
    void drawPlayer()
    {
        //	//cout<<icoHandle;
        SgDrawImage(icoHandle,crd.x,crd.y);
    }
    void drawKingHar(coords x)
    {
        SgSelectBrush(BRUSH_SOLID,sgRGB(252,255,187));
        int i=30, j=0;
        characteristics ret;
        ret.maxhp=har.maxhp;
        ret.power=har.power;
        ret.reakcia=har.reakcia;
        ret.regeneracia=har.regeneracia;
        ret.speed=har.speed;
        for(int i=0;i<10;i++)
        {
            ret.maxhp+=box[i].plus.maxhp;
            ret.power+=box[i].plus.power;
            ret.reakcia+=box[i].plus.reakcia;
            ret.regeneracia+=box[i].plus.regeneracia;
            ret.speed+=box[i].plus.speed;
        }

        if(ret.maxhp<0) ret.maxhp=1;
        if(ret.power<0) ret.power=1;
        if(ret.reakcia<0) ret.reakcia=1;
        if(ret.regeneracia<0) ret.regeneracia=1;
        if(ret.speed<0) ret.speed=3;
        speed=ret.speed;
        maxHp=ret.maxhp;
        regen=ret.regeneracia;
        {
            characteristics har=ret;
            SgRectangle(x.x,x.y,x.x+220,x.y+240);
            SgDrawText(x.x+5,x.y+5+j,"Сила");
            SgDrawText(x.x+5+175,x.y+5+j,intstroka(har.power));
            j+=i;
            SgDrawText(x.x+5,x.y+5+j,"Реакция");
            SgDrawText(x.x+5+175,x.y+5+j,intstroka(har.reakcia));
            j+=i;
            SgDrawText(x.x+5,x.y+5+j,"Регенерация");
            SgDrawText(x.x+5+175,x.y+5+j,intstroka(har.regeneracia));
            j+=i;
            SgDrawText(x.x+5,x.y+5+j,"Макс. жизни");
            SgDrawText(x.x+5+175,x.y+5+j,intstroka(har.maxhp));
            j+=i;
            SgDrawText(x.x+5,x.y+5+j,"Скорость");
            SgDrawText(x.x+5+175,x.y+5+j,intstroka(har.speed));
            j+=i;
            SgLine(x.x+10,x.y+j,x.x+210,x.y+j);
            SgDrawText(x.x+5,x.y+5+j,"Жизни");
            SgDrawText(x.x+5+80,x.y+5+j,intstroka(hp));
            j+=i;
            SgDrawText(x.x+5,x.y+5+j,"Деньги");
            SgDrawText(x.x+5+80,x.y+5+j,intstroka(money));
            j+=i;
            SgDrawText(x.x+5,x.y+5+j,"Доход");
            SgDrawText(x.x+5+80,x.y+5+j,intstroka(dohod));
        }
    }
    void drawKingHarReal(coords x)
    {
        int i=30, j=0;
        SgSelectBrush(BRUSH_SOLID,sgRGB(252,255,187));
        SgRectangle(x.x,x.y,x.x+220,x.y+240);
        SgDrawText(x.x+5,x.y+5+j,"Сила");
        SgDrawText(x.x+5+175,x.y+5+j,intstroka(har.power));
        j+=i;
        SgDrawText(x.x+5,x.y+5+j,"Реакция");
        SgDrawText(x.x+5+175,x.y+5+j,intstroka(har.reakcia));
        j+=i;
        SgDrawText(x.x+5,x.y+5+j,"Регенерация");
        SgDrawText(x.x+5+175,x.y+5+j,intstroka(har.regeneracia));
        j+=i;
        SgDrawText(x.x+5,x.y+5+j,"Макс. жизни");
        SgDrawText(x.x+5+175,x.y+5+j,intstroka(har.maxhp));
        j+=i;
        SgDrawText(x.x+5,x.y+5+j,"Скорость");
        SgDrawText(x.x+5+175,x.y+5+j,intstroka(har.speed));
        j+=i;
        SgLine(x.x+10,x.y+j,x.x+210,x.y+j);
        SgDrawText(x.x+5,x.y+5+j,"Жизни");
        SgDrawText(x.x+5+80,x.y+5+j,intstroka(hp));
        j+=i;
        SgDrawText(x.x+5,x.y+5+j,"Деньги");
        SgDrawText(x.x+5+80,x.y+5+j,intstroka(money));
        j+=i;
        SgDrawText(x.x+5,x.y+5+j,"Доход");
        SgDrawText(x.x+5+80,x.y+5+j,intstroka(dohod));

    }
    characteristics getHar()
    {
        return har;
    }
    characteristics getChar()
    {
        characteristics ret;
        ret=har;
        for(int i=0;i<10;i++)
        {
            ret.maxhp+=box[i].plus.maxhp;
            ret.power+=box[i].plus.power;
            ret.reakcia+=box[i].plus.reakcia;
            ret.regeneracia+=box[i].plus.regeneracia;
            ret.speed+=box[i].plus.speed;
        }

        if(ret.maxhp<0) ret.maxhp=1;
        if(ret.power<0) ret.power=1;
        if(ret.reakcia<0) ret.reakcia=1;
        if(ret.regeneracia<0) ret.regeneracia=1;
        if(ret.speed<0) ret.speed=3;
        return ret;
    }
    void startHod()
    {
        money+=dohod;
        ifHod=true;
        hod=speed*8;
        if(hp==0)
        {
            crd.x=-16000;
            crd.y=-16000;
            kill=5;
        }
        if(crd.x<0  || crd.y<0)
        {
            hod=0;
            kill--;
        }
        if((crd.x<0  || crd.y<0) && kill==0)
        {
            crd.x=rand()%1000;
            crd.y=rand()%700;
        }
        if(hp+regen<maxHp)
        {
            hp+=regen;
        }
        else if(hp<maxHp)
        {
            hp=maxHp;
        }
    }
    void endHod()
    {
        hod=0;
        ifHod=false;
    };
    int getHp()
    {
        return hp;
    }
    void setHp(int hhp)
    {
        if(hhp>=0)
            hp=hhp;
    }
    int getMoney()
    {
        return money;
    }
    void setMoney(int mon)
    {
        if(mon>-2000)
        {
            money=mon;
        }
    }
    void upPower()
    {
        har.power++;
    }
    void upReakcia()
    {
        har.reakcia++;
    }
    void upRegeneracia()
    {
        har.regeneracia++;
    }
    void upMaxHp()
    {
        har.maxhp++;
    }
    void upSpeed()
    {
        har.speed++;
    }
    bool buy(object o)
    {
        if(money>o.coast)
        {
            money-=o.coast;
        }
        else
        {
            return false;
        }
        //if(o.type-1>=0 && o.type-1<10)
        box[o.type-1]=o;
        // //cout<<box[o.type-1].imageHandle;
        return true;
    }
    coords getCoords()
    {
        return crd;
    }
    void addToImpire(coords a)
    {
        //if(a.x>=0 && a.y>=0)
        impire[impireCounter]=a;
        impireCounter++;
    }
    void overlineImpire(table &world)
    {
        for(int i=0;i<impireCounter;i++)
        {
            if(impire[i].x!=-1 && impire[i].y!=-1)
            world.overline(impire[i],5,sgRGB(0,255,0),true);
            ////cout<<impire[i].x<<" "<<impire[i].y<<endl;

        }
    }
    void recountDohod(table &world)
    {
        dohod=100;
        for(int i=0;i<impireCounter;i++)
        {
            dohod+=world.getConent(impire[i]);  
        }
    }
};
characteristics getKingdom(coords a,table &world)
{
    if(a.x>=0 && a.y>=0)
    {
        int get=world.getConent(a);
        characteristics ret;
        ret.maxhp=get;//+rand()%4;
        ret.power=sqrt(0.119)*get;//+rand()%4;
        ret.reakcia=sqrt(1.3)*get;//+rand()%4;
        ret.regeneracia=get/20;//+rand()%4;
        ret.speed=get/20;
        return ret;
    }
    characteristics ret={-1,-1,-1,-1,-1};
}
void drawKingdomHar(characteristics a,coords x)
{
    SgSelectPen(1,sgRGB(0,0,0));
    SgSelectBrush(BRUSH_SOLID,sgRGB(213,215,225));
    SgRectangle(x.x,x.y,x.x+220,x.y+120);
    SgDrawText(x.x+5,x.y+5,"Сила");
    SgDrawText(x.x+180,x.y+5,intstroka(a.power));
    SgDrawText(x.x+5,x.y+35,"Реакция");
    SgDrawText(x.x+180,x.y+35,intstroka(a.reakcia));
    SgDrawText(x.x+5,x.y+65,"Регенерация");
    SgDrawText(x.x+180,x.y+65,intstroka(a.regeneracia));
    SgDrawText(x.x+5,x.y+95,"Жизни");
    SgDrawText(x.x+180,x.y+95,intstroka(a.maxhp));
}
void harToFile(FILE* file,characteristics a)
{
    fputs(intstroka(a.maxhp),file);
    fputs("|",file);
    fputs(intstroka(a.power),file);
    fputs("|",file);
    fputs(intstroka(a.reakcia),file);
    fputs("|",file);
    fputs(intstroka(a.regeneracia),file);
    fputs("|",file);
    fputs(intstroka(a.speed),file);
    fputs("|",file);

}
void up(player &p, bool &end, int butUp,int hoverUp,int endBut, int endHover,int design)
{


    //FILE* file=fopen("buffer.wall","w");
    //harToFile(file,p.getHar());
    //fputs(intstroka(p.getMoney()),file);
    //system("cd..");
    // SgDrawText(50,50,intstroka(p.getMoney()));
    coords a={500,200};
    characteristics pHar;

    p.drawKingHar(a);
    characteristics coast;
    a.x=730;
    a.y=200;
    button upPower(a,butUp,"UP",5,35,hoverUp);
    //upPower.just=just[0];
    a.x=730;
    a.y=230;
    button upReakcia(a,butUp,"UP",5,35,hoverUp);
    //upReakcia.just=just[1];
    a.x=730;
    a.y=260;
    button upRegen(a,butUp,"UP",5,35,hoverUp);
    //upRegen.just=just[2];
    a.x=730;
    a.y=290;
    button upMaxHp(a,butUp,"UP",5,35,hoverUp);
    //upMaxHp.just=just[3];
    a.x=730;
    a.y=320;
    button upSpeed(a,butUp,"UP",5,35,hoverUp);
    //upSpeed.just=just[4];
    a.x=500;
    a.y=440;
    button endTren(a,endBut,"НАЗАД",20,72,endHover);  
    //endTren.just=just[5];
    //endTren.drawButton();
    //while(end)
    //{
    char* str;
    while(!endTren.drawButtonUnDown())
    {
        SgClearScreen(sgRGB(240,230,240));
        SgDrawImage(design,0,0);
        pHar=p.getHar();
        endTren.drawButtonUnDown();
        coast.power=50*pHar.power*sqrt(double(pHar.power))*sqrt(3.0)+5;
        coast.reakcia=40*pHar.reakcia*sqrt(double(pHar.reakcia))*sqrt(3.0)+5;
        coast.regeneracia=10*pHar.regeneracia*sqrt(double(pHar.regeneracia))*sqrt(3.0)+5;
        coast.maxhp=15*(pHar.maxhp-90)*sqrt(double(pHar.maxhp-90))*sqrt(3.0)+5;
        coast.speed=350*pHar.speed*sqrt(double(pHar.speed))*sqrt(3.0)*sqrt(2.0)+5;

        a.x=500;
        a.y=200;
        p.drawKingHarReal(a);
        a.x=730;
        a.y=200;
        str=intstroka(coast.power);
        SgDrawText(a.x+100,a.y+5,str);
        delete[] str;
        a.x=730;
        a.y=230;
        str=intstroka(coast.reakcia);
        SgDrawText(a.x+100,a.y+5,str);
        delete[] str;
        a.x=730;
        a.y=260;
        str=intstroka(coast.regeneracia);
        SgDrawText(a.x+100,a.y+5,str);
        delete[] str;
        a.x=730;
        a.y=290;
        str=intstroka(coast.maxhp);
        SgDrawText(a.x+100,a.y+5,str);
        delete[] str;
        a.x=730;
        a.y=320;
        str=intstroka(coast.speed);
        SgDrawText(a.x+100,a.y+5,str);
        delete[] str;
        int money=p.getMoney();
        if(upPower.drawButtonUnDown() && money-coast.power>-1000)
        {
            p.upPower();
            money-=coast.power;
            p.setMoney(money);

        }
        if(upReakcia.drawButtonUnDown() && money-coast.reakcia>-1000)
        {
            p.upReakcia();
            money-=coast.reakcia;
            p.setMoney(money);
        }
        if(upRegen.drawButtonUnDown() && money-coast.regeneracia>-1000)
        {
            p.upRegeneracia();
            money-=coast.regeneracia;
            p.setMoney(money);
        }
        if(upMaxHp.drawButtonUnDown() && money-coast.maxhp>-1000)
        {
            p.upMaxHp();
            money-=coast.maxhp;
            p.setMoney(money);
        }
        if(upSpeed.drawButtonUnDown() && money-coast.speed>-1000)
        {
            p.upSpeed();
            money-=coast.speed;
            p.setMoney(money);
        }


        SgFlipPages();
        SgPause(10);
    }
    end=false;
    //

    //   
    // }
    // 
}
char* generateName(int mode, int id)
{
    char* m=new char[15];
    m=intstroka(mode);
    m=strcat(m," ");
    m=strcat(m,"(");
    char* a=intstroka(id);
    m=strcat(m,a);
    m=strcat(m,").bmp");

    //delete []m;
    //    delete []a;
    ////cout<<m<<" ";
    return m;
}
int* load(int &n,int mode)
{
    n=20;
    int* mas=new int[20];
    char* buf;
    for(int i=1;i<=20;i++)
    {
        buf=generateName(mode,i);
        mas[i-1]=SgLoadImage(buf);

        ////cout<<mas[i]<<" ";
        //if(mas[i-1]==0) break;
    }
    //delete buf;
    return mas; 
}
bool objectInfo(object o,int imageHndle,coords x,button &buy)
{
    SgSelectBrush(BRUSH_SOLID,sgRGB(255,206,0));
    SgRectangle(x.x,x.y,x.x+250,x.y+440);
    //SgRectangle(x.x,x.y,x+182,x.y+200);
    char* str;
    //   coords c={x.x+15,x.y+445};
    //   button buy(c,but,"Купить",17,70,hover);
    SgDrawText(x.x+10,x.y+190,"Тип:");
    SgDrawImage(imageHndle,x.x+35,x.y);
    switch(o.type)
    {
    case 1:    SgDrawText(x.x+100,x.y+190,"Доспех"); break;
    case 2:    SgDrawText(x.x+100,x.y+190,"Меч");break;
    case 3:    SgDrawText(x.x+100,x.y+190,"Шлем");break;
    case 4:    SgDrawText(x.x+100,x.y+190,"Щит");break;
    }

    str=intstroka(o.coast);
    ////cout<<o.coast;
    SgDrawText(x.x+10,x.y+220,"Цена");
    SgDrawText(x.x+100,x.y+220,str);
    delete[] str;
    SgDrawText(x.x+60,x.y+250,"Характеристики");
    SgDrawText(x.x+10,x.y+280,"Сила");
    str=intstroka(o.plus.power);
    if(str[0]=='0') {str[0]=' ';    SgDrawText(x.x+150,x.y+280,"-");}else{SgDrawText(x.x+150,x.y+280,"+");}


    SgDrawText(x.x+180,x.y+280,str);
    delete[] str;
    SgDrawText(x.x+10,x.y+310,"Реакция");
    str=intstroka(o.plus.reakcia);
    if(str[0]=='0') {str[0]=' ';    SgDrawText(x.x+150,x.y+310,"-");}else{SgDrawText(x.x+150,x.y+310,"+");}
    SgDrawText(x.x+180,x.y+310,str);
    delete[] str;
    SgDrawText(x.x+10,x.y+340,"Макс. жизни");
    str=intstroka(o.plus.maxhp);
    if(str[0]=='0') {str[0]=' ';    SgDrawText(x.x+150,x.y+340,"-");}else{SgDrawText(x.x+150,x.y+340,"+");}
    SgDrawText(x.x+180,x.y+340,str);
    delete[] str;
    SgDrawText(x.x+10,x.y+370,"Регенерация");
    str=intstroka(o.plus.regeneracia);
    if(str[0]=='0') {str[0]=' ';    SgDrawText(x.x+150,x.y+370,"-");}else{SgDrawText(x.x+150,x.y+370,"+");}
    SgDrawText(x.x+180,x.y+370,str);
    delete[] str;
    SgDrawText(x.x+10,x.y+400,"Скорость");
    str=intstroka(o.plus.speed);
    if(str[0]=='0') {str[0]=' ';    SgDrawText(x.x+150,x.y+400,"-");}else{SgDrawText(x.x+150,x.y+400,"+");}
    SgDrawText(x.x+180,x.y+400,str);
    delete[] str;
    //buy.drawButtonUnDown();
    return buy.drawButtonUnDown();
}
void objectInfo(object o,int imageHndle,coords x)
{
    SgSelectBrush(BRUSH_SOLID,sgRGB(255,206,0));
    SgRectangle(x.x,x.y,x.x+250,x.y+440);
    //SgRectangle(x.x,x.y,x+182,x.y+200);
    char* str;
    //   coords c={x.x+15,x.y+445};
    //   button buy(c,but,"Купить",17,70,hover);
    SgDrawText(x.x+10,x.y+190,"Тип:");
    SgDrawImage(imageHndle,x.x+35,x.y);
    switch(o.type)
    {
    case 1:    SgDrawText(x.x+100,x.y+190,"Доспех"); break;
    case 2:    SgDrawText(x.x+100,x.y+190,"Меч");break;
    case 3:    SgDrawText(x.x+100,x.y+190,"Шлем");break;
    case 4:    SgDrawText(x.x+100,x.y+190,"Щит");break;
    }

    str=intstroka(o.coast);
    ////cout<<o.coast;
    SgDrawText(x.x+10,x.y+220,"Цена");
    SgDrawText(x.x+100,x.y+220,str);
    delete[] str;
    SgDrawText(x.x+60,x.y+250,"Характеристики");
    SgDrawText(x.x+10,x.y+280,"Сила");
    str=intstroka(o.plus.power);
    if(str[0]=='0') {str[0]=' ';    SgDrawText(x.x+150,x.y+280,"-");}else{SgDrawText(x.x+150,x.y+280,"+");}


    SgDrawText(x.x+180,x.y+280,str);
    delete[] str;
    SgDrawText(x.x+10,x.y+310,"Реакция");
    str=intstroka(o.plus.reakcia);
    if(str[0]=='0') {str[0]=' ';    SgDrawText(x.x+150,x.y+310,"-");}else{SgDrawText(x.x+150,x.y+310,"+");}
    SgDrawText(x.x+180,x.y+310,str);
    delete[] str;
    SgDrawText(x.x+10,x.y+340,"Макс. жизни");
    str=intstroka(o.plus.maxhp);
    if(str[0]=='0') {str[0]=' ';    SgDrawText(x.x+150,x.y+340,"-");}else{SgDrawText(x.x+150,x.y+340,"+");}
    SgDrawText(x.x+180,x.y+340,str);
    delete[] str;
    SgDrawText(x.x+10,x.y+370,"Регенерация");
    str=intstroka(o.plus.regeneracia);
    if(str[0]=='0') {str[0]=' ';    SgDrawText(x.x+150,x.y+370,"-");}else{SgDrawText(x.x+150,x.y+370,"+");}
    SgDrawText(x.x+180,x.y+370,str);
    delete[] str;
    SgDrawText(x.x+10,x.y+400,"Скорость");
    str=intstroka(o.plus.speed);
    if(str[0]=='0') {str[0]=' ';    SgDrawText(x.x+150,x.y+400,"-");}else{SgDrawText(x.x+150,x.y+400,"+");}
    SgDrawText(x.x+180,x.y+400,str);
    delete[] str;
}
void shop(player &p, bool &end, int butUp,int hoverUp, int shlemMas[],int mechMas[],int shitMas[],int dospehMas[])//,int endBut, int endHover)
{
    coords infoCoords={980,100};
    coords a={infoCoords.x+15,infoCoords.y+445};
    button buy(a,butUp,"Купить",17,70,hoverUp);
    a.x=0;
    a.y=0;
    button shlem(a,butUp,"Шлемы",20,72,hoverUp);

    a.x=220;
    a.y=0;
    button mech(a,butUp,"Мечи",20,72,hoverUp);

    a.x=440;
    a.y=0;
    button shit(a,butUp,"Щит",20,72,hoverUp);

    a.x=660;
    a.y=0;
    button dospeh(a,butUp,"Доспех",20,72,hoverUp);

    a.x=880;
    a.y=0;

    button endTren(a,butUp,"НАЗАД",20,72,hoverUp);  

    char* str;
    int money;
    table shlemT(0,60,180,180,5,4,sgRGB(0,0,0),sgRGB(0,0,0));
    table mechT(0,60,180,180,5,4,sgRGB(0,0,0),sgRGB(0,0,0));
    table shitT(0,60,180,180,5,4,sgRGB(0,0,0),sgRGB(0,0,0));
    table dospehT(0,60,180,180,5,4,sgRGB(0,0,0),sgRGB(0,0,0));

    int g=0;
    coords l;
    //int mas[5][4];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<5;j++)
        {
            //mas[i][j]=shlemMas[];
            l.x=j;
            l.y=i;
            shlemT.setContent(l,shlemMas[g]);
            mechT.setContent(l,mechMas[g]);
            shitT.setContent(l,shitMas[g]);
            dospehT.setContent(l,dospehMas[g]);
            g++;
        }
    }
            //cout<<"dfhfgh";

    bool shlemBool=true;
    bool mechBool=false;
    bool shitBool=false;
    bool dospehBool=false;
    bool shlemBool1=false;
    bool mechBool1=false;
    bool shitBool1=false;
    bool dospehBool1=false;

    object dospehHar[20];
    for(int i=0;i<20;i++)
    {
        dospehHar[i].plus.power=i*7+6*(i/5);
        dospehHar[i].plus.reakcia=+2*sqrt(double(i))*i;
        dospehHar[i].plus.speed=-double(i)*1.5;
        dospehHar[i].plus.maxhp=sqrt(13.0)*i;
        dospehHar[i].plus.regeneracia=sqrt(2.0)*i;
        dospehHar[i].type=1;
        dospehHar[i].coast=pow(double(i+4),4)+sqrt(double(i))*30*i;
        dospehHar[i].imageHandle=dospehMas[i];
        dospehHar[i].imageHandleId=i;
        // //cout<<dospehHar[i].imageHandle;
    }
    object mechHar[20];
    for(int i=0;i<20;i++)
    {
        mechHar[i].plus.power=i*7+6*(i/5);
        mechHar[i].plus.reakcia=-i;
        mechHar[i].plus.speed=-i;
        mechHar[i].plus.maxhp=sqrt(3.0)*i;
        mechHar[i].plus.regeneracia=sqrt(2.0)*i;
        mechHar[i].type=2;
        mechHar[i].coast=pow(double(i+3),4)+sqrt(double(i))*35*i;
        mechHar[i].imageHandle=mechMas[i];
        mechHar[i].imageHandleId=i;
    }
    object shlemHar[20];
    for(int i=0;i<20;i++)
    {
        shlemHar[i].plus.power=i*7+2*(i/5);
        shlemHar[i].plus.reakcia=-i/4;
        shlemHar[i].plus.speed=i/3;
        shlemHar[i].plus.maxhp=sqrt(3.0)*i;
        shlemHar[i].plus.regeneracia=sqrt(2.0)*i;
        shlemHar[i].type=3;
        shlemHar[i].coast=pow(double(i+2),4)+sqrt(double(i))*17*i;
        shlemHar[i].imageHandle=shlemMas[i];
        shlemHar[i].imageHandleId=i;
    }
    object shitHar[20];
    for(int i=0;i<20;i++)
    {
        shitHar[i].plus.power=i/3;
        shitHar[i].plus.reakcia=-i;
        shitHar[i].plus.speed=-i;
        shitHar[i].plus.maxhp=sqrt(3.0)*i;
        shitHar[i].plus.regeneracia=sqrt(2.0)*i;
        shitHar[i].type=4;
        shitHar[i].coast=pow(double(i+1),4)+sqrt(double(i))*21*(i+2);
        shitHar[i].imageHandle=shitMas[i];
        shitHar[i].imageHandleId=i;
    }



    l.x=0;
    l.y=0;
    coords cursor;




    while(!endTren.drawButtonUnDown())
    {
        SgClearScreen(sgRGB(240,230,240));
        endTren.drawButtonUnDown();
        money=p.getMoney();
        SgGetCursorPos(cursor.x,cursor.y);
        str=intstroka(money);
        SgDrawText(920,80,"Деньги:");
        SgDrawText(1080,80,str);
        delete[] str;
        if(shlem.drawButtonUnDown())
        {
            shlemBool=true;
            mechBool=false;
            shitBool=false;
            dospehBool=false;
        }
        if(shlemBool)
        {
            shlemT.drawImages();
            if(SgIsKeyDown(VK_LBUTTON) && !(cursor.x<infoCoords.x+250 && cursor.x>infoCoords.x && cursor.y<infoCoords.y+505 && cursor.y>infoCoords.y))
            {
                if(shlemT.active(l))
                {
                    shlemBool1=true;
                }
            }
            if(shlemBool1 && (l.y+1)*5-5+l.x>=0)
            {
                if(objectInfo(shlemHar[(l.y+1)*5-5+l.x],shlemT.getConent(l),infoCoords,buy))
                {
                    p.buy(shlemHar[(l.y+1)*5-5+l.x]);                    
                }
            }
        }
        if(dospeh.drawButtonUnDown())
        {
            dospehBool=true;
            shlemBool=false;
            mechBool=false;
            shitBool=false;
        }
        if(dospehBool)
        {
            dospehT.drawImages();
            if(SgIsKeyDown(VK_LBUTTON) && !(cursor.x<infoCoords.x+250 && cursor.x>infoCoords.x && cursor.y<infoCoords.y+505 && cursor.y>infoCoords.y))
            {
                if(dospehT.active(l))
                {
                    dospehBool1=true;
                }
            }
            if(dospehBool1 && (l.y+1)*5-5+l.x>=0)
            {
                if(objectInfo(dospehHar[(l.y+1)*5-5+l.x],dospehT.getConent(l),infoCoords,buy))
                    p.buy(dospehHar[(l.y+1)*5-5+l.x]);
            }
        }
        if(shit.drawButtonUnDown())
        {
            shitBool=true;
            dospehBool=false;
            shlemBool=false;
            mechBool=false;
        }
        if(shitBool)
        {
            shitT.drawImages();
            if(SgIsKeyDown(VK_LBUTTON) && !(cursor.x<infoCoords.x+250 && cursor.x>infoCoords.x && cursor.y<infoCoords.y+505 && cursor.y>infoCoords.y))
            {
                if(shitT.active(l))
                {
                    shitBool1=true;
                }
            }
            if(shitBool1 && (l.y+1)*5-5+l.x>=0)
            {
                // //cout<<shitHar[(l.y+1)*4-5+l.x].coast;
                if(objectInfo(shitHar[(l.y+1)*5-5+l.x],shitT.getConent(l),infoCoords,buy))
                    p.buy(shitHar[(l.y+1)*5-5+l.x]);
            }
        }
        if(mech.drawButtonUnDown())
        {
            mechBool=true;
            shlemBool=false;
            shitBool=false;
            dospehBool=false;
        }
        if(mechBool)
        {
            mechT.drawImages();
            if(SgIsKeyDown(VK_LBUTTON) && !(cursor.x<infoCoords.x+250 && cursor.x>infoCoords.x && cursor.y<infoCoords.y+505 && cursor.y>infoCoords.y))
            {
                if(mechT.active(l))
                {
                    mechBool1=true; 
                }
            }
            if(mechBool1 && (l.y+1)*5-5+l.x>=0)
            {
                if(objectInfo(mechHar[(l.y+1)*5-5+l.x],mechT.getConent(l),infoCoords,buy))
                    p.buy(mechHar[(l.y+1)*5-5+l.x]);
            }
        }

        SgFlipPages();
        SgPause(10);
    }
    end=false;
}
void showBox(player &p, bool end,int but,int hover)
{
    coords x={1030,0};
    coords l={x.x-30,x.y+60};
    coords c={0,0};
    button endTren(x,but,"Назад",20,75,hover);
    table boxT(x.x-960,x.y,180,180,5,2,SgRGB(0,0,0),SgRGB(0,0,0));
    bool boxBool=false;
    while(!endTren.drawButtonUnDown())
    {
        SgClearScreen(sgRGB(215,220,230));
        boxT.drawTable(); 
        if(SgIsKeyDown(VK_LBUTTON))
        {
            if(boxT.active(c))
            {
                boxBool=true;
            }
        }

        if(boxBool && (c.y)*5+c.x>=0 && p.box[c.y*5+c.x].imageHandle>0)
        {
            ////cout<<(c.y)*5+c.x;
            objectInfo(p.box[(c.y)*5+c.x],p.box[c.y*5+c.x].imageHandle,l);            
        }
        for(int i=0;i<5;i++)
        {
            if(p.box[i].imageHandle>0)
                SgDrawImage(p.box[i].imageHandle,x.x-(5-i)*180-60,x.y);
        }
        endTren.drawButtonUnDown();
        SgFlipPages();
        SgPause(10);
    }

}
void showHp(int hp,coords x,int color=sgRGB(255,0,0))
{
    SgSelectBrush(BRUSH_SOLID,color);
    SgRectangle(x.x,x.y,x.x+30,x.y+hp*4);
    // SgRectangle(20,30,40,50);
}
void showAtack(int atack,int x,int y,int color=sgRGB(255,0,0))
{
    SgSelectBrush(BRUSH_SOLID,sgRGB(213,213,213));
    SgRectangle(x,y,x+1000/3,y+30);
    SgSelectBrush(BRUSH_SOLID,color);
    SgRectangle(x,y,x+atack/3,y+30);

}
bool atackF(player &p,characteristics kingdom, int king, int kingAtack, int enemy, int enemyAtack, int king1, int kingAtack1, int enemy1, int enemyAtack1,int &hp,int bg)
{
    characteristics kingHar=p.getChar();
    int hpKing=p.getHp();
    int hpKingdom=kingdom.maxhp;
    int width,height;
    int gravity=3;
    int g=10;
    int hodChange=1000;
    bool ifatack=false;
    bool just=false;
    bool at=false;
    bool atEnemy=false;
    SgGetImageSizes(king,width,height);
    coords kingCoords={0,800-height}, enemyCoords={1250-width,800-height};
    int d;
    int napr=0;
    int enemyNapr=0;
    int enemyChange=1000;
    bool enemyIfAtack=true;
    coords kingHpCoords={0,0};
    int enemyChange1=enemyChange;
    coords enemyHpCoords={1219,0};
    int regen, enemyRegen;
    if(kingHar.reakcia/3>1) 
        regen=kingHar.reakcia/3;
    else
        regen=1;
    if(kingdom.reakcia/3>1)
        enemyRegen=kingdom.reakcia/3;
    else
        enemyRegen=1;
    while(hpKing>0 && hpKingdom>0)
    {
        SgClearScreen(sgRGB(213,213,213));
        d=Distance(kingCoords,enemyCoords);

        if(SgIsKeyDown(VK_LEFT))
        {
            kingCoords.x-=kingHar.speed;
            napr=1;
        }
        if(SgIsKeyDown(VK_RIGHT))
        {
            kingCoords.x+=kingHar.speed;
            napr=0;
        }
        if(SgIsKeyDown(VK_CONTROL) && g>0)
        {
            kingCoords.y-=double(kingHar.reakcia*2.5);
            g--;
        }
        if(kingCoords.y<800-height)
        {
            kingCoords.y+=gravity;
        }
        if(kingCoords.y>=800-height)
        {
            g=10;
        }

        /////барьеры
        if(kingCoords.x<0)
            kingCoords.x=0;
        if( kingCoords.x>=1250-width)
            kingCoords.x=1250-width;

        if(kingCoords.y<0)
            kingCoords.y=0;
        if(kingCoords.y>800-height)
            kingCoords.y=800-height;

        SgClearScreen(sgRGB(213,213,213));
         SgDrawImage(bg,0,0);
        if((SgIsKeyDown(VK_LBUTTON)&& !at))
        {
            if(napr==1)
                SgDrawImage(kingAtack1,kingCoords.x,kingCoords.y);
            else
                SgDrawImage(kingAtack,kingCoords.x,kingCoords.y);

           
            if(d<=double(width/1.9) && !at && ifatack)
            {
                hpKingdom-=kingHar.power/3;
                at=true;
                
            }
            hodChange--;
            if(hodChange==0) { ifatack=false;};
            just=true;
           // //cout<<" xfdgxdfgf";
        }
        else
        {
            if(napr==1)
                SgDrawImage(king1,kingCoords.x,kingCoords.y); 
            else
                SgDrawImage(king,kingCoords.x,kingCoords.y); 
            if(just)
            {
                just=false;
                hodChange=00;
            }
            if(hodChange==1000)
            {
                ifatack=true;hodChange=1000;
            }
            if(hodChange<1000)
            {
                if(hodChange+kingHar.reakcia/10>=1000)
                    hodChange=1000;
                if(hodChange+kingHar.reakcia/10<1000)
                    hodChange+=regen;
            }
            at=false;
        }

        if(d>=double(width/1.9) && enemyCoords.x<=kingCoords.x)
        {
            enemyCoords.x+=kingdom.speed;
            enemyChange+=enemyRegen;
            SgDrawImage(enemy1,enemyCoords.x,enemyCoords.y);
            if(enemyChange>=1000)
            {
                enemyChange=1000;
                enemyIfAtack=true;            
            }
        }
        else if(d>double(width/1.9) && enemyCoords.x>kingCoords.x)
        {
            enemyCoords.x-=kingdom.speed;  
            SgDrawImage(enemy,enemyCoords.x,enemyCoords.y);
            enemyChange+=enemyRegen;

            if(enemyChange>=1000)
            {
                enemyChange=1000;
                enemyIfAtack=true;            
            }       
        }

        else if(enemyCoords.x<=kingCoords.x && enemyIfAtack)
        {
            SgDrawImage(enemyAtack1, enemyCoords.x,enemyCoords.y);
            hpKing-=kingdom.power/3;
            enemyIfAtack=false;
            enemyChange=0;

        }
        else if(enemyCoords.x>kingCoords.x && enemyIfAtack)
        {
            SgDrawImage(enemyAtack, enemyCoords.x,enemyCoords.y);
            hpKing-=kingdom.power/3;
            enemyIfAtack=false;
            enemyChange=0;
        }
        else
        {

            enemyCoords.x-=kingdom.speed;  
            SgDrawImage(enemy1,enemyCoords.x,enemyCoords.y);
            enemyChange+=enemyRegen;

            if(enemyChange>=1000)
            {
                enemyIfAtack=true;            
            } 
        } 
       // //cout<<enemyChange<<" ";
        showHp(hpKing,kingHpCoords);
        showHp(hpKingdom,enemyHpCoords,sgRGB(0,0,255));
        showAtack(hodChange,30,0);
        showAtack(enemyChange,500,0,sgRGB(0,255,255));
              

        SgFlipPages();
        SgPause(10);


    }



    if(hpKing>0 && hpKingdom<=0)
    { 
        for(int i=0;i<800;i+=5)
        {
            SgClearScreen(sgRGB(255,0,0));
            SgDrawText(600,800-i,"Вы победили");

            SgFlipPages();
            SgPause(10);
        }

        hp=hpKing;
        return true;
    }
    else
    {
        for(int i=0;i<800;i+=5)
        {
            SgClearScreen(sgRGB(0,0,255));
            SgDrawText(600,800-i,"Вы проиграли");
            SgFlipPages();
            SgPause(10);
        }
        hp=hpKingdom;
        SgClearScreen(sgRGB(0,0,0));
        return false;
    }

}
void saveWorld(table &world)
{
    FILE* file=fopen("wall.wsh","w");
    char* str;
    str=intstroka(world.cols);
    fputs(str,file);
    delete[] str;
    fputs("|",file);
    str=intstroka(world.lines);
    fputs(str,file);
    delete[] str;
    fputs("|",file);
    str=intstroka(world.width);
    fputs(str,file);
    delete[] str;
    fputs("|",file);
    str=intstroka(world.height);
    fputs(str,file);
    delete[] str;
    fputs("|",file);
    str=intstroka(world.xy.x);
    fputs(str,file);
    fputs("|",file);
    str=intstroka(world.xy.y);
    fputs(str,file);
    fputs("|",file);
    delete[] str;
    int x;
    coords c;
    for(int i=0;i<world.cols;i++)
    {
        for(int j=0;j<world.lines;j++)
        {
            c.x=i;
            c.y=j;
            x=world.getConent(c);
            str=intstroka(x);
            fputs(str,file);
            delete[] str;
            if(j!=world.lines)
                fputs("/",file);
        }
        fputs("*",file);
    }
    fclose(file);
}
void loadWorld(table &world)
{
   FILE* file=fopen("wall.wsh","r");
   char* str=new char[2500];
   fgets(str,2499,file);
   int x=0;
   char** strMas=new char*[9];
   strMas[0]=strtok(str,"|");
//   //cout<<strMas[0]<<endl;
   for(int i=1;i<8;i++)
   {
       strMas[i]=strtok(NULL,"|");
       //if(strMas[i]!=NULL)
       ////cout<<strMas[i]<<endl;
   }
   world.cols=atoi(strMas[0]);
   world.lines=atoi(strMas[1]);
   world.width=atoi(strMas[2]);
   world.height=atoi(strMas[3]);
   world.xy.x=atoi(strMas[4]);
   world.xy.y=atoi(strMas[5]);
//   //cout<<strMas[6]<<endl;
   coords c;
   char** strS=new char*[world.cols+1];
   strS[0]=strtok(strMas[6],"*");
 //  //cout<<strS[0]<<endl;
   for(int i=1;i<world.cols;i++)
   {
       strS[i]=strtok(NULL,"*");
 //      //cout<<strS[i]<<endl;
   }
   char* t;
   for(int j=0;j<world.cols;j++)
   {
       t=strtok(strS[j],"/");
       c.x=j;
       c.y=0;
       world.setContent(c,atoi(t));       
       for(int i=1;i<world.lines;i++)
       {
           t=strtok(NULL,"/"); 
           c.x=j;
           c.y=i;
           world.setContent(c,atoi(t));
          // //cout<<world.getConent(c)<<" ";
       }
       ////cout<<endl;
   }
 //  //cout<< world.cols<<world.lines<<world.width<<world.height<<world.xy.x<<world.xy.y<<endl;
  
        ////cout<<world.getConent(lllll)<<" ";   
   fclose(file);
}
void savePlayer(player &p)
{
    FILE* file=fopen("player.whs","w");
    fputs(intstroka(p.world),file);
    fputs("|",file);
    fputs(intstroka(p.crd.x),file);
    fputs("|",file);
    fputs(intstroka(p.crd.y),file);
    fputs("|",file);
    fputs(intstroka(p.money),file);
    fputs("|",file);
    fputs(intstroka(p.impireCounter),file);
    fputs("|",file);
    fputs(intstroka(p.hod),file);
    fputs("|",file);
    fputs(intstroka(p.har.maxhp),file);
    fputs("|",file);
    fputs(intstroka(p.har.power),file);
    fputs("|",file);
    fputs(intstroka(p.har.reakcia),file);
    fputs("|",file);
    fputs(intstroka(p.har.regeneracia),file);
    fputs("|",file);
    fputs(intstroka(p.har.speed),file);
    fputs("|",file);
    for(int i=0;i<10;i++)
    {
        fputs(intstroka(p.box[i].coast),file);
        fputs("/",file);
        fputs(intstroka(p.box[i].imageHandleId),file);
        fputs("/",file);
        fputs(intstroka(p.box[i].type),file);
        fputs("/",file);
        fputs(intstroka(p.box[i].plus.maxhp),file);
        fputs("/",file);
        fputs(intstroka(p.box[i].plus.power),file);
        fputs("/",file);
        fputs(intstroka(p.box[i].plus.reakcia),file);
        fputs("/",file);
        fputs(intstroka(p.box[i].plus.regeneracia),file);
        fputs("/",file);
        fputs(intstroka(p.box[i].plus.speed),file);
        fputs("*",file);
    }
    fputs("|",file);
    for(int i=0;i<p.impireCounter;i++)
    {
        fputs(intstroka(p.impire[i].x),file);
        fputs("/",file);
        fputs(intstroka(p.impire[i].y),file);
        fputs("/",file);
    }
    fputs("|",file);
    fclose(file);
}
void loadPlayer(player &p,int shlemMas[],int mechMas[],int shitMas[],int dospehMas[])
{
   FILE* file=fopen("player.whs","r");
   char* str=new char[2500];
   fgets(str,2499,file);
   char** strMas=new char*[15];
   strMas[0]=strtok(str,"|");
   for(int i=1;i<15;i++)
   {
       strMas[i]=strtok(NULL,"|");
   }
   p.world=atoi(strMas[0]);
   p.crd.x=atoi(strMas[1]);
   p.crd.y=atoi(strMas[2]);
   p.money=atoi(strMas[3]);
   p.impireCounter=atoi(strMas[4]);
 //  //cout<<p.impireCounter<<endl;
   p.hod=atoi(strMas[5]);
   p.har.maxhp=atoi(strMas[6]);
   p.har.power=atoi(strMas[7]);
   p.har.reakcia=atoi(strMas[8]);
   p.har.regeneracia=atoi(strMas[9]);
   p.har.speed=atoi(strMas[10]);
  // //cout<<p.world<<" "<<p.crd.x<<" "<<p.crd.y<<" "<<p.money<<" "<<p.impireCounter<<" "<<p.hod<<" "<<p.har.maxhp<<" "<<p.har.power<<" "<<p.har.reakcia<<" "<<p.har.regeneracia<<" "<<p.har.speed<<endl;
   ////cout<<strMas[11]<<endl;
   char** strS=new char*[10];
   strS[0]=strtok(strMas[11],"*");
   for(int i=1;i<10;i++)
   {
       strS[i]=strtok(NULL,"*");
   }
   char* strSS;
   
   for(int i=0;i<10;i++)
   {
       p.box[i].coast=atoi(strtok(strS[i],"/"));
       p.box[i].imageHandleId=atoi(strtok(NULL,"/"));
       p.box[i].type=atoi(strtok(NULL,"/"));
       p.box[i].plus.maxhp=atoi(strtok(NULL,"/"));
       p.box[i].plus.power=atoi(strtok(NULL,"/"));
       p.box[i].plus.reakcia=atoi(strtok(NULL,"/"));
       p.box[i].plus.regeneracia=atoi(strtok(NULL,"/"));
       p.box[i].plus.speed=atoi(strtok(NULL,"/"));
       if(p.box[i].type==1 && p.box[i].imageHandleId>=0)
       {
           p.box[i].imageHandle=dospehMas[p.box[i].imageHandleId];
       }
       if(p.box[i].type==2)
       {
           p.box[i].imageHandle=mechMas[p.box[i].imageHandleId];
       }
       if(p.box[i].type==3)
       {
           p.box[i].imageHandle=shlemMas[p.box[i].imageHandleId];
       }
       if(p.box[i].type==4)
       {
           p.box[i].imageHandle=shitMas[p.box[i].imageHandleId];
       }
    }
   //cout<<strMas[12]<<endl;
   p.impire[0].x=atoi(strtok(strMas[12],"/"));
   p.impire[0].y=atoi(strtok(NULL,"/"));
   char* pStr;
   for(int i=1;i<p.impireCounter;i++)
   {
       pStr=strtok(NULL,"/");
       if(pStr!=NULL)
       p.impire[i].x=atoi(pStr);
       pStr=strtok(NULL,"/");
       if(pStr!=NULL)
       p.impire[i].y=atoi(pStr);
   }
}
void main()
{
    SetConsoleOutputCP(1251);
    SgCreate(1250,800, "KINGS:Wall Street Hotel 0.105");
    table wsh(0,0,60,60,17,13,sgRGB(255,255,255),sgRGB(213,213,213));
    coords h={0,0};
    srand(time(0));
    for(int i=0;i<13;i++)
    {
        for(int j=0;j<17;j++)
        {
            h.x=j;
            h.y=i;
            wsh.setContent(h,rand()%200+15,15,15);           
        }    
    }
            
    /////////////// Подгрузка главной кнопки
     
    int mainButHandle=SgLoadImage("Main.jpg");//cout<<mainButHandle<<"gfgf";
    int mainButHandleHover=SgLoadImage("1.jpg");
    //////////////
    coords x={1020,740};
    
    button tren(x,mainButHandle,"Тренировка",13,20,mainButHandleHover);
    coords z={0,0};
    player p1(1,z,1,SgLoadImage("red.jpg"));
    coords l={1106,0};
    coords k={3,3};
    button endHod(l,SgLoadImage("hod.jpg")," ",0,0,SgLoadImage("hodhover.jpg"));
    l.x=1026;
    button atack(l,SgLoadImage("atack.jpg")," ",0,0,SgLoadImage("atackHover.jpg"));
    l.y+=163;
    button lavka(l,mainButHandle,"Лавка",13,35,mainButHandleHover);
    l.y+=60;
    button show(l,mainButHandle,"Ящик",13,50,mainButHandleHover);
    coords f;
    ///// булы для кнопок 
    bool upBool=false;
    bool over=false;
    bool atackBool=false;
    bool lavkaBool=false;
    bool wshBool=false;
    bool showBool=false;
    l.y+=60;
    coords kingdomHar=l;
    ////////////Загрузка элементов магазина
    int dospehCounter;
    int* dospeh=load(dospehCounter,1);
    int mechCounter;
    int* mech=load(mechCounter,2);
    int shlemCounter;
    int* shlem=load(shlemCounter,3);
    int shitCounter;
    int* shit=load(shitCounter,4);
            
    //////////// Картинки для сражений
    int king=SgLoadImage("king.bmp");
    int king1=SgLoadImage("king1.bmp");
    int kingAtack=SgLoadImage("atackKing.bmp");
    int kingAtack1=SgLoadImage("atackKing1.bmp");
    int enemy=SgLoadImage("enemy.bmp");
    int enemy1=SgLoadImage("enemy1.bmp");
    int enemyAtack=SgLoadImage("enemyAtack.bmp");
    int enemyAtack1=SgLoadImage("enemyAtack1.bmp");
    SgSetImageColorKey(king,sgRGB(255,255,255));
    SgSetImageColorKey(kingAtack,sgRGB(255,255,255));
    SgSetImageColorKey(enemy,sgRGB(255,255,255));
    SgSetImageColorKey(enemyAtack,sgRGB(255,255,255));
    SgSetImageColorKey(king1,sgRGB(255,255,255));
    SgSetImageColorKey(kingAtack1,sgRGB(255,255,255));
    SgSetImageColorKey(enemy1,sgRGB(255,255,255));
    SgSetImageColorKey(enemyAtack1,sgRGB(255,255,255));
    //////////// Мини кнопка для прокачки
    int u=SgLoadImage("upBut.jpg");
    int u1=SgLoadImage("upButHover.jpg");
    ////////////менюшка
    bool menuBool=true;
    bool menuBool1=true;
    coords menuCoords={0,0};
    button newGame(menuCoords,mainButHandle,"Новая игра",15,50,mainButHandleHover);
    menuCoords.y+=60;
    button saveGame(menuCoords,mainButHandle,"Сохранить",15,50,mainButHandleHover);
    menuCoords.y+=60;
    button loadGame(menuCoords,mainButHandle,"Загрузить",15,50,mainButHandleHover);
    menuCoords.y+=60;
    button exitGame(menuCoords,mainButHandle,"Выход",15,60,mainButHandleHover);
    ////////////Декорации
    int knight=SgLoadImage("knight.jpg");
    int trenImg=SgLoadImage("tren.bmp");
    int batleImg=SgLoadImage("batle.bmp");
    ///////////
    coords nap;
    characteristics deff;
    int hpNap;
    coords over1={0,0};
    while(SgIsActive())
    {
        SgClearScreen(sgRGB(213,213,213));
        //SgDrawImage(batleImg,0,0);
       // wsh.overline(over1,5,sgRGB(0,255,0),true);

        SgSelectPen(1,sgRGB(255,0,0));
        SgGetCursorPos(x.x,x.y);
        SgSelectPen(1,sgRGB(0,0,0));
        // wsh.drawTable();

        wsh.drawContent();
        wsh.overline(x,5,sgRGB(255,0,0));
        SgSelectPen(1,sgRGB(0,0,0));
        p1.drawPlayer();



        if(atack.drawButton())
        {
            nap=wsh.getKletkiByCoords(p1.getCoords());
            ////cout<<nap.x<<nap.y;
            if(nap.x>=0 && nap.y>=0)
            {
                deff=getKingdom(nap,wsh);
                if(atackF(p1,deff,king,kingAtack,enemy,enemyAtack,king1,kingAtack1,enemy1,enemyAtack1,hpNap,batleImg))
                {
                    p1.setHp(hpNap);
                    p1.setMoney(p1.getMoney()+deff.maxhp*4);
                    p1.addToImpire(nap);
                }
                else
                {
                    wsh.setContent(nap,hpNap);
                    p1.setHp(0);
                }
            }

        }
        if(wsh.active(x) && !(menuBool || menuBool1) )
        {
            p1.moovePlayer(x,wsh);
            wshBool=true;
        }

        if(wshBool)
        {
            if(x.x!=-1 && x.y!=-1) 
                drawKingdomHar(getKingdom(x,wsh),kingdomHar);
        }
        if(lavka.drawButtonUnDown())
        {
            lavkaBool=true;    
        }
        if(lavkaBool)
        {
            shop(p1,lavkaBool,mainButHandle,mainButHandleHover,shlem,mech,shit,dospeh);
        }
        if(endHod.drawButtonUnDown())
        {
            p1.endHod();
            p1.startHod();
        }
        if(show.drawButtonUnDown())
        {
            SgClearScreen(sgRGB(213,213,231));
            showBox(p1,showBool,mainButHandle,mainButHandleHover);        
        }
        // bool a=tren.drawButton();

        p1.showHodChange();




        coords k={1020,500};
        p1.drawKingHar(k);
        ////cout<<a<<" ";


        if(tren.drawButtonUnDown() || upBool)
        {

            upBool=true;
        }
        if(upBool)
        {
            up(p1,upBool,u,u1,mainButHandle,mainButHandleHover,trenImg); 
        }
        p1.overlineImpire(wsh);
        p1.recountDohod(wsh);
        menuBool=SgIsKeyPressed(VK_ESCAPE);
        if(menuBool) menuBool1=true;
        if(menuBool || menuBool1)
        {
           // menuBool1=menuBool;
            SgClearScreen(SgRGB(213,214,215));
            SgDrawImage(knight,0,0);
            if(SgIsKeyPressed(VK_F1))
            {
                 menuBool=false;
                menuBool1=false;           
            }
            if(newGame.drawButtonUnDown())
            {
                menuBool=false;
                menuBool1=false;
            }
            if(saveGame.drawButtonUnDown())
            {
                saveWorld(wsh);
                savePlayer(p1);
                menuBool=false;
                menuBool1=false;
            }
            if(loadGame.drawButtonUnDown())
            {
                loadWorld(wsh);
                loadPlayer(p1,shlem,mech,shit,dospeh);
                menuBool=false;
                menuBool1=false;
                
            }
            if(exitGame.drawButtonUnDown())
            {
                SgDestroy();
            }

        }



        SgFlipPages();
        SgPause(10);
    }
    SgDestroy();
}