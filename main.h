#define MAX_COMMAND_SIZE 6
#define MAX_OPT1_SIZE 6

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <iostream>




//TODO size must be set. spits segmentation fault otherwise.
//parameter name and value from the mainsvr side. Each parameter is given a char code and value is an int
struct paramMain{
	char paramName;
	unsigned int value;
};

char opt1[10];

void dispSplash(void);
void dispHelp(void);

int importExperiment(string fileName);
