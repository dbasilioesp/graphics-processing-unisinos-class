#include <stdlib.h>
#include <GL/glut.h>


using namespace std;


// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor branca
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Define a cor de desenho: azul
	glColor3f(0,0,1);
	glPointSize(5);

	// Desenha um tri�ngulo no centro da janela
	glBegin(GL_LINE_LOOP);
		glVertex3f(-0.5,-0.5,0);
		glVertex3f( 0.0, 0.5,0);
		glVertex3f( 0.5,-0.5,0);
	glEnd();

	// Define a cor de desenho: verde
	glColor3f(0,1,0);
	
	// Desenha um tri�ngulo no centro da janela
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

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa(void)
{
	// Define a janela de visualiza��o 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1.0,1.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal 
int main(void)
{
	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
 
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(400, 600); 
 
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Primeiro Programa");
 
	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();
 
	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();
 
	return 0;
}