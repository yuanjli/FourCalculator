#include <LiquidCrystal.h>
#include <math.h>

// Added by Anna B.
// I think my teammate got his starter code from here: https://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay
// But I'm unsure
// I found example code here: https://www.arduino.cc/en/Tutorial/Button

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//number of buttons
const int button_count = 3;

char char_ops[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '*', '/', 'S'};
int char_index = -1;

// start with an empty equation
String equation = "";

// button that moves through the diff inputs
const int button1Pin = 7;
// enter
const int button2Pin = 8;
// delete
const int button3Pin = 9;

void setup() {
  // initialize the pushbutton pins as an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  
  lcd.clear();
  lcd.print("<< Welcome! >>");
  lcd.begin(16,2);
  // removed createChar call
  lcd.clear();
}

void loop() {
  // main code
  // start in the top left
  // won't this just keep resetting?
  lcd.setCursor(0, 0);
  check_click();
}

//function that checks the clicked the button.
void check_click(){

  // input mode
  if (digitalRead(button1Pin) == LOW){

    // cycle back around if you get to the end of char_ops
    if (char_index == char_ops.length()) {
      char_index = -1;
    }
    char_index =+ 1;
    // get next character from char_ops and display on screen
    lcd.print(equation.substring(0, equation.length()-1) + char_ops[char_index]);
  }

  // enter
  if (digitalRead(button2Pin) == LOW){

    if (equation.charAt(equation.length()-1) != 'S') {
      // re-init char_index, so that when the user enters a new character, they must start from
      // the beginning of char_ops again
      char_index = -1;

      // need to add a condition here for solving equation
      lcd.print(equation + " ");
    } else {
      int result = calc_result(equation);
      lcd.print(result);
    }    
  }

  // delete
  if (digitalRead(button2Pin) == LOW) {
    // delete the last character in the equation string
    equation = equation.substring(0, equation.length());
    lcd.print(equation);
  }
}


// in order to solve the equation, we'll need to tokenize the string
// there's not a great way to do this...

int calc_result(String equation) {
  int result = 0;
  int equation_size = equation.length();
  boolean found_first_num = false;
  int curr_num = 0;
  char last_op = '\0';
  int last_op_index = -1;
  
  for (int i=0; i<equation_size; i++) {
    int j=i;
    while (j < equation_size && equation.charAt(j) != '+' && equation.charAt(j) != '-' && equation.charAt(j) != '*' && equation.charAt(j) != '/'){
      j++;
    }
  
    // at the beginning of the string
    if (found_first_num == false) {
      // set result to the first number we find
      result = equation.substring(0, j).toInt();
      found_first_num = true;
      
    } else {
        // get everything between the last operator found and the current operator (at index j)
        // store this as the current number and determine how to handle it, in relation to the running result
        curr_num = equation.substring(last_op_index+1,j).toInt();
        switch(last_op) {
          case '+': // add
            result = result + curr_num;
            break;
          case '-': // subtract
            result = result - curr_num;
            break;
          case '*': // multiply
            result = result * curr_num;
            break;
          case '/': // divide
            result = result - curr_num;
          break;
        }
    }
    last_op = equation.charAt(j);
    last_op_index = j;
    i = j;
  }
  return result;
}
   





