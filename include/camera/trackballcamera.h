#ifndef ORANGUTAN_CAMERA_TRACK_BALL_CAMERA_H
#define ORANGUTAN_CAMERA_TRACK_BALL_CAMERA_H

#include "camera/camera.h"
#include "object/object.h"

namespace orangutan {

class TrackBallCamera : public Camera {
 public:
  TrackBallCamera(const std::string &name);

  void Update() override;
  void Move(glm::vec3 &direction) override;

 private:
  float _radius;
};

}  // namespace orangutan

#endif  // ORANGUTAN_CAMERA_TRACK_BALL_CAMERA_H
