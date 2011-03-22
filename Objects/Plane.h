/*
 * plane.h
 *
 *  Created on: 19 Oct 2010
 *      Author: Ziggy
 */

#ifndef PLANE_H_
#define PLANE_H_

#include <vectormath/scalar/cpp/vectormath_aos.h>
#include "DynamicObject.h"

class Plane: public DynamicObject{
protected:
	Vectormath::Aos::Vector3 h;
	Vectormath::Aos::Vector3 w;
	Vectormath::Aos::Vector3 v1;
	Vectormath::Aos::Vector3 v2;
	Vectormath::Aos::Vector3 v3;
	Vectormath::Aos::Vector3 v4;
public:
	void draw();
	Plane(Vectormath::Aos::Vector3 h,Vectormath::Aos::Vector3 w,Vectormath::Aos::Vector3 c);
	~Plane();
	Vectormath::Aos::Vector3 getH();
	Vectormath::Aos::Vector3 getW();
};

#endif /* PLANE_H_ */
