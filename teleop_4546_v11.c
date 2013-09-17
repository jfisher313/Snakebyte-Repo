#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     left,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     unused,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     right,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     unused,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

/* Change log
16 9 2013 Jonathan - Program created
17 9 2012 Jonathan - *Added seperate tasks for left and right drive control
										 *Added basic drive controls - left stick = left motor & right stick = right motor
										 *Note - controllers have inverted y values
*/
task driveL() {
	while(true) {

		getJoystickSettings(joystick);

		if(joystick.joy1_y1 < -25) {
			motor[left] = 100;
		}
		else {
			motor[left] = 0;
		}

		if(joystick.joy1_y1 > 25) {
			motor[left] = -100;
		}
		else {
			motor[left] = 0;
		}
		wait1Msec(5);
	}
}



task driveR() {
	while(true) {

		getJoystickSettings(joystick);

		if(joystick.joy1_y2 < -25) {
			motor[right] = 100;
		}
		else {
			motor[right] = 0;
		}

		if(joystick.joy1_y2 > 25) {
			motor[right] = -100;
		}
		else {
			motor[left] = 0;
		}

		wait1Msec(5);
	}
}



task main() {
	waitForStart();
	StartTask (driveL);
	StartTask (driveR);
	while(true){}

}
