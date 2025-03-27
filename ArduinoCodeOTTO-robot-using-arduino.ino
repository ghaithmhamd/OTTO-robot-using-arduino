//Project created by Ghaith Mhamdi on 19/02/2020
/*Arduino Code for Walking and Dancing Robot
 * Coded by Circuitdigest.com
 * On 25-05-2017
 */

 /*CONNECTION DETIALS
  * Arduino D11 -> RX of BT Module
  * Arduino D12 -> Tx of BT
  * Arduino D2  -> Hall sensor 3rd pin
  * Servo1 -> pin 3 of arduino Nano
  * Servo2 -> pin 5 of arduino Nano
  * Servo4 -> pin 9 of arduino Nano
  * Servo5 -> pin 10 of arduino Nano
  */

#include <Servo.h> //header to srive servo motors
#include <SoftwareSerial.h>// import the serial library
SoftwareSerial Bot_BT(12, 11);  // RX, TX
int ledpin=13; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer

//lets declare the servo objects
Servo servo1;  
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
//End of declaration

long gmotor,gnum1,gnum2;
int pos,pos2;
int flag=0; 
int poss1,poss2,poss3,poss4;

void setup() 
{
   servo1.attach(3);
   servo2.attach(5);;
   servo4.attach(9);
   servo5.attach(10);

   //**Initial position of all four servo motors**//
   servo1.write(110);
   servo2.write(100);
   servo4.write(90);
   servo5.write(80);
   //**inititialised**//
   
Bot_BT.begin(9600); //start the Bluetooth communication at 9600 baudrate
Bot_BT.println("Blue Bob is ready to take actions");

Serial.begin(57600); 
Serial.println("Biped Servo programming by CircuitDigest.com");
Serial.println("Enter any of the following commands for theier respective actions");
Serial.println("1. Servomotor Number, From angle, To angle -> To control one particular Servo");
Serial.println("          Servomotor Number -> 1,2,4,5");
Serial.println("          From angle -> 0 to 180");
Serial.println("          To angle -> 0 to 180");
Serial.println("2. Servomotor Number, From angle, To angle -> To control one particular Servo");
Serial.println("3. Enter 10 -> To lift left leg up");
Serial.println("4. Enter 11 -> To lift right leg up");
Serial.println("5. Enter 12 -> To move left leg front");
Serial.println("6. Enter 13 -> To move right leg front");
Serial.println("7. Enter 49 -> To say Hi ;-)");
Serial.println("8. Enter 50 -> To Walk with style 1");
Serial.println("9. Enter 51 -> To Walk with style 2");
Serial.println("10. Enter 52 -> To Dance with style 1");
Serial.println("11. Enter 53 -> To Dance with style 2");
Serial.println("12. Enter 54 -> To Say Bye!!");
}

//***Function for each Servo actions**//
void call(int motor, int num1, int num2) // The values like Motor number , from angle and to angle are received 
{
Serial.println("Passing values...");
flag =0;
switch (motor) 
  {  
    case 1:            // For motor one
      { Serial.println("Executing motor one");
        if(num1<num2) // Clock wise rotation
  { for ( pos =num1; pos<=num2; pos+=1)
  {
    servo1.write(pos);
    delay( 20);
  }}

if(num1>num2) // Anti-Clock wise rotation
  {
  for ( pos =num1; pos>=num2; pos-=1)
  {
    servo1.write(pos);
    delay( 20);
  }}
      break;
      }     

       ////////JUST  DUPLICATE FOR OTHER SERVOS////

       
    case 2:    // For motor 2
      {
        Serial.println("Executing motor two");
        if(num1<num2)
  {
  for ( pos =num1; pos<=num2; pos+=1)
  {
    servo2.write(pos);
    delay( 20);
  }}
if(num1>num2)
  {
  for ( pos =num1; pos>=num2; pos-=1)
  {
    servo2.write(pos);
    delay( 20);
  }}
      break;
      }     
      
           
    case 4:    // for motor four
      {
        Serial.println("Executing motor four");
        if(num1<num2)
  {
  for ( pos =num1; pos<=num2; pos+=1)
  {
    servo4.write(pos);
    delay (20);
  }}

if(num1>num2)
  {
  for ( pos =num1; pos>=num2; pos-=1)
  {
    servo4.write(pos);
    delay (20);
  }}
      break;
      }
      
      case 5:    // for motor five
      {
        Serial.println("Executing motor five");
  {
  for ( pos =num1; pos<=num2; pos+=1)
        if(num1<num2)
  {
    servo5.write(pos);
    delay (20);
  }}

if(num1>num2)
  {
  for ( pos =num1; pos>=num2; pos-=1)
  {
    servo5.write(pos);
    delay (20);
  }}
      break;
      }
  }
}

