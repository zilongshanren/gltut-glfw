//
//  Scene.cpp
//  gltut-glfw
//
// Copyright (C) 2010-2012 by Jason L. McKesson
// Xcode and glfw adaptation: Ricardo Sánchez-Sáez.
//
// This file is licensed under the MIT License.
//

#include "Scene.h"

#include <string>
#include <vector>

#include "debug.h"
#include "glhelpers.h"
#include "GLFW/glfw3.h"

#include <math.h>

const float vertexData[] = {
    0.25f,  0.25f, -1.25f, 1.0f,
    0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f,  0.25f, -1.25f, 1.0f,
    
    0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f,  0.25f, -1.25f, 1.0f,
    
    0.25f,  0.25f, -2.75f, 1.0f,
	-0.25f,  0.25f, -2.75f, 1.0f,
    0.25f, -0.25f, -2.75f, 1.0f,
    
    0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f,  0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,
    
	-0.25f,  0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,
    
	-0.25f,  0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f,  0.25f, -2.75f, 1.0f,
    
    0.25f,  0.25f, -1.25f, 1.0f,
    0.25f, -0.25f, -2.75f, 1.0f,
    0.25f, -0.25f, -1.25f, 1.0f,
    
    0.25f,  0.25f, -1.25f, 1.0f,
    0.25f,  0.25f, -2.75f, 1.0f,
    0.25f, -0.25f, -2.75f, 1.0f,
    
    0.25f,  0.25f, -2.75f, 1.0f,
    0.25f,  0.25f, -1.25f, 1.0f,
	-0.25f,  0.25f, -1.25f, 1.0f,
    
    0.25f,  0.25f, -2.75f, 1.0f,
	-0.25f,  0.25f, -1.25f, 1.0f,
	-0.25f,  0.25f, -2.75f, 1.0f,
    
    0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
    0.25f, -0.25f, -1.25f, 1.0f,
    
    0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
    
    
    
    
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
    
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
    
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
    
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
    
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
    
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
    
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
    
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
    
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
    
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
    
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
    
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
    
};

GLuint offsetUniform;
GLuint perspectiveMatrixUniform;

float perspectiveMatrix[16];
const float frustumScale = 2.0f;

Scene::Scene()
{
}

void Scene::init()
{
    _shaderProgram = createShaderProgramWithFilenames("MatrixPerspective.vert", "StandardColors.frag");
    glUseProgram(_shaderProgram);
    printOpenGLError();
    
    // Initialize Vertex Buffer
    glGenBuffers(1, &_vertexBufferObject);
    
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    printOpenGLError();
    
    // Vertex array object
    glGenVertexArrays(1, &_vertexArrayObject);
	glBindVertexArray(_vertexArrayObject);
    printOpenGLError();

    // Enable cull facing
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    // Uniforms
	offsetUniform = glGetUniformLocation(_shaderProgram, "offset");
    
	perspectiveMatrixUniform = glGetUniformLocation(_shaderProgram, "perspectiveMatrix");
    
	float zNear = 0.5f; float zFar = 4.0f;
    
	memset(perspectiveMatrix, 0, sizeof(float) * 16);
    
	perspectiveMatrix[0] = frustumScale;
	perspectiveMatrix[5] = frustumScale;
	perspectiveMatrix[10] = (zFar + zNear) / (zNear - zFar);
	perspectiveMatrix[14] = (2 * zFar * zNear) / (zNear - zFar);
	perspectiveMatrix[11] = -1.0f;
    
	glUniformMatrix4fv(perspectiveMatrixUniform, 1, GL_FALSE, perspectiveMatrix);
    
    
    
    
}

Scene::~Scene()
{
    glDeleteProgram(_shaderProgram);
    glDeleteBuffers(1, &_vertexBufferObject);
    printOpenGLError();
}

void Scene::reshape(int width, int height)
{
    perspectiveMatrix[0] = frustumScale / (width / (float)height);
    perspectiveMatrix[5] = frustumScale;
    
    glUseProgram(_shaderProgram);
    glUniformMatrix4fv(perspectiveMatrixUniform, 1, GL_FALSE, perspectiveMatrix);
    glUseProgram(0);
    
    glViewport(0, 0, width, height);
}


void Scene::draw()
{
    glClearColor(0.2f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(_shaderProgram);
	glUniform2f(offsetUniform, 0.0f, 0.3f);

	size_t colorData = sizeof(vertexData) / 2;
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)colorData);
    printOpenGLError();

	glDrawArrays(GL_TRIANGLES, 0, 36);
    printOpenGLError();

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
    printOpenGLError();
}

void Scene::keyStateChanged(int key, int action)
{
}