#ifndef SEAPERCH_ROBOTDATA_H
#define SEAPERCH_ROBOTDATA_H

class RobotData {
public:
    explicit RobotData();

    const float getBatteryVoltage() const;

    void setBatteryVoltage(const float aBatteryVoltage);

private:
    float batteryVoltage;
};

#endif //SEAPERCH_ROBOTDATA_H
