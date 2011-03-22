/*
 * CollisionDetection.cpp
 *
 *  Created on: Oct 29, 2010
 *      Author: ziggy
 */
#include <vectormath/scalar/cpp/vectormath_aos.h>
#include "CollisionDetection.h"

CollisionDetection::CollisionDetection()
{
}
CollisionDetection::~CollisionDetection()
{

}
bool CollisionDetection::collision(Sphere *s, Sphere*s2)
{
	float l = length(s->getCenter()-s2->getCenter());
	if(l<=s->getRadius()+s2->getRadius())
	{
		response(s,s2);
		return true;
	}
	return false;
}
bool CollisionDetection::collision(Plane*p, Sphere* s)
{
	return collision(p->getH(),p->getW(),s,Vectormath::Aos::Vector3(0.0,0.0,0.0));
}
bool CollisionDetection::collision(Vectormath::Aos::Vector3 h, Vectormath::Aos::Vector3 w,Sphere *s,Vectormath::Aos::Vector3 pos)
{
	Vectormath::Aos::Vector3 normal = cross(h,w);
	normal = normal/sqrt(dot(normal,normal));
	float d = dot(normal,s->getCenter()-pos);
	if(pos.getY()>0)
	{
	}
	if(d>s->getRadius())
	{
		return false;
	}
	//formula for reflecting velocity taken from: http://www.3dkingdoms.com/weekly/weekly.php?a=2
	if(s->onAPlane())
	{
		s->applyFriction();
	}
	else {
		response(s,normal);
	}
	return true;
}
bool CollisionDetection::collision(Sphere *s, AABB * box)
{
	Vectormath::Aos::Vector3 point = s->getCenter();
	point+=(( box->getCenter() -s->getCenter())/length(s->getCenter()- box->getCenter()))*s->getRadius();
	if(point.getX()>box->getCenter().getX()-box->getX()&&point.getX()<box->getCenter().getX()+box->getX())
	{
		if(point.getY()>box->getCenter().getY()-box->getY()&&point.getY()<box->getCenter().getY()+box->getY())
		{
			if(point.getZ()>box->getCenter().getZ()-box->getZ()&&point.getZ()<box->getCenter().getZ()+box->getZ())
			{
				Vectormath::Aos::Vector3 toCollision =point-box->getCenter();
				float disX = box->getX()-toAbsolute(toCollision.getX());
				float disY = box->getY()-toAbsolute(toCollision.getY());
				float disZ = box->getZ()-toAbsolute(toCollision.getZ());
				if(disX<disY&&disX<disZ)
				{
						Vectormath::Aos::Vector3 normal = cross(Vectormath::Aos::Vector3(0,box->getY(),0),Vectormath::Aos::Vector3(0,0,box->getZ()));
						normal =normal/sqrt(dot(normal,normal));
						response(s,normal);
				}
				else if(disY<disZ)
				{
					Vectormath::Aos::Vector3 normal = cross(Vectormath::Aos::Vector3(0,0,box->getZ()),Vectormath::Aos::Vector3(box->getX(),0,0));
					normal =normal/sqrt(dot(normal,normal));
					response(s,normal);
				}

				else
				{
					Vectormath::Aos::Vector3 normal = cross(Vectormath::Aos::Vector3(0,box->getY(),0),Vectormath::Aos::Vector3(box->getX(),0,0));
					normal =normal/sqrt(dot(normal,normal));
					response(s,normal);
				}
				return true;
			}
		}
	}
	return false;
}
bool CollisionDetection::collision(Sphere *s, OBB * box)
{
	Vectormath::Aos::Vector3 point = box->getCenter();
	float hs =box->getHalfSize();
	Matrix3 rot = Matrix3();
	rot.calculateFromQuaternion(box->getRot());
	Vectormath::Aos::Vector3 mid = Vectormath::Aos::Vector3(point.getX()+hs,point.getY()+hs,point.getZ()-hs);
	mid =rot.multiplyByVector(mid-point)+point;
	/*
	if(collision(rot.multiplyByVector(Vectormath::Aos::Vector3(point.getX()-hs,point.getY()+hs,point.getZ()-hs)-mid),
			rot.multiplyByVector(Vectormath::Aos::Vector3(point.getX()+hs,point.getY()+hs,point.getZ()+hs)-mid),s,mid))
	{
		cout<<"yatta"<<endl;
		return true; // top quad
	}
	*/
	Vectormath::Aos::Vector3 first = rot.multiplyByVector(Vectormath::Aos::Vector3(point.getX()-hs,point.getY()+hs,point.getZ()-hs)-point)+point-mid;
	//cout<<first.getX()<<"    "<<first.getY()<<"   "<<first.getZ()<<endl;
	Vectormath::Aos::Vector3 second = rot.multiplyByVector(Vectormath::Aos::Vector3(point.getX()+hs,point.getY()+hs,point.getZ()+hs)-point)+point-mid;
	//cout<<second.getX()<<"    "<<second.getY()<<"    "<<second.getZ()<<endl;
	if(collision(rot.multiplyByVector(Vectormath::Aos::Vector3(point.getX()-hs,point.getY()+hs,point.getZ()-hs)-point)+point-mid,
			rot.multiplyByVector(Vectormath::Aos::Vector3(point.getX()+hs,point.getY()+hs,point.getZ()+hs)-point)+point-mid,s,mid))
	{
		//cout<<"yatta"<<endl;
		return true; // top quad
	}
	else
	{
		return false;
	}

}
void CollisionDetection::response(Sphere *s, Sphere *s2)
{
	float l = length(s->getCenter()-s2->getCenter());
	//find the unit vector from center to center
	Vectormath::Aos::Vector3 x = (s->getCenter()-s2->getCenter())/l;
	//x = x/sqrt(dot(x,x));

	//New direction for sphere 1
	Vectormath::Aos::Vector3 velo1 = s->getVelocity();
	float dotProdx = dot(x,velo1);
	Vectormath::Aos::Vector3 veloInx = x*dotProdx;
	Vectormath::Aos::Vector3 veloIny = velo1 - veloInx;

	//New direction for sphere 2
	x*= -1;
	Vectormath::Aos::Vector3 velo2 = s2->getVelocity();
	float dotProdx2 = dot(x,velo2);
	Vectormath::Aos::Vector3 veloInx2 = x*dotProdx2;
	Vectormath::Aos::Vector3 veloIny2 = velo2 - veloInx2;

	// masses
	float mass1 = s->getMass();
	float mass2 = s2->getMass();

	Vectormath::Aos::Vector3 newVelo1 = veloInx*((mass1-mass2)/(mass1+mass2))+veloInx2*((2+mass2)/(mass1+mass2))+veloIny;
	Vectormath::Aos::Vector3 newVelo2 = veloInx*((2*mass1)/(mass1+mass2))+veloInx2*((mass2-mass1)/(mass1+mass2))+veloIny2;

	s->setVelocity(newVelo1);
	s2->setVelocity(newVelo2);
}
void CollisionDetection::response(Sphere* s, Vectormath::Aos::Vector3 normal)
{
	Vectormath::Aos::Vector3 newVelo = s->getBounce()*(-((2*(dot(normal,s->getVelocity()))*normal)-s->getVelocity()));
			s->setVelocity(newVelo);
}

