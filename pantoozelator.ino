#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#define TFT_CS        10
#define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Every 50 marks is an alternating color
const byte kSpokes = 10; // number of spokes on the wheel
// number of spins equal to 20 feet, wheel is 15"
// the three extra spokes is a manual adjustment from testing.
const byte kMarkSpins = 5 * kSpokes + 3;
const unsigned int  kSprayTime = 250;  // time, in milliseconds to spray the paint.

const byte kSpray1 = 4;
const byte kSpray2 = 3;

const byte kPrime1 = 6;
const byte kPrime2 = 5;

const byte kHallPin = 2;

unsigned long sprayTime1 = 0;
unsigned long sprayTime2 = 0;
unsigned int sprays = 0;
unsigned int spins = 0;
unsigned int nextSpray = kMarkSpins;

volatile byte state = LOW;

unsigned long now = 1;
byte spraying = 0;
byte spray2 = 0;

void setup() {
  pinMode(kHallPin, INPUT_PULLUP);
  pinMode(kSpray1, OUTPUT);
  pinMode(kSpray2, OUTPUT);
  pinMode(kPrime1, INPUT_PULLUP);
  pinMode(kPrime2, INPUT_PULLUP);
  
  // Interrupt 0 is on Pin #2.
  attachInterrupt(0, count, CHANGE);
  
  digitalWrite(kSpray1, HIGH);
  digitalWrite(kSpray2, HIGH);
  now = millis();

  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setRotation(1); // use 1 or 3
  tft.fillScreen(ST77XX_BLACK);
  testdrawtext("LILO loading Linux...", ST77XX_WHITE);
  tft.fillScreen(ST77XX_BLACK); 
}


unsigned long count_now;
unsigned long count_last = 0;
byte hallState = HIGH;
byte lastHallState = HIGH;

void loop() {
  now = millis();
  
  if (digitalRead(kPrime1) == LOW) {
    sprayTime1 = now + 100;
  } else if (digitalRead(kPrime2) == LOW) {
    sprayTime2 = now + 100;
  }
  
  spraying = sprayTime1 > now || sprayTime2 > now;
  
  digitalWrite(kSpray1, sprayTime1 > now ? LOW : HIGH);
  digitalWrite(kSpray2, sprayTime2 > now ? LOW : HIGH);
  
  if (now % 250 == 0) {
    updateDisplay();
  }
}

void count() {
  count_now = millis();
  hallState = digitalRead(kHallPin);
  //if (count_now > sprayTime1 + 250 && count_now > sprayTime2 + 250 && digitalRead(kHallPin) == LOW) {
  if (count_now > count_last + 1 && lastHallState != hallState) { // && digitalRead(kPrime1) == HIGH && digitalRead(kPrime2) == HIGH) {
    count_last = count_now;
    spins++;
    if (spins >= nextSpray) {
        sprays ++;
        if (sprays % 50 == 0) {
          sprayTime2 = millis() + kSprayTime;
        } else {
          sprayTime1 = millis() + kSprayTime;
        }
        nextSpray += kMarkSpins;
    }
  }
}


void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

const char* boolToStr(int value) {
  return value == 1 ? "On " : "Off";
}

char d_num[16];


void updateDisplay() {

  tft.setCursor(0,0);
  tft.setTextColor(ST77XX_RED, ST77XX_BLUE);
  tft.println("Pantozalator PRIME        ");
  tft.println("");
  tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);

  tft.print("Spokes: ");
  tft.println(spins);
  tft.print("Sprays: ");
  itoa(sprays, d_num, 10);
  tft.println(d_num);
  tft.println("");
  
  // output the "prime" status
  tft.print("Prime Tank 1: ");
  tft.println(boolToStr(digitalRead(kPrime1) == LOW));
  tft.print("Prime Tank 2: ");
  tft.println(boolToStr(digitalRead(kPrime2) == LOW));
  
  // and if we are spraying
  tft.println("");
  tft.print("Spraying: ");
  tft.println(boolToStr(spraying));
  
  tft.println("");
  tft.print("On spoke? ");
  tft.println(boolToStr(digitalRead(kHallPin) == LOW));
}
