#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     HTSMUX,         sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorBR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorFR,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     conveyorL,     tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     conveyorR,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     lifter,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     flag,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     motorBL,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C4_2,     motorFL,       tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S2_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*====================
VANDEGRIFT VIPERBOTS
Austin, Texas
viperbots.org

CONTRIBUTORS:
Jacob Greenway
Jonathan Fisher
Matt Mitchell
Mikalai Shlapkou
Lillie Hammer
Linnea May
Joshua Johnson

MENTORS:
Jesse Vera

TEAMS IN COLLABORATION:
FTC 6299 & FTC 4546

=====================*/

// Driver References
#include "drivers/hitechnic-sensormux.h";
#include "drivers/hitechnic-accelerometer.h";
#include "drivers/hitechnic-compass.h";

// Multiplexer Sensor Setup
const tMUXSensor HTAC = msensor_S4_1;
const tMUXSensor HTIR = msensor_S4_2;
const tMUXSensor HTMC = msensor_S4_3;

// Acceleration
short xA;
short yA;
short zA;

// Velocity
float xV;

// Displacement
float xD;

// Acceleration variable used for calculations in the x, y, and z direction
float cxA;
float cyA;
float czA;

// Acceleration Offset
float xOffset;

// Turn method variables
short endPos;
short current;

// Timer
short t;

bool reset = false;

// Defining Methods
void resetVariables(){
	reset = true;
	xA = 0;
	yA = 0;
	zA = 0;

	xD = 0;

	xV = 0;

	cxA = 0;
	cyA = 0;
	czA = 0;

	xOffset = 0;

	endPos = 0;
	current = 0;

	t = 0;
	ClearTimer(T1);

	wait10Msec(100);
	//theoretically the timer still runs while the wait is going on
	ClearTimer(T1);
	reset = false;
}

void xMoveTo(float dis){

	resetVariables();
	//do nothing while reset is true
  while(reset){}
	// 6299 Fail Safe: 0.1412
	// 4546 Fail Safe: 0.2016

	// Get first reading of accelerometer and calibrate the x axis
	HTACreadAllAxes(HTAC, xA, yA, zA);
	xOffset = xA * -1;

	wait10Msec(5);

	// Move forward if dis > 0
	if(dis > 0){
		while(xD < dis){
			t = time100(T1);
			motor[motorFL] = 25;
			motor[motorBL] = 25;
			motor[motorFR] = 25;
			motor[motorBR] = 25;
		}
		motor[motorFL] = 0;
		motor[motorBL] = 0;
		motor[motorFR] = 0;
		motor[motorBR] = 0;
	}

	// Move backward if dis < 0
	if(dis < 0){
		while(xD > dis || t < (dis * -1/0.2016)){
			t = time100(T1);
			motor[motorFL] = -25;
			motor[motorBL] = -25;
			motor[motorFR] = -25;
			motor[motorBR] = -25;
		}
		motor[motorFL] = 0;
		motor[motorBL] = 0;
		motor[motorFR] = 0;
		motor[motorBR] = 0;
	}
}

void turn(short deg){

	resetVariables();
	//do nothing while reset is true
  while(reset){}
	if(deg > 0){
		endPos = current + deg;
		if(endPos > 359){
			endPos = endPos - 360;
		}

		if(current > endPos){
			while(current > endPos){
				motor[motorFL] = 25;
				motor[motorBL] = 25;
				motor[motorFR] = -25;
				motor[motorBR] = -25;
			}
			motor[motorFL] = 0;
			motor[motorBL] = 0;
			motor[motorFR] = 0;
			motor[motorBR] = 0;
		}

		if(current < endPos){

			while(current < endPos){
				motor[motorFL] = 25;
				motor[motorBL] = 25;
				motor[motorFR] = -25;
				motor[motorBR] = -25;
			}
			motor[motorFL] = 0;
			motor[motorBL] = 0;
			motor[motorFR] = 0;
			motor[motorBR] = 0;
		}
	}

	if(deg < 0){
		endPos = current + deg;
		if(endPos < 0){
			endPos = endPos + 360;
		}
		if(current < endPos){
			while(current < endPos){
				motor[motorFL] = -25;
				motor[motorBL] = -25;
				motor[motorFR] = 25;
				motor[motorBR] = 25;
			}
			motor[motorFL] = 0;
			motor[motorBL] = 0;
			motor[motorFR] = 0;
			motor[motorBR] = 0;
		}
		if(current > endPos){
			while(current > endPos){
				motor[motorFL] = -25;
				motor[motorBL] = -25;
				motor[motorFR] = 25;
				motor[motorBR] = 25;
			}
			motor[motorFL] = 0;
			motor[motorBL] = 0;
			motor[motorFR] = 0;
			motor[motorBR] = 0;
		}
	}
}


void lift(short sec){

}

void irScan(float irVal){

	// Moves right until the ir seeker is equal to the set value
	if(irVal > 0){
		while(SensorValue[HTIR] != irVal){
			motor[motorFL] = 25;
			motor[motorBL] = -25;
			motor[motorFR] = -25;
			motor[motorBR] = 25;
		}
		motor[motorFL] = 0;
		motor[motorBL] = 0;
		motor[motorFR] = 0;
		motor[motorBR] = 0;
	}

	// Moves left until the ir seeker is equal to the set value
	if(irVal < 0){
		while(SensorValue[HTIR] != irVal * -1){
			motor[motorFL] = -25;
			motor[motorBL] = 25;
			motor[motorFR] = -25;
			motor[motorBR] = 25;
		}
		motor[motorFL] = 0;
		motor[motorBL] = 0;
		motor[motorFR] = 0;
		motor[motorBR] = 0;
	}
}

// Task that takes in all the methods and runs the robot
task autonomous(){

	xMoveTo(.7);
	turn(45);
	xMoveTo(1.1);

	// Move forward, turn right, then scan for the ir beacon

	// No resetVariables in irScan, it will use the data collected to move the rest of the distance
	/*irScan(5);

	// Turn and drop the block into the crate
	turn(-90);

	lift(200);
	// Set servo to dump block
	lift(-200);

	turn(90);

	// Move until the robot reaches the end of the block crates and can go up the ramp
	xMoveTo(1.5);
	turn(-90);
	xMoveTo(0.7);

	// Turn and head up the ramp
	turn(-90);
	xMoveTo(0.7);*/

}

task main(){

	StartTask(autonomous);

	wait10Msec(5);

	// Reads the accelerometer axes and returns 3 values
	while(true){

		current = HTMCreadHeading(HTMC);

		if(!reset){

			// Numbers recieved are 1/200th of 1G
			HTACreadAllAxes(HTAC, xA, yA, zA);

			// Normalize acceleration by the offset in increments of 200ths of a G
			// Acceleration in m/s^2 = acceleration / 9.8
			cxA = (xA + xOffset) / (200 / 9.8);

			// Distance = Velocity * Time + Acceleration * Time^2 all divided by 2
			xD += (.5 * (cxA * .0025) + (xV * .05)) * 2;

			// Solving for and recording velocity in the x direction
			// Acceleration * Time = V
			xV += (cxA * .05);

		}
		wait10Msec(5);
	}
}
