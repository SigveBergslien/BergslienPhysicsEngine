/*
 * Sphere.cpp
 *
 *  Created on: 19 Oct 2010
 *      Author: Ziggy
 */


#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <vectormath/scalar/cpp/vectormath_aos.h>
#include <iostream>
#include "Maths/Matrix3.h"

using namespace std;


#include "Sphere.h"

Sphere::Sphere(float r,Vectormath::Aos::Vector3 c, float m):DynamicObject(c,m)
{
	radius = r;
	bounce=0.9;
	ID=0;
	inertiaTensor = new Matrix3((2*mass*(radius*radius))/5,0.0,0.0,
			0.0,(2*mass*(radius*radius))/5,0.0,
			0.0,0.0,(2*mass*(radius*radius))/5);
	inertiaTensor->inverseMatrix();
}
Sphere::~Sphere()
{

}
void Sphere::draw()
{
	if(length(velocity)>0.5)
	{
		center+=(velocity)/60;
	}
	if(length(angularVelocity)>0.2f)
	{
		angularVelocity*=angularDamping;
		orientation->rotateByVector(angularVelocity);
	}
	glPushMatrix();
	glRotatef(orientation->getData(0),orientation->getData(1),orientation->getData(2),orientation->getData(3));
	glTranslatef(center.getX(),center.getY(),center.getZ());
	glColor3f(0.0,0.0,1.0);
	gluSphere(gluNewQuadric(),radius,32,32);
	glPopMatrix();
}
float Sphere::getRadius()
{
	return radius;
}
void Sphere::applyGravity(Vectormath::Aos::Vector3 g, int fr)
{
	velocity-= g/fr;
}
