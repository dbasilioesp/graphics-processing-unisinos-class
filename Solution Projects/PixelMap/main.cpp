#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

// Globals
int windowWidth;
int windowHeight;
float aspectRadio;

struct MyPixel {
	int r;
	int g;
	int b;
};

MyPixel ** image;

void readImage(void)
{
	ifstream file;
	file.open("penguins.ppm");
	
	if(file.is_open())
	{
		string token;
		int rangeColors;

		// PS3
		file >> token;
		// Size
		file >> windowWidth;
		file >> windowHeight;
		file >> rangeColors;
		
		image = new MyPixel*[windowHeight];

		for (int i = 0; i < windowHeight; i++)
		{
			image[i] = new MyPixel[windowWidth];
			
			for (int j = 0; j < windowWidth; j++)
			{
				file >> image[i][j].r;
				file >> image[i][j].g;
				file >> image[i][j].b;
			}
		}

		file.close();
	}

}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < windowHeight; i++)
		for (int j = 0; j < windowWidth; j++){

			if(image[i][j].b > 100){
				image[i][j].b -= 100;
			}

			glColor3ub(image[i][j].r, image[i][j].g, image[i][j].b);
			glBegin(GL_POINTS);
				glVertex2i(j, i);
			glEnd();

		}

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

	// Estabelece a janela de seleção (esquerda, direita, inferior, 
	// superior) mantendo a proporção com a janela de visualização
	/*if (largura <= altura)
		gluOrtho2D (0.0f, windowWidth, windowHeight * aspectRadio, 0.0f);
	else 
		gluOrtho2D (0.0f, windowWidth * aspectRadio, windowHeight, 0.0f);*/
	
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

	readImage();

	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(windowWidth, windowHeight); 
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Reading Image");

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