#include <beamlib.h>
#include "scene.h"

int main() {
    const auto window = Blib::CreateWindow("envmap", Blib::WIDTH, Blib::HEIGHT);

    EnvMapScene::LoadResources();
    static EnvMapScene scene;
    scene.init();
    scene.setup();

    glfwSetWindowSizeCallback(window, [](GLFWwindow *, int width, int height) {
        Blib::WIDTH = width;
        Blib::HEIGHT = height;
        glViewport(0, 0, width, glm::max<int>(height, 1));
        Blib::camera.setAspect((float)width / height);
    });

    while (!Blib::WindowShouldClose(window)) {
        Blib::mouse.Update(window);
        Blib::camera.Update();

        scene.render();

        Blib::BeginUI();
        scene.renderUI();
        Blib::EndUI();

        glfwSwapBuffers(window);
    }

    Blib::DestroyWindow(window);

    return 0;
}
