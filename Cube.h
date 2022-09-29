#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

class Cube : public Shape {
public:
	Cube() {};
	~Cube() {};

	OBJ_TYPE getType() {
		return SHAPE_CUBE;
	}

	void draw() {
            glPushMatrix();
            glBegin(GL_TRIANGLES);
            glVertex3f(1.9,1.9,1.9);
            glVertex3f(0,0,0);
            glVertex3f(30,30,30);
            glEnd();
            glPopMatrix();
	};


	void drawNormal() {
	};

private:
};

#endif