#include <LiquidCrystal.h>
#include <math.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//number of buttons
const int button_count = 3;
const int button1Pin = 7;
const int button2Pin = 8;
const int button3Pin = 9;

byte press_count = 0
byte inputs[press_count] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, +, -, *, /, S};
//Delete the previous char
const char* space = " "
// a list that stores the numbers 
byte flash_data[] = {0, 0, 0};
long last_result = 0;



void setup() {
  // put your setup code here, to run once:
  lcd.clear();
  lcd.print("<< Welcome! >>");
  lcd.begin(16,2);
  lcd.createChar(0);
  result = 0;
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 1);
  check_click();
}


//function that checks the clicked the button.
void check_click(){
  boolean button_on = false;
  if (digitalRead(button1Pin) == low){
    press_count =+ 1;
    button_on = true;
    break;
  }
  if (digitalRead(button2Pin) == low){
    // needs to move the previous char ahead. 
    press_count =+ 1;
    button_on = true;
    break;
  }
  if (digitalRead(button3Pin) == low){
    //needs to remove one of the charactors that has already entered.
    break;
  }
}

//function that display the numbers.
void show_digits(){
  lcd.print(inputs[press_count]);
}


//function that solve the math.
void s_entered(){
  //
  switch(flash_data[1]) {
    case 1: // add
      result = flash_data[0] + flash_data[2];
      break;
    case 2: // subtract
      result = flash_data[0] - flash_data[2];
      break;
    case 3: // multiply
      result = flash_data[0] * flash_data[2];
      break;
    case 4: // divide
      result = flash_data[0] / flash_data[2];
      break;
    }
    reset();
    last_result = result;
    showResult();
}




