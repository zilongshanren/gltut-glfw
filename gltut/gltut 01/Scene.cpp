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

const std::string vertexShaderString(
                                     "#version 330\n"
                                     " "
                                     "layout(location = 0) in vec4 inputPosition; "
                                     " "
                                     "void main() "
                                     "{ "
                                     "   gl_Position = inputPosition; "
                                     "} "
                                     );

const std::string fragmentShaderString(
                                       "#version 330\n"
                                       " "
                                       "out vec4 outputColor; "
                                       " "
                                       "void main() "
                                       "{ "
                                       "   outputColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f ); "
                                       "} "
                                       );
//coordinates within a range [-1,1] of all axis will be displayed in the screen
//If you can't understand this, please refer to these videos
//https://www.youtube.com/watch?v=-tonZsbHty8&index=26&list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY
const float vertexPositions[] =
{
	-1.5f, -1.0f, 0.0f, 1.0f,
	0.0f, 2.0f, 0.0f, 1.0f,
	1.0f, -1.0f,  0.0f, 1.0f
};

Scene::Scene()
{
}

void Scene::init()
{
    _shaderProgram = createShaderProgramWithSource(vertexShaderString, fragmentShaderString);
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

Scene::~Scene()
{
    glDeleteProgram(_shaderProgram);
    glDeleteBuffers(1, &_vertexBufferObject);
    printOpenGLError();
}


void Scene::draw()
{
    glClearColor(0.2f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
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