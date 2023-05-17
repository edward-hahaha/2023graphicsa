#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"///week13-1
GLMmodel * head =NULL;///week13-1
GLMmodel * uparmR =NULL;///week13-1
GLMmodel * lowarmR =NULL;///week13-1
GLMmodel * body =NULL;///week13-1
int show[4]={1,1,1,1};///week13-3///week14 3-2
int ID = 3;///week14-3-1 //0頭 1身體 2上手臂 3下手臂///week14 3-2
void keyboard(unsigned char key,int x, int y){
    if(key=='0') ID = 0;///week14 3-1
    if(key=='1') ID = 1;///week14 3-1
    if(key=='2') ID = 2;///week14 3-1
    if(key=='3') ID = 3;///week14 3-1
    ///if(key=='0') show[0] = !show[0];///week13-3
    ///if(key=='1') show[1] = !show[1];
    ///if(key=='2') show[2] = !show[2];
    ///if(key=='3') show[3] = !show[3];
    glutPostRedisplay();
}///原來的keyboard先註解
FILE * fout=NULL;///step2-2
FILE * fin =NULL;///2
float teapotX=0,teapotY=0;
float angle=0,angle2=0,angle3=0;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glScalef(0.2,0.2,0.2);///week13-2
        if(body==NULL){///week13-1
            head = glmReadOBJ("model/head.obj");///week13-2
            body = glmReadOBJ("model/body.obj");///week13-1
            uparmR = glmReadOBJ("model/uparmR.obj");///week13-3
            lowarmR = glmReadOBJ("model/lowarmR.obj");///week13-3
            ///glmUnitize(body);///week13-1
        }
        if(ID==0)glColor3f(1,0,0);///week14-3-1
        else glColor3f(1,1,1);///week14-3-1
        if(show[0]) glmDraw(head, GLM_MATERIAL);///week13-1

        if(ID==1)glColor3f(1,0,0);///week14-3-1
        else glColor3f(1,1,1);///week14-3-1
        if(show[1]) glmDraw(body, GLM_MATERIAL);///week13-2

        glPushMatrix();///week13-4
            glTranslatef(-1.200356,+0.466667,0);///week14-3-2

            glRotatef(angle,0,0,1);///week14-3-2 TRT建出來
            glTranslatef(1.200356,-0.466667,0);///week14-3-2
            if(ID==2)glColor3f(1,0,0);///week14-3-1
            else glColor3f(1,1,1);///week14-3-1
            if(show[2]) glmDraw(uparmR, GLM_MATERIAL);///week13-3

            glPushMatrix();
                glTranslatef(-1.946666,0.126667,0);///幫忙找出TRT移動的值///week14-3-3
                glRotatef(angle,0,0,1);///week14-3-2 TRT建出來
                glTranslatef(1.946666,-0.126667,0);///week14-3-2

                if(ID==3)glColor3f(1,0,0);///week14-3-1
                else glColor3f(1,1,1);///week14-3-1
                if(show[3]) glmDraw(lowarmR, GLM_MATERIAL);///week13-3
            glPopMatrix();

        glPopMatrix();///week13-4


    glPopMatrix();

    glColor3f(0,1,0);///week14-3-2放個小茶壺在中心當參考點
    glutSolidTeapot(0.02);///week14-3-2
    glutSwapBuffers();
}
int oldX=0,oldY=0;///week13-4
void motion (int x,int y){///week13-4
    teapotX += (x-oldX)/150.0;
    teapotY-= (y-oldY)/150.0;
    oldX = x;
    oldY = y;
    angle= x;///week14-3-2
    printf("glTranslatef(%f,%f,0);\n",teapotX,teapotY);
    glutPostRedisplay();
}
void mouse(int button,int state,int x,int y)
{
    if(state==GLUT_DOWN){
        oldX = x;///week13-4teapotX = (x-150)/150.0;
        oldY = y;///week13-4teapotY = (150-y)/150.0;
        angle =x;///week13-4
        ///if(fout==NULL)fout =fopen("file4.txt","w");week12
        ///fprintf(fout,"%f %f\n",teapotX,teapotY);
    }
    display();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("week14");

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);///week13-4
	glutKeyboardFunc(keyboard);///2keboard要做事了

    glutMainLoop();
}
