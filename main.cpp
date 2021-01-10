#include <stdio.h>
#include "Train.h"
int main(int argc, char **argv)
{
    RegionalTrain t1=new RegionalTrain();
	printf(t1.getSpeed());
	return 0;
}
