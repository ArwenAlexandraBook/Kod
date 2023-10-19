
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "ESP8266.h"

#define RED_BUTTON_PIN 2    // Röda knappens pin
#define YELLOW_BUTTON_PIN 4 // Gula knappens pin
#define GREEN_BUTTON_PIN 5  // Gröna knappens pin

const int buttonPin[] = {RED_BUTTON_PIN, YELLOW_BUTTON_PIN, GREEN_BUTTON_PIN};
const int numButton = sizeof(buttonPin) / sizeof(buttonPin[0]);

char currentText[5] = {0};
char questionText[20] = " "; 

// Specificerar SSID och lösenord för lokala wifinätverk

const char *wifiSSIDs[] = {"SSID1"}; //Det SSID man använder. 
const char *wifiPassWords[] = {"Password1"}; //Lösenord till wifi
const int numNetworks = sizeof(wifiSSIDs) /sizeof(wifiSSIDs[0]);

struct ButtonEvent
{

 int button;
 unsigned long timestamp;
};

struct ButtonEvent buttonEvents[60];
int numEvents = 0;

bool ConnectToWifi(const char *ssid, const char *password)
{
wifi_set_opmode(STATION_MODE);

struct station_config stationConf;
memset(&statonConf, 0, sizeof(struct station_config));
strcpy(stationConf.ssid,wifiSSID[0]);  // Ange det wifi man ska logga in på.
strcpy(stationConf.password,wifiPassWord[0]); //Ange lösenord

wifi_station_set_config(&stationConf);
wifi_station_connect();


int timeout = 10000; // 10 sekunders väntan på om anslutningen till wifi lyckas
while (wifi_station_get_connect_status()! = STATION_GOT_IP && timeout > 0)
{
    _delay_us(100000); 
    timeout -=1000;
}

if (wifi_station_get_connect_status() === STATION_GOT_IP)
{
 return true;
}
else 
{
    return false;
}
}
void HandleButtonClick(char *txt)
{
    _delay_us(200000); //Förfröjning mikrosekunder
    strncat(currentText, txt, sizeof(currentText) - strlen(currentText) - 1);
    lcd_set_cursor(0, 1);
    lcd_puts(currentText);

    if (strlen(currentText) == 4)
    {
        if (strcmp("1442", currentText) == 0)
        {
            lcd_printf("That's correct!");
        }
        else
        {
            lcd_printf("Incorrct code!"); // Felmeddelande
            _delay_us(300000); //Fördröjning i mikrosekunder
            lcd_set_cursor(0, 1); // LCD-cursor rad 1
            lcd_puts("  "); //Rensar raden
            lcd_set_cursor(0, 1); //Återgår till rad 1
        }
        currentText[0] = 0;
    }
}

void ConnectToWiFiNetworks()
{

for (int i = 0; i < numNetworks;i++)  //Söker efter tillgänliga nätverk.
{
    if (ConnectToWifi(wifiSSIDs[i], wifiPassWords[i]))
    {

        break;
    }
}

}

void setup()
{
    for (int i = 0; i < numButton; i++)
    {
        pinMode(buttonPin[i], INPUT_PULLUP);
    }

    lcd_init();            // Initialiserar LCD
    lcd_enable_blinking(); // Aktiverar blink
    lcd_enable_cursor();   // Aktiverar cursor

    lcd_set_cursor(0, 0);   // LCD-cursor rad 0
    lcd_puts(questionText); // Frågan visas på lcd skärmen

    ConnectToWifiNetworks();
}

void loop()
{

    for (int i = 0; i < numButton; i++)
    {
        if (digitalRead(buttonPin[i]) == LOW)
        {

            if (numEvents < sizeof(buttonEvents) / sizeof(buttonEvents[0]))
            {
                buttonEvents[numEvents].button = i;
            buttonEvents[numEvents].timestamp = millis();
            numEvents++;
        }
    }
}
}
