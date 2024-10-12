#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 objectColour;

void main()
{    
    color = vec4(objectColour, 0.5);
}  