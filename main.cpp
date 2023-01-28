#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"

using namespace std;
const double PI = 3.14159265389;
GLfloat theta1 = 360.0,theta = 0.0, alpha0 = 0.0,theta0 = 0.0,eye_x = -50, axis_x=0.0, axis_y=0.0,axis_z=0.0, eye_y = 40, eye_z = 650.0, look_x = 0.0, look_y = 5.0, look_z = 0.0, upx = 0, upy = 1, upz = 0,
theta_fan = 0.0, theta_pakha = 0.0,
angle_P = 270.0, angle_Y = 270.0,angle_R = 90.0,inc_value = 5.1;

int rr=0;
GLboolean fan_rotate = true,pop=false, dooroff=false,bRotate = true,sRotate = false,uRotate = false, light6=true,
lamp_am=false,tlamp_on=false,lamp_duf=false,lamp_on=false,lamp_spec=false,lamp_off=true;

float angle=0.0;
int anglex= 0, angley = 0, anglez = 0;          //rotation angles
int window;
int wired=0;
int shcpt=1;
int animat = 0;
const int L=20;
const int dgre=3;
int ncpt=L+1;
int clikd=0;
const int nt = 40;				//number of slices along x-direction
const int ntheta = 20;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f,ly = 0.0f;
// XZ position of the camera
float ex=0.0f,ez=0.0f;
int turn=0;
double doorX = 0, lifty=0;

float cloudX = 0, ccX = 0;
int cloudStatus = 1, ccStatus =0, be=0;

GLboolean light1=true, a1=true, d1=true, s1=true, light2=true, a2=true, d2=true, s2=true, light3=true, a3=true, d3=true, s3=true, dooron=false,liftup=false, liftdown=false;
unsigned int ID[50];


static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};


static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}


void drawCube()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);

        glVertex3fv(&v_cube[quadIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);glTexCoord2f(0,1);
    }
    glEnd();
}




static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte quadIndices2[1][4] =
{
    {0, 3, 2, 1}
};

void drawpyramid()
{

    //glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        //glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);

        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        //glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(v_pyramid[quadIndices2[i][0]][0], v_pyramid[quadIndices2[i][0]][1], v_pyramid[quadIndices2[i][0]][2],
                    v_pyramid[quadIndices2[i][1]][0], v_pyramid[quadIndices2[i][1]][1], v_pyramid[quadIndices2[i][1]][2],
                    v_pyramid[quadIndices2[i][2]][0], v_pyramid[quadIndices2[i][2]][1], v_pyramid[quadIndices2[i][2]][2]);

        glVertex3fv(&v_pyramid[quadIndices2[i][0]][0]);
        glVertex3fv(&v_pyramid[quadIndices2[i][1]][0]);
        glVertex3fv(&v_pyramid[quadIndices2[i][2]][0]);
        glVertex3fv(&v_pyramid[quadIndices2[i][3]][0]);
    }
    glEnd();
    //glutSolidSphere (3.0, 20, 16);

}

void triangle()
{
    glBegin(GL_TRIANGLES);
    glColor3f(2.0,2.0,2.0);
    glVertex2f(4.0,4.0);
    glColor3f(0.0,0.2,0.0);
    glVertex2f(4.0,0.0);
    glColor3f(0.0,0.0,0.2);
    glVertex2f(0.0,0.0);
    glEnd();
}

void drawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere (1.0, 16, 16);
}


void getCameraEye_Y() // x axis , y t
{
     look_x= eye_x+30.0*(cos(angle_Y*3.1416/180.0));
    look_z = eye_z+30.0*(sin(angle_Y*3.1416/180.0));
}

void getCameraEye_P() // y axis , p o
{
   look_y = eye_y+30.0*(cos(angle_P*3.1416/180.0));
   look_z = eye_z+30.0*(sin(angle_P*3.1416/180.0));
}


void getCameraEye_R() // z axis ,r e
{
    upx = 100.0*(cos(angle_R*3.1416/180.0));
    upy = 100.0*(sin(angle_R*3.1416/180.0));

}



void base()
{
    ///field
    glBindTexture(GL_TEXTURE_2D, ID[1]);
    glEnable(GL_TEXTURE_2D);

    glColor3f(0.0, 0.5, 0.6);
    glPushMatrix();
    //glViewport(0, 0, 400, 400);
    glTranslatef(-300,-20,-500);
    glScalef(200, 0.05, 430);

    GLfloat no_mat56[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient56[] = { 0.5, 0.5, 0.5, 0.5 };
    GLfloat mat_diffuse56[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular56[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess56[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient56);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse56);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular56);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess56);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///sky_middle

    glBindTexture(GL_TEXTURE_2D, ID[2]);
    glEnable(GL_TEXTURE_2D);

    glColor3f(0.0, 0.5, 0.6);
    glPushMatrix();
    //glViewport(0, 0, 400, 400);
    glTranslatef(-300,570,-500);
    glScalef(200, 200, 0.05);
    glRotatef(-90,0,0,1);

    GLfloat no_mat5[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient5[] = { 0.5, 0.5, 0.5, 0.5 };
    GLfloat mat_diffuse5[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular5[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess5[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient5);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse5);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular5);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess5);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    ///sky_left
    glBindTexture(GL_TEXTURE_2D, ID[2]);
    glEnable(GL_TEXTURE_2D);

    glColor3f(0.0, 0.5, 0.6);
    glPushMatrix();
    glTranslatef(-300,-30,-500);
    glScalef(0.05, 200,430 );
    //glRotatef(-90,0,0,1);



    glRotatef(-90,1,0,0);
    glRotatef(180,0,0,1);
    GLfloat no_mat5m[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient5m[] = { 0.5, 0.5, 0.5, 0.5 };
    GLfloat mat_diffuse5m[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular5m[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess5m[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient5m);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse5m);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular5m);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess5m);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    ///sky_right
    glBindTexture(GL_TEXTURE_2D, ID[2]);
    glEnable(GL_TEXTURE_2D);

    glColor3f(0.0, 0.5, 0.6);
    glPushMatrix();
    glTranslatef(300,570,-500);
    glScalef(0.05, 200,430 );
    glRotatef(-90,0,0,1);


    GLfloat no_mat5mm[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient5mm[] = { 0.5, 0.5, 0.5, 0.5 };
    GLfloat mat_diffuse5mm[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular5mm[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess5mm[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient5mm);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse5mm);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular5mm);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess5mm);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void basement()
{
    glPushMatrix();
    glScalef(1,1,1);
    base();
    glPopMatrix();
}

void road()
{
    glBindTexture(GL_TEXTURE_2D, ID[3]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(-300,-20,310);
    glScalef(200, 0.2, 30);

    GLfloat no_mat56[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient56[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffuse56[] = { 1,1,1, 1.0 };
    GLfloat mat_specular56[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess56[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient56);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse56);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular56);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess56);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}


void cone()
{
  glutSolidCone(2.3,5,5,8);

}

void tree1()
{
    ///tree1 body
    //glColor3f( 	0.545, 0.070, 0.070);
    glBindTexture(GL_TEXTURE_2D, ID[4]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(-8,20,34);
    glScalef(0.2,3.8,0.3);
    glRotatef(90,1,0,0);
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.0, 0.0, 0, 1.0 };
    GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    GLUquadric *qd;
    qd = gluNewQuadric();
    gluQuadricTexture(qd, TRUE);
    gluCylinder(qd,3,3,7,100,100);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, ID[5]);
    glEnable(GL_TEXTURE_2D);

    ///tree leaf1
    glPushMatrix();
    glTranslatef(-8,14,34);
    glScalef(2,3.5,2);
    glRotatef(-90,1,0,0);

    GLfloat no_mat1[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient1[] = { 0, 0.15, 0.000, 1.0 };
    GLfloat mat_diffuse1[] = {0, 0.2, 0.000, 1.0 };
    GLfloat mat_specular1[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess1[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular1);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess1);

    cone();
    glPopMatrix();

    ///tree leaf2
    glPushMatrix();
    glTranslatef(-8,18,34);
    glScalef(2,3.5,2);
    glRotatef(-90,1,0,0);

    GLfloat no_mat2[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient2[] = { 0, 0.15, 0.000, 1.0 };
    GLfloat mat_diffuse2[] = {0, 0.2, 0.000, 1.0 };
    GLfloat mat_specular2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess2[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient2);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular2);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess2);

    cone();
    glPopMatrix();

    ///tree leaf3
    glPushMatrix();
    glTranslatef(-8,22,34);
    glScalef(2,3,2);
    glRotatef(-90,1,0,0);

    GLfloat no_mat3[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient3[] = { 0, 0.15, 0.000, 1.0 };
    GLfloat mat_diffuse3[] = {0, 0.2, 0.000, 1.0 };
    GLfloat mat_specular3[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess3[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient3);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse3);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular3);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess3);

    cone();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

}
void tree2()
{
    ///tree2 body
    //glColor3f( 	0.545, 0.070, 0.070);
    glBindTexture(GL_TEXTURE_2D, ID[4]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(-8,20,34);
    glScalef(0.2,3.8,0.3);
    glRotatef(90,1,0,0);
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.0, 0.0, 0, 1.0 };
    GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    GLUquadric *qd;
    qd = gluNewQuadric();
    gluQuadricTexture(qd, TRUE);
    gluCylinder(qd,3,3,7,100,100);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, ID[5]);
    glEnable(GL_TEXTURE_2D);

    ///tree2 leaf1
    glPushMatrix();
    glTranslatef(-8,14,34);
    glScalef(2,3.5,2);
    glRotatef(-90,1,0,0);

    GLfloat no_mat1[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient1[] = { 0, 0.4, 0.000, 1.0 };
    GLfloat mat_diffuse1[] = {0, 0.6, 0.000, 1.0 };
    GLfloat mat_specular1[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess1[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular1);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess1);

    cone();
    glPopMatrix();

    ///tree2 leaf2
    glPushMatrix();
    glTranslatef(-8,18,34);
    glScalef(2,3.5,2);
    glRotatef(-90,1,0,0);

    GLfloat no_mat2[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient2[] = { 0, 0.4, 0.000, 1.0 };
    GLfloat mat_diffuse2[] = {0, 0.6, 0.000, 1.0 };
    GLfloat mat_specular2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess2[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient2);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular2);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess2);

    cone();
    glPopMatrix();

    ///tree2 leaf3
    glPushMatrix();
    glTranslatef(-8,22,34);
    glScalef(2,3,2);
    glRotatef(-90,1,0,0);

    GLfloat no_mat3[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient3[] = { 0, 0.4, 0.000, 1.0 };
    GLfloat mat_diffuse3[] = {0, 0.60, 0.000, 1.0 };
    GLfloat mat_specular3[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess3[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient3);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse3);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular3);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess3);

    cone();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

}

