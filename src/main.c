
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "millis.h"
#include "lcd.h"
#include "ESP8266.h"

#define BIT_SET(a,b) ((a) |=(1ULL <<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a)^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!(a) &(1ULL<<(b)))

#define Set_Button_As_Input_Pullup(ddr,pdr,pin) BIT_CLEAR(ddr,pin);BIT_SET(pdr,pin);
#define Button_is_Clicked(pinr, pin) !BIT_CHECK(pinr,pin)

// B (digital pin 8 to 13)
// C (analog input pins)
// D (digital pins 0 to 7)
//https://wokwiki.com/projects/365067824797777921

#define RED_BUTTON_PIN_1 1    // Röda knappens pin
#define YELLOW_BUTTON_PIN_2 2 // Gula knappens pin
#define GREEN_BUTTON_PIN_3 3  // Gröna knappens pin

const int buttonPin[] = {RED_BUTTON_PIN_1, YELLOW_BUTTON_PIN_2, GREEN_BUTTON_PIN_3};
const int numButton = sizeof(buttonPin) / sizeof(buttonPin[0]);

char currentText[5] = {0};
char questionText[20] = " "; 

// Specificerar SSID och lösenord för lokala wifinätverk

const char *wifiSSID[] = {"SSID1"}; //Det SSID man använder. 
const char *wifiPassWord[] = {"Password1"}; //Lösenord till wifi
const int numNetwork = sizeof(wifiSSID) /sizeof(wifiSSID[0]);

struct ButtonEvent
{

 int button;
 unsigned long timestamp;
};

struct ButtonEvent buttonEvents[60];
int numEvents = 0;

void HandleButtonClick(char *txt)
{
    _delay_ms(20); //Förfröjning mikrosekunder
    strncat(currentText, txt);
    lcd_set_cursor(0, 1);
    lcd_puts(currentText);
    return;

    if (strlen(currentText) == 4)
    {
        if (!strcmp("1442", currentText))
        {
            lcd_printf("That's correct!");
        }
        else
        {
            lcd_printf("Incorrct code!"); // Felmeddelande
            _delay_ms(30); //Fördröjning i mikrosekunder
            lcd_set_cursor(0, 1); // LCD-cursor rad 1
            lcd_puts("  "); //Rensar raden
            lcd_set_cursor(0, 1); //Återgår till rad 1
        }
        currentText[0] = 0;
    }
}


int main(void)
{
    
   lcd_init();
   lcd_enable_blinking();
   lcd_enable_cursor();
   _delay_ms(10);


   Set_Button_As_Input_Pullup (DDRB, PORTB, RED_BUTTON_PIN_1);
   Set_Button_As_Input_Pullup (DDRB, PORTB, YELLOW_BUTTON_PIN_2);
   Set_Button_As_Input_Pullup (DDRB, PORTB, GREEN_BUTTON_PIN_3); 

while (1)
{
 if (Button_Is_Clicked(PINB, RED_BUTTON_PIN_1))
 {
    HandleButtonClick(1);
 }
 else if (Button_Is_Clicked(PINB, YELLOW_BUTTON_PIN_2))
 {
    HandleButtonClick(2);
 }
 else if (Button_Is_Clicked(PINB, GREEN_BUTTON_PIN_3)) 
 {
    HandleButtonClick(3);
 }
}
return 0;
}
