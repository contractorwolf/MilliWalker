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

	
	int time_delay = 200;

	while(Serial.available()) {

		incomingCommand = "";
		character = Serial.read();
		incomingCommand.concat(character);
	}

	if (incomingCommand == "w") {
		//match with all 4 leg sets
		SendServoCommand("#1P1100#2P1200#3P1500#4P1600#5P1200#6P1250#7P1500#8P1600",time_delay);
		SendServoCommand("#1P1500#2P1200#3P1100#4P1600#5P1500#6P1250#7P1100#8P1600",time_delay);
		SendServoCommand("#1P1500#2P1600#3P1100#4P1200#5P1500#6P1600#7P1100#8P1200",time_delay);
		SendServoCommand("#1P1100#2P1600#3P1500#4P1200#5P1200#6P1600#7P1500#8P1200",time_delay);


	}else if (incomingCommand == "c") {
		//match with all 4 leg sets
		SendServoCommand("#1P1300#2P1300#3P1300#4P1300#5P1300#6P1300#7P1300#8P1300",time_delay);
	
	
	
	}else if (incomingCommand == "1") {
		//match with all 4 leg sets
		SendServoCommand("#1P1100#2P1200#3P1500#4P1600#5P1200#6P1250#7P1500#8P1600",time_delay);


	}else if (incomingCommand == "2") {
		//match with all 4 leg sets
		SendServoCommand("#1P1500#2P1200#3P1100#4P1600#5P1500#6P1250#7P1100#8P1600",time_delay);

	}else if (incomingCommand == "3") {
		//match with all 4 leg sets
		SendServoCommand("#1P1500#2P1600#3P1100#4P1200#5P1500#6P1600#7P1100#8P1200",time_delay);

	}else if (incomingCommand == "4") {
		//match with all 4 leg sets
		SendServoCommand("#1P1100#2P1600#3P1500#4P1200#5P1200#6P1600#7P1500#8P1200",time_delay);



	}else if (incomingCommand != "") {
		//match with all 4 leg sets
		SendServoCommand("#1P1300#2P1300#3P1300#4P1300#5P1300#6P1300#7P1300#8P1300",time_delay);

	}










  /* add main program code here */
		//flash led
    digitalWrite(led, HIGH);   
    delay(30);               
    digitalWrite(led, LOW); 
	//delay(100);  
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
    
  /*
    if(Serial1.available()){
      while(Serial1.available()) {
          Serial.print(Serial1.read());
      }
      Serial.println("");
    }
*/
}