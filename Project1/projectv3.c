#pragma config(Sensor, S2,     distance_sensor, sensorEV3_Ultrasonic)
#pragma config(Sensor, S3,     light_sensor,   sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor,  motorA,          leftmotor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          rightmotor,    tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main(){

int reflected_value;
float target_value=22.0;
float kp=10;
float ki=0.001;
float kd=3;
int steering_value;
int lasterror=0;
int error, integral, derivative;

int flag_dist=0;
int flag2 = 0;
int greenTally = 0;
int blueTally = 0;

string colour = "";


resetMotorEncoder(motorA);
resetMotorEncoder(motorB);
while(true)
{

	reflected_value=getColorReflected(light_sensor);
	    
		//PID ALGORITHM
		error = reflected_value - target_value;
		integral = error + integral;
		derivative = error - lasterror;
		steering_value=(kp * error) + (ki * integral) + (kd * derivative);


	setMotorSyncEncoder(leftmotor, rightmotor, steering_value, 1000, 16);

	lasterror = error;



		while((getUSDistance(distance_sensor) <= 18) && (getUSDistance(distance_sensor) > 10))
		{

		   //detect the colour in between 10-18cm 
	       reflected_value=getColorReflected(light_sensor);
	       error = reflected_value - target_value;
           integral = error + integral;
	  	   derivative = error - lasterror;
		   steering_value=(kp * error) + (ki * integral) + (kd * derivative);
         setMotorSyncEncoder(leftmotor, rightmotor, steering_value, 1000, 16);



			if(getColorName(light_sensor) == colorGreen)
			{
				//count if colour is green
				greenTally++;

			}
			else if(getColorName(light_sensor) == colorBlack)
			{
				//count if colour is blue
				blueTally++;
			}

		}



if( flag_dist==0)
  {

		if(getUSDistance(distance_sensor) <= 10)
		{
			//detect the obstacle and make sound and do tasks based on if the line is BLUE or GREEN
		    setMotorSpeed(motorA, 0);
			setMotorSpeed(motorB, 0);
			flag_dist++;
			playSound(soundLowBuzz);
			sleep(2000);


			if(greenTally>blueTally)
			{
				displayStringAt(5,120, "green");

				resetMotorEncoder(motorA);
				resetMotorEncoder(motorB);

				setMotorTarget(leftmotor, 120, 20);
				setMotorTarget(rightmotor, 120, 20);

				waitUntilMotorStop(leftmotor);
		        waitUntilMotorStop(rightmotor);

		    	delay(100);

		    	resetMotorEncoder(motorA);
				resetMotorEncoder(motorB);

				setMotorTarget(leftmotor, 205, 30);
                waitUntilMotorStop(leftmotor);

		   	delay(100);

		    	    resetMotorEncoder(motorA);
					resetMotorEncoder(motorB);

					setMotorTarget(leftmotor, 140, 20);
					setMotorTarget(rightmotor, 140, 20);

					waitUntilMotorStop(leftmotor);
		    	    waitUntilMotorStop(rightmotor);

		    	delay(100);

		    	resetMotorEncoder(motorA);
				resetMotorEncoder(motorB);

		    	setMotorTarget(leftmotor, 250, -20);
		    	setMotorTarget(rightmotor, 250, -20);

		    	waitUntilMotorStop(leftmotor);
		    	waitUntilMotorStop(rightmotor);

		    	delay(100);

		    	resetMotorEncoder(motorA);
				resetMotorEncoder(motorB);


				setMotorTarget(rightmotor, 225, 30);

				waitUntilMotorStop(leftmotor);
				waitUntilMotorStop(rightmotor);

				delay(1000);

				resetMotorEncoder(motorA);
				resetMotorEncoder(motorB);


		  flag2++;

			}//if
			else
			{
				displayStringAt(5,120, "blue");
	            resetMotorEncoder(motorA);
	             resetMotorEncoder(motorB);

	       setMotorTarget(motorA, 40, -50);
	       setMotorTarget(motorB, 40, -50);

	       waitUntilMotorStop(leftmotor);
	       waitUntilMotorStop(rightmotor);

	       resetMotorEncoder(motorA);
	       resetMotorEncoder(motorB);

		     setMotorTarget(motorA, 330, 28);
			setMotorTarget(motorB, -330, 28);

	       waitUntilMotorStop(leftmotor);
	       waitUntilMotorStop(rightmotor);
	       sleep(500);




	     while(true)
      {

		    reflected_value=getColorReflected(light_sensor);
	          error = reflected_value - target_value;
	          integral = error + integral;
			  derivative = error - lasterror;
			  steering_value=(-1)*((kp * error) + (ki * integral) + (kd * derivative));


				setMotorSyncEncoder(leftmotor, rightmotor, steering_value, 1000, 16);

				lasterror = error;

			}

			 }
		}

	}


	}
}
