//*****************************************************
//
// Author: David Basilio Espitalher
// 
//*****************************************************

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <GL/glut.h>

#include "structs.cpp"

using namespace std;

const GLsizei WINDOW_WIDTH = 720;
const GLsizei WINDOW_HEIGHT = 480;
const GLsizei MIDDLE_X = WINDOW_WIDTH/2;
const GLsizei MIDDLE_Y = WINDOW_HEIGHT/2;
const int STARS_NUMBER = 250;
const int ENEMIES_NUMBER = 10;
const float PI = 3.14159;
const float SPEED = 0.01;

float angle = 0.0;
float slice = (2 * PI) / 100.0;

bool stateGoalReached = false;
bool stateInitialAnimation = true;
bool goalCreated = false;
bool enemiesCreated = false;
int timeline = 0;
int deltatime = 0;
int lasttime = 0;

Star * stars;
Spaceship * spaceshipPlayer;
Goal * goal;
vector<Spaceship> spaceshipEnemies;


int GetDeltatime()
{
	return (clock() - lasttime) / 1000;
}


void DrawSquare(float x, float y, float width, float height)
{
	float x2 = x + width;
	float y2 = y+height;

	glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x2, y);
		glVertex2f(x2, y2);
		glVertex2f(x, y2);
	glEnd();
}


void DrawCircle(float radius, float x = 0, float y = 0, GLenum mode = GL_POLYGON)
{
	float pointX, pointY;
	angle = 0.0;
	glBegin(mode);
	while(angle < 2*PI)
	{
		pointX = radius * cos(angle);
		pointY = radius * sin(angle);
		glVertex3f(pointX + x, pointY + y, 0);
		angle += slice;
	}
	glEnd();
}


void CreateStars()
{
	float speed;

	stars = new Star[STARS_NUMBER];
	
	for (int i = 0; i < STARS_NUMBER; i++)
	{
		stars[i].x = rand() % WINDOW_WIDTH + 1;
		stars[i].y = rand() % WINDOW_HEIGHT + 1;
		speed = rand() % 1000;

		if(speed < 100){
			stars[i].speed = 0.5;
		}else if(speed < 800){
			stars[i].speed = 1;
		}else if(speed < 950) {
			stars[i].speed = 2;
		}else {
			stars[i].speed = 2.5;
		}

		stars[i].size = 5;
	}

}


Spaceship * CreateSpaceship(Spaceship * spaceship)
{
	spaceship->width = 40;
	spaceship->height = 22;
	spaceship->x = 100;
	spaceship->y = WINDOW_HEIGHT / 2 - (spaceship->height / 2);
	spaceship->speed = 8;
	spaceship->distanceFromBegin = 0;

	return spaceship;
}


void CreateSpaceshipPlayer()
{
	spaceshipPlayer = CreateSpaceship(new Spaceship);

	spaceshipPlayer->x = -200;

	spaceshipPlayer->color[0] = 255;
	spaceshipPlayer->color[1] = 50;
	spaceshipPlayer->color[2] = 50;
}


void CreateEnemies(int enemies_number)
{
	for (int i = 0; i < enemies_number; i++)
	{
		Spaceship * enemy = CreateSpaceship(new Spaceship);

		enemy->color[0] = rand() % 155;
		enemy->color[1] = rand() % 255;
		enemy->color[2] = rand() % 255;

		enemy->x = (rand() % (MIDDLE_X) + WINDOW_WIDTH);
		enemy->y = rand() % WINDOW_HEIGHT;

		spaceshipEnemies.push_back(*enemy);
	}
}


void CreateGoal()
{
	goal = new Goal;
	goal->width = 15.0;
	goal->height = 15.0;
	goal->x = WINDOW_WIDTH + goal->width;
	goal->y = WINDOW_HEIGHT/2;
	goal->angle = 0.0;
	goal->angleSpeed = 1;
	goal->moveSpeed = 1;
}


void ResetGame()
{
	stateGoalReached = false;
	goalCreated = false;
	enemiesCreated = false;

	timeline = 0;
	deltatime = 0;
	lasttime = clock();

	delete stars;
	delete spaceshipPlayer;
	delete goal;

	spaceshipEnemies.clear();

	CreateStars();
	CreateSpaceshipPlayer();
}


