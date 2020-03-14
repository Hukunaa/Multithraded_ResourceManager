#version 460 core

out vec4 color;

in vec3 frag_pos;
in vec3 o_normal;
in vec3 alightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float time;

void main()
{
    vec3 lightColor = vec3(cos(time), sin(time), -sin(time));

    vec3 lightpos = vec3(0, 80, -8);
    vec3 objectColor = vec3(1.0, 1.0, 1.0);
	vec3 ambientColor = vec3(1);

    vec3 viewDir = normalize(viewPos - frag_pos);
    // ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * ambientColor;
  	
    // diffuse 
    vec3 norm = o_normal;

    vec3 lightDir = normalize(lightpos - frag_pos);

    float checkSide = dot(viewDir, norm);

    float diffStrength = 40;
    float dist = distance(frag_pos, lightpos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffStrength * ((diff * lightColor) / (dist));
    
    // specular
    float specularStrength = 0.2;
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular) * objectColor;
    vec4 FragColor = vec4(result, 1.0);
    color = FragColor;
};