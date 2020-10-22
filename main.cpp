#include <bits/stdc++.h>
#include <GL/glut.h>
#include "BmpLoader.h"
using namespace std;

char title[] = "Rayhan Azka Anandhias Putra - 181524028";
float angle = 0.0;
GLuint texture_wall, texture_door, texture_grass, texture_roof, texture_sky;
GLuint texture_window, texture_pagar, texture_gapura;

void init();
void keyboard_handler(unsigned char key, int x, int y);
void reshape(GLsizei w, GLsizei h);
void display();
float z_trans = -15, x_trans = 0.0, y_trans = 0.0;
float x_rot  = 0.0 ,y_rot=1.0,z_rot=0.0;
GLuint load_texture(const char* fname);
void draw_house();
void draw_pagar();
void draw_gapura();

int main(int argc, char **argv) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(title);
	glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard_handler);
    init();
    glutMainLoop();
    return 0;
}


void init() {
    glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);

    texture_grass = load_texture("grass.bmp");
    texture_sky = load_texture("sky.bmp");
    texture_wall = load_texture("wall3.bmp");
    texture_roof = load_texture("roof2.bmp");
    texture_door = load_texture("door2.bmp");
    texture_window = load_texture("window2.bmp");
    texture_pagar = load_texture("roof.bmp");
    texture_gapura = load_texture("roof.bmp");
}

void keyboard_handler(unsigned char key, int x, int y) {
    // d dan f
	switch (key) {
        case GLUT_KEY_RIGHT:  
            angle += 1;
            if (angle > 360) angle = 0.0;
            break;
        case GLUT_KEY_LEFT:
            angle -= 1;
            if (angle > 360) angle = 0.0;
            break;
        case 'q':
            exit(0);
            break;
        case 'u':
            z_trans +=1;
            break;
        case 'i':
            z_trans -=1;
            break;
        default: 
            break;
	}
	glutPostRedisplay();
}

void reshape(GLsizei w, GLsizei h) {
    const float ar = (float) w / (float) h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //draw grass
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_grass );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,70.0,1);  glVertex3f(-50,-1.5,50);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(-50,-1.5,-50);
            glTexCoord3f(70.0,0.0,1);  glVertex3f(50,-1.5,-50);
            glTexCoord3f(70.0,70.0,1);  glVertex3f(50,-1.5,50);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //draw sky
    glPushMatrix();
    	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_sky);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS); //Belakang
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-50,50,-50);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-50,-50,-50);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(50,-50,-50);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(50,50,-50);
        glEnd();
        glBegin(GL_QUADS); //Depan
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-50,50,50);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-50,-50,50);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(50,-50,50);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(50,50,50);
        glEnd();
        glBegin(GL_QUADS); //Kanan
            glTexCoord3f(1.0,1.0,0);  glVertex3f(50,50,-50);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(50,-50,-50);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(50,-50,50);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(50,50,50);
        glEnd();
        glBegin(GL_QUADS); //Kiri
            glTexCoord3f(1.0,1.0,0);  glVertex3f(-50,50,-50);
            glTexCoord3f(0.0,0.0,0);  glVertex3f(-50,-50,-50);
            glTexCoord3f(1.0,0.0,0);  glVertex3f(-50,-50,50);
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-50,50,50);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    draw_house();
    draw_pagar();
    draw_gapura();

    glutSwapBuffers();
}

