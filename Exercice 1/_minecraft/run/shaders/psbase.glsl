
varying vec3 normal;
varying vec3 vertex_to_light_vector;
varying vec4 color;
uniform vec3 lightDir;
uniform float ambientLevel;
uniform mat4 invertView;
uniform sampler2D colorMap;

void main()
{
	float intensity;
	vec3 n = normalize(normal);
	intensity = dot(vec3(gl_LightSource[0].position),n);

		// Calculating The Diffuse Term And Clamping It To [0;1]
	float DiffuseTerm = clamp(dot(normal, vertex_to_light_vector), 0.0, 1.0);
	color = texture2D( colorMap, gl_TexCoord[0].st);

	if (intensity > 0.95)
		color *= vec4(1.0,0.9,0.9,1.0); 
	else if (intensity > 0.50) 
		color *= vec4(1.0,0.7,0.7,1.0); 
	else if (intensity > 0.25) 
		color *= vec4(0.8,0.6,0.6,1.0); 
	else color *= vec4(0.6,0.5,0.5,1.0); 
	
	gl_FragColor = color * (DiffuseTerm*(1-ambientLevel) + ambientLevel);

	gl_FragColor.a = color.a;




}
