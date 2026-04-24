/*
* controller.h
*
*  Created on: Jan 10, 2026
*      Author: Akinlabi
*/
#include "controller.h"
 
void PI_Init(PI_Controller *pid, float Kp, float Ki, float Ts) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->T_sample = Ts; //0.00002
    pid->integral_sum = 0.0f;
    pid->limit_max = 100.0f;
    pid->limit_min = -100.0f;
}
 
void PI_Reset(PI_Controller *pid) {
    pid->integral_sum = 0.0f;
}
 
float PI_Calculate(PI_Controller *pid, float reference, float measurement) {
    float error = reference - measurement;
    float p_out = pid->Kp * error;
 
    pid->integral_sum += (error * pid->T_sample);
 
    float output = p_out + (pid->Ki * pid->integral_sum);
 
    if (output > pid->limit_max) {
        output = pid->limit_max;
        pid->integral_sum -= (error * pid->T_sample);
    } else if (output < pid->limit_min) {
        output = pid->limit_min;
        pid->integral_sum -= (error * pid->T_sample);
    }
 
    return output;
}
