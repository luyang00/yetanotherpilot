#include "config.h"

float stablize_Kp = 5;
int LOG_LEVEL = LOG_SDCARD;

float pid_quad_altitude[4]=			// P, I, D, IMAX, 
									// unit: 1/second, 1/seconds^2, 1, meter*second
									// convert altitude error(meter) to target climb rate(meter/second)
{
	1, 0, 0, 0,
};
float pid_quad_alt_rate[4]=			// P, I, D, IMAX
									// unit: 1/second, 1/seconds^2, 1, meter*second
									// convert climb rate error(meter/second) to target acceleration(meter/second^2)
{
	6, 0, 0, 0,
};
float pid_quad_accel[4]=			// P, I, D, IMAX
									// unit: 1/second, 1/seconds^2, 1, meter*second
									// convert acceleration error(meter/second^2) to motor output
									// In ardupilot, default P = 0.75 converts 1 cm/s^2 into 0.75 * 0.1% of full throttle
									// the max accel error in default value is around +- 6.66 m/s^2, but should not use that much
{
	75,
	150,
	0,
	0.05,
};


#if QUADCOPTER == 1

float pid_limit[3][3] = 				// pid_limit[roll,pitch,yaw][p max offset, I limit, d dummy]
{
	{PI, PI/3.6, 1},
	{PI, PI/3.6, 1},
	{PI/2, PI/3.6, 1},
};
float pid_factor[3][3] = 			// pid_factor[roll,pitch,yaw][p,i,d]
{
	{0.35, 0.70, 0.035,},
	{0.35, 0.70, 0.035,},
	{1.75, 0.25, 0,},
};
float pid_factor2[3][3] = 			// pid_factor2[roll,pitch,yaw][p,i,d]
{
	{5, 0, 0.03,},
	{5, 0, 0.03,},
	{5, 0, 0.03,},
};
float quadcopter_trim[3]
= 
{
	-0 * PI / 180,			// roll
	-0 * PI / 180,			// pitch
	0,							// yaw
};

#else

float pid_limit[3][3] = 				// pid_limit[roll,pitch,yaw][p max offset, I limit, d dummy]
{
	{PI/4, PI/2, 1},
	{PI/4, PI/2, 1},
	{PI/6, PI/3, 1},
};


float pid_factor[3][3] = 			// pid_factor[roll,pitch,yaw][p,i,d]
{
	{1.50, 0.05, 0.36,},
	{1.50, 0.05, 0.36,},
	//{0, 0.0, 20,},
	//{0, 0.0, 20,},
	{0, 0, 0,},
};

float pid_factor2[3][3] = 				// pid_limit[roll,pitch,yaw][p max offset, I limit, d dummy]
{
	0, 			// we dont need it in fixed wing!
};

#endif