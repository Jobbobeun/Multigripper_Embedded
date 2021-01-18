/*
 * This file holds the functions for making contact 
 * with the computer application. 
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
  Serial.print("receive positions command with gripper ID: ");
  Serial.println(int(*gripperID));
}




/*
 * This function should send:
 * 2;IdGripper;Setpoint;Acc;Vel;Kp;Ki;Kd;LPF 
 * 
 * (2 is the check bit)
 */
void receiveControllerInfoCommand(long* gripperID)
{
  Serial.print("receive controller info command with gripper ID: ");
  Serial.println(int(*gripperID));
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
  Serial.print("send postion command with gripper ID: ");
  Serial.print(int(*gripperID));
  Serial.print(", and setpoint: ");
  Serial.println(int(*setpoint));
}

/*
 * This function should send:
 * 5;Status
 * 
 * Where status is the "echo"
 * (5 is the check bit)
 */
void receiveStatusCommand()
{
  Serial.print("4;OK\n");
}

/*
 * This function should send:
 * 6;IdGripper;Kp;Ki;Kd;LPF
 * 
 * Which is basically an echo
 * (6 is the check bit)
 */
void sendStatusCommand(long* statusSignal)
{
  Serial.print("5;");
  Serial.print(*statusSignal);
  Serial.print("\n");
}


/*
 * This function should send:
 * 4;Status [ dit nog verifieren ]
 * 
 * (4 is the check bit)
 */
void sendControllerSettingsCommand(long* gripperID, long* Kp, long* Ki, long* Kd, long* LPF)
{
  Serial.print("send controller settings command with gripper ID: ");
  Serial.print(int(*gripperID));
  Serial.print(", and Kp: ");
  Serial.print(int(*Kp));
  Serial.print(", and Ki: ");
  Serial.print(int(*Ki));
  Serial.print(", and Kd: ");
  Serial.print(int(*Kd));
  Serial.print(", and LPF: ");
  Serial.println(int(*LPF));
}
