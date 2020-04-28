#include "Camera.hpp"

#include <iostream>

Camera::Camera() : proj{glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f)},
  cameraPos{0.0f, 0.0f, 0.0f},
  modelPos{0.0f, 0.0f, 0.0f} {
    for (int i = 0; i <= READY; ++i) {
      cameraCalculation[i] = true;
    }
    result = proj;
}

Camera::~Camera() {

}

void Camera::setProj(float x1, float x2, float y1, float y2, float z1, float z2) {
  proj = glm::ortho(x1,x2, y1, y2, z1, z2);
  
  for (int i = CAMERA; i <= READY; ++i) {
      cameraCalculation[i] = false;
    }
}

void Camera::setProjAspectRatio(float aspect, float scale) {
  setProj(-scale*aspect, scale*aspect, -scale, scale, -1.0f, 1.0f);
}

void Camera::setCameraPos(float x, float y, float z) {
  cameraPos = glm::vec3(-x, -y, -z);

  for (int i = CAMERA; i <= READY; ++i) {
      cameraCalculation[i] = false;
    }
}

void Camera::setModelPos(float x, float y, float z) {
  modelPos = glm::vec3(x, y, z);
  
  for (int i = MODEL; i <= READY; ++i) {
      cameraCalculation[i] = false;
    }
}

void Camera::rotateCamera(float angle, float vx, float vy, float vz) {
  
  if (angle != 0.0f && (vx != 0.0f || vy != 0.0f || vz != 0.0f)) {
  
    cameraRotations.push_back({angle, {vx, vy, vz}});

  }

  for (int i = MODEL; i <= READY; ++i) {
      cameraCalculation[i] = false;
    }
}

void Camera::resetCameraRotation(float angle, float vx, float vy, float vz) {
  cameraRotations.clear();

  cameraRotated = camera;
  
  rotateCamera(angle, vx, vy, vz);
}

void Camera::rotateModel(float angle, float vx, float vy, float vz) {
  if (angle != 0.0f && (vx != 0.0f || vy != 0.0f || vz != 0.0f)) {
  
    modelRotations.push_back({angle, {vx, vy, vz}});

  }
  for (int i = READY; i <= READY; ++i) {
      cameraCalculation[i] = false;
    }

}

void Camera::resetModelRotation(float angle, float vx, float vy, float vz) {
  modelRotations.clear();

  result = model;
  
  rotateModel(angle, vx, vy, vz);
}

const glm::mat4& Camera::getResult() {
  if (!cameraCalculation[READY]) calculateResult();
  return result;
}

void Camera::calculateCamera() {
  camera = glm::translate(proj, cameraPos);
}

void Camera::applyCameraRotations() {
  cameraRotated = camera;
  for (struct Camera::Rotation r : cameraRotations) {
    cameraRotated = glm::rotate(cameraRotated, r.angle, r.normal);
  }
}

void Camera::calculateModel() {
  model = glm::translate(cameraRotated, modelPos);
}

void Camera::applyModelRotations() {
  result = model;
  for (struct Camera::Rotation r : modelRotations) {
    result = glm::rotate(result, r.angle, r.normal);
  }
}

void Camera::calculateResult() {

  if (!cameraCalculation[CAMERA])
    calculateCamera();

  if (!cameraCalculation[CAMERAROTATE])
    applyCameraRotations();

  if (!cameraCalculation[MODEL])
    calculateModel();

  if (!cameraCalculation[MODELROTATE]) 
    applyModelRotations();

  cameraCalculation[READY] = true;
  

}