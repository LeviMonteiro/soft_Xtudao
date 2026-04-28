#pragma once
#ifndef NB_FUNCTIONS_H
#define NB_FUNCTIONS_H

#include "main.h"


typedef enum
{
	off = 0,
	on  = 1
}type_on_off;

typedef enum
{
	False = 0,
	True  = 1
}type_bool;

typedef struct
{
	uint32_t initial_time;
	uint32_t elapsed_time;
	uint32_t delay_time;
}type_ST; // tipo soft timer

typedef enum
{
	Inactive = 0,
	Active   = 1
}type_bool_state;

typedef struct
{
	type_bool_state state;
	uint32_t T;
	uint32_t t_act;
	uint32_t t_ina;
	float duty_cycle;
	GPIO_TypeDef *Port;
	uint16_t Pin;
	type_ST timer;
	uint32_t T_shadow;
	float duty_cicle_shadow;
	type_bool_state shadow;

}type_PWM; // tipo PWM

typedef enum
{
	Detecting           = 0,
	Possible_transition = 1,
	Detected            = 2
} type_transition_state;

typedef struct 
{
	type_bool_state atu;
	
	type_bool_state ant;
	
	type_transition_state state;
	
	type_ST timer_db;
	
	int time_debounce;
	
	GPIO_TypeDef *Port;
	
	uint16_t Pin;
	
}type_rise_transition;

typedef enum
{
	RISE_EDGE = 0,
	FALL_EDGE = 1
} type_edge;


typedef struct
{
	type_bool_state atu;
	type_bool_state ant;

	type_transition_state transition_state;

	type_ST timer_db;
	uint32_t debounce_time;

} type_button;





void ST_Init(type_ST *pST, uint32_t time_lapse);
type_bool ST(type_ST *pST);
void ST_Lapse(type_ST *pST);

void PWM_Run(type_PWM *pPWM);
void PWM_Init(type_PWM *pPWM,
	GPIO_TypeDef* GPIO_Port,
	uint16_t GPIO_Pin, 
	uint32_t Period,
	float Duty); 
void PWM_Update(type_PWM *pPWM,
	uint32_t Period, 
	float Duty,
	type_bool_state shadow);

type_transition_state Button_Debounce(type_button *btn, type_bool_state leitura);

void Button_Init(type_button *btn, uint32_t debounce_time);

void Rise_Init(type_rise_transition *rt, uint32_t debounce_time);
type_bool Edge_Detect(type_rise_transition *rt, type_bool_state leitura, type_edge edge);

#endif
