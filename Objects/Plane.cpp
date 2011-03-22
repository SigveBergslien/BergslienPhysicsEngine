/*
 * Plane.cpp
 *
 *  Created on: 19 Oct 2010
 *      Author: Ziggy
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <iostream>

#include "Plane.h"

using namespace std;

Plane::Plane(Vectormath::Aos::Vector3 ph,Vectormath::Aos::Vector3 pw,Vectormath::Aos::Vector3 c):DynamicObject(c,0.0)
{
	w = pw;
	h = ph;
	v1 = center-((h/2)+(w/2));
	v2 = v1 +w;
	v3 = v2+h;
	v4 = v1+h;
}
void Plane::draw()
{
	glPushMatrix();
	glBegin(GL_QUADS);

	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(v1.getX(),v1.getY(),v1.getZ());
	glVertex3f(v2.getX(),v2.getY(),v2.getZ());
	glVertex3f(v3.getX(),v3.getY(),v3.getZ());
	glVertex3f(v4.getX(),v4.getY(),v4.getZ());

	glEnd();
	glPopMatrix();
}
Vectormath::Aos::Vector3 Plane::getH()
{
	return h;
}

Vectormath::Aos::Vector3 Plane::getW()
{
	return w;
}
