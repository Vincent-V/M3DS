#version 130

uniform sampler2D depthTexture;

in vec4 fTexCoord;

out vec4 fragColor;

void main() {

    vec4 texCoord=fTexCoord;
    texCoord.xyz/=texCoord.w;

    texCoord.x = (texCoord.x+1)/2;
    texCoord.y = (texCoord.y+1)/2;
    texCoord.z = (texCoord.z+1)/2;

    if(texCoord.z>=0){
      //fragColor=texture(depthTexture,texCoord.xy);
        if(texCoord.z-0.001>texture(depthTexture,texCoord.xy).z){
            fragColor=vec4(0,0,0,0.6);
        }
        else {
            fragColor=vec4(0,0,0,0);
        }
    }
    else {
      fragColor=vec4(0,0,0,0);
    }
}
