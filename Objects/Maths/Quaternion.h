/*
 * Quaternion.h
 *
 *  Created on: Jan 18, 2011
 *      Author: ziggy
 */

#ifndef QUATERNION_H_
#define QUATERNION_H_
#include <vectormath/scalar/cpp/vectormath_aos.h>
#include <iostream>

using namespace std;
class Quaternion {
private:
	float data[4];
public:
	Quaternion(float w, float x, float y, float z);
	~Quaternion();
	void normalize();
	float getData(int index);
	Quaternion multiplyByQuaternion(Quaternion q);
	void addScaledVector(Vectormath::Aos::Vector3 v, float scale);
	void rotateByVector(Vectormath::Aos::Vector3 v);
};
#endif /* QUATERNION_H_ */
