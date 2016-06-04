#version 140


//in vec3 fColor;

//out vec4 fragColor;

in vec3 fColor;
in vec2 TexCoord;

uniform float opacity;
uniform sampler2D image;

out vec4 fragColor;

void main()
{
  //fragColor = vec4( fColor, 1.0f );
  fragColor = texture2D(image, TexCoord);
}
