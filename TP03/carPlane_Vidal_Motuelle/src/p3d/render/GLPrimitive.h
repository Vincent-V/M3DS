#ifndef GLUTILPRIMITIVE_H
#define GLUTILPRIMITIVE_H

#include "GLRender.h"
#include "Texture.h"
#include "Vector3.h"


/**
@file
@author F. Aubert
@brief Cone, Cube, Cylinder, Sphere, Torus, Square, Segment, Lines, Grid
*/

namespace p3d {

/** PRIMITIVES **/
void initGLPrimitive();
void initCube();
void initCylinder(bool cap=true,int nbSlice=20);
void initCone(bool cap=true,int nbSlice=20);
void initSphere(int nbSlice=20,int nbStack=20);
void initTorus(int nbSlice=20,int nbStack=20);
void initSquare();
void initSegment();


void drawSquare(double size=2.0);
void drawCube(double size=2.0);
void drawCylinder(double size=2.0);
void drawSphere(double size=1.0);
void drawCone(double size=1.0);
void drawTorus(double size=1.0);

void drawLine(const Vector3 &a,const Vector3 &b);
void drawLineTo(const Vector3 &a);
void drawMoveTo(const Vector3 &a);
void drawPoint(const Vector3 &a);

void drawLineStrip(const std::vector<p3d::Vector3> &point, int nbVertex=-1);
void drawLines(const std::vector<p3d::Vector3> &point, int nbVertex=-1);
void drawPoints(const std::vector<p3d::Vector3> &point);
void drawGrid(const std::vector<Vector3> &point,int nbU);
void fillGrid(const std::vector<Vector3> &point,int nbU);

}



#endif // GLUTILPRIMITIVE_H

