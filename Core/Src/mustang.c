/*
 * mustang.c
 *
 *  Created on: Jan 9, 2024
 *      Author: Bartlomiej Ufnalski
 *
 * Sources:
 *   https://github.com/v-ivanyshyn/parse_can_logs/blob/master/Ford%20CAN%20IDs%20Summary.md
 *   https://github.com/EricTurner3/s550-canbus/wiki/Getting-Started
 *
 */
#include "mustang.h"
#include "fdcan.h"

extern volatile uint8_t up_button_flag;
extern volatile uint8_t down_button_flag;
extern volatile uint8_t left_button_flag;
extern volatile uint8_t right_button_flag;
extern volatile uint8_t mid_button_flag;
extern volatile uint8_t set_button_flag;
extern volatile uint8_t reset_button_flag;

extern FDCAN_TxHeaderTypeDef TxHeader;
extern uint8_t TxData8[8];

#ifdef GR3T
#define HOLD_ON_REPS 40
#endif
#ifdef FR33
#define HOLD_ON_REPS 80
#endif
#ifdef JR3T
#define HOLD_ON_REPS 80
#endif

// X12 2016 Ford Mustang Base | Coupe | 3.7L | RWD | Automat

// -------------------------------------------------------------------- 0x4C (76) ----------------------
void send_seatbelt(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x4C;  // 76 DEC
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x80; // airbag
	TxData8[1] = 0xAF;
	TxData8[2] = 0;
	TxData8[3] = 0;
	TxData8[4] = 0;
	TxData8[5] = 0;
	TxData8[6] = 0;
	TxData8[7] = 0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// -------------------------------------------------------------------- 0x81 (129) ----------------------
void navigate_menu(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x81; // 129 DEC
	memset(TxData8, 0, sizeof(TxData8));

	if (up_button_flag == 1)
	{
		up_button_flag = 0;
		TxData8[0] = 0x08;
	}
	else if (down_button_flag == 1)
	{
		down_button_flag = 0;
		TxData8[0] = 0x01;
	}
	else if (left_button_flag == 1)
	{
		left_button_flag = 0;
		TxData8[0] = 0x02;
	}
	else if (right_button_flag == 1)
	{
		right_button_flag = 0;
		TxData8[0] = 0x04;
	}
	else if (set_button_flag == 1)
	{
		set_button_flag = 0;
		TxData8[0] = 0x10;
	}
	else if (reset_button_flag == 1)
	{
		reset_button_flag = 0;
		TxData8[0] = 0x10;
		for (uint8_t i = 0; i < HOLD_ON_REPS; i++)
		{
			if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8)
					!= HAL_OK)
			{
				Error_Handler();
			}
			HAL_Delay(25);
		}
	}
	else
	{
		TxData8[0] = 0;
	}
	TxData8[1] = 0;
	TxData8[2] = 0;
	TxData8[3] = 0;
	TxData8[4] = 0;
	TxData8[5] = 0;
	TxData8[6] = 0;
	TxData8[7] = 0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// -------------------------------------------------------------------- 0x156 (342) ----------------------
