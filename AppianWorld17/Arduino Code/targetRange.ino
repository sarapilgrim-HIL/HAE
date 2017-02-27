/*
TODO

*/

// PIN 0 AND 1 SHOULD NOT BE USED!
const int numberTargetButtons = 5; // UPDATE with count of buttons, sizeof() doesn't seem to cooperate and apparently there is no count / array length function!?
const int targetButtonPin[] = {2, 3, 4, 5, 6}; // UPDATE for new button
const int targetButtonScore[] = {75, 100, 50, 100, 75}; // UPDATE for new button
const int targetLedPin[] = {9, 10, 11, 12, 13}; // UPDATE for new button
/*int targetLedFlashCount[] = {0, 0, 0}; // UPDATE for new button*/
/*unsigned long targetLedPreviousMillis[] = {0, 0, 0}; // UPDATE for new button*/

const int newGameButtonPin = 7;
const int newGameLedPin = 8;

const int newGameTimesFlash = 5;
const int newGameFlashDelay = 500;

const int hitTimesFlash = 5;
const int hitTimeFlashDelay = 100;

const int newShotFlashTimes = 3;

const int switchDelay = 500;

int bonusIndex = 0;
int previousBonusIndex = 0;
int bonusCheckCount = 0;
unsigned long bonusLedPreviousMillis = 0;
int bonusLedFlashCount = 0;

const int bonusMultiplier = 2;
const int bonusTimesFlash = 5;
const int bonusTimeFlashDelay = 1000;

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
  
  randomSeed(analogRead(0));
  setBonusIndex();
  
}

void loop() {
	
  checkNewGameButton();
  checkBonusIndex();
  flashBonusLed();
  checkTargetButtons();
  /*flashTargetLeds();*/
}

void checkNewGameButton() {
  if (digitalRead(newGameButtonPin) == HIGH) {
    Serial.println("NewGame");
    for (int i = 0; i < numberTargetButtons; i++) {
      digitalWrite(targetLedPin[i], LOW);
      /*targetLedFlashCount[i] = 0;*/
    }
    for (int i = 0; i <newGameTimesFlash; i++) {
      digitalWrite(newGameLedPin, HIGH);
      delay(newGameFlashDelay);
      digitalWrite(newGameLedPin, LOW);
      delay(newGameFlashDelay);
    }
    setBonusIndex();
		delay(switchDelay);
  } else {
    
  }
}

void checkTargetButtons() {
  for (int i = 0; i < numberTargetButtons; i++) {
    if (digitalRead(targetButtonPin[i]) == HIGH) {
      if (i == bonusIndex) {
        Serial.println(targetButtonScore[i] * bonusMultiplier);
      }
      else {
        Serial.println(targetButtonScore[i]);
      }
			flashHitLed(i);
      setBonusIndex();
    }
    else {
      
    }
  }
}

/*void checkTargetButtons() {
  for (int i = 0; i < numberTargetButtons; i++) {
    if (targetLedFlashCount[i] == 0 && digitalRead(targetButtonPin[i]) == HIGH) {
      targetLedFlashCount[i] += hitTimesFlash;
      if (i == bonusIndex) {
        Serial.println(targetButtonScore[i] * bonusMultiplier);
      }
      else {
        Serial.println(targetButtonScore[i]);
      }
      setBonusIndex();
    }
    else {
      
    }
  }
}*/

void flashHitLed(int hitIndex) {
	for (int i = 0; i < hitTimesFlash; i++) {
		digitalWrite(targetLedPin[bonusIndex], LOW);
		digitalWrite(targetLedPin[hitIndex], HIGH);
		delay(hitTimeFlashDelay);
		digitalWrite(targetLedPin[hitIndex], LOW);
		delay(hitTimeFlashDelay);
	}
	/*for (int i = 0; i < 2; i++) { 
		digitalWrite(newGameLedPin, HIGH);
		delay(hitTimeFlashDelay);
		digitalWrite(newGameLedPin, LOW);
		delay(hitTimeFlashDelay);
	}*/
	delay(hitTimeFlashDelay);
	delay(hitTimeFlashDelay);
	flashAllButtons();
}

/*void flashTargetLeds() {
  for (int i = 0; i < numberTargetButtons; i++) {
    if (targetLedFlashCount[i] > 0 && digitalRead(targetLedPin[i]) == LOW) {
      if (millis() - targetLedPreviousMillis[i] >= hitTimeFlashDelay) {
        targetLedPreviousMillis[i] = millis();
        digitalWrite(targetLedPin[i], HIGH);
      }
    } 
    else {
      if (targetLedFlashCount[i] > 0 && digitalRead(targetLedPin[i]) == HIGH && millis() - targetLedPreviousMillis[i] >= hitTimeFlashDelay) {
        targetLedPreviousMillis[i] = millis();
        digitalWrite(targetLedPin[i], LOW);
        targetLedFlashCount[i]--;
      } 
    }
  }
}*/

void checkBonusIndex() {
  if (bonusLedFlashCount == 0 && millis() - bonusLedPreviousMillis >= bonusTimeFlashDelay) {
    setBonusIndex();
    bonusLedFlashCount = bonusTimesFlash;
  }
}

void setBonusIndex() {
  bonusLedFlashCount = 0;
  digitalWrite(targetLedPin[bonusIndex], LOW);
	previousBonusIndex = bonusIndex;
	while (previousBonusIndex == bonusIndex) {
		bonusIndex = random(0, numberTargetButtons);
		if (bonusCheckCount == 10) {
			break;
		}
	}
	bonusCheckCount = 0;
}

void flashBonusLed() {
  if (bonusLedFlashCount > 0 && digitalRead(targetLedPin[bonusIndex]) == LOW) {
    if (millis() - bonusLedPreviousMillis >= bonusTimeFlashDelay) {
      bonusLedPreviousMillis = millis();
      digitalWrite(targetLedPin[bonusIndex], HIGH);
    }
  } 
  else {
    if (bonusLedFlashCount > 0 && millis() - bonusLedPreviousMillis >= bonusTimeFlashDelay && digitalRead(targetLedPin[bonusIndex]) == HIGH) {
      bonusLedPreviousMillis = millis();
      digitalWrite(targetLedPin[bonusIndex], LOW);
      bonusLedFlashCount--;
    } 
  }
  
}

void flashAllButtons() {
	for (int i = 0; i < newShotFlashTimes; i++) {
		for (int i = 0; i < numberTargetButtons; i++) {
			digitalWrite(targetLedPin[i], HIGH);
		}
		delay(switchDelay);
		if (i == newShotFlashTimes - 1) {
			delay(switchDelay);
		}
		for (int i = 0; i < numberTargetButtons; i++) {
			digitalWrite(targetLedPin[i], LOW);
		}
		delay(switchDelay);
	}
}