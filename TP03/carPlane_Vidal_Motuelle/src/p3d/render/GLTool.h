#ifndef GLTOOL_H
#define GLTOOL_H

#include "GLPrimitive.h"
#include "GLText.h"
#include "Camera.h"

/**
@file
@author F. Aubert
@brief Useful draw : arrow, ground, texture
*/

namespace p3d {

void initGLTool();

void drawArrow(const p3d::Vector3 &a,const p3d::Vector3 &u,double radius,const std::string &s1,const std::string &s2,double arrowRatio);
void drawGround(const p3d::Texture &texture, bool visible=true);
void drawTexture(const p3d::Texture &texture, double x=0, double y=0, double w=0.5, double h=0.5, bool depthTexture=false);
void apply(const p3d::Camera &c);
}

#endif // GLTOOL_H

