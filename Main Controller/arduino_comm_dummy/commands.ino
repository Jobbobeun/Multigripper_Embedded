/*
 * This file holds all the "dummy" data
 */
int DUMMY_ACCELERATION = 2500; // mm/s^2 ?
int DUMMY_VELOCITY = 50; // mm/s^2 ?

int DUMMY_KP = 20; // mm/s^2 ?
int DUMMY_KI = 15; // mm/s^2 ?
int DUMMY_KD = 5; // mm/s^2 ?

int DUMMY_LPF = 150; // rad/s or hz ?
/*
 * This file holds the functions for making contact 
 * with the computer application. 
 * 
 * All the data is taken from dummy_data
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
  delay(DELAY_TIME);
  const long DUMMY_SETPOINT = 500000; // in um?
  int DUMMY_TIME = 0; // time in ms!
  int DUMMY_POSITION = 0;

  // Send 5000 data points, so repeat loop that many times
  for (int i = 0; i < 5000; i++)
  {
    Serial.print("1;"); // check byte
    Serial.print(int(*gripperID));
    Serial.print(";");
    Serial.print(DUMMY_SETPOINT);
    Serial.print(";");
    Serial.print(DUMMY_TIME);
    Serial.print(";");
    Serial.print(DUMMY_POSITION);
    Serial.print("\n");

    // Increase every dummy "sample step"
    DUMMY_TIME++;
    DUMMY_POSITION += 5;
  }
}




/*
 * This function should send:
 * 2;IdGripper;Setpoint;Kp;Ki;Kd;LPF;Acc;Vel
 * 
 * (2 is the check bit)
 */
void receiveControllerInfoCommand(long* gripperID)
{
  delay(DELAY_TIME);
  const long DUMMY_SETPOINT = random(400000, 500000); // in um?
  const int DUMMY_TIME = random(0, 1000); // time in ms!
  const int DUMMY_POSITION = random(0, 1000);
  
  Serial.print("2;"); // check byte
  Serial.print(int(*gripperID));
  Serial.print(";");
  Serial.print(DUMMY_SETPOINT);

  Serial.print(";");
  Serial.print(DUMMY_KP); 
  Serial.print(";");
  Serial.print(DUMMY_KI); 
  Serial.print(";");
  Serial.print(DUMMY_KD);
  Serial.print(";");
  Serial.print(DUMMY_LPF); 

  Serial.print(";");
  Serial.print(DUMMY_ACCELERATION); // in dummy_data
  Serial.print(";");
  Serial.print(DUMMY_VELOCITY); // in dummy_data
  
  Serial.print("\n");
}




/*
 * This function should send:
 * 3;idGripper;Setpoint
 * Which is basically a command echo
 * 
 * (3 is the check bit)
 */
void sendPositionCommand(long* gripperID, long* setpoint)
{
  Serial.print("3;");
  Serial.print(int(*gripperID));
  Serial.print(";");
  Serial.print(int(*setpoint));
  Serial.print("\n");
}

/*
 * This function should send:
 * 4;Status
 * 
 * Where status is the "echo"
 * (4 is the check bit)
 */
void receiveStatusCommand()
{
  delay(DELAY_TIME);
  Serial.print("4;");
  Serial.print(systemStatus); // in main file, integer (enum)
  Serial.print("\n");
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
  delay(DELAY_TIME);
  systemStatus = int(*statusSignal);
  Serial.print("5;");
  Serial.print(systemStatus);
  Serial.print("\n");
}


/*
 * This function should send:
 * 6;IdGripper;Kp;Ki;Kd;LPF
 * 
 * (6 is the check bit)
 */
void sendControllerSettingsCommand(long* gripperID, long* Kp, long* Ki, long* Kd, long* LPF, long* acc, long* vel)
{
  delay(DELAY_TIME);
  DUMMY_KP = int(*Kp);
  DUMMY_KI = int(*Ki);
  DUMMY_KD = int(*Kd);

  DUMMY_LPF = int(*LPF);

  DUMMY_ACCELERATION = int(*acc);
  DUMMY_VELOCITY = int(*vel);
  
  Serial.print("6;");
  Serial.print(int(*gripperID));
  Serial.print(";");
  Serial.print(DUMMY_KP);
  Serial.print(";");
  Serial.print(DUMMY_KI);
  Serial.print(";");
  Serial.print(DUMMY_KD);
  Serial.print(";");
  Serial.print(DUMMY_LPF);
  Serial.print(";");
  Serial.print(DUMMY_ACCELERATION);
  Serial.print(";");
  Serial.print(DUMMY_VELOCITY);
  Serial.print("\n");
}
