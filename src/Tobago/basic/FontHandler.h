#pragma once
#include <GL/glew.h>
#include <GL/glfw.h>
#include "FBO.h"
#include "TBO.h"
#include "Buffer_Object.h"
#include "shader.h"
/*
	La intencion de uso de esta estupida clase es crear una diferente para cada fuente, algo del estilo : 
	FontHandler Calibri("Calibri.png")
	FontHandler Verdana("Verdana.png")
	
	Si la textura es 512x512 el constructor de cinco parametros no es necesario.
	Las variables internas ya asumiran el valor por defecto para este tipo de texturas.

	De hecho si quereis alguna fuente me lo contais y os la genero u os ensenio el programa que utilizo.

	... etc ...
	Si queremos una textura de letras que contenga la palabra "perro" usando la fuente Calibri, podemos hacer : 
	FBO Perro = Calibri.StringTex("perro",4);

	Tambien puede usarse el infame operador sizeof() si lo que estamos enviando son punteros a char : 

	char  dog[] = "perro";
	FBO Perro = Calibri.StringTex( &dog[0], sizeof(dog) );

*/

class FontHandler {
	private :
		TBO* Alphabet;
		Shader* TexReader;
		// Esto realmente son enteros, se usa float para aligerar el trabajo de conversion del programa.
		unsigned StartingCharacter;
		unsigned CHeight;
		unsigned CWidth ;
		unsigned CharsPerRow;
		GLuint TextureID;
		FBO* ret;

	public :
		FontHandler(char*); // Por defecto las tres variables valdran 32.
		FontHandler(char*, unsigned, unsigned, unsigned,unsigned);
		//FBO StringTexA(char*, unsigned); //Here is the fucking perleman.
		TBO StringTex(char*, unsigned); //Here is the fucking perleman.
};