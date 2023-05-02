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
// Définition des pins avec des noms de variable
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
  
  // définition des modes de chaque pin (entrée ou sortie)
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
  // programme de calibrage du joystick
  if (!digitalRead(SELpress)) { // actionnement du bouton du joystick (changer le bouton + enlever l'inverse "!" )
    ValeurHorizontale_Milieu = 0; // on redéfinit la variable de calibrage à 0
    ValeurVerticale_Milieu = 0; // on redéfinit la variable de calibrage à 0
    for (int i = 0; i < 150; i++) { // on fait 150 tests pour former une moyenne assez correcte des valeurs correspondants à la position IDLE du joystick
      ValeurHorizontale_Milieu += analogRead(HorizontalAxis);
      ValeurVerticale_Milieu += analogRead(VerticalAxis);
      delay(2);
    }
    ValeurHorizontale_Milieu /= 150; // on divise la variable par 150 pour avoir la moyenne, et on l'affecte alors à la position IDLE du joystick de référence
    ValeurVerticale_Milieu /= 150;
    Serial.println("Valeure Horizontale Calibree :");
    Serial.print(ValeurHorizontale_Milieu);
    Serial.println("Valeur Verticale Calibree :");
    Serial.print(ValeurVerticale_Milieu);
  }
  

  // captage des valeurs verticales et horizontales du joystick
  int VerticalValue = analogRead(VerticalAxis);
  int HorizontalValue = analogRead(HorizontalAxis);


  // on ne fait rien si le joystick est en position IDLE, => on met tous les pins en LOW pour éviter qu'un quelconque moteur tourne
  if (VerticalValue==ValeurVerticale_Milieu&&HorizontalValue==ValeurHorizontale_Milieu){ 
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
  }


  // programme permettant de faire tourner les moteurs en avant quand le joystick est poussé sur l'axe Y
  if (VerticalValue>ValeurVerticale_Milieu){
    digitalWrite(ENA, HIGH); // on permet l'actionnement du moteur A (voir schéma electrique & portes logiques)
    digitalWrite(ENB, HIGH); // on permet l'actionnement du moteur B (voir schéma electrique & portes logiques)
    int PWM_forward_Rmotor = map(PWM_forward_Rmotor, ValeurVerticale_Milieu, 1023, 0, 255); // redéfinition de la valeur de la PWM selon la position du Joystick
    int PWM_forward_Lmotor = map(PWM_forward_Lmotor, ValeurVerticale_Milieu, 1023, 0, 255); // redéfinition de la valeur de la PWM selon la position du Joystick
    analogWrite(in1, PWM_forward_Rmotor); // commande de vitesse du moteur selon la valeur de PWM calculée si dessus
    digitalWrite(in2, LOW); // actionnement des transistors pour commander le sens de rotation
    analogWrite(in3, PWM_forward_Lmotor); // commande de vitesse du moteur selon la valeur de PWM calculée si dessus
    digitalWrite(in4, LOW); // actionnement des transistors pour commander le sens de rotation
  }


  // programme permettant de faire tourner les moteurs dans le sens contraire quand le joystick est tiré sur l'axe Y
  if (VerticalValue<ValeurVerticale_Milieu){
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
