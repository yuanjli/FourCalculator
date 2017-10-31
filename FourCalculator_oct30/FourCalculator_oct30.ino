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

// number of buttons
const int button_count = 3;

// all the possible input options
char input_ops[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '*', '/', 'S'};
int input_index = -1;

// we represent the equation as a string
String equation = "";

// input 
const int button1Pin = 7;
// enter
const int button2Pin = 8;
// delete
const int button3Pin = 9;

// representing this char as a string for simple concatenation later
String cur_char;

void setup() {
  // initialize the pushbutton pins as an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  
  // Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("<< Calculator >>");
}

void loop() {
  // main code
  // start in the top right
  lcd.setCursor(15, 0);
  check_click();
  delay(100); // added this because it was incrementing an index too quickly
}

//function that checks the clicked the button.
void check_click(){
  int button1State = digitalRead(button1Pin);
  int button2State = digitalRead(button2Pin);
  int button3State = digitalRead(button3Pin);
  
  // input mode
  if (button1State == LOW){

    // see if user has reached end of input_ops
    // start at beginning of array again, if necessary
    if (input_index == (sizeof(input_ops) / sizeof(char))) {
      input_index = -1;
    }  
    
    input_index += 1; // ensures we always start at the 0th index
    
    //Serial.println(input_index);
    // get next character from input_ops and display on screen
    // for example, if the user presses the button 5 times, she will see 1, then 2, then 3...and finally 5
    lcd.clear();
    
    cur_char = input_ops[input_index];

    // don't include the current character in the equation just yet
    lcd.print(equation + cur_char);
  }

  // enter
  if (button2State == LOW){    
    
    // only execute if the user has chosen a character from input_ops
    if (cur_char.length() > 0) {
      
      //Serial.println("current equation char: " + cur_char);
      equation = equation + cur_char;
      
      //Serial.println("equation: " + equation);
      cur_char = "";   
      
      if (equation.charAt(equation.length()-1) != 'S') {
        
        // re-init input_index, so that when the user enters a new character, they must start from
        // the beginning of input_ops again
        input_index = -1;
        lcd.clear();
        lcd.print(equation);
        
      } else {
        int result = calc_result(equation);
        lcd.clear();
        lcd.print(result);
      }  
    }
  }

  // delete
  if (button3State == LOW) {
    
    // delete the last character in the equation string
    if (equation.length() > 1) {
      equation = equation.substring(0, equation.length());
      lcd.print(equation);
    } else {
      lcd.clear();
    }

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
  int op_index = -1;
  
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
        // get everything after the operator
        // store this as the current number and determine how to handle it, in relation to the running result
        curr_num = equation.substring(op_index+1,j).toInt();
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
    op_index = j;
    i = j;
  }
  return result;
}
   





