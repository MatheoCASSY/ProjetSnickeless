#include "pitches.h"
#include <Servo.h>

// Définition de la broche du buzzer passif
const int buzzerPin = 11;

// Création de l'objet Servo
Servo monServo;

// Mélodie du Nyan Cat (suite des notes)
int melody[] = {
  NOTE_DS5, NOTE_E5, NOTE_FS5, 0, NOTE_B5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_FS5, NOTE_B5, NOTE_DS6, NOTE_E6, NOTE_DS6, NOTE_AS5, NOTE_B5, 0,
  NOTE_FS5, 0, NOTE_DS5, NOTE_E5, NOTE_FS5, 0, NOTE_B5, NOTE_CS6, NOTE_AS5, NOTE_B5, NOTE_CS6, NOTE_E6, NOTE_DS6, NOTE_E6, NOTE_CS6,
  NOTE_FS4, NOTE_GS4, NOTE_D4, NOTE_DS4, NOTE_FS2, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_B3, NOTE_CS4,
  NOTE_D4, NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_CS4
};

// Durée des notes correspondantes (chaque note est de la même durée)
int noteDurations[] = {
  16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
  16,16,16,16,16,16,8,16,16,16,16,16,16,16,16,
  8,8,16,16,16,16,16,16,8,8,8,
  8,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
  8,8,16,16,16,16,16,16,16,16,16,16,16,16
};

void setup() {
  // Initialisation de la broche du buzzer
  pinMode(buzzerPin, OUTPUT);

  // Initialisation du servomoteur
  monServo.attach(13);
  monServo.write(0);  // Position initiale du servomoteur à 0°

  // Attente de 15 secondes avant de commencer
  delay(15000);
  
  // fait tourner le moteur et Lance la mélodie
  turnServo();
  playMelody();
}

void loop() {
  // Ne fait rien, exécution unique dans le `setup()`
}

// Fonction pour jouer la mélodie Nyan Cat
void playMelody() {
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);

    // Pause entre les notes
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(buzzerPin);  // Stoppe le son
  }
  digitalWrite(buzzerPin, LOW);  // Éteindre le buzzer après la mélodie
}

// Fonction pour faire tourner le servomoteur
void turnServo() {
  monServo.write(90);  // Faire tourner le servo à 90°
  delay(1000);         // Attendre 1 seconde pour que le mouvement soit complet
  monServo.write(0);   // Remettre le servo à 0°
}
