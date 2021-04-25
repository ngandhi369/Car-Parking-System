#include <Servo.h> 			// Servo Motor Library
#include <LiquidCrystal.h> 		// LCD Library

LiquidCrystal lcd(12,11,5,4,3,2);	// Create LCD Object to connect LCD with 12,11,5,4,3,2 pins of arduino
Servo myservo;  			// Create servo object to control a servo

// Below are some variables which we have define

#define ServoM 7        		// Connection between 7 no. pin of arduino with servo motor.
#define Exit 9         			// Pin 9 of arduino connected to the EXIT push button sensor sensor.
#define In 8         			// Pin 8 connected to the IN push button sensor.
#define Pwr 6           		// Power pin for push button sensors
#define Gnd 10          		// Ground pin for push button sensors
#define BarLow 0      			// Low position of the servo motor which is 0 degree out of 360.
#define BarUp 180       		// Up position of the servo motor which is 180 degree out of 360
#define CAPACITY 7      		// Total Capacity of the parking lot.


void setup()
{
	
    Serial.begin(9600);			// Serial monitor starts

    myservo.attach(ServoM);         	// Attaches the servo motor with arduino 7 pin
    
    lcd.begin(16,2);			// That means LCD has 2 lines and each line have 16 characters
    lcd.print("Space left for");	// At the begining, we have to print this- it has 14 characters
    
    pinMode(Gnd, OUTPUT);		// pin 10(GND) to output
    pinMode(Pwr, OUTPUT);		// pin 6(PWR) to output
    pinMode(Exit, INPUT);            	// set "EXIT" sensor pin to input whether the car is exit or not
    pinMode(In, INPUT);              	// set "IN" sensor pin to input whether the car is enter or not
    
    digitalWrite(Gnd, LOW);		// 0 volt mean ground - write data given from the push buttons to GND
    digitalWrite(Pwr, HIGH);		// High means - 5v - write data given from the push buttons to PWR
    
    myservo.write(BarLow);           	// Servo motor's rotary actuator is on 0 degree at the begining.
}

int  Available=7;                   	// Number of places available at particular moment


void loop()
{
    if (Available >= 1)			// If there is only 1 place is avaliable then
    {
        lcd.clear();			// Clear the LCD
        lcd.setCursor(0,0);		// setCursor(col,row)
        lcd.print("Space left for");	// 
        lcd.setCursor(0,1);  		// Begining in the next row
        lcd.print(Available);		// Print available slot numbers
        lcd.print(" car");
    }
    else				// If there is 0 - no place is avaliable then
    {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Sorry!");
        lcd.setCursor(0,1);
        lcd.print("No place left!");
    }

    if(digitalRead(In)==1)		// If someone enters a car then
    {
        if(Available != 0)		// If parking slot is available then
        {
            Available--;		// Driver is allowed to park and total available slot is decreased by 1
            myservo.write(BarUp);	// Servo motor rotates with 180 degree
            delay(2000);		// It will take time for rotating servo motor
            myservo.write(BarLow);
        }
    }

    if(digitalRead(Exit)==1)		// If someone is exiting.
    {
        if(Available != CAPACITY)	// If available slot is not = to 7
        {
            Available++;		// then ++1 in total availablity
            myservo.write(BarUp);	// Rotate servo
            delay(2000);		// Delay
            myservo.write(BarLow);	// Low servo
        }
    }

    Serial.println(Available);		// Prints total available slot on serial monitor
	
    delay(20);

}
