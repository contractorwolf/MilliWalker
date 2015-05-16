/*
MilliWalker v3
added joystick controls for forwards and back





*/




//int led = 13;
int upJoystickPin = 2;
int downJoystickPin = 3;
int rightJoystickPin = 4;
int leftJoystickPin = 5;
int buttonJoystickPin = 6;


bool upPressed = false;
bool downPressed = false;
bool leftPressed = false;
bool rightPressed = false;
bool buttonPressed = false;






int pot1pin = A0;  // analog pin used to connect the potentiometer
//int pot1power = 2;  
int pot2pin = A1;  // analog pin used to connect the potentiometer
//int pot2power = 4; 
//int pot2GND = 3; 




int speed;
int bend;
int bend_angle;

int middle_joint = 1300;


int time_delay = 300;
int centers[] = {1366,1329,1367,1369,1407,1399,1402,1297,1141};//1572,1132

int vertical_sway = 250;
int horizontal_sway = 175;
int bend_sway = 300;



int horizontal_angle;
int vertical_angle;
int reverse_horizontal_angle;
int reverse_vertical_angle;

String incomingCommand = "c";

char character;

/*

FORWARD DIRECTION, max speed ~180
step 1: #1P1541#2P1579#3P1192#4P1119#5P1582#6P1649#7P1227#8P1047T300
step 2: #1P1541#2P1079#3P1192#4P1619#5P1582#6P1149#7P1227#8P1547T300
step 3: #1P1191#2P1079#3P1542#4P1619#5P1232#6P1149#7P1577#8P1547T300
step 4: #1P1191#2P1579#3P1542#4P1119#5P1232#6P1649#7P1577#8P1047T300
*/

void setup()
{
	//pinMode(led, OUTPUT);  
	pinMode(pot1pin, INPUT);  // backbone servos controller
	pinMode(pot2pin, INPUT);  // leg servo controller

	pinMode(upJoystickPin, INPUT);
	pinMode(buttonJoystickPin, INPUT); 
	pinMode(downJoystickPin, INPUT); 
	pinMode(leftJoystickPin, INPUT);
	pinMode(rightJoystickPin, INPUT);

	Serial.begin(115200);// COM7 USB
	Serial1.begin(9600);// USC32 Servo Control Board
  
	Serial.println("MilliWalker v4 Started");

	delay(3000);
}


void loop()
{
	//get joystick values
	upPressed = digitalRead(upJoystickPin);
	downPressed = digitalRead(downJoystickPin);  
	leftPressed = digitalRead(leftJoystickPin);  
	rightPressed = digitalRead(rightJoystickPin);  
	buttonPressed = digitalRead(buttonJoystickPin);  


	//output joystick values to serial monitor
	Serial.print("up: ");
	Serial.print(upPressed);
	Serial.print("  down: ");
	Serial.print(downPressed);  
	Serial.print("  left: ");
	Serial.print(leftPressed);  
	Serial.print("  right: ");
	Serial.print(rightPressed);  
	Serial.print("  button: ");
	Serial.print(buttonPressed);  


	//speed = analogRead(pot1pin);            // reads the value of the potentiometer (value between 0 and 1023) 
	//bend = analogRead(pot2pin);            // reads the value of the potentiometer (value between 0 and 1023) 
	//0-1017 pot values
	//530-2340 max values
	// show analog values
	//Serial.print("	speed value: ");  
	//Serial.print(speed); 
	//Serial.print("  bend value: ");  
	//Serial.println(bend); 
	//SendSingleServoCommand(9, bend, 300);
	//bend_angle = map(bend, 0, 1023, 600, 2000); //horizontal_angle


	//change turn angle, defaults to straight
	if(rightPressed){
		bend_angle = centers[8] + bend_sway;
	}else if(leftPressed){
		bend_angle = centers[8] - bend_sway;
	}else{
		bend_angle = centers[8];
	}

	//change speed based on button being pressed
	if(buttonPressed){
		speed = 250;	
	}else{
		speed = 350;	
	}

	//get commands from serial monitor
	while(Serial.available()) {
		incomingCommand = "";
		character = Serial.read();
		incomingCommand.concat(character);
	}


	if (incomingCommand == "w"||upPressed) {
		//forward all steps
		SendServoCommandList(1191,1579,1542,1119,1232,1149,1577,1547,bend_angle,speed);//step 4
		SendServoCommandList(1191,1079,1542,1619,1232,1649,1577,1047,bend_angle,speed);//step 3
		SendServoCommandList(1541,1079,1192,1619,1582,1649,1227,1047,bend_angle,speed);//step 2
		SendServoCommandList(1541,1579,1192,1119,1582,1149,1227,1547,bend_angle,speed);//step 1
	}else if (incomingCommand == "r"||downPressed) {
		//send 4 step movements, walks in opposite direction
		//reverse walking, 4 steps                    leg       leg
		SendServoCommandList(1541,1579,1192,1119,1582,1149,1227,1547,bend_angle,speed);//step 1
		SendServoCommandList(1541,1079,1192,1619,1582,1649,1227,1047,bend_angle,speed);//step 2
		SendServoCommandList(1191,1079,1542,1619,1232,1649,1577,1047,bend_angle,speed);//step 3
		SendServoCommandList(1191,1579,1542,1119,1232,1149,1577,1547,bend_angle,speed);//step 4
	}else if (incomingCommand == "c"||(!downPressed && !downPressed)) {
		//center all joints
		//center all servos
		SendServoCommandList(centers[0],centers[1],centers[2],centers[3],centers[4],centers[5],centers[6],centers[7],bend_angle,speed);
	}else if (incomingCommand == "1") {
		//first step, all servos
		SendServoCommandList(1541,1579,1192,1119,1582,1149,1227,1547,bend_angle,speed);//step 1

	}else if (incomingCommand == "2") {
		//second step, all servos
		SendServoCommandList(1541,1079,1192,1619,1582,1649,1227,1147,bend_angle,speed);//step 2

	}else if (incomingCommand == "3") {
		//third step, all servos
		SendServoCommandList(1191,1079,1542,1619,1232,1649,1577,1147,bend_angle,speed);//step 3
	}else if (incomingCommand == "4") {
		//fourth step, all servos
		SendServoCommandList(1191,1579,1542,1119,1232,1149,1577,1547,bend_angle,speed);//step 4
	}else if (incomingCommand != "") {
		//defaults to center
		//center all servos
		SendServoCommandList(centers[0],centers[1],centers[2],centers[3],centers[4],centers[5],centers[6],centers[7],bend_angle,speed);
	}


	//delay(100);
}


