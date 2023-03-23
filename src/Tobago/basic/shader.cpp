#ifdef DEBUG_LOG
#include "shader.h"

Shader::Shader(char *vertex, char *fragment) {
    load(vertex, fragment);
    compile();
    link();
}

Shader::Shader(const char *vertex, const char *fragment, bool verbose) {
    loadmemory(vertex, fragment);
    compile();
    link();
}

bool Shader::load(char *vertex, char *fragment) {
    char *vs, *fs;
    bool ret = true;

    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);

    //Loading vertex shader.
    vs = textFileRead(vertex);
    if (vs == NULL) {
        global::log.error("Vertex shader file wasn't read correctly:");
        global::log.error(vertex);
        ret = false;
    }

    vv = vs;

    //Loading fragment shader.
    fs = textFileRead(fragment);
    if(fs == NULL) {
        global::log.error("Fragment shader file wasn't read correctly:");
        global::log.error(fragment);
        ret = false;
    }
    
    ff = fs;

    if(ret) {
        glShaderSource(v, 1, &vv, NULL);
        glShaderSource(f, 1, &ff, NULL);
        free(vs);
        free(fs);
    }

    return ret;
}

void Shader::loadmemory(const char *vertex, const char *fragment) {
    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);

    //Loading vertex shader.
    glShaderSource(v, 1, &vertex, NULL);

    //Loading fragment shader.
	glShaderSource(f, 1, &fragment, NULL);
}

bool Shader::compile() {
    glCompileShader(v);
    glCompileShader(f);
	#ifdef DEBUG_LOG
    bool cv = printShaderInfoLog(v); //returns true if error
    bool cf = printShaderInfoLog(f); //returns true if error
	return !(cv || cf); //returns false if error	
	#else
	return 1;
	#endif
    
}

bool Shader::link() {
    p = glCreateProgram();

    glAttachShader(p, v);
    glAttachShader(p, f);

    glLinkProgram(p);
	#ifdef DEBUG_LOG
    bool pl = printProgramInfoLog(p); //returns true if error

    return !pl;
	#else
	return 1;
	#endif
}

void Shader::use() {
    glUseProgram(p);
}

GLuint Shader::getUniform(char *name) {
	return glGetUniformLocation(p, name);
}

/*void Shader::unuse() {
    glUseProgram(0);
}*/
//El shader 0 o shader trivial no hace falta llamarlo.


void Shader::uni_float(char *name, float value) {
    GLint loc = glGetUniformLocation(p, name);
    glUniform1f(loc, value);
}

void Shader::uni_int(char *name, int value) {
    GLint loc = glGetUniformLocation(p, name);
    glUniform1i(loc, value);
}

/*
void setShaders() {
    GLint loc = glGetUniformLocation(p, "tex");
    
    glUniform1i(loc, 0);
}*/


char *Shader::textFileRead(char *fn) {
    FILE *fp;
    char *content = NULL;
    
    int count=0;

    if (fn != NULL) {
        fp = fopen(fn,"rt");

        if (fp != NULL) {
            fseek(fp, 0, SEEK_END);
            count = int(ftell(fp));
            rewind(fp);
            if (count > 0) {
                content = (char *)malloc(sizeof(char) * (count+1));
                count = int(fread(content,sizeof(char),count,fp));
                content[count] = '\0';
            }
            fclose(fp);
        }
    }
    return content;
}

bool Shader::printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
	
    if (infologLength > 1)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        global::log.error("Shader compiling error:");
        global::log.error(infoLog);
        free(infoLog); 
    }
	
    return !(infologLength > 1);
}

bool Shader::printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
    
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);
    
    if (infologLength > 1)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
        global::log.error("Shader program linking error:");
        global::log.error(infoLog);
        free(infoLog);
    }
    
    return !(infologLength > 1);
}

#endif