int VerticalAxis = A0;
int HorizontalAxis = A1;
int SELpress = 2;
int ENA = 3;
int in1 = 4;
int in2 = 5;
int in3 = 6;
int in4 = 7;
int ENB = 8;
int Calibrage_Button = 9;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(SELpress)) {  // calibrage du joystick
    long ValeurHorizontale_Milieu = 0;
    long ValeurVerticale_Milieu = 0;

    for (int i = 0; i++; i < 150) {
      ValeurHorizontale_Milieu += analogRead(HorizontalAxis);
      ValeurVerticale_Milieu += analogRead(VerticalAxis);
    }
    ValeurHorizontale_Milieu /= 150;
    ValeurVerticale_Milieu /= 150;
    Serial.println("Valeure Horizontale Calibree :");
    Serial.print(ValeurHorizontale_Milieu);
    Serial.println("Valeur Verticale Calibree :");
    Serial.print(ValeurVerticale_Milieu);
  }
  int VerticalValue = analogRead(VerticalAxis);
  int HorizontalValue = analogRead(HorizontalAxis);
}