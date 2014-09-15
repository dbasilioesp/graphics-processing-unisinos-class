//*****************************************************
//
// Casa.cpp 
// Um programa OpenGL simples que abre uma janela GLUT 
// e desenha uma casa.
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

GLsizei windowWidth = 1000;
GLsizei windowHeight = 600;
float aspectRadio;
float gridPoints = 100;
float gridWidth = windowWidth/gridPoints;
float gridHeight = windowHeight/gridPoints;

float PI = 3.14159;
float angle = 0.0;
float points = 100.0;
float slice = (2 * PI) / points;


void DesenhaGrid()
{
	glColor3ub(230, 230, 230);

	for (int i = 0.0; i < windowHeight; i += gridWidth)
	{
		glBegin(GL_LINES);
			glVertex2f(0, i);
			glVertex2f(windowWidth, i);
		glEnd();
	}
	
	for (int i = 0.0; i < windowWidth; i += gridHeight)
	{
		glBegin(GL_LINES);
			glVertex2f(i, 0);
			glVertex2f(i, windowHeight);
		glEnd();
	}
}

void DesenhaSquare(float x, float y, float width, float height)
{
	float x2 = x + width;
	float y2 = y+height;

	glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x2, y);
		glVertex2f(x2, y2);
		glVertex2f(x, y2);
	glEnd();
}

void DesenhaCircle(float radius, float x = 0, float y = 0, GLenum mode = GL_POLYGON)
{
	float pointX, pointY;
	angle = 0.0;
	glBegin(mode);
	while(angle < 2*PI)
	{
		pointX = radius * cos(angle);
		pointY = radius * sin(angle);
		glVertex3f(pointX + x, pointY + y, 0);
		angle += slice;
	}
	glEnd();
}

void DesenhaBackground()
{
	// Map
	glColor3ub(50, 230, 50);
	DesenhaSquare(0, 0, windowWidth, windowHeight);
	
	// Quartos
	glColor3ub(211, 182, 148);
	DesenhaSquare(5, 173, 337, 280);
	DesenhaSquare(229, 141, 113, 32);
	DesenhaSquare(342, 9, 189, 292);
	
	// Cozinha
	glColor3ub(220, 220, 228);
	DesenhaSquare(531, 9, 88, 292);
	DesenhaSquare(352, 298, 173, 86);

	// Banheiro
	glColor3ub(201, 179, 165);
	DesenhaSquare(5, 173, 119, 72);
}

void DesenhaParede(float x = 0, float y = 0, float size = 0, float angle = 0)
{
	glPushMatrix();

	float width, height;

	if(angle != 0) {
		height = gridWidth;
		x += height;
	} else {
		height = gridWidth;
	}

	if(size)
		width = size;
	else
		width = gridWidth;

	glTranslatef(x, y, 1);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex2f(0.0f,  0.0f);
		glVertex2f(size,  0.0f);
		glVertex2f(size,  height);
		glVertex2f(0.0f,  height);
	glEnd();

	glPopMatrix();
}

void DesenhaCamaSolteiro()
{
	glColor3ub(163, 180, 196);
	DesenhaSquare(0, 0, 47, 115);

	glColor3ub(235, 255, 255);
	glBegin(GL_QUADS);
		glVertex2f(0, 74);
		glVertex2f(47, 87);
		glVertex2f(47, 115);
		glVertex2f(0, 115);
	glEnd();

	glColor3ub(163, 180, 196);
	DesenhaSquare(5, 90, 37, 17);

	glColor3ub(120, 67, 49);
	DesenhaSquare(0, 113, 48, 2);
	DesenhaSquare(-2, 112, 5, 5);
	DesenhaSquare(43, 112, 5, 5);
}

void DesenhaCabeceiraCama()
{
	glColor3ub(224, 157, 112);
	DesenhaSquare(0, 0, 25, 29);

	glColor3ub(98, 111, 145);
	DesenhaCircle(10, 12, 14);

	glColor3ub(224, 157, 112);
	DesenhaCircle(1, 12, 14);

}

