#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     leftB,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     leftF,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     conveyorL,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     flagLifter,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     conveyorR,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     tumbler,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     rightB,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     rightF,        tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S2_C1_1,    bucketdropL,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    bucketdropR,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    flagL,                tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    flagR,                tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

/*
21 09 2013 Jonathan - *code created
										  *code compressed into single task
										  *added a convyor belt task
										  *commented out 85 limit until further notice
										  *added second conveyor belt motor
										  *commented out conveyor belt task
23 09 2013 Jonathan - *bug fixing
03 10 2013 Jonathan - *changed motor config for new robot
*/

task drive() {
	while(true){

		//Get joystick values
		getJoystickSettings(joystick);

		//Define variables
		short y1 = -joystick.joy1_y1;
		short y2 = -joystick.joy1_y2;

		//If statement determines motor movement
		if ((y2 > -15 && y2 < 15) && (y1 > -15 && y1 < 15)) {
   		motor[rightB] = 0;
   		motor[rightF] = 0;
   		motor[leftB] = 0;
			motor[leftF] = 0;
 		}

		else {
			motor[rightB] = (y2 * .5);
			motor[rightF] = (y2 * .5);
			motor[leftB] = (y1 * .5);
			motor[leftF] = (y1 * .5);
 		}

		//Wait to avoid latency issues
		wait1Msec(5);
	}
}


//Block lift
task lift() {
	while(true) {

		//Get joystick values
		getJoystickSettings(joystick);

		//If A is pressed, conveyor moves
		if(joy2Btn(05) == 1) {						// RB
			motor[conveyorR] = 50;
			motor[conveyorL] = 50;
		}
		else if(joy2Btn(06) == 1) {				// LB
			motor[conveyorR] = -50;
			motor[conveyorL] = -50;
		}
		else{
			motor[conveyorR] = 0;
			motor[conveyorL] = 0;
		}

		//Wait to avoid latency issues
		wait1Msec(5);
	}
}


//chuteServo task
task bucketServo() {
		servo[bucketdropR] = 105;

	while(true)
	{
		getJoystickSettings(joystick);
		if (joy2Btn(02) == 1 && ServoValue[bucketdropR] < 105) {		// Y
		//	servo[bucketdropL] = ServoValue[bucketdropL] -1;
			servo[bucketdropR] = ServoValue[bucketdropR] +10;
		}
		else if (joy2Btn(02) == 1 && joy2Btn(06) == 1)
		{
			//	servo[bucketdropL] = ServoValue[bucketdropL] -1;
			servo[bucketdropR] = ServoValue[bucketdropR] +106;
		}

		if (joy2Btn(01) == 1 ){
		//	servo[bucketdropL] = ServoValue[bucketdropL] +1;				// A
			servo[bucketdropR] = ServoValue[bucketdropR] -1;
		}
	}
}


//move flag task.
task flagLift() {
	while(true){
		getJoystickSettings(joystick);

		if(joy1Btn(3) == 1){					//
			motor[flagLifter] = 75;
		}
		else{
			motor[flagLifter] = 0;
		}
		wait1Msec(5);
	}
}

task flagServos()
{
	servo[flagR] = 127;
	while(true){
		getJoystickSettings(joystick);

		if (joy1Btn(05) == 1) {		// Y
		//	servo[flagL] = ServoValue[flagL] -1;
			servo[flagR] = ServoValue[flagR] +1;
		}

		if (joy1Btn(06) == 1 ){
		//	servo[flagL] = ServoValue[flagL] +1;				// A
			servo[flagR] = ServoValue[flagR] -1;
		}
	}
}

task blockTumbler(){
	while(true){
		getJoystickSettings(joystick);

		if(joy2Btn(03) == 1){					// X
			motor[tumbler] = 30;
		}
		else{
			motor[tumbler] = 0;
		}
	}
}

//Main task
task main()
{
	waitForStart();

	//servo[flagL] = 155;
	//servo[flagR] = 100;


	StartTask(drive);
	StartTask(flagServos);
	StartTask(bucketServo);
	StartTask(lift);
	StartTask(flagLift);
	StartTask(blockTumbler);
	while(true){}
}
