#version 130

in vec3 position;
in vec3 normal;

out vec3 fColor;

uniform mat4 projection;
uniform mat4 transform;
uniform vec3 lightPosition;
uniform vec3 diffuseColor;

void main() {
      vec3 N = normal;
      vec3 L = position - lightPosition;
      N = normalize(N);
      L = normalize(L);
      float intensity = max(dot(N,L),0.0);
      vec4 clipPosition=vec4(position,1); // coordonnées homogènes

      clipPosition = projection*transform*clipPosition; // transformation par la matrice de projection

      fColor=intensity*diffuseColor;
      gl_Position=clipPosition; // gl_Position = clip coordinates
}
