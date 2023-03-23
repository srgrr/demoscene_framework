#include "FontHandler.h"

char *FontHandler_vertex = \
	"#version 330 core\n"
	"layout( location = 0) in vec2 spacecoord; "
	"layout( location = 1) in vec2 theUV; "
	"out vec2 UV; "
	"void main(){ "
	"UV = theUV; "
	"gl_Position.xyz = vec3(spacecoord,0); "
	"}";

char *FontHandler_fragment= \
	"#version 330 core\n"
	"in vec2 UV; "
	"uniform sampler2D theTex; "
	"out vec4 Color; "
	"void main(){ "
	"Color = texture2D(theTex, vec2( UV.x, 1 - UV.y) ); "
	"}";


// Se supone que en alphabet quedaria la textura SIN INVERTIR.
FontHandler::FontHandler(char* FontName) {
	StartingCharacter = 32;
	CHeight = 32;
	CWidth  = 32;	
	CharsPerRow = 16;
	Alphabet = new TBO(FontName,true);
	TexReader = new Shader(FontHandler_vertex, FontHandler_fragment, true);
	TextureID = TexReader->getUniform("theTex");
}

FontHandler::FontHandler(char* FontName, unsigned StartingChar, unsigned CellHeight, unsigned CellWidth, unsigned Square){
	StartingCharacter = StartingChar;
	CHeight = CellHeight;
	CWidth  = CellWidth;
	CharsPerRow = Square / CWidth ;
	Alphabet = new TBO(FontName,true);
	TexReader = new Shader(FontHandler_vertex, FontHandler_fragment, true);
	TextureID = TexReader->getUniform("theTex");
}

TBO FontHandler::StringTex(char* Message, unsigned len){
	TBO rett;
	ret = new FBO(CWidth * len, CHeight, &rett, NULL, true);
	vector< GLfloat > QuadsCoord;
	vector< GLfloat > QuadsUV	;
	float x		 = -1.00f;
	float offset = 2/float(len);

	for(unsigned i = 0; i < len; ++i){
		//Inferior izq.
		QuadsCoord.push_back(x + float(i*offset) );
		QuadsCoord.push_back(-1.00f);
		//Inferior dx.
		QuadsCoord.push_back(x + float( (i+1)*offset ) );
		QuadsCoord.push_back(-1.00f);
		//Superior dx.
		QuadsCoord.push_back(x + float( (i+1)*offset ) );
		QuadsCoord.push_back( 1.00f );

		//Inferior izq.
		QuadsCoord.push_back(x + float(i*offset) );
		QuadsCoord.push_back(-1.00f);
		//Superior dx.
		QuadsCoord.push_back(x + float( (i+1)*offset ) );
		QuadsCoord.push_back( 1.00f );
		//Superior izq.
		QuadsCoord.push_back(x + float(i*offset) );
		QuadsCoord.push_back(1.00f);

		//Calcular UVs.

		float uv_x = ( (Message[i] - StartingCharacter) % CharsPerRow ) / float(CharsPerRow);
		float uv_y = ( (Message[i] - StartingCharacter) / CharsPerRow ) / float(CharsPerRow);


		//Inferior izq.
		QuadsUV.push_back(uv_x);
		QuadsUV.push_back(1.0f - (uv_y + 1.0f/float(CharsPerRow) ) );
		//Inferior dx.
		QuadsUV.push_back(uv_x+1.0f / float(CharsPerRow) );
		QuadsUV.push_back(1.0f - (uv_y + 1.0f/float(CharsPerRow) ) );
		//Superior dx.
		QuadsUV.push_back(uv_x+1.0f / float(CharsPerRow) );
		QuadsUV.push_back(1.0f - uv_y);

		//Inferior izq.
		QuadsUV.push_back(uv_x);
		QuadsUV.push_back(1.0f - (uv_y + 1.0f/float(CharsPerRow) ) );
		//Superior dx.
		QuadsUV.push_back(uv_x+1.0f / float(CharsPerRow) );
		QuadsUV.push_back(1.0f - uv_y);
		//Superior izq.
		QuadsUV.push_back(uv_x);
		QuadsUV.push_back(1.0f - uv_y);

	}

	VBO QuadCoord(QuadsCoord,0);
	VBO QuadUV   (QuadsUV	,1);
	TexReader->use();
	ret->bind();
	Alphabet->bind(0);
	glUniform1i( TextureID, 0 );
	QuadCoord.enable(2);
	QuadUV.enable(2);
	QuadCoord.draw( GL_TRIANGLES );
	QuadCoord.disable();
	QuadUV.disable();
	ret->unbind();
	ret->erase();
	return rett;
}