#include <TimerFreeTone.h>
#include <toneAC.h>
#include <MD_TCS230.h>
#include <FreqCount.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>
#include <math.h>

#define cs 10
#define dc 9
#define rst 8
#define sclk 6
#define mosi 7

// Color definitions
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define GREY 0xC618

// Pin definitions
#define S0_OUT 4
#define S1_OUT 5
#define S2_OUT 3
#define S3_OUT 2

// Buzzer
#define BUZZER_PIN 30

int R = 0;
int G = 0;
int B = 0;

MD_TCS230 CS(S2_OUT, S3_OUT, S0_OUT, S1_OUT);

int state = 0;

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, mosi, sclk, rst);

int freq;

bool activeRED = false;
bool activeBLUE = false;
bool activeGREEN = false;
bool activeCYAN = false;
bool activeORANGE = false;
bool activeVIOLET = false;
bool activeYELLOW = false;

void setup()
{

  Serial.begin(9600);
  Serial1.begin(9600); // bluetooth

  pinMode(BUZZER_PIN, OUTPUT); // buzzer

  tft.initR(INITR_144GREENTAB); // initialize a ST7735S chip, black tab

  drawBlackScreen();

  tft.setCursor(20, 30);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("  HEAR ");

  tft.setCursor(20, 50);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print(" COLORS ");

  tft.setCursor(20, 70);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("-INATOR ");

  tft.setCursor(20, 100);
  tft.setTextColor(RED);
  tft.setTextSize(1);
  tft.print(" by serju ");

  delay(1000);

  drawBlackScreen();

  tft.setCursor(10, 30);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("SET BLACK");
  delay(5000);

  CS.begin();
  CS.read();
}

void loop()
{

  if (state == 0)
  {
    if (CS.available())
    {
      sensorData sd;
      CS.getRaw(&sd);
      CS.setDarkCal(&sd);
      Serial.println("Black Calibration Set");
      state++;
      drawBlackScreen();

      tft.setCursor(10, 30);
      tft.setTextColor(WHITE);
      tft.setTextSize(2);
      tft.print("SET WHITE");

      delay(5000);
      CS.read();
    }
  }
  else if (state == 1)
  {
    if (CS.available())
    {
      sensorData sd;
      CS.getRaw(&sd);
      CS.setWhiteCal(&sd);
      Serial.println("White Calibration Set");
      drawBlackScreen();

      tft.drawRect(30, 60, 70, 60, WHITE);
      state++;
    }
  }
  else
  {
    readColorsSelections();
    readSensor();
  }
}

void readColorsSelections()
{

  if (Serial1.available() > 0)
  {

    char value_bt[3];
    Serial1.readBytes(value_bt, 2);
    value_bt[2] = '\0';

    // RED
    if (strcmp(value_bt, "10") == 0)
      activeRED = false;
    if (strcmp(value_bt, "11") == 0)
      activeRED = true;

    // ORANGE
    if (strcmp(value_bt, "20") == 0)
      activeORANGE = false;
    if (strcmp(value_bt, "21") == 0)
      activeORANGE = true;

    // YELLOW
    if (strcmp(value_bt, "30") == 0)
      activeYELLOW = false;
    if (strcmp(value_bt, "31") == 0)
      activeYELLOW = true;

    // GREEN
    if (strcmp(value_bt, "40") == 0)
      activeGREEN = false;
    if (strcmp(value_bt, "41") == 0)
      activeGREEN = true;

    // CYAN
    if (strcmp(value_bt, "50") == 0)
      activeCYAN = false;
    if (strcmp(value_bt, "51") == 0)
      activeCYAN = true;

    // BLUE
    if (strcmp(value_bt, "60") == 0)
      activeBLUE = false;
    if (strcmp(value_bt, "61") == 0)
      activeBLUE = true;

    // VIOLET
    if (strcmp(value_bt, "70") == 0)
      activeVIOLET = false;
    if (strcmp(value_bt, "71") == 0)
      activeVIOLET = true;
  }
}