void DesenhaGuardaRoupa()
{
	glColor3ub(222, 166, 115);
	DesenhaSquare(0, 0, 31, 34);

	glColor3ub(196, 135, 88);
	glBegin(GL_LINES);
		glVertex2f(31.0f,  0.0f);
		glVertex2f(31.0f,  34.0f);
		glVertex2f(0.0f,  34.0f);
	glEnd();

	glColor3ub(136, 75, 28);
	glBegin(GL_LINES);
		
		glVertex2f(0.0f,  17.0f);
		glVertex2f(31.0f,  17.0f);

		glVertex2f(6.0f,  4.0f);
		glVertex2f(3.0f,  28.0f);

		glVertex2f(9.0f,  4.0f);
		glVertex2f(9.0f,  29.0f);

		glVertex2f(20.0f,  4.0f);
		glVertex2f(15.0f,  29.0f);

		glVertex2f(25.0f,  4.0f);
		glVertex2f(28.0f,  29.0f);

	glEnd();

	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
		glVertex2f(29.0f,  34.0f);
		glVertex2f(26.0f,  37.0f);
	glEnd();

}

void DesenhaEscrivaninha(bool mirrorX = false)
{
	float turnX = 1;
	if(mirrorX)
		turnX = -1;

	glColor3ub(200, 141, 97);
	glBegin(GL_QUADS);
		glVertex2f(0.0f,  21.0f);
		glVertex2f(29.0f * turnX,  0.0f);
		glVertex2f(29.0f * turnX,  94.0f);
		glVertex2f(0.0f,  94.0f);
	glEnd();
}

void DesenhaCadeiraEstofada()
{
	glColor3ub(103, 116, 151);
	DesenhaSquare(0, 0, 4, 25);
	glBegin(GL_QUADS);
		glVertex2f(5.0f,  2.0f);
		glVertex2f(30.0f,  0.0f);
		glVertex2f(30.0f,  25.0f);
		glVertex2f(5.0f,  23.0f);
	glEnd();
}

void DesenhaTapete()
{
	// Tapete
	glPushMatrix();
		glTranslatef(387, 162, 1);
		glColor3ub(254, 249, 207);
		DesenhaSquare(0, 0, 101, 124);
		glColor3ub(224, 212, 172);
		DesenhaSquare(17, 14, 68, 99);
		glColor3ub(254, 249, 207);
		DesenhaSquare(25, 20, 52, 87);
	glPopMatrix();
}

