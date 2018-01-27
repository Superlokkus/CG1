#include "sdl2_helper.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

mk::sdl2_error::sdl2_error(const std::string &what) :
        runtime_error(what + " SDL:" + SDL_GetError()) {
    SDL_ClearError();

}

mk::sdl2_error::sdl2_error(const char *what) :
        runtime_error(std::string(what) + " SDL:" + SDL_GetError()) {
    SDL_ClearError();
}

struct mk::sdl2_helper::impl {
    SDL_Window *mainwindow{nullptr};
    SDL_GLContext maincontext{};
};

mk::sdl2_helper::sdl2_helper(int gl_major, int gl_minor) :
        impl(new struct impl()) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw sdl2_error("Unable to initialize SDL");

    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_major))
        throw sdl2_error("Unable to set gl major version to " + std::to_string(gl_major));
    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_minor))
        throw sdl2_error("Unable to set gl minor version to " + std::to_string(gl_minor));
    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE))
        throw sdl2_error("Unable to set gl profile");

    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    /* Create our window centered at 512x512 resolution */
    this->impl->mainwindow = SDL_CreateWindow("s70357", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                              512, 512,
                                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    if (!this->impl->mainwindow)
        throw sdl2_error("Unable to create window");

    this->impl->maincontext = SDL_GL_CreateContext(this->impl->mainwindow);
    if (!this->impl->maincontext) {
        SDL_DestroyWindow(this->impl->mainwindow);
        SDL_Quit();
        throw sdl2_error("Unable to create context");
    }
}

mk::sdl2_helper::~sdl2_helper() {
    SDL_GL_DeleteContext(this->impl->maincontext);
    SDL_DestroyWindow(this->impl->mainwindow);
    SDL_Quit();
}
