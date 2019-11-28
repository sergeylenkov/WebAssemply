#include <emscripten.h>
#include <emscripten/html5.h>
#include <functional>
#include <iostream>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

std::function<void()> loop;
void main_loop() { loop(); }

int main() {
    EmscriptenWebGLContextAttributes attrs;

    attrs.explicitSwapControl = 0;
    attrs.depth = 1;
    attrs.stencil = 1;
    attrs.antialias = 1;
    attrs.majorVersion = 2;
    attrs.minorVersion = 0;

    auto context = emscripten_webgl_create_context("canvas", &attrs);
    emscripten_webgl_make_context_current(context);

    glViewport(0, 0, 1200, 1000);

    GLint compile_ok = GL_FALSE;
    GLint link_ok = GL_FALSE;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const char *vs_source =	
		"attribute vec2 coord2d;\n\
		void main(void) {\n\
			gl_Position = vec4(coord2d, 0.0, 1.0);\n\
		}";

	glShaderSource(vs, 1, &vs_source, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);

	if (!compile_ok) {
		std::cout << "Error in vertex shader" << std::endl;
		return 0;
	}

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fs_source =	
		"void main(void) {\n\
			gl_FragColor = vec4(0.5, 1.0, 1.0, 1.0);\n\
		}";

	glShaderSource(fs, 1, &fs_source, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);

	if (!compile_ok) {
		std::cout << "Error in fragment shader" << std::endl;
		return 0;
	}

    GLuint program = glCreateProgram();

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);

	if (!link_ok) {
		std::cout << "Error in glLinkProgram" << std::endl;
		return 0;
	}

    const char* attribute_name = "coord2d";
	GLint attribute_coord2d = glGetAttribLocation(program, attribute_name);

	if (attribute_coord2d == -1) {
		std::cout << "Could not bind attribute " << attribute_name << std::endl;
		return 0;
	}

	GLuint vbo_triangle;

   	GLfloat triangle_vertices[] = {
	    0.0,  0.5,
	    -0.5, -0.5,
	     0.5, -0.5,
	};
	
	glGenBuffers(1, &vbo_triangle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);

	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

    loop = [&] {    
        glClearColor(0.2f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	    glEnableVertexAttribArray(attribute_coord2d);

		glVertexAttribPointer(
			attribute_coord2d,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			0
		);	 
	   
	    glDrawArrays(GL_TRIANGLES, 0, 3);
	
	    glDisableVertexAttribArray(attribute_coord2d);
    };

    emscripten_set_main_loop(main_loop, 0, true);

    return 0;
}