void send_coolant_and_oil_temp(uint8_t coolant_temp, uint8_t oil_temp,
		uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x156; // 342 DEC
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = coolant_temp + 60; // [degC]
	TxData8[1] = oil_temp + 60; // [degC]
	TxData8[2] = 0;
	TxData8[3] = 0;
	TxData8[4] = 0x03; // activates gauge
	TxData8[5] = 0;
	TxData8[6] = 0;
	TxData8[7] = 0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// -------------------------------------------------------------------- 0x171 (369) ----------------------
void send_gearbox_mode(uint8_t gearbox_mode, uint8_t gear_number,
		uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x171;  // 369 DEC
	memset(TxData8, 0, sizeof(TxData8));
	if ((gearbox_mode == 'P') || (gearbox_mode == 'N'))
	{
		TxData8[0] = 20;
	}
	else
	{
		switch (gear_number)
		{
		case 1:
			TxData8[0] = 36;
			break;
		case 2:
			TxData8[0] = 52;
			break;
		case 3:
			TxData8[0] = 68;
			break;
		case 4:
			TxData8[0] = 84;
			break;
		case 5:
			TxData8[0] = 100;
			break;
		default:
			;
		}
	}
	switch (gearbox_mode)
	{
	case 'P':
		TxData8[1] = 0;
		break;
	case 'R':
		TxData8[1] = 32;
		break;
	case 'N':
		TxData8[1] = 64;
		break;
	case 'D':
		TxData8[1] = 96;
		break;
	case 'S':
		TxData8[1] = 128;
		break;
	default:
		;
	}
	TxData8[2] = 0;
	TxData8[3] = 0;
	TxData8[4] = 0;
	TxData8[5] = 0;
	TxData8[6] = 0;
	TxData8[7] = 0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// -------------------------------------------------------------------- 0x178 (376) ----------------------
void send_launch_control(uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x178;  // 376 DEC
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0x20;
	TxData8[1] = 0;
	TxData8[2] = 0;
	TxData8[3] = 0;
	TxData8[4] = 0;
	TxData8[5] = 0;
	TxData8[6] = 0;
	TxData8[7] = 0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// -------------------------------------------------------------------- 0x202 (514) ----------------------
void send_ground_speed(uint16_t vehicle_speed, uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x202;  // 514 DEC
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0;
	TxData8[1] = 0;
	TxData8[2] = 0;
	TxData8[3] = 0;
	TxData8[4] = 0x60; // activates gauge
	TxData8[5] = 0;
	TxData8[6] = (uint8_t) ((vehicle_speed * 175) >> 8); // [km/h]
	TxData8[7] = (uint8_t) (vehicle_speed * 175);
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// -------------------------------------------------------------------- 0x204 (516) ----------------------
void send_engine_speed(uint16_t engine_speed, uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x204; // 516 DEC
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0;
	TxData8[1] = 0;
	TxData8[2] = 0;
	TxData8[3] = (uint8_t) ((engine_speed / 2) >> 8); // [rpm]
	TxData8[4] = (uint8_t) (engine_speed / 2);
	TxData8[5] = 0;
	TxData8[6] = 0;
	TxData8[7] = 0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// -------------------------------------------------------------------- 0x3B2 (946) ----------------------
void activate_cluster(uint8_t left_turn_indicator, uint8_t right_turn_indicator,
		uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
#ifdef GR3T
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x3B2;  // 946 DEC
	TxData8[0] = 0x40; // activates cluster
	TxData8[1] = 0;
	TxData8[2] = 0;
	TxData8[3] = 0x0B; // backlight: 0x0B - night mode, 0x10 - day mode
	TxData8[4] = 0b00010000 /* Track AppsTM */ | (0b00001000 * (1 == right_turn_indicator));
	TxData8[5] = 0; // 0 - instruments cluster backlight in day mode, 5 - instruments cluster backlight in night mode
	TxData8[6] = 0 | (0b01000000 * (1 == left_turn_indicator));
	TxData8[7] = 0x02;
#endif
#ifdef FR33
	TxHeader.Identifier = 0x3B3;  // 947 DEC
	TxData8[0] = 0x40; // activates cluster
	TxData8[1] = 0;
	TxData8[2] = 0;
	TxData8[3] = 0x0B; // backlight: 0x0B - night mode, 0x10 - day mode
	TxData8[4] = 0;
	TxData8[5] = 0;
	TxData8[6] = 0;
	TxData8[7] = 0;
#endif
#ifdef JR3T
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x3B2;  // 946 DEC
	TxData8[0] = 0x40; // activates cluster
	TxData8[1] = 0;
	TxData8[2] = 0;
	TxData8[3] = 0x0B; // backlight: 0x0B - night mode, 0x10 - day mode
	TxData8[4] = 0b00010000 /* Track AppsTM */
	| (0b00001000 * (1 == right_turn_indicator));
	TxData8[5] = 5; // 0 - instruments cluster backlight in day mode, 5 - instruments cluster backlight in night mode
	TxData8[6] = 0 | (0b01000000 * (1 == left_turn_indicator));
	TxData8[7] = 0x02;
#endif
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}

#ifdef FR33
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
		TxHeader.Identifier = 0x3B2;  // 946 DEC
		TxData8[0] = 0;
		TxData8[1] = 0;
		TxData8[2] = 0;
		TxData8[3] = 0;
		TxData8[4] = 0b00010000 /* Track AppsTM */ | (0b00001000 * (1 == right_turn_indicator));
		TxData8[5] = 0; // 0 - instruments cluster backlight in day mode, 5 - instruments cluster backlight in night mode
		TxData8[6] = 0 | (0b01000000 * (1 == left_turn_indicator));
		TxData8[7] = 0x02;

		if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
			{
				Error_Handler();
			}
#endif
}

// -------------------------------------------------------------------- 0x3B5 (949) ----------------------
void send_tyre_pressure(uint8_t tyre1_pressure, uint8_t tyre2_pressure,
		uint8_t tyre3_pressure, uint8_t tyre4_pressure,
		uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x3B5;  // 949 DEC
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0;
	TxData8[1] = tyre1_pressure; // [kPa]
	TxData8[2] = 0;
	TxData8[3] = tyre2_pressure;
	TxData8[4] = 0;
	TxData8[5] = tyre3_pressure;
	TxData8[6] = 0;
	TxData8[7] = tyre4_pressure;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// -------------------------------------------------------------------- 0x421 (1057) ----------------------
void send_oil_pressure(uint8_t oil_pressure, uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x421; // 1057 DEC
	memset(TxData8, 0, sizeof(TxData8));
	// one of the bytes sends oil pressure warning
	TxData8[0] = 0;
	TxData8[1] = 0;
	TxData8[2] = 0;
	TxData8[3] = 0;
	TxData8[4] = 0;
	TxData8[5] = 0;
	TxData8[6] = 0;
	TxData8[7] = 0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// -------------------------------------------------------------------- 0x42D (1069) ----------------------
void send_inlet_air_temp(uint16_t inlet_air_temp, uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x42D; // 1069 DEC
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0;
	TxData8[1] = (uint8_t) (((inlet_air_temp * 4) - 512) >> 8);
	TxData8[2] = (uint8_t) ((inlet_air_temp * 4) - 512);
	TxData8[3] = 0;
	TxData8[4] = 0;
	TxData8[5] = 0;
	TxData8[6] = 0;
	TxData8[7] = 0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// -------------------------------------------------------------------- 0x43E (1086) ----------------------
void send_cylinder_head_temp(uint8_t cylinder_head_temp, int16_t boost_in_mmhg,
		uint8_t air_fuel_ratio, uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x43E; // 1086 DEC
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0;
	TxData8[1] = 0;
	TxData8[2] = 0;
	TxData8[3] = air_fuel_ratio * 10;
	TxData8[4] = cylinder_head_temp + 60;
	TxData8[5] = (uint8_t) (boost_in_mmhg / 25 + 66); // vacuum/boost, 1 bar = 750 mmHg, different formula for vacuum?
	TxData8[6] = 0; //
	TxData8[7] = 0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

// -------------------------------------------------------------------- 0x470 (1136) ----------------------
void send_transmission_oil_temp(uint8_t trans_oil_temp,
		uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x470;  // 1136 DEC
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0;
	TxData8[1] = 0;
	TxData8[2] = 0xFF; // activates readings
	TxData8[3] = trans_oil_temp + 60;
	TxData8[4] = 0;
	TxData8[5] = 0;
	TxData8[6] = 0;
	TxData8[7] = 0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

void send_add_25m_to_odometer(uint8_t flip_me, uint32_t delay_before_send)
{
	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x179;  // 377 DEC
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0;
	TxData8[1] = 0;
	TxData8[2] = 0;
	TxData8[3] = 0;
	TxData8[4] = 0;
	TxData8[5] = flip_me;
	TxData8[6] = 0;
	TxData8[7] = 0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}

void send_accelerometer(double accel_x, double accel_y,
		uint32_t delay_before_send)
{
	if (accel_x > 1.5)
	{
		accel_x = 1.5;
	}
	else if (accel_x < -1.5)
	{
		accel_x = -1.5;
	}

	if (accel_y > 1.5)
	{
		accel_y = 1.5;
	}
	else if (accel_y < -1.5)
	{
		accel_y = -1.5;
	}

	HAL_Delay(delay_before_send);
	TxHeader.DataLength = FDCAN_DLC_BYTES_8;
	TxHeader.Identifier = 0x76;  // 118 DEC tested for JR3T
	memset(TxData8, 0, sizeof(TxData8));
	TxData8[0] = 0;
	TxData8[1] = 0;
	uint16_t accel_y_uint16 = 1024 + (int16_t) (accel_y * 512);
	TxData8[2] = 16 + (int8_t) (accel_x * 8);
	TxData8[3] = (uint8_t) (accel_y_uint16 >> 8);
	TxData8[4] = (uint8_t) accel_y_uint16;
	TxData8[5] = 0;
	TxData8[6] = 0;
	TxData8[7] = 0;
	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData8) != HAL_OK)
	{
		Error_Handler();
	}
}
