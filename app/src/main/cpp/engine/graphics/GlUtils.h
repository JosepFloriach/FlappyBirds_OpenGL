//
// Created by Josep on 14/08/2018.
//

#ifndef ZEPTOLABTEST_GLUTILS_H
#define ZEPTOLABTEST_GLUTILS_H

#include <GLES2/gl2.h>

class GlUtils 
{
public:	
	static void PreRender()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}

	static void PostRender()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		glDisableVertexAttribArray(0);
	}
};


#endif //ZEPTOLABTEST_GLUTILS_H