void draw_house() {
    //draw front-side wall
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_wall);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,0.1);  glVertex3f(-2,0,1);
            glTexCoord3f(4.0,2.0,0.1);  glVertex3f(1,0,1);
            glTexCoord3f(4.0,0.0,0.1);  glVertex3f(1,-1.5,1);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-2,-1.5,1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //draw right-side wall
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_wall);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,0.1);  glVertex3f(1,0,1);
            glTexCoord3f(4.0,2.0,0.1);  glVertex3f(1,0,-1.5);
            glTexCoord3f(4.0,0.0,0.1);  glVertex3f(1,-1.5,-1.5);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(1,-1.5,1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //draw left-side wall
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_wall);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,0.1);  glVertex3f(-2,0,1);
            glTexCoord3f(4.0,2.0,0.1);  glVertex3f(-2,0,-1.5);
            glTexCoord3f(4.0,0.0,0.1);  glVertex3f(-2,-1.5,-1.5);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-2,-1.5,1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_wall);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,0.1);  glVertex3f(-5,0,-1.5);
            glTexCoord3f(4.0,2.0,0.1);  glVertex3f(-2,0,-1.5);
            glTexCoord3f(4.0,0.0,0.1);  glVertex3f(-2,-1.5,-1.5);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-5,-1.5,-1.5);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_wall);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,0.1);  glVertex3f(4,0,-1.5);
            glTexCoord3f(4.0,2.0,0.1);  glVertex3f(1,0,-1.5);
            glTexCoord3f(4.0,0.0,0.1);  glVertex3f(1,-1.5,-1.5);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(4,-1.5,-1.5);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_wall);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,0.1);  glVertex3f(4,0,-1.5);
            glTexCoord3f(4.0,2.0,0.1);  glVertex3f(4,0,-7);
            glTexCoord3f(4.0,0.0,0.1);  glVertex3f(4,-1.5,-7);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(4,-1.5,-1.5);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_wall);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,0.1);  glVertex3f(-5,0,-1.5);
            glTexCoord3f(4.0,2.0,0.1);  glVertex3f(-5,0,-7);
            glTexCoord3f(4.0,0.0,0.1);  glVertex3f(-5,-1.5,-7);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-5,-1.5,-1.5);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_wall);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,2.0,0.1);  glVertex3f(-5,0,-7);
            glTexCoord3f(4.0,2.0,0.1);  glVertex3f(4,0,-7);
            glTexCoord3f(4.0,0.0,0.1);  glVertex3f(4,-1.5,-7);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-5,-1.5,-7);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //sisi kanan atap
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_wall);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_TRIANGLES);  // Wall
            glTexCoord3f(0.0,1.0,0);  glVertex3f(4,1,-4.25);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(4,0,-1.5);
            glTexCoord3f(-1.0,0.0,-1);  glVertex3f(4,0,-7);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //sisi kiri atap
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_wall);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_TRIANGLES);  // Wall
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-5,1,-4.25);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(-5,0,-1.5);
            glTexCoord3f(-1.0,0.0,-1);  glVertex3f(-5,0,-7);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //genteng belakang
    glPushMatrix(); 
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_roof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
	glBegin(GL_QUADS); //Atap Belakang
		glTexCoord3f(0.0,2.0,0); glVertex3f(-5.3,1,-4.25);
		glTexCoord3f(4.0,2.0,0); glVertex3f(4.3,1,-4.25);
		glTexCoord3f(4.0,0.0,-1.25); glVertex3f(4.3,-0.01,-7.1);
		glTexCoord3f(0.0,.00,-1.25); glVertex3f(-5.3,-0.01,-7.1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

    //genteng belakang
    glPushMatrix(); 
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_roof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
	glBegin(GL_QUADS); //Atap depan
		glTexCoord3f(0.0,2.0,0); glVertex3f(-5.3,1,-4.25);
		glTexCoord3f(4.0,2.0,0); glVertex3f(4.3,1,-4.25);
		glTexCoord3f(4.0,0.0,-1.25); glVertex3f(4.3,-0.01,-1.4);
		glTexCoord3f(0.0,.00,-1.25); glVertex3f(-5.3,-0.01,-1.4);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

    //sisi depan atap
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_wall);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_TRIANGLES);  // Wall
            glTexCoord3f(0.0,1.0,0);  glVertex3f(-0.5,1,1);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(-2,0,1);
            glTexCoord3f(-1.0,0.0,-1);  glVertex3f(1,0,1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix(); 
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_roof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
	glBegin(GL_QUADS); //Atap depan
		glTexCoord3f(0.0,2.0,0); glVertex3f(-0.5,1,1.6);
		glTexCoord3f(4.0,2.0,0); glVertex3f(-0.5,1,-4.25);
		glTexCoord3f(4.0,0.0,-1.25); glVertex3f(-2.1,-0.01,-4.25);
		glTexCoord3f(0.0,.00,-1.25); glVertex3f(-2.1,-0.01,1.6);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

    glPushMatrix(); 
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_roof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
	glBegin(GL_QUADS); //Atap depan
		glTexCoord3f(0.0,2.0,0); glVertex3f(-0.5,1,1.6);
		glTexCoord3f(4.0,2.0,0); glVertex3f(-0.5,1,-4.25);
		glTexCoord3f(4.0,0.0,-1.25); glVertex3f(1.1,-0.01,-4.25);
		glTexCoord3f(0.0,.00,-1.25); glVertex3f(1.1,-0.01,1.6);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

    //Pintu
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_door);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0.0,0,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,10001);    glVertex3f(-1.2,-0.4,1.0001);
            glTexCoord3f(1.0,1.0,10001);    glVertex3f(0.25,-0.4,1.0001);
            glTexCoord3f(1.0,0.0,10001);    glVertex3f(0.25,-1.5,1.0001);
            glTexCoord3f(0.0,0.0,10001);    glVertex3f(-1.2,-1.5,1.0001);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //jendela
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_window);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0.0,0,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,10001);    glVertex3f(-4.5,-0.4,-1.49);
            glTexCoord3f(1.0,1.0,10001);    glVertex3f(-4.0,-0.4,-1.49);
            glTexCoord3f(1.0,0.0,10001);    glVertex3f(-4.0,-1.0,-1.49);
            glTexCoord3f(0.0,0.0,10001);    glVertex3f(-4.5,-1.0,-1.49);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //jendela
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_window);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0.0,0,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,10001);    glVertex3f(-3.5,-0.4,-1.49);
            glTexCoord3f(1.0,1.0,10001);    glVertex3f(-3.0,-0.4,-1.49);
            glTexCoord3f(1.0,0.0,10001);    glVertex3f(-3.0,-1.0,-1.49);
            glTexCoord3f(0.0,0.0,10001);    glVertex3f(-3.5,-1.0,-1.49);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //jendela
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_window);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0.0,0,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,10001);    glVertex3f(3.5,-0.4,-1.49);
            glTexCoord3f(1.0,1.0,10001);    glVertex3f(3.0,-0.4,-1.49);
            glTexCoord3f(1.0,0.0,10001);    glVertex3f(3.0,-1.0,-1.49);
            glTexCoord3f(0.0,0.0,10001);    glVertex3f(3.5,-1.0,-1.49);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //jendela
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_window);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0.0,0,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,10001);    glVertex3f(2.5,-0.4,-1.49);
            glTexCoord3f(1.0,1.0,10001);    glVertex3f(2.0,-0.4,-1.49);
            glTexCoord3f(1.0,0.0,10001);    glVertex3f(2.0,-1.0,-1.49);
            glTexCoord3f(0.0,0.0,10001);    glVertex3f(2.5,-1.0,-1.49);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //jendela
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_window);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0.0,0,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,10001);    glVertex3f(-4.5,-0.4,-7.1);
            glTexCoord3f(1.0,1.0,10001);    glVertex3f(-4.0,-0.4,-7.1);
            glTexCoord3f(1.0,0.0,10001);    glVertex3f(-4.0,-1.0,-7.1);
            glTexCoord3f(0.0,0.0,10001);    glVertex3f(-4.5,-1.0,-7.1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //jendela
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_window);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0.0,0,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,10001);    glVertex3f(-2.5,-0.4,-7.1);
            glTexCoord3f(1.0,1.0,10001);    glVertex3f(-2.0,-0.4,-7.1);
            glTexCoord3f(1.0,0.0,10001);    glVertex3f(-2.0,-1.0,-7.1);
            glTexCoord3f(0.0,0.0,10001);    glVertex3f(-2.5,-1.0,-7.1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //jendela
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_window);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0.0,0,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,10001);    glVertex3f(3.5,-0.4,-7.1);
            glTexCoord3f(1.0,1.0,10001);    glVertex3f(3.0,-0.4,-7.1);
            glTexCoord3f(1.0,0.0,10001);    glVertex3f(3.0,-1.0,-7.1);
            glTexCoord3f(0.0,0.0,10001);    glVertex3f(3.5,-1.0,-7.1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //jendela
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_window);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0.0,0,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,10001);    glVertex3f(1.5,-0.4,-7.1);
            glTexCoord3f(1.0,1.0,10001);    glVertex3f(1.0,-0.4,-7.1);
            glTexCoord3f(1.0,0.0,10001);    glVertex3f(1.0,-1.0,-7.1);
            glTexCoord3f(0.0,0.0,10001);    glVertex3f(1.5,-1.0,-7.1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_window);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0.0,0,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,10001);    glVertex3f(4.1,-0.4,-3.0);
            glTexCoord3f(1.0,1.0,10001);    glVertex3f(4.1,-0.4,-3.5);
            glTexCoord3f(1.0,0.0,10001);    glVertex3f(4.1,-1.0,-3.5);
            glTexCoord3f(0.0,0.0,10001);    glVertex3f(4.1,-1.0,-3.0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_window);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0.0,0,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,10001);    glVertex3f(4.1,-0.4,-5.0);
            glTexCoord3f(1.0,1.0,10001);    glVertex3f(4.1,-0.4,-5.5);
            glTexCoord3f(1.0,0.0,10001);    glVertex3f(4.1,-1.0,-5.5);
            glTexCoord3f(0.0,0.0,10001);    glVertex3f(4.1,-1.0,-5.0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_window);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0.0,0,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,10001);    glVertex3f(-5.1,-0.4,-3.0);
            glTexCoord3f(1.0,1.0,10001);    glVertex3f(-5.1,-0.4,-3.5);
            glTexCoord3f(1.0,0.0,10001);    glVertex3f(-5.1,-1.0,-3.5);
            glTexCoord3f(0.0,0.0,10001);    glVertex3f(-5.1,-1.0,-3.0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_window);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0.0,0,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,10001);    glVertex3f(-5.0001,-0.4,-5.0);
            glTexCoord3f(1.0,1.0,10001);    glVertex3f(-5.0001,-0.4,-5.5);
            glTexCoord3f(1.0,0.0,10001);    glVertex3f(-5.0001,-1.0,-5.5);
            glTexCoord3f(0.0,0.0,10001);    glVertex3f(-5.0001,-1.0,-5.0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void draw_pagar() {
    //pagar kiri
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_pagar);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,1);  glVertex3f(-6,-0.8,4);
            glTexCoord3f(1.0,1.0,1);  glVertex3f(-6,-0.8,-9);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(-6,-1.5,-9);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(-6,-1.5,4);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //pagar kanan
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_pagar);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,1);  glVertex3f(5,-0.8,4);
            glTexCoord3f(1.0,1.0,1);  glVertex3f(5,-0.8,-9);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(5,-1.5,-9);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(5,-1.5,4);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //pagar belakang
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_pagar);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,1);  glVertex3f(-6,-0.8,-9);
            glTexCoord3f(1.0,1.0,1);  glVertex3f(5,-0.8,-9);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(5,-1.5,-9);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(-6,-1.5,-9);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    //depan kiri
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_pagar);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,1);  glVertex3f(-6,-0.8,4);
            glTexCoord3f(1.0,1.0,1);  glVertex3f(-1.7,-0.8,4);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(-1.7,-1.5,4);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(-6,-1.5,4);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //depan kanan
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_pagar);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(x_trans,y_trans,z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,1);  glVertex3f(0.6,-0.8,4);
            glTexCoord3f(1.0,1.0,1);  glVertex3f(5,-0.8,4);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(5,-1.5,4);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(0.6,-1.5,4);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void draw_gapura() {
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_gapura);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0, z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,1);  glVertex3f(-1.7,1,4.2);
            glTexCoord3f(1.0,1.0,1);  glVertex3f(-1.4,1,4.2);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(-1.4,-1.5,4.2);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(-1.7,-1.5,4.2);

            glTexCoord3f(0.0,1.0,1);  glVertex3f(-1.4,1,4.2);
            glTexCoord3f(1.0,1.0,1);  glVertex3f(-1.4,1,3.8);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(-1.4,-1.5,3.8);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(-1.4,-1.5,4.2);

            glTexCoord3f(0.0,1.0,1);  glVertex3f(-1.7,1,4.2);
            glTexCoord3f(1.0,1.0,1);  glVertex3f(-1.7,1,3.8);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(-1.7,-1.5,3.8);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(-1.7,-1.5,4.2);

            glTexCoord3f(0.0,1.0,1);  glVertex3f(-1.7,1,3.8);
            glTexCoord3f(1.0,1.0,1);  glVertex3f(-1.4,1,3.8);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(-1.4,-1.5,3.8);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(-1.7,-1.5,3.8);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_gapura);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0, z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(0.0,1.0,1);  glVertex3f(0.6,1,4.2);
            glTexCoord3f(1.0,1.0,1);  glVertex3f(0.3,1,4.2);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(0.3,-1.5,4.2);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(0.6,-1.5,4.2);

            glTexCoord3f(0.0,1.0,1);  glVertex3f(0.3,1,4.2);
            glTexCoord3f(1.0,1.0,1);  glVertex3f(0.3,1,3.8);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(0.3,-1.5,3.8);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(0.3,-1.5,4.2);

            glTexCoord3f(0.0,1.0,1);  glVertex3f(0.6,1,4.2);
            glTexCoord3f(1.0,1.0,1);  glVertex3f(0.6,1,3.8);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(0.6,-1.5,3.8);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(0.6,-1.5,4.2);

            glTexCoord3f(0.0,1.0,1);  glVertex3f(0.6,1,3.8);
            glTexCoord3f(1.0,1.0,1);  glVertex3f(0.3,1,3.8);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(0.3,-1.5,3.8);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(0.6,-1.5,3.8);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_gapura);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0, z_trans);
        glRotatef(angle, x_rot, y_rot, z_rot);
        glBegin(GL_QUADS);  // Wall
            glTexCoord3f(1.0,1.0,1);  glVertex3f(-1.8,1.01,4.3);
            glTexCoord3f(0.0,1.0,1);  glVertex3f(0.7,1.01,4.3);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(0.7,1.01,3.7);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(-1.8,1.01,3.7);

            glTexCoord3f(1.0,1.0,1);  glVertex3f(-1.8,1.01,4.3);
            glTexCoord3f(0.0,1.0,1);  glVertex3f(0.7,1.01,4.3);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(0.7,1.41,4.3);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(-1.8,1.41,4.3);

            glTexCoord3f(1.0,1.0,1);  glVertex3f(-1.8,1.01,3.7);
            glTexCoord3f(0.0,1.0,1);  glVertex3f(0.7,1.01,3.7);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(0.7,1.41,3.7);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(-1.8,1.41,3.7);

            glTexCoord3f(1.0,1.0,1);  glVertex3f(-1.8,1.41,4.3);
            glTexCoord3f(0.0,1.0,1);  glVertex3f(0.7,1.41,4.3);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(0.7,1.41,3.7);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(-1.8,1.41,3.7);

            glTexCoord3f(1.0,1.0,1);  glVertex3f(0.7,1.01,4.3);
            glTexCoord3f(0.0,1.0,1);  glVertex3f(0.7,1.01,3.7);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(0.7,1.41,3.7);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(0.7,1.41,4.3);

            glTexCoord3f(1.0,1.0,1);  glVertex3f(-1.8,1.01,4.3);
            glTexCoord3f(0.0,1.0,1);  glVertex3f(-1.8,1.01,3.7);
            glTexCoord3f(0.0,0.0,1);  glVertex3f(-1.8,1.41,3.7);
            glTexCoord3f(1.0,0.0,1);  glVertex3f(-1.8,1.41,4.3);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

GLuint load_texture(const char* fname) {
    BmpLoader bl(fname);	
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 GL_RGB,
				 bl.iWidth, bl.iHeight,
				 0,
				 GL_RGB,
				 GL_UNSIGNED_BYTE,
				 bl.textureData);
	return textureId;
}