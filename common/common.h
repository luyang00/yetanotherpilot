#ifndef __COMMON_H__
#define __COMMON_H__

#include <math.h>
#include <stm32f10x_usart.h>
#include "printf.h"

#ifndef WIN32
#include "timer.h"
#else
typedef unsigned char u8;
#endif
#include "config.h"

enum fly_mode
{
	initializing,
	manual,
	acrobatic,
	fly_by_wire,
	quadcopter,
	shutdown,
	rc_fail,
	acrobaticV,
};

static int abs(int x)
{
	return x>0 ? x : -x;
}

static void swap(void *p, int size)
{
	int i;
	u8 *pp = (u8*)p;
	u8 tmp;
	for(i=0; i<size/2; i++)
	{
		tmp = pp[i];
		pp[i] = pp[size-1-i];
		pp[size-1-i] = tmp;
	}
}

static float limit(float v, float low, float high)
{
	if (v < low)
		return low;
	if (v > high)
		return high;
	return v;
}

static float radian_add(float a, float b)
{
	a += b;
	if (a>=PI)
		a -= 2*PI;
	if (a<-PI)
		a += 2*PI;
	
	return a;
}

#ifndef __cplusplus
#define abs fabs
#endif

// a & b : -PI ~ PI
// return a - b
static float radian_sub(float a, float b)
{
	float v1 = a-b;
	float v2 = a+2*PI-b;
	float v3 = a-2*PI-b;
	
	v1 = fabs(v1)>fabs(v2) ? v2 : v1;
	return fabs(v1)>fabs(v3) ? v3 : v1;
}

#endif
