/*
TODO

* Implement new game button

* Bonus point targets
** Randomly assign a button to be worth double points
** Use random number in size of array
** Light up bonus button, then flash as normal
** Light up bonus target for X seconds

* Get MySQL connection working

*/

const int hitTimesFlash = 4;
const int hitTimeFlashDelay = 200;
const int bonusTimeFlashDelay = 500;

const int numberTargetButtons = 2; // Update with count of buttons, sizeof() doesn't seem to cooperate and apparently there is no count / array length function!?

const int targetButtonScore[] = {50, 100}; // Update for new button

/*const int buttonNewGamePin = 0;*/
const int targetButtonPin[] = {9, 10}; // Update for new button
const int targetLedPin[] = {6, 13}; // Update for new button

unsigned long currentMillis = 0;
int targetLedFlashCount[] = {0, 0}; // Update for new button
unsigned long targetLedPreviousMillis[] = {0, 0}; // Update for new button


int newGameNumber = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(buttonNewGamePin, INPUT);
  
  for (int i = 0; i < numberTargetButtons; i++){
    pinMode(targetButtonPin[i], INPUT);
  }
  
  for (int i = 0; i < numberTargetButtons; i++){
    pinMode(targetLedPin[i], OUTPUT);
  }
  
}

void loop() {
	
  /*if (digitalRead(buttonNewGamePin) == HIGH) {
    displayNewGameMessage();
    newGameNumber++;
  } else {
    
  }*/
	
	currentMillis = millis(); 
	checkTargetButtons();
  flashTargetLeds();
	
}

void checkTargetButtons() {
	for(int i = 0; i < numberTargetButtons; i++) {
    if (digitalRead(targetButtonPin[i]) == HIGH) {
      targetLedFlashCount[i] += hitTimesFlash;
			delay(250);
			displayHitMessage(i); // For debugging only, to be replaced by MySQL method
    }
    else {
      
    }
  }
}

void flashTargetLeds() {
	for (int i = 0; i < numberTargetButtons; i++) {
		if (targetLedFlashCount[i] > 0 && digitalRead(targetLedPin[i]) == LOW) {
			if (currentMillis - targetLedPreviousMillis[i] >= hitTimeFlashDelay) {
				digitalWrite(targetLedPin[i], HIGH);
				targetLedPreviousMillis[i] = millis();
				targetLedFlashCount[i] -= 1;
			}
		} 
		else {
			if (currentMillis - targetLedPreviousMillis[i] >= hitTimeFlashDelay) {
				digitalWrite(targetLedPin[i], LOW);
				targetLedPreviousMillis[i] = millis();
			}	
		}
	}
}

// For debugging only
void displayHitMessage(int i) {
  Serial.print(targetButtonScore[i]); 
  Serial.println(" Points!");
}