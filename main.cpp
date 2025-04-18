#include "main.h"
#include "input_manager.cpp"

InputManager* input = new InputManager();

float ballX = 0.0f;
float ballY = 0.0f;
float ballZ = -5.0f;

void initWindow(int argc, char** argv) {
    // create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("Team Project");

    // initialize perspective
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
}

void keyboard(unsigned char key, int x, int y)
{
    glutPostRedisplay();
}
void specialKeyboard(int key, int x, int y)
{
    float step = 0.2f; // how quickly to move

    switch (key) {
    case GLUT_KEY_LEFT:
        ballX -= step;
        break;
    case GLUT_KEY_RIGHT:
        ballX += step;
        break;
    case GLUT_KEY_UP:
        ballY += step;
        break;
    case GLUT_KEY_DOWN:
        ballY -= step;
        break;
    }

    glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
    input->mouse(button, state, x, y);
}
void mouseMotion(int x, int y)
{
    input->mouseMotion(x, y);

    glutPostRedisplay();
}

void drawBox()
{
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glColor3f(0.0f, 1.0f, 0.0f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
}

void drawBall() {
    glPushMatrix();
    glTranslatef(ballX, ballY, ballZ);  // move to ball's current position
    glColor3f(1.0f, 0.5f, 0.0f);
    glutSolidSphere(0.5, 30, 30);
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
        0.0f, 0.0f, 3.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.1f, 0.0f
    );

    //glRotatef(45, 0.0f, 1.0f, 0.0f);
    //drawBox();
    //glTranslatef(0.5, 0, -50);
    drawBall();

    glFlush();
    glutSwapBuffers();
}

void resize(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    initWindow(argc, argv);
    // input
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    // render
    glutDisplayFunc(display);
    glutReshapeFunc(resize);

    glutSpecialFunc(specialKeyboard); // movement for the ball

    // loop
    glutMainLoop();
    return 0;
}