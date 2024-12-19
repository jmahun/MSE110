#pragma config(Sensor, S1,     TouchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     UltrasonicSensor, sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          RightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorA,          LeftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)


const int length_grid = 490;
const int right_turn = 186;
const int left_turn = 186;
const int wall_dist = 10;
const int straight_speed = 30;
const int right_left_speed = 40;




typedef enum Direction {
	NONE_DIRECTION,
	NORTH,
	EAST,
	SOUTH,
	WEST
} Direction;

typedef struct {
	unsigned int x;
	unsigned int y;
} Location;


void directionToString(Direction l, string* s);
Direction check_opposite_direction(Direction d);
Direction getDirectionLeft(Direction d);
Direction getDirectionRight(Direction d);

void setLocation(Location* l, unsigned int x, unsigned int y);
bool equals(Location l1, Location l2);
unsigned int check_x(Location l, Direction d);
unsigned int check_y(Location l, Direction d);


void directionToString(Direction l, string* s) {
	switch(l) {
		case NORTH:
			*s = "NORTH";
			break;
		case WEST:
			*s = "WEST";
			break;
		case SOUTH:
			*s = "SOUTH";
			break;
		case EAST:
			*s = "EAST";
			break;
		default:
		  *s = "";
	}
}

Direction check_opposite_direction(Direction d) {
	if(d == NORTH) return SOUTH;
	else if(d == SOUTH) return NORTH;
	else if(d == EAST) return WEST;
	else if(d == WEST) return EAST;
	else return NONE_DIRECTION;

	switch(d) {
		case NORTH:
			return SOUTH;
		case EAST:
			return WEST;
		case SOUTH:
			return NORTH;
		case WEST:
			return EAST;
		default:
			return NONE_DIRECTION;
	}
}

Direction getDirectionLeft(Direction d) {
	switch(d) {
		case NORTH:
			return WEST;
		case WEST:
			return SOUTH;
		case SOUTH:
			return EAST;
		case EAST:
			return NORTH;
		default:
			return NONE_DIRECTION;
	}
}

Direction getDirectionRight(Direction d) {
	switch(d) {
		case NORTH:
			return EAST;
		case EAST:
			return SOUTH;
		case SOUTH:
			return WEST;
		case WEST:
			return NORTH;
		default:
			return NONE_DIRECTION;
	}
}

void setLocation(Location* l, unsigned int x, unsigned int y) {
	l->x = x;
	l->y = y;
}

bool equals(Location l1, Location l2) {
	return l1.x == l2.x && l1.y == l2.y;
}


unsigned int check_x(Location l, Direction d) {
	switch(d) {
		case WEST:
			return l.x;
		case EAST:
			return l.x;
		case NORTH:
			return l.x + 1;
		case SOUTH:
			return l.x - 1;

	}
}


unsigned int check_y(Location l, Direction d) {
	switch(d) {
		case WEST:
			return l.y + 1;
		case EAST:
			return l.y - 1;
		case NORTH:
			return l.y;
		case SOUTH:
			return l.y;
			
	}
}


typedef struct {
	unsigned int top_of_stack;
	unsigned int len;
	Direction* arr;
} Stack;



void initializeStack(Stack s, Direction* arr, unsigned int len);
void displayStack(Stack s);
Direction peek(Stack s);
bool push(Stack s, Direction d);
Direction pop(Stack s);


void initializeStack(Stack s, Direction* arr, unsigned int len) {
	s.top_of_stack = 0;
	s.len = len;
	s.arr = arr;

	for(unsigned int i = 0; i < s.len; ++i) {
		s.arr[i] = NONE_DIRECTION;
	}
}

void displayStack(Stack s) {
	for(unsigned int i = 0; i < s.len; ++i) {
		string str = "";
		directionToString(s.arr[i], &str);
		displayCenteredTextLine(i, str);
	}
}

Direction peek(Stack s) {
	if(s.top_of_stack == 0) {
		return NONE_DIRECTION;
	}
	return s.arr[s.top_of_stack-1];
}

bool push(Stack s, Direction d) {
	if(s.top_of_stack == s.len) {
		return false;
	}
	s.arr[s.top_of_stack] = d;
	++s.top_of_stack;
	return true;
}

