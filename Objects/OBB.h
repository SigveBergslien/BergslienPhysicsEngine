/*
 * OBB.h
 *
 *  Created on: Jan 23, 2011
 *      Author: ziggy
 */

#ifndef OBB_H_
#define OBB_H_

#include "Maths/Quaternion.h"
#include "DynamicObject.h"

class OBB: public DynamicObject{
private:
	float halfSize;
public:
	OBB(float hs, Vectormath::Aos::Vector3 c, float m);
	~OBB();
	void Draw();
	float getHalfSize();
	Quaternion getRot();
};
#endif /* OBB_H_ */
