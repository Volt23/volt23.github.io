#include <VirtualWire.h> //library for the rf module
#include <ADCTouch.h> //// Library for the capacitive sensor 
// http://tuomasnylund.fi/drupal6/content/capacitive-touch-sensing-avr-and-single-adc-pin

int ref0, ref1, ref2, ref3, ref4, ref5; //used for minimum values calibration
int refm0, refm1, refm2, refm3, refm4, refm5; //used for maximum values calibration
int capread[6]; // store the values of capacitive pads
char msg[6]; // store the 6byte message that will be sent through the rf module 
bool doitonce=true; //boolean for a setup cycle inside loop

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  
  /////////// Rf communication
  vw_setup(6000);	 // Bits per sec
}

void loop()
{
  /////////// Calibration for each pad, it happens once
  if(doitonce==true){
  Calibrate();
  doitonce=false;}
  else{};

  /////////// Read the values of capacitive pads and store these
  int cap0 = ADCTouch.read(A0);
  int cap1 = ADCTouch.read(A1);
  int cap2 = ADCTouch.read(A2);
  int cap3 = ADCTouch.read(A3);
  int cap4 = ADCTouch.read(A4);
  int cap5 = ADCTouch.read(A5);

  /////////// Bring the minimum values around 0 
  /////////// subtracting the values that have been read during calibration
  cap0 -= ref0;
  cap1 -= ref1;
  cap2 -= ref2;
  cap3 -= ref3;
  cap4 -= ref4;
  cap5 -= ref5;

  /////////// Calculate the max values source, 
  /////////// using the values that have been read during calibration
  int mapfrom=0;
  int mapto0=refm0-ref0;
  int mapto1=refm1-ref1;
  int mapto2=refm2-ref2;
  int mapto3=refm3-ref3;
  int mapto4=refm4-ref4;
  int mapto5=refm5-ref5;

  /////////// Map the values in order to have a 1byte data for each capacitive sensor 
  int capread[]={
  map(cap0,mapfrom,mapto0,0,250),
  map(cap1,mapfrom,mapto1,0,250),
  map(cap2,mapfrom,mapto2,0,250),
  map(cap3,mapfrom,mapto3,0,250),
  map(cap4,mapfrom,mapto4,0,250),
  map(cap5,mapfrom,mapto5,0,250)};
  
for(int i=0; i<6;i++){
  if(capread[i]<0){
    capread[i]=0;
  }
  else if(capread[i]>255){
    capread[i]=255;
  }
  else{}
  }

  //////////// Debug
  String debug= "Send: ";
  for(int i=0; i<6;i++){
    String tmp= String(capread[i]);
    debug=String(debug+tmp+" ");
  } Serial.println(debug);

  /////////// Split the values in order to have each sensor with 2byte information for 3 pads
  /////////// The mapping values above should be removed, capread[] array index should be 3 
  /////////// All the variables that are 6 should be 3:cap.., mapto..,ref..,refm
/*
  byte lowerByte = (capread[0] & 0xFF);  // gives you the right hand 8 bits
  byte upperByte=(capread[0] >>8);
  
  byte lowerByte1 = (capread[1] & 0xFF);  // gives you the right hand 8 bits
  byte upperByte1=(capread[1] >>8);
  
  byte lowerByte2 = (capread[2] & 0xFF);  // gives you the right hand 8 bits
  byte upperByte2=(capread[2] >>8);
  
  byte lowerByte3 = (capread[3] & 0xFF);  // gives you the right hand 8 bits
  byte upperByte3=(capread[3] >>8);
  
  msg[0]=lowerByte;
  msg[1]=upperByte;
  msg[2]=lowerByte1;
  msg[3]=upperByte1;
  msg[4]=upperByte2;
  msg[5]=upperByte2;
  msg[6]=upperByte3;
  */

  //////////// Store the data into the char array in order to send it
  msg[0]=capread[0];
  msg[1]=capread[1];
  msg[2]=capread[2];
  msg[3]=capread[3];
  msg[4]=capread[4];
  msg[5]=capread[5];

  //////////// Send the value to the receiver
  { vw_send((uint8_t *)msg, sizeof(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, false);
    delay(10);
  }
}

void Calibrate(){
  /////////// Set up max values by touching each pad,
  /////////// the led on pin 13 shows when touch each pad from A0 to A5
  Serial.println("setup max values");
  digitalWrite(13, HIGH);  
  /////////// 3sec led on to show the beginning of calibration
  delay(3000);
  refm0 = ADCTouch.read(A0, 100);
  digitalWrite(13, LOW);
  delay(500);
  
  digitalWrite(13, HIGH);    
  delay(1000);
  refm1 = ADCTouch.read(A1, 100);
  digitalWrite(13, LOW);  
  delay(500);
  
  digitalWrite(13, HIGH);  
  delay(1000);
  refm2 = ADCTouch.read(A2, 100);  
  digitalWrite(13, LOW);   
  delay(500);
  
  digitalWrite(13, HIGH);   
  delay(1000);
  refm3 = ADCTouch.read(A3, 100); 
  digitalWrite(13, LOW);  
  
  digitalWrite(13, HIGH);  
  delay(1000);
  refm4 = ADCTouch.read(A4, 100); 
  digitalWrite(13, LOW);  
  delay(500);
  
  digitalWrite(13, HIGH);  
  delay(1000);
  refm5 = ADCTouch.read(A5, 100); 

  ///////// At the end of max values calibration led blinks three times
  digitalWrite(13, LOW);   
    delay(200); 
  digitalWrite(13, HIGH);  
    delay(200);  
  digitalWrite(13, LOW); 
    delay(200); 
  digitalWrite(13, HIGH);  
      delay(200);  
  digitalWrite(13, LOW); 
  delay(500);

  ///////// Setup base values
  ///////// don't touch the pads during this
  Serial.println("setup base value");
  digitalWrite(13, HIGH);    // turn the LED off by making the voltage LOW
  delay(3000);
  ref0 = ADCTouch.read(A0, 100);    //account for the capacitance of the pad
  ref1 = ADCTouch.read(A1, 100);    //account for the capacitance of the pad
  ref2 = ADCTouch.read(A2, 100);    //account for the capacitance of the pad
  ref3 = ADCTouch.read(A3, 100);    //account for the capacitance of the pad
  ref4 = ADCTouch.read(A4, 100);    //account for the capacitance of the pad
  ref5 = ADCTouch.read(A5, 100);    //account for the capacitance of the pad
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
}
