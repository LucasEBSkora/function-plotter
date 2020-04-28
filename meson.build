project('log-esp-opengl', 'cpp')
src = ['main.cpp', 'IndexBuffer.cpp', 'VertexBuffer.cpp', 'renderer.cpp', 'VertexArray.cpp', 'VertexBufferLayout.cpp', 'Shader.cpp', 'GLErrorUtils.cpp', 'stb_image.cpp', 'Texture.cpp', 'Camera.cpp']
deps = [dependency('gl'), dependency('glfw3'), dependency('glew'), dependency('glm')]
executable('log-esp-opengl', sources : src, dependencies: deps)