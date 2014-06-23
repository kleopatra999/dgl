#include "intercept.hpp"

/*********************************************************
	Pointer Structures
*********************************************************/
//some methods simply specify a pointer to the beginning
//of an array, that will be used later. As we do not yet
//know the size of the array, we cannot send the buffer
//We store the values for the method until the size is
//known (usually when glDrawElements is called)

int iCurrentActiveTextureUnit = 0;

storedPointer rpTex[GL_MAX_TEXTURES]; //[8], usually
storedPointer rpVert;
storedPointer rpCol;
storedPointer rpInter;
storedPointer rpNormals;


bool enablePointerDebug = false;

static int hash(char *data, int len){
	int r = 0;

	for(int i=0;i<len;i++){
		r += data[i];
	}
	return r;
}

int plen(GLenum type, int size, int stride, int length){
	return ((getTypeSize(type) * size) + stride) * length;
}

void sendPointers(int length) {

	//TODO: fill in other pointer values, or
	//create a better, more elegant solution

	//texture pointer
	for(int i=0;i<GL_MAX_TEXTURES;i++){
		if(!rpTex[i].sent && rpTex[i].size){
			int size = plen(rpTex[i].type, rpTex[i].size, rpTex[i].stride, length);

			//We have to operate on the correct texture unit
			//This makes stuff like multitexturing work properly with VBOs
			//TODO This will cause an extra glClientActiveTexture() call
			//which probably isn't an issue, but...
			//
			//glClientActiveTexture()
			pushOp(375);
			pushParam(GL_TEXTURE0 + i); //pretty sure this is okay, carmack does it

			//glTexCoordPointer()
			pushOp(320);
			pushParam(rpTex[i].size);
			pushParam(rpTex[i].type);
			pushParam(rpTex[i].stride);
			pushParam(false);
			pushBuf(rpTex[i].pointer, size);
			rpTex[i].sent = true;
			rpTex[i].pointer = NULL;

			if(enablePointerDebug){
				LOG("Sending glTexCoordPointer() data %d for texture %d\n", size, i);
			}
		}
	}

	//vertex pointer
	if(!rpVert.sent && rpVert.size){
		int size = plen(rpVert.type, rpVert.size, rpVert.stride, length);
		pushOp(321);
		pushParam(rpVert.size);
		pushParam(rpVert.type);
		pushParam(rpVert.stride);
		pushParam(false);
		pushBuf(rpVert.pointer, size);
		rpVert.sent = true;
		rpVert.pointer = NULL;

		if(enablePointerDebug){
			LOG("Sending glVertexPointer() data %d, %d, %d, %d = %d\n",
				rpVert.size, getTypeSize(rpVert.type), rpVert.stride,
				length, size);
		}
	}

	if(!rpCol.sent && rpCol.size){
		int size = plen(rpCol.type, rpCol.size, rpCol.stride, length);
		//colour pointer
		pushOp(308);
		pushParam(rpCol.size);
		pushParam(rpCol.type);
		pushParam(rpCol.stride);
		pushParam(false);
		pushBuf(rpCol.pointer, size);
		rpCol.sent = true;
		rpCol.pointer = NULL;

		if(enablePointerDebug){
			LOG("Sending glColorPointer() data %d %d\n", length, size);
		}
	}

	if(!rpInter.sent && rpInter.size)	//check if sent already, and not null
	{
		//interleaved arrays pointer
		int size = 0;
		switch (rpInter.type)
		{
			case GL_V2F:			size = sizeof(GLfloat) * 2; break;
	        case GL_V3F:			size = sizeof(GLfloat) * 3; break;
	        case GL_C4UB_V2F:		size = sizeof(GLfloat) * 2 + sizeof(GLubyte) * 4; break;
	        case GL_C4UB_V3F:		size = sizeof(GLfloat) * 3 + sizeof(GLubyte) * 4; break;
	        case GL_C3F_V3F:		size = sizeof(GLfloat) * 6; break;
	        case GL_N3F_V3F:		size = sizeof(GLfloat) * 6; break;
	        case GL_C4F_N3F_V3F:		size = sizeof(GLfloat) * 10; break;
	        case GL_T2F_V3F:		size = sizeof(GLfloat) * 5; break;
	        case GL_T4F_V4F:		size = sizeof(GLfloat) * 8; break;
	        case GL_T2F_C4UB_V3F:		size = sizeof(GLfloat) * 5 + sizeof(GLubyte) * 4; break;
	        case GL_T2F_C3F_V3F:		size = sizeof(GLfloat) * 8; break;
	        case GL_T2F_N3F_V3F:		size = sizeof(GLfloat) * 8; break;
	        case GL_T2F_C4F_N3F_V3F:	size = sizeof(GLfloat) * 12; break;
	        case GL_T4F_C4F_N3F_V4F:	size = sizeof(GLfloat) * 15; break;
			default:LOG("DEFAULTED glInterleavedArrays lookup %d should be %d!\n", rpInter.type, GL_T2F_C4UB_V3F); size = sizeof(GLfloat) * 15;
		}
		pushOp(317);
		pushParam(rpInter.type);
		pushParam(rpInter.stride);
		pushParam(false);
		pushBuf(rpInter.pointer, ((size + rpInter.stride) * length)); //drawing quads?
		rpInter.sent = true;
	}

	if(!rpNormals.sent && rpNormals.size){
		int size = plen(rpNormals.type, rpNormals.size, rpNormals.stride, length);
		//colour pointer
		pushOp(318);
		pushParam(rpNormals.type);
		pushParam(rpNormals.stride);
		pushParam(false);
		pushBuf(rpNormals.pointer, size);
		rpNormals.sent = true;
	}
}
