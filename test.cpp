#include <cmath>
#include "sgl.h"
bool pMode;
//test
float ball_x = 1.0f;
float ball_y = 0.0f;
float ball_velx = 0.01f;
float ball_vely = 0.02f;
float ball_rad = 0.2f;
float box_len = 4.0f;
float tri_x = 0.0f;
float tri_y = 0.0f;
float theta = 0.0f; 
//test function definitions

void drawScene();
void update(int value);
void drawBox(float len);
void drawBall(float rad);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);

int main(int argc, char **argv) {
    
    // Initialize GLUT
    pMode = false;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    allInit();
    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = w * 2 / 3;
    int windowHeight = h * 2 / 3;

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

    glutCreateWindow("CSE251_sampleCode");  // Setup the window
    initRendering();

    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    glutMouseFunc(handleMouseclick);
    glutReshapeFunc(handleResize);
    glutTimerFunc(10, update, 0);

    glutMainLoop();
    return 0;
}

// Function to draw objects on the screen
void drawScene() {
 //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sglClear(0,0,0);
    //    glMatrixMode(GL_MODELVIEW);
 //   sglLookAt(0,0,-1,tri_x, tri_y,-5.0,0,1,0);
//    sglLookAt(tri_x, tri_y, 0.0, 0, 0, -5.0, 0, 1, 0);
    
    sglModLoadIdentity();
    sglModPushMatrix();

    // Draw Box
    sglModTranslate(0.0f, 0.0f, -5.0f);
    sglColour(1.0f, 0.0f, 0.0f);
    drawBox(box_len);
    
    // Draw Ball
    sglModPushMatrix();
    sglModTranslate(ball_x, ball_y, 0.0f);
    sglColour(0.0f, 1.0f, 0.0f);
    drawBall(ball_rad);
    sglModPopMatrix();

    // Draw Triangle
    sglModPushMatrix();
    sglModTranslate(tri_x, tri_y, 0.0f);
    sglModRotate(theta, 0.0f, 0.0f, 1.0f);
    sglModScale(0.5f, 0.5f, 0.5f);
    drawTriangle();
    sglModPopMatrix();

    sglModPopMatrix();
    glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {
    
    // Handle ball collisions with box
    if(ball_x + ball_rad > box_len/2 || ball_x - ball_rad < -box_len/2)
        ball_velx *= -1;
    if(ball_y + ball_rad > box_len/2 || ball_y - ball_rad < -box_len/2)
        ball_vely *= -1;
    
    // Update position of ball
    ball_x += ball_velx;
    ball_y += ball_vely;

    glutTimerFunc(10, update, 0);
}

void drawBox(float len) {
   
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    sglVertex(-len / 2, -len / 2, 0.0);
    sglVertex(len / 2, -len / 2, 0.0);
    sglVertex(len / 2, len / 2, 0.0);
    sglVertex(-len / 2, len / 2, 0.0);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawBall(float rad) {
    
   glBegin(GL_TRIANGLE_FAN);
   for(int i=0 ; i<360 ; i++) {
       sglVertex(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)), 0.0);
   }
   glEnd();
}

void drawTriangle() {

    sglBegin(SGL_TRIANGLES);
    sglColour(0.0f, 0.0f, 1.0f);
    sglVertex(0.0f, 1.0f, 0.0f);
    sglColour(0.0f, 1.0f, 0.0f);
    sglVertex(-1.0f, -1.0f, 0.0f);
    sglColour(1.0f, 0.0f, 0.0f);
    sglVertex(1.0f, -1.0f, 0.0f);
    sglEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

    sglViewport(0, 0, w, h);
    /*TO TEST*/
  //  glMatrixMode(GL_PROJECTION);
  //  glOrtho(-4.0, 4.0 , -4.0, 4.0, 1.0, 100.0);
  //  gFrustum(-4.0, 4.0 , -4.0, 4.0, 1.0, 100.0);

    if(pMode)
        sglProjOrtho(-4.0, 4.0 , -4.0, 4.0, 1.0, 100.0);
    else
        sglProjFrustum(-1.0, 1.0 , -1.0, 1.0, 1.0, 100.0);
   
    glMatrixMode(GL_MODELVIEW);
    sglModLoadIdentity();
    glOrtho(-10,10,-10,10,-1,-1);
}

void handleKeypress1(unsigned char key, int x, int y) {

    if (key == 27) {
        sglShow();   //show the file in output.txt
        exit(0);     // escape key is pressed
    }
    //translating the camera
    if (key == 'w')
    {
        sglViewTranslate(0.0, 0.0, 0.1);
    }
    if (key == 's')
    {
        sglViewTranslate(0.0, 0.0, -0.1);
    }
    if (key == 'a')
    {
        sglViewTranslate(-0.1, 0.0, 0.0);
    }
    if (key == 'd')
    {
        sglViewTranslate(0.1, 0.0, 0.0);
    }
    //rotating the camera
    if(key == 'r')
    {
        sglViewRotate(5.0,0.0,0.0,1.0);
    }
    if(key == 'l')
    {
        sglViewRotate(-5.0,0.0,0.0,1.0);
    }
    //press p to switch between ortho and frustum mode of projection
    if(key == 'p')
    {
        if(pMode == false)
        {
            sglProjOrtho(-4.0, 4.0 , -4.0, 4.0, 1.0, 100.0);
        }
        if(pMode == true)
        {
            sglProjFrustum(-1.0, 1.0 , -1.0, 1.0, 1.0, 100.0);
        }
        (pMode==false)? pMode = true : pMode = false;
    }



}

void handleKeypress2(int key, int x, int y) {

    if (key == GLUT_KEY_LEFT)
        tri_x -= 0.1;
    if (key == GLUT_KEY_RIGHT)
        tri_x += 0.1;
    if (key == GLUT_KEY_UP)
        tri_y += 0.1;
    if (key == GLUT_KEY_DOWN)
        tri_y -= 0.1;
}

void handleMouseclick(int button, int state, int x, int y) {

    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
            theta += 15;
        else if (button == GLUT_RIGHT_BUTTON)
            theta -= 15;
    }
}
