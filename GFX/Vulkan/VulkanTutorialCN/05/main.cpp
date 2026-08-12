//#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
const int WIDTH = 800;
const int HEIGHT = 600;

class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:

    GLFWwindow* window = nullptr;
    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan() {

    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        glfwDestroyWindow(window);

        glfwTerminate();
    }
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}