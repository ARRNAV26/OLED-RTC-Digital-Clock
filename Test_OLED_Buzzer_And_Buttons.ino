//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Test OLED Buzzer and Buttons

//----------------------------------------Include Library
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//----------------------------------------

//----------------------------------------Configure OLED screen size in pixels
#define SCREEN_WIDTH 128 //--> OLED display width, in pixels
#define SCREEN_HEIGHT 64 //--> OLED display height, in pixels
//----------------------------------------

//----------------------------------------Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//----------------------------------------

byte btn_Menu_Select, btn_Up, btn_Down; //--> Variables for Buttons

byte Buzzer = 7; //--> Variable for Buzzer

bool Button_1;
bool Button_2;
bool Button_3;

//________________________________________________________________________void setup()
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //----------------------------------------Push-button configuration as INPUT
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  //----------------------------------------

  pinMode(Buzzer, OUTPUT); //--> Configure Buzzer as OUTPUT

  //----------------------------------------SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  // Address 0x3C for 128x32 and Address 0x3D for 128x64.
  // But on my 128x64 module the 0x3D address doesn't work. What works is the 0x3C address.
  // So please try which address works on your module.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); //--> Don't proceed, loop forever
  }
  //----------------------------------------
  
  //----------------------------------------Show initial display buffer contents on the screen
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000);
  //----------------------------------------
}
//________________________________________________________________________

//________________________________________________________________________void loop()
void loop() {
  read_button();
  
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.setCursor(0,0); //--> (x position, y position)
  display.print("Button 1 : ");
  Button_1 = btn_Menu_Select;
  if (Button_1 == LOW) {
    display.print("Pressed");
    Button_Sound(1);
  } else {
    display.print("UnPress");
  }

  display.setCursor(0,10); //--> (x position, y position)
  display.print("Button 2 : ");
  Button_2 = btn_Up;
  if (Button_2 == LOW) {
    display.print("Pressed");
    Button_Sound(1);
  } else {
    display.print("UnPress");
  }

  display.setCursor(0,20); //--> (x position, y position)
  display.print("Button 3 : ");
  Button_3 = btn_Down;
  if (Button_3 == LOW) {
    display.print("Pressed");
    Button_Sound(1);
  } else {
    display.print("UnPress");
  }

  if (Button_1 == HIGH && Button_2 == HIGH && Button_3 == HIGH) {
    Button_Sound(0);
  }

  display.setCursor(0,55); //--> (x position, y position)
  display.print("Buzzer : ");
  int Buzzer_Stat = digitalRead(Buzzer);
  if (Buzzer_Stat == 1) {
    display.print("On");
  } else {
    display.print("Off");
  }
  
  display.display();
  delay(100);
}
//________________________________________________________________________

//________________________________________________________________________Subroutines for reading Buttons
void read_button() {
  btn_Menu_Select = digitalRead(4);
  btn_Up = digitalRead(5);
  btn_Down = digitalRead(6);
}
//________________________________________________________________________

//________________________________________________________________________Subroutines to turn the Buzzer on or off
void Button_Sound(byte snd) {
  digitalWrite(Buzzer, snd);
}
//________________________________________________________________________

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

