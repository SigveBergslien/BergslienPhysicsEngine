/*
 * Quaternion.cpp
 *
 *  Created on: Jan 18, 2011
 *      Author: ziggy
 */

#include "Quaternion.h"
#include <math.h>
#include <cmath>
#include <iostream>

using namespace std;

Quaternion::Quaternion(float w, float x, float y,float z)
{
	data = { w,
			x,
			y,
			z};
}
Quaternion::~Quaternion()
{

}
/**
 * Normalize a quaternion. Methd will not preform the normalization
 * if the quaternion is already normalized.
 */
void Quaternion::normalize()
{
	float d= data[0]*data[0]+data[1]*data[1]+data[2]*data[2]+data[3]*data[3];
	if(d<0.9||d>1.1) //tolerance points
	{
		d = sqrt(d);
		for(int i = 0; i<4;i++)
		{
			data[i] /= d;
		}
	}
}
float Quaternion::getData(int index)
{
	return data[index];
}
Quaternion Quaternion::multiplyByQuaternion(Quaternion q)
{
	Quaternion *mq = new Quaternion(data[0]*q.getData(0) - data[1]*q.getData(1)- data[2]*q.getData(2) - data[3]*q.getData(3),
			data[0]*q.getData(1)+data[1]*q.getData(0)+data[2]*q.getData(3)-data[3]*q.getData(2),
			data[0]*q.getData(2)-data[1]*q.getData(3)+data[2]*q.getData(0)+data[3]*q.getData(1),
			data[0]*q.getData(3)+data[1]*q.getData(2)-data[2]*q.getData(1)+data[3]*q.getData(0));

	return *mq;
}
void Quaternion::addScaledVector(Vectormath::Aos::Vector3 v, float scale)
{
	Quaternion *q= new Quaternion(0,
			v.getX()*scale,
			v.getY()*scale,
			v.getZ()*scale);
	*q=q->multiplyByQuaternion(*this);
	for(int i=0;i<4;i++)
	{
		data[i]+=q->getData(i)*(0.5f);
		//cout<<i<<"    "<<data[i]<<endl;
	}
}


/**
 * Method for rotation the orientation by a vector.
 */
void Quaternion::rotateByVector(Vectormath::Aos::Vector3 v)
{
	Quaternion *q = new Quaternion(0,v.getX(),v.getY(),v.getZ());
	Quaternion rq = q->multiplyByQuaternion(*this);
	for(int i=0;i<4;i++)
	{
		data[i]=rq.getData(i)/2;
	}
}
