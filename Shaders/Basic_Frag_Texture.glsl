#version 330 core
uniform vec3 u_color;
uniform sampler2D sampler;
varying vec2 vert_uv;
void main()
{
if(vert_uv.x<0.0 || vert_uv.y<0.0)
   gl_FragColor=vec4(u_color,0);
else
   gl_FragColor=texture2D(sampler,vert_uv);
}