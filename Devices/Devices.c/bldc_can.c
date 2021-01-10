#include "bldc_can.h"

void vesc_can_set_duty(uint8_t controller_id, float duty) {
int32_t send_index = 0;
uint8_t buffer[4];
buffer_append_int32(buffer, (int32_t)(duty * 100000.0f), &send_index);//数据类型转换
common_can_transmit(controller_id | ((uint32_t)CAN_PACKET_SET_DUTY << 8),buffer, send_index);//通过CAN发送
                                                  	            //前半部分是被控制驱动的ID号，后半部分是枚举类型中的命令。

}



void vesc_can_set_current(uint8_t controller_id, float current) {
	int32_t send_index = 0;
	uint8_t buffer[4];
	buffer_append_int32(buffer, (int32_t)(current * 1000.0), &send_index);
	common_can_transmit(controller_id |
			((uint32_t)CAN_PACKET_SET_CURRENT << 8), buffer, send_index);
}



void common_can_transmit(uint32_t id, uint8_t *data,uint8_t len)  
{	  
	CANTx_msg BLDC_TxMessage;
	
	
	if(len > 8){
	   len = 8;
	}
	
	BLDC_TxMessage.TxMessageHeader.ExtId = id;;					 
	BLDC_TxMessage.TxMessageHeader.IDE = CAN_ID_EXT;  //ID类型
	BLDC_TxMessage.TxMessageHeader.RTR = CAN_RTR_DATA;				 //发送的为数据
	BLDC_TxMessage.TxMessageHeader.DLC = len;						 //数据长度为8字节
	BLDC_TxMessage.TxMessageHeader.TransmitGlobalTime = DISABLE;
	memcpy(BLDC_TxMessage.Data, data, len);//从CANTxFrame中复制数据
	HAL_CAN_AddTxMessage(&hcan1,&BLDC_TxMessage.TxMessageHeader,data,(uint32_t*)CAN_TX_MAILBOX0);
	
}




uint8_t  id ;
can_status_msg   stat_msg[CAN_STATUS_MSGS_TO_STORE]; //结构体指针
can_status_msg_2 stat_msg_2[CAN_STATUS_MSGS_TO_STORE];
can_status_msg_3 stat_msg_3[CAN_STATUS_MSGS_TO_STORE];
can_status_msg_4 stat_msg_4[CAN_STATUS_MSGS_TO_STORE];
can_status_msg_5 stat_msg_5[CAN_STATUS_MSGS_TO_STORE];





CAN_PACKET_ID  cmd ;
void comm_can_state_process(CAN_RxTypedef RxMessage)
{
    uint8_t i;
		int ind;
	
 id = (RxMessage.CAN_RxHeader.ExtId & 0xFF); //截取ID
	
 cmd = (RxMessage.CAN_RxHeader.ExtId >>8);; //命令  //截取命令
        switch (cmd)	{ //cmd判断				
 case CAN_PACKET_SET_DUTY:
        ind = 0;
        break;
 
      case CAN_PACKET_SET_CURRENT:
        ind = 0;

        break;

      case CAN_PACKET_SET_CURRENT_BRAKE:
        ind = 0;
        break;

      case CAN_PACKET_SET_RPM:
        ind = 0;
        break;

      case CAN_PACKET_SET_POS:
        ind = 0;
        break;
			case CAN_PACKET_STATUS:
				for (i = 0; i < 10; i++) 
				{
					can_status_msg *stat_tmp = &stat_msg[i];
					ind = 0;
					stat_tmp->id = id; //id存取
					stat_tmp->rx_time = 0;//rx_time 存取
					stat_tmp->rpm = (float)buffer_get_int32(RxMessage.CAN_RxMessage, &ind); //转速
					stat_tmp->current = (float)buffer_get_int16(RxMessage.CAN_RxMessage, &ind) / 10.0f; //电流
					stat_tmp->duty = (float)buffer_get_int16(RxMessage.CAN_RxMessage, &ind) / 1000.0f; //占空比
				}
			break;

	case CAN_PACKET_STATUS_2:
			for ( i = 0;i < CAN_STATUS_MSGS_TO_STORE;i++) {
			can_status_msg_2  *stat_tmp_2 = &stat_msg_2[i];
			ind = 0;
			stat_tmp_2->id = id;
			stat_tmp_2->rx_time = 0;
			stat_tmp_2->amp_hours = (float)buffer_get_int32(RxMessage.CAN_RxMessage, &ind) / 1e4;
			stat_tmp_2->amp_hours_charged = (float)buffer_get_int32(RxMessage.CAN_RxMessage, &ind) / 1e4;
			}
			break;
  case CAN_PACKET_STATUS_3:
		for ( i = 0;i < CAN_STATUS_MSGS_TO_STORE;i++) {
		can_status_msg_3 *stat_tmp_3 = &stat_msg_3[i];
		ind = 0;
		stat_tmp_3->id = id;
		stat_tmp_3->rx_time = 0;
		stat_tmp_3->watt_hours = (float)
		buffer_get_int32(RxMessage.CAN_RxMessage, &ind) / 1e4;
		stat_tmp_3->watt_hours_charged = (float)
		buffer_get_int32(RxMessage.CAN_RxMessage, &ind) / 1e4;
		}
		break;
  case CAN_PACKET_STATUS_4:
		for ( i = 0;i < CAN_STATUS_MSGS_TO_STORE;i++) {
		can_status_msg_4 *stat_tmp_4 = &stat_msg_4[i];
		ind = 0;
		stat_tmp_4->id = id;
		stat_tmp_4->rx_time = 0;
		stat_tmp_4->temp_fet = (float)
		buffer_get_int16(RxMessage.CAN_RxMessage, &ind) / 10.0f;
		stat_tmp_4->temp_motor = (float)
		buffer_get_int16(RxMessage.CAN_RxMessage, &ind) / 10.0f;
		stat_tmp_4->current_in = (float)
		buffer_get_int16(RxMessage.CAN_RxMessage, &ind) / 10.0f;
		stat_tmp_4->pid_pos_now = (float)
		buffer_get_int16(RxMessage.CAN_RxMessage, &ind) / 50.0f;
		}
		break;
  case CAN_PACKET_STATUS_5:
		for ( i = 0;i < CAN_STATUS_MSGS_TO_STORE;i++) {
		can_status_msg_5 *stat_tmp_5 = &stat_msg_5[i];
		ind = 0;
		stat_tmp_5->id = id;
		stat_tmp_5->rx_time = 0;
		stat_tmp_5->tacho_value =
		buffer_get_int32(RxMessage.CAN_RxMessage, &ind);
		stat_tmp_5->v_in = (float)
		buffer_get_int16(RxMessage.CAN_RxMessage, &ind) / 1e1;
		}
		 
		break;
		  
	default:
		break;
		 
		}
		 
		}





