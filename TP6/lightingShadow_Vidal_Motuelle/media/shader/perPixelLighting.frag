#version 130

out vec4 fragColor;

uniform vec3 materialDiffuse,materialSpecular;
uniform vec4 materialAmbient;

varying vec3 fN, fL, fV;

void main() {

  vec3 N,L,V,R;

  float diffuseIntensity;
  float specularIntensity=0;

  L=normalize(fL);
  V=normalize(fV);
  N=normalize(fN);

  diffuseIntensity=max(dot(N,L),0.0); //calcul couleurDiffus

  R = 2*(dot(L,N))*N-L; //calcul de R
  R = normalize(R);

  specularIntensity = pow(dot(V,R),50); //calcul couleurSpeculaire


  fragColor=vec4(diffuseIntensity*materialDiffuse+materialAmbient.xyz+(materialSpecular*specularIntensity),materialAmbient.a);
}
