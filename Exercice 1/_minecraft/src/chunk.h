#pragma once

#include "engine/render/renderer.h"
#include "cube.h"

/**
  * On utilise des chunks pour que si on modifie juste un cube, on ait pas
  * besoin de recharger toute la carte dans le buffer, mais juste le chunk en question
  */
class NYChunk
{
	public :

		int index = 0;
		static const int CHUNK_SIZE = 16; ///< Taille d'un chunk en nombre de cubes (n*n*n)
		NYCube _Cubes[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE]; ///< Cubes contenus dans le chunk

		GLuint _BufWorld; ///< Identifiant du VBO pour le monde
		
		static float _WorldVert[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE*3*6*6]; ///< Buffer pour les sommets
		static float _WorldCols[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE*3*6*6]; ///< Buffer pour les couleurs
		static float _WorldNorm[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE*3*6*6]; ///< Buffer pour les normales

		static const int SIZE_VERTICE = 3 * sizeof(float); ///< Taille en octets d'un vertex dans le VBO
		static const int SIZE_COLOR = 3 * sizeof(float);  ///< Taille d'une couleur dans le VBO
		static const int SIZE_NORMAL = 3 * sizeof(float);  ///< Taille d'une normale dans le VBO
		
		int _NbVertices; ///< Nombre de vertices dans le VBO (on ne met que les faces visibles)

		NYChunk * Voisins[6];
		
		NYChunk()
		{
			_NbVertices = CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE * 6 * 6;
			_BufWorld = 0;
			memset(Voisins,0x00,sizeof(void*) * 6);
		}

		void setVoisins(NYChunk * xprev, NYChunk * xnext,NYChunk * yprev,NYChunk * ynext,NYChunk * zprev,NYChunk * znext)
		{
			Voisins[0] = xprev;
			Voisins[1] = xnext;
			Voisins[2] = yprev;
			Voisins[3] = ynext;
			Voisins[4] = zprev;
			Voisins[5] = znext;
		}

		/**
		  * Raz de l'état des cubes (a draw = false)
		  */
		void reset(void)
		{
			for(int x=0;x<CHUNK_SIZE;x++)
				for(int y=0;y<CHUNK_SIZE;y++)
					for(int z=0;z<CHUNK_SIZE;z++)
					{
						_Cubes[x][y][z]._Draw = true;
						_Cubes[x][y][z]._Type = CUBE_AIR;
					}
		}
		
		void feed_WorldVert()
		{
			index = 0;
			int cubeSize = NYCube().CUBE_SIZE;
			float col[] = { 0.0, 0.0, 0.0 };
			for (int x = 0; x < CHUNK_SIZE; x++)
			{
				for (int y = 0; y < CHUNK_SIZE; y++)
				{
					for (int z = 0; z < CHUNK_SIZE; z++)
					{
						NYVert3Df col = NYCube::makeMaterial(_Cubes[x][y][z]._Type);
						if (_Cubes[x][y][z]._Type != CUBE_AIR && _Cubes[x][y][z]._Draw)
							addCube(x, y, z, col.X, col.Y, col.Z);
					}
				}
			}
		}

