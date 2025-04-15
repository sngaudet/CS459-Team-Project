#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> // (or others, depending on the system in use)
#include <iostream>
#include <Windows.h>

static GLfloat position[] = { 10.0, 10.0, 10.0, 1.0 };
static GLdouble cpos[] = { 0.0, 10.0, 200.0 };

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0,0.0,0.0);
    glScalef(0.3,0.2,0.05);
    glutSolidCube(1.0);

    glColor3f(1.0,0.5,1.0);
    glTranslatef(0.0,0.0,0.0);
    glutSolidSphere(0.1,100,100);

    glFlush();
}

void init(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("Team Project");

    glClearColor(0.0, 0.0, 0.0, 1.0);
    //glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
}

void run() {
     glutMainLoop();
}

int main(int argc, char** argv) {
    init(argc, argv);
    run();
    return 0;
}


