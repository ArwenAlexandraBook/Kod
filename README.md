# class-project 
# AVR Mikrokontroller med LCD och ESP8266
Inbäddad Systemkod.
Detta projekt är avsett att användas med en AVR-mikrokontroller, en LCD-skärm och en ESP8266-modul för att skapa en användargränssnitt där användaren kan ange en fyrsiffrig kod och skicka data över Wi-Fi via ESP8266. Projektet är uppdelat i flera filer, var och en med en specifik uppgift.

## Innehållsförteckning
1. [Beskrivning](#beskrivning)
2. Huvudkomponenter
3. [Krav](#krav)
4. [Installation](#installation)
5. [Konfiguration](#konfiguration)
6. [Användning](#användning)
7. [Felsökning](#felsökning)
8. [Bidrag](#bidrag)
9. [Licens](#licens)
10.[C program](#C)

## Beskrivning
Det här projektet är en Inbäddad Systemkod. Koden är utformad för att köras på en AVR-mikrokontroller och interagerar med olika komponenter, inklusive knappar, en LCD-skärm och en ESP8266 Wi-Fi-modul.
Huvudkomponenter
AVR-bibliotek: Koden använder AVR-bibliotek för att interagera med mikrokontrollerens hårdvara. Viktiga bibliotek inkluderar:

avr/io.h: Används för att konfigurera och interagera med hårdvaran.
avr/interrupt.h: Innehåller funktioner för att hantera avbrott (interrupts).
util/delay.h: Erbjuder fördröjningsfunktioner för tidsstyrning.
LCD-gränssnitt: Koden styr en LCD-skärm med funktioner som lcd_init(), lcd_command() och lcd_puts(). Detta möjliggör visning av information på LCD-skärmen.

Hantering av knappar: Koden interagerar med flera knappar kopplade till mikrokontrollern. Den konfigurerar knapparna med interna pull-up-motstånd och registrerar knapptryckningar, vilket sparas i en datastruktur kallad buttonEvents.

ESP8266 Wi-Fi-modul: Koden innehåller funktioner för att interagera med en ESP8266 Wi-Fi-modul. Viktiga funktioner inkluderar:

ESPinit(): Initialiserar ESP8266-modulen.
addData() och pushData(): Används för att förbereda och skicka data till en fjärrserver, möjligtvis för IoT-dataöverföring.
ping(): Används för att kontrollera om ESP8266-modulen svarar.
Wi-Fi-konfiguration: Koden innehåller konfiguration för Wi-Fi SSID och lösenord, samt inställningar relaterade till ThingSpeak (IoT-plattform), inklusive API-nyckel och serverinformation. Koden försöker ansluta till ett Wi-Fi-nätverk med funktionen ConnectToWifi().

Setup- och Loop-funktioner: Funktionen setup() anropas under initialisering och konfigurerar knapparna och Wi-Fi-anslutningen. Funktionen loop() hanterar knapptryckningar och övervakar händelser.
## Krav
För att använda detta projekt behöver du följande komponenter:

- En AVR-mikrokontroller
- En LCD-skärm
- En ESP8266-modul
- Tillhörande kretsar, kablar och knappar

## Installation
1. Koppla och konfigurera dina mikrokontroller-, LCD- och ESP8266-moduler enligt din hårdvaru- och kopplingsspecifikation.
2. Ladda upp koden till din AVR-mikrokontroller med hjälp av din föredragna utvecklingsmiljö.
3. Säkerställ att du har rätt Wi-Fi-nätverksuppgifter konfigurerade i koden för att möjliggöra anslutning till ett nätverk.

## Konfiguration
I kodfilerna bör du se följande variabler som kan behöva konfigureras:

- `RED_BUTTON_PIN`, `YELLOW_BUTTON_PIN`, och `GREEN_BUTTON_PIN`: Ange GPIO-stiften som dina knappar är anslutna till.
- `wifiSSIDs` och `wifiPasswords`: Ange SSID och lösenord för de Wi-Fi-nätverk du vill ansluta till.
- Övriga konfigurationsparametrar som specifika pins eller inställningar som kan vara nödvändiga för din hårdvaru- och anslutningsuppsättning.

## Användning
1. När koden har laddats upp till din AVR-mikrokontroller bör du kunna mata in en fyrsiffrig kod med hjälp av dina knappar.
2. LCD-skärmen kommer att visa din inmatade kod och ge feedback om det är korrekt eller felaktigt.
3. ESP8266-modulen försöker ansluta till konfigurerade Wi-Fi-nätverk.

## Felsökning
Om du stöter på problem under användning, kan du överväga att kontrollera följande:

- Hårdvarukopplingar: Se till att dina kretsar är korrekt kopplade.
- Konfiguration: Dubbelkolla dina Wi-Fi-nätverksuppgifter och andra konfigurationsparametrar.
- Följ koden: Gå igenom kodfilerna steg för steg för att identifiera potentiella problemområden.

## Bidrag
Om du vill bidra till detta projekt eller förbättra koden, är du välkommen att skapa en "pull request" eller lämna feedback i projektets GitHub-repo (om det är tillgängligt). Detta projekt är avsett som ett exempel och kan anpassas och utvecklas ytterligare.

## Licens
Detta projekt levereras utan någon specifik licens. Om du vill använda eller distribuera koden bör du överväga att inkludera en lämplig licens som passar dina behov och skyddar ditt arbete.

---

_För mer information om hur du använder eller anpassar detta projekt, kolla in de specifika kodfilerna och referenser till AVR, LCD och ESP8266-dokumentation._
