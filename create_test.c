// Created on Thu February 21 2013
#include "create_library.h"

int get_pot_reading(int port, int min, int max);

int main()
{
	create_connect();
	create_full();
	float sec = seconds();
	set_create_distance(0);
	create_drive_distance(50, get_pot_reading(1, 1, 50), FORWARDS);
	printf("distance traveled = %i, time = %f\n", get_create_distance(), seconds() - sec);
	//sleep(2);
	//create_spin_degrees(90, 300, LEFT);
	//printf("%d\n", i);
	create_disconnect();
	return 0;
}

int get_pot_reading(int port, int min, int max)
{
	int pot_reading;
	int actual_reading;
	int previous_reading = -1;
	while (1)
	{
		pot_reading = analog10(port);
		actual_reading = (pot_reading / 1023.0) * (max - min) + min + 0.5;
		if (actual_reading != previous_reading)
		{
			printf("%i\n", actual_reading);
		}
		previous_reading = actual_reading;
		if (a_button_clicked())
		{
			msleep(500);
			return actual_reading;
		}
	}
	
	
}
