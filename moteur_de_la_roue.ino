#include <Stepper.h>

//On défini le nombre de pas total de notre moteur

//const int nbPas 4096;--> Mauvais résultat...

const int nbPas = 2048;

const int In_1 = 8;// Inl

const int In_2 = 9;// In2

const int In_3 = 10;// In3

const int In_4 = 11; // In4

Stepper myStepper (nbPas, In_1, In_2, In_3, In_4);

void setup() {

// put your setup code here, to run once:



  myStepper.setSpeed(10);

};

void loop() {

// put your main code here, to run repeatedly: /

  myStepper.step(9999999999999999);

  delay(10);



};