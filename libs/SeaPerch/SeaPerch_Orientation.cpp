#include "SeaPerch_Orientation.h"

Orientation::Orientation() { }

Orientation::Orientation(float roll, float pitch, float yaw) : roll(roll), pitch(pitch), yaw(yaw) {

}

Orientation::Orientation(Orientation const &orientation) {
    roll = orientation.getRoll();
    pitch = orientation.getPitch();
    yaw = orientation.getYaw();
}

float Orientation::getRoll() const {
    return roll;
}

float Orientation::getPitch() const {
    return pitch;
}

float Orientation::getYaw() const {
    return yaw;
}