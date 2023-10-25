#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util/delay.h"
#include "uart.h"
#include "ESP8266.h"

#define _OK "OK"
#define _CONNECT "CONNECT"
#define _CLOSE "CLOSE"


char ssid[] = "Wokwi-GUEST";
char psk[] ="";  //Inget lösenord.
char api_key[] = "32UCVEN8HC19WGQM"; //ThingSpeak API-nyckel (inget upplagt än!)
int port = 80;
char buffer[64];
char HTTP[512];
int dataCount = 0; 

//Funktion som initerar ESP8266

void ESPinit(void)
{
    
    lcd_puts("Connect to wifi");
    lcd_set_cursor(0, 1);
    printf("AT+RST\r\n");
    lcd_set_cursor (0,1);
    ping();

    printf("AT+CWJAP=\"%s\",\"%s\"\r\n",ssid,psk);
    ping();

    printf("AT+CWMODE=1\r\n");

    ping();
    //waitFor(_OK);

    printf("AT+CIPMUX=1\r\n");
    ping();
    //WaitFor(_OK);
    
    _delay_ms(500); 

}


void waitFor(char* response)
{
 while(1) {
    memset(buffer,0,strlen(buffer)); 
    scanf("\n%s",buffer);   //Få meddelande från ESP8266
    if (strstr(buffer,response)  == NULL)
    {
        _delay_ms(500); //Fördröjning i mikrosekunder
    } else break;
 }

}

void addData(char* name, int data) {
    if (dataCount == 0) 
    {
        strcat(HTTP, "GET https://api.thingspeak.com/update?api_key=");
        strcat(HTTP,api_key);
    }
    strcat(HTTP, "&");
    strcat(HTTP, name);
    strcat(HTTP, "=");
    memset(buffer, 0,strlen(buffer));
    itoa(data,buffer,10); //Omvandlar heltal till sträng
    strcat(HTTP,buffer);
    dataCount++;
}

void pushData(void) {

    //Kolla omm ESP8266 är redo att skicka
    printf("AT+CIPSTART=0,\"TCP\",\"api.thingspeak.com\",%d\r\n",port);
    ping();
    //WaitFor(_OK);

    //Använd kanal 0 och definiera längden på message
    printf("AT+CIPSEND_0,%d\r\n", strlen(HTTP)+34); //Längden är 34
    _delay_ms(1000);
    //ping();
    //waitFor(_OK);
    //WaitFor(_OK);

    //Skicka HTTP request med data 
    printf("%s\nHTTP/1.1 Host: api.thingspeak.com\r\n",HTTP);

    //Vänta på att mottagningen ska stängas
    ping();
    // waitFor(_CLOSED);
    printf("Data sent\n");

    //Reset HTTP array and close connection to be sure
    printf ("AT+CIPCLOSE=0\r\n");
    memset(HTTP,0,strlen(HTTP));
    dataCount=0;
}

void ping(void)
{
    //Kolla om ESP8266 svarar
    for(int i = 0; i < 3;i++) {
        printf("AT\r\n");
        memset(buffer,0,strlen(buffer));
        scanf("%ns", buffer);
        if (strstr(buffer,"OK") == NULL)
    {
           _delay_ms(1000);

        } else break;
        }
}




