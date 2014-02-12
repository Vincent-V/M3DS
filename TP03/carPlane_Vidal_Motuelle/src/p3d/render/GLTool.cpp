#include "GLTool.h"
#include "GLRender.h"
#include "Shader.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "VertexArray.h"
#include "Camera.h"

#include <vector>

/*!
*
* @file
*
* @brief
* @author F. Aubert
*
*/

using namespace std;

namespace p3d {


void initGLTool() {
  initGLRender();
  initGLPrimitive();
}

void apply(const p3d::Camera &c) {
  p3d::projectionMatrix=c.projectionMatrix();
  p3d::modelviewMatrix=c.cameraWorld();
  glViewport(c.viewX(),c.viewY(),c.viewWidth(),c.viewHeight());
}

void drawGround(const p3d::Texture &texture,bool visible) {
  texture.bind(0);
  Vector4 saveLight=p3d::lightPosition[0];
  p3d::modelviewMatrix.push();
  p3d::modelviewMatrix.rotate(-90,Vector3(1,0,0));
  p3d::lightPosition[0]=p3d::modelviewMatrix.transform(Vector4(0,0,2,1));
  p3d::modelviewMatrix.scale(Vector3(50,50,1));
  if (visible)
    p3d::shaderTextureLight();
  else
    p3d::shaderTextureAmbient();

  p3d::drawSquare();

  p3d::modelviewMatrix.pop();
  p3d::lightPosition[0]=saveLight;
}

void drawTexture(const p3d::Texture &texture,double x,double y,double w,double h,bool depthTexture) {
  texture.bind(0);
  p3d::modelviewMatrix.push();
  p3d::projectionMatrix.push();
  p3d::projectionMatrix=Matrix4::fromOrtho(0,1,0,1,0,1);
  // square is drawn in [-1,1]
  p3d::modelviewMatrix.setIdentity();
  p3d::modelviewMatrix.translate(x,y,-0.00001);
  p3d::modelviewMatrix.scale(w/2.0,h/2.0,1);
  p3d::modelviewMatrix.translate(1,1,0);
  if (depthTexture)
    p3d::shaderTextureDepth();
  else
    p3d::shaderTextureAmbient();

  p3d::drawSquare();
  p3d::projectionMatrix.pop();
  p3d::modelviewMatrix.pop();
}

} // namespace p3d



