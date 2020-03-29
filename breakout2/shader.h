#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// General purpsoe shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.
class Shader
{
public:
    // State
    unsigned int ID; 
    // Constructor
    Shader() { }
    // Sets the current shader as active
    Shader &Use();
    // Compiles the shader from given source code
    void Compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr); // Note: geometry source code is optional 
    // Utility functions
    void SetFloat    (const char *name, GLfloat value, GLboolean useShader = false);
    void SetInteger  (const char *name, GLint value, GLboolean useShader = false);
    void SetVector2f (const char *name, GLfloat x, GLfloat y, GLboolean useShader = false);
    void SetVector2f (const char *name, const glm::vec2 &value, GLboolean useShader = false);
    void SetVector3f (const char *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void SetVector3f (const char *name, const glm::vec3 &value, GLboolean useShader = false);
    void SetVector4f (const char *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void SetVector4f (const char *name, const glm::vec4 &value, GLboolean useShader = false);
    void SetMatrix4  (const char *name, const glm::mat4 &matrix, GLboolean useShader = false);
private:
    // Checks if compilation or linking failed and if so, print the error logs
    void checkCompileErrors(GLuint object, std::string type); 
};