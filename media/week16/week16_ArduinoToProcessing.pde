/* 
ARDUINO TO PROCESSING

Read Serial messages from Arduino for use in Processing
Created by Daniel Christopher 10/27/12

Read six bytes sent from Arduino through serial communication; convert from String to ints and assign these values to the heights of 6 quads.
Modified by Ernesto Voltaggio 25/05/16
*/

import processing.serial.*; //import the Serial library

int[] values=new int[6];  // store the values coming

int end = 10;    // the number 10 is ASCII for linefeed (end of serial.println), later we will look for this to break up individual messages
String serial;   // declare a new string called 'serial' . A string is a sequence of characters (data type know as "char")
Serial port;  // The serial port, this is a new instance of the Serial class (an Object)

int quadwidth=60;
float padsx;
int margindx=15;
int ypos=420;


void setup() {
  size(500,450);
  background(255);
  
  port = new Serial(this, Serial.list()[1], 9600); // initializing the object by assigning a port and baud rate (must match that of Arduino)
  port.clear();  // function from serial library that throws out the first reading, in case we started reading in the middle of a string from Arduino
  serial = port.readStringUntil(end); // function that reads the string from serial port until a println and then assigns string to our string variable (called 'serial')
  serial = null; // initially, the string will be null (empty)
 //println(Serial.list()); //print the port list
}


void draw(){
  background(0);
  float padsx=width/2-quadwidth*3-margindx*2.5; //center the rects based on stage's width
  
  SerialRead(); //read values, convert in ints, store these in values[]
  
  //////////Draw six rects and assign the arduino values to height
  for(int i=0; i<6;i++){
   rect(padsx+((quadwidth+margindx)*i),ypos,quadwidth,values[i]*-1.2); 
   }
  
  /////////Debug
  for(int i=0; i<6;i++){
      print(values[i]); //print Values
      print(" ");}      
      println(); 
    };



/////////Read serial values and store these in 'values' array converting from String to int
void SerialRead() {
  while (port.available() > 0) {  //as long as there is data coming from serial port, read it and store it 
    serial = port.readStringUntil(end);  // read String until new line is found
  }
    ///////////// Parse, convert and store the values coming from serial communication.
    if (serial != null) {  //if the string is not empty, print the following
      String[] a = split(serial, ',');  //a new array (called 'a') that stores values into separate cells (separated by commas specified in your Arduino program)
      for(int i=0; i<6;i++){
      values[i]= int(a[i]);  // Convert into ints and store the values
      }      
   }
}