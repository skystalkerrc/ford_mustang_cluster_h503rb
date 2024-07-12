/*
 * mustang.h
 *
 *  Created on: Jan 9, 2024
 *      Author: Bartlomiej Ufnalski
 */

#ifndef INC_MUSTANG_H_
#define INC_MUSTANG_H_

#include "main.h"
#include <string.h>

#define GR3T // RGB backlight
//#define FR33 // RGB backlight, no Track AppsTM?
//#define JR3T // no RGB backlight :(

void activate_cluster(uint8_t left_turn_indicator, uint8_t right_turn_indicator, uint32_t delay_before_send);
void navigate_menu(uint32_t delay_before_send);
void send_engine_speed(uint16_t engine_speed, uint32_t delay_before_send);
void send_ground_speed(uint16_t vehicle_speed, uint32_t delay_before_send);
void send_coolant_and_oil_temp(uint8_t coolant_temp, uint8_t oil_temp, uint32_t delay_before_send);
void send_tyre_pressure(uint8_t tyre1_pressure, uint8_t tyre2_pressure, uint8_t tyre3_pressure, uint8_t tyre4_pressure, uint32_t delay_before_send);
void send_transmission_oil_temp(uint8_t trans_oil_temp, uint32_t delay_before_send);
void send_launch_control(uint32_t delay_before_send);
void send_seatbelt(uint32_t delay_before_send);
void send_inlet_air_temp(uint16_t inlet_air_temp, uint32_t delay_before_send);
void send_cylinder_head_temp(uint8_t cylinder_head_temp, int16_t boost_in_mmhg, uint8_t air_fuel_ratio, uint32_t delay_before_send);
void send_oil_temp(uint32_t delay_before_send);
void send_gearbox_mode(uint8_t gearbox_mode, uint8_t gear_number, uint32_t delay_before_send);
void send_oil_pressure(uint8_t oil_pressure, uint32_t delay_before_send);
void send_add_25m_to_odometer(uint8_t flip_me, uint32_t delay_before_send);
void send_accelerometer(double accel_x, double accel_y, uint32_t delay_before_send);

#endif /* INC_MUSTANG_H_ */
