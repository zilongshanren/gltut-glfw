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

const float vertexPositions[] =
{
	0.75f, 0.75f, 1.0f, 1.0f,
	0.75f, -0.75f, 1.0f, 1.0f,
	-0.75f, -0.75f, 1.0f, 1.0f
};

Scene::Scene()
{
}

void Scene::reshape(int width, int height)
{
    const float aspectRatio = 1.0f;
    
    int finalWidth = width;
    int finalHeight = height;
    
    int derivedHeight = height * (1/aspectRatio);
    int derivedWidth = width * aspectRatio;
    
    if (derivedHeight <= height)
    {
        finalHeight = derivedHeight;
    }
    else if (derivedWidth <= width)
    {
        finalWidth = derivedWidth;
    }
    
    glViewport( (width-finalWidth)  / 2,
               (height-finalHeight) / 2,
               finalWidth,
               finalHeight);
}

void Scene::init()
{
    _shaderProgram = createShaderProgramWithFilenames("FragPosition.vert", "FragPosition.frag");
    glUseProgram(_shaderProgram);
    printOpenGLError();
    
    // Initialize Vertex Buffer
    glGenBuffers(1, &_vertexBufferObject);
    
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    printOpenGLError();
    
    // Vertex array object
    glGenVertexArrays(1, &_vertexArrayObject);
	glBindVertexArray(_vertexArrayObject);
    printOpenGLError();
    
    //glEnable(GL_DEPTH_TEST);
}

Scene::~Scene()
{
    glDeleteProgram(_shaderProgram);
    glDeleteBuffers(1, &_vertexBufferObject);
    printOpenGLError();
}



void Scene::draw()
{
    glClearColor(0.2f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
	glDrawArrays(GL_TRIANGLES, 0, 3);
    printOpenGLError();
    
	glDisableVertexAttribArray(0);
    printOpenGLError();
}

void Scene::keyStateChanged(int key, int action)
{
}