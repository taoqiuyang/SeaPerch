class MotorSpecs {
public:
    float getNormalized_joystick_X() const {
        return normalized_joystick_X;
    }

    void setNormalized_joystick_X(float normalized_joystick_X) {
        MotorSpecs::normalized_joystick_X = normalized_joystick_X;
    }

private:
    float normalized_joystick_X;
};