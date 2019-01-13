//This code uses the third party library MD_Parola, created by MajicDesigns to control our LED Matrix
//This code uses the third party libarary NewPing, created by Tim Eckel to control our Ultrasonic Sensor

//Include the libraries that we will be using to make our lives much easier
#include <NewPing.h> //Library Docs https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
#include <MD_Parola.h> //Library Docs https://majicdesigns.github.io/MD_Parola/index.html
#include <SPI.h>


// Define the pins we will be using for the LED Matrix, how many 8X8 LED Matrix will be used
// Define the hardware type for the MD_Parola library to know what is being used, we are using FC16_HW
#define hardware_type MD_MAX72XX::FC16_HW
#define max_devices 4
#define clk_pin   13
#define data_pin  11
#define cs_pin    10

// MD_Parola library LED Matrix function constructor
MD_Parola ledMatrix(hardware_type, data_pin, clk_pin, cs_pin, max_devices);

int scrollSpeed = 0;    // How fast we want the text to scroll (lower the number the faster the speed)
textEffect_t scrollEffect = PA_SCROLL_DOWN; //Scroll the text DOWN, we can change to UP, LEFT, or RIGHT
textPosition_t scrollAlign = PA_CENTER; // Align text to the CENTER, we can also set it to LEFT or RIGHT
int scrollPause = 10000; // How long we want the text to sit at the end of the scroll (in milliseconds)

//Create the message as a string inside the "" section
#define  BUF_SIZE  75
char message[BUF_SIZE] = { "STOP !" };

//Define pins used for echo and trigger and the max distance for the Ultrasonic Sensor
#define trig_pin 5
#define echo_pin 6
#define maximum_distance 500

//New Ping library sensor function constructor
NewPing sonar(trig_pin, echo_pin, maximum_distance);


void setup()
{
  //Initialize the object data for the LED Matrix
  ledMatrix.begin();
  //Initiate the serial object
  Serial.begin(9600);
}


void loop()
{
  //Delay the next loop to allow for more accurate ping (in milliseconds)
  delay(150);
  //Create distance variable for using the sonar ping function
  int distance = sonar.ping_in();
  //Print the distance in serial monitor so we can see the distance
  Serial.println(distance);

  if (ledMatrix.displayAnimate()){
    //Set the distance of your car from the sensor, measured in Inches
    if ((distance <= 50) && (distance > 3)){
      ledMatrix.displayText(message, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
      ledMatrix.displayReset();
    }
  }

}
