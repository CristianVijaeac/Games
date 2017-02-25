#version 330
 
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform int t1;
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function
	vec4 color = texture2D(texture_1, texcoord);
	if(t1 == 1)
	{
		color = mix(texture2D(texture_2,texcoord),texture2D(texture_1,texcoord),0.5f);
	}
	if(color.a < 0.5f)
		discard;
	out_color = color;
}