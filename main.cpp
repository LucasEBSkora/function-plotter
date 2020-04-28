
#include "GLErrorUtils.hpp"
#include "renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

void error_callback(int error, const char* description) {
    std::cout << description << std::endl;
}

int main(void)
{
    GLFWwindow* window;
    

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
    int w_width = 1080;
    int w_height = 720;
    window = glfwCreateWindow(w_width, w_height, "Hello World", NULL, NULL);
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

      float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
      };

      unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
      };

      //docs.gl

      Texture texture("res/textures/Kuo-Toa+Druid-finished.png");
      texture.bind();

      
      VertexArray va;
      VertexBuffer vb(positions, 4 * (2 + 2)* sizeof (float));
      
      VertexBufferLayout layout;
      layout.Push<float>(2);
      layout.Push<float>(2);
      va.addBuffer(vb, layout);

      IndexBuffer ib(indices, 6);


      Shader shader("res/shaders/basic.shader");
      
      shader.bind();

      Camera camera;
      camera.setProjAspectRatio(aspect_ratio, 1.0f);
      camera.setCameraPos(0.0f, 0.25f, 0.f);
      camera.setModelPos(0.75f, 0.0f, 0.0f);

      shader.setUniforMat4f("u_MVP", camera.getResult());
      shader.setUniform1i("u_Texture", 0);

     Renderer renderer;

      float festa1 = 0.0f;
      float festa2 = 0.5f;
      float festa3 = 0.1f;
      float inc1 = 0.01f;
      float inc2 = 0.005f;
      float inc3 = 0.02f;
      /* Loop until the user closes the window */
      while (!glfwWindowShouldClose(window)) {
          /* Render here */

          renderer.clear();

          shader.setUniform4f("u_Color", festa1, festa2, festa3, 1.0f);

          renderer.draw(GL_TRIANGLES, va, ib, shader);

          camera.resetCameraRotation(festa1*6.28f, 0.0f, 1.0f, 0.0f);
          camera.resetModelRotation(festa2*6.28f, 1.0f, 0.0f, 0.0f);
          shader.setUniforMat4f("u_MVP", camera.getResult());

          /* Swap front and back buffers */
          glfwSwapBuffers(window);

          /* Poll for and process events */
          glfwPollEvents();

          festa1 += inc1;
          festa2 += inc2;
          festa3 += inc3;
          if (festa1 > 1.0f || festa1 < 0.0f) inc1 *= -1;
          if (festa2 > 1.0f || festa2 < 0.0f) inc2 *= -1;
          if (festa3 > 1.0f || festa3 < 0.0f) inc3 *= -1;
      }

    }

    glfwTerminate();
    return 0;
}