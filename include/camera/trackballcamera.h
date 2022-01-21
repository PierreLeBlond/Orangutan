#ifndef TRACK_BALL_CAMERA_H
#define TRACK_BALL_CAMERA_H

#include "camera/camera.h"
#include "object/object.h"

class TrackBallCamera : public Camera {
 public:
  TrackBallCamera(const std::string &name);

  void Update() override;
  void Move(glm::vec3 &direction) override;

 private:
  float _radius;
};

#endif  // TRACK_BALL_CAMERA_H