void bark()
{
    glBindTexture(GL_TEXTURE_2D, ID[4]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(-8,12,34);
    glScalef(0.2,4,0.3);
    glRotatef(90,1,0,0);
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.0, 0.0, 0, 1.0 };
    GLfloat mat_diffuse[] = { 1, 1, 1, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    GLUquadric *qd;
    qd = gluNewQuadric();
    gluQuadricTexture(qd, TRUE);
    gluCylinder(qd,10,10,7,100,100);

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}



void treem1()
{
    glPushMatrix();
    glTranslatef(-140,14,-80);
    glScalef(5,5,5);
    tree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-178,70,55);
    glRotatef(30,0,0,1);
    glScalef(1,0.5,1);
    bark();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-168,70,55);
    glRotatef(-30,0,0,1);
    glScalef(1,0.5,1);
    bark();
    glPopMatrix();
}
void treem2()
{
    glPushMatrix();
    glTranslatef(-140,14,-80);
    glScalef(5,5,5);
    tree2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-178,70,55);
    glRotatef(30,0,0,1);
    glScalef(1,0.5,1);
    bark();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-168,70,55);
    glRotatef(-30,0,0,1);
    glScalef(1,0.5,1);
    bark();
    glPopMatrix();
}

void treess()
{
    glPushMatrix();
    glTranslatef(-150,-13,255);
    glScalef(0.4,0.4,0.4);
    treem1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-140,-13,240);
    glScalef(0.4,0.4,0.4);
    treem2();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(145,-13,255);
    glScalef(0.4,0.4,0.4);
    treem1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(155,-13,240);
    glScalef(0.4,0.4,0.4);
    treem2();
    glPopMatrix();

}
void drawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);

    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);glTexCoord2f(0,1);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);glTexCoord2f(1,1);
    }
    glEnd();
}

void drawCube2(GLfloat difX, GLfloat difY, GLfloat difZ)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5*difX, 0.5*difY, 0.5*difZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);

    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);glTexCoord2f(0,1);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);glTexCoord2f(1,1);
    }
    glEnd();
}

void siri()
{
    int a=0,b=-4,c=-4.99,d=3.7;
    for (int i=0;i<16;i++)
    {
    glPushMatrix();
    glRotatef(180,0,1,0);
    glScalef(13, 4.5, 4);
    glTranslatef(-4.53,c,d);


    if(i%2==0)
        drawCube1(0.4, .4, 0.4, 0.2, .2, 0.2);
    else
         drawCube1(0.25, .25, 0.25, 0.12, .12, 0.12);
    glPopMatrix();
    a+= 1; b+=5; c+=1.2; d+=3;
    }
}
void siri_bal()
{

    glPushMatrix();

    glTranslatef(19.9,72,-254);
    glScalef(13, 0.5, 20.5);


    GLfloat no_mat56[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient56[] = { 0.05,0.05,0.05, 0.5 };
    GLfloat mat_diffuse56[] = { 0.1,.1,.1, 1.0 };
    GLfloat mat_specular56[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess56[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient56);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse56);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular56);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess56);

    drawCube();
    glPopMatrix();

}


void chair()
{
    glTranslatef(0, -0.4, 0);

    //seat part
    glPushMatrix();
    glScalef(0.5, 0.05, 0.5);
    drawCube1(0.2,0.2,0.2,  0.2,0.2,0.2);
    glPopMatrix();

    //seat left back
    glPushMatrix();
    glTranslatef(0, -1.5, 0);
    glScalef(0.05, 1.4, 0.05);
    drawCube1(0.1,0.1,0.1,  0.1,0.1,0.1);
    glPopMatrix();

    //seat right back
    glPushMatrix();
    glTranslatef(1.35, -1.5, 0);
    glScalef(0.05, 1.4, 0.05);
     drawCube1(0.1,0.1,0.1,  0.1,0.1,0.1);
    glPopMatrix();

    //seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 2, 0);
    glScalef(0.5, 0.05, 0.05);
    drawCube1(0.1,0.1,0.1,  0.1,0.1,0.1);
    glPopMatrix();

    //seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 1.5 , 0);
    glScalef(0.5, 0.05, 0.05);
    drawCube1(0.1,0.1,0.1,  0.1,0.1,0.1);
    glPopMatrix();

    //seat horizontal up back
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glScalef(0.5, 0.05, 0.05);
     drawCube1(0.1,0.1,0.1,  0.1,0.1,0.1);
    glPopMatrix();

    //seat left front leg
    glPushMatrix();
    glTranslatef(0, -1.5, 1.3);
    glScalef(0.05, .55, 0.05);
     drawCube1(0.1,0.1,0.1,  0.1,0.1,0.1);
    glPopMatrix();

    //seat right front leg
    glPushMatrix();
    glTranslatef(1.35, -1.5, 1.3);
    glScalef(0.05, .55, 0.05);
    drawCube1(0.1,0.1,0.1,  0.1,0.1,0.1);
    glPopMatrix();

}

void tablem()
{
    //table
    glPushMatrix();
    glScalef(4, 0.3, 4);
     drawSphere(0.45,0.027,0.08,  0.45,0.027,0.08);
    glPopMatrix();

    //stand
    glPushMatrix();
    glScalef(0.1, -1, -0.1);
    drawCube1(0.8,0.8,0.8, 0.9,0.9,0.9);
    glPopMatrix();

    //stand bottom
    glPushMatrix();
    glTranslatef(0.2, -2.8, -0.2);
    glScalef(1, 0.2, 1);
    drawSphere(0.45,0.027,0.08,  0.45,0.027,0.08);
    glPopMatrix();
}


void tissuebox()
{
    glPushMatrix();
    glTranslatef(0, .3, 0);
    glScalef(0.4, 0.2, 0.25);
    drawCube1(0.4,0.2,0,  0.4,0.2,0);
    glPopMatrix();
}
void tissue()
{
    glPushMatrix();
    glRotatef(45, 0, 0, 1);
    glTranslatef(0.15, .1, .1);
    glScalef(0.25, 0.25, 0.01);
    drawCube1(1,1,1,  1,1,1);
    glPopMatrix();
}


