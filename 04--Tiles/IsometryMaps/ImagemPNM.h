#ifndef IMAGEM_PNM_H
#define IMAGEM_PNM_H

#include "Imagem.h"

#include <cstdio>

class ImagemPNM
{

public:
	ImagemPNM() { imagem = NULL; altura = 0; largura = 0;}
	~ImagemPNM() {;}

	void LePNM(char *nomeDoArquivo);
	void CriaPNM(char *nomeDoArquivo);
	void ConverteGrayscale();
	void Coloriza(int r, int g, int b);
	void Inverte();
	void Binariza(int k);
	void TransformaMarioEmLuigi();

	Imagem *RetornaImagem() 
	{
		return imagem;
	}
	void RecebeImagem(Imagem *im, int a, int l)
	{
		imagem = im;
		altura = a;
		largura = l;
	}
	int RetornaLargura() { return largura; }
	int RetornaAltura() { return altura; }

private:
	Imagem *imagem;
	int altura, largura;

};

#endif