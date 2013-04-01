// Created on Sun March 31 2013


#define GREEN 0
#define LARGEST_BLOB 0
point2 get_camera_reading();
void center_x(int min, int max);
void move_to_y(int y);

int main()
{
	center_x(0, 159);
	move_to_y(4);
	//get_camera_reading();
	return 0;
}

point2 get_camera_reading()
{
	point2 new;
	point2 old;
	int x;
	old.x = -1;
	old.y = -1;
	set_a_button_text("Done");
	set_b_button_text("Pause");
	set_c_button_text("Resume");
	printf("Press 'Done' when the pom is centered\n");
	msleep(1000);
	camera_open(LOW_RES);
	while (!a_button_clicked())
	{
		camera_update();
		x = get_object_count(GREEN);
		if (x > 0)
		{
			new = get_object_center(GREEN, LARGEST_BLOB);
			if (new.x != old.x || new.y != old.y)
			{
				printf("Largest blob at (%i, %i)\n", new.x, new.y);				
			}
			old = new;
		}
		else
		{
			printf("NO VISIBLE BLOB\n");
		}
		if (b_button_clicked())
		{
			while (1)
			{
				if (c_button_clicked())
				{
					break;
				}
				if (a_button_clicked())
				{
					display_clear();
					printf("Final position is (%i, %i)\n", new.x, new.y);
					return new;
				}
			}
		}
	}
	display_clear();
	printf("Final position is (%i, %i)\n", new.x, new.y);
	return new;
}

// 0 - 159 x
// 0 - 119 y
void center_x(int min, int max)
{
	int center_x = ((min + max) / 2) + .5;
	int center_of_blob;
	
	camera_open(LOW_RES);
	while (1)
	{
		camera_update();
		center_of_blob = get_object_center(GREEN, LARGEST_BLOB).x;
		printf("center of range , center of blob; %i, %i\n", center_x, center_of_blob);
		if(center_of_blob > center_x - 3 && center_of_blob < center_x + 3)
		{
			ao();
			printf("Robot is centered on blob\n");
			break;
		}
		if (center_of_blob < center_x - 3)
		{
			mav(0, -100);
			mav(1, 100);
			printf("TURNING LEFT\n");
		}
		if (center_of_blob > center_x + 3)
		{
			mav(0, 100);
			mav(1, -100);
			printf("TURNING RIGHT\n");
		}
	}
}

void move_to_y(int y)
{
	int center_of_blob;
	
	camera_open(LOW_RES);
	while (1)
	{
		camera_update();
		center_of_blob = get_object_center(GREEN, LARGEST_BLOB).y;
		printf("y, center of blob; %i, %i\n", y, center_of_blob);
		if(center_of_blob > y - 3 && center_of_blob < y + 3)
		{
			ao();
			printf("Robot is centered on blob\n");
			break;
		}
		if (center_of_blob < y - 3)
		{
			mav(0, 100);
			mav(1, 100);
			printf("FORWARDS\n");
		}
		if (center_of_blob > y + 3)
		{
			mav(0, -100);
			mav(1, -100);
			printf("BACKWARDS\n");
		}
	}
}
