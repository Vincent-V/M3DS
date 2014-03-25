#version 130

out vec4 fragColor;

uniform vec3 materialDiffuse,materialSpecular;
uniform vec4 materialAmbient;

void main() {

  vec3 N,L,V;
  vec4 color=vec4(0,0,0,0);


  fragColor=color;
}
