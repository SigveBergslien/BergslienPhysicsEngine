/*
 * DynamicObject.h
 *
 *  Created on: 19 Oct 2010
 *      Author: Ziggy
 */

#ifndef DYNAMICOBJECT_H_
#define DYNAMICOBJECT_H_

#include "Maths/Quaternion.h"
#include "Maths/Matrix4.h"
#include "Maths/Matrix3.h"
#include <vectormath/scalar/cpp/vectormath_aos.h>
#include <iostream>

using namespace std;

class DynamicObject{
protected:
	Vectormath::Aos::Vector3 center;
	Vectormath::Aos::Vector3 velocity;
	Vectormath::Aos::Vector3 acceleration;
	Vectormath::Aos::Vector3 angularVelocity;
	Quaternion *orientation;
	Matrix4 *transformMatrix;
	Matrix3 *inertiaTensor;
	float bounce; //bounce property
	float mass;
	float coefficient; //With ground
	float angularDamping;
	bool onPlane;
	int ID;
public:
	DynamicObject(Vectormath::Aos::Vector3 c, float m);
	~DynamicObject();
	virtual void draw();
	virtual void applyGravity(Vectormath::Aos::Vector3 g, int fr){};
	void setVelocity(Vectormath::Aos::Vector3 v);
	void invertVelocity();
	void applyForce(Vectormath::Aos::Vector3 f);
	Vectormath::Aos::Vector3 getCenter();
	Vectormath::Aos::Vector3 getVelocity();
	float getBounce();
	float getMass();
	float getCoefficient();
	void setCoefficient(float c);
	void setOrientation(Quaternion* o);
	void applyFriction();
	bool onAPlane();
	void setOnPlane(bool b);
	int getID(){return ID;};
	void calculateTransformMatrix();
	Matrix3 inertiaWorld();
	Matrix4 getTransformMatrix();
	void addTorque(Vectormath::Aos::Vector3 p, Vectormath::Aos::Vector3 f);
};
#endif /* DYNAMICOBJECT_H_ */
