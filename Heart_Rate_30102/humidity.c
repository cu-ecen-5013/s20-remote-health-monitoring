/*	File Name: humidity.c
	Description: This file measures humidity value from DHT11 humidity sensor.
	Sensor Interface: GPIO
	Auther: Sankalp Pund
	Refrence: http://wiringpi.com/reference/core-functions/
			  http://wiringpi.com/reference/timing/
			  http://www.uugear.com/portfolio/read-dht1122-temperature-humidity-sensor-from-raspberry-pi/ 				  	 
*/
/*Header files*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <wiringPi.h>

/*Macros*/ 
#define MAX_TIMINGS	50            /*Delay to detect change on GPIO*/
#define HUMIDITY_GPIO_PIN 3	      /* GPIO-22 */
#define BYTE_DATA 8               /*Bit resolution*/
#define MAX_CHECK 255             /*data check counter*/
#define MIN_CHECK 50        	  /*data check counter*/
#define SENSOR_DETECTION_DELAY 18 /*Delay to detect MCU Signals*/
#define WAIT_FOR_RESPONSE 2000    /*wait for 2 sec for sensor response*/
 
/*Buffer to store sensor value*/ 
int humidity_buffer[1] = { 0 };

/*
Function Name: Main()
Description: Measures humidity and setup wiring connection
Input: void
Return: integer
*/
int main( void )
{
	printf( "Started Measuring Humidity sensor\n" );

	int status;
 
	status=wiringPiSetup();
	
	if(status!=-1)
	{
		printf( "wiring setup for Humidity sensor is correct.\n" );
	}
	else
	{
		exit( 1 );
	}	
		
 
	while (true)
	{
		Humidity();

		delay( WAIT_FOR_RESPONSE ); /* wait 2 seconds before next read */
	}
 
	return(0);
}

/*
Function Name: Humidity()
Description: Measures humidity value from sensor.
Input: void
Return: void
*/
 
void Humidity()
{
	uint8_t state_level	= HIGH;
	uint8_t check		= 0;
	uint8_t index2		= 0, index1;
 
	humidity_buffer[0]  = 0;
 
	/* pull pin down for 18 milliseconds */
	pinMode( HUMIDITY_GPIO_PIN, OUTPUT );
	digitalWrite( HUMIDITY_GPIO_PIN, LOW );
	delay( SENSOR_DETECTION_DELAY );
 
	/* prepare to read the pin */
	pinMode( HUMIDITY_GPIO_PIN, INPUT );
 
	/* detect change and read data */
	for ( index1 = 0; index1 < MAX_TIMINGS; index1++ )
	{
		check = 0;
		
		while ( digitalRead( HUMIDITY_GPIO_PIN ) == state_level )
		{
			check++;

			delayMicroseconds( 1 );

			if ( check == MAX_CHECK )
			{
				break;
			}
		}
		
		state_level = digitalRead( HUMIDITY_GPIO_PIN );
 
		if ( check == MAX_CHECK )
		{
			break;
		}

		
		/* ignore first 3 transitions */
		if ( (index1 >= 4) && (index1 % 2 == 0) )
		{
			/* shove each bit into the storage bytes */
			humidity_buffer[index2 / BYTE_DATA] <<= 1;
			if ( check > MIN_CHECK )
			humidity_buffer[index2 / BYTE_DATA] |= 1;
			index2++;
		}
	}
	printf("Humidity of ICU = %.1d% \n", humidity_buffer[0]);
}
 
