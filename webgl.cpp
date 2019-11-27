#include <emscripten.h>
#include <emscripten/html5.h>
#include <functional>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

extern "C" {

}

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

    loop = [&] {    
        glClearColor(0.2f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    };

    emscripten_set_main_loop(main_loop, 0, true);

    return 0;
}
