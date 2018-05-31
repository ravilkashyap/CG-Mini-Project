#include <GL/glut.h>
#include <iostream>//for strlen
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <cstdio>
#include <time.h>
#include<math.h>
#include <thread>  


int c=010;
int i,q,speed=0;
int score = 0;//for score counting
int screen = 0;
bool collide = false;//check if tile collide to make game over
char buffer[10];
int tileX = 247, tileY = 70;
int otileX[4], otileY[4];
int divx = 0, divy = 6;


void drawText(char ch[],int xpos, int ypos)//draw the text for score and game over
{
    int numofchar = strlen(ch);
    glLoadIdentity ();
    glRasterPos2f( xpos , ypos);
    for (i = 0; i <= numofchar - 1; i++)
    {

        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ch[i]);//font used here, may use other font also
    }
}


void drawTextNum(char ch[],int numtext,int xpos, int ypos)//counting the score
{
    int len;
    int k;
    k = 0;
    len = numtext - strlen (ch);
    glLoadIdentity ();
    glRasterPos2f( xpos , ypos);
    for (i = 0; i <=numtext - 1; i++)
    {
        if ( i < len )
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'0');
        else
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
            k++;
        }

    }
}


void ovpos()
{
    glClearColor(0.1,0.4,0.7,1);
    for(i = 0; i < 4; i++)
    {
        if(rand() % 2 == 0)
            {
                otileX[i] = 200;
            }
            else if(rand() % 3 == 0||rand() % 5==0)
            {
                otileX[i] = 280;
            }
            else
            {
                otileX[i] = 350;
            }
        otileY[i] = 1000 - i * 160;
    }
}



void drawPath()
{
    
glBegin(GL_QUADS);
    glColor3f(0.4,0.4,0.4);
    glVertex2f(120, 500);
    glVertex2f(120, 0);
    glVertex2f(130, 0);
    glVertex2f(130, 500);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.4,0.4,0.4);
    glVertex2f(370, 500);
    glVertex2f(370, 0);
    glVertex2f(380, 0);
    glVertex2f(380, 500);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2f(230 - 100, 500);
    glVertex2f(230 - 100, 0);
    glVertex2f(270 + 100, 0);
    glVertex2f(270 + 100, 500);

    glEnd();
}



void drawCircle(int tileX, int tileY, int radius)
{
	float x2,y2;
float angle;
	glBegin(GL_TRIANGLE_FAN);
glVertex2f(tileX,tileY);

for (angle=1.0f;angle<361.0f;angle+=1)
{
    x2 = tileX+sin(angle)*radius;
    y2 = tileY+cos(angle)*radius;
    glVertex2f(x2,y2);
}

glEnd();
}

void drawObject()//our target object
{
    // glPointSize(50.0);
    // glBegin(GL_POINTS);
    // glColor3f(1,0.5,0);
    // //glColor3f((rand() % 100 + 30)/100,(rand() % 100 + 30)/100,(rand() % 100 + 30)/100);
    // glVertex2f(tileX, tileY);
    // glEnd();

    //filled circle


glColor3f(0.9,0.9,0.9);
drawCircle(tileX,tileY,20);

glColor3f(1,0.5,0);
drawCircle(tileX,tileY,10);




glColor3f(0,0,0.8);
drawCircle(tileX+10,tileY+10,4);

glColor3f(0.8,0,0.8);
drawCircle(tileX+10,tileY-10,4);

glColor3f(0.8,0,0);
drawCircle(tileX-10,tileY+10,4);

glColor3f(0,0.8,0);
drawCircle(tileX-10,tileY-10,4);


// glColor3f(0,0,0.7);
// drawCircle(tileX,tileY+10,4);

// glColor3f(0.7,0,0.7);
// drawCircle(tileX,tileY-10,4);

// glColor3f(0.7,0,0);
// drawCircle(tileX+10,tileY,4);

// glColor3f(0,0.7,0);
// drawCircle(tileX-10,tileY,4);



}


