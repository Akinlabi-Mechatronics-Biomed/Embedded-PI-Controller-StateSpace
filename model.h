#ifndef MODEL_H
#define MODEL_H
typedef struct { float x[6]; } SystemState;
void Model_Init(void);
float Model_Update(float u_in);
float Model_GetOutputVoltage(void);
#endif
