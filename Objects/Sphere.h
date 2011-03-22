/*
 * Sphere.h
 *
 *  Created on: 19 Oct 2010
 *      Author: Ziggy
 */

#include <vectormath/scalar/cpp/vectormath_aos.h>
#include "DynamicObject.h"
#include "Maths/Matrix3.h"

#ifndef _SPHERE_H
#define _SPHERE_H

class Sphere: public DynamicObject{
protected:
	float radius;
public:
	Sphere(float r,Vectormath::Aos::Vector3 c, float m);
	~Sphere();
	void draw();
	void applyGravity(Vectormath::Aos::Vector3 g, int fr);
	float getRadius();
};

#endif
