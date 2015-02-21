
varying vec3 normal;
varying vec3 vertex_to_light_vector;
varying vec4 color;
uniform float elapsed;
uniform mat4 invertView;
 
void main()
{

	// Transforming The Vertex
	gl_Vertex = invertView *  gl_ModelViewMatrix * gl_Vertex;
	if(gl_Vertex.z <= 10)
	{
		gl_Vertex.z += sin(elapsed*5 + gl_Vertex.x *0.5) *5;
		//gl_Vertex.z += sin(elapsed*5 + gl_Vertex.y *0.5) *5;
	}
	gl_Position = gl_ProjectionMatrix * inverse(invertView) * gl_Vertex;

	// Transforming The Normal To ModelView-Space
	normal = gl_NormalMatrix * gl_Normal; 

	//Direction lumiere
	vertex_to_light_vector = vec3(gl_LightSource[0].position);

	//Couleur
	color = gl_Color;
}
