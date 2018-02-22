/*
 * Project: tunable
 * Description: Libreria de tunable version 0.1 con hardware v1
 * Author: Arturo Gasca
 * Date:  Febrero-2018
 * Copyright: Tuna Shields
 */
#ifndef TunaBle_h
#define TunaBle_h
#include "Arduino.h"

#define DEBUG
#define relevador 	2
#define pin_reset 	12
#define pinConect	6
#define	boton		3
#define PASS_ADRRESS 			0
#define MODE_ADDRESS 			10
#define OWNER_ADDRESS 			20
#define STORE_CURRENT_ADDRESS 	11
#define SENSIBILIDAD 			0.100
#define SAMPLES					10
#define CORRIENTE_CORTE			0.3


#ifdef DEBUG
 #define DEBUG_PRINTLN(x)  Serial.println (x)
 #define DEBUG_PRINT(x)  Serial.print (x)
 #define DEBUG_PRINTHEX(x)  Serial.print (x,HEX)
 #define DEBUG_WRITE(x)  Serial.write (x)
#else
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINTLN(x)
 #define DEBUG_PRINTHEX(x)
 #define DEBUG_WRITE(x)
#endif
class TunaBle
{
	public:

		bool available();
		char read();
		void write(char data);
		void send(char *data);
		void changeName(char *data);
		void begin();
		bool relay(bool status);
		bool relayStatus();
		bool button();
		bool disconnect();
		bool waitConnection();
		float getCurrent();
		void saveCurrent();
		void loadStoredCurrent(int tipo);
		void TunaBle::calibration(void);
		unsigned char owner[10];
		
	private:
		float currentStored;
		int adcStored;

};
#endif
