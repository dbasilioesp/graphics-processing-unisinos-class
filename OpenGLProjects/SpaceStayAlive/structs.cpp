#include <GL/glut.h>

#ifndef __structs_cpp__
#define __structs_cpp__


struct Star {
	float x;
	float y;
	float size;
	float speed;
};


struct Spaceship {
	float x;
	float y;
	float width;
	float height;
	float speed;
	float distanceFromBegin;
	GLubyte color[3];
};


struct Goal {
	float x;
	float y;
	float width;
	float height;
	float angle;
	float moveSpeed;
	float angleSpeed;
	bool catched;
};

#endif