Direction pop(Stack s) {
	if(s.top_of_stack == 0) {
		return NONE_DIRECTION;
	}
	Direction retval = s.arr[s.top_of_stack-1];
	s.arr[s.top_of_stack-1] = NONE_DIRECTION;
	--s.top_of_stack;
	return retval;
}


const unsigned int start_x = 0 ;
const unsigned int start_y = 2;
const Direction direction_start = NORTH;

const unsigned int target_x = 5;
const unsigned int target_y = 0;



typedef enum TurnDirection {
	no_turn,
	LEFT,
	RIGHT
} TurnDirection;

typedef struct {
	Direction direction;
	TurnDirection lastTurn;
	Location location;
	Stack previousMoves;
} Robot;


void moveEncoderAndStop(
		float leftMotorPosition, int leftMotorSpeed,
		float rightMotorPosition, int rightMotorSpeed);
void turnRight(Robot r);
void turnLeft(Robot r);
void turn180(Robot r);
bool goForwards(Robot r);
void optimal_path_return(Robot r);


void moveEncoderAndStop(
		float leftMotorPosition, int leftMotorSpeed,
		float rightMotorPosition, int rightMotorSpeed) {
	resetMotorEncoder(LeftMotor);
	resetMotorEncoder(RightMotor);
	setMotorTarget(LeftMotor, leftMotorPosition, leftMotorSpeed);
	setMotorTarget(RightMotor, rightMotorPosition, rightMotorSpeed);
	waitUntilMotorStop(LeftMotor);
	waitUntilMotorStop(RightMotor);

}


void turnRight(Robot r) {
	unsigned int turnDistance = right_turn;
	if(r.lastTurn == LEFT) {
		turnDistance += 2;
	}
	resetMotorEncoder(LeftMotor);
	resetMotorEncoder(RightMotor);
  setMotorSyncEncoder(LeftMotor, RightMotor, 100, turnDistance, 16);
  waitUntilMotorStop(LeftMotor);
	waitUntilMotorStop(RightMotor);
	r.direction = getDirectionRight(r.direction);
	r.lastTurn = RIGHT;
	sleep(100);
}

void turnLeft(Robot r) {
	unsigned int turnDistance = left_turn;
	if(r.lastTurn == RIGHT) {
		turnDistance += 2;
	}
	resetMotorEncoder(LeftMotor);
	resetMotorEncoder(RightMotor);
setMotorSyncEncoder(LeftMotor, RightMotor, -100, turnDistance, 16);
	waitUntilMotorStop(LeftMotor);
	waitUntilMotorStop(RightMotor);

	r.direction = getDirectionLeft(r.direction);
	r.lastTurn = LEFT;
	sleep(100);
}

void turn180(Robot r) {
	moveEncoderAndStop(
			right_turn*2, right_left_speed/2,
			-right_turn*2, right_left_speed/2
	);
	r.direction = check_opposite_direction(r.direction);
	sleep(100);
}


