// Définition des broches du capteur ultrason
const int trigPin = 9;
const int echoPin = 8;

// Définition de la broche du buzzer passif
const int buzzerPin = 11;

// Seuil de distance en cm
const int distanceSeuil = 3;

#include "pitches.h"

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
  8,8,16,16,16,16,16,16,16,16,16,16,16,16,
  8,16,16,16,16,16,16,16,16,8,8,8,
  8,8,16,16,16,16,16,16,8,8,8,
  8,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
  8,8,16,16,16,16,16,16,16,16,16,16,16,16,
  8,16,16,16,16,16,16,16,16,8,8,8
};

void setup() {
  // Initialisation des broches
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialisation du moniteur série
  Serial.begin(9600);
}

void loop() {
  // Mesure de la distance via le capteur ultrason
  long duration, distance;
  
  // Envoi d'une impulsion ultrasonique
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lecture du signal de retour
  duration = pulseIn(echoPin, HIGH);

  // Calcul de la distance (en cm)
  distance = duration * 0.034 / 2;

  // Affichage de la distance dans le moniteur série
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Si la distance est inférieure au seuil, joue la mélodie Nyan Cat
  if (distance < distanceSeuil) {
    playMelody();  // Lance la mélodie
    delay(3000);   // Attendre 3 secondes avant la prochaine détection
  }

  // Délai avant la prochaine mesure
  delay(500);
}

// Fonction pour jouer la mélodie Nyan Cat
void playMelody() {
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(melody[0]); thisNote++) {

    /*
      to calculate the note duration, take one second divided by the note type.
      e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
     */
    int noteDuration = 1000/noteDurations[thisNote];
    tone(11, melody[thisNote],noteDuration);

    /*
      to distinguish the notes, set a minimum time between them.
      the note's duration + 30% seems to work well:
     */
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(11); //stop the tone playing:
  }
  digitalWrite(11,LOW);
}