void playColor(String colorName, int freq)
{
  Serial.print("aici");
  int duration = 500;
  noToneAC();

  if (colorName == "red" && activeRED)
  {
    TimerFreeTone(BUZZER_PIN, freq, duration);
  }
  else if (colorName == "orange" && activeORANGE)
  {
    TimerFreeTone(BUZZER_PIN, freq, duration);
  }
  else if (colorName == "yellow" && activeYELLOW)
  {
    TimerFreeTone(BUZZER_PIN, freq, duration);
  }
  else if (colorName == "green" && activeGREEN)
  {
    TimerFreeTone(BUZZER_PIN, freq, duration);
  }
  else if (colorName == "cyan" && activeCYAN)
  {
    TimerFreeTone(BUZZER_PIN, freq, duration);
  }
  else if (colorName == "blue" && activeBLUE)
  {
    TimerFreeTone(BUZZER_PIN, freq, duration);
  }
  else if (colorName == "violet" && activeVIOLET)
  {
    TimerFreeTone(BUZZER_PIN, freq, duration);
  }
  else
  {
    noToneAC();
  }
  delay(700);
}

void drawBlackScreen()
{
  tft.fillScreen(BLACK);
  // Draw white frame
  tft.drawRect(0, 0, 127, 159, WHITE);
  tft.drawRect(1, 1, 127, 159, WHITE);
}

uint16_t convertRGB24toRGB565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r / 8) << 11) | ((g / 4) << 5) | (b / 8);
}

float rgbToWavelenght(int r, int g, int b){
    float R = r / 255.0;
    float G = g / 255.0;
    float B = b / 255.0;


    // rgb to hue
    float hue;
    float maxV = max(R, max(G,B));
    float minV = min(R, min(G,B));
    
    if(maxV == R)
      hue = (G-B)/(maxV-minV);
      
    if(maxV == G)
      hue = 2.0 + (B-R)/(maxV-minV);
      
    if(maxV == B)
      hue = 4.0 + (R-G)/(maxV-minV);

    hue *= 60.0;
    if(hue < 0.0)
      hue += 360.0;

    // hue to waveleght
    
    // waveleght  -> [400, 700]
    // hue        -> [0, 270]
    float wavelenght = 700 - (300/270 * hue);

    return wavelenght;
    
}

void rgbToThz(int r, int g, int b, String &color, int &freqThz){

    //float lightSpeed = 3e8;
    
   
    float wln = rgbToWavelenght(r, g, b);
    Serial.print(wln);
    
    //freqThz = (lightSpeed / wln) / 1e12;

    // assign wavelength to color
    if(wln >= 400 && wln <= 425){
      color = "violet";
      freqThz = 762;
    } 

    if(wln > 425 && wln <= 465){
      color = "blue";
      freqThz = 639;
    } 
    
    if(wln > 465 && wln <= 480){
      color = "cyan";
      freqThz = 604;
    } 

    if(wln > 480 && wln <= 550){
      color = "green";
      freqThz = 562;
    }    

    if(wln > 550 && wln <= 580){
      color = "yellow";
      freqThz = 512;
    }     

    if(wln > 580 && wln <= 630){
      color = "orange";
      freqThz = 483;
    }      

    if(wln > 630 && wln <= 700){
      color = "red";
      freqThz = 456;
    }   

    Serial.print(" ");
    Serial.println(color);
    
}

String lastColor = "black";
void readSensor()
{
  static bool waiting = false;

  if (!waiting)
  {
    CS.read();
    waiting = true;
  }
  else
  {
    if (CS.available())
    {
      colorData rgb;
      String colorName;
      int freq;

      CS.getRGB(&rgb);
      /*
      Serial.print("RGB [");
      Serial.print(rgb.value[TCS230_RGB_R]);
      Serial.print(",");
      Serial.print(rgb.value[TCS230_RGB_G]);
      Serial.print(",");
      Serial.print(rgb.value[TCS230_RGB_B]);
      Serial.println("]");
      */

      R = rgb.value[TCS230_RGB_R];
      G = rgb.value[TCS230_RGB_G];
      B = rgb.value[TCS230_RGB_B];

      int color = convertRGB24toRGB565(R, G, B); // Convertion to 16bit color for the display

      rgbToThz(R, G, B, colorName, freq);
      
      //Serial.println(colorName);
      playColor(colorName, freq);
      tft.setCursor(35, 30);
      tft.setTextColor(WHITE);
      tft.setTextSize(2);
      tft.print(colorName);

      if(colorName != lastColor){
        tft.fillRect(31, 30, 80, 20, BLACK);
        lastColor = colorName;
      }

      delay(100);

      tft.fillRect(31, 61, 68, 58, color);

      waiting = false;
    }
  }
}
