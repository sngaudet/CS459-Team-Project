#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> // (or others, depending on the system in use)
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

// window
void initWindow(int argc, char** argv);
// inputs
void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
// render
void display();

int main(int argc, char** argv);


