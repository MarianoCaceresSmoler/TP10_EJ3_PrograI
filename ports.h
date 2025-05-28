#ifndef PORTS_H_
#define PORTS_H_

#define PORT_A 'A'
#define PORT_B 'B'
#define PORT_D 'D'

void bitSet(char port, int bit); // Funcion para setear en 1 un bit

void bitClr(char port, int bit); // Funcion para setear en 0 un bit

int bitGet(char port, int bit); // Funcion que devuelve el valor de un bit

void bitToggle(char port, int bit); // Funcion que alterna el valor de un bit

void maskOn(char port, int mask); // Funcion que prende todos los bits que esten prendidos en la mascara

void maskOff(char port, int mask); // Funcion que apaga todos los bits que esten prendidos en la mascara

void maskToggle(char port, int mask); // Funcion que alterna todos los bits que esten prendidos en la mascara

#endif /* PORTS_H_ */
