#pragma once

#include <GL/glew.h> // Include this library before any other
#include <GLFW/glfw3.h>

#include <iostream>

// Debug macro to insert a breakpoint
#define ASSERT(x) if (!(x)) __debugbreak();

// Debug macro for clearing errors and displaying error
#define GLCALL(x) GLClearErrors();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))

// Declaration to clear errors
void GLClearErrors();
// Declaration to display verbose error message
bool GLLogCall(const char* function, const char* file, int line);