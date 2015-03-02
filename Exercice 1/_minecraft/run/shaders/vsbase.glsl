
varying vec3 normal;
varying vec3 vertex_to_light_vector;
varying vec4 color;

uniform float elapsed;
uniform mat4 invertView;
 
void main()
{
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	// Transforming The Normal To ModelView-Space
	normal = gl_NormalMatrix * gl_Normal; 
	
	// Transforming The Vertex
	vec4 vertex = gl_Vertex;
	vertex = invertView *  gl_ModelViewMatrix * vertex;

	if(vertex.z <= 10.1)
	{
		vertex.z += sin(elapsed * 5 + (vertex.y + vertex.x) );
		normal.x += sin(elapsed * 0.2 + (vertex.x + vertex.y) * 5);
		normal.y += sin(elapsed * 0.2 + (vertex.x + vertex.y * 2));
		//normal.z += sin(elapsed * 2 + (vertex.z));
		//normal.y += sin(elapsed * 0.4 + (vertex.x + vertex.y ) * 6);
		//normal.x += sin(elapsed * 2 + (gl_Vertex.x + vertex.y  )* 6 );
	}
	
	gl_Position = gl_ProjectionMatrix * inverse(invertView) * vertex;
	//Direction lumiere
	vertex_to_light_vector = vec3(gl_LightSource[0].position);
	
	//Couleur
	color = gl_Color;

}
