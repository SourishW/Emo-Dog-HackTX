#include "Movement.h"
#include <esp32-hal-ledc.h>
#include <esp_timer.h>
#include <Arduino.h>

// hw_timer_t* pwm_updater = NULL;
// Vehicle* val;
// void IRAM_ATTR update_pwm(){
//     if(val->current_speed == val->desired_speed) return;
//     if(val->desired_speed)
// }

void Vehicle::init(){
    ledcSetup(MOTOR_A_LEDC_CHAN, MOTOR_FREQ, 8);
    ledcSetup(MOTOR_C_LEDC_CHAN, MOTOR_FREQ, 8);
    ledcAttachPin(MOTOR_PWMA, MOTOR_A_LEDC_CHAN);
    ledcAttachPin(MOTOR_PWMC, MOTOR_C_LEDC_CHAN);
    pinMode(MOTOR_AIN1, OUTPUT);
    pinMode(MOTOR_AIN2, OUTPUT);
    pinMode(MOTOR_CIN1, OUTPUT);
    pinMode(MOTOR_CIN2, OUTPUT);
    digitalWrite(MOTOR_AIN1, HIGH);
    digitalWrite(MOTOR_AIN2, LOW);
    digitalWrite(MOTOR_CIN1, HIGH);
    digitalWrite(MOTOR_CIN2, LOW);
    ledcWrite(MOTOR_A_LEDC_CHAN, 0);
    ledcWrite(MOTOR_C_LEDC_CHAN, 0);
    
    // pwm_updater = timerBegin(0, 80, true);
    // val = this;
}

void Vehicle::setSpeed(int desired){
    current_speed = desired;
    if(current_speed > 0){
        digitalWrite(MOTOR_AIN1, HIGH);
        digitalWrite(MOTOR_AIN2, LOW);
        digitalWrite(MOTOR_CIN1, HIGH);
        digitalWrite(MOTOR_CIN2, LOW);
    }else{
        digitalWrite(MOTOR_AIN1, LOW);
        digitalWrite(MOTOR_AIN2, HIGH);
        digitalWrite(MOTOR_CIN1, LOW);
        digitalWrite(MOTOR_CIN2, HIGH);
    }
    ledcWrite(MOTOR_A_LEDC_CHAN, current_speed%128);
    ledcWrite(MOTOR_C_LEDC_CHAN, current_speed%128);
}

int Vehicle::getSpeed(){
    return current_speed;
}

void Vehicle::turnRight(int turnSpeed){
    current_speed = turnSpeed;
    if(current_speed > 0){
        digitalWrite(MOTOR_AIN1, HIGH);
        digitalWrite(MOTOR_AIN2, LOW);
        digitalWrite(MOTOR_CIN1, HIGH);
        digitalWrite(MOTOR_CIN2, LOW);
    }else{
        digitalWrite(MOTOR_AIN1, HIGH);
        digitalWrite(MOTOR_AIN2, LOW);
        digitalWrite(MOTOR_CIN1, HIGH);
        digitalWrite(MOTOR_CIN2, LOW);
    }
    ledcWrite(MOTOR_A_LEDC_CHAN, turnSpeed%256);
    ledcWrite(MOTOR_C_LEDC_CHAN, ((turnSpeed)>>2)%256);
}

void Vehicle::turnLeft(int turnSpeed){
    current_speed = turnSpeed;
    if(desired_speed < 0){
        digitalWrite(MOTOR_AIN1, HIGH);
        digitalWrite(MOTOR_AIN2, LOW);
        digitalWrite(MOTOR_CIN1, LOW);
        digitalWrite(MOTOR_CIN2, HIGH);
    }else{
        digitalWrite(MOTOR_AIN1, LOW);
        digitalWrite(MOTOR_AIN2, HIGH);
        digitalWrite(MOTOR_CIN1, HIGH);
        digitalWrite(MOTOR_CIN2, LOW);
    }
    ledcWrite(MOTOR_A_LEDC_CHAN, turnSpeed%128);
    ledcWrite(MOTOR_C_LEDC_CHAN, turnSpeed%128);
}

void Vehicle::turnLeftBackwards(int turnSpeed){
    
}

void Vehicle::turnRightBackwards(int turnSpeed){
    
}