#include <iostream>
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ErrorCallback.h"

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}