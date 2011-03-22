/*
 * DynamicObject.cpp
 *
 *  Created on: 19 Oct 2010
 *      Author: Ziggy
 */
#include "DynamicObject.h"

DynamicObject::DynamicObject(Vectormath::Aos::Vector3 c, float m)
{
	center =c;
	velocity = Vectormath::Aos::Vector3(0.0f,0.0f,0.0f);
	angularVelocity = Vectormath::Aos::Vector3(0.0f,0.0f,0.0f);
	mass =m;
	coefficient = 0.20;
	onPlane = true;
	transformMatrix = new Matrix4(0.0,0.0,0.0,0.0,
								0.0,0.0,0.0,0.0,
								0.0,0.0,0.0,0.0);
	orientation = new Quaternion(0.0,0.0,0.0,0.0);
}

DynamicObject::~DynamicObject()
{

}
void DynamicObject::draw()
{
}
void DynamicObject::invertVelocity()
{
	velocity*=-1;
}
void DynamicObject::applyForce(Vectormath::Aos::Vector3 f)
{
	velocity+=f;
}
Vectormath::Aos::Vector3 DynamicObject::getCenter()
{
	return center;
}
void DynamicObject::setVelocity(Vectormath::Aos::Vector3 v)
{
	velocity = v;
}

Vectormath::Aos::Vector3 DynamicObject::getVelocity()
{
	return velocity;
}
float DynamicObject::getBounce()
{
	return bounce;
}
float DynamicObject::getMass()
{
	return mass;
}
float DynamicObject::getCoefficient()
{
	return coefficient;
}
void DynamicObject::setCoefficient(float c)
{
	coefficient = c;
}
void DynamicObject::applyFriction()
{
	Vectormath::Aos::Vector3 friction;
		friction = -((coefficient*mass*9.81)*(velocity/sqrt(dot(velocity,velocity))));
		velocity += friction/60;
}
bool DynamicObject::onAPlane()
{
	return onPlane;
}
void DynamicObject::setOnPlane(bool b)
{
	onPlane = b;
}
void DynamicObject::calculateTransformMatrix()
{
	transformMatrix->insert(0,(1-2*orientation->getData(2)*orientation->getData(2)-2*orientation->getData(3)*orientation->getData(3)));
	transformMatrix->insert(1,(2*orientation->getData(1)*orientation->getData(2)+2*orientation->getData(0)*orientation->getData(3)));
	transformMatrix->insert(2,(2*orientation->getData(1)*orientation->getData(3)-2*orientation->getData(0)*orientation->getData(2)));
	transformMatrix->insert(3,center.getX());

	transformMatrix->insert(4,(2*orientation->getData(1)*orientation->getData(2)-2*orientation->getData(0)*orientation->getData(3)));
	transformMatrix->insert(5,(1-2*orientation->getData(1)*orientation->getData(1)-2*orientation->getData(3)*orientation->getData(3)));
	transformMatrix->insert(6,(2*orientation->getData(2)*orientation->getData(3)+2*orientation->getData(0)*orientation->getData(1)));
	transformMatrix->insert(7,center.getY());

	transformMatrix->insert(8,(2*orientation->getData(1)*orientation->getData(3)+2*orientation->getData(0)*orientation->getData(2)));
	transformMatrix->insert(9,(2*orientation->getData(2)*orientation->getData(3)-2*orientation->getData(0)*orientation->getData(1)));
	transformMatrix->insert(10,(1-2*orientation->getData(1)*orientation->getData(1)-2*orientation->getData(2)*orientation->getData(2)));
	transformMatrix->insert(11,center.getZ());
}
/**
 * Return the inertia tensor in world spaces
 */
