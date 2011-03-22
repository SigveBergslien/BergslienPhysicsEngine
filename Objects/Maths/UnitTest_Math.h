/*
 * UnitTest_Math.h
 *
 *  Created on: Feb 23, 2011
 *      Author: ziggy
 */

#ifndef UNITTEST_MATH_H_
#define UNITTEST_MATH_H_

#include "Matrix3.h"
#include "Quaternion.h"
#include <vectormath/scalar/cpp/vectormath_aos.h>
#include <iostream>

using namespace std;

class UnitTest_Math {
private:
	Matrix3 *testMatrix1;
	Matrix3 *testMatrix2;
	Matrix3 *testMatrix3;
	Vectormath::Aos::Vector3 testVector;
	Quaternion *testQuaternion1;
public:
	UnitTest_Math();
	void runTest();
	void testMatrixVectorMultiplication();
	void testMatrixMatrixMultiplication();
	void testMatrixFromQuaternion();
};

#endif /* UNITTEST_MATH_H_ */
