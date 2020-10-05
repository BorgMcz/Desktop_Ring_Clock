/* 
 *   BorgMcz  http://www.dccmm.cz
 * * ESP32 ring clock NEOPIXEL
 *   fork to https://github.com/ancalex/Desktop_Ring_Clock
 * 
 *
 * Add: 	- button reset default config
 * 			- dislpay second to time
 *			- light sensor 
 *			- set color to full LED
 * 			- add button to default config or set light
 */
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#include "FastLED.h"					// https://github.com/FastLED/FastLED
#define LED_TYPE NEOPIXEL
//#define COLOR_ORDER GRB
#define LED_PIN 21
#define NUM_LEDS  108
CRGB leds[NUM_LEDS];
byte RING_LEDS[] = {30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
byte RING_LEDH[] = {84, 88, 92, 96, 100, 104, 60, 64, 68, 72, 76, 80};
//					v0	1	2	v3	 4	5  v6  7  8  v9  10	 11
byte RING_LEDF[] = {84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 
					60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83};
unsigned int BRIGHTNESS = 20;
byte temp_second = 0;
#define DEFAULT_PIN 22
#define FOTO_PIN 33
#include <WiFi.h>
#include <ESP32WebServer.h>				// https://github.com/Pedroalbuquerque/ESP32WebServer
#include <WiFiUdp.h>
#include <Ticker.h>
#include <EEPROM.h>
#include "global.h"
#include "NTP.h"

#include <RBD_Timer.h>          // Arduino Timer Library v1.2.0, by Alex Taujenis - https://github.com/alextaujenis/RBD_Timer
#include <RBD_Button.h>         // Arduino RBD Button Library Example v2.1.0, by Alex Taujenis - https://github.com/alextaujenis/RBD_Button
RBD::Button buttonMode(DEFAULT_PIN);     // mode setings

// Include STYLE and Script "Pages"
#include "Page_Script.js.h"
#include "Page_Style.css.h"

// Include HTML "Pages"
#include "Page_Admin.h"
#include "Page_NTPSettings.h"
#include "Page_Information.h"
#include "Page_NetworkConfiguration.h"
#include "Page_SetTime.h"

//extern "C" {
//#include "user_interface.h"
//}

void setup() {
	Serial.begin(115200);
	pinMode(DEFAULT_PIN, INPUT_PULLUP);			// defaul setings pins (reset config)
	// tell FastLED about the LED strip configuration
	FastLED.addLeds<LED_TYPE, LED_PIN >(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
	FastLED.setBrightness(BRIGHTNESS);
	   // limit my draw to 1A at 5v of power draw
	FastLED.setMaxPowerInVoltsAndMilliamps(5,400); 
	Serial.println("FastLed Setup done ... waiting..");
	delay(2000);

	//**** Network Config load
	EEPROM.begin(512); // define an EEPROM space of 512Bytes to store data
	CFG_saved = ReadConfig();
	if (digitalRead(DEFAULT_PIN) == 0) {						// reset config data to default
		CFG_saved = false;
		rotring();
	}

	//  Connect to WiFi acess point or start as Acess point
	if (CFG_saved)  //if no configuration yet saved, load defaults
	{
		// Connect the ESP8266 to local WIFI network in Station mode
		Serial.println("Booting");
		//printConfig();
		WiFi.mode(WIFI_STA);
		WiFi.begin(config.ssid.c_str(), config.password.c_str());
		WIFI_connected = WiFi.waitForConnectResult();
		if (WIFI_connected != WL_CONNECTED)
			Serial.println("Connection Failed! activating the AP mode...");

		Serial.print("Wifi ip:");
		Serial.println(WiFi.localIP());
	}

	if ((WIFI_connected != WL_CONNECTED) or !CFG_saved) {
		// DEFAULT CONFIG
		Serial.println("Setting AP mode default parameters");
		config.ssid = "RingClock-config"; // SSID of access point
		config.password = "";   // password of access point
		config.dhcp = true;
		config.IP[0] = 192;
		config.IP[1] = 168;
		config.IP[2] = 1;
		config.IP[3] = 100;
		config.Netmask[0] = 255;
		config.Netmask[1] = 255;
		config.Netmask[2] = 255;
		config.Netmask[3] = 0;
		config.Gateway[0] = 192;
		config.Gateway[1] = 168;
		config.Gateway[2] = 1;
		config.Gateway[3] = 254;
		config.DeviceName = "Ring Clock";
		config.ntpServerName = "0.europe.pool.ntp.org"; // to be adjusted to PT ntp.ist.utl.pt
		config.Update_Time_Via_NTP_Every = 3;
		config.timeZone = 20;
		config.isDayLightSaving = true;
		config.displaySec = true;
		config.displaySecStart = 0;
		config.displaySecStop = 24;
		config.brightnessMin = 10;
		config.brightnessMax = 80;
		config.colorSecPrint = 0x4169E1;
		config.colorMinPrint = 0x6A5ACD;
		config.colorHourPrint = 0xD62505;
		config.colorCif1Print = 0xFFF238;
		config.colorCif2Print = 0xBFCB1A;
		config.colorLight = 0xF0F0F0;
		config.colorLightBr = 200;
		config.colorLightTm = 5;		
		//WriteConfig();
		WiFi.mode(WIFI_AP);
		WiFi.softAP(config.ssid.c_str(),"admin1234");
		Serial.print("Wifi ip:");
		Serial.println(WiFi.softAPIP());
	}

	// Start HTTP Server for configuration
	server.on("/", []() {
		Serial.println("admin.html");
		server.send_P ( 200, "text/html", PAGE_AdminMainPage); // const char top of page
	});

/*
	server.on("/favicon.ico", []() {
		Serial.println("favicon.ico");
		server.send( 200, "text/html", "" );
	});
*/	
	// Network config
	server.on("/config.html", send_network_configuration_html);
	// Info Page
	server.on("/info.html", []() {
		Serial.println("info.html");
		Information_Page();
		
	});
	server.on("/ntp.html", send_NTP_configuration_html);
	server.on("/time.html", send_Time_Set_html);
	server.on("/style.css", []() {
		Serial.println("style.css");
		server.send_P ( 200, "text/plain", PAGE_Style_css );
	});
	server.on("/microajax.js", []() {
		Serial.println("microajax.js");
		server.send_P ( 200, "text/plain", PAGE_microajax_js );
	});
	server.on("/admin/values", send_network_configuration_values_html);
	server.on("/admin/connectionstate", send_connection_state_values_html);
	server.on("/admin/infovalues", send_information_values_html);
	server.on("/admin/ntpvalues", send_NTP_configuration_values_html);
	server.on("/admin/timevalues", send_Time_Set_values_html);
	server.onNotFound([]() {
		Serial.println("Page Not Found");
		server.send ( 400, "text/html", "Page not Found" );
	});
	server.begin();
	Serial.println("HTTP server started");

	printConfig();
	delay (1000);
	buttonMode.onPressed();
	// start internal time update ISR
	tkSecond.attach(1, ISRsecondTick);

	// start internal time update ISR
	tkSecond.attach(1, ISRsecondTick);
	
}

// the loop function runs over and over again forever
void loop() {
	server.handleClient();
	if (config.Update_Time_Via_NTP_Every > 0) {
		if (cNTP_Update > 5 && firstStart) {
			getNTPtime();
			delay(2000); //wait for DateTime
			cNTP_Update = 0;
			firstStart = false;
		}
		else if (cNTP_Update > (config.Update_Time_Via_NTP_Every * 60)) {
			getNTPtime();
			cNTP_Update = 0;
		}
	}
	//  feed de DOG :)
	customWatchdog = millis();
  if (white_light_on == false) {      					// test light on
	//============================
	if (WIFI_connected != WL_CONNECTED and manual_time_set == false) {
		config.Update_Time_Via_NTP_Every = 0;
		//display_animation_no_wifi
		softtwinkles();
		FastLED.show();
	} else if (ntp_response_ok == false and manual_time_set == false) {
		config.Update_Time_Via_NTP_Every = 1;
		//display_animation_no_ntp
		pride();
		FastLED.show();
	} else if (ntp_response_ok == true or manual_time_set == true) {
		if (temp_second != DateTime.second) {
			temp_second = DateTime.second;
			timeDisplay(DateTime.hour, DateTime.minute, DateTime.second);
			FastLED.show();
		}
	}
	// test button
	if (buttonMode.onPressed()) {
		whiteringon();
		white_light_on = true;
		white_light_timer = (millis() + (60000 * config.colorLightTm));
	}
  } else {
	// test button and time light
	if (buttonMode.onPressed() || (millis() > white_light_timer)) {	
		white_light_on = false;
		whiteringoff();
		timeDisplay(DateTime.hour, DateTime.minute, DateTime.second);
		FastLED.show();
	}
  }
}

void timeDisplay(byte h, byte m, byte s) {

	int y = map(analogRead(FOTO_PIN), 300, 4095, config.brightnessMin, config.brightnessMax);
	FastLED.setBrightness(y);
	
	//minute dial
	fill_solid( leds, NUM_LEDS, CRGB(0,0,0));    // clear leds
	byte h24 = h;
	if (h > 11) {h = h - 12;}
	//	hour dials
	for (int i = 0; i < 60; i += 5) {
		leds[RING_LEDS[i]] = config.colorCif2Print;
	}
	for (int i = 0; i < 60; i += 15) {
		leds[RING_LEDS[i]] = config.colorCif1Print;
	}
	for (int i = 0; i < 12; i += 3) {
		leds[RING_LEDH[i]] = config.colorCif1Print;
	}
	
	//time
	//hour
	leds[RING_LEDH[h]] = config.colorHourPrint;

	//minute
	leds[RING_LEDS[m]] = config.colorMinPrint;
	//second
	if (config.displaySec) {
		if ((h24 >= config.displaySecStart) && (h24 < config.displaySecStop)) {
			leds[RING_LEDS[s]] = config.colorSecPrint;
		}
	}
}

void pride()
{
	static uint16_t sPseudotime = 0;
	static uint16_t sLastMillis = 0;
	static uint16_t sHue16 = 0;

	uint8_t sat8 = beatsin88( 87, 220, 250);
	uint8_t brightdepth = beatsin88( 341, 96, 224);
	uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
	uint8_t msmultiplier = beatsin88(147, 23, 60);

	uint16_t hue16 = sHue16;//gHue * 256;
	uint16_t hueinc16 = beatsin88(113, 1, 3000);

	uint16_t ms = millis();
	uint16_t deltams = ms - sLastMillis ;
	sLastMillis  = ms;
	sPseudotime += deltams * msmultiplier;
	sHue16 += deltams * beatsin88( 400, 5,9);
	uint16_t brightnesstheta16 = sPseudotime;

	for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
		hue16 += hueinc16;
		uint8_t hue8 = hue16 / 256;

		brightnesstheta16  += brightnessthetainc16;
		uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

		uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
		uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
		bri8 += (255 - brightdepth);

		CRGB newcolor = CHSV( hue8, sat8, bri8);

		uint16_t pixelnumber = i;
		pixelnumber = (NUM_LEDS-1) - pixelnumber;

		nblend( leds[pixelnumber], newcolor, 64);
	}
}

//code from https://gist.github.com/kriegsman/99082f66a726bdff7776
const CRGB lightcolor(8,5,1);

void softtwinkles() {
	for( int i = 0; i < NUM_LEDS; i++) {
		if( !leds[i]) continue; // skip black pixels
		if( leds[i].r & 1) { // is red odd?
			leds[i] -= lightcolor; // darken if red is odd
		} else {
			leds[i] += lightcolor; // brighten if red is even
		}
	}
	// Randomly choose a pixel, and if it's black, 'bump' it up a little.
	// Since it will now have an EVEN red component, it will start getting
	// brighter over time.
	if( random8() < 40) {
		int j = random16(NUM_LEDS);
		if( !leds[j] ) leds[j] = lightcolor;
	}
}

void rotring() {
	for (int i = 0; i < 48; i++) {
		leds[RING_LEDH[i]] = CRGB::Red;
		FastLED.show();
		delay(20);
	}	
}
void whiteringon() {
	FastLED.setBrightness(config.colorLightBr);
	for (int i = 0; i < 48; i++) {
		leds[RING_LEDF[i]] = config.colorLight;
		FastLED.show();
		delay(10);
	}	
	for (int i = 0; i < 60; i++) {
		leds[RING_LEDS[i]] = config.colorLight;
		FastLED.show();
		delay(10);		
		
	}	
}

void whiteringoff() {
	int x = 47;
	for (int i = 0; i < 48; i++) {
		x--;
		leds[RING_LEDF[x]] = 0x000000;
		FastLED.show();
		delay(20);
	}	
	x = 59;
	for (int i = 0; i < 60; i++) {
		x--;
		leds[RING_LEDS[x]] = 0x000000;
		FastLED.show();
		delay(20);		
	}	
}
