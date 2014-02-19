#ifndef GLRENDER_H
#define GLRENDER_H

#include "glsupport.h"

#include <vector>
#include <string>

#include "Vector4.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Shader.h"

/**
@file
@author F. Aubert
@brief Simple GL renderer
*/

namespace p3d {

void initGLRender();

extern Matrix4 projectionMatrix;
extern Matrix4 modelviewMatrix;
extern Matrix4 textureMatrix;
extern Vector4 ambientColor;
extern Vector3 diffuseColor;
extern Vector3 specularColor;
extern std::vector<Vector4> lightPosition;
extern std::vector<float> lightIntensity;
extern int shininess;
extern Vector4 color;


void uniformTransformation(); // shader has : modelviewMatrix, projectionMatrix, normalMatrix *and* mvp. normalMatrix is computed from modelviewMatrix
void uniformMVP(); // shader has : mvp. mvp is computed from projectionMatrix*modelviewMatrix
void uniformModelview(); // shader has : modelviewMatrix and normalMatrix
void uniformProjection(); // shader has : projectionMatrix
void uniformLightPosition(); // shader has : lightPosition
void uniformMaterial(); // shader has : material.ambient, material.diffuse, material.specular, material.shininess
void uniformAmbient();
void uniformAmbient(const Vector4 &c);

void shaderLightPhong();  // enable and init uniform
void shaderTextureLight();
void shaderVertexAmbient();
void shaderTextureAmbient();
void shaderTexture3DAmbient();
void shaderTexture4DAmbient();
void shaderTextureDepth();

void material(const p3d::Vector4 &ambientColor,const p3d::Vector3 &diffuseColor,const p3d::Vector3 &specularColor,int shininess);
void materialBlueGreen();
void shader(p3d::Shader *s);

}




#endif // GLUTILRENDER_H
