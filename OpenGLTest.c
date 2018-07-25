#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// COMPILE WITH cc OpenGLTest.c -o tracking -lGL -lGLU -lglut for linux

// IF YOU ARE GREG
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

// IF YOU ARE NOT GREG
// #include <GLUT/glut.h>
// #include <OpenGL/gl.h>
// #include <OpenGL/glu.h>

#include <stdio.h>
#include <string.h>
#include <assert.h>

// GLOBALS
bool keys[256] = {false};
int doubleCount[256] = {0};

float angle = 0.0;
float x = 0,y = 0;
float oldX, oldY;
float newX, newY;
float resizeH = 0;
float resizeW = 0;
int kSpeed = 1;

int autoState = 0;

float theWidth;
float theHeight;

int elapsed;
int cycleCounter = 0;

char string[256];
// FLAGS
bool isDisplayingText = true;
bool timerSet = false;
int testFlag = 0;
int triangleFlag = 0;
int squareFlag = 1;
float red = 0,green = 0,blue = 0;
int theAuton = 0;
int fullTestState = 0;

void GL_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    theHeight = height;
    theWidth = width;
//    sprintf(string, "WIDTH: %i HEIGHT: %i",width,height);
}

void GL_keyPressed(unsigned char key){
  keys[key] = true;

  if(keys['w']) y+=0.01*kSpeed;
  if(keys['a']) x-=0.01*kSpeed;
  if(keys['s']) y-=0.01*kSpeed;
  if(keys['d']) x+=0.01*kSpeed;

  if(keys['W']) y+=0.05*kSpeed;
  if(keys['A']) x-=0.05*kSpeed;
  if(keys['S']) y-=0.05*kSpeed;
  if(keys['D']) x+=0.05*kSpeed;

  if(keys['i']) resizeH+=0.01;
  if(keys['j']) resizeW+=0.01;
  if(keys['k']) resizeH-=0.01;
  if(keys['l']) resizeW-=0.01;

  if(keys['I']) resizeH+=0.05;
  if(keys['J']) resizeW+=0.05;
  if(keys['K']) resizeH-=0.05;
  if(keys['L']) resizeW-=0.05;

  if(key == 'R'){
    x = 0;
    y = 0;
    resizeW = 0;
    resizeH = 0;
    testFlag = 0;
    angle = 0.0;
  }

  if(key == 'z'){
    if(theAuton > 0)
      theAuton--;
  }

  if(key == 'x'){
    if(theAuton < 4)
      theAuton++;
  }

  if(key == 32){
    if(timerSet){
      timerSet = false;
    }else{
      timerSet = true;
      elapsed = 0;
    }
  }

  if (key == 'u') {
    angle += 10;
  }

  if (key == 'o') {
    angle -= 10;
  }


  if(key == 'G'){
    if(testFlag) testFlag = 0;
    else testFlag = 1;
    autoState = 1;
    fullTestState = 0;
  }

  if (key == 'q') {
    if(kSpeed > 1){
      kSpeed--;
    }
  }

  if (key == 'e') {
    if(kSpeed < 10){
      kSpeed++;
    }
  }


  if (key == 'm') {
    if(triangleFlag){
      if(doubleCount['m'] > 0){
        resizeH = -0.30 - resizeH;
        doubleCount['m'] = 0;
      }
      if(doubleCount['m'] == 0)doubleCount['m'] = 20;
    }
  }

  if(key == 'B'){
    if(doubleCount['B'] > 0){
      if(isDisplayingText){
        isDisplayingText = 0;
        doubleCount['B'] = 0;
      }else{
        isDisplayingText = 1;
        doubleCount['B'] = 0;
      }
    }else if(doubleCount['B'] == 0){
      doubleCount['B'] = 20;
    }
  }

  if (key == 'T') {
    if(triangleFlag){
     triangleFlag = 0;
     squareFlag = 1;
    }else{
     triangleFlag = 1;
     squareFlag = 0;
    }
  }


  if(key == 27)exit(EXIT_SUCCESS);

  // if(key == 'r')
  //   if(red) red = 0.0;
  //   else red = 1.0;
  // if(key == 'g')
  //   if(green) green = 0.0;
  //   else green = 1.0;
  // if(key == 'b')
  //   if(blue) blue = 0.0;
  //   else blue = 1.0;

}