void SendServoCommandList(int servo0,int servo1,int servo2,int servo3,int servo4,int servo5,int servo6,int servo7,int servo8,int time_delay){

	//send to USC32 servo
	Serial1.print("#1P");
	Serial1.print(servo0);
	Serial1.print("#2P");
	Serial1.print(servo1);
	Serial1.print("#3P");
	Serial1.print(servo2);
	Serial1.print("#4P");
	Serial1.print(servo3);
	Serial1.print("#5P");
	Serial1.print(servo4);
	Serial1.print("#6P");
	Serial1.print(servo5);
	Serial1.print("#7P");
	Serial1.print(servo6);
	Serial1.print("#8P");
	Serial1.print(servo7);

	Serial1.print("#9P");
	Serial1.print(servo8);
	Serial1.print("T");
	Serial1.println(time_delay);

	//output to USB
	Serial.print("#1P");
	Serial.print(servo0);
	Serial.print("#2P");
	Serial.print(servo1);
	Serial.print("#3P");
	Serial.print(servo2);
	Serial.print("#4P");
	Serial.print(servo3);
	Serial.print("#5P");
	Serial.print(servo4);
	Serial.print("#6P");
	Serial.print(servo5);
	Serial.print("#7P");
	Serial.print(servo6);
	Serial.print("#8P");
	Serial.print(servo7);

	Serial.print("#9P");
	Serial.print(servo8);


	Serial.print("T");
	Serial.println(time_delay);

	delay(time_delay); 
}


//for walk testing only
void SendServoCommand(int pot_angle, int pot_angle2, int time_delay){

	//first segment responding to potentiometers
	int servo0 = map(pot_angle, 0, 1023, centers[0] + horizontal_sway, centers[0] - horizontal_sway); //horizontal_angle
	int servo1 = map(pot_angle2,0, 1023, centers[1] + vertical_sway, centers[1] - vertical_sway); //vertical_angle


	int servo2 = map(pot_angle, 0, 1023, centers[2] - horizontal_sway, centers[2] + horizontal_sway); //reverse_horizontal_angle
	int servo3 = map(pot_angle2,0, 1023, centers[3] - vertical_sway, centers[3] + vertical_sway); //reverse_vertical_angle

	int servo4 = map(pot_angle, 0, 1023, centers[4] + horizontal_sway, centers[4] - horizontal_sway); //horizontal_angle
	int servo5 = map(pot_angle2,0, 1023, centers[5] + vertical_sway, centers[5] - vertical_sway); //vertical_angle


	int servo6 = map(pot_angle, 0, 1023, centers[6] - horizontal_sway, centers[6] + horizontal_sway); //reverse_horizontal_angle
	int servo7 = map(pot_angle2,0, 1023, centers[7] - vertical_sway, centers[7] + vertical_sway); //reverse_vertical_angle

	//send to USC32 servo
	Serial1.print("#1P");
	Serial1.print(servo0);
	Serial1.print("#2P");
	Serial1.print(servo1);
	Serial1.print("#3P");
	Serial1.print(servo2);
	Serial1.print("#4P");
	Serial1.print(servo3);
	Serial1.print("#5P");
	Serial1.print(servo4);
	Serial1.print("#6P");
	Serial1.print(servo5);
	Serial1.print("#7P");
	Serial1.print(servo6);
	Serial1.print("#8P");
	Serial1.print(servo7);
	Serial1.print("T");
	Serial1.println(time_delay);

	//output to USB
	Serial.print("#1P");
	Serial.print(servo0);
	Serial.print("#2P");
	Serial.print(servo1);
	Serial.print("#3P");
	Serial.print(servo2);
	Serial.print("#4P");
	Serial.print(servo3);
	Serial.print("#5P");
	Serial.print(servo4);
	Serial.print("#6P");
	Serial.print(servo5);
	Serial.print("#7P");
	Serial.print(servo6);
	Serial.print("#8P");
	Serial.print(servo7);
	Serial.print("T");
	Serial.println(time_delay);

	delay(time_delay); 
}


//for testing sending a single value
void SendSingleServoCommand(int servo, int pot_angle, int time_delay){

	//first segment responding to potentiometers
	int servo_angle = map(pot_angle, 0, 1023, 600, 2000); //horizontal_angle

	//send to USC32 servo
	Serial1.print("#");
	Serial1.print(servo);
	Serial1.print("P");
	Serial1.print(servo_angle);
	Serial1.print("T");
	Serial1.println(time_delay);

	
	//send to USC32 servo
	Serial.print("#");
	Serial.print(servo);
	Serial.print("P");
	Serial.print(servo_angle);
	Serial.print("T");
	Serial.println(time_delay);

}
