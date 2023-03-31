int motor1 = 6;
int motor2 = 8;

void setup(){
    Serial.begin(9600);
}

void loop(){
    int PWM = 124;
    analogWrite(motor1, PWM);
}