#version 330 core

out vec4 daColor;
in vec3 theColor;
void main()
{
   //daColor=vec4(0.0,1.0,0.0,1.0);
   //lec_13->0:11->(RGBA)turn everything in to green
   
   daColor=vec4(theColor,1.0);
}