#version 130

/**
  <c> F.Aubert Univ-Lille1
  **/

struct Material {
  vec3 diffuse;
  vec3 specular;
  int shininess;
};


vec3 diffuse(in vec3 N,in vec3 L,in vec3 kd,in float id) {
  float intensity=max(dot(N,L),0.0);
  return intensity*kd*id;
}

uniform Material material;


out vec3 colorDiffuse;
out vec3 fNormal,fView;
out vec3 fLight[4];


in vec3 position;
in vec3 normal;


uniform mat4 projectionMatrix;
uniform mat4 modelviewMatrix;
uniform mat3 normalMatrix;
uniform mat4 mvp;

uniform vec4 lightPosition[4];
uniform float lightIntensity[4];


void main() {

  fNormal=normalMatrix*normal;
  vec4 vertexEye=modelviewMatrix*vec4(position,1.0);
  fView=-vertexEye.xyz/vertexEye.w;
  int i;
  for(i=0;i<4;++i) {
    fLight[i]=lightPosition[i].xyz+fView;
    fLight[i]=normalize(fLight[i]);
  }
  fNormal=normalize(fNormal);

  vec3 normalDiffuse;
  if (dot(fNormal,fView)<0.0) normalDiffuse=-fNormal; else normalDiffuse=fNormal;

  colorDiffuse=vec3(0,0,0);
  for(i=0;i<4;++i) {
    colorDiffuse+=diffuse(normalDiffuse,fLight[i],material.diffuse,lightIntensity[i]);
  }


  gl_Position=mvp*vec4(position,1.0);
}
