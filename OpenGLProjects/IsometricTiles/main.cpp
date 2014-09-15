#include "ImagePNM.h"

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <GL/glut.h>

using namespace std;


struct Player {
	int x;
	int y;
};


int largura=640, altura=480;

ImagePNM tiles[5];
Player player;

void DesenhaImagem(Image *imagem, int x, int y)
{
	//Habilita a transparência na OpenGL
	glEnable(GL_BLEND);
	
	//Especifica o tipo de função de transparência
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Informa como vai ser feito o alinhamento dos pixels em memória (por byte)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Desenha o array de pixels
	if(imagem != NULL){
	    // Use Window coordinates to set raster position
		glRasterPos2i(x, y + imagem->getHeight());

		glDrawPixels(imagem->getWidth(), imagem->getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, imagem->getPixels());
	}
}


void SlideMap(){

	int tileset[] = {
		0, 0, 0,
		1, 1, 1,
		0, 0, 0,
		1, 1, 1,
	};

	int tileCounter = 0;
	int tileIndex = 0;
	int tileHeight = 0;
	int tileWidth = 0;

	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 3; x++){

			tileIndex = tileset[tileCounter];

			tileWidth = tiles[tileIndex].RetornaLargura();
			tileHeight = tiles[tileIndex].RetornaAltura();
			
			DesenhaImagem(tiles[tileIndex].RetornaImagem(), 
						  50 + (x * tileWidth) + (y * (tileWidth/2)), 
						  50 +  y * (tileHeight/2));
			tileCounter++;
		}
	}


	tileWidth = tiles[2].RetornaLargura();
	tileHeight = tiles[2].RetornaAltura();

	DesenhaImagem(tiles[2].RetornaImagem(), 
				  50 + (player.x * tileWidth) + (player.y * (tileWidth/2)),
				  50 +  player.y * (tileHeight/2));

	/*DesenhaImagem(tiles[0].RetornaImagem(), 0, 0);
	DesenhaImagem(tiles[1].RetornaImagem(), 1 * 75, 0);
	DesenhaImagem(tiles[2].RetornaImagem(), 75 / 2, 50 / 2);*/

}


void StaggeredMap(){

	int tileset[] = {
		0, 0, 0,
		1, 1, 1,
		0, 0, 0,
		1, 1, 1,
	};

	int tileCounter = 0;
	int tileIndex = 0;
	int tileHeight = 0;
	int tileWidth = 0;

	int pixelX = 0;
	int pixelY = 0;

	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 3; x++){

			tileIndex = tileset[tileCounter];

			tileWidth = tiles[tileIndex].RetornaLargura();
			tileHeight = tiles[tileIndex].RetornaAltura();
			
			if(y % 2 == 0){
				pixelX = x * tileWidth;
			} else {
				pixelX = (x * tileWidth) + (tileWidth / 2);
			}

			pixelY = y * tileHeight / 2;

			DesenhaImagem(tiles[tileIndex].RetornaImagem(), pixelX + 50, pixelY + 50);
			tileCounter++;
		}
	}

	tileWidth = tiles[2].RetornaLargura();
	tileHeight = tiles[2].RetornaAltura();

	if(player.y % 2 == 0){
		pixelX = player.x * tileWidth;
	} else {
		pixelX = (player.x * tileWidth) + (tileWidth / 2);
	}

	pixelY = player.y * tileHeight / 2;

	DesenhaImagem(tiles[2].RetornaImagem(), pixelX + 50, pixelY + 50);

}


void DiamondMap(){

	int tileset[] = {
		0, 0, 0,
		1, 1, 1,
		0, 0, 0,
		1, 1, 1,
	};

	int tileCounter = 0;
	int tileIndex = 0;
	int tileHeight = 0;
	int tileWidth = 0;

	int pixelX = 0;
	int pixelY = 0;

	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 3; x++){

			tileIndex = tileset[tileCounter];

			tileWidth = tiles[tileIndex].RetornaLargura();
			tileHeight = tiles[tileIndex].RetornaAltura();
			
			pixelX = (x - y) * tileWidth / 2;
			pixelY = (x + y) * tileHeight / 2;

			DesenhaImagem(tiles[tileIndex].RetornaImagem(), pixelX + 250, pixelY + 150);
			tileCounter++;
		}
	}

	tileWidth = tiles[2].RetornaLargura();
	tileHeight = tiles[2].RetornaAltura();

	pixelX = (player.x - player.y) * tileWidth / 2;
	pixelY = (player.x + player.y) * tileHeight / 2;

	DesenhaImagem(tiles[2].RetornaImagem(), 250 + pixelX, 150 + pixelY);

}


void UpadateKeySlideMovement(unsigned char key = ' ')
{
	
	switch(key){
		case 'w': // NORTH EAST
			player.x += 1;
			player.y -= 1;
			break;
		case 'a': // NORTH WEST
			player.y -= 1;
			break;
		case 'd': // SOUTH EAST
			player.y += 1;
			break;
		case 's': // SOUTH WEST
			player.x -= 1;
			player.y += 1;
			break;
	}
	
}


void UpadateKeyStaggeredMovement(unsigned char key = ' ')
{
	
	bool pair = player.y % 2 == 0 ? true : false;

	switch(key){
		case 'w': // NORTH EAST
			if(pair){
				player.y -= 1;
			} else {
				player.x += 1;
				player.y -= 1;
			}
			
			break;
		case 'a': // NORTH WEST
			if(pair){
				player.x -= 1;
				player.y -= 1;
			} else {
				player.y -= 1;
			}
			break;
		case 'd': // SOUTH EAST
			if(pair){
				player.y += 1;
			} else {
				player.x += 1;
				player.y += 1;
			}
			
			break;
		case 's': // SOUTH WEST
			if(pair){
				player.x -= 1;
				player.y += 1;
			} else {
				player.y += 1;
			}
			break;
	}
	
}


void UpadateKeyDiamondMovement(unsigned char key = ' ')
{
	
	switch(key){
		case 'w': // NORTH EAST
			player.y -= 1;
			break;
		case 'a': // NORTH WEST
			player.x -= 1;
			break;
		case 'd': // SOUTH EAST
			player.x += 1;
			break;
		case 's': // SOUTH WEST
			player.y += 1;
			break;
	}
	
}


void ReshapeFunc(int w, int h){
    
    if(h == 0)
        h = 1;

	largura = w;
	altura= h;
  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
    glViewport(0, 0, largura, altura);
    gluOrtho2D(0.0f, (GLfloat) largura, (GLfloat) altura, 0.0);
        
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void DisplayFunc(void)
{

	// Limpa a janela de visualização com a cor branca
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);

	// SlideMap();

	// StaggeredMap();

	DiamondMap();

	//Executa os comandos OpenGL 
	glFlush();
}


void KeyboardFunc(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);

	// UpadateKeySlideMovement(key);
	
	// UpadateKeyStaggeredMovement(key);
	
	UpadateKeyDiamondMovement(key);

	glFlush();
	glutPostRedisplay();
}


int main(void)
{
	player.x = 1;
	player.y = 1;

	tiles[0].LePNMTransparent("tile1.ppm");
	tiles[1].LePNMTransparent("tile2.ppm");
	tiles[2].LePNMTransparent("tile3.ppm");

	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(largura, altura); 
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("SlideMap, StaggeredMap, Diamond");
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(DisplayFunc);

	// Registra a função callback de ajuste de tamanho da janela de visualização
	glutReshapeFunc(ReshapeFunc);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (KeyboardFunc);

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
 
	return 0;
}