int dragState = 0;


void GL_mouseHandler(int button, int state, int theX, int theY){


  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    red  = 0.0;
    green = 0.0;
    blue = 0.0;
  }

// DISCLAIMER: THIS IS A COMPLETE GUESS ON HOW TO DO THIS
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    if(dragState == 0){
      oldX = theX;
      oldY = theY;
      dragState = 1;
    }
  }

  if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
    // newX = theX;
    // newY = theY;
    dragState = 0;
  }

  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !testFlag){
    x = (theX - (theWidth/2))/(theWidth/2);
    y = -((theY - theHeight/2)/(theHeight/2));
  }

}
// MIGHT NOT EVEN BE NEEDED?
void GL_dragHandler(int theX, int theY){

  glutPostRedisplay();
  newX = theX;
  newY = theY;
  if(fabs(oldX - newX) > 20 && fabs(oldY - newY) > 20){
    resizeW = -((newX - oldX)/(theWidth/2.0));
    resizeH = -((newY - oldY)/(theHeight/2.0));
  }

}

void GL_keyUp(unsigned char key){

  if(keys[key]) keys[key] = false;

}

void GL_Periodic(){
  // sprintf(string, "DOUBLECOUNT M: %i",doubleCount['m']);
  sprintf(string, "ELAPSED: %i",elapsed);
  displayText(string,1,15);
  sprintf(string, "RUNNING TEST: %i", theAuton);
  displayText(string,1,30);
  sprintf(string, "SPEED: X%i",kSpeed);
  displayText(string,1,21);

  for (int i = 0; i < 256; i++) {
    if(doubleCount[i]) doubleCount[i]--;
  }
}

void GL_idle(){
  glutPostRedisplay();
}

void GL_timer(){

  if(timerSet){
    elapsed++;
  }
  glutTimerFunc(1000,GL_timer,0);

}

void borderTest(){
  switch (autoState) {
    case 1:
      x += 0.01*kSpeed;
      if (x > 0.85) {
        autoState = 2;
      }
      break;
    case 2:
      y -= 0.01*kSpeed;
      if(y < -0.85){
        autoState = 3;
      }
      break;
    case 3:
      x -= 0.01*kSpeed;
      if(x < -0.85){
        autoState = 4;
      }
      break;
    case 4:
      y += 0.01*kSpeed;
      if(y > 0.85){
        autoState = 1;
        cycleCounter++;
      }
      break;
  }
}

void sweepTest(){
  // red = 1.0;
  // green = 0.0;
  // blue = 0.0;
  switch (autoState) {
    case 1:
      x += 0.01*kSpeed;
      if(x > 0.85){
        autoState = 2;
      }
      break;
    case 2:
      x -= 0.01*kSpeed;
      if(x < -0.85){
        autoState = 1;
        cycleCounter++;
      }
      break;
  }

}

void verticalTest(){
  // red = 0.0;
  // green = 1.0;
  // blue = 0.0;
  switch (autoState) {
    case 1:
        y += 0.01*kSpeed;
        if(y > 0.85){
          autoState = 2;
        }
      break;
    case 2:
        y -= 0.01*kSpeed;
        if(y < -0.85){
          autoState = 1;
          cycleCounter++;
        }
      break;
  }
}

void infinityTest(){
    switch (autoState) {
      case 1:
          if (x < 0.85) {
            x += 0.01*kSpeed;
          }
          if (y < 0.85) {
            y += 0.01*kSpeed;
          }
          if (x >= 0.85 && y >= 0.85) {
            autoState = 2;
          }
        break;
      case 2:
          y -= 0.01*kSpeed;
          if (y < -0.85) {
            autoState = 3;
          }
        break;
      case 3:
          if (x > -0.85) {
            x -= 0.01*kSpeed;
          }
          if (y < 0.85) {
            y += 0.01*kSpeed;
          }
          if (x <= -0.85 && y >= 0.85) {
            autoState = 4;
          }
        break;
      case 4:
          y -= 0.01*kSpeed;
          if (y < -0.85) {
            autoState = 1;
            cycleCounter++;
          }
        break;
    }
}

