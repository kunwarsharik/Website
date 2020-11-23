#include <Wire.h>
#include <IRremote.h>

typedef uint16_t microseconds_t;
typedef uint16_t frequency_t;
static inline unsigned hz2khz(frequency_t f) { return f/1000U; }
static const long BAUD = 115200UL;
IRsend irsend;
long times=1;

const microseconds_t repeat_CHANNEL_DOWN[] PROGMEM = { 417U, 278U, 167U, 278U, 167U, 611U, 167U, 444U, 167U, 611U, 167U, 278U, 167U, 278U, 167U, 278U, 167U, 278U, 167U, 278U, 167U, 611U, 167U, 444U, 167U, 611U, 167U, 278U, 167U, 611U, 167U, 278U, 167U, 444U, 167U, 65535U };
const microseconds_t repeat_CHANNEL_UP[] PROGMEM = { 417U, 278U, 167U, 278U, 167U, 611U, 167U, 444U, 167U, 611U, 167U, 278U, 167U, 278U, 167U, 278U, 167U, 278U, 167U, 278U, 167U, 611U, 167U, 444U, 167U, 611U, 167U, 278U, 167U, 611U, 167U, 278U, 167U, 278U, 167U, 65535U };
const microseconds_t repeat_VOLUME_DOWN[] PROGMEM = { 417U, 278U, 167U, 278U, 167U, 611U, 167U, 444U, 167U, 611U, 167U, 278U, 167U, 278U, 167U, 278U, 167U, 278U, 167U, 278U, 167U, 611U, 167U, 444U, 167U, 611U, 167U, 278U, 167U, 444U, 167U, 278U, 167U, 444U, 167U, 65535U };
const microseconds_t repeat_VOLUME_UP[] PROGMEM = { 417U, 278U, 167U, 278U, 167U, 611U, 167U, 444U, 167U, 611U, 167U, 278U, 167U, 278U, 167U, 278U, 167U, 278U, 167U, 278U, 167U, 611U, 167U, 444U, 167U, 611U, 167U, 278U, 167U, 444U, 167U, 278U, 167U, 278U, 167U, 65535U };
static void sendRaw(const microseconds_t intro_P[], size_t lengthIntro, const microseconds_t repeat_P[],size_t lengthRepeat, frequency_t frequency, unsigned times) {
  microseconds_t intro[lengthIntro];
  microseconds_t repeat[lengthRepeat];
  memcpy_PF(intro, (uint_farptr_t) intro_P, sizeof(microseconds_t) * lengthIntro);
  memcpy_PF(repeat, (uint_farptr_t) repeat_P, sizeof(microseconds_t) * lengthRepeat);
  if (lengthIntro > 0U)
    irsend.sendRaw(intro, lengthIntro, hz2khz(frequency));
  if (lengthRepeat > 0U)
    for (unsigned i = 0U; i < times - (lengthIntro > 0U); i++)
      irsend.sendRaw(repeat, lengthRepeat, hz2khz(frequency));
}

int c,prev_c;
void setup() {
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent); /* register request event */
 Serial.begin(115200); /* start serial for debug */
 Serial.setTimeout(60000UL);
}

void loop() {
// long commandno = c;
// long times=1;
 
//Serial.println(times);
//   if (prev_c!=c){
   switch (c) {
    case 1:
      sendRaw(NULL, 0U, repeat_CHANNEL_DOWN, 36U, 36000U, times);
      Serial.println("sent channel down");
      break;
    case 2:
      sendRaw(NULL, 0U, repeat_CHANNEL_UP, 36U, 36000U, times);
      Serial.println("sent channel up");
      break;
    case 3:
      sendRaw(NULL, 0U, repeat_VOLUME_DOWN, 36U, 36000U, times);
      Serial.println("sent vol down");
      break;
    case 4:
      sendRaw(NULL, 0U, repeat_VOLUME_UP, 36U, 36000U, times);
      Serial.println("sent vol up");
      break;
    default:
//      Serial.println("Invalid number entered, try again");
      break;
      
//  }
  }
//  prev_c=c;
c=100;// spme random value
//  Serial.print(c);
delay(100);
 
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 
 while (0 <Wire.available()) {
   c = Wire.read();      /* receive byte as a character */
   Serial.println(c);          /* print the character */
   
  }
 
 Serial.println();             /* to newline */
}

//function that executes whenever data is requested from master
void requestEvent() {
 Wire.write("Hello NodeMCU");  /*send string on request */
}
