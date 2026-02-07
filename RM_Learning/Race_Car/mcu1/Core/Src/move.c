#include "motor_mecanum.h"
#include "pid.h"
#include "remote_control.h"
#include "move.h"
// #include "tim.h"
// #include "main.h"

double TargetSpeed_LA = 0;
double TargetSpeed_LB = 0;
double TargetSpeed_RA = 0;
double TargetSpeed_RB = 0;
double PWM_LA = 0;
double PWM_LB = 0;
double PWM_RA = 0;
double PWM_RB = 0;


void Brake_All(void){
    Motor_Mecanum_LA_Brake();
    Motor_Mecanum_LB_Brake();
    Motor_Mecanum_RA_Brake();
    Motor_Mecanum_RB_Brake();
}

void Move_Update(RC_Type *rc)
{
    if(rc == NULL) return;


    /*------Straight------*/
    if(rc->ch2 < 0 && rc->ch1 == 0) //Forward
    {
        // HAL_GPIO_WritePin(LA1_GPIO_Port, LA1_Pin, GPIO_PIN_SET);
        // HAL_GPIO_WritePin(LA2_GPIO_Port, LA2_Pin, GPIO_PIN_RESET);
        // __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 420);

        TargetSpeed_LA = Real_MaxSpeed_LA;
        TargetSpeed_LB = Real_MaxSpeed_LB;
        TargetSpeed_RA = Real_MaxSpeed_RA;
        TargetSpeed_RB = Real_MaxSpeed_RB;
        
        PWM_LA = Speed_PID(0,TargetSpeed_LA,1);
        Motor_Mecanum_LA_Speed(PWM_LA);

        PWM_LB = Speed_PID(1,TargetSpeed_LB,1);
        Motor_Mecanum_LB_Speed(PWM_LB);

        PWM_RA = Speed_PID(2,TargetSpeed_RA,1);
        Motor_Mecanum_RA_Speed(PWM_RA);

        PWM_RB = Speed_PID(3,TargetSpeed_RB,1);
        Motor_Mecanum_RB_Speed(PWM_RB);
    }

    else if(rc->ch2 > 0 && rc->ch1 == 0) //Backward
    {
        TargetSpeed_LA = -Real_MaxSpeed_LA;
        TargetSpeed_LB = -Real_MaxSpeed_LB;
        TargetSpeed_RA = -Real_MaxSpeed_RA;
        TargetSpeed_RB = -Real_MaxSpeed_RB;
        
        PWM_LA = Speed_PID(0,TargetSpeed_LA,-1);
        Motor_Mecanum_LA_Speed(PWM_LA);

        PWM_LB = Speed_PID(1,TargetSpeed_LB,-1);
        Motor_Mecanum_LB_Speed(PWM_LB);

        PWM_RA = Speed_PID(2,TargetSpeed_RA,-1);
        Motor_Mecanum_RA_Speed(PWM_RA);

        PWM_RB = Speed_PID(3,TargetSpeed_RB,-1);
        Motor_Mecanum_RB_Speed(PWM_RB);
    }

    else if(rc->ch1 < 0 && rc->ch2 == 0) //Left
    {
        TargetSpeed_LA = -Real_MaxSpeed_LA;
        TargetSpeed_LB = Real_MaxSpeed_LB;
        TargetSpeed_RA = Real_MaxSpeed_RA;
        TargetSpeed_RB = -Real_MaxSpeed_RB;
        
        PWM_LA = Speed_PID(0,TargetSpeed_LA,-1);
        Motor_Mecanum_LA_Speed(PWM_LA);

        PWM_LB = Speed_PID(1,TargetSpeed_LB,1);
        Motor_Mecanum_LB_Speed(PWM_LB);

        PWM_RA = Speed_PID(2,TargetSpeed_RA,1);
        Motor_Mecanum_RA_Speed(PWM_RA);

        PWM_RB = Speed_PID(3,TargetSpeed_RB,-1);
        Motor_Mecanum_RB_Speed(PWM_RB);
    }

    else if(rc->ch1 > 0 && rc->ch2 == 0) //Right
    {
        TargetSpeed_LA = Real_MaxSpeed_LA;
        TargetSpeed_LB = -Real_MaxSpeed_LB;
        TargetSpeed_RA = -Real_MaxSpeed_RA;
        TargetSpeed_RB = Real_MaxSpeed_RB;
        
        PWM_LA = Speed_PID(0,TargetSpeed_LA,1);
        Motor_Mecanum_LA_Speed(PWM_LA);

        PWM_LB = Speed_PID(1,TargetSpeed_LB,-1);
        Motor_Mecanum_LB_Speed(PWM_LB);

        PWM_RA = Speed_PID(2,TargetSpeed_RA,-1);
        Motor_Mecanum_RA_Speed(PWM_RA);

        PWM_RB = Speed_PID(3,TargetSpeed_RB,1);
        Motor_Mecanum_RB_Speed(PWM_RB);
    }


    /*------Diagonal------*/
    else if(rc->ch1 < 0 && rc->ch2 < 0)//Diagonal Left Forward
    {
        TargetSpeed_LA = 0;
        TargetSpeed_LB = Real_MaxSpeed_LB;
        TargetSpeed_RA = Real_MaxSpeed_RA;
        TargetSpeed_RB = 0;

        Motor_Mecanum_LA_Brake();

        PWM_LB = Speed_PID(1,TargetSpeed_LB,1);
        Motor_Mecanum_LB_Speed(PWM_LB);

        PWM_RA = Speed_PID(2,TargetSpeed_RA,1);
        Motor_Mecanum_RA_Speed(PWM_RA);

        Motor_Mecanum_RB_Brake();
    }

    else if(rc->ch1 > 0 && rc->ch2 < 0)//Diagonal Right Forward
    {
        TargetSpeed_LA = Real_MaxSpeed_LA;
        TargetSpeed_LB = 0;
        TargetSpeed_RA = 0;
        TargetSpeed_RB = Real_MaxSpeed_RB;
        
        PWM_LA = Speed_PID(0,TargetSpeed_LA,1);
        Motor_Mecanum_LA_Speed(PWM_LA);

        Motor_Mecanum_LB_Brake();

        Motor_Mecanum_RA_Brake();

        PWM_RB = Speed_PID(3,TargetSpeed_RB,1);
        Motor_Mecanum_RB_Speed(PWM_RB);
    }

    else if(rc->ch1 < 0 && rc->ch2 > 0)//Diagonal Left Backward
    {
        TargetSpeed_LA = -Real_MaxSpeed_LA;
        TargetSpeed_LB = 0;
        TargetSpeed_RA = 0;
        TargetSpeed_RB = -Real_MaxSpeed_RB;
        
        PWM_LA = Speed_PID(0,TargetSpeed_LA,-1);
        Motor_Mecanum_LA_Speed(PWM_LA);

        Motor_Mecanum_LB_Brake();

        Motor_Mecanum_RA_Brake();

        PWM_RB = Speed_PID(3,TargetSpeed_RB,-1);
        Motor_Mecanum_RB_Speed(PWM_RB);
    }

    else if(rc->ch1 > 0 && rc->ch2 > 0)//Diagonal Right Backward
    {
        TargetSpeed_LA = 0;
        TargetSpeed_LB = -Real_MaxSpeed_LB;
        TargetSpeed_RA = -Real_MaxSpeed_RA;
        TargetSpeed_RB = 0;
        
        Motor_Mecanum_LA_Brake();

        PWM_LB = Speed_PID(1,TargetSpeed_LB,-1);
        Motor_Mecanum_LB_Speed(PWM_LB);

        PWM_RA = Speed_PID(2,TargetSpeed_RA,-1);
        Motor_Mecanum_RA_Speed(PWM_RA);

        Motor_Mecanum_RB_Brake();
    }
    

    /*------Turn-------*/
    else if(rc->ch3 < 0 && rc->ch4 == 0) //Left Turn
    {
        TargetSpeed_LA = -Real_MaxSpeed_LA;
        TargetSpeed_LB = -Real_MaxSpeed_LB;
        TargetSpeed_RA = Real_MaxSpeed_RA;
        TargetSpeed_RB = Real_MaxSpeed_RB;
        
        PWM_LA = Speed_PID(0,TargetSpeed_LA,-1);
        Motor_Mecanum_LA_Speed(PWM_LA);

        PWM_LB = Speed_PID(1,TargetSpeed_LB,-1);
        Motor_Mecanum_LB_Speed(PWM_LB);

        PWM_RA = Speed_PID(2,TargetSpeed_RA,1);
        Motor_Mecanum_RA_Speed(PWM_RA);

        PWM_RB = Speed_PID(3,TargetSpeed_RB,1);
        Motor_Mecanum_RB_Speed(PWM_RB);
    }

    else if(rc->ch3 > 0 && rc->ch4 == 0) //Right Turn
    {
        TargetSpeed_LA = Real_MaxSpeed_LA;
        TargetSpeed_LB = Real_MaxSpeed_LB;
        TargetSpeed_RA = -Real_MaxSpeed_RA;
        TargetSpeed_RB = -Real_MaxSpeed_RB;
        
        PWM_LA = Speed_PID(0,TargetSpeed_LA,1);
        Motor_Mecanum_LA_Speed(PWM_LA);

        PWM_LB = Speed_PID(1,TargetSpeed_LB,1);
        Motor_Mecanum_LB_Speed(PWM_LB);

        PWM_RA = Speed_PID(2,TargetSpeed_RA,-1);
        Motor_Mecanum_RA_Speed(PWM_RA);

        PWM_RB = Speed_PID(3,TargetSpeed_RB,-1);
        Motor_Mecanum_RB_Speed(PWM_RB);
    }

    /*------Brake-------*/
    else Brake_All();
    
}