		void addCube(float x, float y, float z, float r, float g, float b)
		{

			//Face 1
			addVertex(x , y , z + 1, r, g, b, 0, 0, 1);
			addVertex(x + 1, y , z + 1, r, g, b, 0, 0, 1);
			addVertex(x , y + 1, z + 1, r, g, b, 0, 0, 1);

			addVertex(x + 1, y , z + 1, r, g, b, 0, 0, 1);
			addVertex(x + 1, y + 1, z + 1, r, g, b, 0, 0, 1);
			addVertex(x , y + 1, z + 1, r, g, b, 0, 0, 1);

			//Face2 Down

			addVertex(x , y + 1, z , r, g, b, 0, 0, -1);
			addVertex(x + 1, y , z , r, g, b, 0, 0, -1);
			addVertex(x , y , z , r, g, b, 0, 0, -1);
			addVertex(x , y + 1, z , r, g, b, 0, 0, -1);
			addVertex(x + 1, y + 1, z , r, g, b, 0, 0, -1);
			addVertex(x + 1, y , z , r, g, b, 0, 0, -1);
			//Face3 X Front

			addVertex(x + 1, y , z , r, g, b, 1, 0, 0);
			addVertex(x + 1, y + 1, z , r, g, b, 1, 0, 0);
			addVertex(x + 1, y , z + 1, r, g, b, 1, 0, 0);
			addVertex(x + 1, y + 1, z , r, g, b, 1, 0, 0);
			addVertex(x + 1, y + 1, z + 1, r, g, b, 1, 0, 0);
			addVertex(x + 1, y , z + 1, r, g, b, 1, 0, 0);

			//Face4 X Back

			addVertex(x , y , z + 1, r, g, b, -1, 0, 0);
			addVertex(x , y + 1, z , r, g, b, -1, 0, 0);
			addVertex(x , y , z , r, g, b, -1, 0, 0);
			addVertex(x , y , z + 1, r, g, b, -1, 0, 0);
			addVertex(x , y + 1, z + 1, r, g, b, -1, 0, 0);
			addVertex(x , y + 1, z , r, g, b, -1, 0, 0);

			//Face5 Y Front

			addVertex(x + 1, y + 1, z , r, g, b, 0, 1, 0);
			addVertex(x , y + 1, z , r, g, b, 0, 1, 0);
			addVertex(x + 1, y + 1, z + 1, r, g, b, 0, 1, 0);
			addVertex(x , y + 1, z , r, g, b, 0, 1, 0);
			addVertex(x , y + 1, z + 1, r, g, b, 0, 1, 0);
			addVertex(x + 1, y + 1, z + 1, r, g, b, 0, 1, 0);

			//Face6 Y Back

			addVertex(x + 1, y , z + 1, r, g, b, 0, -1, 0);
			addVertex(x , y , z , r, g, b, 0, -1, 0);
			addVertex(x + 1, y , z , r, g, b, 0, -1, 0);
			addVertex(x + 1, y , z + 1, r, g, b, 0, -1, 0);
			addVertex(x , y , z + 1, r, g, b, 0, -1, 0);
			addVertex(x , y , z , r, g, b, 0, -1, 0);

		}

		void addVertex(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz)
		{
			_WorldVert[index] = x * NYCube::CUBE_SIZE;
			_WorldCols[index] = r;
			_WorldNorm[index] = nx;
			index++;
			_WorldVert[index] = y * NYCube::CUBE_SIZE;
			_WorldCols[index] = g;
			_WorldNorm[index] = ny;
			index++;
			_WorldVert[index] = z * NYCube::CUBE_SIZE;
			_WorldCols[index] = b;
			_WorldNorm[index] = nz;
			index++;
		}

