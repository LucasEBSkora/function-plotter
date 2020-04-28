#ifndef __FUNCTION_PLOT_GENERATOR__
#define __FUNCTION_PLOT_GENERATOR__

#include <vector>
#include <functional>

typedef std::function<float(float,float)> sphericalCoordinateFunction;

class FunctionPlotGenerator {

  private:
    
    struct Vertex {
      float x;
      float y;
      float z;
    };

    struct Line {
      struct Vertex start;
      struct Vertex end;
    };

    std::vector<float> vertexBufferData;

    std::vector<unsigned int> surfaceIndexBufferData;
    std::vector<unsigned int> lineIndexBufferData;
    
    unsigned int currentIndex;

    sphericalCoordinateFunction callback;
    unsigned int slices;
    double angularIncrement; 
    float scale;

  public:
    FunctionPlotGenerator(sphericalCoordinateFunction toDraw, unsigned int slices, float scaleFactor);
    ~FunctionPlotGenerator();

    const float* getVertexBufferData() const;
    unsigned int getVertexBufferDataCount() const;
    
    const unsigned int* getSurfaceIndexBufferData() const;
    unsigned getSurfaceIndexBufferDataCount() const;
    
    const unsigned int* getLineIndexBufferData() const;
    unsigned getLineIndexBufferDataCount() const;

    void fillBuffers();
  
  private:
    void fillDataBuffer();
    void fillLineIndexBuffer();
    void fillSurfaceIndexBuffer();


    unsigned int getVertexBufferCoords(unsigned int theta, unsigned int phi) const;
    void addVertexToBuffer(struct Vertex vertex);
    

};

#endif