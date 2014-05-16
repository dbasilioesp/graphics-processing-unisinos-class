//*****************************************************
//
// Casa.cpp 
// Um programa OpenGL simples que abre uma janela GLUT 
// e desenha uma casa.
//
// Marcelo Cohen e Isabel H. Manssour
// Este código acompanha o livro 
// "OpenGL - Uma Abordagem Prática e Objetiva"
// 
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
    // Limpa a janela de visualização com a cor  
    // de fundo definida previamente
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha uma casinha composta de um quadrado e um triângulo

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
    GLsizei largura, altura;

    // Evita a divisao por zero
    if(h == 0) h = 1;

    // Atualiza as variáveis
    largura = w;
    altura = h;

    // Especifica as dimensões da Viewport
    glViewport(0, 0, largura, altura);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de seleção (esquerda, direita, inferior, 
    // superior) mantendo a proporção com a janela de visualização
    if (largura <= altura) 
        gluOrtho2D (-40.0f, 40.0f, -40.0f*altura/largura, 40.0f*altura/largura);
    else 
        gluOrtho2D (-40.0f*largura/altura, 40.0f*largura/altura, -40.0f, 40.0f);

    //gluOrtho2D (-40.0f, 40.0f, -40.0f, 40.0f);
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
    glutInitWindowSize(450,450); 
 
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