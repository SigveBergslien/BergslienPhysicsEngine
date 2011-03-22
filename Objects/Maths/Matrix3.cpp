/*
 * Matrix3.cpp
 *
 *  Created on: Jan 16, 2011
 *      Author: ziggy
 */

#include "Matrix3.h"

Matrix3::Matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	data = {a,b,c,
			d,e,f,
			g,h,i};
}
Matrix3::Matrix3()
{

}
Matrix3::~Matrix3()
{
}
/**
 * Takes a Vector as its argument and calculate the new rotated vector using the
 * current rotation matrix. The new vector wll be returned.
 */
Vectormath::Aos::Vector3 Matrix3::multiplyByVector(Vectormath::Aos::Vector3 v)
{
	float tmp[3];
	int counter = 0;
	for(int i = 0; i<3;i++)
	{
		tmp[i]= data[0+counter]*v.getX()+data[1+counter]*v.getY()+data[2+counter]*v.getZ();
		counter+= 3;
	}
	return Vectormath::Aos::Vector3(tmp[0],tmp[1],tmp[2]);
}

float Matrix3::getValue(int index)
{
	return data[index];
}

/**
 * Takes a matrix as its argument then multiply the the supplied
 * matrix with the current matrix. The multiplied matrix is returned.
 */
Matrix3 Matrix3::multiplyByMatrix(Matrix3 m)
{
	Matrix3 *mm = new Matrix3 (
	data[0]*m.getValue(0) + data[1]*m.getValue(3) + data[2]*m.getValue(6),
	data[0]*m.getValue(1) + data[1]*m.getValue(4) + data[2]*m.getValue(7),
	data[0]*m.getValue(2) + data[1]*m.getValue(5) + data[2]*m.getValue(8),

	data[3]*m.getValue(0) + data[4]*m.getValue(3) + data[5]*m.getValue(6),
	data[3]*m.getValue(1) + data[4]*m.getValue(4) + data[5]*m.getValue(7),
	data[3]*m.getValue(2) + data[4]*m.getValue(5) + data[5]*m.getValue(8),

	data[6]*m.getValue(0) + data[7]*m.getValue(3) + data[8]*m.getValue(6),
	data[6]*m.getValue(1) + data[7]*m.getValue(4) + data[8]*m.getValue(7),
	data[6]*m.getValue(2) + data[7]*m.getValue(5) + data[8]*m.getValue(8)
	);

	return *mm;
}

/**
 * Return a matrix that is an inverse of
 * the current matrix.
 */
Matrix3 Matrix3::inverseMatrix()
{
	float determinant = ((data[0]*data[4]*data[8])
			-(data[0]*data[5]*data[7])
			-(data[1]*data[3]*data[8])
			+(data[2]*data[3]*data[7])
			+(data[1]*data[6]*data[5])
			-(data[2]*data[6]*data[4]));

	if(determinant !=0.0f)
	{
		determinant = 1/determinant;
	}
	Matrix3 *m = new Matrix3(
			 (data[4]*data[8]-data[5]*data[7])*determinant,
			-(data[1]*data[8]-data[2]*data[7])*determinant,
			 (data[1]*data[5]-data[2]*data[4])*determinant,
			-(data[3]*data[8]-data[5]*data[6])*determinant,
			 (data[0]*data[8]-data[2]*data[6])*determinant,
			-(data[0]*data[5]-data[2]*data[3])*determinant,
			 (data[3]*data[7]-data[4]*data[6])*determinant,
			-(data[0]*data[7]-data[1]*data[6])*determinant,
			 (data[0]*data[4]-data[1]*data[3])*determinant
			);
	return *m;
}

/**
 * Transpose the current matrix and return.
 * used to inverse rotation matrecies.
 */

Matrix3 Matrix3::transposeMatrix()
{
	Matrix3 *m = new Matrix3(
			data[0],data[3],data[6],
			data[1],data[4],data[7],
			data[2],data[5],data[8]);

	return *m;
}
/**
 * Takes a quaternion and change the current
 * matrix to match the rotation.
 */

void Matrix3::calculateFromQuaternion(Quaternion q)
{
	data[0] = 1 - 2*q.getData(2)*q.getData(2)+ 2*q.getData(3)*q.getData(3);
	data[1] = 2*q.getData(1)*q.getData(2) + 2*q.getData(3)*q.getData(0);
	data[2] = 2*q.getData(1)*q.getData(3);data[2]+= - 2*q.getData(2)*q.getData(0);
	data[3] = 2*q.getData(1)*q.getData(2);data[3]+= - 2*q.getData(3)*q.getData(0);
	data[4] = 1 - 2*q.getData(1)*q.getData(1)+2*q.getData(3)*q.getData(3);
	data[5] = 2*q.getData(2)*q.getData(3) + 2*q.getData(1)*q.getData(0);
	data[6] = 2*q.getData(1)*q.getData(3) + 2*q.getData(2)*q.getData(0);
	data[7] = 2*q.getData(2)*q.getData(3);data[7]+= - 2*q.getData(1)*q.getData(0);
	data[8] = 1 - 2*q.getData(1)*q.getData(1)+2*q.getData(2)*q.getData(2);
}
