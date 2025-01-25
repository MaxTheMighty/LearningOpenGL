#version 330 core
uniform float time;
out vec4 FragColor;
in vec4 vertexColor;

void main()
{
    FragColor = vec4(sin(vertexColor.x+time),sin(vertexColor.y+time+2.09439),sin(vertexColor.z+time+4.1887),1.0f);
}