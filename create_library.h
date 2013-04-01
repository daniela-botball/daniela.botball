// Created: 2/22/2013

// #inlcudes go below

// #defines go below
#define write_byte create_write_byte
#define CBD create_block_done

#define CREATE_BUSY
#define CREATE_FREE

//#define get_high_byte(x) ((x & 0xFFFF) >> 8)
#define get_high_byte(x) ((x >> 8) & 0x00FF)
#define get_low_byte(x) (x & 0xFF)

#define PI 3.14159

#define FORWARDS 1
#define BACKWARDS -1
#define LEFT -1
#define RIGHT 1

#define DRIVE_DIRECT 145
#define DRIVE 137
#define WAIT_DISTANCE 156
#define WAIT_ANGLE 157
#define WAIT_TIME 155
#define SENSORS 142

#define PACKET_OI_MODE 35

void wait_duration(float seconds);
void _wait_degrees(int degrees);
void _wait_distance(int distance);
void create_drive(int speed, int direction);
void create_spin(int speed, int direction);
void create_halt();
void create_drive_distance(float centimeters, float speed, int direction);
void create_spin_degrees(int degrees, int speed, int direction);
void create_block_done();

/* SIMPLE MOVE FUNCTIONS */

void create_drive(int speed, int direction)
{
	CREATE_BUSY;
	write_byte(DRIVE_DIRECT);
	write_byte(get_high_byte(direction * speed));
	write_byte(get_low_byte(direction * speed));
	write_byte(get_high_byte(direction * speed));
	write_byte(get_low_byte(direction * speed));
	CREATE_FREE;
}

void create_spin(int speed, int direction)
{
	write_byte(DRIVE);
    write_byte(get_high_byte(speed));
	write_byte(get_low_byte(speed));
    if(direction < 0)
    {
        write_byte(255);
        write_byte(255);
    }
    if(direction > 0)
    {
        write_byte(0);
        write_byte(1);
    }
}

void create_halt()
{
	CREATE_BUSY;
	write_byte(DRIVE_DIRECT);
	write_byte(0);
	write_byte(0);
	write_byte(0);
	write_byte(0);
	CREATE_FREE;
}

/* ADVANCED MOVE FUNCTIONS */

// moves the create robot in a straight manner with a given distance in centimeters, speed in centimeters per second, and direction (FORWARDS or BACKWARDS) 
void create_drive_distance(float centimeters, float speed, int direction)
{
	int millimeters = (int) (centimeters * 10);
	create_drive(speed * 10, direction);
	_wait_distance(millimeters * direction);
	CBD();
}

void create_spin_degrees(int degrees, int speed, int direction)
{
	create_spin(speed, direction);
	_wait_degrees(direction * degrees);
}

/* WAIT FUNCTIONS */

void _wait_distance(int distance)
{
	CREATE_BUSY;
	write_byte(WAIT_DISTANCE);
	write_byte(get_high_byte(distance));
	write_byte(get_low_byte(distance));
	CREATE_FREE;
}

void _wait_degrees(int degrees)
{
	CREATE_BUSY;
	write_byte(WAIT_ANGLE);
	write_byte(get_high_byte(degrees));
	write_byte(get_low_byte(degrees));
	CREATE_FREE;
}

void wait_duration(float seconds) // SECONDS CAN BE NO LARGER THAN 255
{
	int mseconds = (int) (seconds * 10);
	CREATE_BUSY;
	write_byte(WAIT_TIME);
	write_byte(mseconds); // SECONDS SHOULD NOT BE SPLIT INTO A HIGH BYTE AND A LOW BYTE
	CREATE_FREE;
}

/* Other functions */

void create_block_done()
{
	char buffer[1];
	write_byte(SENSORS);
	write_byte(PACKET_OI_MODE);
	while (create_read_block(buffer, 1) == -1);
	//printf("create free\n");
}
