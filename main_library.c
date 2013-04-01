// Created on Sun March 31 2013

void servo_booster(int servo_port, int motor_port, int servo_position, int motor_position);

int main()
{
	msleep(1000);
	set_servo_position(1, 442);
	set_servo_position(3, 233);
	enable_servos();
	msleep(5000);
	servo_booster(1, 0, 1500 , 250);
	msleep(5000);
	return 0;
}

void servo_booster(int servo_port, int motor_port, int servo_position, int motor_position)
{
	clear_motor_position_counter(motor_port);
	motor(motor_port, 100);
	set_servo_position(servo_port, servo_position);
	while (get_motor_position_counter(motor_port) < motor_position);
	off(motor_port);
}
