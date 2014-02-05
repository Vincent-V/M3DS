#version 130

in vec3 position;
in vec3 color;

out vec3 fColor;

void main() {
  vec4 clipPosition=vec4(position,1);

  fColor=color;

  gl_Position=clipPosition;
}
