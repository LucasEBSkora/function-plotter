project('function-plotter', 'cpp')
src = ['main.cpp', 'IndexBuffer.cpp', 'VertexBuffer.cpp', 'renderer.cpp', 'VertexArray.cpp', 'VertexBufferLayout.cpp', 'Shader.cpp', 'GLErrorUtils.cpp', 'stb_image.cpp', 'Texture.cpp', 'Camera.cpp', 'FunctionPlotGenerator.cpp']
deps = [dependency('gl'), dependency('glfw3'), dependency('glew'), dependency('glm')]
executable('plot', sources : src, dependencies: deps)