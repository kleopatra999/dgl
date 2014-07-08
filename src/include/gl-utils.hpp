#pragma once

static
size_t pname_size(GLenum pname) {
	switch(pname) {
    case GL_ACTIVE_TEXTURE: return 1;
    case GL_ALIASED_LINE_WIDTH_RANGE: return 2;
    case GL_ALIASED_POINT_SIZE_RANGE: return 2;
    case GL_ALPHA_BITS: return 1;
    case GL_ARRAY_BUFFER_BINDING: return 1;
    case GL_BLEND: return 1;
    case GL_BLEND_COLOR: return 4;
    case GL_BLEND_DST_ALPHA: return 1;
    case GL_BLEND_DST_RGB: return 1;
    case GL_BLEND_EQUATION_ALPHA: return 1;
    case GL_BLEND_EQUATION_RGB: return 1;
    case GL_BLEND_SRC_ALPHA: return 1;
    case GL_BLEND_SRC_RGB: return 1;
    case GL_BLUE_BITS: return 1;
    case GL_COLOR_CLEAR_VALUE: return 4;
    case GL_COLOR_WRITEMASK: return 4;
    case GL_COMPRESSED_TEXTURE_FORMATS: {
        int num;
        glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &num);
        return num;
    }
    case GL_CULL_FACE: return 1;
    case GL_CULL_FACE_MODE: return 1;
    case GL_CURRENT_PROGRAM: return 1;
    case GL_DEPTH_BITS: return 1;
    case GL_DEPTH_CLEAR_VALUE: return 1;
    case GL_DEPTH_FUNC: return 1;
    case GL_DEPTH_RANGE: return 2;
    case GL_DEPTH_TEST: return 1;
    case GL_DEPTH_WRITEMASK: return 1;
    case GL_DITHER: return 1;
    case GL_ELEMENT_ARRAY_BUFFER_BINDING: return 1;
    case GL_FRAMEBUFFER_BINDING: return 1;
    case GL_FRONT_FACE: return 1;
    case GL_GENERATE_MIPMAP_HINT: return 1;
    case GL_GREEN_BITS: return 1;
    case GL_IMPLEMENTATION_COLOR_READ_FORMAT: return 1;
    case GL_IMPLEMENTATION_COLOR_READ_TYPE: return 1;
    case GL_LINE_WIDTH: return 1;
    case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS: return 1;
    case GL_MAX_CUBE_MAP_TEXTURE_SIZE: return 1;
    case GL_MAX_FRAGMENT_UNIFORM_VECTORS: return 1;
    case GL_MAX_RENDERBUFFER_SIZE: return 1;
    case GL_MAX_TEXTURE_IMAGE_UNITS: return 1;
    case GL_MAX_TEXTURE_SIZE: return 1;
    case GL_MAX_VARYING_VECTORS: return 1;
    case GL_MAX_VERTEX_ATTRIBS: return 1;
    case GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS: return 1;
    case GL_MAX_VERTEX_UNIFORM_VECTORS: return 1;
    case GL_MAX_VIEWPORT_DIMS: return 2;
    case GL_NUM_COMPRESSED_TEXTURE_FORMATS: return 1;
    case GL_NUM_SHADER_BINARY_FORMATS: return 1;
    case GL_PACK_ALIGNMENT: return 1;
    case GL_POLYGON_OFFSET_FACTOR: return 1;
    case GL_POLYGON_OFFSET_FILL: return 1;
    case GL_POLYGON_OFFSET_UNITS: return 1;
    case GL_RED_BITS: return 1;
    case GL_RENDERBUFFER_BINDING: return 1;
    case GL_SAMPLE_ALPHA_TO_COVERAGE: return 1;
    case GL_SAMPLE_BUFFERS: return 1;
    case GL_SAMPLE_COVERAGE: return 1;
    case GL_SAMPLE_COVERAGE_INVERT: return 1;
    case GL_SAMPLE_COVERAGE_VALUE: return 1;
    case GL_SAMPLES: return 1;
    case GL_SCISSOR_BOX: return 4;
    case GL_SCISSOR_TEST: return 1;
    case GL_SHADER_BINARY_FORMATS: {
        int num;
        glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS, &num);
        return num;
    }
    case GL_SHADER_COMPILER: return 1;
    case GL_STENCIL_BACK_FAIL: return 1;
    case GL_STENCIL_BACK_FUNC: return 1;
    case GL_STENCIL_BACK_PASS_DEPTH_FAIL: return 1;
    case GL_STENCIL_BACK_PASS_DEPTH_PASS: return 1;
    case GL_STENCIL_BACK_REF: return 1;
    case GL_STENCIL_BACK_VALUE_MASK: return 1;
    case GL_STENCIL_BACK_WRITEMASK: return 1;
    case GL_STENCIL_BITS: return 1;
    case GL_STENCIL_CLEAR_VALUE: return 1;
    case GL_STENCIL_FAIL: return 1;
    case GL_STENCIL_FUNC: return 1;
    case GL_STENCIL_PASS_DEPTH_FAIL: return 1;
    case GL_STENCIL_PASS_DEPTH_PASS: return 1;
    case GL_STENCIL_REF: return 1;
    case GL_STENCIL_TEST: return 1;
    case GL_STENCIL_VALUE_MASK: return 1;
    case GL_STENCIL_WRITEMASK: return 1;
    case GL_SUBPIXEL_BITS: return 1;
    case GL_TEXTURE_BINDING_2D: return 1;
    case GL_TEXTURE_BINDING_CUBE_MAP: return 1;
    case GL_UNPACK_ALIGNMENT: return 1;
    case GL_VIEWPORT: return 4;
	default: assert(false);
	}
}

