 
#version 330 core
attribute vec3 position;
attribute vec2 uv;
uniform mat4 mvp;

varying vec2 vert_uv;
void main()
{
   vert_uv =uv;
   gl_Position=mvp* vec4( position,1);
}