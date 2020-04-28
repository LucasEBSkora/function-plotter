#ifndef __INDEXBUFFER__HPP__
#define __INDEXBUFFER__HPP__

class IndexBuffer {
  private:
    unsigned int m_renderer_ID;
    unsigned int m_count;

  public:
    IndexBuffer(const void* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
    inline unsigned int getCount() const {return m_count;}
};

#endif