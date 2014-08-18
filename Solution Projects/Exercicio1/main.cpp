//*****************************************************
//
// PrimeiroPrograma.cpp
// Um programa OpenGL simples que abre uma janela GLUT
// e desenha um triângulo no centro
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
// Adaptado por Rossana B. Queiroz 08/2011
//
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>


// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// http://codepen.io/mattboldt/pen/LjJAt

	// Limpa a janela de visualização com a cor branca
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Define a cor de desenho: azul
	glColor3f(0,0,1);
	glPointSize(5);

	// Background Left
	glBegin(GL_POLYGON);
		glColor3ub(243, 214, 87);
		glVertex3f(-100, -100, 0);
		glVertex3f(   0, -100, 0);
		glVertex3f(   0,  100, 0);
		glVertex3f(-100,  100, 0);
	glEnd();

	// Background Right
	glBegin(GL_POLYGON);
		glColor3ub(207, 79, 140);
		glVertex3f(   0, -100, 0);
		glVertex3f( 100, -100, 0);
		glVertex3f( 100,  100, 0);
		glVertex3f(   0,  100, 0);
	glEnd();

	// Third Square
	glBegin(GL_POLYGON);
		glColor3ub(245, 245, 245);
		glVertex3f(-40, -40, 0);
		glVertex3f( 40, -40, 0);
		glVertex3f( 40,  40, 0);
		glVertex3f(-40,  40, 0);
	glEnd();

	// Second Square
	glBegin(GL_POLYGON);
		glColor3ub(230, 230, 230);
		glVertex3f(-20, -20, 0);
		glVertex3f( 20, -20, 0);
		glVertex3f( 20,  20, 0);
		glVertex3f(-20,  20, 0);
	glEnd();
	
	// First Square
	glBegin(GL_POLYGON);
		glColor3ub(245, 245, 245);
		glVertex3f(-10, -10, 0);
		glVertex3f( 10, -10, 0);
		glVertex3f( 10,  10, 0);
		glVertex3f(-10,  10, 0);
	glEnd();

	// Cable
	glBegin(GL_POLYGON);
		glColor3ub(245, 245, 245);
		glVertex3f(-10, -40, 0);
		glVertex3f(-10, -60, 0);
		glVertex3f( 10, -60, 0);
		glVertex3f( 10, -40, 0);
	glEnd();

	// Iron
	glBegin(GL_POLYGON);
		glColor3ub( 240, 240, 240);
		glVertex3f( -5, -60, 0);
		glVertex3f( -5, -80, 0);
		glVertex3f( -3, -80, 0);
		glVertex3f( -3, -90, 0);
		glVertex3f( -1, -90, 0);
		glVertex3f( -1, -95, 0);
		glVertex3f(  1, -95, 0);
		glVertex3f(  1, -90, 0);
		glVertex3f(  3, -90, 0);
		glVertex3f(  3, -80, 0);
		glVertex3f(  5, -80, 0);
		glVertex3f(  5, -60, 0);
	glEnd();

	//Executa os comandos OpenGL 
	glFlush();
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa(void)
{
	// Define a janela de visualização 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal 
void main(void)
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
 
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(400, 400); 
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Primeiro Programa");
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
 
}