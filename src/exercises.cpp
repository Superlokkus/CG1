#include "exercises.hpp"
#include "opengl_helper.hpp"
#include "sdl2_opengl_helper.hpp"

#include <GL/glew.h>
#include <vector>
#include <array>

namespace {
enum VAO_IDs {
    Triangles, NumVAOs
};
enum Buffer_IDs {
    ArrayBuffer, NumBuffers
};
enum Attrib_IDs {
    vPosition, vColor
};
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6;

}

exercises::praktikum01_1::praktikum01_1() {
    glGenBuffers(NumBuffers, Buffers);//NumBuffers = 1
    glGenVertexArrays(NumVAOs, VAOs);//NumVAOs = 1
    GLfloat vertices[NumVertices][2] = {
            {-0.90, -0.90},
            {0.85,  -0.90},
            {-0.90, 0.85},
            {0.90,  -0.85},
            {0.90,  0.90},
            {-0.85, 0.90}};
    glBindVertexArray(VAOs[Triangles]);//Triangles = 0
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]); //ArrayBuffer = 0
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);//vPosition = 0
    glEnableVertexAttribArray(vPosition);
}

exercises::praktikum01_1::~praktikum01_1() {
    glDeleteBuffers(NumBuffers, Buffers);
}

void exercises::praktikum01_1::draw() {
    glClearColor(0, 1.0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glVertexAttrib3f(vColor, 1, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices / 2);
    glVertexAttrib3f(vColor, 0, 1, 0);
    glDrawArrays(GL_LINE_LOOP, 3, NumVertices / 2);
}

struct exercises::praktikum01_2::impl {
    using vertex_t = std::tuple<GLfloat, GLfloat>;
    std::vector<vertex_t> htw_logo_vertices;
    std::array<GLuint, 1> buffer_objects;
    std::array<GLuint, 1> vertex_array_objects;
};

exercises::praktikum01_2::praktikum01_2() : impl(new struct impl) {
    this->impl->htw_logo_vertices = {
            {-0.90, -0.90},
            {0.85,  -0.90},
            {-0.90, 0.85},
            {0.90,  -0.85},
            {0.90,  0.90},
            {-0.85, 0.90}};
    /*{
    {0, 0},
    {3, 0},
    {3, 15},
    {0, 15},
    {0,0},
};*/
    glGenBuffers(this->impl->buffer_objects.max_size(), this->impl->buffer_objects.data());
    glGenBuffers(this->impl->vertex_array_objects.max_size(), this->impl->vertex_array_objects.data());

    //glBindVertexArray(this->impl->vertex_array_objects.at(0));
    glBindBuffer(GL_ARRAY_BUFFER, this->impl->buffer_objects.at(0));
    glBufferData(GL_ARRAY_BUFFER,
                 this->impl->htw_logo_vertices.size() * sizeof(decltype(this->impl->htw_logo_vertices)::value_type),
                 this->impl->htw_logo_vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, true, 0, 0);
    glEnableVertexAttribArray(0);
}

exercises::praktikum01_2::~praktikum01_2() {
    glDeleteBuffers(this->impl->buffer_objects.size(), this->impl->buffer_objects.data());
    glDeleteVertexArrays(this->impl->vertex_array_objects.size(), this->impl->vertex_array_objects.data());
}

void exercises::praktikum01_2::draw() {
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(this->impl->vertex_array_objects.at(0));
    glVertexAttrib3f(vColor, 1, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, this->impl->htw_logo_vertices.size());
    glFlush();
}
