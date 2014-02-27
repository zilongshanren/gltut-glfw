//
//  Scene.h
//  gltut-glfw
//
// Copyright (C) 2010-2012 by Jason L. McKesson
// Xcode and glfw adaptation: Ricardo Sánchez-Sáez.
//
// This file is licensed under the MIT License.
//

#ifndef __gltut_glfw__Scene__
#define __gltut_glfw__Scene__

#ifndef GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLCOREARB
#endif
#define GL_GLEXT_PROTOTYPES
#include "GLFW/glfw3.h"

#include <vector>

class Scene {
    GLuint _shaderProgram;
    GLuint _vertexBufferObject;
    GLuint _vertexArrayObject;
    
  public:
    Scene();
    ~Scene();
    
    void init();
    void draw();
    

    virtual void reshape(int width, int height)
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
    
    void keyStateChanged(int key, int action);
    
    // Only used in Chapter 3
    void computePositionOffsets(float &fXOffset, float &fYOffset);
    void adjustVertexData(float fXOffset, float fYOffset);
};


#endif /* defined(__circular__Scene__) */