void diningSet()
{
    glPushMatrix();
    glTranslatef(0, -16, 0);
    tablem();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6, -16, 0.2);
    tissuebox();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -15.8, 0.5);
    tissue();
    glPopMatrix();

    for(int i = 0; i <= 360; i+=72)
     {
         glPushMatrix();
         glRotatef(i, 0, 1, 0);
         glTranslatef(0, -17, -4);
         chair();
         glPopMatrix();
     }
}


void foodcort()
{   glTranslatef(-175, -26.5, -25);
    for(float i=-4; i<=25; i+=12)//32
    {
        for(float j=2; j<=18; j+=12)//26
        {
            glPushMatrix();
            glScalef(6.5,8,7);
            glTranslatef(i, 20, j);

            diningSet();
            glPopMatrix();
        }
    }
}
void path()
{
    glBindTexture(GL_TEXTURE_2D, ID[6]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(20,-20,-20);
    glScalef(13, 0.5, 110);


    GLfloat no_mat56[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient56[] = { 0.4,0.25,0, 0.5 };
    GLfloat mat_diffuse56[] = { 0.8,0.4,0, 1.0 };
    GLfloat mat_specular56[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess56[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient56);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse56);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular56);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess56);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void pools()
{

    ///back
    glBindTexture(GL_TEXTURE_2D, ID[20]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(270,6.5,-255);

    glScalef(55, 8, 3.5);

    GLfloat no_matc1[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientc1[] = { 0.5, 0.5, 0.5, 0.5 };
    GLfloat mat_diffusec1[] = { 1, 1, 1, 1.0 };
    GLfloat mat_specularc1[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessc1[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientc1);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusec1);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularc1);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessc1);

    drawCube();
    glPopMatrix();


    ///left
    glPushMatrix();

    glTranslatef(270,6.5,-255);
    glScalef(3, 8, 135);

    GLfloat no_matc1l[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientc1l[] = { 0.5, 0.5, 0.5, 0.5 };
    GLfloat mat_diffusec1l[] = { 1, 1, 1, 1.0 };
    GLfloat mat_specularc1l[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessc1l[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientc1l);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusec1l);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularc1l);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessc1l);

    drawCube();
    glPopMatrix();


    ///right
    glPushMatrix();

    glTranslatef(426,6.5,-255);
    glScalef(3, 8, 135);

    GLfloat no_matc1lr[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientc1lr[] = { 0.5, 0.5, 0.5, 0.5 };
    GLfloat mat_diffusec1lr[] = { 1, 1, 1, 1.0 };
    GLfloat mat_specularc1lr[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessc1lr[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientc1lr);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusec1lr);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularc1lr);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessc1lr);

    drawCube();
    glPopMatrix();


    ///front
    glPushMatrix();

    glTranslatef(270,6.5,150);
    glScalef(55, 8, 3.5);

    GLfloat no_matc1lf[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientc1lf[] = { 0.5, 0.5, 0.5, 0.5 };
    GLfloat mat_diffusec1lf[] = { 1, 1, 1, 1.0 };
    GLfloat mat_specularc1lf[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessc1lf[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientc1lf);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusec1lf);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularc1lf);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessc1lf);

    drawCube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);



}
void water()
{
    if(pop==false)
    {glBindTexture(GL_TEXTURE_2D, ID[28]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(279,6.5,-250);
    glScalef(49, 7, 133);

    GLfloat no_mat56[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient56[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffuse56[] = { 1,1,1, 1.0 };
    GLfloat mat_specular56[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess56[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient56);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse56);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular56);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess56);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);}
    else

    {glBindTexture(GL_TEXTURE_2D, ID[28]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(279,6.5,-247);
    glScalef(49, 7, 133);

    GLfloat no_mat56[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient56[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffuse56[] = { 1,1,1, 1.0 };
    GLfloat mat_specular56[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess56[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient56);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse56);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular56);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess56);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);}
}


void building()
{

    ///level1 floor

    glBindTexture(GL_TEXTURE_2D, ID[7]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(-260,-20,-250);
    glScalef(93.3, 0.7, 128);

    GLfloat no_mat56[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient56[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffuse56[] = { 1,1,1, 1.0 };
    GLfloat mat_specular56[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess56[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient56);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse56);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular56);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess56);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///level1 ceiling

    glBindTexture(GL_TEXTURE_2D, ID[20]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(-260,73.46,-250);
    glScalef(93.3, 0.8, 128);

    GLfloat no_matc[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientc[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusec[] = { 1,0,0, 1.0 };
    GLfloat mat_specularc[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessc[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientc);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusec);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularc);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessc);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    ///level1 side wall1
    glBindTexture(GL_TEXTURE_2D, ID[19]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(19.3,-20,-250);
    glScalef(0.2, 31.1, 81);

    GLfloat no_matcs[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcs[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusecs[] = { 1,1,1, 1.0 };
    GLfloat mat_specularcs[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscs[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcs);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecs);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcs);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscs);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///level1 side wall2
    glBindTexture(GL_TEXTURE_2D, ID[15]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(58.8,-20,-250);
    glScalef(0.2, 46, 81);

    GLfloat no_matcs2[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcs2[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusecs2[] = { 1,1,1, 1.0 };
    GLfloat mat_specularcs2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscs2[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcs2);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecs2);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcs2);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscs2);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}


void building2()
{
    glBindTexture(GL_TEXTURE_2D, ID[18]);
    glEnable(GL_TEXTURE_2D);
    ///level2 floor

    glPushMatrix();
    glTranslatef(-260,76,-250);

    glScalef(93.3, 0.7, 128);


    GLfloat no_mat56[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient56[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffuse56[] = { 1,1,1, 1.0 };
    GLfloat mat_specular56[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess56[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient56);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse56);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular56);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess56);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    ///level2 ceiling


    glPushMatrix();

    glTranslatef(-260,169.46,-250);
    glScalef(93.3, 0.7, 128);

    GLfloat no_matc[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientc[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusec[] = { 1,1,1, 1.0 };
    GLfloat mat_specularc[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessc[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientc);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusec);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularc);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessc);

    drawCube();
    glPopMatrix();


  //  glBindTexture(GL_TEXTURE_2D, ID[23]);
   // glEnable(GL_TEXTURE_2D);

    ///level2 side wall left

    glPushMatrix();

    glTranslatef(-260,78,-250);
    glScalef(0.2, 30.5, 128);

    GLfloat no_matcs2[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcs2[] = { 0.5,0.15,0.15, 0.5 };
    GLfloat mat_diffusecs2[] = { 1,0.3,0.3, 1.0 };
    GLfloat mat_specularcs2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscs2[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcs2);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecs2);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcs2);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscs2);

    drawCube();
    glPopMatrix();


    ///level2 side wall right

    glPushMatrix();

    glTranslatef(19.3,78,-188.9);
    glScalef(0.2, 30.5, 107.6);

    GLfloat no_matcs2a[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcs2a[] = { 0.5,0.15,0.15, 0.5 };
    GLfloat mat_diffusecs2a[] = { 1,0.3,0.3, 1.0 };
    GLfloat mat_specularcs2a[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscs2a[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcs2a);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecs2a);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcs2a);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscs2a);

    drawCube();
    glPopMatrix();

   //glDisable(GL_TEXTURE_2D);





    ///level2 wall front
   glBindTexture(GL_TEXTURE_2D, ID[21]);
   glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(-260,76,128);
    glScalef(93.3, 31.1, 0.2);

    GLfloat no_matcsf[] = { 0.0, 0.0, 0.0, 1 };
    GLfloat mat_ambientcsf[] = { 0.5,0.5,0.5, 0 };
    GLfloat mat_diffusecsf[] = { 1,1,1, 0};
    GLfloat mat_specularcsf[] = { 1.0, 1.0, 1.0, 0};
    GLfloat mat_shininesscsf[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcsf);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecsf);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcsf);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscsf);

    drawCube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);


    ///level2 wall back
    glBindTexture(GL_TEXTURE_2D, ID[19]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-260,76,-250);
    glScalef(93.3, 31.1, 0.2);

    GLfloat no_matcs222[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcs222[] = { 0.5,0,0, 0.5 };
    GLfloat mat_diffusecs222[] = { 1,0,0, 1.0 };
    GLfloat mat_specularcs222[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscs222[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcs222);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecs222);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcs222);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscs222);

    drawCube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);





    ///level2 pillar0

    glBindTexture(GL_TEXTURE_2D, ID[26]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-260,78,128);
    glScalef(3.5, 30.5, 2);

    GLfloat no_matcsp0[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcsp0[] = { 0.15,0.15,0.15, 0.5 };
    GLfloat mat_diffusecsp0[] = { 0.3,0.3,0.3, 1.0 };
    GLfloat mat_specularcsp0[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscsp0[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcsp0);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecsp0);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcsp0);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscsp0);

    drawCube();
    glPopMatrix();


    ///level2 pillar1

    glPushMatrix();

    glTranslatef(-220,78,128);
    glScalef(3.5, 30.5, 2);

    GLfloat no_matcsp[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcsp[] = { 0.15,0.15,0.15, 0.5 };
    GLfloat mat_diffusecsp[] = { 0.3,0.3,0.3, 1.0 };
    GLfloat mat_specularcsp[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscsp[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcsp);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecsp);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcsp);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscsp);

    drawCube();
    glPopMatrix();


    ///level2 pillar2

    glPushMatrix();

    glTranslatef(-175,78,128);
    glScalef(3.5, 30.5, 2);

    GLfloat no_matcsp2[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcsp2[] = { 0.15,0.15,0.15, 0.5 };
    GLfloat mat_diffusecsp2[] = { 0.3,0.3,0.3, 1.0 };
    GLfloat mat_specularcsp2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscsp2[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcsp2);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecsp2);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcsp2);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscsp2);

    drawCube();
    glPopMatrix();

   /*   ///level2 pillar3

    glPushMatrix();

    glTranslatef(-125,78,128);
    glScalef(3.5, 30.5, 2);

    GLfloat no_matcsp3[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcsp3[] = { 0.15,0.15,0.15, 0.5 };
    GLfloat mat_diffusecsp3[] = { 0.3,0.3,0.3, 1.0 };
    GLfloat mat_specularcsp3[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscsp3[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcsp3);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecsp3);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcsp3);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscsp3);

    drawCube();
    glPopMatrix();

    */
      ///level2 pillar4

    glPushMatrix();

    glTranslatef(-75,78,128);
    glScalef(3.5, 30.5, 2);

    GLfloat no_matcsp4[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcsp4[] = { 0.15,0.15,0.15, 0.5 };
    GLfloat mat_diffusecsp4[] = { 0.3,0.3,0.3, 1.0 };
    GLfloat mat_specularcsp4[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscsp4[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcsp4);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecsp4);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcsp4);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscsp4);

    drawCube();
    glPopMatrix();

    ///level2 pillar5

    glPushMatrix();

    glTranslatef(-30,78,128);
    glScalef(3.5, 30.5, 2);

    GLfloat no_matcsp5[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcsp5[] = { 0.15,0.15,0.15, 0.5 };
    GLfloat mat_diffusecsp5[] = { 0.3,0.3,0.3, 1.0 };
    GLfloat mat_specularcsp5[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscsp5[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcsp5);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecsp5);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcsp5);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscsp5);

    drawCube();
    glPopMatrix();

      ///level2 pillar6

    glPushMatrix();

    glTranslatef(10,78,128);
    glScalef(3.5, 30.5, 2);

    GLfloat no_matcsp6[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcsp6[] = { 0.15,0.15,0.15, 0.5 };
    GLfloat mat_diffusecsp6[] = { 0.3,0.3,0.3, 1.0 };
    GLfloat mat_specularcsp6[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscsp6[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcsp6);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecsp6);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcsp6);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscsp6);

    drawCube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

}



