#version 460 core
out vec4 fragColor;
in vec3 normal;

void main(){
	vec3 lightDir = vec3(0, 1, 0);
	float ndotl = dot(-lightDir, normal);
	vec3 ambient = vec3(0.7, 0.7, 0.7);
	vec3 diffuse = ndotl * vec3(1, 1, 1);
	vec3 color = ambient + diffuse;
	fragColor = vec4(color, 1.0);
}
