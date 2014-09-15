#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>


using namespace std;


GLsizei largura, altura;
float taxaScrollX = 0.5;
float taxaScrollY = 0.5;
int observadorX = 0;
int observadorY = 0;
float aspectRatio = 0;
float orthoPoints = 10.0;


// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior, 
	// superior) mantendo a proporção com a janela de visualização
	float deslocamentoX = observadorX*taxaScrollX;
	float deslocamentoY = observadorY*taxaScrollY;
	aspectRatio = altura/largura;

	if (largura <= altura) 
		gluOrtho2D (-orthoPoints + deslocamentoX,  orthoPoints+ deslocamentoX, (-orthoPoints + deslocamentoY)*aspectRatio, (orthoPoints + deslocamentoY) *aspectRatio);
	else 
		gluOrtho2D ((-orthoPoints+ deslocamentoX)*aspectRatio, (orthoPoints + deslocamentoX)*aspectRatio, -orthoPoints + deslocamentoY, orthoPoints + deslocamentoY);

	
	// Desenha uma casinha composta de um quadrado e um triângulo
	glViewport(0, 0, largura, altura);
	// Altera a cor do desenho para azul
	glColor3f(0.4f, 1.0f, 0.4f);
	
	// Desenha a casa
	glBegin(GL_QUADS);
		glVertex2f(-90.0f, -30.0f);
		glVertex2f(-90.0f, -15.0f);       
		glVertex2f( 90.0f, -15.0f);       
		glVertex2f( 90.0f, -30.0f);
	glEnd();
	
	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);

	// Desenha a casa
	glBegin(GL_QUADS);
		glVertex2f(-15.0f,-15.0f);
		glVertex2f(-15.0f,  5.0f);       
		glVertex2f( 15.0f,  5.0f);       
		glVertex2f( 15.0f,-15.0f);
	glEnd();

	// Altera a cor do desenho para branco
	glColor3f(1.0f, 1.0f, 1.0f);  
	// Desenha a porta e a janela  
	glBegin(GL_QUADS);
		glVertex2f(-4.0f,-14.5f);
		glVertex2f(-4.0f,  0.0f);       
		glVertex2f( 4.0f,  0.0f);       
		glVertex2f( 4.0f,-14.5f);       
		glVertex2f( 7.0f,-5.0f);
		glVertex2f( 7.0f,-1.0f);       
		glVertex2f(13.0f,-1.0f);       
		glVertex2f(13.0f,-5.0f);             
	glEnd();

	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);     
	// Desenha as "linhas" da janela
	glBegin(GL_LINES);
		glVertex2f( 7.0f,-3.0f);
		glVertex2f(13.0f,-3.0f);
		glVertex2f(10.0f,-1.0f);
		glVertex2f(10.0f,-5.0f);      
	glEnd();

	// Altera a cor do desenho para vermelho
	glColor3f(1.0f, 0.0f, 0.0f); 
	// Desenha o telhado
	glBegin(GL_TRIANGLES);
		glVertex2f(-15.0f, 5.0f);   
		glVertex2f(  0.0f,17.0f);    
		glVertex2f( 15.0f, 5.0f);       
	glEnd();
 
	// Executa os comandos OpenGL 
	glFlush();
	
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{

	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;

	// Especifica as dimensões da Viewport
	//glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char tecla, int x, int y)
{
	if (tecla == 27)
		exit(0);
}

//Função callback para eventos de teclas especiais
void TecladoEspecial(int key, int x, int y)
{
	switch(key)
	{
		
		case GLUT_KEY_LEFT:		observadorX--;
			cout<< observadorX << "\n";
								break;
		case GLUT_KEY_RIGHT:	observadorX++;
			cout<< observadorX << "\n";
								break;
			case GLUT_KEY_UP:	observadorY++;
			cout<< observadorX << "\n";
								break;
		case GLUT_KEY_DOWN:	observadorY--;
			cout<< observadorX << "\n";
								break;
	}
	glutPostRedisplay();
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
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Exemplo simples de scrolling");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Registra a função callback de teclas especiais
	glutSpecialFunc(TecladoEspecial);

    
	// Chama a função responsável por fazer as inicializações 
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}