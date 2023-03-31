int VerticalAxis = A0;
int HorizontalAxis = A1;
int SELpress = 2;
int motor1 = 6;
int motor2 = 8;

void setup(){
    Serial.begin(9600);
}

void loop(){
    int VerticalValue = analogRead(VerticalAxis);
    int HoriVal = analogRead(HorizontalAxis);
    Serial.println("Valeur verticale :");
    Serial.println(VertVal);
    Serial.println("Valeur horizontale :");
    Serial.println(HoriVal);
    int PWM1 = VerticalValue/4;
    int PWM2 = HoriVal/4;
    analogWrite(motor1, PWM1);
    analogWrite(motor2, PWM2);
}