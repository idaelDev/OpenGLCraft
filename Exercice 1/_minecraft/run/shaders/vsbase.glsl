
varying vec3 normal;
varying vec3 vertex_to_light_vector;
varying vec4 color;

uniform float elapsed;
uniform mat4 invertView;
 
void main()
{
	
	gl_Position = ftransform();
	gl_TexCoord[0] = gl_MultiTexCoord0;
		
	// Transforming The Normal To ModelView-Space
	normal = gl_NormalMatrix * gl_Normal; 

	// Transforming The Vertex
	gl_Vertex = invertView *  gl_ModelViewMatrix * gl_Vertex;

	if(gl_Vertex.z <= 10.1)
	{
		gl_Vertex.z += sin(elapsed * 5 + (gl_Vertex.y + gl_Vertex.x) );
		normal.x += sin(elapsed * 0.2 + (gl_Vertex.x + gl_Vertex.y) * 5);
		normal.y += sin(elapsed * 0.2 + (gl_Vertex.x + gl_Vertex.y * 2));
		//normal.z += sin(elapsed * 2 + (gl_Vertex.z));
		//normal.y += sin(elapsed * 0.4 + (gl_Vertex.x + gl_Vertex.y ) * 6);
		//normal.x += sin(elapsed * 2 + (gl_Vertex.x + gl_Vertex.y  )* 6 );
	}

	gl_Position = gl_ProjectionMatrix * inverse(invertView) * gl_Vertex;
	//Direction lumiere
	vertex_to_light_vector = vec3(gl_LightSource[0].position);
	
	//Couleur
	color = gl_Color;

}
