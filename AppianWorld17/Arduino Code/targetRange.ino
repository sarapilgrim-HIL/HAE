/*
TODO

* Bonus point targets
** Randomly assign a button to be worth double points
** Use random number in size of array
** Light up bonus button, then flash as normal
** Light up bonus target for X seconds

* Implement new game button

*/

const int numberTargetButtons = 1; // Update with count of buttons, sizeof() doesn't seem to cooperate and apparently there is no count / array length function!?
const int targetButtonScore[] = {100}; // Update for new button
const int targetButtonPin[] = {13}; // Update for new button
const int targetLedPin[] = {7}; // Update for new button
int targetLedFlashCount[] = {0}; // Update for new button
unsigned long targetLedPreviousMillis[] = {0}; // Update for new button

const int newGameButtonPin = 12;
const int newGameLedPin = 6;
const int newGameTimesFlash = 4;
const int newGameFlashDelay = 250;

const int hitTimesFlash = 2;
const int hitTimeFlashDelay = 250;
const int bonusTimeFlashDelay = 500;
const int buttonCheckDelay = 250;

void setup() {
  Serial.begin(9600);
  
  pinMode(newGameButtonPin, INPUT);
	pinMode(newGameLedPin, OUTPUT);
  
  for (int i = 0; i < numberTargetButtons; i++){
    pinMode(targetButtonPin[i], INPUT);
  }
  
  for (int i = 0; i < numberTargetButtons; i++){
    pinMode(targetLedPin[i], OUTPUT);
  }
  
}

void loop() {
  
  checkNewGameButton();
  checkTargetButtons();
  flashTargetLeds();
  
}

void checkNewGameButton() {
	if (digitalRead(newGameButtonPin) == HIGH) {
		Serial.println("NewGame");
		for (int i = 0; i < numberTargetButtons; i++) {
			digitalWrite(targetLedPin[i], LOW);
			targetLedFlashCount[i] = 0;
		}
		for (int i = 0; i <newGameTimesFlash; i++) {
			digitalWrite(newGameLedPin, HIGH);
			delay(newGameFlashDelay);
			digitalWrite(newGameLedPin, LOW);
			delay(newGameFlashDelay);
		}
  } else {
    
  }
}

void checkTargetButtons() {
  for (int i = 0; i < numberTargetButtons; i++) {
    if (digitalRead(targetButtonPin[i]) == HIGH) {
      targetLedFlashCount[i] += hitTimesFlash;
      Serial.println(targetButtonScore[i]);
			delay(buttonCheckDelay);
    }
    else {
      
    }
  }
}

void flashTargetLeds() {
  for (int i = 0; i < numberTargetButtons; i++) {
    if (targetLedFlashCount[i] > 0 && digitalRead(targetLedPin[i]) == LOW) {
      if (millis() - targetLedPreviousMillis[i] >= hitTimeFlashDelay) {
        digitalWrite(targetLedPin[i], HIGH);
        targetLedPreviousMillis[i] = millis();
        targetLedFlashCount[i]--;
      }
    } 
    else {
      if (millis() - targetLedPreviousMillis[i] >= hitTimeFlashDelay) {
        digitalWrite(targetLedPin[i], LOW);
        targetLedPreviousMillis[i] = millis();
      } 
    }
  }
}