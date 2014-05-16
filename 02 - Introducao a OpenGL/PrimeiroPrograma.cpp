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
	// Limpa a janela de visualização com a cor branca
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Define a cor de desenho: azul
	glColor3f(0,0,1);
	glPointSize(5);

	// Desenha um triângulo no centro da janela
	glBegin(GL_LINE_LOOP);
		glVertex3f(-0.5,-0.5,0);
		glVertex3f( 0.0, 0.5,0);
		glVertex3f( 0.5,-0.5,0);
	glEnd();

	// Define a cor de desenho: verde
	glColor3f(0,1,0);
	
	// Desenha um triângulo no centro da janela
	glBegin(GL_POINTS);
		glVertex3f(-0.2,-0.2,0);
		glVertex3f( 0.0, 0.2,0);
		glVertex3f( 0.2,-0.2,0);

		// Define a cor de desenho: verde
		glColor3f(1,0,0);

		glVertex3f(-0.1,-0.1,0);
		glVertex3f( 0.0, 0.1,0);
		glVertex3f( 0.1,-0.1,0);
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
	gluOrtho2D(-1.0,1.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal 
int main(void)
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
 
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(400,400); 
 
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
 
	return 0;
}