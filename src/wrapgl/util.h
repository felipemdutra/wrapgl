#include <GL/glew.h>

// @brief Checks the type of the error, and throws with a matching error 
// description
//
// @param The error to check.
// @returns 0 If no error occurred, a negative number otherwise.
int ThrowIfGlError(GLenum error);