void StarsGotoLightSpeed()
{
	for (int i = 0; i < STARS_NUMBER; i++)
		stars[i].speed += 20;
}


void StarsBackNormalSpeed()
{
	for (int i = 0; i < STARS_NUMBER; i++)
		stars[i].speed -= 20;
}


void CollisionGoal()
{
	if(goalCreated == true){
		float spaceshipXFinal = spaceshipPlayer->x + spaceshipPlayer->width;
		float spaceshipYFinal = spaceshipPlayer->y + spaceshipPlayer->height;

		// TODO: Fazer os inimigos andarem sozinhos
		if(spaceshipXFinal > goal->x && 
			spaceshipYFinal > goal->y &&
			spaceshipPlayer->x < (goal->x + goal->width) && 
			spaceshipPlayer->y < (goal->y + goal->height) && 
			stateGoalReached == false){

			stateGoalReached = true;
			lasttime = clock();

			StarsGotoLightSpeed();

			for (int i = 0; i < spaceshipEnemies.size(); i++){
				spaceshipEnemies[i].speed += 2;
			}

		}
	}
}


void CollisionEnemy(Spaceship * enemy)
{
	if((spaceshipPlayer->x + spaceshipPlayer->width) > enemy->x && 
	   (spaceshipPlayer->y + spaceshipPlayer->height) > enemy->y &&
	    spaceshipPlayer->x < (enemy->x + enemy->width) &&
		spaceshipPlayer->y < (enemy->y + enemy->height)){
				
			ResetGame();
			spaceshipPlayer->x = 100;
	}
}