void loop()
{

  if(Serial.available()>0) //Read whats coming in through Serial
  {
  gmotor= Serial.parseInt(); 
  Serial.print(" selected Number-> ");  
  Serial.print(gmotor);
  Serial.print(" , ");    
  gnum1= Serial.parseInt();   
  Serial.print(gnum1);  
  Serial.print(" degree , ");
  gnum2= Serial.parseInt();   
  Serial.print(gnum2);  
  Serial.println(" degree ");
   flag=1;
   }

 if (Bot_BT.available()) //Read whats coming in through Bluetooth
   {
BluetoothData=Bot_BT.read();
Serial.print("Incoming from BT:");
Serial.println(BluetoothData);
}
   
if (flag ==1 )
call(gmotor,gnum1,gnum2); //call the respective motor for action
 

    //Execute the functions as per the commond received through the Serial monitor or Bluetooth//
if (gmotor ==10)
left_leg_up();  

if (gmotor ==11)
right_leg_up();  

if (gmotor ==12)
move_left_front();

if (gmotor ==13)
move_right_front();

if (BluetoothData ==49 || gmotor ==49)
say_hi();

if (BluetoothData ==50 || gmotor ==50)
walk1();

if (BluetoothData ==51 || gmotor ==51)
walk2();

if (BluetoothData ==52 || gmotor ==52)
dance1();

if (BluetoothData ==53 || gmotor ==53)
dance2();

if (BluetoothData ==54 || gmotor ==54)
{test();test();test();}

//End of executions//

gmotor=0; //To prevet repetetion
BluetoothData = 0; //To prevet repetetion
//stay_put(); //bring the Bot to initial posotion if required

}

 

/*---------------------------------------------------------------------------*/

 

// Code for Bot Functions......

//***Function to lift the left leg**//
void stay_put()
{
   servo5.attach(10);
   servo1.write(110);
   servo2.write(100);
   servo4.write(90);
   servo5.write(80);
   delay(20);
}
//**_____End of Function______**//

//***Function to lift the left lef**//
void left_leg_up()
{
   Serial.println("left leg up");
    poss1 = 80;
    poss2 = 110;
   do{
    servo5.write(poss1);
    servo4.write(poss2);
    poss1++;
    poss2++;
    delay(20);
   }while(poss1 <100 || poss2<140);
   call(4,130,100);
}
//**_____End of Function______**//

//***Function to lift the left lef**//
void right_leg_up()
{
Serial.println("right leg up");
    poss1 = 80;
    poss2 = 100;
   do{
    servo4.write(poss2);
    servo5.write(poss1);
    poss1--;
    poss2--;
    delay(20);
   }while(poss1 >50 || poss2>60); 
   call(5,50,80);
}
//**_____End of Function______**//

//***Function to lift the left lef**//
void move_left_front()
{
   Serial.println("moving left front");
    poss1=120;poss2=110;poss3=110;
       do{
    servo2.write(poss1);
    servo1.write(poss2);
    servo5.write(poss3);
    poss1--;
    poss2--;
    poss3--;
    delay(20);
   }while(poss1 >100 || poss2>80 || poss3>80  );
}
//**_____End of Function______**//

//***Function to lift the left lef**//
void  move_right_front()
{
    poss1=80;poss2=100;poss3=60;
       do{
    servo1.write(poss1);
    servo2.write(poss2);
    servo4.write(poss3);
    poss1++;
    poss2++;
    poss3++;
    delay(20);
   }while(poss1 <110 || poss2<120 || poss3<90);    
}
//**_____End of Function______**//

//***Function to lift the left lef**//
void say_hi()
{
  stay_put();
  right_leg_up();
  call(5,80,50); //wave up
  call(5,50,80); //wave down 
  call(5,80,50); //wave up 
  call(5,50,80); //wave down
  stay_put();  
}
//**_____End of Function______**//

//***Function to lift the left lef**//
void walk1()
{
  stay_put();
  char temp=10; //number of steps to make * 2
  do{
  right_leg_up();
  move_right_front();
  left_leg_up();
  move_left_front();  
  temp--;
  }while(temp>0);
}
//**_____End of Function______**//

//***Function to lift the left lef**//
void walk2()
{
  stay_put();
  char temp=10; //number of steps to make * 2
  do{
  move_right_front();
  move_left_front();  
  temp--;
  }while(temp>0);
}
//**_____End of Function______**//

//***Function to lift the left lef**//
void dance1()
{
  stay_put();
  char temp=3; //number of steps to make * 2
  do{
    poss1 = 80;
    poss2 = 60;
   do{
    servo1.write(poss1);
    servo2.write(poss2);
    poss1++;
    poss2++;
    delay(20);
   }while(poss1 <140 || poss2<120);
   
    poss1 = 140;
    poss2 = 120;
   do{
    servo1.write(poss1);
    servo2.write(poss2);
    poss1--;
    poss2--;
    delay(20);
   }while(poss1 >80 || poss2>60);
  temp--;
  }while(temp>0);
  stay_put();
}
//**_____End of Function______**//

//***Function to lift the left lef**//
void dance2()
{
  stay_put();
  char temp=3; //number of steps to make * 2
  do{
  right_leg_up(); right_leg_up();
  stay_put();
  left_leg_up();left_leg_up();
  stay_put();
  temp--;
  }while(temp>0);
  stay_put();
}
//**_____End of Function______**//

//***Function to lift the left lef**//
void test()
{
    poss1 = 40;
    poss2 = 130;
   do{
    servo5.write(poss1);
    servo4.write(poss2);
    poss1++;
    poss2--;
    delay(5);
   }while(poss1 <120 || poss2>50);
   poss1 = 120;
   poss2 = 50;
   do{
    servo5.write(poss1);
    servo4.write(poss2);
    poss1--;
    poss2++;
    delay(5);
   }while(poss1 >40 || poss2<130); 
}
//**_____End of Function______**//
