#define BLYNK_TEMPLATE_ID "TMPL36Suy7DIZ"
#define BLYNK_TEMPLATE_NAME "Patient Monitoring System"
#define BLYNK_AUTH_TOKEN "WJme6hVZ_9fOMtEJ40vcQntgYc2SUzmw"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT SwSerial


#include <SoftwareSerial.h>
SoftwareSerial SwSerial(10, 11); // RX, TX

#include <BlynkSimpleStream.h>

#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7) 

#define samp_siz 4
#define rise_threshold 4

// Pulse Monitor  Test Script
int sensorPin = 0;
#define tempsensorPin A1
#define Spo2sensorPin A2
int buzzer = 8;

BlynkTimer timer;

// int temp(int t)
// {
//   Blynk.virtualWrite(V0, t);
// }

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

void setup()
{
  // Debug console
  SwSerial.begin(115200);
  pinMode(buzzer, OUTPUT);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, BLYNK_AUTH_TOKEN);

  // Setup a function to be called every second
  // timer.setInterval(1000L, myTimerEvent);
  lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
  // lcd.print("Heart Beat = "); // Prints "Arduino" on the LCD 
  lcd.print("BPM = "); // Prints "Arduino" on the LCD 
  lcd.setCursor(0,1);
  lcd.print("TEMP = "); // Prints "Arduino" on the LCD 
}

void loop()
{
    Blynk.run();
    // timer.run(); // Initiates BlynkTimer

   float reads[samp_siz], sum;
    long int now, ptr;
    float  last, reader, start;
    float first, second, third, before, print_value;
    bool rising;
    int rise_count;
    int n;
    long int last_beat;

    for (int i = 0; i < samp_siz; i++)
      reads[i] = 0;
    sum = 0;
    ptr = 0;

    while(1)
    {
      // calculate an average of the  sensor
      // during a 20 ms period (this will eliminate
      // the 50  Hz noise caused by electric light
      n = 0;
      start = millis();
      reader = 0.;
      do
      {
        reader += analogRead (sensorPin);
        n++;
        now = millis();
      }
      while (now < start +  20);  
      reader /= n;  // we got an average
      
      // Add the  newest measurement to an array
      // and subtract the oldest measurement from  the array
      // to maintain a sum of last measurements
      sum -= reads[ptr];
      sum += reader;
      reads[ptr] = reader;
      last = sum / samp_siz;
      // now last holds the average of the values in the array

      // check  for a rising curve (= a heart beat)
      if (last > before)
      {
        rise_count++;
        if (!rising && rise_count > rise_threshold)
        {
          //  Ok, we have detected a rising curve, which implies a heartbeat.
          //  Record the time since last beat, keep track of the two previous
          //  times (first, second, third) to get a weighed average.
          // The rising  flag prevents us from detecting the same rise more than once.
          rising  = true;
          first = millis() - last_beat;
          last_beat = millis();

          // Calculate the weighed average of heartbeat rate
          // according  to the three last beats
          print_value = 60000. / (0.4 * first + 0.3 *  second + 0.3 * third);
          
          // Get the voltage reading from the LM35
          int reading = analogRead(tempsensorPin);
          int val = map(analogRead(Spo2sensorPin), 0, 1023, 0, 100);

          // Convert that reading into voltage
          float voltage = reading * (5.0 / 1024.0);

          // Convert the voltage into the temperature in Celsius
          float temperatureC = voltage * 100;

          // Serial.print(print_value);
          // Serial.print('\n');
          // // Print the temperature in Celsius
          // Serial.print("Temperature: ");
          // Serial.print(temperatureC);
          // Serial.print("\xC2\xB0"); // shows degree symbol
          // Serial.print("C  |  ");


          // lcd.setCursor(0,1); // Sets the location at which subsequent text written to the LCD will be displayed 
          lcd.setCursor(7,0); // Sets the location at which subsequent text written to the LCD will be displayed 
          lcd.print(print_value);
          lcd.setCursor(7,1); // Sets the location at which subsequent text written to the LCD will be displayed 
          lcd.print(temperatureC);
          // temp(print_value);
          Blynk.virtualWrite(V0, print_value);
          Blynk.virtualWrite(V1, temperatureC);
          Blynk.virtualWrite(V2, val);

          if(print_value > 150 || temperatureC > 50 || val < 90)
          {
            digitalWrite(buzzer, HIGH);
          }
          else
          {
            digitalWrite(buzzer, LOW);
          }
          
          // Serial.print(print_value);
          // Serial.print('\n');
          
          third = second;
          second  = first;
          // delay(1000);
          // lcd.clear(); // Clears the LCD screen 
          
        }
      }
      else
      {
        //  Ok, the curve is falling
        rising = false;
        rise_count = 0;
      }
      before = last;
      
      
      ptr++;
      ptr  %= samp_siz;

    }
}
