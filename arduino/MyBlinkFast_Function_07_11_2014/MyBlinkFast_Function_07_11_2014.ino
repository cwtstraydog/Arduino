// sketch 01_02_blink_fast_slow
int ledPin = 13;

void setup()
{
  Serial.begin(115200);
  Serial.println("start");
  pinMode (ledPin, OUTPUT);
  flash(10, 100);
}

void loop()
{
  flash(10, 500);

 // Serial.println("in loop");
}

void flash(int n, int delayPeriod)
{
  for (int i = 0; i < n; i++)
  {
    digitalWrite(ledPin, HIGH);
    delay(delayPeriod);
    digitalWrite(ledPin, LOW);
    delay(delayPeriod);
    //  Serial.println("in flash");
  }

}
