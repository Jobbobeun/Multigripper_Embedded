/*
 * This file holds all the "dummy" data
 */
int DUMMY_ACCELERATION = 2500; // mm/s^2 ?
int DUMMY_VELOCITY = 50; // mm/s^2 ?
long DUMMY_SETPOINT = 500000; // in um?

/*
 * This file holds the functions for making contact 
 * with the computer application. 
 * 
 * 
 */


/*
 * This function should send:
 *  1;IdGripper;SetPoint;Time;ActualpositonBuffer
 *  (1 is the check bit)
 *  
 *  With input "IdGripper"
 */

void receivePositionsCommand(long* gripperID)
{
  int oldStatus;
  memcpy(&oldStatus, &systemStatus, sizeof(systemStatus));
  systemStatus = PAUSED;
  
  delay(DELAY_TIME); // this delay is there to avoid "too quick" responses

  int DUMMY_TIME = 0; // time in ms!
  int DUMMY_POSITION = 0;

  // Send 50 data points, so repeat loop that many times
  int numItems;
  if (bufferFull == false) 
  {
    numItems = memoryPointer;
  }
  else
  {
    numItems = 50;
  }
  
  for (int i = 0; i < numItems; i++)
  {
    Serial.print("1;"); // check byte
    Serial.print(int(*gripperID));
    Serial.print(";");
    Serial.print(setpointData[i]);
    Serial.print(";");
    Serial.print(timeData[i]);
    Serial.print(";");
    Serial.print(positionData[i]);
    Serial.print("\n");

    // Increase every dummy "sample step"
    DUMMY_TIME++;
    DUMMY_POSITION = random(0, 3000);
  }

  systemStatus = oldStatus;
}




/*
 * This function should send:
 * 2;IdGripper;Setpoint;Kp;Ki;Kd;LPF;Acc;Vel
 * 
 * (2 is the check bit)
 */
void receiveControllerInfoCommand(long* gripperID)
{
  delay(DELAY_TIME); // this delay is there to avoid "too quick" responses
  
  Serial.print("2;"); // check byte
  Serial.print(int(*gripperID));
  Serial.print(";");
  Serial.print(setpoint);

  Serial.print(";");
  Serial.print(int(kp)); 
  Serial.print(";");
  Serial.print(int(ki*10)); 
  Serial.print(";");
  Serial.print(int(kd*100));
  Serial.print(";");
  Serial.print(LPF);

  Serial.print(";");
  Serial.print(DUMMY_ACCELERATION); // in dummy_data
  Serial.print(";");
  Serial.print(DUMMY_VELOCITY); // in dummy_data
  
  Serial.print("\n");
}




/*
 * This function should send:
 * 3;idGripper;Setpoint;acc;vel
 * Which is basically a command echo
 * 
 * (3 is the check bit)
 */
void sendPositionCommand(long* gripperID, long* setpointNew, long* acc, long* vel)
{
  delay(DELAY_TIME); // this delay is there to avoid "too quick" responses
  
  Serial.print("3;");
  Serial.print(int(*gripperID));
  Serial.print(";");
  Serial.print(int(setpoint));
  Serial.print(";");
  Serial.print(int(DUMMY_ACCELERATION));
  Serial.print(";");
  Serial.print(int(DUMMY_VELOCITY));
  Serial.print("\n");

  DUMMY_ACCELERATION = *acc;
  DUMMY_VELOCITY = *vel;
  setpoint = *setpointNew;
}

/*
 * This function should send:
 * 4;Status;Gripper1Setpoint;Gripper1Position;Gripper2Setpoint;Gripper2Position;
 * [……]Gripper20Setpoint;Gripper20Position
 * 
 * Where status is the "echo"
 * (4 is the check bit)
 */
void receiveStatusCommand()
{
  delay(DELAY_TIME); // this delay is there to avoid "too quick" responses
  Serial.print("4;");
  Serial.print(systemStatus); // in main file, integer (enum)
  
  for(int i = 0; i < 20; i++) 
  {
    Serial.print(";");
    Serial.print(setpoint);
    Serial.print(";");
    Serial.print(measured);
    
  }

  Serial.print("\n"); // close with newline char  
}

/*
 * This function should send:
 *
 * 5;Status
 * Which is basically an echo
 * (5 is the check bit)
 */
void sendStatusCommand(long* statusSignal)
{
  
  delay(DELAY_TIME); // this delay is there to avoid "too quick" responses

  Serial.print("5;");
  Serial.print(systemStatus);
  Serial.print("\n");

  systemStatus = int(*statusSignal);
}


/*
 * This function should send:
 * 6;IdGripper;Kp;Ki;Kd;LPF
 * 
 * (6 is the check bit)
 */
void sendControllerSettingsCommand(long* gripperID, long* kpNew, long* kiNew, long* kdNew, long* LPFNew)
{
  delay(DELAY_TIME); // this delay is there to avoid "too quick" responses
  kp = int(*kpNew);
  ki = float(*kiNew) / 10;
  kd = float(*kdNew) / 100;

  LPF = int(*LPFNew);
  
  Serial.print("6;");
  Serial.print(int(*gripperID));
  Serial.print(";");
  Serial.print(int(kp));
  Serial.print(";");
  Serial.print(int(ki*10));
  Serial.print(";");
  Serial.print(int(kd*100));
  Serial.print(";");
  Serial.print(LPF);
  Serial.print("\n");
}
