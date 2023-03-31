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
    if(digitalRead(Calibrage_Button)==1){   // Calibrage du joystick
        int ValeurHorizontale_Milieu = analogRead(HorizontalAxis);
        int ValeurVerticale_Milieu = analogRead(VerticalAxis);
    }
    int VerticalValue = analogRead(VerticalAxis);
    int HorizontalValue = analogRead(HorizontalAxis);
    Serial.println("Valeur verticale :");
    Serial.println(VerticalValue);
    Serial.println("Valeur horizontale :");
    Serial.println(HorizontalValue);
}