/*
 * OBB.cpp
 *
 *  Created on: Jan 23, 2011
 *      Author: ziggy
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <vectormath/scalar/cpp/vectormath_aos.h>
#include <iostream>

using namespace std;
#include "OBB.h"

OBB::OBB(float hs, Vectormath::Aos::Vector3 c, float m):DynamicObject(c,m)
{
	halfSize = hs;
	inertiaTensor = new Matrix3((1*mass*4*(hs*hs))/12,0.0,0.0,
			0.0,(1*mass*4*(hs*hs))/12,0.0,
			0.0,0.0,(1*mass*4*(hs*hs))/12);
	calculateTransformMatrix();
}
OBB::~OBB()
{
}
void OBB::Draw()
{
	if(length(velocity)>0.5)
	{
		center+=(velocity)/60;
	}
	//if(length(angularVelocity)>0.1f||length(angularVelocity)<-0.1f)
	//{
	//	angularVelocity*=angularDamping;
		//orientation->rotateByVector(angularVelocity);
	//orientation->rotateByVector(Vectormath::Aos::Vector3(0.0, 0.0, 0.3));
	orientation->addScaledVector(Vectormath::Aos::Vector3(0.0, 0.0, -0.1),1);
	orientation->normalize();
		//orientation->addScaledVector(angularVelocity,1/60);
	//}
	glPushMatrix();
	glTranslatef(center.getX(),center.getY(),center.getZ());
	glRotatef(orientation->getData(0),orientation->getData(1),orientation->getData(2),orientation->getData(3));
	glBegin(GL_QUADS);
	glColor3f(1.0f,0.0f,0.0f);

	glVertex3f(-halfSize,-halfSize,-halfSize);//front
	glVertex3f(+halfSize,-halfSize,-halfSize);
	glVertex3f(+halfSize,+halfSize,-halfSize);
	glVertex3f(-halfSize,+halfSize,-halfSize);

	glVertex3f(-halfSize,+halfSize,-halfSize);//top
	glVertex3f(+halfSize,+halfSize,-halfSize);
	glVertex3f(+halfSize,+halfSize,+halfSize);
	glVertex3f(-halfSize,+halfSize,+halfSize);

	glVertex3f(+halfSize,-halfSize,-halfSize);//right
	glVertex3f(+halfSize,-halfSize,+halfSize);
	glVertex3f(+halfSize,+halfSize,+halfSize);
	glVertex3f(+halfSize,+halfSize,-halfSize);

	glVertex3f(-halfSize,-halfSize,-halfSize);//left
	glVertex3f(-halfSize,-halfSize,+halfSize);
	glVertex3f(-halfSize,+halfSize,+halfSize);
	glVertex3f(-halfSize,+halfSize,-halfSize);

	glVertex3f(-halfSize,-halfSize,-halfSize);//bottom
	glVertex3f(+halfSize,-halfSize,-halfSize);
	glVertex3f(+halfSize,-halfSize,+halfSize);
	glVertex3f(-halfSize,-halfSize,+halfSize);

	glVertex3f(-halfSize,-halfSize,+halfSize);//back
	glVertex3f(+halfSize,-halfSize,+halfSize);
	glVertex3f(+halfSize,+halfSize,+halfSize);
	glVertex3f(-halfSize,+halfSize,+halfSize);

	glEnd();
	glPopMatrix();

	calculateTransformMatrix();
}

float OBB::getHalfSize()
{
	return halfSize;
}

Quaternion OBB::getRot()
{
	return *orientation;
}
