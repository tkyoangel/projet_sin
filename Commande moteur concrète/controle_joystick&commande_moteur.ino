/*
         _          __________                              _,
     _.-(_)._     ."          ".      .--""--.          _.-{__}-._
   .'________'.   | .--------. |    .'        '.      .:-'`____`'-:.
  [____________] /` |________| `\  /   .'``'.   \    /_.-"`_  _`"-._\
  /  / .\/. \  \|  / / .\/. \ \  ||  .'/.\/.\'.  |  /`   / .\/. \   `\
  |  \__/\__/  |\_/  \__/\__/  \_/|  : |_/\_| ;  |  |    \__/\__/    |
  \            /  \            /   \ '.\    /.' / .-\                /-.
  /'._  --  _.'\  /'._  --  _.'\   /'. `'--'` .'\/   '._-.__--__.-_.'   \
 /_   `""""`   _\/_   `""""`   _\ /_  `-./\.-'  _\'.    `""""""""`    .'`\
(__/    '|    \ _)_|           |_)_/            \__)|        '       |   |
  |_____'|_____|   \__________/   |              |;`_________'________`;-'
   '----------'    '----------'   '--------------'`--------------------`
   
   !!!! METTRE LE ENA et le ENB pour chaque moteur A et B pour qu'ils marchent ( voir docu shields )
*/
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
long ValeurHorizontale_Milieu;
long ValeurVerticale_Milieu;

void setup() {
  Serial.begin(9600);
  pinMode(SELpress, INPUT_PULLUP);
  pinMode(ENA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(Calibrage_Button, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(SELpress)) {  // calibrage du joystick mais changer le bouton de calibrage, mettre un bouton à côté
    ValeurHorizontale_Milieu = 0;
    ValeurVerticale_Milieu = 0;
    for (int i = 0; i < 150; i++) {
      ValeurHorizontale_Milieu += analogRead(HorizontalAxis);
      ValeurVerticale_Milieu += analogRead(VerticalAxis);
      delay(2);
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

  if (VerticalValue==ValeurVerticale_Milieu&&HorizontalValue==ValeurHorizontale_Milieu){ // faire en sorte de pas bouger les moteurs
    digitalWrite(in1, LOW);digitalWrite(in2, LOW);digitalWrite(in3, LOW);digitalWrite(in4, LOW);digitalWrite(ENA, LOW);digitalWrite(ENB, LOW);
  }

  if (VerticalValue>ValeurVerticale_Milieu){ // avancer quand le joystick est poussé
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    int PWM_forward_Rmotor = map(PWM_forward_Rmotor, ValeurVerticale_Milieu, 1023, 0, 255);
    int PWM_forward_Lmotor = map(PWM_forward_Lmotor, ValeurVerticale_Milieu, 1023, 0, 255);
    analogWrite(in1, PWM_forward_Rmotor);
    digitalWrite(in2, LOW);
    analogWrite(in3, PWM_forward_Lmotor);
    digitalWrite(in4, LOW);
  }

  if (VerticalValue<ValeurVerticale_Milieu){ // reculer quand le joystick est tiré
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    int PWM_backward_Rmotor = map(PWM_backward_Rmotor, 0, ValeurVerticale_Milieu, 0, 255);
    int PWM_backward_Lmotor = map(PWM_backward_Lmotor, 0, ValeurVerticale_Milieu, 0, 255);
    analogWrite(in2, PWM_backward_Lmotor);
    digitalWrite(in1, LOW);
    analogWrite(in4, PWM_backward_Rmotor);
    digitalWrite(in3, LOW);
  } 
}

/*
        .--'''''''''--.
     .'      .---.      '.
    /    .-----------.    \
   /        .-----.        \
   |       .-.   .-.       |
   |      /   \ /   \      |
    \    | .-. | .-. |    /
     '-._| | | | | | |_.-'
         | '-' | '-' |
          \___/ \___/
       _.-'  /   \  `-._
     .' _.--|     |--._ '.
     ' _...-|     |-..._ '
            |     |
            '.___.'
              | |
             _| |_
            /\( )/\
           /  ` '  \
          | |     | |
          '-'     '-'
          | |     | |
          | |     | |
          | |-----| |
       .`/  |     | |/`.
       |    |     |    |
       '._.'| .-. |'._.'
             \ | /
             | | |
             | | |
             | | |
            /| | |\
          .'_| | |_`.
          `. | | | .'
       .    /  |  \    .
      /o`.-'  / \  `-.`o\
     /o  o\ .'   `. /o  o\
     `.___.'       `.___.'
     */
