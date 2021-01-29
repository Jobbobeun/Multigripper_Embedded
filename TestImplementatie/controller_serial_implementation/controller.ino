

/*
 * 
 * Main controller implementation function
 */
 
void updatePID()
{
  error_current = setpoint - measured;
  integral += error_current;
  output = kp * error_current; // Proportional
  output += ki * integral; // Integral
  output += kd * ((error_current - error_previous) / ts); // Derivative


  // integral windup correction
  if ((ki * integral) > 255) 
  {
    integral = 255 / ki;
  }
  else if ((ki * integral) < -255)
  {
    integral = -255 / ki;
  }
  error_previous = error_current; // store most recent error value

}

// Write PWM motor output. Sign determines direction. Output = duty cycle -OUTPUT_MAX <-> +OUTPUT_MAX
void writeMotorOutput(int* output_temp)
{
  if (*output_temp < 0)
  {
    if (*output_temp < OUTPUT_MAX) 
    {
      *output_temp = -OUTPUT_MAX;
    }
    
    analogWrite(PIN_MOTOR_B, *output_temp * -1);
    digitalWrite(PIN_MOTOR_A, LOW);
  }
  else
  {
    if (*output_temp > OUTPUT_MAX) 
    {
      *output_temp = OUTPUT_MAX;
    }

    analogWrite(PIN_MOTOR_A, *output_temp);
    digitalWrite(PIN_MOTOR_B, LOW);
  }
}

/*
 * This function stores the data of the last 50 data points in memory
 * First-In-First-Out, so there will be a pointing moving downwards 
 * until it reaches the end of the data, after which it starts over at position
 * zero.
 * The data gets sorted in the computer application later on, so we can send the saved data in an arbitrary order
 */

long lastUpdateTime = 0;

void savePosition()
{
  if ((millis() - lastUpdateTime) > 24)
  {
    timeData[memoryPointer] = millis();
    memcpy(&positionData[memoryPointer], &measured, sizeof(measured));
    memcpy(&setpointData[memoryPointer], &setpoint, sizeof(measured));
  
    if (memoryPointer < 99)
    {
      memoryPointer++;
    }
    else 
    {
      bufferFull = true; // to tell data sending function not to use the memory_pointer for its loop
      memoryPointer = 0; // start at bottom again to overwrite oldest values
    }
    lastUpdateTime = millis();
  }
}