vector<Vectormath::Aos::Vector3> CollisionDetection::collision(OBB* box, Plane* p)
{
	vector<Vectormath::Aos::Vector3> contactPoints;
	Vectormath::Aos::Vector3 center = box->getCenter();
	float hs =box->getHalfSize();
	Matrix3 rot = Matrix3();
	rot.calculateFromQuaternion(box->getRot());
	Vectormath::Aos::Vector3 normal = cross(p->getH(),p->getW());
	normal = normal/sqrt(dot(normal,normal));

	Vectormath::Aos::Vector3 fblf = rot.multiplyByVector(Vectormath::Aos::Vector3(-hs,-hs,-hs))+center;//Front bottom left
	if(contact(fblf,normal))
	{
		contactPoints.push_back(fblf);
	}

	Vectormath::Aos::Vector3 fbrt = rot.multiplyByVector(Vectormath::Aos::Vector3(+hs,-hs,-hs))+center;//Front bottom right
	if(contact(fbrt,normal))
	{
		contactPoints.push_back(fbrt);
	}

	Vectormath::Aos::Vector3 ftlf = rot.multiplyByVector(Vectormath::Aos::Vector3(-hs,+hs,-hs))+center;//Front top left
	if(contact(ftlf,normal))
	{
		contactPoints.push_back(ftlf);
	}

	Vectormath::Aos::Vector3 ftrt = rot.multiplyByVector(Vectormath::Aos::Vector3(+hs,+hs,-hs))+center;//Front top right
	if(contact(ftrt,normal))
	{
		contactPoints.push_back(ftrt);
	}

	Vectormath::Aos::Vector3 bblf = rot.multiplyByVector(Vectormath::Aos::Vector3(-hs,-hs,+hs))+center;//Back bottom left
	if(contact(bblf,normal))
	{
		contactPoints.push_back(bblf);
	}

	Vectormath::Aos::Vector3 bbrt = rot.multiplyByVector(Vectormath::Aos::Vector3(+hs,-hs,+hs))+center;//Back bottom right
	if(contact(bbrt,normal))
	{
		contactPoints.push_back(bbrt);
	}

	Vectormath::Aos::Vector3 btlf = rot.multiplyByVector(Vectormath::Aos::Vector3(-hs,+hs,+hs))+center;//Back top left
	if(contact(btlf,normal))
	{
		contactPoints.push_back(btlf);
	}

	Vectormath::Aos::Vector3 btrt = rot.multiplyByVector(Vectormath::Aos::Vector3(+hs,+hs,+hs))+center;//Back top right
	if(contact(btrt,normal))
	{
		contactPoints.push_back(btrt);
	}

	return contactPoints;
}

bool CollisionDetection::contact(Vectormath::Aos::Vector3 point,Vectormath::Aos::Vector3 normal)
{
	float d = dot(normal,point);
	if(d<0)
	{
		return true;
	}
}

/**
 * take any int and returns the absolute value of that int
 */
float CollisionDetection::toAbsolute(float x)
{
	if(x<0)
	{
		return x*-1;
	}
	return x;
}
