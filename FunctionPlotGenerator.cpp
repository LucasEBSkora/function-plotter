#include "FunctionPlotGenerator.hpp"

#include <iostream>
#include <math.h>

FunctionPlotGenerator::FunctionPlotGenerator(std::function<float(float,float)> toDraw, unsigned int slices, float scaleFactor) 
 : callback{toDraw},
   slices{slices},
   angularIncrement{M_PI/slices},
   scale{scaleFactor}
  {

}

FunctionPlotGenerator::~FunctionPlotGenerator() {
  
}

const float* FunctionPlotGenerator::getVertexBufferData() const {
  unsigned int i = 0;
  while (i < vertexBufferData.size()) {
    std::cout << '(' << vertexBufferData[i++] << ',' << vertexBufferData[i++] << ',' << vertexBufferData[i++] << ')' << std::endl;
  }
  return vertexBufferData.data();
}

unsigned int FunctionPlotGenerator::getVertexBufferDataCount() const {
  return vertexBufferData.size();
}

const unsigned int* FunctionPlotGenerator::getSurfaceIndexBufferData() const {
  unsigned int i = 0;
  while (i < surfaceIndexBufferData.size()) {
    std::cout << '(' << surfaceIndexBufferData[i++] << ',' << surfaceIndexBufferData[i++] << ',' << surfaceIndexBufferData[i++] << ')' << std::endl;
  }
  return surfaceIndexBufferData.data();
}

unsigned FunctionPlotGenerator::getSurfaceIndexBufferDataCount() const {
  return surfaceIndexBufferData.size();
}

const unsigned int* FunctionPlotGenerator::getLineIndexBufferData() const {
  return lineIndexBufferData.data();
}

unsigned FunctionPlotGenerator::getLineIndexBufferDataCount() const {
  return lineIndexBufferData.size();
}


void FunctionPlotGenerator::fillBuffers() {
  fillDataBuffer();
  fillLineIndexBuffer();
  fillSurfaceIndexBuffer();
}

void FunctionPlotGenerator::fillDataBuffer() {


  addVertexToBuffer({0.0f, scale*callback(0, 0), 0.0f});

  for (unsigned int phi = 1; phi < slices; ++phi) {
    for (unsigned int theta = 0; theta < 2*slices; ++theta) {
      
      float r = scale*callback(theta*angularIncrement, phi*angularIncrement);

      addVertexToBuffer({r*(float)cos(theta*angularIncrement)*(float)sin(phi*angularIncrement), r*(float)cos(phi*angularIncrement), r*(float)sin(theta*angularIncrement)*(float)sin(phi*angularIncrement)});
    }
    
  }

  addVertexToBuffer({0.0f, -scale*callback(0, slices*angularIncrement), 0.0f});  

}

void FunctionPlotGenerator::fillLineIndexBuffer() {
    
    //horizontal lines
  for (unsigned int phi = 1; phi < slices; ++phi) {
    for (unsigned int theta = 0; theta < 2*slices; ++theta) {
      lineIndexBufferData.push_back(getVertexBufferCoords(theta, phi));
      lineIndexBufferData.push_back(getVertexBufferCoords(theta + 1, phi));
    } 
  }

  std::cout.flush();
  for (unsigned int theta = 0; theta < 2*slices; ++theta) {
    for (unsigned int phi = 0; phi < slices; ++phi) {
      lineIndexBufferData.push_back(getVertexBufferCoords(theta, phi));
      lineIndexBufferData.push_back(getVertexBufferCoords(theta, phi + 1));
    } 
  }
}

void FunctionPlotGenerator::fillSurfaceIndexBuffer() {
  for (unsigned int phi = 0; phi < slices; ++phi) {
    for (unsigned int theta = 0; theta < 2*slices; ++theta) {
      surfaceIndexBufferData.push_back(getVertexBufferCoords(theta    , phi    ));
      surfaceIndexBufferData.push_back(getVertexBufferCoords(theta    , phi + 1));
      surfaceIndexBufferData.push_back(getVertexBufferCoords(theta + 1, phi + 1));

      surfaceIndexBufferData.push_back(getVertexBufferCoords(theta    , phi    ));
      surfaceIndexBufferData.push_back(getVertexBufferCoords(theta + 1, phi + 1));
      surfaceIndexBufferData.push_back(getVertexBufferCoords(theta + 1, phi   ));



    } 
  }
}

unsigned int FunctionPlotGenerator::getVertexBufferCoords(unsigned int theta, unsigned int phi) const {
    if (phi == 0) return 0;
    else if (phi == slices) theta = 0;
    return (unsigned int) 2*slices*(phi - 1) + ((theta != 2*slices) ? theta + 1 : 1);
}

void FunctionPlotGenerator::addVertexToBuffer(struct FunctionPlotGenerator::Vertex vertex) {
  vertexBufferData.push_back(vertex.x);
  vertexBufferData.push_back(vertex.y);
  vertexBufferData.push_back(vertex.z);
}
