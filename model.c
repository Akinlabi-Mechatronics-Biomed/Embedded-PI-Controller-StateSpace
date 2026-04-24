/*
* model.c
*
* 
*/
 
#include "model.h"
 
SystemState sys_state;
 
// Matrices derived from PDF Equation 3 (50kHz sampling)
// Hardcoded flattened arrays for performance
const float Ad[6][6] = {
    {0.9652, -0.0172, 0.0057, -0.0058, 0.0052, -0.0251},
    {0.7732, 0.1252, 0.2315, 0.0700, 0.1282, 0.7754},
    {0.8278, -0.7522, -0.0956, 0.3299, -0.4855, 0.3915},
    {0.9948, 0.2655, -0.3848, 0.4212, 0.3927, 0.2899},
    {0.7648, -0.4165, -0.4855, -0.3366, -0.0986, 0.7281},
    {1.1056, 0.7587, 0.1179, 0.0748, -0.2192, 0.1491}
};
 
const float Bd[6] = {0.0471, 0.0377, 0.0404, 0.0485, 0.0373, 0.0539};
 
void Model_Init(void) {
    for(int i=0; i<6; i++) sys_state.x[i] = 0.0f;
}
 
// Runs one time-step of the discrete model
float Model_Update(float u_in) {
    float next_x[6] = {0};
 
    // Matrix Multiplication: x(k+1) = Ad * x(k) + Bd * u(k)
    for (int r = 0; r < 6; r++) {
        // A * x part
        for (int c = 0; c < 6; c++) {
            next_x[r] += Ad[r][c] * sys_state.x[c];
        }
        // + B * u part
        next_x[r] += Bd[r] * u_in;
    }
 
    // Update state
    for (int i = 0; i < 6; i++) {
        sys_state.x[i] = next_x[i];
    }
 
    // Output y = u3 (Last state element based on C matrix [0 0 0 0 0 1])
    return sys_state.x[5];
}
 
float Model_GetOutputVoltage(void) {
    return sys_state.x[5];
}
