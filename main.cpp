
#include "GLErrorUtils.hpp"
#include "renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

#include "FunctionPlotGenerator.hpp"

#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

void error_callback(int error, const char* description) {
    std::cout << description << std::endl;
}

int main(int argc, char **argv)
{
    GLFWwindow* window;

    if (argc != 2) {
      std::cout << "usage: ./build/plot N\nWhere N is the number of slices to use" << std::endl;
      exit(-1);
    }



    const unsigned int N = atoi(argv[1]);

    glfwSetErrorCallback(error_callback);
    /* Initialize the library */
    if (!glfwInit()) {
      std::cout << "oh boy" << std::endl;
      return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    int w_width = 1920;
    int w_height = 1080;
    window = glfwCreateWindow(w_width, w_height, "Spherical Plotter", glfwGetPrimaryMonitor(), NULL);
    float aspect_ratio = (float)w_width/w_height;
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    GLcall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLcall(glEnable(GL_BLEND));
    // glBlendEquation(GL_FUNC_ADD); ??

    if (glewInit() != GLEW_OK) {
      std::cout << "GLEW is not ok" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    {


      FunctionPlotGenerator sphere(
        [](float theta, float phi) {

          return 
            pow(cos(theta), 2)*
            (
              (
                log(1 + phi)*phi
                + sin((3.0f/2.0f)*phi)
              )
            )
            /
            (log(1+M_PI)*M_PI  - 1)
            + 
            pow(sin(theta), 2)*(exp(2*phi) - 1)/(exp(2*M_PI) - 1);
        },
        N, 1.0f);

      sphere.fillBuffers();
      //docs.gl
      
      VertexArray va;
      VertexBuffer vb(sphere.getVertexBufferData(), sphere.getVertexBufferDataCount() * sizeof (float));
      
      VertexBufferLayout layout;
      layout.Push<float>(3);
      va.addBuffer(vb, layout);

      IndexBuffer lines(sphere.getLineIndexBufferData(), sphere.getLineIndexBufferDataCount());

      IndexBuffer surface(sphere.getSurfaceIndexBufferData(), sphere.getSurfaceIndexBufferDataCount());

      Shader shader("res/shaders/basic.shader");
      
      shader.bind();

      Camera camera;
      camera.setProjAspectRatio(aspect_ratio, 1.0f);
      camera.setCameraPos(0.0f, -0.4f, 0.f);
      camera.rotateCamera(-0.1*M_PI, 1.0f, 0.0f, 0.0f);
      camera.setModelPos(0.0f, 0.0f, 0.0f);

      shader.setUniforMat4f("u_MVP", camera.getResult());

     Renderer renderer;

      double angle = 0.0;
      double incr = 0.01;

      /* Loop until the user closes the window */
      while (!glfwWindowShouldClose(window)) {
          /* Render here */

          renderer.clear();

          camera.resetModelRotation(angle, .0f, 1.0f, 0.0f);
          shader.setUniforMat4f("u_MVP", camera.getResult());

          shader.setUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 0.5f);
          renderer.draw(GL_TRIANGLES, va, surface, shader);

          shader.setUniform4f("u_Color", 0.5f, 0.5f, 0.5f, 1.0f);
          renderer.draw(GL_LINES, va, lines, shader);
          
          /* Swap front and back buffers */
          glfwSwapBuffers(window);

          /* Poll for and process events */
          glfwPollEvents();

          angle += incr;
      }

    }

    glfwTerminate();
    return 0;
}