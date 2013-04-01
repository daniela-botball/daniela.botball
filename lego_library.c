// Created on Sun March 10 2013

#define LEFT_MOTOR 1
#define RIGHT_MOTOR 3
#define FORWARDS 1
#define BACKWARDS -1
int centimeters_to_ticks(float centimeters);
void lego_stop();
void lego_drive(int speed, int direction);
int lego_drive_distance(float centimeters, int speed, int direction);

int main()
{
	//lego_drive_distance(10.0, 1000, FORWARDS);
	mav(RIGHT_MOTOR, 1000);
	mav(LEFT_MOTOR, 1000);
	msleep(2000);
	ao();
	//lego_drive_distance(10, 100, FORWARDS);
	return 0;
}

void lego_drive(int speed, int direction)
{
	mav(RIGHT_MOTOR, speed * direction);
	mav(LEFT_MOTOR, speed * direction);
}

int lego_drive_distance(float centimeters, int speed, int direction)
{
	clear_motor_position_counter(LEFT_MOTOR);
	int ticks = centimeters_to_ticks(centimeters);
	lego_drive(speed, direction);
	while (get_motor_position_counter(LEFT_MOTOR) < ticks);
	lego_stop();
	return 0; // FIXME
}

void lego_stop()
{
	off(RIGHT_MOTOR);
	off(LEFT_MOTOR);
}

int centimeters_to_ticks(float centimeters)
{
	
	float ticks_per_centimeter = 1050.0 / 8.0;
	float ticks = ticks_per_centimeter * centimeters;
	return (int) (ticks);
}
 
