#include "Buffer_Object.h"
#include  <iostream>
void Buffer_Object::destroy()
{
	this-> ~Buffer_Object();
}

Buffer_Object::~Buffer_Object()
{
	glDeleteBuffers(1, &theID);
}

VBO::VBO( GLfloat *theArray, GLuint theSizeof , GLuint theIx)
{
	theBytes = theSizeof;
	theFloats = (GLfloat*)malloc(theBytes);
	memcpy(theFloats , theArray, theBytes);
	theIndex = theIx;
	BUFFER = GL_ARRAY_BUFFER;
	TYPE = GL_FLOAT;

	glGenBuffers(1, &this->theID);
    glBindBuffer( BUFFER , theID);
    glBufferData( BUFFER, theBytes, &this->theFloats[0], GL_STATIC_DRAW);
}

VBO::VBO( vector<float> theArray, GLuint theIx)
{
	theIndex = theIx;
	BUFFER = GL_ARRAY_BUFFER;
	TYPE = GL_FLOAT;
	theBytes = theArray.size() * sizeof( GLfloat );

	glGenBuffers(1, &this->theID);
    glBindBuffer( BUFFER , theID);
	glBufferData( BUFFER, theArray.size()*sizeof(float), &theArray[0], GL_STATIC_DRAW);
}

void VBO::enable( GLubyte Rn )
{
	//std::cout << "Im enabling the buffer!" << std::endl;
	glEnableVertexAttribArray(theIndex);
    glBindBuffer(BUFFER, theID);
    glVertexAttribPointer(theIndex , Rn, TYPE , GL_FALSE , 0 , (void*)0 );
}

void VBO::disable()
{
	glDisableVertexAttribArray(theIndex);
}

VBO::~VBO()
{
}

IBO::IBO( GLushort *theArray , GLuint theSizeof )
{
	theBytes = theSizeof;
	theIndices = (GLushort*)malloc(theBytes);
	memcpy(theIndices,theArray,theBytes);
	theBytes+=4;
	//std::cout << theIndices[1] << " ";
/*	for(unsigned i = 0; i< theBytes / 2 ; i++)
		std::cout << theIndices[i] << " ";
	std::cout << std::endl;*/
	//std::cout << " " << theBytes << std::endl;
	BUFFER = GL_ELEMENT_ARRAY_BUFFER;
	TYPE   = GL_UNSIGNED_SHORT;
	glGenBuffers(1, &this->theID);
    glBindBuffer( BUFFER , theID);
    glBufferData( BUFFER, theSizeof, &this->theIndices[0], GL_STATIC_DRAW);		
}

IBO::IBO( vector<GLushort> theArray)
{
	BUFFER = GL_ELEMENT_ARRAY_BUFFER;
	TYPE   = GL_UNSIGNED_SHORT;
	glGenBuffers(1, &this->theID);
    glBindBuffer( BUFFER , theID);
	theBytes = 2*theArray.size();
    glBufferData( BUFFER, theArray.size()*sizeof(GLushort), &theArray[0], GL_STATIC_DRAW);		
}

void VBO::draw( GLushort theDrawType ) {
	glDrawArrays( theDrawType,0, theBytes / sizeof( GLfloat ) );
}

void IBO::draw( GLushort theDraw)
{
	glBindBuffer(BUFFER, theID);
	glDrawElements(theDraw,theBytes/2,TYPE,(void*)0 );
}

IBO::~IBO()
{

}