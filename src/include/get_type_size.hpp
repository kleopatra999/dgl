#pragma once

#include <iostream>
#include <GL/gl.h>

static
int get_type_size(GLenum type) {
	switch (type) {
	case GL_BYTE: 			    		return sizeof(GLbyte);
	case GL_UNSIGNED_BYTE:  	    	return sizeof(GLubyte);
	case GL_SHORT: 			    		return sizeof(GLshort);
	case GL_UNSIGNED_SHORT: 	    	return sizeof(GLushort);
	case GL_INT: 			    		return sizeof(GLint);
	case GL_UNSIGNED_INT: 		    	return sizeof(GLuint);
	case GL_FLOAT: 			    		return sizeof(GLfloat);
	//case GL_DOUBLE:			    		return sizeof(GLdouble);
	//case GL_BITMAP: 		    		return sizeof(GLubyte);
	//case GL_UNSIGNED_BYTE_3_3_2:  	    return sizeof(GLubyte);
	//case GL_UNSIGNED_BYTE_2_3_3_REV:    return sizeof(GLubyte);
	case GL_UNSIGNED_SHORT_5_6_5: 	    return sizeof(GLushort);
	//case GL_UNSIGNED_SHORT_5_6_5_REV:   return sizeof(GLushort);
	case GL_UNSIGNED_SHORT_4_4_4_4:     return sizeof(GLushort);
	//case GL_UNSIGNED_SHORT_4_4_4_4_REV: return sizeof(GLushort);
	case GL_UNSIGNED_SHORT_5_5_5_1:	    return sizeof(GLushort);
	//case GL_UNSIGNED_SHORT_1_5_5_5_REV: return sizeof(GLushort);
	//case GL_UNSIGNED_INT_8_8_8_8: 	    return sizeof(GLuint);
	//case GL_UNSIGNED_INT_8_8_8_8_REV:   return sizeof(GLuint);
	//case GL_UNSIGNED_INT_10_10_10_2:    return sizeof(GLuint);
	//case GL_UNSIGNED_INT_2_10_10_10_REV:return sizeof(GLuint);
	default:
        std::cerr << "DEFAULTED getTypeSize!\n" << std::endl;
        return 4;
	}
}
