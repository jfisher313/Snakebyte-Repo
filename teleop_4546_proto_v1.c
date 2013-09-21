#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     leftF,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftB,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     rightF,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     rightB,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_1,     conveyor,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     unused,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

/*
21 9 2013 Jonathan - *code created
										 *code compressed into single task
										 *added a convyor belt task
										 *commented out 85 limit until further notice
*/
task drive() {
	while(true) {

		//Get joystick values
		getJoystickSettings(joystick);

		//Define variables
		short y1 = -joystick.joy1_y1;
		short y2 = -joystick.joy1_y2;

		//If statement determines motor movement
		if((15 < (y1 || y2) < 85) || (-15 > (y1 || y2) > -85)) {
			motor[leftF] = y1;
			motor[leftB] = y1;
			motor[rightF] = y2;
			motor[rightB] = y2;
		}

		/*
		//Left wheel threshold
		else if(y1 >= 85) {
			motor[leftF] = 85;
			motor[leftB] = 85;
		}

		//Right wheel threshold
		else if(y2 <= -85) {
			motor[rightF] = -85;
			motor[rightB] = -85;
		}
		*/
		//Motors not moving
		else {
			motor[leftF] = 0;
			motor[leftB] = 0;
			motor[rightF] = 0;
			motor[rightB] = 0;
		}

		//Wait to avoid latency issues
		wait1Msec(5);
	}
}



//Conveyor belt
task conveyor() {
	while(true) {

		//Get joystick values
		getJoystickSettings(joystick);

		//If A is pressed, conveyor moves
		if(joystick.joy2Btn(01) == 1) {
			motor[conveyor] == 50
		}

		//Wait to avoid latency issues
		wait1Msec(5);
	}
}



//Main task
task main()
{
	waitForStart();
	StartTask(drive);
	StartTask(conveyor);
	while(true){}
}
