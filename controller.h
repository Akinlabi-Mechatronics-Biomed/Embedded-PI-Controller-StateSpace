#ifndef CONTROLLER_H
#define CONTROLLER_H
typedef struct {
    float Kp; float Ki; float integral_sum;
    float limit_max; float limit_min; float T_sample;
} PI_Controller;
void PI_Init(PI_Controller *pid, float Kp, float Ki, float Ts);
float PI_Calculate(PI_Controller *pid, float ref, float meas);
void PI_Reset(PI_Controller *pid);
#endif
