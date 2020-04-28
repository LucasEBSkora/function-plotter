#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

class Camera {
  private:

    enum CameraCalculationStep {
      CAMERA = 0,
      CAMERAROTATE = 1,
      MODEL = 2,
      MODELROTATE = 3,
      READY = 4
    };

    struct Rotation {
      float angle;
      glm::vec3 normal;
    };

    public:
    
    glm::mat4 proj;
    glm::mat4 camera;
    glm::mat4 cameraRotated;
    glm::mat4 model;
    glm::mat4 result;

    glm::vec3 cameraPos;
    glm::vec3 modelPos;

    std::vector<struct Rotation> cameraRotations;

    std::vector<struct Rotation> modelRotations;

    bool cameraCalculation[READY];
  
  public:
    Camera();
    ~Camera();
    
    void setProj(float x1, float x2, float y1, float y2, float z1 = -1.0f, float z2 = 1.0f);
    void setProjAspectRatio(float aspect, float scale = 1.0f);

    void setCameraPos(float x, float y, float z);
    void setModelPos(float x, float y, float z);

    void rotateCamera(float angle, float vx, float vy, float vz);
    void resetCameraRotation(float angle = 0.0f, float vx = 0.0f, float vy = 0.0f, float vz = 0.0f);

    void rotateModel(float angle, float vx, float vy, float vz);
    void resetModelRotation(float angle = 0.0f, float vx = 0.0f, float vy = 0.0f, float vz = 0.0f);

    void calculateResult();
    const glm::mat4& getResult();
  
  private:
    void calculateCamera();
    void applyCameraRotations();
    void calculateModel();
    void applyModelRotations();
    
};

#endif