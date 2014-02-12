#version 130
/**
  <c> F.Aubert Univ-Lille1
  **/

in vec3 fNormal;
in vec3 fLight[4];
in vec3 fEye;
in vec2 fTexCoord;

out vec4 fragColor;

uniform sampler2D texture0;
uniform float lightIntensity[4];

void main(void) {
  vec3 light;
  float intensity;
  vec3 normal=normalize(fNormal);
  if (dot(normal,-fEye)<0.0) normal=-normal;
  for(int i=0;i<4;++i) {
    light=normalize(fLight[i]);
    intensity+=max(dot(normal,light),0.0)*lightIntensity[i];
  }
  vec4 color=texture2D(texture0,fTexCoord);
  fragColor=color*vec4(intensity,intensity,intensity,1);
}
