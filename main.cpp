#include "main.h"
#include "input_manager.cpp"

InputManager* input = new InputManager();

void initWindow(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("Team Project");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    //glEnable(GL_DEPTH_TEST);
}

void keyboard(unsigned char key, int x, int y)
{
    input->keyboard(key, x, y);
}
void specialKeyboard(int key, int x, int y)
{
    input->specialKeyboard(key, x, y);
}
void mouse(int button, int state, int x, int y)
{
    input->mouse(button, state, x, y);
}
void mouseMotion(int x, int y)
{
    input->mouseMotion(x, y);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0, 0.0, 0.0);
    glScalef(0.3, 0.2, 0.05);
    glutSolidCube(1.0);

    glColor3f(1.0, 0.5, 1.0);
    glTranslatef(0.0, 0.0, 0.0);
    glutSolidSphere(0.1, 100, 100);

    glFlush();
}

int main(int argc, char** argv) {
    initWindow(argc, argv);
    // input
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    // render
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}