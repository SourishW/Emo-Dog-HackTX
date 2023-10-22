#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H
// for future reference, can be reduced to max 6 pins
#define MOTOR_PWMA 7
#define MOTOR_AIN1 16
#define MOTOR_AIN2 15

#define MOTOR_PWMC 19
#define MOTOR_CIN1 21
#define MOTOR_CIN2 20

// A is left, C is right
#define MOTOR_A_LEDC_CHAN 0
#define MOTOR_C_LEDC_CHAN 1

#define MOTOR_FREQ 20000

class Vehicle{
    public:
        int current_speed;
        int desired_speed;
        Vehicle() : current_speed(0), desired_speed(0) {};
        void init();
        // positive is cw, negative is ccw
        void setSpeed(int desired);
        int getSpeed();
        void turnRight(int turnSpeed);
        void turnLeft(int turnSpeed);
        void turnRightBackwards(int turnSpeed);
        void turnLeftBackwards(int turnSpeed);
};




#endif