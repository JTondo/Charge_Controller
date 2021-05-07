int PWM_MOSFET = 3;
bool cutoff_MOSFET = 5;
float Vout_pin = A1;
float V_sense_out_pin = A0;
float Vin_pin = A2;
float V_sense_in_pin = A3;
//const float charge_current = 1.0;
const float Vcc = 5.0;  //supply voltage for current sensors
const float FACTOR = 0.04;  //40mV/A;
bool ON = true;
const int numReadings = 20;
float readings1[numReadings];    
float readings2[numReadings];  
 
int readIndex = 0;              
float total1 = 0;
float total2 = 0;  
                
float average1 = 0;  
float average2 = 0;
               

void setup() {
  pinMode(PWM_MOSFET, OUTPUT);
  pinMode(cutoff_MOSFET, OUTPUT);
  Serial.begin(9600);
  //PWM Frequency Setup---------------
  TCCR2A = 0x23;
  TCCR2B = 0x09;
  OCR2A = 160 - 1;
  OCR2B = 80; // Initial Duty Cycle 50%
  TCNT2 = 0;
  //----------------------------------
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings1[thisReading] = 0;
    readings2[thisReading] = 0;
  }
}

void loop() {
  if (ON == true) {
    digitalWrite(cutoff_MOSFET, HIGH);  //Keep ground connected
  }
  else if (ON == false) {
    digitalWrite(cutoff_MOSFET, LOW);   //Create open circuit
  }

  //Converting Input Voltage from current sensors to current values-------
  float V_I_out = (5.0 / 1024.0)*(analogRead(V_sense_out_pin));
  V_I_out = V_I_out - (Vcc * 0.5) - 0.09;
  float Iout = V_I_out / FACTOR;
  total1 = total1 - readings1[readIndex];
  readings1[readIndex] = Iout;
  total1 = total1 + readings1[readIndex];
  Iout = total1 / numReadings;

  float V_I_in = (5.0 / 1024.0)*(analogRead(V_sense_in_pin));
  V_I_in = V_I_in - (Vcc * 0.5) - 0.094;
  float Iin = V_I_in / FACTOR;
  total2 = total2 - readings2[readIndex];
  readings2[readIndex] = Iin;
  total2 = total2 + readings2[readIndex];
  Iin = total2 / numReadings;
  

  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
    Serial.print("Iout = ");
    Serial.print(Iout);
    Serial.print("\n");
   
    Serial.print("Iin = ");
    Serial.print(Iin);
    Serial.print("\n");
    //----------------------------------------------------------------------
    //Converting Input Voltage from voltage dividers to voltage values------
    float Vout_init = (5.0 / 1024.0) * analogRead(Vout_pin);
    float Vout = 10.68 * Vout_init;
  
    float Vin_init = (5.0 / 1024.0) * analogRead(Vin_pin);
    float Vin = 11.62 * Vin_init;
    Serial.print("Vout = ");
    Serial.print(Vout);
    Serial.print("\n");
    Serial.print("Vin = ");
    Serial.print(Vin);
    Serial.print("\n");
    Serial.print("----------------------------\n");
    Serial.print("\n");
    float Pin = Vin * Iin;
    float Pout = Vout * Iout;
    float efficiency = Pout / Pin;
    //----------------------------------------------------------------------
  }
  
  
    
  

  
  



  //  if(Vout >= 41.5){
  //    ON = false;
  //  }
  //  else{
  //    if ((Vout >= 41.0) && (Vout < 41.1)){
  //      ON = true;
  //      if((Iout > charge_current*0.75) && (OCR2B < 160)){
  //        OCR2B++;
  //      }
  //      else if ((Iout < charge_current*0.75) && (OCR2B > 0)){
  //        OCR2B--;
  //      }
  //      else{
  //        //change nothing
  //      }
  //    }
  //    else if ((Vout >= 41.1) && (Vout < 41.2)){
  //      ON = true;
  //      if((Iout > charge_current*0.5) && (OCR2B < 160)){
  //        OCR2B++;
  //      }
  //      else if ((Iout < charge_current*0.5) && (OCR2B > 0)){
  //        OCR2B--;
  //      }
  //      else{
  //        //change nothing
  //      }
  //    }
  //    else if ((Vout >= 41.2) && (Vout < 41.3)){
  //      ON = true;
  //      if((Iout > charge_current*0.25) && (OCR2B < 160)){
  //        OCR2B++;
  //      }
  //      else if ((Iout < charge_current*0.25) && (OCR2B > 0)){
  //        OCR2B--;
  //      }
  //      else{
  //        //change nothing
  //      }
  //    }
  //    else if ((Vout >= 41.3) && (Vout < 41.4)){
  //      ON = true;
  //      if((Iout > charge_current*0.1) && (OCR2B < 160)){
  //        OCR2B++;
  //      }
  //      else if ((Iout < charge_current*0.1) && (OCR2B > 0)){
  //        OCR2B--;
  //      }
  //      else{
  //        //change nothing
  //      }
  //    }
  //    else if ((Vout >= 41.4) && (Vout < 41.5)){
  //      ON = true;
  //      if((Iout > charge_current*0.05) && (OCR2B < 160)){
  //        OCR2B++;
  //      }
  //      else if ((Iout < charge_current*0.05) && (OCR2B > 0)){
  //        OCR2B--;
  //      }
  //      else{
  //        //change nothing
  //      }
  //    }
  //    else{
  //      ON = true;
  //      if((Iout > charge_current) && (OCR2B < 160)){
  //        OCR2B++;
  //      }
  //      else if ((Iout < charge_current) && (OCR2B > 0)){
  //        OCR2B--;
  //      }
  //      else{
  //        //change nothing
  //      }
  //    }
  //  }
  
}
