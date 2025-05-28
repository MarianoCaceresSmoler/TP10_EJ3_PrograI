#include "ports.h"
#include <stdio.h>

#define BIT_CHECK(b) (((b) >= 0) && ((b) <= 15))
#define PORT_CHECK(p) (((p) == PORT_A) || ((p) == PORT_B) || ((p) == PORT_D))
#define BIT_ERROR_MESSAGE "Wrong port number"
#define PORT_ERROR_MESSAGE "Port is not defined"

typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;

// Estructura de union para espacio de memoria de los puertos
typedef union
{
	struct
	{
		uint8_t portB;
		uint8_t portA;
	};
	uint16_t portD;
} ports_t;

static ports_t ports; // Inicializa la variable estatica para los puertos

// Prototipos de funciones privadas para escribir y leer un puerto
static void writePort(char port, uint16_t value); // Funcion que escribe sobre un puerto
static uint16_t getPort(char port); // Funcion que devuelve el valor de un puerto

// EN CADA FUNCION, SE REVISA QUE EL PUERTO (PORT_CHECK) Y/O EL BIT (BIT_CHECK) DADOS A LAS FUNCIONES SEAN VALIDOS
// PRINTEA MENSAJES DE ERROR EN CASO DE RECIBIR DATOS INVALIDOS

void bitSet(char port, int bit)
{
	uint16_t portValue;

	if(PORT_CHECK(port))
	{
		portValue = getPort(port);

		if(BIT_CHECK(bit))
		{
			portValue = portValue | (1<<bit);
			writePort(port, portValue);
		}
		else
		{
			printf(BIT_ERROR_MESSAGE);
		}

	}
	else{
		printf(PORT_ERROR_MESSAGE);
	}

}

void bitClr(char port, int bit)
{

	uint16_t portValue;

	if(PORT_CHECK(port))
	{
		portValue = getPort(port);

		if(BIT_CHECK(bit))
		{
			portValue = portValue & (~(1<<bit));
			writePort(port, portValue);
		}
		else
		{
			printf(BIT_ERROR_MESSAGE);
		}
	}
	else
	{
		printf(PORT_ERROR_MESSAGE);
	}

}

int bitGet(char port, int bit)
{
	char bitValue;
	uint16_t portValue;

	if(PORT_CHECK(port))
	{
		portValue = getPort(port);

		if(BIT_CHECK(bit))
		{
			bitValue = ((portValue & (1<<bit)) != 0);
		}
		else
		{
			printf(BIT_ERROR_MESSAGE);
		}
	}
	else
	{
		printf(PORT_ERROR_MESSAGE);
		return 0;
	}

	return bitValue;
}

void bitToggle(char port, int bit)
{
	uint16_t portValue;

	if(PORT_CHECK(port))
	{
		portValue = getPort(port);

		if(BIT_CHECK(bit))
		{
			portValue = portValue ^ (1<<bit);
			writePort(port, portValue);
		}
		else
		{
			printf(BIT_ERROR_MESSAGE);
		}
	}
	else
	{
		printf(PORT_ERROR_MESSAGE);
	}

}

void maskOn(char port, int mask)
{
	uint16_t portValue;

	if(PORT_CHECK(port))
	{
		portValue = getPort(port);
		portValue = portValue | mask;
		writePort(port, portValue);
	}
	else
	{
		printf(PORT_ERROR_MESSAGE);
	}

}

void maskOff(char port, int mask)
{
	uint16_t portValue;

	if(PORT_CHECK(port))
	{
		portValue = getPort(port);
		portValue = portValue & (~mask);
		writePort(port, portValue);
	}
	else
	{
		printf(PORT_ERROR_MESSAGE);
	}

}

void maskToggle(char port, int mask)
{
	uint16_t portValue;

	if(PORT_CHECK(port))
	{
		portValue = getPort(port);
		portValue = portValue ^ mask;
		writePort(port, portValue);
	}
	else
	{
		printf(PORT_ERROR_MESSAGE);
	}

}

static uint16_t getPort(char port)
{
	uint16_t value;

	switch(port)
	{
	case PORT_A:
		value = (uint16_t) ports.portA;
		break;
	case PORT_B:
		value = (uint16_t) ports.portB;
		break;
	case PORT_D:
		value = ports.portD;
		break;
	default:
		printf(PORT_ERROR_MESSAGE);
		value = 0;
		break;
	}

	return value;
}

static void writePort(char port, uint16_t value)
{
	switch(port)
	{
	case PORT_A:
		ports.portA = (uint8_t) value;
		break;
	case PORT_B:
		ports.portB = (uint8_t) value;
		break;
	case PORT_D:
		ports.portD = value;
		break;
	default:
		printf(PORT_ERROR_MESSAGE);
		break;
	}
}



