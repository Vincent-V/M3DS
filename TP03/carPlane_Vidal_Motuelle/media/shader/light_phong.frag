#version 130

/**
  <c> F.Aubert Univ-Lille1
  **/

struct Material {
  vec3 diffuse;
  vec3 specular;
  int shininess;
};


vec3 specular(in vec3 N,in vec3 L,in vec3 V,in int s,in vec3 ks,in float is) {
  vec3 H=(L+V)/length(L+V);
  float intensity;
  intensity=pow(max(dot(H,N),0.0),float(s));
  return intensity*ks*is;
}

uniform Material material;
uniform vec4 ambient;
uniform float lightIntensity[4];

in vec3 fNormal,fView;
in vec3 fLight[4];
in vec3 colorDiffuse;
out vec4 fragColor;

void main() {

  vec3 N,L,V;
  vec3 colorSpec;

  N=normalize(fNormal);
  V=normalize(fView);

  if (dot(N,V)<0) N=-N;

  colorSpec=vec3(0,0,0);
  for(int i=0;i<4;++i) {
    L=normalize(fLight[i]);
    colorSpec+=specular(N,L,V,material.shininess,material.specular,lightIntensity[i]);
  }

  fragColor=vec4(colorDiffuse+colorSpec,ambient.a);
//  fragColor=vec4(N,1);
}
