#pragma once
#include <GL/glew.h>
#include <GL/glfw.h>
#include <string.h>
#include <cstdlib>
#include <vector>
/*
	Clases de objetos buffer especificos :
	Aunque se puedan llamar individualmente , estan
	pensados para ser llamados y gestionados desde la clase
	OBJECT , pudiendo permanecer totalmente ajeno al funcionamiento
	de estos objetos.

	Los arrays se guardan en el objeto porque no es posible asegurar que 
	los numeros generados realmente esten en globales estaticas, de esta forma
	se facilita la gestion y libertad a nivel de algoritmos, pero implica tener que ir liberando los arrays originarios
	si se necesitara para no colapsar la memoria con atributos identicos, pero de distinto fin.
*/

using namespace std;

class Buffer_Object
{
	public :
	//Tipo del buffer , se llena con el adecuado en funcion de que heredada se llame.
	GLuint BUFFER;
	//Tipo de variable , idem.
	GLuint TYPE  ;
	//Los bytes que ocupa el array "nucleo" del objeto , es necesario guardarlo.
	GLuint theBytes;
	//La ID generada del buffer.
	GLuint theID;
	//Destruir el objeto.
	void destroy();
	//Destructor propiamente dicho , no hay por que llamarlo.
	~Buffer_Object();
};

class VBO : public Buffer_Object
{
	public :
	//El conjunto de floats que , leidos de 3 en 3 , forman los vertices.
	GLfloat *theFloats;
	//El indice del buffer.
	GLuint theIndex;
	VBO() {};
	VBO( GLfloat *theArray, GLuint theSizeof , GLuint theIx );
	VBO( vector<float> theArray, GLuint theIx );
	//Habilitar puntero.
	void enable( GLubyte);
	void draw( GLushort );
	//Deshabilitar puntero.
	void disable();
	~VBO();
};

class IBO : public Buffer_Object
{
	public :
	//El conjunto de halfs que leidos de 3 en 3 , forman triangulos.
	GLushort *theIndices;
	IBO() {};
	IBO( GLushort *theArray , GLuint theSizeof );
	IBO( vector<GLushort> theArray );
	void draw( GLushort );
	~IBO();
};