Matrix3 DynamicObject::inertiaWorld()
{
	float t4 = transformMatrix->getValue(0)*inertiaTensor->getValue(0)+
			transformMatrix->getValue(1)*inertiaTensor->getValue(3)+
			transformMatrix->getValue(2)*inertiaTensor->getValue(6);
	float t9 = transformMatrix->getValue(0)*inertiaTensor->getValue(1)+
			transformMatrix->getValue(1)*inertiaTensor->getValue(4)+
			transformMatrix->getValue(2)*inertiaTensor->getValue(7);
	float t14 = transformMatrix->getValue(0)*inertiaTensor->getValue(2)+
			transformMatrix->getValue(1)*inertiaTensor->getValue(5)+
			transformMatrix->getValue(2)*inertiaTensor->getValue(8);
	float t28 = transformMatrix->getValue(4)*inertiaTensor->getValue(0)+
			transformMatrix->getValue(5)*inertiaTensor->getValue(3)+
			transformMatrix->getValue(6)*inertiaTensor->getValue(6);
	float t33 = transformMatrix->getValue(4)*inertiaTensor->getValue(1)+
			transformMatrix->getValue(5)*inertiaTensor->getValue(4)+
			transformMatrix->getValue(6)*inertiaTensor->getValue(7);
	float t38 = transformMatrix->getValue(4)*inertiaTensor->getValue(2)+
			transformMatrix->getValue(5)*inertiaTensor->getValue(5)+
			transformMatrix->getValue(6)*inertiaTensor->getValue(8);
	float t52 = transformMatrix->getValue(8)*inertiaTensor->getValue(0)+
			transformMatrix->getValue(9)*inertiaTensor->getValue(3)+
			transformMatrix->getValue(10)*inertiaTensor->getValue(6);
	float t57 = transformMatrix->getValue(8)*inertiaTensor->getValue(1)+
			transformMatrix->getValue(9)*inertiaTensor->getValue(4)+
			transformMatrix->getValue(10)*inertiaTensor->getValue(7);
	float t62 = transformMatrix->getValue(8)*inertiaTensor->getValue(2)+
			transformMatrix->getValue(9)*inertiaTensor->getValue(5)+
			transformMatrix->getValue(10)*inertiaTensor->getValue(8);

	Matrix3 *iitWorld = new Matrix3(t4*transformMatrix->getValue(0)+t9*transformMatrix->getValue(1)+t14*transformMatrix->getValue(2),
			t4*transformMatrix->getValue(4)+t9*transformMatrix->getValue(5)+t14*transformMatrix->getValue(6),
			t4*transformMatrix->getValue(8)+t9*transformMatrix->getValue(9)+t14*transformMatrix->getValue(10),
			t28*transformMatrix->getValue(0)+t33*transformMatrix->getValue(1)+t38*transformMatrix->getValue(2),
			t28*transformMatrix->getValue(4)+t33*transformMatrix->getValue(5)+t38*transformMatrix->getValue(6),
			t28*transformMatrix->getValue(8)+t33*transformMatrix->getValue(9)+t38*transformMatrix->getValue(10),
			t52*transformMatrix->getValue(0)+t57*transformMatrix->getValue(1)+t62*transformMatrix->getValue(2),
			t52*transformMatrix->getValue(4)+t57*transformMatrix->getValue(5)+t62*transformMatrix->getValue(6),
			t52*transformMatrix->getValue(8)+t57*transformMatrix->getValue(9)+t62*transformMatrix->getValue(10));

	return *iitWorld;
}

void DynamicObject::addTorque(Vectormath::Aos::Vector3 p, Vectormath::Aos::Vector3 f)
{
	//p-= center;
	Vectormath::Aos::Vector3 t=  cross(p,f);
	Matrix3 iitWorld = inertiaWorld();
	Vectormath::Aos::Vector3 av = iitWorld.multiplyByVector(t);
	angularVelocity += av;
	cout<<angularVelocity.getX()<<"    "<<angularVelocity.getY()<<"      "<<angularVelocity.getZ()<<endl;
}

Matrix4 DynamicObject::getTransformMatrix()
{
	return *transformMatrix;
}

void DynamicObject::setOrientation(Quaternion* q)
{
	orientation = new Quaternion(q->getData(0),q->getData(1),q->getData(2),q->getData(3));
	//orientation->normalize();
	calculateTransformMatrix();
}
