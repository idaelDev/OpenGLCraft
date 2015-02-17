#include "Primitive.h"


Primitive::Primitive()
{
}

void Primitive::cube(NYVert3Df position, NYVert3Df rotation, NYVert3Df scale)
{
	glTranslatef(position.X, position.Y, position.Z);
	glRotated(rotation.X, 1, 0, 0);
	glRotated(rotation.Y, 0, 1, 0);
	glRotated(rotation.Z, 0, 0, 1);

	glBegin(GL_TRIANGLES);


	//Face1 UP
	makeMat(0, 0, 1);

	glColor3d(0, 0, 1);
	glNormal3f(-1, -1, 1);
	glVertex3d(-scale.X, -scale.Y, scale.Z);
	glNormal3f(1, -1, 1);
	glVertex3d(scale.X, -scale.Y, scale.Z);
	glNormal3f(-1, 1, 1);
	glVertex3d(-scale.X, scale.Y, scale.Z);
	glNormal3f(1, -1, 1);
	glVertex3d(scale.X, -scale.Y, scale.Z);
	glNormal3f(1, 1, 1);
	glVertex3d(scale.X, scale.Y, scale.Z);
	glNormal3f(-1, 1, 1);
	glVertex3d(-scale.X, scale.Y, scale.Z);

	//Face2 Down
	
	glNormal3f(-1, 1, -1);
	glVertex3d(-scale.X, scale.Y, -scale.Z);
	glNormal3f(1, -1, -1);
	glVertex3d(scale.X, -scale.Y, -scale.Z);
	glNormal3f(-1, -1, -1);
	glVertex3d(-scale.X, -scale.Y, -scale.Z);
	glNormal3f(-1, 1, -1);
	glVertex3d(-scale.X, scale.Y, -scale.Z);
	glNormal3f(1, 1, -1);
	glVertex3d(scale.X, scale.Y, -scale.Z);
	glNormal3f(1, -1, -1);
	glVertex3d(scale.X, -scale.Y, -scale.Z);


	//Face3 X Front
	makeMat(1, 0, 0);
	
	glColor3d(1, 0, 0);
	glNormal3f(1, -1, -1);
	glVertex3d(scale.X, -scale.Y, -scale.Z);
	glNormal3f(1, 1, -1);
	glVertex3d(scale.X, scale.Y, -scale.Z);
	glNormal3f(1, -1, 1);
	glVertex3d(scale.X, -scale.Y, scale.Z);
	glNormal3f(1, 1, -1);
	glVertex3d(scale.X, scale.Y, -scale.Z);
	glNormal3f(1, 1, 1);
	glVertex3d(scale.X, scale.Y, scale.Z);
	glNormal3f(1, -1, 1);
	glVertex3d(scale.X, -scale.Y, scale.Z);

	//Face4 X Back
	
	glNormal3f(-1, -1, 1);
	glVertex3d(-scale.X, -scale.Y, scale.Z);
	glNormal3f(-1, 1, -1);
	glVertex3d(-scale.X, scale.Y, -scale.Z);
	glNormal3f(-1, -1, -1);
	glVertex3d(-scale.X, -scale.Y, -scale.Z);
	glNormal3f(-1, -1, 1);
	glVertex3d(-scale.X, -scale.Y, scale.Z);
	glNormal3f(-1, 1, 1);
	glVertex3d(-scale.X, scale.Y, scale.Z);
	glNormal3f(-1, 1, -1);
	glVertex3d(-scale.X, scale.Y, -scale.Z);

	//Face5 Y Front
	makeMat(0, 1, 0);
	
	glColor3d(0, 1, 0);
	glNormal3f(1, 1, -1);
	glVertex3d(scale.X, scale.Y, -scale.Z);
	glNormal3f(-1, 1, -1);
	glVertex3d(-scale.X, scale.Y, -scale.Z);
	glNormal3f(1, 1, 1);
	glVertex3d(scale.X, scale.Y, scale.Z);
	glNormal3f(-1, 1, -1);
	glVertex3d(-scale.X, scale.Y, -scale.Z);
	glNormal3f(-1, 1, 1);
	glVertex3d(-scale.X, scale.Y, scale.Z);
	glNormal3f(1, 1, 1);
	glVertex3d(scale.X, scale.Y, scale.Z);

	//Face6 Y Back
	
	glNormal3f(1, -1, 1);
	glVertex3d(scale.X, -scale.Y, scale.Z);
	glNormal3f(-1, -1, -1);
	glVertex3d(-scale.X, -scale.Y, -scale.Z);
	glNormal3f(1, -1, -1);
	glVertex3d(scale.X, -scale.Y, -scale.Z);
	glNormal3f(1, -1, 1);
	glVertex3d(scale.X, -scale.Y, scale.Z);
	glNormal3f(-1, -1, 1);
	glVertex3d(-scale.X, -scale.Y, scale.Z);
	glNormal3f(-1, -1, -1);
	glVertex3d(-scale.X, -scale.Y, -scale.Z);
	
	glEnd();
}

void Primitive::makeMat(float r, float g, float b)
{
	//Diffuse
	GLfloat materialDiffuse[] = { r*0.7, g*0.7, b*0.7, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	//Materiau spéculaire, le meme pour tout le cube
	GLfloat whiteSpecularMaterial[] = { 0.3, 0.3, 0.3, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecularMaterial);
	GLfloat mShininess = 100;
	glMaterialf(GL_FRONT, GL_SHININESS, mShininess);

	////Emissive
	//GLfloat emissive[] = { r, g, b, 0.02};
	//glMaterialfv(GL_FRONT, GL_EMISSION, emissive);

	//Ambient
	GLfloat materialAmbient[] = { 0.3, 0.3, 0.3, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
}

Primitive::~Primitive()
{
}
