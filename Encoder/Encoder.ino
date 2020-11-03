#define input_1 PB12
#define input_2 PB13
int counter = 0, speed_ppm;
String direc = "";
static int current_time = 0, working_time;
void setup() {
  Serial.begin(9600);
  pinMode(input_1, INPUT_PULLUP);    // for A port
  pinMode(input_2, INPUT_PULLUP);    // for B port
  attachInterrupt(input_1, check_A, CHANGE);
  attachInterrupt(input_2, check_B, CHANGE);


}

void loop() {


}
void check_A()
{
  if (digitalRead(input_1) != digitalRead(input_2))   // to check if A and B have same signal (Anticlockwise) or not (clockwise)
  {
    counter++;
    direc = "CW";


  }
  else
  {
    counter--;
    direc = "CCW";
  }
  current_time = millis();      // to know the time which the encoder took for this  number of turns
  working_time = current_time  / 60000;    //to convert the result to pulse per minute(RPM) (60==>for minute 1000=> to convert to second )
  speed_ppm = counter / working_time;
  Serial.print("Direction");
  Serial.print(direc);
  Serial.print("/t");
  Serial.print("Value");
  Serial.print(speed_ppm);
  Serial.print("  PPM");
  current_time = 0;

}

void check_B()
{
  if (digitalRead(input_1) == digitalRead(input_2))   // to know the time which the encoder took for this  number of turns
  {
    counter++;
    direc = "CW";


  }
  else
  {
    counter--;
    direc = "CCW";
  }

  current_time = millis();
  working_time = current_time  / 60000;    //to convert the result to pulse per minute(RPM) (60==>for minute 1000=> to convert to second )
  speed_ppm = counter / working_time;
  Serial.print("Direction");
  Serial.print(direc);
  Serial.print("/t");
  Serial.print("Value");
  Serial.print(speed_ppm);
  Serial.print("  PPM");
  current_time = 0;



}
