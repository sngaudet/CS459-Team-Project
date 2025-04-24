#include "main.h"
//#include "input_manager.cpp"

float ballX = 0.0f;
float ballY = 0.0f;
float ballZ = -5.0f;

float ballVelocityX = 0.015f;
float ballVelocityY = 0.015f;
float ballVelocityZ = 0.02f;

float cameraRotationX = 0.0f;
float cameraRotationY = 0.0f;
float cameraZoomZ = 5.0f;
float cameraPanX = 0.0f;
float cameraPanY = 0.0f;

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

// Update input handling to use standalone functions
void initInputHandlers() {
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
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

// Transfromations
void transformCamera() {
    glTranslatef(cameraPanX, cameraPanY, -cameraZoomZ);
    glRotatef(cameraRotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraRotationY, 0.0f, 1.0f, 0.0f);
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
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Apply camera transformations
    transformCamera();

    drawBall();
    drawWall(); // the grey wall is at z=-6

    glFlush();
    glutSwapBuffers();
}

void resize(int w, int h) {
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
    initInputHandlers(); // Initialize input handlers

    // render
    glutDisplayFunc(display);
    glutReshapeFunc(resize);

    srand(static_cast<unsigned>(time(0))); // seed RNG
    glutTimerFunc(0, moveBall, 0);

    // TEMP, printing camera position
    //glutTimerFunc(5000, printCameraPosition, 0);

    // loop
    glutMainLoop();
    return 0;
}