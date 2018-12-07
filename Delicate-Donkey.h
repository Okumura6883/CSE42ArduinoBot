#ifndef DELICATE-DONKEY_H
#define DELICATE-DONKEY_H

#include "Gadgetron.h"

static const int LEFT = 0;
static const int UP = 1;
static const int RIGHT = 2;
static const int DOWN = 3;

static const uint8_t PROGMEM
forward1_bmp[] =
{   B00111100,
    B01011010,
    B10011001,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00000000 },
    forward2_bmp[] =
{   B01011010,
    B10011001,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00000000,
    B00111100 },
    forward3_bmp[] =
{   B10011001,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00000000,
    B00111100,
    B01011010 },
    forward4_bmp[] =
{   B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00000000,
    B00111100,
    B01011010,
    B10011001 },
   forward5_bmp[] =
{   B00011000,
    B00011000,
    B00011000,
    B00000000,
    B00111100,
    B01011010,
    B10011001,
    B00011000 },
    forward6_bmp[] =
{   B00011000,
    B00011000,
    B00000000,
    B00111100,
    B01011010,
    B10011001,
    B00011000,
    B00011000 },
    forward7_bmp[] =
{   B00011000,
    B00000000,
    B00111100,
    B01011010,
    B10011001,
    B00011000,
    B00011000,
    B00011000 },
    forward8_bmp[] =
{   B00000000,
    B00111100,
    B01011010,
    B10011001,
    B00011000,
    B00011000,
    B00011000,
    B00011000 },
    spinLeft_bmp[] = 
{
    B00111100,
    B01000010,
    B10000000,
    B10010000,
    B10001000,
    B01111100,
    B00001000,
    B00010000
}, spinRight_bmp[] = 
{
    B00111100,
    B01000010,
    B00000001,
    B00001001,
    B00010001,
    B00111110,
    B00010000,
    B00001000
};

LEDArray display;

#define DRIVE_STBY 8        
#define DRIVE_PWMA 5        
#define DRIVE_AIN1 11        
#define DRIVE_AIN2 12        
#define DRIVE_PWMB 6        
#define DRIVE_BIN1 13        
#define DRIVE_BIN2 A2        
Motor drive(DRIVE_STBY,DRIVE_PWMA,DRIVE_AIN1,DRIVE_AIN2,DRIVE_PWMB,DRIVE_BIN1,DRIVE_BIN2);

#define LED_CONTROL_RED 9        
#define LED_CONTROL_GREEN 10        
#define LED_CONTROL_BLUE 10        
RGBLED led(LED_CONTROL_RED,LED_CONTROL_GREEN,LED_CONTROL_BLUE);

#define BUZZER_1 4        
Buzzer buzzer(BUZZER_1);
Song song(buzzer);

#define SERVO_DATA 3        
ServoMotor Servo(SERVO_DATA);

#define DISTANCESENSOR_A A0        
DistanceSensor distanceSensor(DISTANCESENSOR_A);

#define DISTANCESENSOR_2_A A1        
DistanceSensor distanceSensor_2(DISTANCESENSOR_2_A);


#endif
