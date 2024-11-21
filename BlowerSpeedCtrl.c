/*
 * BlowerSpeedCtrl.c
 *
 *  Created on: Sep 26, 2024
 *      Author: YiJie
 */

#include "BlowerSpeedCtrl.h"
#include "DAVE.h"

void runBlowerSpeedCtrl(void *arg){

    static uint8_t inBlowerSpeedCmd;
	static uint8_t inRightTempCmd;
	static uint8_t inLeftTempCmd;


	int32_t CANstatus;

  while(1)
  {
	CANstatus = CAN_NODE_MO_GetStatus(&BcmNode_LMO_01_Config);


	if (CANstatus & XMC_CAN_MO_STATUS_RX_PENDING){
		 CAN_NODE_MO_ClearStatus(&BcmNode_LMO_01_Config, XMC_CAN_MO_RESET_STATUS_RX_PENDING);

         CAN_NODE_MO_Receive(&BcmNode_LMO_01_Config);

       	 inLeftTempCmd = BcmNode_LMO_01_Config.mo_ptr->can_data_byte[4] & 0x3F;
       	 inRightTempCmd = BcmNode_LMO_01_Config.mo_ptr->can_data_byte[5]  & 0x3F;
       	 inBlowerSpeedCmd = BcmNode_LMO_01_Config.mo_ptr->can_data_byte[6] & 0x0F;
       	 inBlowerSpeedCmd &= 0x07;

       	 if(inBlowerSpeedCmd & 0x01){
       		 DIGITAL_IO_SetOutputLow(&LED_0);
       	 }
       		 else{
       			 DIGITAL_IO_SetOutputHigh(&LED_0);
       		 }


       	 if(inBlowerSpeedCmd & 0x02){
       		DIGITAL_IO_SetOutputLow(&LED_1);
       	 }
       		else{
       			 DIGITAL_IO_SetOutputHigh(&LED_1);
       		}


       	 if(inBlowerSpeedCmd & 0x04){
       		 DIGITAL_IO_SetOutputLow(&LED_2);
       	 }
       		 else{
       			 DIGITAL_IO_SetOutputHigh(&LED_2);
       		 }

       	 PWM_SetDutyCycle(&BlowerPWM, inBlowerSpeedCmd * 1400);

    }
  }
  osDelay(100);
}
