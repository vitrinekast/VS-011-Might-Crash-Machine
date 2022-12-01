void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
}
int val = 0;
void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(0);
  Serial.print("analog 0 is: ");
  Serial.println(val);
  delay(250);
}
