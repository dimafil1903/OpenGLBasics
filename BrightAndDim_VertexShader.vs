#version 330

attribute vec3 position;

varying vec4 vertexColor; // specify a color output to the fragment shader
uniform float time;
uniform vec3 rgb;
uniform mat4 modelView;
uniform mat4 modelProj;
void main()
{

    gl_Position = modelProj * modelView * vec4(position, 1.0); // see how we directly give a vec3 to vec4's constructor
    vertexColor = noise4(1); // set the output variable to a dark-red color
}