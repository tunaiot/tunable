/*
 * Project: Wand.cpp
 * Description: Libreria de wand version 0.1 con hardware v1
 * Author: Arturo Gasca
 * Date:  Junio-2017
 * Copyright: Tuna Shields
 */
#include "Arduino.h"
#include "TunaBle.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(11,10); //Rx,Tx
 
 void TunaBle::begin()
{
	DEBUG_PRINTLN("Tunable library start!");
	pinMode(relevador,OUTPUT);
  	pinMode(pin_reset,OUTPUT);
  	pinMode(pinConect,INPUT);
  	pinMode(boton,INPUT);
  	digitalWrite(pin_reset,HIGH); 
  	mySerial.begin(9600);
  	
}
bool TunaBle::disconnect()
{
	digitalWrite(pin_reset,LOW);
	delay(100);
	digitalWrite(pin_reset,HIGH);
}
void TunaBle::send(char *data){
	mySerial.print(data);
}
void TunaBle::write(char data){
	mySerial.write(data);
}
bool TunaBle::available(){
	return mySerial.available();
}

char TunaBle::read(){
	return mySerial.read();
}

 bool TunaBle::relay(bool status)
 {
 	if (status)
 	{
 		digitalWrite(relevador,HIGH);
 	}
 	else
 	{
 		digitalWrite(relevador,LOW);
 	}

 	return true;
 }

 void TunaBle::changeName(char *data){
 	disconnect();
 	delay(500);
 	mySerial.print("AT+NAME=");
 	mySerial.println(data);
 }

 bool TunaBle::relayStatus()
 {
 	if (digitalRead(relevador))
 	{
 		return true;
 	}
 	else
 	{
 		return false;
 	}
 }

bool TunaBle::button()
{
	if (digitalRead(boton))
	{
		delay(300);
		return true;
	}
	else
	{
		return false;
	}
}


bool TunaBle::waitConnection()
{
	bool conexion;
	bool ciclo = true;
	int contador = 0;
	DEBUG_PRINTLN("Check connection...");
	if (!digitalRead(pinConect))
	{
		conexion = false;
	}
	else
	{
		while(ciclo)
		{
			if (digitalRead(pinConect))
			{
				ciclo = true;
				contador++;
				delay(10);
				if (contador>=150)
				{
					ciclo = false;
					conexion = true;
				}
			}
			else
			{
				ciclo = false;
				conexion = false;
			}
		}
	

		
		/*DEBUG_PRINT("Contador: ");
		DEBUG_PRINTLN(contador);*/
	}
	return conexion;
}

float TunaBle::getCurrent(void)
{
	bool response;
	int sensorValue;
	sensorValue = analogRead(A7);

	DEBUG_PRINTLN("Check current...");
	DEBUG_PRINT("ADC: ");
	DEBUG_PRINTLN(sensorValue);
	//analogReference(EXTERNAL);
	float voltajeSensor = sensorValue*(5.0 / 1023.0);
	//float I = (voltajeSensor-2.5)/SENSIBILIDAD;
	float I = (voltajeSensor-currentStored)/SENSIBILIDAD;

	DEBUG_PRINT("Voltaje adc: ");
	DEBUG_PRINTLN(voltajeSensor);
	DEBUG_PRINT("Corriente calculada: ");
	DEBUG_PRINTLN(I);

	return I;
}
void TunaBle::saveCurrent(void)
{
	DEBUG_PRINTLN("Obetiendo muestras...");

	int sensorSample[SAMPLES];
	int sensorValue = 0;
	int averageValue = 0;
	for (int i = 0; i < SAMPLES; i++)
	{
		sensorSample[i] = analogRead(A7);
		sensorValue = sensorValue + sensorSample[i];
		delay(100);
	}
	averageValue = sensorValue / SAMPLES;

	DEBUG_PRINT("Valor ADC promedio : ");
	DEBUG_PRINTLN(averageValue);
	
	//Aqui guardamos en EEPROM
	adcStored = averageValue;
	currentStored = adcStored*(5.0 / 1023.0);
	//STORE_CURRENT_ADDRESS
	//EEPROMWritelong(STORE_CURRENT_ADDRESS,averageValue);
	
}

void TunaBle::calibration(void){
	TunaBle::saveCurrent();
	delay(500);
	DEBUG_PRINTLN("Calibracion lista");


	
}

/*void TunaBle::loadStoredCurrent(int tipo)
{
	if (tipo == 1)  //Guardada en eeprom
	{
		adcStored = EEPROMReadlong(STORE_CURRENT_ADDRESS);
		//Aqui leemos en eeprom adcStored = STORE_CURRENT_ADDRESS
		DEBUG_PRINT("adc leido de EE: ");
		DEBUG_PRINTLN(adcStored);
		currentStored = adcStored*(5.0 / 1023.0);
	}
	else if (tipo == 0)  //¨por default
	{
		currentStored = 2.5;
	}
	
}


*/