void drawOTile()//other tiles
{

    for(i = 0; i < 4; i++)
    {
        glPointSize(90.0);
        glBegin(GL_QUADS);
        if(i==0)
        glColor3f(0.8,0.2,0);
    	else if(i==1)
        glColor3f(0.5,0.2,0.8);
    	else if(i==2)
        glColor3f(0.5,0.8,0.2);
    	else
    	glColor3f(0.8,0.2,0.5);

        //glColor3f((rand() % 100 + 10)/100,(rand() % 100 + 10)/100,(rand() % 100 + 10)/100);
        glVertex2f(otileX[i]-60, otileY[i]+50);
        glVertex2f(otileX[i]-60, otileY[i]);
        glVertex2f(otileX[i], otileY[i]);
        glVertex2f(otileX[i], otileY[i]+50);
   


		glVertex2f(370, 500);
		glVertex2f(370, 0);
		glVertex2f(380, 0);
		glVertex2f(380, 500);


        glEnd();
        otileY[i] = otileY[i] - 10*speed	;

        if(otileY[i] > tileY - 25 - 25 || otileY[i] < tileY + 25 + 25 || otileX[i] > tileX)
        {
            collide = true;
            
        }

        // if(otileY[i] < -25)
        // {
        //     if(rand() % 2 == 0)
        //     {
        //         otileX[i] = 200;
        //     }
        //     else
        //     {
        //         otileX[i] = 280;
        //     }
        //     otileY[i] = 600;
        // }

        if(otileY[i] < -25)
        {
            if(rand() % 2 == 0)
            {
                otileX[i] = 200;
            }
            else if(rand() % 3 == 0||rand() % 5==0)
            {
                otileX[i] = 280;
            }
            else
            {
                otileX[i] = 360;
            }
            otileY[i] = 600;
        }
    }
}

void Specialkey(int key, int x, int y)//allow to use navigation key for movement of tile
{
    
    switch(key)
    {
            
        case GLUT_KEY_LEFT:
            if(c==100) 
            {   
                tileX = 170;
            }
            else if(c==010) 
            {   c=100;
                tileX = 170;
            }
            else if(c==001) 
            {
                tileX = 255;
                c=010;
            }
            else
            tileX = 170;

            break;
        case GLUT_KEY_RIGHT:

        if(c==001) 
            {   
                tileX = 333;
            }
            else if(c==010) 
            {
                tileX = 333;
                c=001;
            }
            else if(c==100) 
            {
                tileX = 255;
                c=010;
            }
            else
            tileX = 333;

            break;

    }

    glutPostRedisplay();
}

void Normalkey(unsigned char key, int x, int y)
{
    switch(key)
    {
        case ' ':if(screen == 0)
            screen=1;
            break;
        case 'b':
        case 'B':if(screen == 1)
            screen=2;
            speed=1;
            break;
        case 'i':
        case 'I':if(screen == 1)
            screen=2;
            speed=1.5;
            break;
        case 'e':
        case 'E':if(screen == 1)
            screen=2;
            speed=2;
            break;
        case 27:
        exit(0);
    }
}


void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}


void display()
{
    if(screen == 0)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1,1,1);
        drawText("2D DODGE GAME", 180, 280);
        // drawText("PLAYER", 170, 250);
        drawText("Press SPACE to continue", 180, 180);
        glutSwapBuffers();
    }
    else if(screen == 1)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1,1,1);
        drawText("Instructions:",30, 440);
        drawText("The aim of the game is to dodge the obstacles for as long as you can!",30, 400);
        drawText("Controls:",30, 340);

        drawText("Use <- to move left", 170, 310);
        drawText("Use -> to move right", 170, 270);
        drawText("Levels:",30, 210);
        drawText("B - Beginner", 170, 190);
        drawText("I  - Intermediate", 170, 160);
        drawText("E - Expert", 170, 130);
        drawText("Select (B,I,E) - ", 30, 80);
    
        glutSwapBuffers();
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT);
        drawPath();
        drawObject();
        drawOTile();
        score = score + 1;
        glColor3f(1,1,1);

        drawText("Score :", 395,465);
        sprintf( buffer, "%d", score );
        drawTextNum(buffer, 6, 450,465);

        drawText("Dodge :", 395,425);
        sprintf( buffer, "%d", score/20 );
        drawTextNum(buffer, 6, 450,425);

        glutSwapBuffers();
        for(q = 0; q<= 10000000; q++){;}
        if(collide == true)
        {
            glColor3f(1,1,1);
            drawText("Game Over", 200,250);
            glutSwapBuffers();

            //getchar();
        }
    }
}

void playmusic()
{
	system("canberra-gtk-play -f imperial_march.wav");
}
int main(int argc, char **argv)
{
	
    srand(time(NULL));
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,500);
    glutCreateWindow("2D Dodge game");
    ovpos();
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(Specialkey);
    glutKeyboardFunc(Normalkey);
    // glutFullScreen();
    glutIdleFunc(display);
    //std::thread first (playmusic);
    glutMainLoop();
}
