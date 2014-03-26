#version 130

uniform sampler2D image1;

in vec4 fTexCoord;

out vec4 fragColor;

void main() {

  vec4 texCoord=fTexCoord;
  texCoord.xy/=texCoord.w;

  texCoord.x = (texCoord.x+1)/2;
  texCoord.y = (texCoord.y+1)/2;

  if(texCoord.z>=0)
    fragColor=texture(image1,texCoord.st);
  else {
    fragColor=vec4(0,0,0,0);
  }
}
