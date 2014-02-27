#version 330

smooth in vec4 theColor;

out vec4 outputColor;

void main()
{
    float lerp = gl_FragCoord.y / 500.0;
	outputColor = mix(vec4(0.0,0.0,0.0,1.0), theColor,lerp);
}
