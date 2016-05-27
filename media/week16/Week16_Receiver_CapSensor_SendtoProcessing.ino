#include <VirtualWire.h> //library for the rf module
 
void setup()
{
    Serial.begin(9600); 
    
    /////////Rf communication
    vw_set_rx_pin(11); // Set the Pin where data will be received by the receiver module
    vw_setup(6000);  // Bits per sec
    vw_rx_start();  // Start the receiver PLL running
}
 
void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
 
    if (vw_get_message(buf,&buflen)) // Non-blocking
    { int i;
      int capread[6];
      digitalWrite(13, true); // Flash a light to show received good message

//////////// Store the data received in capread[]
 capread[0] = buf[0];
 capread[1] = buf[1];
 capread[2] = buf[2];
 capread[3] = buf[3];
 capread[4] = buf[4];
 capread[5] = buf[5];

/////////// 3*2byte data for 3 high resolution capacitive pads
/*for(int i=0; i<3; i++){
 *int leftbyte=i*2+1;
 *int rightbyte=i*2;
 *capread[i] = (buf[leftbyte] << 8) | buf[rightbyte];} //Put toghether 2byte
 */

////////// Send data
  Serial.print(capread[0],DEC);
     Serial.print(",");
  Serial.print(capread[1],DEC);
       Serial.print(",");
  Serial.print(capread[2],DEC);
       Serial.print(",");
  Serial.print(capread[3],DEC);
       Serial.print(",");
  Serial.print(capread[4],DEC);
       Serial.print(",");
  Serial.print(capread[5],DEC);
         Serial.print(",");
  Serial.println();
        digitalWrite(13, false);
}

delay(50);}

