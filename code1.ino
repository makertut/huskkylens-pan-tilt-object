/*!
 * MindPlus
 * uno
 *
 */
#include <DFRobot_Servo.h>
#include <DFRobot_HuskyLens.h>

// Dynamic variables
volatile float mind_n_currentx, mind_n_currenty;
// Create an object
DFRobot_HuskyLens huskylens;
Servo             servo_9;
Servo             servo_10;


// Main program start
void setup() {
	servo_9.attach(9);
	servo_10.attach(10);
	huskylens.writeOSD(String("wating..."), 230, 35);
	huskylens.beginI2CUntilSuccess();
	huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING);
	delay(1000);
	huskylens.writeOSD(String("ok"), 230, 35);
	mind_n_currentx = 40;
	mind_n_currenty = 150;
	servo_9.angle(abs(mind_n_currentx));
	servo_10.angle(abs(mind_n_currenty));
}
void loop() {
	huskylens.request();
	huskylens.writeOSD(String(huskylens.readBlockParameter(1).xCenter), 230, 35);
	if ((huskylens.readBlockParameter(1).xCenter>190)) {
		mind_n_currentx -= 1.5;
		servo_9.angle(abs((constrain(mind_n_currentx, 0, 120))));
	}
	else if (((huskylens.readBlockParameter(1).xCenter>10) && (huskylens.readBlockParameter(1).xCenter<130))) {
		mind_n_currentx += 1.5;
		servo_9.angle(abs((constrain(mind_n_currentx, 0, 120))));
	}
	if ((huskylens.readBlockParameter(1).yCenter>150)) {
		mind_n_currenty += 1.0;
		servo_10.angle(abs((constrain(mind_n_currenty, 0, 120))));
	}
	else if (((huskylens.readBlockParameter(1).yCenter>10) && (huskylens.readBlockParameter(1).yCenter<90))) {
		mind_n_currenty -= 1;
		servo_10.angle(abs((constrain(mind_n_currenty, 0, 120))));
	}
}
