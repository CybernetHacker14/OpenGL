#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main(){
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D crateTexture;
uniform sampler2D dirtTexture;
uniform sampler2D maskTexture;

uniform int renderChoice;

void main(){
	vec4 crateColor = texture(crateTexture, v_TexCoord);
	vec4 dirtColor = texture(dirtTexture, v_TexCoord);
	vec4 maskColor = texture(maskTexture, v_TexCoord);

	if(renderChoice == 1){
		color = crateColor;

	}else if(renderChoice == 2){
		color = mix(crateColor, dirtColor, maskColor.a);
	}
}