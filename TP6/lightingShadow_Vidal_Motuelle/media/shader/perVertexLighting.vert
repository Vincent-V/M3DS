#version 130

in vec3 position;  // in Local coordinates
in vec3 normal;    // in Local coordinates

uniform mat4 modelviewMatrix; // Eye->Local
uniform mat3 normalMatrix;
uniform mat4 mvp;             // Projection * Eye->Local = Clip coordinates -> Local

uniform vec3 lightPosition;   // in Eye coordinates.

uniform vec3 materialDiffuse,materialSpecular;
uniform vec4 materialAmbient;

out vec4 fColor;

void main() {
  float diffuseIntensity;
  float specularIntensity=0;
  vec4 positionEye;
  vec3 L,V,N;

  positionEye=modelviewMatrix*vec4(position,1);

  V=-positionEye.xyz/positionEye.w;
  L=lightPosition+V;
  N=normalMatrix*normal;

  L=normalize(L);
  V=normalize(V);
  N=normalize(N);


  diffuseIntensity=max(dot(N,L),0.0);

  fColor=vec4(diffuseIntensity*materialDiffuse+materialAmbient.xyz,materialAmbient.a);

  gl_Position=mvp*vec4(position,1);
}
