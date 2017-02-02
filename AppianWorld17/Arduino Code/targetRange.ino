/*
TODO

* Bonus point targets
** Randomly assign a button to be worth double points
** Use random number in size of array
** Light up bonus button, then flash as normal
** Light up bonus target for X seconds

* Get MySQL connection working

*/

/*#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>*/
#include <LiquidCrystal.h>

// byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

/*IPAddress server_addr(10, 100, 100, 117);    // IP of the MySQL *server* here
char user[] = "root";                     // MySQL user login username
char password[] = "Password1!";           // MySQL user login password

// Sample query
char query[] = "SELECT name FROM test WHERE id = 1";

EthernetClient client;
MySQL_Connection conn((Client *)&client);
// Create an instance of the cursor passing in the connection
MySQL_Cursor cur = MySQL_Cursor(&conn);*/

const String hitMessage = "  Direct Hit!";
const int timeMessageSwitchDelay = 2000;
const int timesFlash = 2;
const int timeFlashDelay = 500;
const int targetButtonScore[] = {50, 100};

const int buttonNewGamePin = 0;
const int targetButtonPin[] = {9, 10};
const int targetLedPin[] = {6, 13};

// int connectionTimeCounter = 1;

int newGameNumber = 0;

void setup() {
  Serial.begin(9600);
  /*while (!Serial); // wait for serial port to connect
  Ethernet.begin(mac_addr);
  lcd.begin(16, 2);
  lcd.print("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    lcd.clear();
    lcd.print("Connecting...");
    lcd.print(connectionTimeCounter);
    connectionTimeCounter++;
  }
  else {
    lcd.clear();
    lcd.print("Connection failed.");
    delay(5000);
    lcd.clear();
  }
  lcd.clear();
  lcd.print("Connection Successful!");
  delay(timeMessageSwitchDelay);
  lcd.clear();*/
  
  pinMode(buttonNewGamePin, INPUT);
  
  for (int i = 0; i < sizeof(targetButtonPin); i++){
    pinMode(targetButtonPin[i], INPUT);
  }
  
  for (int i = 0; i < sizeof(targetLedPin); i++){
    pinMode(targetLedPin[i], OUTPUT);
  }
  
}

void loop() {
	
  /*if (digitalRead(buttonNewGamePin) == HIGH) {
    displayNewGameMessage();
    newGameNumber++;
  } else {
    
  }*/
  
  for (int i = 0; i < sizeof(targetButtonPin); i++) {
    if (digitalRead(targetButtonPin[i]) == HIGH) {
      displayHitMessage(i);
      delay(100);
    }
    else {
      
    }
  }
  
  delay(100);
}

void displayNewGameMessage() {
  lcd.begin(16, 2);
  lcd.print("   New game!");
  lcd.setCursor(0,1);
  lcd.print("   Number: ");
  lcd.print(newGameNumber);
	delay(timeMessageSwitchDelay);
  lcd.clear();
}

void displayHitMessage(int i) {
  lcd.begin(16, 2);
  lcd.print(hitMessage);
  flashButton(i, timesFlash);
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("  ");
  lcd.print(targetButtonScore[i]); 
  lcd.print(" Points!");
  flashButton(i, timesFlash);
  lcd.clear();
}

void flashButton(int i, int numberTimes) {
  for(int x = 0; x < numberTimes; x++) {
    digitalWrite(targetLedPin[i], HIGH);
    delay(timeFlashDelay);
    digitalWrite(targetLedPin[i], LOW);
    delay(timeFlashDelay);
  }
}