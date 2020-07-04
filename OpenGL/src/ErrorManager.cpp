#include "ErrorManager.h"

// Function to clear errors
void GLClearErrors() {
	while (glGetError() != GL_NO_ERROR);
}

// Function to display verbose error message
bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): " << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}