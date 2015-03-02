#include "Primitive.h"


Primitive::Primitive()
{
}

void Primitive::cube(NYVert3Df position, NYVert3Df rotation, NYVert3Df scale)
{
	glPushMatrix();
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
	glPopMatrix();
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

void Primitive::skybox(NYVert3Df position, NYVert3Df rotation, NYVert3Df scale, NYTexFile* texture)
{

	float sizeX = 0.25f;
	float sizeY = 0.33f;
	glColor3d(1, 1, 1);

		glPushMatrix();
	glTranslatef(position.X, position.Y, position.Z);
	glRotated(rotation.X, 1, 0, 0);
	glRotated(rotation.Y, 0, 1, 0);
	glRotated(rotation.Z, 0, 0, 1);

	glBegin(GL_QUADS);

	//Face Front
	glTexCoord2d(0.50f, 0.33f);
	glVertex3f(scale.X, scale.Y, scale.Z);
	glTexCoord2d(0.50f, 0.33f+sizeY);
	glVertex3f(scale.X, scale.Y, -scale.Z);
	glTexCoord2d(0.50f+sizeX, 0.33f+sizeY);
	glVertex3f(scale.X, -scale.Y, -scale.Z);
	glTexCoord2d(0.50f+sizeX, 0.33f);
	glVertex3f(scale.X, -scale.Y, scale.Z);

	//Face Back
	glTexCoord2d(0.0f, 0.33f);
	glVertex3f(-scale.X, -scale.Y, scale.Z);
	glTexCoord2d(0.0f, 0.33f+sizeY);
	glVertex3f(-scale.X, -scale.Y, -scale.Z);
	glTexCoord2d(0.0f+sizeX, 0.33f+sizeY);
	glVertex3f(-scale.X, scale.Y, -scale.Z);
	glTexCoord2d(0.0f+sizeX, 0.33f);
	glVertex3f(-scale.X, scale.Y, scale.Z);

	//Face Left
	glTexCoord2d(0.25f, 0.33f);
	glVertex3f(-scale.X, scale.Y, scale.Z);
	glTexCoord2d(0.25f, 0.33f+sizeY);
	glVertex3f(-scale.X, scale.Y, -scale.Z);
	glTexCoord2d(0.25f+sizeX, 0.33f+sizeY);
	glVertex3f(scale.X, scale.Y, -scale.Z);
	glTexCoord2d(0.25f+sizeX, 0.33f);
	glVertex3f(scale.X, scale.Y, scale.Z);

	//Face Right
	glTexCoord2d(0.75f, 0.33f);
	glVertex3f(scale.X, -scale.Y, scale.Z);
	glTexCoord2d(0.75f, 0.33f + sizeY);
	glVertex3f(scale.X, -scale.Y, -scale.Z);
	glTexCoord2d(0.75f + sizeX, 0.33f + sizeY);
	glVertex3f(-scale.X, -scale.Y, -scale.Z);
	glTexCoord2d(0.75f + sizeX, 0.33f);
	glVertex3f(-scale.X, -scale.Y, scale.Z);

	//Face up
	glTexCoord2d(0.25f, 0.0f);
	glVertex3f(-scale.X, -scale.Y, scale.Z);
	glTexCoord2d(0.25f, 0.0f + sizeY);
	glVertex3f(-scale.X, scale.Y, scale.Z);
	glTexCoord2d(0.25f + sizeX, 0.0f + sizeY);
	glVertex3f(scale.X, scale.Y, scale.Z);
	glTexCoord2d(0.25f + sizeX, 0.0f);
	glVertex3f(scale.X, -scale.Y, scale.Z);

	//Face down
	glTexCoord2d(0.25f, 0.66f);
	glVertex3f(scale.X, -scale.Y, -scale.Z);
	glTexCoord2d(0.25f, 0.66f + sizeY);
	glVertex3f(scale.X, scale.Y, -scale.Z);
	glTexCoord2d(0.25f + sizeX, 0.66f + sizeY);
	glVertex3f(-scale.X, scale.Y, -scale.Z);
	glTexCoord2d(0.25f + sizeX, 0.66f);
	glVertex3f(-scale.X, -scale.Y, -scale.Z);
	
	glEnd();
	glPopMatrix();

}

Primitive::~Primitive()
{
}
