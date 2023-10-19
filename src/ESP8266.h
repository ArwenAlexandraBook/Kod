#ifndef ESP8266_H
#define ESP8266_H

void esp8266_init(void);  //Initierar ESP8266
void waitFor (char* response); // Vänta på svar från ESP8266
void addData(char* name ,int data); // Lägga till data
void pushData(void); //Skicka data från ESP8266
void ping(void); // Testar anslutningen till ESP8266


#endif /*ESP8266_H*/
