
const int trigger1 = 2; //Trigger pin of 1st Sesnor
const int echo1 = 3; //Echo pin of 1st Sesnor
const int trigger2 = 4; //Trigger pin of 2nd Sesnor
const int echo2 = 5;//Echo pin of 2nd Sesnor

long time_taken;
int dist, distL, distR;



void setup() {
  Serial.begin(9600);

  pinMode(trigger1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trigger2, OUTPUT);
  pinMode(echo2, INPUT);
}

void calculate_distance(int trigger, int echo)
{
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  time_taken = pulseIn(echo, HIGH);
  dist = time_taken * 0.034 / 2;
  if (dist > 50)
    dist = 50;
}

void loop() { //infinite loopy
  calculate_distance(trigger1, echo1);
  distL = dist;      //Distance of left sensor

  calculate_distance(trigger2, echo2);
  distR = dist;     //Distance of right sensor

  //Pause Modes -Hold
  if ((distL > 40 && distL > 40) && (distL < 50 && distR < 50))     //Both hands
  {
    Serial.println("Play/Pause");
    delay (500);
  }

  calculate_distance(trigger1, echo1);
  distL = dist;

  calculate_distance(trigger2, echo2);
  distR = dist;

  if (distL >= 13 && distL <= 17)
  {
    delay(100);
    calculate_distance(trigger1, echo1);
    distL = dist;
    if (distL >= 13 && distL <= 17)
    {
      while (distL <= 40)
      {
        calculate_distance(trigger1, echo1);
        distL = dist;
        if (distL < 10)     // Push In Left Hand
        {
          Serial.println ("Vup");
          delay (300);
        }
        if (distL > 20)     //Pull Out Left Hand
        {
          Serial.println ("Vdown");
          delay (300);
        }
      }
    }
  }

  if (distR >= 13 && distR <= 17)
  {
    delay(100);
    calculate_distance(trigger2, echo2);
    distR = dist;
    if (distR >= 13 && distR <= 17)
    {
      while (distR <= 40)
      {
        calculate_distance(trigger2, echo2);
        distR = dist;
        if (distR < 10) //Push In Right hand
        {
          Serial.println ("Rewind");
          delay (300);
        }
        if (distR > 20) //Pull Out Right hand
        {
          Serial.println ("Forward");
          delay (300);
        }
      }
    }
  }

  delay(200);
}

