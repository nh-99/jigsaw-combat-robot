#include "Arduino.h"

#include <IBusBM.h>
#include <BTS7960.h>

#include "swervedrive.h"

// Telementry for iBUS
#define IBUS_SENSOR_TYPE_FUEL 0x06

// Stick values for iBUS
#define FULL_SPEED_FORWARDS 2012
#define FULL_SPEED_BACKWARDS 988
#define FULL_SPEED_RIGHT 2012
#define FULL_SPEED_LEFT 988
#define TRUE_CENTER 1500
#define STICK_DEADZONE 10

// Drivetrain motor PWM
#define FLM_L_EN 22
#define FLM_R_EN 23
#define FLM_L_PWM 2
#define FLM_R_PWM 3

#define FRM_L_EN 24
#define FRM_R_EN 25
#define FRM_L_PWM 4
#define FRM_R_PWM 5

#define BLM_L_EN 26
#define BLM_R_EN 27
#define BLM_L_PWM 6
#define BLM_R_PWM 7

#define BRM_L_EN 28
#define BRM_R_EN 29
#define BRM_L_PWM 8
#define BRM_R_PWM 9

/**
 * Controls are:
 * - Movement
 * - Arm up/down
 * - Weapon on/off
 * - Overall arm/disarm
 * - Weapon motor direction
 * 
 * - Curve for throttle - configurable via remote??
 * 
 * 
 * Channel 01 - aileron - Movement right/left
 * Channel 02 - elevon - Movement forward/back
 * Channel 03 - throttle - arm position
 * Channel 04 - rudder - n/a
 * Channel 05 - switch - drivetrain arm/disarm
 * Channel 06 - switch - weapon arm/disarm
 * Channel 07 - right potentiometer - weapon direction
 * Channel 08 - switch 3pos - speed curve (3 choices)
 */

IBusBM IBus; // IBus object

// Motors for swerve drive
BTS7960 frontLeftMotor(FLM_L_EN, FLM_R_EN, FLM_L_PWM, FLM_R_PWM);
BTS7960 frontRightMotor(FRM_L_EN, FRM_R_EN, FRM_L_PWM, FRM_R_PWM);
BTS7960 backLeftMotor(BLM_L_EN, BLM_R_EN, BLM_L_PWM, BLM_R_PWM);
BTS7960 backRightMotor(BRM_L_EN, BRM_R_EN, BRM_L_PWM, BRM_R_PWM);

SwerveDrive swerveDrive(&frontLeftMotor, &frontRightMotor, &backLeftMotor, &backRightMotor);

void setup() {
  Serial.begin(115200);

  // Setup drivetrain motors
  frontLeftMotor.Enable();
  frontRightMotor.Enable();
  backLeftMotor.Enable();
  backRightMotor.Enable();

  IBus.begin(Serial1);    // iBUS connected to Serial1: 19 (RX) and 18 (TX)
  
  // We have to wait for the receiver to receive data from the transmitter (transmitter needs to be turned on)
  // as the channel values all read 0 as long as the transmitter is turned off at boot time.
  // We do not want the car to drive full speed backwards out of control.
  Serial.println("Wait for receiver");
  while (IBus.cnt_rec==0) delay(100);
  Serial.println("Init done");
}

int lastRightLeftMoveVal, lastForwardBackwardMoveVal = 0;

void loop() {
  int rightLeftMoveVal, forwardBackwardMoveVal;

  // Set values for channels
  rightLeftMoveVal = IBus.readChannel(0);
  forwardBackwardMoveVal = IBus.readChannel(1);

  // TODO: Normalize stick values to speed (even with angular stick pattern)
  // TODO: Check stick positions & set drive direction
}