#include "main.h"
#include "input_manager.cpp"

InputManager* input = new InputManager();

float ballX = 0.0f;
float ballY = 0.0f;
float ballZ = -5.0f;

float ballVelocityX = 0.015f;
float ballVelocityY = 0.015f;
float ballVelocityZ = 0.02f;

// Initilizations
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

void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // light properties
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    GLfloat lightPosition[] = { 5.0f, 5.0f, 1.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // Enable color tracking for materials
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

// Input Controll
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

// Drawing
void drawWall() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-10.0f, -10.0f, -6.0f);
    glVertex3f(10.0f, -10.0f, -6.0f);
    glVertex3f(10.0f, 10.0f, -6.0f);
    glVertex3f(-10.0f, 10.0f, -6.0f);
    glEnd();
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

void moveBall(int value) {
    // Move ball
    //ballX += ballVelocityX;
    //ballY += ballVelocityY;
    ballZ -= ballVelocityZ;

    // Bounce off "walls"
    if (ballZ < -6.0f || ballZ > 5.0f) ballVelocityZ *= -1;

    glutPostRedisplay();
    glutTimerFunc(16, moveBall, 0); // ~60 FPS
}

// Display
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
        0.0f, -1.0f, 5.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.1f, 0.0f
    );

    //glRotatef(45, 0.0f, 1.0f, 0.0f);
    //drawBox();
    //glTranslatef(0.5, 0, -50);
    drawBall();
    drawWall(); // the grey wall is at z=-6

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
    initLighting();
    // input
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    // render
    glutDisplayFunc(display);
    glutReshapeFunc(resize);

    //glutSpecialFunc(specialKeyboard); // movement for the ball // changing ball to move on its own
    srand(static_cast<unsigned>(time(0))); // seed RNG
    glutTimerFunc(0, moveBall, 0);

    // loop
    glutMainLoop();
    return 0;
}