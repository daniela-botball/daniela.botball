// Created on Tue March 19 2013

#define NUMBER_OF_BOOSTERS 3

void start_robot();
void move_to_booster_pack();
void center_on_booster_pack();
void pick_up_booster_pack();
void move_to_launch_pad();
void realign();
void extend_claw_arm();
void open_claw();

int main()
{
	start_robot(); // enables servos and waits for the starting light
	printf("moving to the first booster pack\n");
	move_to_booster_pack(); // moves to the first set of boosters in the launch area
	int loop_count; // variable that is used to count the number of times through the for loop used below
	for (loop_count = 0; loop_count < NUMBER_OF_BOOSTERS; loop_count++)
	{
		printf("centering on booster pack %d\n", loop_count++);
		center_on_booster_pack(); // centers the robot on a booster pack and moves the robot to an appropriate position to pick up the booster
		printf("picking up booster pack %d\n", loop_count++);
		pick_up_booster_pack(); // picks up the booster pack with the robot's claw
		printf("moving to launch pad\n");
		move_to_launch_pad(); // moves the robot to the second tallest launch pad
		printf("dropping booster pack %d on launch pad\n", loop_count++);
		drop_booster_on_launch_pad(); // extends the claw to the correct height and drops the booster pack on the launch pad
		printf("realigning the robot for next time through the loop\n");
		realign(); // moves the robot to the right corner of the launch area to make sure the create starts from the same place each time through the loop. It also retracts the claw.
	}
	return 0;
}

void drop_booster_on_launch_pad()
{
	extend_claw_arm(); // extends the arm that the claw is attached to
	open_claw(); // opens the claw
}
