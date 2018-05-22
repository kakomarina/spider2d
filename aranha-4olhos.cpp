#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h> 
#include <cstdlib> 

GLint WINDOW_WIDTH  = 500,
      WINDOW_HEIGHT = 500;

GLfloat raio1 = 40;
GLfloat raio2 = raio1/1.5; 
GLfloat xA = 250, xB = xA;
GLfloat yA = 100, yB = yA + raio1 + raio2;
GLfloat movimento = 0;
bool andando = false;
GLfloat rotpers = 2.0;

GLfloat xZ = xA, yZ = yB; 

int tempo_ant; 
float pxpers = 200; 

typedef struct{

}ARANHA;
      
void init();      
void draw_test();

void mouse_test(GLint button, GLint action, GLint x, GLint y);
void mouse_test2(GLint x, GLint y);
void mouse_test3(GLint x, GLint y);

void keybord_test(GLubyte key, GLint x, GLint y);
void keybord_test2(GLint key, GLint x, GLint y);

void anima();


int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  
  GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),
        screen_height = glutGet(GLUT_SCREEN_HEIGHT);  
  
  glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_WIDTH) / 2);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
  glutCreateWindow("A dona aranha subiu pela parede");
  
  tempo_ant = glutGet(GLUT_ELAPSED_TIME);
  init();
  glutDisplayFunc(draw_test);
  glutIdleFunc(anima);
  glutMouseFunc(mouse_test);
  
  glutMainLoop();
  
  
  return EXIT_SUCCESS;
}


void init(){
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  
  gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int triangleAmount = 30; //numero de triangulos
	
	GLfloat doisPi = 2.0f * M_PI;
	
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); 	//centro
	for(i = 0; i <= triangleAmount;i++) { 
		glVertex2f(
	            x + (radius * cos(i *  doisPi / triangleAmount)), 
			    y + (radius * sin(i * doisPi / triangleAmount))
		);
	}
	glEnd();
}

void drawPerninhas(GLfloat width, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2){
	
	glLineWidth(width); 
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0.0);
	glVertex3f(x1, y1, 0);
	glVertex3f(x2, y2, 0);
	glEnd();
}

float alfa; 

void draw_test(){
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(139, 69, 19);	//marrom

    glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();
 	
 	glTranslatef(xA, yA, 0);
	glRotatef(alfa, 0, 0, 1.0);


	//Perna 1 direita
	glPushMatrix(); 
	glTranslatef(raio1*cos(M_PI/3), raio1*sin(M_PI/3), 0); 
	float teta = sin(movimento * 2 * M_PI);
	glRotatef(teta * 15, 0, 0, 1);
	drawPerninhas(4, 40, 50, 60, 35); 
	glPopMatrix();

	//Perna 2 direita
	glPushMatrix();
	glTranslatef(raio1*cos(M_PI/4), raio1*sin(M_PI/4), 0);
	teta = sin(movimento * 2 * M_PI);
	glRotatef(-teta * 7.5, 0, 0, 1);
	drawPerninhas(4, 45, 25, 60, 5); 
	glPopMatrix();	

	// Perna 1 esquerda
	glPushMatrix();
	glTranslatef(-raio1*cos(M_PI/3), raio1*sin(M_PI/3), 0);
	teta = sin(movimento * 2 * M_PI);
	glRotatef(teta * 15, 0, 0, 1);
	drawPerninhas(4, -40, 50, -60, 35); 
	glPopMatrix();

	// Perna 2 esquerda
	glPushMatrix();
	glTranslatef(-raio1*cos(M_PI/4), raio1*sin(M_PI/4), 0);
	teta = sin(movimento * 2 * M_PI);
	glRotatef(-teta * 7.5, 0, 0, 1);
	drawPerninhas(4, -45, 25, -60, 5); 
	glPopMatrix();	
 
 	//Perna 3 direita
 	glPushMatrix();
	glTranslatef(raio1*cos(M_PI/13), raio1*sin(M_PI/13), 0);
	teta = sin(movimento * 2 * M_PI);
	glRotatef(-teta * 15, 0, 0, 1);
	drawPerninhas(4, 45, 0, 60, -20); 
	glPopMatrix();

	//Perna 4 direita
 	glPushMatrix();
	glTranslatef(raio1*cos(-M_PI/7), raio1*sin(-M_PI/7), 0);
	teta = sin(movimento * 2 * M_PI);
	glRotatef(teta * 7.5, 0, 0, 1);
	drawPerninhas(4, 40, -15, 50, -45); 
	glPopMatrix();


	//Perna 3 esquerda
 	glPushMatrix();
	glTranslatef(-raio1*cos(M_PI/13), raio1*sin(M_PI/13), 0);
	teta = sin(movimento * 2 * M_PI);
	glRotatef(-teta * 15, 0, 0, 1);
	drawPerninhas(4, -45, 0, -60, -20); 
	glPopMatrix();

	//Perna 4 esquerda
 	glPushMatrix();
	glTranslatef(-raio1*cos(-M_PI/7), raio1*sin(-M_PI/7), 0);
	teta = sin(movimento * 2 * M_PI);
	glRotatef(teta * 7.5, 0, 0, 1);
	drawPerninhas(4, -40, -15, -50, -45); 
	glPopMatrix();


	//Desenhando a aranha
	drawFilledCircle(0, 0, raio1); //corpo
	drawFilledCircle(0, raio1+raio2, raio2); //cabeca
	glColor3ub(0, 0, 0); //cor preta
	drawFilledCircle(-5, raio1+raio2+12, 4); //olho 1 
	drawFilledCircle(5, raio1+raio2+12, 4); //olho 2
	drawFilledCircle(-15, raio1+raio2+5, 3); //olho 3 
	drawFilledCircle(15, raio1+raio2+5, 3); //olho 4

	



	glFlush();
}


void anima(){


	int tempo_novo = glutGet(GLUT_ELAPSED_TIME);

	int dt = tempo_novo - tempo_ant;

	if(dt == 0) return; 

	float vA = xZ - xA, vB = yZ - yA; 			//vetor direcao
	float norma = sqrt(vA*vA + vB*vB);	
	if(andando){  
		vA = vA/norma;
		vB = vB/norma; 
	
		float px = pxpers/1000 * dt;
		if(px > norma){
			xA = xZ;
			yA = yZ; 
			xB = xA; 
			yB = yA + (raio1+raio2);
			andando = false;
			movimento = 0;
		}else{
			vA = vA * px; 
			vB = vB * px; 

			xA = xA + vA;
			yA = yA + vB; 
			xB = xA; // move cabeca
			yB = yA + (raio1 + raio2); // move cabeca 
			movimento = fmod(movimento + dt/1000.0 * rotpers, 1);
		}
		
	} 


	tempo_ant = tempo_novo;
	glutPostRedisplay();


}


void mouse_test(GLint button, GLint action, GLint x, GLint y){


	if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
	
 		xZ = x; 
 		yZ = WINDOW_HEIGHT - y; 

	 	float dx = xZ-xA; 
 		float dy = yZ-yA; 
		float norma = sqrt(dy*dy + dx*dx);


		if(norma > 1){
			alfa = atan2(dy, dx);
			alfa = alfa * 180/M_PI - 90;
			andando = true;	
		}

		glutPostRedisplay();
	} 
}


