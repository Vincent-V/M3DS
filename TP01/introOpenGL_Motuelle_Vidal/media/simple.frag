#version 130

uniform sampler2D texture;
in vec2 fTexCoord;
in vec4 fColor;

out vec4 fragColor;
        
void main() {
    fragColor=texture2D(texture,fTexCoord);
}
