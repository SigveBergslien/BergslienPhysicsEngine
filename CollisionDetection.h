/*
 * CollisionDetection.h
 *
 *  Created on: Oct 29, 2010
 *      Author: ziggy
 */

#ifndef COLLISIONDETECTION_H_
#define COLLISIONDETECTION_H_


#include <vectormath/scalar/cpp/vectormath_aos.h>
#include <vector>
#include"Objects/DynamicObject.h"
#include"Objects/Sphere.h"
#include"Objects/Plane.h"
#include"Objects/AABB.h"
#include"Objects/OBB.h"

class CollisionDetection
{
private:
public:
	CollisionDetection();
	~CollisionDetection();
	bool collision(Sphere* s, Sphere *s2);
	bool collision(Plane* p,Sphere* s);
	bool collision(Sphere*s, AABB* box);
	bool collision(Sphere*s, OBB* box);
	bool collision(Vectormath::Aos::Vector3 h, Vectormath::Aos::Vector3 w,Sphere *s,Vectormath::Aos::Vector3 pos);
	void response(Sphere* s, Sphere *s2);
	vector<Vectormath::Aos::Vector3> collision(OBB* box, Plane* p);
	void response(Sphere* s, Vectormath::Aos::Vector3 normal);
	float toAbsolute(float i);
	bool contact(Vectormath::Aos::Vector3 point,Vectormath::Aos::Vector3 normal);
};
#endif /* COLLISIONDETECTION_H_ */