void DesenhaSofa()
{
	glColor3ub(247, 221, 170);
	DesenhaSquare(0, 0, 29, 33);
	DesenhaSquare(30, 0, 12, 33);

	glColor3ub(196, 135, 88);
	glBegin(GL_LINES);
		glVertex2f(-1.0f,  0.0f);
		glVertex2f(42.0f,  0.0f);
	glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex2f(-1.0f,  0.0f);
		glVertex2f(-1.0f,  33.0f);
		glVertex2f(29.0f,  33.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
		glVertex2f(29.0f,  0.0f);
		glVertex2f(29.0f,  33.0f);
		glVertex2f(42.0f,  33.0f);
		glVertex2f(42.0f,  0.0f);
	glEnd();
}

void DesenhaTV()
{
	glPushMatrix();
		glTranslatef(352, 231, 1);
		glColor3ub(222, 166, 115);
		DesenhaSquare(0, 0, 15, 63);
	glPopMatrix();

	// TV
	glPushMatrix();
		glTranslatef(349, 239, 1);
		glRotatef(-18, 0, 0, 1);
		glColor3ub(66, 69, 60);
		glBegin(GL_QUADS);
			glVertex2f(0.0f,  25.0f);
			glVertex2f(15.0f,  1.0f);
			glVertex2f(15.0f,  62.0f);
			glVertex2f(0.0f,  40.0f);
		glEnd();
		glColor3ub(108, 103, 109);
		DesenhaSquare(15, 1, 12, 61);
	glPopMatrix();
}

void DesenhaParedes()
{
	// Contorno
	DesenhaParede(5, 173, 227);
	DesenhaParede(5, 453, 80);
	DesenhaParede(227, 138, 45, 90.0f);
	DesenhaParede(227, 138, 120);
	DesenhaParede(342, 9, 129);
	DesenhaParede(342, 9, 172, 90.0f);
	DesenhaParede(515, 9, 111);
	DesenhaParede(618, 9, 299, 90.0f);
	DesenhaParede(448, 298, 81);
	DesenhaParede(342, 298, 15);
	DesenhaParede(342, 229, 234, 90);
	DesenhaParede(291, 453, 54);
	DesenhaParede(177, 453, 21);
	DesenhaParede(5, 453, 78);
	DesenhaParede(5, 173, 290, 90.0f);
	
	glBegin(GL_LINES);
		glVertex2f(82, 457);
		glVertex2f(176, 457);

		glVertex2f(197, 457);
		glVertex2f(291, 457);

		glVertex2f(52, 182);
		glVertex2f(52, 217);

		glVertex2f(55, 210);
		glVertex2f(55, 247);

		glVertex2f(360, 301);
		glVertex2f(407, 301);

		glVertex2f(365, 304);
		glVertex2f(412, 304);
	glEnd();

	// Interno
	DesenhaParede(5, 246, 135);
	DesenhaParede(125, 173, 36, 90.0f);
	DesenhaParede(125, 242, 10);
	DesenhaParede(183, 229, 233, 90);
	DesenhaParede(183, 229, 15);
	DesenhaParede(179, 246, 10);
	DesenhaParede(235, 229, 112);
	DesenhaParede(521, 9, 84, 90);
	DesenhaParede(521, 140, 168, 90);

	glColor3ub(248, 239, 224);
	glBegin(GL_LINE_STRIP);
		glVertex2f(352, 384);
		glVertex2f(525, 384);
		glVertex2f(525, 308);
	glEnd();

}

void DesenhaCabeceiras()
{
	// Cabeceiras
	glPushMatrix();
		glTranslatef(16, 310, 1);
		DesenhaCabeceiraCama();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(16, 424, 1);
		DesenhaCabeceiraCama();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(244, 424, 1);
		glScalef(1.9, 1, 1);
		DesenhaCabeceiraCama();
	glPopMatrix();
}

void DesenhaGuardaRoupas()
{
	// Guarda Roupa
	glPushMatrix();
		glTranslatef(15, 256, 1);
		DesenhaGuardaRoupa();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(46, 256, 1);
		DesenhaGuardaRoupa();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(77, 256, 1);
		DesenhaGuardaRoupa();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(108, 256, 1);
		DesenhaGuardaRoupa();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(311, 239, 1);
		DesenhaGuardaRoupa();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(280, 239, 1);
		DesenhaGuardaRoupa();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(249, 239, 1);
		DesenhaGuardaRoupa();
	glPopMatrix();
}

void DesenhaEscrivaninhas()
{
	glPushMatrix();
		glTranslatef(154, 357, 1);
		DesenhaEscrivaninha();

		glColor3ub(91, 119, 169);
		DesenhaCircle(6, 15, 47);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(223, 281, 1);
		glScalef(1, 0.55, 1);
		DesenhaEscrivaninha(true);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(192, 295, 1);
		glColor3ub(255, 255, 255);
		DesenhaSquare(3, 10, 27, 20);
	glPopMatrix();
}

void DesenhaCadeirasEstofadas()
{

	glPushMatrix();
		glTranslatef(136, 415, 1);
		glRotatef(-30, 0, 0, 1);
		DesenhaCadeiraEstofada();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(245, 325, 1);
		glRotatef(180, 0, 0, 1);
		DesenhaCadeiraEstofada();
	glPopMatrix();
}

void DesenhaSofas()
{
	glPushMatrix();
		glTranslatef(478, 261, 1);
		DesenhaSofa();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(478, 227, 1);
		DesenhaSofa();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(478, 193, 1);
		DesenhaSofa();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(436, 175, 1);
		glRotatef(-90, 0, 0, 1);
		DesenhaSofa();
	glPopMatrix();
}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	
	DesenhaBackground();
	//DesenhaGrid();

	DesenhaParedes();

	// Cama de Casal
	glColor3ub(232, 148, 146);
	DesenhaSquare(16, 340, 115, 83);
	glColor3ub(225, 192, 122);
	DesenhaSquare(25, 347, 13, 32);
	DesenhaSquare(25, 384, 13, 32);

	// Camas de Solteiro
	glPushMatrix();
		glTranslatef(195, 336, 1);
		DesenhaCamaSolteiro();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(294, 336, 1);
		DesenhaCamaSolteiro();
	glPopMatrix();

	DesenhaCabeceiras();
	
	DesenhaGuardaRoupas();

	DesenhaCadeirasEstofadas();

	DesenhaEscrivaninhas();

	DesenhaTapete();

	DesenhaSofas();

	// Mesa
	glPushMatrix();
		glTranslatef(418, 77, 1);
		glColor3ub(218, 226, 231);
		DesenhaCircle(40, 0, 0);
		glColor3ub(98, 71, 50);
		DesenhaCircle(40, 0, 0, GL_LINE_LOOP);
	glPopMatrix();

	DesenhaTV();

	// Executa os comandos OpenGL 
	glFlush();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;

	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;
	aspectRadio = (float) altura/largura;
	
	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D (0.0f, windowWidth, windowHeight, 0.0f);
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// Programa Principal 
int main(void)
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(windowWidth, windowHeight);
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Desenho de uma casa");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);
    
	// Chama a função responsável por fazer as inicializações 
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