void fullTest(){
  switch (fullTestState) {
    case 0:
      sweepTest();
      if(cycleCounter > 3){
        fullTestState = 1;
        cycleCounter = 0;
      }
      break;
    case 1:
      verticalTest();
      if(cycleCounter > 3){
        fullTestState = 2;
        cycleCounter = 0;
      }
      break;
    case 2:
      borderTest();
      if(cycleCounter > 3){
        fullTestState = 3;
        cycleCounter = 0;
      }
      break;
    case 3:
      infinityTest();
      if(cycleCounter > 3){
        fullTestState = 0;
        cycleCounter = 0;
      }
      break;
  }
}

void testingAuton(){
  switch (theAuton) {
    case 0:
      borderTest();
      break;
    case 1:
      sweepTest();
      break;
    case 2:
      verticalTest();
      break;
    case 3:
      infinityTest();
      break;
    case 4:
      fullTest();
      break;
    default:
      break;
  }
}

void GL_drawSquare(void) {

	glColor3f(red,green,blue);
	glBegin(GL_POLYGON);
    if(testFlag){
      testingAuton();
    }
		glVertex3f(-0.15+x-resizeW,0.0+y+resizeH,0.0);
		glVertex3f(0.15+x,0.0+y+resizeH,0.0);
    glVertex3f(0.15+x,0.15+y,0.0);
    glVertex3f(-0.15+x-resizeW,0.15+y,0.0);
	glEnd();

}

void GL_drawTriangle(){
  glColor3f(0.0,0.0,0.0);
  glBegin(GL_TRIANGLES);
    if(testFlag){
      testingAuton();
    }
    glVertex3f(0.0+x,0.15+y+resizeH,0.0);
    glVertex3f(-0.15+x-resizeW,0.0+y,0.0);
    glVertex3f(0.15+x+resizeW,0.0+y,0.0);
  glEnd();
}

void displayText(char *string, int row, int column) {
  int i;
  glColor3f(1.0,0.0,1.0);
  glRasterPos2f((20.0-column)/20.0,(12.0-row)/12.0 );

  i=0;
  do {
   glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i++]);
//	 glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i++]);
  } while (string[i] != '\0');
}

bool isRIncreasing = false,isGIncreasing = false,isBIncreasing = false;
bool isAngleInc = true;

void GL_display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0,1.0,1.0,1.0);
  glPushMatrix();
  glRotatef(angle,0.0,0.0,1.0);
  if(squareFlag) GL_drawSquare();
  if(triangleFlag) GL_drawTriangle();
  glColor3f(1.0,0.0,1.0);
//  if(isDisplayingText) displayText(string, 10, 10);
  GL_Periodic();
  // sprintf(string,"RED: %1.3f GREEN: %1.3f BLUE %1.3f",red,green,blue);
  // displayText(string,5,20);
  glPopMatrix();
  // if(isAngleInc)
  //   angle+=1;
  // else
  //   angle-=1;
  //
  // if(angle > 360) isAngleInc = false;
  // if(angle < 0) isAngleInc = true;
  // if(angle > 75.0 && angle < 280.0){
  //   red = 1.0;
  //   green = 0.0;
  //   blue = 1.0;
  // }else{
  //   red = 1.0;
  //   green = 1.0;
  //   blue = 0.0;
  // }
  glutSwapBuffers();
}



int main(int argc, char **argv){

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(600,600);

  glutCreateWindow("Servo Tracking Test");

  glutDisplayFunc(GL_display);
  glutReshapeFunc(GL_reshape);
  glutKeyboardFunc(GL_keyPressed);
  glutMouseFunc(GL_mouseHandler);
  glutMotionFunc(GL_dragHandler);
  glutKeyboardUpFunc(GL_keyUp);
  glutTimerFunc(1000,GL_timer,0);
  glutIdleFunc(GL_idle);

  glutMainLoop();

  return 0;
}
