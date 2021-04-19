#include <Servo.h>
#include<LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);	//connected to RS,EN,D4,D5,D6,D7 of LCD display respectively
Servo myservo;  					// create servo object to control a servo

#define ServoM 7        			//Connected to the servo motor.
#define Exit 9         				//Pin connected to the EXIT sensor.
#define In 8         				//Pin connected to the IN sensor.
#define Pwr 6           			//Extra power pin for sensors(Don't connect servo's power to this!)
#define Gnd 10          			//Extra groung pin for sensors(Don't connect servo's power to this!)
#define BarLow 90      				//Low position of the barrier.
#define BarUp 177       			//Up position of the barrier.
#define CAPACITY 7      			//Capacity of the parking lot.



void setup()
{
    myservo.attach(ServoM);          // attaches the servo.
    lcd.begin(16,2);
    lcd.print("Space left for");
    pinMode(Gnd, OUTPUT);
    pinMode(Pwr, OUTPUT);
    pinMode(Exit, INPUT);            // set "EXIT" sensor pin to input
    pinMode(In, INPUT);              // set "IN" sensor pin to input
    digitalWrite(Gnd, LOW);
    digitalWrite(Pwr, HIGH);
    myservo.write(BarLow);           //Barrier in the low position
  	//delay(1000);
}

int  Available= 7;                   // Number of places available.



void loop()
{
    if (Available == 1)
    {
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Space left for");
        lcd.setCursor(0,1);  
        lcd.print(Available);
        lcd.print(" car");
    }
    else
    {
        if (Available >= 1)
        {
            lcd.clear();
            lcd.setCursor(1,0);
            lcd.print("Space left for");
            lcd.setCursor(0,1);  
            lcd.print(Available);
            lcd.print(" cars");
        }
        else
        {
            lcd.clear();
            lcd.setCursor(1,0);
            lcd.print("Sorry!");
            lcd.setCursor(0,1);
            lcd.print("No place left!");
        }
    }

    if(digitalRead(In)==1)
    {
        if(Available != 0)
        {
            Available--;
            myservo.write(BarUp);
            delay(3000);
            myservo.write(BarLow);
        }
    }

    if(digitalRead(Exit)==1)
    {
        if(Available != CAPACITY)
        {
            Available++;
            myservo.write(BarUp);
            delay(3000);
            myservo.write(BarLow);
        }
    }

    delay(20);

}