#ifndef SEAPERCH_SEAPERCH_ORIENTATION_H
#define SEAPERCH_SEAPERCH_ORIENTATION_H

class Orientation {
public:
    Orientation();

    Orientation(float roll, float pitch, float yaw);

    Orientation(Orientation const &orientation);

    float getRoll() const;

    float getPitch() const;

    float getYaw() const;

private:
    float roll;
    float pitch;
    float yaw;
};

#endif //SEAPERCH_SEAPERCH_ORIENTATION_H
