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

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform sampler2D u_Texture2;
uniform int u_RenderChoice;

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

void main(){
	vec4 texColor = texture(u_Texture, v_TexCoord);
	vec4 texColor2 = texture(u_Texture2, v_TexCoord);

	if(u_RenderChoice == 1){
		color = texColor;
	}
	else if(u_RenderChoice == 2){	
		color = u_Color;
	}
	else if(u_RenderChoice == 3){
		color = mix(texColor, texColor2, 0.2);
	}
	else if(u_RenderChoice == 4){
		color = mix(texColor, texColor2, 0.2) * u_Color;
	}
}