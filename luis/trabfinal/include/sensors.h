
// SENSORS HEADER FOR THE QUANSER PROJECT
//
// Group members: 	Luís Miguel Santos Batista
//					Gabriel Stefaniak Niemiec
//					Nicolas Eymael da Silva

#pragma once

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <galileo2io.h>



int limitSwitch(int which_switch);

void setupDecoder();

void writeDecoder(char op, char data);

char readDecoder(char op);

int readDecoderCounter();

void resetDecoder();

void closeDecoder();