bool goForwards(Robot r) {
	resetMotorEncoder(LeftMotor);
 	resetMotorEncoder(RightMotor);



setMotorSyncEncoder(LeftMotor, RightMotor,0, length_grid, 26);

 /*		///PID try with utlrasonic sensor to keep straight-----------------------------------------------------------------------------/////
int distance_value;
float target_value=3.8;
float kp=0.9;
float steering_value;
int lasterror=0;
int error, integral, derivative;

if(getUSDistance(UltrasonicSensor)>7.4){
	distance_value=(getUSDistance(UltrasonicSensor2));
}
else
	{
			distance_value=(getUSDistance(UltrasonicSensor));
	}

		//PID ALGORITHM
		error = 	distance_value - target_value;
		integral = error + integral;
		derivative = error - lasterror;
		steering_value=(kp * error);



	setMotorSyncEncoder(LeftMotor, RightMotor, steering_value, 490, 30);*/

	////-----------------------------------------------------------------------------////
	while(getMotorEncoder(LeftMotor) < length_grid*0.9 ||
				getMotorEncoder(RightMotor) < length_grid*0.9) {

		if (getTouchValue(TouchSensor)){

			resetMotorEncoder(LeftMotor);
			resetMotorEncoder(RightMotor);
			setMotorSpeed(LeftMotor, 0);
			setMotorSpeed(RightMotor, 0);
			waitUntilMotorStop(LeftMotor);
			waitUntilMotorStop(RightMotor);

			//moveEncoderAndStop(120, 30, 120, 30);
			resetMotorEncoder(LeftMotor);
			resetMotorEncoder(RightMotor);
			sleep(200);
			setMotorTarget(LeftMotor, -110, 16);
			setMotorTarget(RightMotor, -110, 16);
			waitUntilMotorStop(LeftMotor);
			waitUntilMotorStop(RightMotor);

			sleep(100);
			return false;
		}
	}

	waitUntilMotorStop(LeftMotor);
	waitUntilMotorStop(RightMotor);

	if(r.direction == check_opposite_direction(peek(r.previousMoves))) {
		pop(r.previousMoves);
	}
	else {
		push(r.previousMoves, r.direction);
	}

	setLocation(
			&r.location,
			check_x(r.location, r.direction),
			check_y(r.location, r.direction)
	);

	r.lastTurn = no_turn;

	string s;
	directionToString(peek(r.previousMoves), &s);
	stringDelete(s, 1, 10);
	datalogAddChar(0, (char)atoi(s));
	return true;
}


void optimal_path_return(Robot r) {
	turn180(r);

	Direction nextDirection = check_opposite_direction(pop(r.previousMoves));

	while(nextDirection != NONE_DIRECTION) {

		if(r.direction == NORTH) {
			if(nextDirection == WEST) turnLeft(r);
			if(nextDirection == EAST) turnRight(r);
		}
		else if(r.direction == EAST) {
			if(nextDirection == NORTH) turnLeft(r);
			if(nextDirection == SOUTH) turnRight(r);
		}
		else if(r.direction == SOUTH) {
			if(nextDirection == EAST) turnLeft(r);
			if(nextDirection == WEST) turnRight(r);
		}
		else if(r.direction == WEST) {
			if(nextDirection == SOUTH) turnLeft(r);
			if(nextDirection == NORTH) turnRight(r);
		}

		unsigned int consecutiveRooms = 1;
		while(check_opposite_direction(peek(r.previousMoves)) == nextDirection) {
			++consecutiveRooms;
			pop(r.previousMoves);
			setLocation(
					&r.location,
					check_x(r.location, r.direction),
					check_y(r.location, r.direction)
			);
		}

		moveEncoderAndStop(
				length_grid * consecutiveRooms, straight_speed,
				length_grid * consecutiveRooms, straight_speed
		);

		nextDirection = check_opposite_direction(pop(r.previousMoves));
	}

}

task main()
{
	datalogClose();
	datalogFlush();
	bool datalogOpenSuccess = datalogOpen(0, 1, false);
	if (!datalogOpenSuccess) {
		displayCenteredTextLine(6, "Unable to open datalog.");
	}
	else {
		displayCenteredTextLine(6, "");
	}

	Robot robot;

	const unsigned int len = 50;
	Direction arr[len];
	initializeStack(robot.previousMoves, arr, len);

	setLocation(&robot.location, start_x, start_y);
	robot.direction = direction_start;
	robot.lastTurn = NONE_DIRECTION;

	Location destination;
	setLocation(&destination, target_x, target_y);

	while(!equals(destination, robot.location)) {

		displayStack(robot.previousMoves);
		displayCenteredTextLine(1, " X: %d", robot.location.x);
		displayCenteredTextLine(2, " Y: %d", robot.location.y);

		string s;
		directionToString(robot.direction, &s);
		displayCenteredTextLine(5, "Direction: %s", s);

		if(getUSDistance(UltrasonicSensor) > wall_dist) {
			turnRight(robot);
		}

		bool result = goForwards(robot);
		if(!result) {
			turnLeft(robot);
		}
	}

	playSound(soundFastUpwardTones);
	sleep(100);

	optimal_path_return(robot);
	playSound(soundFastUpwardTones);
	sleep(100);

	datalogClose();
}
