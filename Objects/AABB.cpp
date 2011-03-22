/*
 * AABB.cpp
 *
 *  Created on: Nov 27, 2010
 *      Author: ziggy
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <vectormath/scalar/cpp/vectormath_aos.h>
#include <iostream>

using namespace std;
#include "AABB.h"


AABB::AABB(float xval, float yval, float zval, Vectormath::Aos::Vector3 c, float m):DynamicObject(c,m)
{
	x=xval;y=yval;z=zval;
	ID =1;
}
AABB::~AABB()
{

}
void AABB::draw()
{
	glPushMatrix();
	glTranslatef(center.getX(),center.getY(),center.getZ());

	glBegin(GL_QUADS);
	glColor3f(1.0f,0.0f,0.0f);

	glVertex3f(-x,-y,-z);
	glVertex3f(x,-y,-z);
	glVertex3f(x,y,-z);
	glVertex3f(-x,y,-z);

	glVertex3f(-x,-y,z);
	glVertex3f(-x,-y,-z);
	glVertex3f(-x,y,-z);
	glVertex3f(-x,y,z);

	glVertex3f(x,-y,z);
	glVertex3f(x,-y,-z);
	glVertex3f(x,y,-z);
	glVertex3f(x,y,z);

	glVertex3f(-x,-y,z);
	glVertex3f(-x,-y,-z);
	glVertex3f(x,-y,-z);
	glVertex3f(x,-y,z);

	glVertex3f(-x,y,z);
	glVertex3f(-x,y,-z);
	glVertex3f(x,y,-z);
	glVertex3f(x,y,z);

	glVertex3f(-x,-y,z);
	glVertex3f(x,-y,z);
	glVertex3f(x,y,z);
	glVertex3f(-x,y,z);

	glEnd();
	glPopMatrix();
}

float AABB::getX()
{
	return x;
}
float AABB::getY()
{
	return y;
}
float AABB::getZ()
{
	return z;
}
