#include "servo.h"
#include <math.h>
#include <stdio.h>



void Xturn(uint8_t direction){
	if(direction){
		HAL_GPIO_WritePin(frontal_1_GPIO_Port,frontal_1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(frontal_2_GPIO_Port,frontal_2_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(frontal_3_GPIO_Port,frontal_3_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(frontal_4_GPIO_Port,frontal_4_Pin,GPIO_PIN_SET);
	}
	else{
		
		HAL_GPIO_WritePin(frontal_1_GPIO_Port,frontal_1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(frontal_2_GPIO_Port,frontal_2_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(frontal_3_GPIO_Port,frontal_3_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(frontal_4_GPIO_Port,frontal_4_Pin,GPIO_PIN_RESET);
	}
}

void Yturn(uint8_t direction){
	if(direction){
		HAL_GPIO_WritePin(profile_1_GPIO_Port,profile_1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(profile_2_GPIO_Port,profile_2_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(profile_3_GPIO_Port,profile_3_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(profile_4_GPIO_Port,profile_4_Pin,GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(profile_1_GPIO_Port,profile_1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(profile_2_GPIO_Port,profile_2_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(profile_3_GPIO_Port,profile_3_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(profile_4_GPIO_Port,profile_4_Pin,GPIO_PIN_RESET);
	}
}

float Pitch,Roll,Yaw;

/********************/
void angelToPosition(void){
	
}

uint16_t times = 0; 
double Pitchs = 0,Rolls = 0,Yaws = 0;

int setZero(void){
	printf("p:%.2f  r:%.2f",Pitch,Roll);
	if(times<5000){
		Pitchs += Pitch;
		Rolls += Roll;
		Yaws += Yaw;
	}
	else if(times == 5000){
		Pitchs = Pitchs/5000;
		Rolls = Rolls/5000;
		Yaws = Yaws/5000;
	}
	else{
		return 1;
	}
	return 0;
}

/********************/
int Xbiaslast = 0,Ybiaslast = 0;

void PIDtoPosition(uint8_t* position){
	int Xbias = 0,Ybias = 0;
	uint8_t Xangel = Roll-Rolls;
	uint8_t Yangel = Pitch-Pitchs;
	
	Xbias = position[0] - Xangel;
	Ybias = position[1] - Yangel;
	
	uint8_t Xpwm = frontalKp*Xbias + frontalKi* Xbiaslast;
	uint8_t Ypwm = profileKp*Ybias + profileKi*Ybiaslast;
	
	if(Xbias>=0){
		Xturn(1);
	}
	else{
		Xturn(0);
	}
	if(Ybias>=0){
		Yturn(1);
	}
	else{
		Yturn(0);
	}
	

	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,Xpwm);
	__HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_1,Ypwm);
	
	Xbiaslast = Xbias;
	Ybiaslast = Ybias;
}
