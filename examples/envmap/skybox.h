#pragma once

#include <beamlib.h>

namespace EnvMapDemo {

const float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};

class Skybox {
public:
    void render() {
        glDepthFunc(GL_LEQUAL);
        auto prog = Blib::ResourceManager::GetShader("envmapdemo-skybox");
        prog.Use();
        glm::mat4 view = glm::mat4(glm::mat3(Blib::camera.getViewMatrix()));  
        prog.SetMat4("view", view);
        prog.SetMat4("projection", Blib::camera.getProjectionMatrix());

        glBindVertexArray(Blib::ResourceManager::GetGLuint("envmapdemo-skybox-vao"));
        glBindTexture(GL_TEXTURE_CUBE_MAP, Blib::ResourceManager::GetGLuint("envmapdemo-skybox-texture-cubemap"));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthFunc(GL_LESS);
    }

    static void LoadResources() {
        Blib::ResourceManager::LoadShader("envmapdemo-skybox", "examples/envmap/shaders/skybox.vert.glsl", "shaders/skybox.frag.glsl");
        Blib::ResourceManager::GetGLuint("envmapdemo-skybox-texture-cubemap") = Blib::loadCubeMap("textures/parkinglot");

        GLuint& vao = Blib::ResourceManager::GetGLuint("envmapdemo-skybox-vao");
        GLuint& vbo = Blib::ResourceManager::GetGLuint("envmapdemo-skybox-vbo");

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    }
};

}
