/*
 * AABB.h
 *
 *  Created on: Nov 27, 2010
 *      Author: ziggy
 */
#include <vectormath/scalar/cpp/vectormath_aos.h>
#include "DynamicObject.h"

#ifndef AABB_H_
#define AABB_H_

class AABB: public DynamicObject
{
private:
	float x;
	float y;
	float z;
public:
	AABB(float x, float y, float z, Vectormath::Aos::Vector3 c, float m);
	~AABB();
	virtual void draw();
	float getX();
	float getY();
	float getZ();
};
#endif /* AABB_H_ */
