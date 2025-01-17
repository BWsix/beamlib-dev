#pragma once

#include <beamlib.h>

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
        auto prog = Blib::ResourceManager::GetShader("skybox");
        prog.Use();
        prog.SetMat4("model", glm::scale(glm::mat4(1), glm::vec3(400)));
        prog.SetMat4("view", Blib::camera.getViewMatrix());
        prog.SetMat4("projection", Blib::camera.getProjectionMatrix());

        glBindVertexArray(Blib::ResourceManager::GetGLuint("skybox-vao"));
        glBindTexture(GL_TEXTURE_CUBE_MAP, Blib::ResourceManager::GetGLuint("skybox-texture-cubemap"));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthFunc(GL_LESS);
    }

    static void LoadResources() {
        Blib::ResourceManager::LoadShader("skybox", "shaders/skybox.vert.glsl", "shaders/skybox.frag.glsl");
        Blib::ResourceManager::GetGLuint("skybox-texture-cubemap") = Blib::loadCubeMap("textures/sky");
        // Blib::ResourceManager::GetGLuint("skybox-texture-cubemap") = Blib::loadCubeMap({
        //     "textures/skybox/right.jpg",
        //     "textures/skybox/left.jpg",
        //     "textures/skybox/top.jpg",
        //     "textures/skybox/bottom.jpg",
        //     "textures/skybox/front.jpg",
        //     "textures/skybox/back.jpg",
        // });

        GLuint& vao = Blib::ResourceManager::GetGLuint("skybox-vao");
        GLuint& vbo = Blib::ResourceManager::GetGLuint("skybox-vbo");

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    }
};
