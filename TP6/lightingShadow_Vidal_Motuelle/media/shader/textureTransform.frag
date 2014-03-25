#version 130

uniform sampler2D image1;

in vec4 fTexCoord;

out vec4 fragColor;

void main() {
  vec4 texCoord=fTexCoord;
  texCoord.xy/=texCoord.w;

  fragColor=texture(image1,texCoord.st);
}
