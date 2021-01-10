#include "user_common.h"
#include "buffer.h"


#define CAN_STATUS_MSGS_TO_STORE 10

//-------下列为控制指令枚举-------//
typedef enum {
CAN_PACKET_SET_DUTY = 0,
CAN_PACKET_SET_CURRENT,
CAN_PACKET_SET_CURRENT_BRAKE,
CAN_PACKET_SET_RPM,
CAN_PACKET_SET_POS,
CAN_PACKET_FILL_RX_BUFFER,
CAN_PACKET_FILL_RX_BUFFER_LONG,
CAN_PACKET_PROCESS_RX_BUFFER,
CAN_PACKET_PROCESS_SHORT_BUFFER,
CAN_PACKET_STATUS,
CAN_PACKET_SET_CURRENT_REL,
CAN_PACKET_SET_CURRENT_BRAKE_REL,
CAN_PACKET_SET_CURRENT_HANDBRAKE,
CAN_PACKET_SET_CURRENT_HANDBRAKE_REL,
CAN_PACKET_STATUS_2,
CAN_PACKET_STATUS_3,
CAN_PACKET_STATUS_4,
CAN_PACKET_PING,
CAN_PACKET_PONG,
CAN_PACKET_DETECT_APPLY_ALL_FOC,
CAN_PACKET_DETECT_APPLY_ALL_FOC_RES,
CAN_PACKET_CONF_CURRENT_LIMITS,
CAN_PACKET_CONF_STORE_CURRENT_LIMITS,
CAN_PACKET_CONF_CURRENT_LIMITS_IN,
CAN_PACKET_CONF_STORE_CURRENT_LIMITS_IN,
CAN_PACKET_CONF_FOC_ERPMS,
CAN_PACKET_CONF_STORE_FOC_ERPMS,
CAN_PACKET_STATUS_5
} CAN_PACKET_ID;


//---------结构体---------//////
typedef struct {
int id;
uint32_t rx_time;
float rpm;
float current;
float duty;
} can_status_msg;


typedef struct {
	int id;
	int rx_time;
	float amp_hours;
	float amp_hours_charged;
} can_status_msg_2;



typedef struct {
int id;
uint32_t rx_time;
float watt_hours;
float watt_hours_charged;
} can_status_msg_3;

typedef struct {
int id;
uint32_t rx_time;
float temp_fet;
float temp_motor;
float current_in;
float pid_pos_now;
} can_status_msg_4;

typedef struct {
int id;
uint32_t rx_time;
float v_in;
int32_t tacho_value;
} can_status_msg_5;


typedef struct{
 uint8_t  Data[8];
	
CAN_TxHeaderTypeDef TxMessageHeader;
} CANTx_msg ;



void comm_can_get_values(uint8_t controller_id);
void vesc_can_set_current(uint8_t controller_id, float current) ;
void vesc_can_set_duty(uint8_t controller_id, float duty);
void common_can_transmit(uint32_t id, uint8_t *data,uint8_t len);
void comm_can_state_process(CAN_RxTypedef RxMessage);

