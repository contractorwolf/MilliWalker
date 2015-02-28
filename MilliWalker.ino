
#define CENTER1 1400
#define HIGH1 1100
#define LOW1 1500
#define CENTER2 1400
#define HIGH2 1600
#define LOW2 1200
#define CENTER3 1400
#define HIGH3 1500
#define LOW3 1100
#define CENTER4 1400
#define HIGH4 1600
#define LOW4 1200
#define CENTER5 1400
#define HIGH5 1500
#define LOW5 1200
#define CENTER6 1400
#define HIGH6 1600
#define LOW6 1250
#define CENTER7 1400
#define HIGH7 1500
#define LOW7 1100
#define CENTER8 1400
#define HIGH8 1600
#define LOW8 1200






int led = 13;
String incomingCommand = "c";
char character;



void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);  

  Serial.begin(115200);
  Serial1.begin(9600);
  
  delay(2000);
}

void loop()
{

	
	int time_delay = 300;

	while(Serial.available()) {

		incomingCommand = "";
		character = Serial.read();
		incomingCommand.concat(character);
	}

	if (incomingCommand == "w") {
		//match with all 4 leg sets
		SendFirstCommand(time_delay);
		SendSecondCommand(time_delay);
		SendThirdCommand(time_delay);
		SendFourthCommand(time_delay);
	}else if (incomingCommand == "r") {
		//reverse all, not sure what this will look like
		SendFourthCommand(time_delay);
		SendThirdCommand(time_delay);
		SendSecondCommand(time_delay);		
		SendFirstCommand(time_delay);
	}else if (incomingCommand == "c") {
		SendCenterCommand(time_delay);
	}else if (incomingCommand == "1") {
		//match with all 4 leg sets
		SendServoCommand("#1P1100#2P1200#3P1500#4P1600#5P1200#6P1250#7P1500#8P1530",time_delay);
	}else if (incomingCommand == "2") {
		//match with all 4 leg sets
		SendServoCommand("#1P1500#2P1200#3P1100#4P1600#5P1500#6P1250#7P1100#8P1530",time_delay);
	}else if (incomingCommand == "3") {
		//match with all 4 leg sets
		SendServoCommand("#1P1500#2P1600#3P1100#4P1200#5P1500#6P1600#7P1100#8P1240",time_delay);
	}else if (incomingCommand == "4") {
		//match with all 4 leg sets
		SendServoCommand("#1P1100#2P1600#3P1500#4P1200#5P1200#6P1600#7P1500#8P1240",time_delay);
	}else if (incomingCommand != "") {
		SendCenterCommand(time_delay);
	}










  /* add main program code here */
		//flash led
    digitalWrite(led, HIGH);   
    delay(30);               
    digitalWrite(led, LOW); 
	//delay(100);  
}


void SendCenterCommand(int time_delay){
	SendServoCommand("#1P1300#2P1380#3P1400#4P1380#5P1400#6P1425#7P1320#8P1340",time_delay);
}




//4 steps***********************
void SendFirstCommand(int time_delay){
	SendServoCommand("#1P1100#2P1200#3P1500#4P1560#5P1500#6P1220#7P1100#8P1530",time_delay);
}
void SendSecondCommand(int time_delay){
	SendServoCommand("#1P1500#2P1200#3P1100#4P1560#5P1200#6P1220#7P1500#8P1530",time_delay);
}
void SendThirdCommand(int time_delay){
	SendServoCommand("#1P1500#2P1530#3P1100#4P1200#5P1200#6P1590#7P1500#8P1190",time_delay);
}
void SendFourthCommand(int time_delay){
	SendServoCommand("#1P1100#2P1530#3P1500#4P1200#5P1500#6P1590#7P1100#8P1190",time_delay);
}





void SendServoCommand(String command, int time_delay){
	Serial1.print(command);
	Serial1.print("T");
	Serial1.println(time_delay);
	//Serial.print(command);
	//Serial.print("T");
	//Serial.println(time_delay);
	delay(time_delay); 
	//Serial.println(command);
}

void SendServoStatement(int chan,int ang, int time_delay){
    Serial.print(String("#"));
    Serial.print(String(chan));
    Serial.print(String("P"));
    Serial.print(String(ang));
    Serial.print(String("T"));
    Serial.println(String(time_delay));

    Serial1.print(String("#"));
    Serial1.print(String(chan));
    Serial1.print(String("P"));
    Serial1.print(String(ang));
    Serial1.print(String("T"));
    Serial1.println(String(time_delay));
}