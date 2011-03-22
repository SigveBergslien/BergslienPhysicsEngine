/*
 * Matrix4.h
 *
 *  Created on: Jan 16, 2011
 *      Author: ziggy
 */

#ifndef MATRIX4_H_
#define MATRIX4_H_

#include <vectormath/scalar/cpp/vectormath_aos.h>

class Matrix4 {
private:
	float data[12];
public:
	Matrix4(float a, float b, float c, float d, float e, float f, float g, float h, float i,float j, float k, float l);
	~Matrix4();
	Vectormath::Aos::Vector3 multiplyByVector(Vectormath::Aos::Vector3 v); // post multiplication
	Matrix4 multiplyByMatrix(Matrix4 m);
	float getValue(int index);
	void insert(int index, float number);
};

#endif /* MATRIX4_H_ */