		//On met le chunk ddans son VBO
		void toVbo(void)
		{
			feed_WorldVert();
			_NbVertices = index / 3;
			//On le detruit si il existe deja
			if (_BufWorld != 0)
				glDeleteBuffers(1, &_BufWorld);

			//Genere un identifiant
			glGenBuffers(1, &_BufWorld);

			//On attache le VBO pour pouvoir le modifier
			glBindBuffer(GL_ARRAY_BUFFER, _BufWorld);

			GLint g_sizeVertice = sizeof(float)*3;
			GLint g_sizeColor = sizeof(float)*3;

			//On reserve la quantite totale de datas (creation de la zone memoire, mais sans passer les données)
			//Les tailles g_size* sont en octets, à vous de les calculer
			glBufferData(GL_ARRAY_BUFFER,
				_NbVertices * g_sizeVertice +
				_NbVertices * g_sizeColor +
				_NbVertices * g_sizeVertice,
				NULL,
				GL_STREAM_DRAW);

			//Check error (la tester ensuite...)
			GLenum error = glGetError();


			//On copie les vertices
			glBufferSubData(GL_ARRAY_BUFFER,
				0, //Offset 0, on part du debut                        
				_NbVertices * g_sizeVertice, //Taille en octets des datas copiés
				_WorldVert);  //Datas          

			//Check error (la tester ensuite...)
			error = glGetError();

			//On copie les couleurs
			glBufferSubData(GL_ARRAY_BUFFER,
				_NbVertices * g_sizeVertice, //Offset : on se place après les vertices
				_NbVertices * g_sizeColor, //On copie tout le buffer couleur : on donne donc sa taille
				_WorldCols);  //Pt sur le buffer couleur       

			//Check error (la tester ensuite...)
			error = glGetError();

			//On copie les normales (a vous de déduire les params)
			glBufferSubData(GL_ARRAY_BUFFER,
				_NbVertices * g_sizeVertice + _NbVertices * g_sizeColor,
				_NbVertices * g_sizeVertice ,
				_WorldNorm );

			//On debind le buffer pour eviter une modif accidentelle par le reste du code
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void render(void)
		{
			glEnable(GL_COLOR_MATERIAL);
			glEnable(GL_LIGHTING);

			//On bind le buuffer
			glBindBuffer(GL_ARRAY_BUFFER, _BufWorld);
			NYRenderer::checkGlError("glBindBuffer");

			//On active les datas que contiennent le VBO
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);

			//On place les pointeurs sur les datas, aux bons offsets
			glVertexPointer(3, GL_FLOAT, 0, (void*)(0));
			glColorPointer(3, GL_FLOAT, 0, (void*)(_NbVertices*SIZE_VERTICE));
			glNormalPointer(GL_FLOAT, 0, (void*)(_NbVertices*SIZE_VERTICE + _NbVertices*SIZE_COLOR));

			//On demande le dessin
			glDrawArrays(GL_TRIANGLES, 0, _NbVertices);

			//On cleane
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);

		}

		/**
		  * On verifie si le cube peut être vu
		  */
		bool test_hidden(int x, int y, int z)
		{
			NYCube * cubeXPrev = NULL; 
			NYCube * cubeXNext = NULL; 
			NYCube * cubeYPrev = NULL; 
			NYCube * cubeYNext = NULL; 
			NYCube * cubeZPrev = NULL; 
			NYCube * cubeZNext = NULL; 

			if(x == 0 && Voisins[0] != NULL)
				cubeXPrev = &(Voisins[0]->_Cubes[CHUNK_SIZE-1][y][z]);
			else if(x > 0)
				cubeXPrev = &(_Cubes[x-1][y][z]);

			if(x == CHUNK_SIZE-1 && Voisins[1] != NULL)
				cubeXNext = &(Voisins[1]->_Cubes[0][y][z]);
			else if(x < CHUNK_SIZE-1)
				cubeXNext = &(_Cubes[x+1][y][z]);

			if(y == 0 && Voisins[2] != NULL)
				cubeYPrev = &(Voisins[2]->_Cubes[x][CHUNK_SIZE-1][z]);
			else if(y > 0)
				cubeYPrev = &(_Cubes[x][y-1][z]);

			if(y == CHUNK_SIZE-1 && Voisins[3] != NULL)
				cubeYNext = &(Voisins[3]->_Cubes[x][0][z]);
			else if(y < CHUNK_SIZE-1)
				cubeYNext = &(_Cubes[x][y+1][z]);

			if(z == 0 && Voisins[4] != NULL)
				cubeZPrev = &(Voisins[4]->_Cubes[x][y][CHUNK_SIZE-1]);
			else if(z > 0)
				cubeZPrev = &(_Cubes[x][y][z-1]);

			if(z == CHUNK_SIZE-1 && Voisins[5] != NULL)
				cubeZNext = &(Voisins[5]->_Cubes[x][y][0]);
			else if(z < CHUNK_SIZE-1)
				cubeZNext = &(_Cubes[x][y][z+1]);

			if( cubeXPrev == NULL || cubeXNext == NULL ||
				cubeYPrev == NULL || cubeYNext == NULL ||
				cubeZPrev == NULL || cubeZNext == NULL )
				return false;

			if( cubeXPrev->isSolid() == true && //droite
				cubeXNext->isSolid() == true && //gauche
				cubeYPrev->isSolid() == true && //haut
				cubeYNext->isSolid() == true && //bas
				cubeZPrev->isSolid() == true && //devant
				cubeZNext->isSolid() == true )  //derriere
				return true;
			return false;
		}

		void disableHiddenCubes(void)
		{
			for(int x=0;x<CHUNK_SIZE;x++)
				for(int y=0;y<CHUNK_SIZE;y++)
					for(int z=0;z<CHUNK_SIZE;z++)
					{
						_Cubes[x][y][z]._Draw = true;
						if(test_hidden(x,y,z))
							_Cubes[x][y][z]._Draw = false;
					}
		}


};