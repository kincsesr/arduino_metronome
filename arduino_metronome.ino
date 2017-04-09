/*
 * Simple metronom
 */

#include "pins.h"
#include "state.h"
 
#define NOTE_HIGH  392
#define NOTE_LOW  196

#define NOTE_DURATION 50
#define TEMPO 120L
  
#define MINUTE 60L * 1000
#define SECOND 1000
 
const int numPatterns = 4;
int pattern[] = {
  1, 0, 0, 0
};

// egesz hang ideje 
long fullNoteDuration = MINUTE / TEMPO;
int counter = 0;

State state;
 
void setup() {
 
  Serial.begin(9600);
  // soros sebesseg
  Serial.println("Start...");
  
  // initialize LEDs
  pinMode(tempoLedPinUp, OUTPUT);
  pinMode(tempoLedPinDown, OUTPUT);
  pinMode(rhythmLedPin, OUTPUT);
  pinMode(accentLedPin, OUTPUT);
 
  // initialize buttons;
  pinMode(onOffButtonPin, INPUT);
  pinMode(tempoUpButtonPin, INPUT);
  pinMode(tempoDownButtonPin, INPUT);

  state.enabled = 1;
  state.tempoUp = 0;
  state.tempoDown = 0;
  state.prell_delay = 0;
}

void handle_tempoUp(State state) {
  // ha lenyomtak a gombot, akkor felvillantjuk a LED-et
  if (state.tempoUp) {
	Serial.println("tempo up pressed");
    digitalWrite(tempoLedPinUp, HIGH);
	delay(10);
	state.prell_delay += 10;
	digitalWrite(tempoLedPinUp, LOW);
	
	// visszaallitjuk az allapotot
	state.tempoUp = 0;
  }
}

void handle_tempoDown(State state) {
  // ha lenyomtak a gombot, akkor felvillantjuk a LED-et
  if (state.tempoDown) {
	Serial.println("tempo up pressed");
    digitalWrite(tempoLedPinDown, HIGH);
	delay(10);
	state.prell_delay += 10;
    digitalWrite(tempoLedPinDown, LOW);
	
	// visszaallitjuk az allapotot
	state.tempoDown = 0;
  }
}
  
void handle_enabled(State state) {
  if (state.enabled) {
      counter = (counter + 1) % numPatterns;
   
      int noteToPlay = pattern[counter] == 1 ? NOTE_HIGH : NOTE_LOW;
 
      // turn the LED on
      digitalWrite(rhythmLedPin, HIGH);
      int noteDuration = NOTE_DURATION;

      if (counter == 0) {
        noteDuration -= state.prell_delay;
        digitalWrite(accentLedPin, HIGH);
      }
 
      // send the note
      tone(speaker, noteToPlay, noteDuration);
     
      // turn the LED off
      digitalWrite(rhythmLedPin, LOW); 
      digitalWrite(accentLedPin, LOW);
      
      // to distinguish the notes
      long pauseBetweenNotes = fullNoteDuration - NOTE_DURATION;
      delay(pauseBetweenNotes);
 
      // stop the tone playing:
      noTone(speaker);
  } else {
    noTone(speaker);
    delay(SECOND / 4);
  }
 
}
 
void loop() {

  state.prell_delay = 0;
	get_state(&state);

  handle_tempoUp(state);
  handle_tempoDown(state);
  handle_enabled(state);

}
