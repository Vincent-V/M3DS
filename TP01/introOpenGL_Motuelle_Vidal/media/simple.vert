#version 130
        
in vec3 position;
//in vec4 color;
in vec2 texCoord;


out vec2 fTexCoord;

//uniform float coeff;
        
void main() {
    //vec3 newPosition=position;
    //newPosition=position*coeff;
    fTexCoord = texCoord;
    gl_Position=vec4(position,1.0);
}
