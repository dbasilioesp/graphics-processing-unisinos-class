#ifndef IMAGEM_PNM_H
#define IMAGEM_PNM_H

#include "Image.h"

#include <cstdio>

class ImagePNM
{

public:
	ImagePNM() { imagem = NULL; altura = 0; largura = 0;}
	~ImagePNM() {;}

	void LePNM(char *nomeDoArquivo);
	void LePNMTransparent(char *nomeDoArquivo);
	void CriaPNM(char *nomeDoArquivo);
	void ConverteGrayscale();
	void Coloriza(int r, int g, int b);
	void Inverte();
	void Binariza(int k);
	void TransformaMarioEmLuigi();

	Image *RetornaImagem() 
	{
		return imagem;
	}

	void RecebeImagem(Image *im, int a, int l)
	{
		imagem = im;
		altura = a;
		largura = l;
	}

	int RetornaLargura() { return largura; }
	int RetornaAltura() { return altura; }

private:
	Image *imagem;
	int altura, largura;

};

#endif