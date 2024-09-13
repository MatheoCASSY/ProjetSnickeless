#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Keypad.h>

// Initialisation de l'écran LCD à l'adresse I2C 0x27 (modifiez selon votre modèle d'écran)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Définition des broches du capteur HC-SR04
const int trigPin = 11;
const int echoPin = 12;

// Initialisation du servomoteur
Servo myServo;
const int servoPin = 8;

// Initialisation du clavier matriciel (keypad)
const byte ROWS = 4; // Quatre lignes
const byte COLS = 4; // Quatre colonnes (si vous avez un clavier 4x3, remplacez par 3)

// Définir les touches du clavier
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connecter les lignes du clavier aux broches de l'Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};  // Broches auxquelles les lignes sont connectées
byte colPins[COLS] = {5, 4, 3, 2}; // Broches auxquelles les colonnes sont connectées

// Créer un objet Keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

long duration;
int distance;

bool codeEntered = false; // Variable pour vérifier si l'utilisateur a entré le code

void setup() {
  // Configuration des broches du capteur
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialisation de l'écran LCD
  lcd.init();
  lcd.backlight();

  // Initialisation du servomoteur
  myServo.attach(servoPin); // Attache le servomoteur à la broche 6
  myServo.write(90); // Positionner le servomoteur à 0°

  // Message initial sur le LCD
  lcd.setCursor(0, 0);
  lcd.print("Mesure distance:");
  lcd.setCursor(0, 1);
  lcd.print("Attente...");
  delay(1000);
}

void loop() {
  // Envoyer un signal de 10 microsecondes à la broche Trig pour déclencher la mesure
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lire la durée de l'écho (temps que l'onde met à revenir)
  duration = pulseIn(echoPin, HIGH);

  // Calcul de la distance en centimètres (vitesse du son : 343 m/s)
  distance = duration * 0.034 / 2;

  // Si la distance a changé, demander le code
  if (distance < 100) {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Tapez 1");
    
    // Vérifier l'entrée du clavier
    char key = keypad.getKey();
    
    if (key) { // Si une touche est appuyée
      lcd.setCursor(0, 1);
      lcd.print("Touche : ");
      lcd.print(key);

      // Si la touche "1" est appuyée
      if (key == '1' && !codeEntered) {
        codeEntered = true; // Marquer que le code est entré
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Code valide!");

        // Faire tourner le servomoteur à 180°
        myServo.write(45); // Tourne le servomoteur à 180°
        delay(10000);        // Attendre que le moteur atteigne la position

        myServo.write(90);
        delay(1000);

        // Afficher le message de récupération
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Recuperer");
        delay(10000);
      }
    }
  }

  // Mise à jour de la distance précédente
  previousDistance = distance;

  // Petite pause avant la prochaine mesure
  delay(500);
}