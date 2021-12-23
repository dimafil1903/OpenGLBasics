#version 120

#extension GL_EXT_gpu_shader4 : require


uniform float time;
uniform vec3 rgb;
varying vec4 vertexColor;

void main()
{
 gl_FragColor = vertexColor;
 }