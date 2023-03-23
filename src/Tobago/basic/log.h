#pragma once
#ifndef log_h
#define log_h
#ifdef DEBUG_LOG
#include <cstring>
#include <iostream>
#endif
#include <fstream>
//#include <vector>
#include "GL/glfw.h"


using namespace std;

class Log {
public:
    Log(char* name);
    void error(char* message);
    void warning(char* message);
    void message(char* message);
    void close();

private:
    char* filename;
    ofstream *output;
};


#endif
