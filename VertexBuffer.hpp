#ifndef __VERTEXBUFFER__HPP__
#define __VERTEXBUFFER__HPP__

class VertexBuffer {
  private:
    unsigned int m_renderer_ID;
  public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};

#endif