#version 130
        
in vec3 position;
in vec4 color;

out vec4 fColor;

        
void main() {
    fColor = color;
    gl_Position=vec4(position,1.0);
}
