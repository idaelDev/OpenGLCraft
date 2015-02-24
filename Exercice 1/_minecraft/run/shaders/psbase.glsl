
#pragma glslify: random = require(glsl-random)
varying vec3 normal;
varying vec3 vertex_to_light_vector;
varying vec4 color;
uniform vec3 lightDir;

uniform float ambientLevel;

uint hash( uint x ) {
    x += ( x << 10u );
    x ^= ( x >>  6u );
    x += ( x <<  3u );
    x ^= ( x >> 11u );
    x += ( x << 15u );
    return x;
}

float random( float f ) {
    const uint mantissaMask = 0x007FFFFFu;
    const uint one          = 0x3F800000u;
    
    uint h = hash( floatBitsToUint( f ) );
    h &= mantissaMask;
    h |= one;
    
    float  r2 = uintBitsToFloat( h );
    return r2 - 1.0;
}
/*
void main()
{
	// Scaling The Input Vector To Length 1
	vec3 normalized_normal = normalize(normal);
	vec3 normalized_vertex_to_light_vector = normalize(vertex_to_light_vector);

	// Calculating The Diffuse Term And Clamping It To [0;1]
	float DiffuseTerm = clamp(dot(normal, vertex_to_light_vector), 0.0, 1.0);

	// Calculating The Final Color
	gl_FragColor = color * (DiffuseTerm*(1-ambientLevel) + ambientLevel);
	gl_FragColor.a = color.a;
	gl_FragColor = color;

	//float r = random(color);

	//gl_FragColor = vec4( r,r,r, 1.0 );
}
*/

void main()
{
	float intensity;
	vec3 n = normalize(normal);
	intensity = dot(vec3(gl_LightSource[0].position),n);

		// Calculating The Diffuse Term And Clamping It To [0;1]
	float DiffuseTerm = clamp(dot(normal, vertex_to_light_vector), 0.0, 1.0);

	if (intensity > 0.95)
		color *= vec4(1.0,0.7,0.7,1.0); 
	else if (intensity > 0.5) 
		color *= vec4(0.8,0.5,0.5,1.0); 
	else if (intensity > 0.25) 
		color *= vec4(0.6,0.4,0.4,1.0); 
	else color *= vec4(0.4,0.3,0.3,1.0); 
	gl_FragColor = color * (DiffuseTerm*(1-ambientLevel) + ambientLevel);
	gl_FragColor.a = color.a;
}
