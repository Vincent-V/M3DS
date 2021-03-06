#include <math.h>
#include "Car.h"
#include "GLTool.h"
#include "GLRender.h"

using namespace p3d;
using namespace std;


// ************************************************************
Car::~Car() {
}

Car::Car() {
  _orientation.setIdentity();
  _position.set(0,0,0);
  _steering=0;
  _rotateWheel=0;
  _acceleration=0;
  _velocity=0;
}

// ******************************************************************
// méthodes à compléter lors du TP
void Car::drawRim() {

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.scale(0.2,0.2,4);
    drawCylinder();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.rotate(45,1,0,0);
    p3d::modelviewMatrix.translate(0,1.4,-0.5);
    p3d::modelviewMatrix.scale(0.2,0.2,4);
    drawCylinder();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.rotate(90,1,0,0);
    p3d::modelviewMatrix.translate(0,2,-2);
    p3d::modelviewMatrix.scale(0.2,0.2,4);
    drawCylinder();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.rotate(135,1,0,0);
    p3d::modelviewMatrix.translate(0,1.4,-3.5);
    p3d::modelviewMatrix.scale(0.2,0.2,4);
    drawCylinder();
    p3d::modelviewMatrix.pop();
}

void Car::drawWheel() {
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(0,0,-2);

    p3d::diffuseColor=Vector3(0.5,0.5,0.5);
    drawRim();

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.rotate(90,0,1,0);
    p3d::modelviewMatrix.translate(-2,0,0);
    p3d::modelviewMatrix.scale(2.5,2.5,1.5);
    p3d::diffuseColor=Vector3(0,0,0);
    drawTorus();
    p3d::modelviewMatrix.pop();


    p3d::modelviewMatrix.pop();
}

void Car::drawAxle() {
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(0,0,-2);

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.rotate(90,0,1,0);
    p3d::modelviewMatrix.scale(0.2,0.2,6);
    p3d::diffuseColor=Vector3(0,0,0);
    drawCylinder();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.pop();
}

void Car::drawBody() {
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(0,0,-2);

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(0,1.5,1.8);
    p3d::modelviewMatrix.scale(2,2,6);
    p3d::diffuseColor=Vector3(1,1,0);
    drawCube();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(0,5.5,-2.2);
    p3d::modelviewMatrix.scale(2,2,2);
    p3d::diffuseColor=Vector3(1,1,0);
    drawCube();
    p3d::modelviewMatrix.pop();
    p3d::modelviewMatrix.pop();
}

void Car::drawWA(){
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.rotate(_steering, 0, 1,0);


    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(3,0,0);

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.rotate(_rotateWheel, 1, 0,0);
    drawWheel();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.pop();
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(-3,0,0);
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.rotate(_rotateWheel, 1, 0,0);
    drawWheel();
    p3d::modelviewMatrix.pop();
    p3d::modelviewMatrix.pop();
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(-3,0,2);

    drawAxle();
    p3d::modelviewMatrix.pop();
    p3d::modelviewMatrix.pop();
}

void Car::draw() {

    p3d::modelviewMatrix.scale(0.8,0.8,0.8);
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(0,0,-4);
    drawWA();
    p3d::modelviewMatrix.pop();
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(0,0,4);
    drawWA();
    p3d::modelviewMatrix.pop();
    drawBody();

}


void Car::drawWorld() {
  p3d::modelviewMatrix.push();

  modelviewMatrix.translate(_position);
  modelviewMatrix.rotate(_orientation);
  draw(); // tracé de la voiture dans son repère local
  p3d::modelviewMatrix.pop();
}

void Car::move() {
  _acceleration+=-_velocity/50;
  _velocity+=_acceleration;
  _rotateWheel+=_velocity*20;
  _steering-=_steering/10*fabs(_velocity);

  _orientation.rotate(_steering*_velocity/(1.0+fabs(_velocity)),Vector3(0,1,0)); // le /100 est déterminé par essai/erreur
  _position.add(_orientation*Vector3(0,0,1)*_velocity*0.2);

}


void Car::accelerate() {
  _acceleration=0.05;

}

void Car::decelerate() {
  _acceleration=0;
}

void Car::brake() {
  _acceleration=-0.02;

}

void Car::turnLeft() {
  _steering+=0.5;
  if (_steering>35) _steering=35;
}

void Car::turnRight() {
  _steering-=0.5;
  if (_steering<-35) _steering=-35;
}





