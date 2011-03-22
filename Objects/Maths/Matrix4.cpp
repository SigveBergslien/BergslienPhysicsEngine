/*
 * Matrix4.cpp
 *
 *  Created on: Jan 16, 2011
 *      Author: ziggy
 */

#include "Matrix4.h"

Matrix4::Matrix4(float a, float b, float c, float d, float e, float f, float g, float h, float i,float j, float k, float l)
{
	data = {a,b,c,d,
			e,f,g,h,
			i,j,k,l};
}
Matrix4::~Matrix4()
{
}
Vectormath::Aos::Vector3 Matrix4::multiplyByVector(Vectormath::Aos::Vector3 v)
{
	float tmp[3];
	int counter = 0;
	for(int i = 0; i<3;i++)
	{
		tmp[i]= data[0+counter]*v.getX()+data[1+counter]*v.getY()+data[2+counter]*v.getZ()+data[3+counter];
		counter+= 4;
	}
	return Vectormath::Aos::Vector3(tmp[0],tmp[1],tmp[2]);
}

float Matrix4::getValue(int index)
{
	return data[index];
}

Matrix4 Matrix4::multiplyByMatrix(Matrix4 m)
{
	Matrix4 *mm = new Matrix4(
			data[0]*m.getValue(0)+data[1]*m.getValue(4)+data[2]*m.getValue(8),
			data[0]*m.getValue(1)+data[1]*m.getValue(5)+data[2]*m.getValue(9),
			data[0]*m.getValue(2)+data[1]*m.getValue(6)+data[2]*m.getValue(10),
			data[0]*m.getValue(3)+data[1]*m.getValue(7)+data[2]*m.getValue(11) + data[3],

			data[4]*m.getValue(0)+data[5]*m.getValue(4)+data[6]*m.getValue(8),
			data[4]*m.getValue(1)+data[5]*m.getValue(5)+data[6]*m.getValue(9),
			data[4]*m.getValue(2)+data[5]*m.getValue(6)+data[6]*m.getValue(10),
			data[4]*m.getValue(3)+data[5]*m.getValue(7)+data[6]*m.getValue(11) +data[7],

			data[8]*m.getValue(0)+data[9]*m.getValue(4)+data[10]*m.getValue(8),
			data[4]*m.getValue(1)+data[5]*m.getValue(5)+data[6]*m.getValue(9),
			data[4]*m.getValue(2)+data[5]*m.getValue(6)+data[6]*m.getValue(10),
			data[4]*m.getValue(3)+data[5]*m.getValue(7)+data[6]*m.getValue(11) + data[11]
			);
	return *mm;
}

void Matrix4::insert(int index, float number)
{
	data[index]=number;
}
