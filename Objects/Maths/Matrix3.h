/*
 * Matrix3.h
 *
 *  Created on: Jan 16, 2011
 *      Author: ziggy
 */

#ifndef MATRIX3_H_
#define MATRIX3_H_

#include <vectormath/scalar/cpp/vectormath_aos.h>
#include "Quaternion.h"

class Matrix3 {
private:
	float data[9];
public:
	Matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i);
	Matrix3();
	~Matrix3();
	Vectormath::Aos::Vector3 multiplyByVector(Vectormath::Aos::Vector3 v); // post multiplication
	Matrix3 multiplyByMatrix( Matrix3 m);
	Matrix3 inverseMatrix();
	Matrix3 transposeMatrix();
	float getValue(int index);
	void calculateFromQuaternion(Quaternion q);
};

#endif /* MATRIX3_H_ */