void DrawBackground()
{
	glColor3ub(20, 20, 20);
	DrawSquare(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}


void DrawStar(Star * star)
{
	glColor3ub(255, 255, 255);
	glPointSize(star->size);
	glBegin(GL_POINTS);
		glVertex2d(star->x, star->y);
	glEnd();

}


void DrawSpaceship(Spaceship * spaceship)
{
	glColor3ub(255, 255 ,255);
	DrawSquare(5, 0, spaceship->width, spaceship->height);

	glColor3ubv(spaceship->color);
	DrawSquare(0, 0, spaceship->width, spaceship->height);

	glColor3ub(255, 255 ,255);
	DrawCircle(5, 0 + 12, 0 + 11);
	DrawCircle(5, 0 + 30, 0 + 11);
}


void DrawGoal()
{
	glPushMatrix();
		glTranslatef(goal->x + 0.5, goal->y, 0.0);
		glRotatef(goal->angle, 0.0f, 0.0f, 1.0f);
		glColor3ub(230, 230, 0);
		DrawSquare(0, 0, goal->width, goal->height);
	glPopMatrix();
}


void UpdateStars()
{
	for (int i = 0; i < STARS_NUMBER; i++) {
		stars[i].x -= stars[i].speed;

		if(stars[i].x < 0){
			stars[i].x = WINDOW_WIDTH + 10;
		}
	}

}


void UpadateKeySpaceshipPlayer(unsigned char key = ' ')
{
	if(!stateGoalReached){
		switch(key){
			case 'w': // UP
				spaceshipPlayer->y -= spaceshipPlayer->speed;
				break;
			case 's': // DOWN
				spaceshipPlayer->y += spaceshipPlayer->speed;
				break;
			case 'd': // RIGHT
				spaceshipPlayer->x += spaceshipPlayer->speed;
				break;
			case 'a': // LEFT
				spaceshipPlayer->x -= spaceshipPlayer->speed;
				break;
		}
	}

	CollisionGoal();
}


void UpdateKeyEnemies(unsigned char key = ' ')
{
	if(!stateGoalReached){
		for (int i = 0; i < spaceshipEnemies.size(); i++){
			CollisionEnemy(&spaceshipEnemies[i]);
		}
	}
}


void UpdateSpaceshipPlayer()
{

	deltatime = GetDeltatime();

	if(stateGoalReached == true){
		cout << deltatime << endl;
		if(deltatime < 2){
			spaceshipPlayer->x -= 1;
		}
		else if(deltatime < 4) {
			spaceshipPlayer->x += 15;
		}
		else {
			ResetGame();
			stateInitialAnimation = true;
			StarsGotoLightSpeed();
		}

	}

	if(stateInitialAnimation == true){
	
		if(deltatime > 1 && deltatime < 4){
			spaceshipPlayer->x += 7;
		}
		else if(deltatime < 5) {
			spaceshipPlayer->x -= 2;
		}
		else {
			StarsBackNormalSpeed();
			
			stateInitialAnimation = false;
		}
	}

}


void UpdateEnemies()
{
	vector<Spaceship>::iterator enemy = spaceshipEnemies.begin();
	while (enemy != spaceshipEnemies.end())
	{
		enemy->x -= 2;

		if (enemy->x < 0){
			enemy = spaceshipEnemies.erase(enemy);
		}
		else{
			++enemy;
		}
	}

}


void UpdateGoal()
{
	goal->angle += goal->angleSpeed;
	if(goal->x > WINDOW_WIDTH - 100)
		goal->x -= goal->moveSpeed;
}


void Update(void)
{
	deltatime = GetDeltatime();

	if(stateInitialAnimation == false && enemiesCreated == false){
		if(deltatime < 12){
			enemiesCreated = true;
			CreateEnemies(10);
		}
	}

	if(deltatime == 18){
		CreateGoal();
		goalCreated = true;
	}

	if(goalCreated == true)
		UpdateGoal();

	UpdateSpaceshipPlayer();
	UpdateStars();
	UpdateEnemies();
}


void Draw(void)
{
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	
	DrawBackground();

	for (int i = 0; i < STARS_NUMBER; i++)
		DrawStar(&stars[i]);

	// STATE: GOAL NOT CATCHED
	if(stateGoalReached == false) {

		if(goalCreated == true)
			DrawGoal();

		for (int i = 0; i < spaceshipEnemies.size(); i++){
			if(spaceshipEnemies[i].x > (0 - spaceshipEnemies[i].width) && spaceshipEnemies[i].x < WINDOW_WIDTH + spaceshipEnemies[i].width){
				glPushMatrix();
					glTranslatef(spaceshipEnemies[i].x, spaceshipEnemies[i].y, 0.0);
					// TODO: Ao rotacionar o teste de colisão não funciona
					// glRotatef(-180, 0.0f, 0.0f, 1.0f);
					DrawSpaceship(&spaceshipEnemies[i]);
				glPopMatrix();
			}
		}

	}

	glPushMatrix();
		glTranslatef(spaceshipPlayer->x, spaceshipPlayer->y, 0.0);
		DrawSpaceship(spaceshipPlayer);
	glPopMatrix();
}


void Display(void)
{
	Draw();
	
	glutSwapBuffers();
}


void Timer(int value)
{
	
	Update();
       
    // Redesenha o quadrado com as novas coordenadas 
    glutPostRedisplay();
    glutTimerFunc(33, Timer, 1);
}


void Reshape(GLsizei w, GLsizei h)
{
	glViewport(0.0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();

	gluOrtho2D (0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f);
}


void Keyboard (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);

	cout << GLUT_KEY_DOWN << GLUT_KEY_UP << endl;

	UpdateKeyEnemies();
	UpadateKeySpaceshipPlayer(key);
}


void Joystick(unsigned int buttonMask, int x, int y, int z)
{
	if(stateGoalReached == false){
		spaceshipPlayer->x += x / 100;
		spaceshipPlayer->y += y / 100;
	}

	CollisionGoal();
}


void Initialize (void)
{
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	timeline = clock();

	CreateStars();
	CreateSpaceshipPlayer();
	StarsGotoLightSpeed();
}


int main(void)
{
	srand (time(NULL));

	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5, 5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Space Stay Alive");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Display);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(Reshape);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Keyboard);
    
	glutJoystickFunc(Joystick, 10);

	glutTimerFunc(33, Timer, 1);

	// Chama a função responsável por fazer as inicializações 
	Initialize();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
