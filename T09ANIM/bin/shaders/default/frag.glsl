/**/
#version 330
 
layout(location = 0) out vec4 OutColor;
 
in vec4 DrawColor;
in vec3 DrawNormal;  
in vec3 DrawPos;
in vec3 DrawPosOrg;

uniform float Time, GlobalTime;	
 
void main( void )
{
  vec3 L = normalize(vec3(10 * sin(8 * Time), 1, 1));
  vec3 N = normalize(DrawNormal);
                            
  
  OutColor = DrawColor;
}
