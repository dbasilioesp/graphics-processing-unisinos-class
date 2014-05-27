#include "ImagemPNM.h"

#include <iostream>
#include <fstream>

#define BUFF_SIZE 500

using namespace std;

void ImagemPNM::LePNM(char *nomeDoArquivo)
{

	cout << "Lendo a imagem " << nomeDoArquivo << "\n";
	 // Tenta abrir o arquivo...
    ifstream input(nomeDoArquivo, ios::in);
    if (!input) {
        cerr << "Arquivo "<< nomeDoArquivo << " não pode ser aberto!\n";
        exit(1);
    }

    // Cabeçalho, considerando este formato:
    // Px
    // # comentario
    // Width Height
    // 255

   char buffer[BUFF_SIZE];
   input.getline(buffer,BUFF_SIZE); //pega a linha com o Px
   input.getline(buffer,BUFF_SIZE); //pega a linha com o comentário

    // Pega a altura e a largura
   input >> largura;
   input >> altura;
   cout << "Resolucao " << largura << " X " << altura << "\n";
   
   imagem = new Imagem(largura,altura);

   int max;
   input >> max; //pega o MAX GREY (que pra nós não precisa agora)

   int x=0, y=altura;

   // Percorre os pixels -- lê o y invertido para desenhar certo depois com o glDrawPixels
   for(int y = altura-1; y >= 0; y--)
	   for (int x = 0; x < largura; x++)
	   {
			int r, g, b,a;
			input >> r;
			input >> g;
			input >> b;
			//cout << r << " " << g << " " << b << "\n";
			
			if (r == 255 && g == 0 && b == 255)
				a = 0;
			else a = 255;
			int rgb = (a << 24) | (b << 16) | (g << 8) | r;
			//int rgb = (a << 24) | (r << 16) | (g << 8) | b;
			imagem->setRGB(x, y, rgb);
	   }
	cout << "Leitura realizada com sucesso! \n";
}

void ImagemPNM::CriaPNM(char *nomeDoArquivo)
{
	ofstream arq(nomeDoArquivo, ios::out | ios::binary);

    arq << "P3" << endl;
	arq << "# Criado na aula de Processamento Gráfico ;)" << endl;
    arq << largura << " " << altura << endl;
    arq << 255 << endl;

	for(int i=0; i<altura; i++)
		for(int j=0;  j<largura; j++) {
			int pixel = imagem->getRGB(j,i);
			int b = (pixel >> 16) & 255;
			int g = (pixel >> 8) & 255;
			int r = (pixel) & 255;
			arq << r << " " << g << " " << b << "\n";
		}
	arq.close();
}

void ImagemPNM::TransformaMarioEmLuigi(){

	for(int i=0; i < altura; i++)
		for(int j=0;  j < largura; j++) {
			int pixel = imagem->getRGB(j,i);
			int b = (pixel >> 16) & 255;
			int g = (pixel >> 8) & 255;
			int r = (pixel) & 255;
			
			if(r <= 255 && g <= 100 && b <= 100){
				r = 0;
				g = 255;

				pixel = (b << 16) | (g << 8) | r;

				imagem->setRGB(j, i, pixel);
			}

		}

}

void ImagemPNM::ConverteGrayscale(){

	for(int i=0; i < altura; i++)
		for(int j=0;  j < largura; j++) {
			int pixel = imagem->getRGB(j,i);
			int b = (pixel >> 16) & 255;
			int g = (pixel >> 8) & 255;
			int r = (pixel) & 255;
			
			// r = r*0.333 + g*0.333 + b*0.333;
			int rgb = r*0.2125 + g*0.7154 + b*0.0721;
			r = rgb;
			g = rgb;
			b = rgb;

			pixel = (b << 16) | (g << 8) | r;
			imagem->setRGB(j, i, pixel);
		}

}


void ImagemPNM::Coloriza(int r, int g, int b){

	int rgbModifier = (b << 16) | (g << 8) | r;

	for(int i=0; i < altura; i++)
		for(int j=0;  j < largura; j++) {
			int pixel = imagem->getRGB(j,i);
			pixel = pixel | rgbModifier;
			imagem->setRGB(j, i, pixel);
		}

}

void ImagemPNM::Inverte(){

	for(int i=0; i < altura; i++)
		for(int j=0;  j < largura; j++) {
			int pixel = imagem->getRGB(j,i);
			
			// Mode 1
			// 2^32 = 4294967296
			pixel = pixel ^ 4294967295;

			// Mode 2
			/*
			int b = (pixel >> 16) & 255;
			int g = (pixel >> 8) & 255;
			int r = (pixel) & 255;
			r = r ^ 255;
			g = g ^ 255;
			b = b ^ 255;
			pixel = (b << 16) | (g << 8) | r;
			*/

			imagem->setRGB(j, i, pixel);
		}

}
