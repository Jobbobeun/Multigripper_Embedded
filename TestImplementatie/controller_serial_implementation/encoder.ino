/* Base function for updating postion reading
 * Implements a simple four-state machine for the four combinations
 * of A and B
 * 
  */

int a = 0; // LOW or HIGH actual value
int b = 0; // LOW or HIGH actual value

void updateRead()
{
  a = digitalRead(ENC_A);
  b = digitalRead(ENC_B);

  // state handling:
  switch (state)
  {
    case 0: 
      if (a == LOW && b == HIGH) // forwards
      {
        state = 1;
        measured++;
      }
      else if (a == HIGH && b == LOW) // backwards
      {
        state = 3;
        measured--;
      }
      break;
    case 1:
      if (a == HIGH && b == HIGH) // forwards
      {
        state = 2;
        measured++;
      }
      else if (a == LOW && b == LOW) // backwards 
      {
        state = 0;
        measured--;
      }
      break;
    case 2:
      if (a == HIGH && b == LOW) // forwards
      {
        state = 3;
        measured++;
      }
      else if (a == LOW && b == HIGH) // backwards  
      {
        state = 1;
        measured--;
      }
      break;
    case 3:
      if (a == LOW && b == LOW) // forwards
      {
        state = 0;
        measured++;
      }
      else if (a == HIGH && b == HIGH) // backwards  
      {
        state = 2;
        measured--;
      }
      break;
  }
}
