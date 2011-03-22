/*
 * UnitTest_Math.cpp
 *
 *  Created on: Feb 23, 2011
 *      Author: ziggy
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include "UnitTest_Math.h"
#include <boost/test/unit_test.hpp>

UnitTest_Math::UnitTest_Math()
{
	testMatrix1 = new Matrix3(1,2,3
			,4,5,6
			,7,8,9);

	testMatrix2 = new Matrix3(1,2,3
			,4,3,2
			,1,2,4);

	testMatrix3 = new Matrix3(1,3,4
			,6,2,4
			,1,2,0);

	testVector = Vectormath::Aos::Vector3(10,11,12);

	testQuaternion1 = new Quaternion(3,0,1,2);
}
void UnitTest_Math::runTest()
{
	cout<<"Running math tests"<<endl;
	testMatrixMatrixMultiplication();
	testMatrixVectorMultiplication();
	testMatrixFromQuaternion();
}
void UnitTest_Math::testMatrixMatrixMultiplication()
{
	cout<<"Unit test: Matrix Matrix multiplication"<<endl;
	Matrix3 tmp = testMatrix2->multiplyByMatrix(*testMatrix3);
	if(tmp.getValue(0)==16&&tmp.getValue(1)==13&&tmp.getValue(2)==12
			&&tmp.getValue(3)==24&&tmp.getValue(4)==22&&tmp.getValue(5)==28
			&&tmp.getValue(6)==17&&tmp.getValue(7)==15&&tmp.getValue(8)==12)
	{
		cout<<"Success"<<endl;
	}
	else
	{
		cout<<"Failed"<<endl;
	}
}
void UnitTest_Math::testMatrixVectorMultiplication()
{
	cout<<"Unit test: Matrix vector multiplication"<<endl;
	Vectormath::Aos::Vector3 tmp = testMatrix1->multiplyByVector(testVector);
	if(tmp.getX()==68&&tmp.getY()==167&&tmp.getZ()==266)
	{
		cout<<"Success"<<endl;
	}
	else
	{
		cout<<"Failed"<<endl;
	}
}

void UnitTest_Math::testMatrixFromQuaternion()
{
	cout<<"Unit test: Matrix from Quaternion"<<endl;
	Matrix3 *tmp = new Matrix3();
	tmp->calculateFromQuaternion(*testQuaternion1);
	if(tmp->getValue(0)==(-9)&&tmp->getValue(1)==12&&tmp->getValue(2)==(-6)&&
			tmp->getValue(3)==(-12)&&tmp->getValue(4)==(-7)&&tmp->getValue(5)==4&&
			tmp->getValue(6)==6&&tmp->getValue(7)==4&&tmp->getValue(8)==(-1))
	{
		cout<<"Success"<<endl;
	}
	else
	{
		cout<<"Failed"<<endl;
		cout<<tmp->getValue(1)<<endl;
	}
}
