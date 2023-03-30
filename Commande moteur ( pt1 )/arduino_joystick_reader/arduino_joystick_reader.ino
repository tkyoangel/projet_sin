// modifier les variables ici en fonction du branchement, ici on prend les pins stipulés dans la doc du joystick
int VerticalAxis = A0;
int HorizontalAxis = A1;
int SELpress = 2;
  
void setup(){
  Serial.begin(9600);
}

void loop(){
  int VertVal = analogRead(VerticalAxis);
  int HoriVal = analogRead(HorizontalAxis);
  Serial.println("Valeur verticale :");
  Serial.println(VertVal);
  Serial.println("Valeur horizontale :");
  Serial.println(HoriVal);
  delay(500);
}