void doorl2()
{
    glBindTexture(GL_TEXTURE_2D, ID[25]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(193.9,104.7,-165);
    glScalef(0.2, 30.5, 19.7);
    glRotatef(90,0,1,0);


    GLfloat no_matbd[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientbd[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusebd[] = { 1,1,1, 1.0 };
    GLfloat mat_specularbd[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessbd[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientbd);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusebd);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularbd);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessbd);

    drawCube();
    glPopMatrix();
     glDisable(GL_TEXTURE_2D);


}
void opendoor()
{
    if (dooron == true)
    {
        doorX -= 0.5; ///////speed
    }
    if (doorX<-60)
    {
        dooron = false;
    }
    if(dooroff==true)
    {
        doorX += 0.5;
    }
    if(doorX>-0.5)
    {
        dooroff=false;
    }
    glPushMatrix();
    glTranslatef( 0,0,-doorX);
    doorl2();
    glPopMatrix();
}



  void photoleft()
  {

    glBindTexture(GL_TEXTURE_2D, ID[9]);
    glEnable(GL_TEXTURE_2D);
    ///fenchleft
    glPushMatrix();

    glTranslatef(0,4,0);


    //1
    glPushMatrix();
    glTranslatef(88,5,-200);
    glScalef(2, 27, 0.2);
    drawCube2(0.7,0.29,0);
    glPopMatrix();
    //2
    glPushMatrix();
    glTranslatef(82,5,-200);
    glScalef(2, 23, 0.2);
    drawCube2(1,0.7,0.4);
    glPopMatrix();
    //3
    glPushMatrix();
    glTranslatef(76,5,-200);
    glScalef(2, 19, 0.2);
    drawCube2(0.7,0.29,0);
    glPopMatrix();
    //4
    glPushMatrix();
    glTranslatef(70,5,-200);
    glScalef(2, 15, 0.2);
    drawCube2(1,0.7,0.4);
    glPopMatrix();
    //5
    glPushMatrix();
    glTranslatef(64,5,-200);
    glScalef(2, 11, 0.2);
    drawCube2(0.7,0.29,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

     glPopMatrix();
  }



  void photoright()
  {

    ///fenchleft

    glPushMatrix();

    glTranslatef(232.7,0,-399);
    glRotatef(180,0,1,0);


    photoleft();
    glPopMatrix();

  }


void photo()
{
    photoleft();
    photoright();

    ///back wall photobooth
    glBindTexture(GL_TEXTURE_2D, ID[10]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(94,8.65,-200);
    glScalef(14.9, 30.4, 0.2);

    GLfloat no_matbw[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientbw[] = { 0.44,0.25,0.105, 0.5 };
    GLfloat mat_diffusebw[] = {0.87,0.47,0.21, 1.0 };
    GLfloat mat_specularbw[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessbw[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientbw);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusebw);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularbw);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessbw);

    drawCube();
    glPopMatrix();
   glDisable(GL_TEXTURE_2D);




   ///frame1
    glBindTexture(GL_TEXTURE_2D, ID[11]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(100,65,-195);
    glScalef(4.5, 8, 0.2);


    GLfloat no_matbw1[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientbw1[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusebw1[] = {1,1,1, 1.0 };
    GLfloat mat_specularbw1[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessbw1[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientbw1);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusebw1);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularbw1);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessbw1);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///frame2
    glBindTexture(GL_TEXTURE_2D, ID[12]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(120,47,-195);
    glScalef(4.5, 8, 0.2);


    GLfloat no_matbw11[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientbw11[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusebw11[] = {1,1,1, 1.0 };
    GLfloat mat_specularbw11[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessbw11[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientbw11);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusebw11);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularbw11);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessbw11);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

     ///frame3
    glBindTexture(GL_TEXTURE_2D, ID[13]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(101,30,-195);
    glScalef(4.5, 8, 0.2);


    GLfloat no_matbw111[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientbw111[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusebw111[] = {1,1,1, 1.0 };
    GLfloat mat_specularbw111[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessbw111[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientbw111);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusebw111);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularbw111);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessbw111);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void pillar()
{


    ///pillar bottom
    glBindTexture(GL_TEXTURE_2D, ID[8]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(25,-16,-53);
    glScalef(5, 2.2, 5);
    glRotatef(90,1,0,0);

    GLfloat no_mat502[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient502[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffuse502[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular502[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess502[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient502);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse502);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular502);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess502);

    GLUquadricObj *ob = gluNewQuadric();
    gluQuadricTexture(ob, TRUE);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///pillar top
    glBindTexture(GL_TEXTURE_2D, ID[8]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(32,69,-47);
    glScalef(1, 1.2, 1);
    glRotatef(90,1,0,0);

    GLfloat no_mat50[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient50[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffuse50[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular50[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess50[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient50);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse50);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular50);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess50);

    GLUquadricObj *ob1 = gluNewQuadric();
    gluQuadricTexture(ob1, TRUE);
    gluCylinder(ob1,6,3,10,120,120);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///pillar middle
    glBindTexture(GL_TEXTURE_2D, ID[8]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(32,58,-47);
    glScalef(1, 1.75, 1);
    glRotatef(90,1,0,0);

    GLfloat no_mat5[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient5[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffuse5[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular5[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess5[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient5);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse5);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular5);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess5);

    GLUquadricObj *ob2 = gluNewQuadric();
    gluQuadricTexture(ob2, TRUE);
    gluCylinder(ob2,3,3,46,120,120);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



}
void pillars()
{

    ///left front
    glPushMatrix();
    glTranslatef(-100,31.2,185);
    pillar();
    glPopMatrix();

    ///left back
    glPushMatrix();
    glTranslatef(-100,31.2,-120);
    pillar();
    glPopMatrix();
    ///right back
    glPushMatrix();
    glTranslatef(145,31.2,-120);
    pillar();
    glPopMatrix();
    ///right front
    glPushMatrix();
    glTranslatef(145,31.2,185);
    pillar();
    glPopMatrix();
}

 void pc()
 {
    glPushMatrix();
    glTranslatef(5,3.9,10);

     //laptop
    glPushMatrix();
    glTranslatef(10,53,-120);
    glScalef(5.1, 4.7, 0.5);
     drawCube1(0.20,0.20,0.20, 0.1,0.1,0.1);
    glPopMatrix();

    //laptop backside
    glPushMatrix();
    glTranslatef(11.8,55.3,-119);
    glScalef(4, 3.1, 0.2);
    drawCube1(0.46,0.44,0.44, 0.22,0.22,0.22);
    glPopMatrix();

    //stand
    glPushMatrix();
    glTranslatef(17.3,45,-118);
    glScalef(0.37, 5,0.33);
    drawCube1(0.14,0.14,0.14, 0.07,0.07,0.07);
    glPopMatrix();

    //stand bottom
    glPushMatrix();
    glTranslatef(18.1,44.5,-116.7);
    glScalef(2.5, 0.7, 2.5);
    drawSphere(0.14,0.14,0.14, 0.07,0.07,0.07);
    glPopMatrix();

    glPopMatrix();

 }

 void refrigerator()
{

    glPushMatrix();
    glTranslatef(61,30,-195);
    glScalef(1.5, 1.4, 1.2);

    ///back


    glPushMatrix();

    glTranslatef(-18,30,6);
    glScalef(6, 15, 2);
    glRotatef(90,1,0,0);
    GLfloat no_mattte[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttte[] = { 0.19,0.15,0.15, 0.5 };
    GLfloat mat_diffusettte[] = { 0.38,0.3,0.3, 1.0 };
    GLfloat mat_specularttte[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessttte[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttte);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettte);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttte);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttte);

    drawCube();

    glPopMatrix();

   ///front left
    glBindTexture(GL_TEXTURE_2D, ID[15]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-18,30,12);
    glScalef(3, 15, 0.2);
    glRotatef(90,1,0,0);
    GLfloat no_mattt[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttt[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusettt[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specularttt[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessttt[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttt);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettt);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttt);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttt);

    drawCube();

    glPopMatrix();

    ///front right


    glPushMatrix();

    glTranslatef(-9,30,12);
    glScalef(3, 15, 0.2);
    glRotatef(90,1,0,0);
    GLfloat no_matt[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientt[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusett[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_speculartt[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesstt[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientt);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusett);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_speculartt);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesstt);

    drawCube();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    ///handle left


    glPushMatrix();

    glTranslatef(-10,15,13.5);
    glScalef(1, 1, 1);
    glRotatef(90,1,0,0);

    GLfloat no_mat502[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient502[] = { 0.1,0.1,0.1, 0.5 };
    GLfloat mat_diffuse502[] = { 0.2,0.2,0.2, 1.0 };
    GLfloat mat_specular502[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess502[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient502);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse502);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular502);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess502);

    GLUquadricObj *ob = gluNewQuadric();
    gluQuadricTexture(ob, TRUE);
    gluCylinder(ob,0.4,0.4,10,120,120);

    glPopMatrix();
     glDisable(GL_TEXTURE_2D);

     ///handle right


    glPushMatrix();

    glTranslatef(-8,15,13.5);
    glScalef(1, 1, 1);
    glRotatef(90,1,0,0);

    GLfloat no_mat50[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient50[] = { 0.1,0.1,0.1, 0.5  };
    GLfloat mat_diffuse50[] = {0.2,0.2,0.2, 1.0 };
    GLfloat mat_specular50[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess50[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient50);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse50);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular50);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess50);

    GLUquadricObj *obs = gluNewQuadric();
    gluQuadricTexture(obs, TRUE);
    gluCylinder(obs,0.4,0.4,10,120,120);

    glPopMatrix();


    glPopMatrix();

}

void recept()
{
    glBindTexture(GL_TEXTURE_2D, ID[20]);
    glEnable(GL_TEXTURE_2D);

    ///kitchen side wall1

    glPushMatrix();
    glTranslatef(0,8.65,-200);
    glScalef(0.2, 30.4, 36);

    GLfloat no_matcs[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcs[] = { 0.33,0,0, 0.5 };
    GLfloat mat_diffusecs[] = { 0.44,0,0, 1.0 };
    GLfloat mat_specularcs[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscs[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcs);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecs);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcs);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscs);

    drawCube();
    glPopMatrix();


    ///kitchen side wall2

    glPushMatrix();

    glTranslatef(63.5,8.65,-200);
    glScalef(0.2, 30.4, 36);

    GLfloat no_matcs2[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcs2[] = { 0.39,0,0, 0.5 };
    GLfloat mat_diffusecs2[] = { 0.78,0,0, 1.0 };
    GLfloat mat_specularcs2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscs2[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcs2);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecs2);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcs2);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscs2);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    ///back wall kichen
    glBindTexture(GL_TEXTURE_2D, ID[14]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    //glViewport(0, 0, 400, 400);
    glTranslatef(0,8.65,-200);
    glScalef(21.4, 30.4, 0.2);

    GLfloat no_matbw[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientbw[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusebw[] = { 1,1,1, 1.0 };
    GLfloat mat_specularbw[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessbw[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientbw);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusebw);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularbw);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessbw);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    ///kitchen base
    glBindTexture(GL_TEXTURE_2D, ID[16]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(1,8.65,-120);
    glScalef(16, 13, 8);

    GLfloat no_matcsb[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcsb[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusecsb[] = { 1,1,1, 1.0 };
    GLfloat mat_specularcsb[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscsb[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcsb);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecsb);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcsb);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscsb);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}

void washrm()
{

    glPushMatrix();

    glTranslatef(0,36.5,-295);
    glScalef(2.1, 1.98, 13);

    ///back

    glBindTexture(GL_TEXTURE_2D, ID[18]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(-18,27,8);
    glScalef(6, 13.7, 1.8);
    glRotatef(90,1,0,0);
    GLfloat no_mattte[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttte[] = { 0.3,0.4,0.5, 0.5 };
    GLfloat mat_diffusettte[] = { 0.6,0.8,1, 1.0 };
    GLfloat mat_specularttte[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessttte[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttte);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettte);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttte);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttte);

    drawCube();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    ///front
    glBindTexture(GL_TEXTURE_2D, ID[17]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(-12,18,13.5);
    glScalef(1.5, 4, 0);
    glRotatef(90,1,0,0);
    GLfloat no_mattt[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttt[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusettt[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specularttt[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessttt[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttt);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettt);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttt);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttt);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///handle


    glPushMatrix();

    glTranslatef(-3,10,13.5);
    glScalef(0.7, 0.7, 0.15);
    glRotatef(90,1,0,0);

    GLfloat no_mat50[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient50[] = { 0,0,0.225, 0.5  };
    GLfloat mat_diffuse50[] = {0,0,0.45, 1.0 };
    GLfloat mat_specular50[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess50[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient50);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse50);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular50);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess50);

    GLUquadricObj *obs = gluNewQuadric();
    gluQuadricTexture(obs, TRUE);
    gluCylinder(obs,0.4,0.4,10,120,120);

    glPopMatrix();



    glPopMatrix();

}


void sofan()

{
    glBindTexture(GL_TEXTURE_2D, ID[24]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-70,124.5,-150);
    glScalef(6,7.3,7);
    //sofa1_b

    glPushMatrix();
    glScalef(1.8,1,1.5);
    glTranslatef(2,-2.5,-4);
    drawCube2(0.2,0.2,0.2);
    glPopMatrix();

    //sofa1_m_h
    glPushMatrix();

    glScalef(1.6,1,0.5);
    glTranslatef(2.43,0.5,-12);
    drawCube2(0.4,0.4,0.4);
    glPopMatrix();

    //sofa1_s_h_1

    glPushMatrix();
    glScalef(0.25,0.6,1.3);
    glTranslatef(14.5,0.8,-4.62);
    drawCube2(0.3,0.3,0.3);
    glPopMatrix();

    //sofa1_s_h_2

    glPushMatrix();
    glScalef(0.25,0.6,1.3);
    glTranslatef(33,.8,-4.62);
    drawCube2(0.3,0.3,0.3);
    glPopMatrix();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);


}

void table_n()
{

    glPushMatrix();
    glTranslatef(-68,136,-135);
    glScalef(14,8.5,7);
    ///table_upper

    glPushMatrix();
    glScalef(1.5,0.1,2.1);
    glTranslatef(1.4,-1,-0.1);
    drawCube2(0.5,0,0);
    glPopMatrix();

    ///left_leg

    glPushMatrix();
    glScalef(.15, 1, .3);
    glTranslatef(18,-3.12,9);
    drawCube2(0.05,0.05,0.05);
    glPopMatrix();

    ///right_leg

    glPushMatrix();
    glScalef(.15, 1, .3);
    glTranslatef(37,-3.12,9);
    drawCube2(0.05,0.05,0.05);
    glPopMatrix();

    glPopMatrix();

}



void sofas()
{
    glPushMatrix();
    table_n();
    glPopMatrix();

    glPushMatrix();
    sofan();
    glPopMatrix();

    ///sofa right

    glPushMatrix();
    glTranslatef(45,0,0);
    sofan();
    glPopMatrix();

   ///sofa back

    glPushMatrix();
    glTranslatef(-62,-1.7,-240);
    glRotatef(180,0,1,0);
    sofan();
    glPopMatrix();

    ///sofa back2

    glPushMatrix();
    glTranslatef(-19,-1.7,-240);
    glRotatef(180,0,1,0);
    sofan();
    glPopMatrix();
}



void sofass()
{
    glPushMatrix();
    sofas();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(120,0,0);
    sofas();

    glPopMatrix();
}




void sofa1()
{
    //sofa top
    glBindTexture(GL_TEXTURE_2D, ID[22]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(-140,65.7,-55);
    glScalef(2, 6.3, 12);

    GLfloat no_matlf[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientlf[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffuself[] = { 1,1,1, 1.0 };
    GLfloat mat_specularlf[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesslf[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientlf);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuself);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularlf);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesslf);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //sofa bottom
    glBindTexture(GL_TEXTURE_2D, ID[22]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(-140,51,-55);
    glScalef(5, 5, 12);

    GLfloat no_matl[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientl[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusel[] = { 1.0,1,1, 1.0 };
    GLfloat mat_specularl[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessl[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientl);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusel);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularl);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessl);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}
void sofa2()
{
   //sofa top
    glBindTexture(GL_TEXTURE_2D, ID[22]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(-95,65.7,-55);
    glScalef(2, 6.3, 12);

    GLfloat no_matlf[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientlf[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffuself[] = { 1.0,1,1, 1.0 };
    GLfloat mat_specularlf[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesslf[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientlf);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuself);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularlf);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesslf);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //sofa bottom
    glBindTexture(GL_TEXTURE_2D, ID[22]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-104,51,-55);
    glScalef(5, 5, 12);

    GLfloat no_matl[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientl[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusel[] = { 1.0,1,1, 1.0 };
    GLfloat mat_specularl[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessl[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientl);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusel);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularl);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessl);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}


void table()
{
    glPushMatrix();
    glTranslatef(-122,69,-2);
    glScalef(2.7, 6, 7);
    glRotatef(90,0,1,0);


    ///table_upper

    glPushMatrix();
    glScalef(1.5,0.1,2.1);
    glTranslatef(1.4,-1,-0.1);
    drawCube2(0.38,0.38,0.38);
    glPopMatrix();




    ///left_leg

    glPushMatrix();
    glScalef(.15, 1, .3);
    glTranslatef(18,-3.12,9);
    drawCube2(0.1,0.1,0.1);
    glPopMatrix();

    ///right_leg

    glPushMatrix();
    glScalef(.15, 1, .3);
    glTranslatef(37,-3.12,9);
    drawCube2(0.1,0.1,0.1);
    glPopMatrix();



    glPopMatrix();

}
void sofaset()
{
    glPushMatrix();
    glTranslatef(300,35,140);
    glScalef(1.4, 1.4, 1.4);
    table();
    sofa1();
    sofa2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(210,35,140);
    glScalef(1.4, 1.4, 1.4);
    table();
    sofa1();
    sofa2();
    glPopMatrix();



}

void bar()
{
    /// base
    glBindTexture(GL_TEXTURE_2D, ID[16]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-84,104.8,30);
    glScalef(6.5, 11, 28);

    GLfloat no_matcsb[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambientcsb[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusecsb[] = { 1,1,1, 1.0 };
    GLfloat mat_specularcsb[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininesscsb[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambientcsb);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusecsb);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularcsb);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininesscsb);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void drawSphere1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere (0.44, 16, 16);
}

void tool()
{
    glPushMatrix();
    glTranslatef(-23, 130, 100);
    glScalef(3, 3, 3);
    //tool
    glPushMatrix();
    glTranslatef(-11, -.5, 3);
    glScalef(4, 1.5, 4);
    drawSphere1(0.45,0.027,0.08,  0.45,0.027,0.08);
    glPopMatrix();

    //toolstand
    glPushMatrix();
    glTranslatef(-11.15, -7.65, 3);
    glScalef(0.15, 2.2, 0.15);
    drawCube1(0.2,0.2,0.2, 0.1,0.1,0.1);
    glPopMatrix();

    //toolstand bottom
    glPushMatrix();
    glTranslatef(-11, -8, 3);
    glScalef(1, 0.4, 1);
    drawSphere(0.45,0.027,0.08,  0.45,0.027,0.08);
    glPopMatrix();

    glPopMatrix();
}


void tools()
{
    glPushMatrix();
    glTranslatef(0,0,3);
    tool();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-20);
    tool();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-43);
    tool();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-66);
    tool();
    glPopMatrix();
}


void balcony_fence()
{

    glPushMatrix();glScalef(10, 50, 10); glTranslatef(20.12,2,-28.14);

    glPushMatrix();glScalef(1.32, .06, .06); glTranslatef(-.5,9,90);drawCube1(0.1,0.1,0.1, 0.05,0.05,0.05 );glPopMatrix();//back up
    glPushMatrix();glScalef(1.32, .06, .06); glTranslatef(-.5,2.8,90);drawCube1(0.1,0.1,0.1, 0.05,0.05,0.05 );glPopMatrix();//back down
    for(int i =41;i>-5;i-=10)
    {glPushMatrix();glScalef(.06, .3, .06); glTranslatef(i,-0.01,90);drawCube1(0.1,0.1,0.1, 0.05,0.05,0.05 );glPopMatrix();} //back

    glPopMatrix();
}


void banner()
{
    glBindTexture(GL_TEXTURE_2D, ID[27]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(35,130,160);
    glScalef(13, 15, 0.2);
    //glRotatef(180,0,1,0);

    GLfloat no_mn[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienr[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffun[] = { 1,1,1, 1.0 };
    GLfloat mat_speculn[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininen[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienr);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffun);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_speculn);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininen);

    drawCube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}



void spotli()
{
    glPushMatrix();

    glTranslatef(115,-20,-180);
    glScalef(2.5, 2.5, 2.5);
    ///stand
   // glBindTexture(GL_TEXTURE_2D, ID[5]);
    //glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(5,48,30);
    glScalef(1, 0.45, 1);
    glRotatef(90,1,0,0);
    GLfloat no_mat502[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient502[] = { 0.05,0.05,0.05, 0.5 };
    GLfloat mat_diffuse502[] = { 0,.1,.1 ,1.0 };
    GLfloat mat_specular502[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess502[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient502);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse502);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular502);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess502);

    GLUquadricObj *ob = gluNewQuadric();
    gluQuadricTexture(ob, TRUE);
    gluCylinder(ob,0.3,0.3,15,20,20);

    glPopMatrix();
  //  glDisable(GL_TEXTURE_2D);

    ///lower
    glBindTexture(GL_TEXTURE_2D, ID[25]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(5,39,30);
    glScalef(1, 1, 1);
    glRotatef(theta_pakha, 0.0, 1.0, 0.0);///
    GLfloat no_mat5[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient5[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffuse5[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular5[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess5[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient5);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse5);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular5);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess5);

    GLUquadric *quad;
    quad = gluNewQuadric();
    gluQuadricTexture(quad, TRUE);
    gluSphere(quad,3,10,20);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


void spotli2()
{
    glPushMatrix();

    glTranslatef(20,28,-180);
    glScalef(4.5, 3.5, 4.5);
    ///stand
   // glBindTexture(GL_TEXTURE_2D, ID[5]);
    //glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(5,48,30);
    glScalef(1, 0.45, 1);
    glRotatef(90,1,0,0);
    GLfloat no_mat502[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient502[] = { 0.05,0.05,0.05, 0.5 };
    GLfloat mat_diffuse502[] = { 0,.1,.1 ,1.0 };
    GLfloat mat_specular502[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess502[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient502);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse502);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular502);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess502);

    GLUquadricObj *ob = gluNewQuadric();
    gluQuadricTexture(ob, TRUE);
    gluCylinder(ob,0.3,0.3,15,20,20);

    glPopMatrix();
  //  glDisable(GL_TEXTURE_2D);

    ///lower
    glBindTexture(GL_TEXTURE_2D, ID[25]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(5,39,30);
    glScalef(1, 1, 1);
    glRotatef(theta_pakha, 0.0, 1.0, 0.0);///
    GLfloat no_mat5[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient5[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffuse5[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specular5[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess5[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient5);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse5);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular5);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess5);

    GLUquadric *quad;
    quad = gluNewQuadric();
    gluQuadricTexture(quad, TRUE);
    gluSphere(quad,3,10,20);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


void drawsphere(float r,float g,float b,float alp,int sh)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, alp };
    GLfloat mat_ambient[] = { r, g, b, alp };
    GLfloat mat_diffuse[] = { r, g, b, alp };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, alp };
    GLfloat mat_shininess[] = {sh};

    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glutSolidSphere (.4, 20, 16);

}

void drawcube1(float r,float g,float b,float alp,int sh)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, alp };
    GLfloat mat_ambient[] = { r, g, b, alp };
    GLfloat mat_diffuse[] = { r, g, b, alp };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, alp };
    GLfloat mat_shininess[] = {sh};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidCube (1);
}


void fan()
{
    //glScalef(.5,.5,.5);

    glPushMatrix();

    glTranslatef(30,89,-3);
    glScalef(6.5,7,6.5);

    //base
    glPushMatrix();
    glScalef(2.5,.8,2.5);
    drawsphere(0,0,0,1,60);
    glPopMatrix();

    //base_line
    glPushMatrix();
    glScalef(.5,1.5,.5);
    glTranslatef(0,.5,0);
    drawcube1(0,0,0,1,60);
    glPopMatrix();

    glRotatef( alpha0, axis_x, axis_y, 0.0 );
    glRotatef( theta0, axis_x, axis_y, 0.0 );

    //line
    glPushMatrix();
    glScalef(3,.2,.2);
    drawcube1(0,0,0,1,60);
    glPopMatrix();

    //line
    glPushMatrix();
    glScalef(.2,.2,3);
    drawcube1(0,0,0,1,60);
    glPopMatrix();

    //pakha1
    glPushMatrix();
    glScalef(3.5,.2,1);
    glTranslatef(.85,0,0);
    drawcube1(0,0,0,1,60);
    glPopMatrix();

    //pakha2
    glPushMatrix();
    glScalef(3.5,.2,1);
    glTranslatef(-.85,0,0);
    drawcube1(0,0,0,1,60);
    glPopMatrix();

    //pakha3
    glPushMatrix();
    glScalef(1,.2,3.5);
    glTranslatef(0,0,.85);
    drawcube1(0,0,0,1,60);
    glPopMatrix();

    //pakha4
    glPushMatrix();
    glScalef(1,.2,3.5);
    glTranslatef(0,0,-.85);
    drawcube1(0,0,0,1,60);
    glPopMatrix();
    glPopMatrix();
}

void cup()
{
    glPushMatrix();

    glTranslatef(-85,129,40);
    glScalef(2,1.8,1.5);
    glBindTexture(GL_TEXTURE_2D, ID[10]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(16.3,8,36.2);
    //glScalef(0.8, 7, 0.8);
    glRotatef(90,1,0,0);
    GLfloat no_mattteoc[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttteoc[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusettteoc[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specularttteoc[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessttteoc[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttteoc);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettteoc);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttteoc);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttteoc);

    //drawCube();
    GLUquadric *qd;
    qd = gluNewQuadric();
    gluQuadricTexture(qd, TRUE);
    gluCylinder(qd,0.8,0.5,3,20,20);
    glPopMatrix();

    //coffe

    glBindTexture(GL_TEXTURE_2D, ID[11]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(16.3,7.5,36.2);
    //glScalef(0.8, 7, 0.8);
    glRotatef(90,1,0,0);
    GLfloat no_mattteocf[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttteocf[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusettteocf[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specularttteocf[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessttteocf[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttteocf);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettteocf);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttteocf);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttteocf);

    //drawCube();
    GLUquadric *qdc;
    qdc = gluNewQuadric();
    gluQuadricTexture(qdc, TRUE);
    gluSphere(qdc,0.6,100,20);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


}
void cups()
{
    glPushMatrix();
    glTranslatef(-18,-0.2,3);
    cup();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18,-0.2,-7);
    cup();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18.5,-0.2,-38.5);
    cup();
    glPopMatrix();
}

void cafemachine()
{
    glPushMatrix();
    glTranslatef(-90,141.4,20);
    glScalef(1.15,0.9,1);

    glBindTexture(GL_TEXTURE_2D, ID[29]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(13,17,32);
    glScalef(2.5, 7, 1);
    glRotatef(90,1,0,0);
    GLfloat no_mattte[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttte[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusettte[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specularttte[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessttte[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttte);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettte);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttte);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttte);

    drawCube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13,17,34);
    glScalef(0.8, 7, 0.8);
    glRotatef(90,1,0,0);
    GLfloat no_mattteoo[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttteoo[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusettteoo[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specularttteoo[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessttteoo[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttteoo);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettteoo);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttteoo);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttteoo);

    drawCube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(18,17,34);
    glScalef(0.8, 7, 0.8);
    glRotatef(90,1,0,0);
    GLfloat no_mattteo[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttteo[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusettteo[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specularttteo[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessttteo[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttteo);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettteo);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttteo);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttteo);

    drawCube();
    glPopMatrix();

    //down
    glPushMatrix();
    glTranslatef(15,7,34);
    glScalef(1.4, 0.2, 0.8);
    glRotatef(90,1,0,0);
    GLfloat no_mattteod[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttteod[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusettteod[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specularttteod[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessttteod[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttteod);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettteod);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttteod);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttteod);

    drawCube();
    glPopMatrix();

    //up
    glPushMatrix();
    glTranslatef(13,17.5,32);
    glScalef(2.5, 0.2, 2);
    glRotatef(90,1,0,0);
    GLfloat no_mattteu[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttteu[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusettteu[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specularttteu[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessttteu[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttteu);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettteu);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttteu);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttteu);

    drawCube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    ///switch
    glBindTexture(GL_TEXTURE_2D, ID[30]);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glTranslatef(13,10,36);
    glScalef(0.8, 1.4, 0.2);
    glRotatef(90,1,0,0);
    GLfloat no_mattteoos[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambienttteoos[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffusettteoos[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_specularttteoos[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininessttteoos[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambienttteoos);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffusettteoos);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specularttteoos);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininessttteoos);

    drawCube();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

}

void bowl()
{
    glPushMatrix();

    glTranslatef(50,16.7,30);
    glScalef(1.4, 1.7, 1);

    glBindTexture(GL_TEXTURE_2D, ID[31]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glTranslatef(0,71.5,70);
    //glScalef(7, 0.5, 12);
    glRotatef(90,1,0,0);
    glRotatef(90,0,0,1);
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5,0.5,0.5, 0.5 };
    GLfloat mat_diffuse[] = { 1.0,1,1, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);



    GLUquadric *qd;
    qd = gluNewQuadric();
    gluQuadricTexture(qd, TRUE);
    gluCylinder(qd,3,2,3,120,120);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
     glPopMatrix();
}

void bowls()
{

    glPushMatrix();

    bowl();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(90,0,0);
    bowl();
    glPopMatrix();


}









void animate()
{
   if (fan_rotate == true)
    {
        theta_pakha += 4.0;
        if(theta_pakha > 360) theta_pakha = 0.0;
    }
      if (sRotate == true)
    {
        theta0 += 8.2;
        if(theta0 > 360.0)
            theta0 -= 360.0*floor(theta0/360.0);
    }

    if (uRotate == true)
    {
        alpha0 += 8.2;
        if(alpha0 > 360.0)
            alpha0 -= 360.0*floor(alpha0/360.0);
    }



    if(rr%5==0)
    {
        if(pop==true) {pop=false;}
        else
        {
            pop=true;
        }

    }

    glutPostRedisplay();

}






void light()
{


    ///LIGHT1 (sun/e)
    GLfloat no_lightl[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambientl[]  = {0.5, 0.5, 0.5, 0.5};
    GLfloat light_diffusel[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specularl[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_positionl[] = { 1, 4, 20, 1.0 };
    GLfloat light_positionl1[] = { 10, 200, 500, 1.0 }; /// 1 200 30 1

    if(light1==true){glEnable( GL_LIGHT0);
    }
    else{  glDisable(GL_LIGHT0);  }
    glLightfv( GL_LIGHT0, GL_POSITION, light_positionl1);///position
    if(a1) {glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambientl);}///ambient
    else {glLightfv( GL_LIGHT0, GL_AMBIENT, no_lightl);}

    if(d1){ glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffusel);}///diffuse
    else {glLightfv(GL_LIGHT0, GL_DIFFUSE, no_lightl);}

    if(s1){glLightfv( GL_LIGHT0, GL_SPECULAR, light_specularl);}///specular
    else {glLightfv( GL_LIGHT0, GL_SPECULAR, no_lightl);}


   ///LIGHT2
    GLfloat no_lightl2[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambientl2[]  = {0.5, 0.5, 0.5, 0.5};
    GLfloat light_diffusel2[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specularl2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_positionl2[] = {1000, 100.8 ,242.7, 1.0 };//1.3 100.8 242.7

    if(light2){glEnable( GL_LIGHT1);
    }
    else{  glDisable(GL_LIGHT1); }
    glLightfv( GL_LIGHT1, GL_POSITION, light_positionl2);///position
    if(a2) {glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambientl2);}///ambient
    else {glLightfv( GL_LIGHT1, GL_AMBIENT, no_lightl2);}

    if(d2){ glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffusel2);}///diffuse
    else {glLightfv(GL_LIGHT1, GL_DIFFUSE, no_lightl2);}

    if(s2){glLightfv( GL_LIGHT1, GL_SPECULAR, light_specularl2);}///specular
    else {glLightfv( GL_LIGHT1, GL_SPECULAR, no_lightl2);}


   ///spot light
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient1[]  = {.3, .3, .3, 1.0};
    GLfloat light_ambient2[]  = {1, 0.843, 0, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 0.843, 0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0,0.0, 1.0 };
    GLfloat light_position2[] = { 135, 57, 0, 1.0 };
    GLfloat spot_direction2[] = { 0, -20, -250.0 };
    glEnable( GL_LIGHT6);
    glLightfv( GL_LIGHT6, GL_AMBIENT, light_ambient2);
    glLightfv( GL_LIGHT6, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT6, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT6, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spot_direction2);
    glLightf( GL_LIGHT6, GL_SPOT_CUTOFF, 20.0);
}









void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {

        case 'P':
        angle_P += inc_value;

        getCameraEye_P();

        break;
    case 'O':
        angle_P -= inc_value;
        getCameraEye_P();

        break;
    case 'Y':
        angle_Y +=  inc_value;

        getCameraEye_Y();


        break;
    case 'T':
        angle_Y -=  inc_value;

        getCameraEye_Y();

        break;
    case 'R':

        angle_R +=  inc_value;

        printf("%lf\n", angle_R);
        getCameraEye_R();
        break;

    case 'E':

        angle_R -=  inc_value;

        getCameraEye_R();

        break;
    case '8':
        eye_z=eye_z-5;
        look_z=look_z-5;
        break;
    case '9':
        eye_z=eye_z+5;
        look_z=look_z+5;
        break;
    case 'k':
        look_x=look_x+5;
        eye_x=eye_x+5;
        break;
    case 'j':
        look_x=look_x-5;
        eye_x=eye_x-5;
        break;

    case 'i':
        look_y=look_y+5;
        eye_y=eye_y+5;
        break;
    case 'm':
        look_y=look_y-5;
        eye_y=eye_y-5;
        break;

    case '2':
        dooroff = true;
        break;
    case '1':
        dooron = true;
        break;


    case 'w':
        light1=!light1;
        break;

    case 'e':
        light2=!light2;
        break;


    case 'x':
        s1=!s1;
        //std::cout<<light1;
        break;

    case 'y':
        d1=!d1;
        //std::cout<<light2;
        break;

    case 'z':
        a1=!a1;
        //std::cout<<light1;
        break;

    case '3':
        theta+=2.0;
        break;
    case '4':
        theta-=2.0;
        break;

   case 's':

        light6=!light6;
        break;
     case 'f':
        sRotate = !sRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        axis_z=0.0;
        break;



    case 27:
        exit(1);
    }
}




void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-5,5,-5,5, 4, 50);
    gluPerspective(60,1,40,3000);
    //glOrtho(-15, 15, -15, 15,-15,15);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eye_x,eye_y,eye_z, look_x,look_y,look_z, upx,upy,upz);

    glViewport(0, 0, 1500, 1000);

    glRotatef( theta, 0.0, 1.0, 0.0 );

    basement();
    road();
    path();
    treess();
    siri();
    siri_bal();

    building();
    building2();
    foodcort();
    pillars();

    photo();
    pc();
    refrigerator();
    recept();
    washrm();

    opendoor();
    sofass();
    sofaset();
    bar();
    tools();
    balcony_fence();
    banner();
    pools();
    water();
    cups();

    spotli();
    spotli2();
    fan();
    cafemachine();
    bowls();

    light();

    glFlush();
    glutSwapBuffers();
}

void LoadTexture(const char*filename, int a)
{
    glGenTextures(1, &ID[a]);
    glBindTexture(GL_TEXTURE_2D, ID[a]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[a]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(1500, 1000);
    glutCreateWindow("restaurant");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    LoadTexture("D:\\pro_graphics\\grass2.bmp",1);
    LoadTexture("D:\\pro_graphics\\sky.bmp",2);
    LoadTexture("D:\\pro_graphics\\road.bmp",3);
    LoadTexture("D:\\pro_graphics\\bark.bmp",4);
    LoadTexture("D:\\pro_graphics\\leaf3.bmp",5);
    LoadTexture("D:\\pro_graphics\\r2.bmp",6);
    LoadTexture("D:\\pro_graphics\\floor.bmp",7);
    LoadTexture("D:\\pro_graphics\\pillar1.bmp",8);
    LoadTexture("D:\\pro_graphics\\pfence.bmp",9);
    LoadTexture("D:\\pro_graphics\\cup.bmp",10);
    LoadTexture("D:\\pro_graphics\\f3.bmp",11);
    LoadTexture("D:\\pro_graphics\\f2.bmp",12);
    LoadTexture("D:\\pro_graphics\\f1.bmp",13);
    LoadTexture("D:\\pro_graphics\\kwall.bmp",14);
    LoadTexture("D:\\pro_graphics\\frz.bmp",15);
    LoadTexture("D:\\pro_graphics\\kbase.bmp",16);
    LoadTexture("D:\\pro_graphics\\t.bmp",17);
    LoadTexture("D:\\pro_graphics\\blue.bmp",18);
    LoadTexture("D:\\pro_graphics\\q.bmp",19);
    LoadTexture("D:\\pro_graphics\\upp.bmp",20);
    LoadTexture("D:\\pro_graphics\\gls5.bmp",21);
    LoadTexture("D:\\pro_graphics\\sofa.bmp",22);
    LoadTexture("D:\\pro_graphics\\wall2.bmp",23);
    LoadTexture("D:\\pro_graphics\\sofas.bmp",24);
    LoadTexture("D:\\pro_graphics\\gls2.bmp",25);
    LoadTexture("D:\\pro_graphics\\floor3.bmp",26);
    LoadTexture("D:\\pro_graphics\\logo.bmp",27);
    LoadTexture("D:\\pro_graphics\\river.bmp",28);
    LoadTexture("D:\\pro_graphics\\cofb.bmp",29);
    LoadTexture("D:\\pro_graphics\\switch.bmp",30);
    LoadTexture("D:\\pro_graphics\\machinebody.bmp",31);
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
