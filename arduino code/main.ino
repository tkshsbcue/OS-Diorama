#include <Servo.h>

const int LED_PINS[5] = {2, 3, 4, 5, 6};
const int SERVO_PIN = 9;

const int SERVO_POSITIONS[5] = {0, 45, 90, 135, 180};

struct Process {
  int id;
  int startTime;
  int endTime;
};

Process timeline[50];
int timelineSize = 0;

Servo processServo;
String inputString = "";
boolean stringComplete = false;

unsigned long startMillis = 0;

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
  
  processServo.attach(SERVO_PIN);
  processServo.write(90);
  
  Serial.begin(9600);
  Serial.println("Arduino CPU Scheduling Demonstration Ready");
  Serial.println("Connect to the web interface to start");
  
  inputString.reserve(200);
}

void loop() {
  if (stringComplete) {
    processCommand(inputString);
    inputString = "";
    stringComplete = false;
  }
  
  if (timelineSize > 0) {
    runDemonstration();
  }
}

void processCommand(String command) {
  Serial.print("Received command: ");
  Serial.println(command);
  
  int colonIndex = command.indexOf(':');
  int pipeIndex = command.indexOf('|');
  
  if (colonIndex == -1 || pipeIndex == -1) {
    Serial.println("Invalid command format");
    return;
  }
  
  String algorithm = command.substring(0, colonIndex);
  String paramStr = command.substring(colonIndex + 1, pipeIndex);
  String dataStr = command.substring(pipeIndex + 1);
  
  timelineSize = 0;
  
  int segmentStart = 0;
  int segmentIndex = 0;
  
  while (segmentStart < dataStr.length()) {
    int segmentEnd = dataStr.indexOf(';', segmentStart);
    if (segmentEnd == -1) {
      segmentEnd = dataStr.length();
    }
    
    String segment = dataStr.substring(segmentStart, segmentEnd);
    
    int firstComma = segment.indexOf(',');
    int secondComma = segment.indexOf(',', firstComma + 1);
    
    if (firstComma != -1 && secondComma != -1) {
      String processIdStr = segment.substring(1, firstComma);
      String startTimeStr = segment.substring(firstComma + 1, secondComma);
      String endTimeStr = segment.substring(secondComma + 1);
      
      int processId = processIdStr.toInt();
      int startTime = startTimeStr.toInt();
      int endTime = endTimeStr.toInt();
      
      if (processId >= 1 && processId <= 5) {
        timeline[segmentIndex].id = processId;
        timeline[segmentIndex].startTime = startTime;
        timeline[segmentIndex].endTime = endTime;
        segmentIndex++;
        timelineSize++;
      }
    }
    
    segmentStart = segmentEnd + 1;
  }
  
  Serial.print("Parsed ");
  Serial.print(timelineSize);
  Serial.println(" segments");
  
  for (int i = 0; i < timelineSize; i++) {
    Serial.print("P");
    Serial.print(timeline[i].id);
    Serial.print(" from ");
    Serial.print(timeline[i].startTime);
    Serial.print(" to ");
    Serial.println(timeline[i].endTime);
  }
  
  if (algorithm == "SJF") {
    bool isPreemptive = (paramStr.toInt() == 1);
    Serial.print("Algorithm: SJF ");
    Serial.println(isPreemptive ? "Preemptive" : "Non-Preemptive");
  } else if (algorithm == "RR") {
    int timeQuantum = paramStr.toInt();
    Serial.print("Algorithm: Round Robin with quantum = ");
    Serial.println(timeQuantum);
  }
  
  Serial.println("Starting demonstration...");
  
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
  
  processServo.write(90);
  
  startMillis = millis();
}

void runDemonstration() {
  unsigned long currentMillis = millis();
  unsigned long elapsedTime = currentMillis - startMillis;
  
  int currentSegment = -1;
  for (int i = 0; i < timelineSize; i++) {
    if (elapsedTime >= timeline[i].startTime && elapsedTime < timeline[i].endTime) {
      currentSegment = i;
      break;
    }
  }
  
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
  
  if (currentSegment != -1) {
    int processId = timeline[currentSegment].id;
    
    digitalWrite(LED_PINS[processId - 1], HIGH);
    
    processServo.write(SERVO_POSITIONS[processId - 1]);
    
    if (elapsedTime % 500 < 10) {
      Serial.print("Running P");
      Serial.print(processId);
      Serial.print(" (");
      Serial.print(elapsedTime);
      Serial.print(" ms) - Segment ");
      Serial.print(currentSegment + 1);
      Serial.print(" of ");
      Serial.println(timelineSize);
    }
  } else if (elapsedTime > timeline[timelineSize - 1].endTime) {
    if (elapsedTime % 1000 < 10) {
      Serial.println("Demonstration complete. Send new data to restart.");
    }
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    
    if (inChar != '\n') {
      inputString += inChar;
    } 
    else {
      stringComplete = true;
    }
  }
}