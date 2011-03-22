/*
 * main.cpp
 *
 *  Created on: 26. feb. 2010
 *      Author: ziggy
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <vectormath/scalar/cpp/vectormath_aos.h>
#include <iostream>
#include <vector>

#include"Objects/Plane.h"
#include"Objects/DynamicObject.h"
#include"Objects/Sphere.h"
#include "CollisionDetection.h"
#include "Objects/AABB.h"
#include "Objects/OBB.h"
#include "Objects/Maths/Quaternion.h"

#include"Objects/Maths/UnitTest_Math.h"
using namespace std;

using std::endl;


UnitTest_Math *mathTest = new UnitTest_Math();

float rot;
int frameRate=60;

Vectormath::Aos::Vector3 gravity= Vectormath::Aos::Vector3(0.0f,9.81f,0.0f);

CollisionDetection *cd = new CollisionDetection(); //Collision Handler

Plane *fl = new Plane(Vectormath::Aos::Vector3(0,0,100),Vectormath::Aos::Vector3(100,0,0),
		Vectormath::Aos::Vector3 (0,0,0));

vector<DynamicObject*> dynamicObjects;

AABB *cube = new AABB(10.0,10.0,10.0,Vectormath::Aos::Vector3(15,10,0),10);
OBB *orientedCube = new OBB(3,Vectormath::Aos::Vector3(-10.0,40.0,0.0),20);




#define RUN_GRAPHICS_DISPLAY 0x00;

/*
 * SDL timers run in separate threads.  In the timer thread
 * push an event onto the event queue.  This event signifies
 * to call display() from the thread in which the OpenGL
 * context was created.
 */

Uint32 display(Uint32 interval, void *param) {
    SDL_Event event;
    event.type = SDL_USEREVENT;
    event.user.code = RUN_GRAPHICS_DISPLAY;
    event.user.data1 = 0;
    event.user.data2 = 0;
    SDL_PushEvent(&event);
    return interval;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,-30.0,-100.0);
    fl->draw();
    cube->draw();
    orientedCube->Draw();
    for(unsigned int i = 0; i<dynamicObjects.size();i++ )
    {
    	//if(dynamicObjects[i]->getID()==0)
    	//{
    		Sphere * s= dynamic_cast<Sphere*>(dynamicObjects[i]);
    	//}
    	for(unsigned int j =i+1;j<dynamicObjects.size();j++)
    	{
        	//if(dynamicObjects[i]->getID()==0)
        	//{
        		Sphere* s2=dynamic_cast<Sphere*>(dynamicObjects[j]);
        	//}
    		cd->collision(s,s2);
    	}

    	if(cd->collision(fl,s))
    	{
    		s->setOnPlane(true);
    	}
    	else
    	{
    		s->setOnPlane(false);
    		dynamicObjects[i]->applyGravity(gravity,frameRate);
    	}
    	if(cd->collision(s,cube))
    	{

    	}
    	dynamicObjects[i]->draw();
    }
    cd->collision(dynamic_cast<Sphere*>(dynamicObjects[4]),orientedCube);
    rot++;
    SDL_GL_SwapBuffers();
}

int main(int argc, char ** argv) {

	mathTest->runTest();

	dynamicObjects.push_back(new Sphere(1.5f,Vectormath::Aos::Vector3(-15.0f,1.5f,0.0f),4.0));
	dynamicObjects.push_back(new Sphere(1.5f,Vectormath::Aos::Vector3(20.0f,1.5f,1.55f),3.0));
	dynamicObjects.push_back(new Sphere(1.5f,Vectormath::Aos::Vector3(30.0f,1.5f,-1.55f),2.0));
	dynamicObjects.push_back(new Sphere(1.5f,Vectormath::Aos::Vector3(10.0f,40.0f,0.0f),2.0));
	dynamicObjects.push_back(new Sphere(1.5f,Vectormath::Aos::Vector3(-10.0f,60.0f,0.0f),2.0));
	dynamicObjects[2]->applyForce(Vectormath::Aos::Vector3(0.1f,0.0f,0.0f));
	dynamicObjects[1]->applyForce(Vectormath::Aos::Vector3(0.1f,0.0f,0.0f));
	dynamicObjects[0]->applyForce(Vectormath::Aos::Vector3(50.0f,0.0f,0.0f));
	dynamicObjects[3]->applyForce(Vectormath::Aos::Vector3(-10.0f,0.0f,0.0f));
	//dynamicObjects[4]->applyForce(Vectormath::Aos::Vector3(10.0f,0.0f,0.0f));
	//dynamicObjects[4]->addTorque(Vectormath::Aos::Vector3(30.0f,0.0f,0.0f),Vectormath::Aos::Vector3(-11.0f,41.0f,0.0f));

	orientedCube->setOrientation(new Quaternion(20.0f,0.0f,0.0f,1.0f));
	//orientedCube->addTorque(Vectormath::Aos::Vector3(1.0f,0.0f,0.0f),Vectormath::Aos::Vector3(-3.0f,2.0f,0.0f));


    SDL_Surface * surf;
    Uint32 width = 640;
    Uint32 height = 480;
    Uint32 colour_depth = 16; // in bits
    Uint32 delay = 1000/frameRate; // in milliseconds

    // Initialise SDL - when using C/C++ it's common to have to
    // initialise libraries by calling a function within them.
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)<0) {
            cout << "Failed to initialise SDL: " << SDL_GetError() << endl;
            SDL_Quit();
    }

    // When we close a window quit the SDL application
    // Create a new window with an OpenGL surface
    if (!(surf = SDL_SetVideoMode(width, height, colour_depth, SDL_OPENGL))) {
            cout << "Failed to initialise video mode: " << SDL_GetError() << endl;
            SDL_Quit();
    }

    // Set the state of our new OpenGL context
    glViewport(0,0,(GLsizei)(width),(GLsizei)(height));
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)(width)/(GLfloat)(height),1.0f,10000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                // Black Background
    glClearDepth(1.0f);                                    // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                                // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // Really Nice Perspective Calculations

    // Call the function "display" every delay milliseconds
    SDL_AddTimer(delay, display, NULL);

    SDL_Event event;
   while(SDL_WaitEvent(&event)){
   switch (event.type){
   case SDL_QUIT:
   SDL_Quit();
   break;
   case SDL_USEREVENT:
   display();
   }
   }
    return 0;
}
