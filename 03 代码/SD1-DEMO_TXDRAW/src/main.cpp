#include <Arduino.h>
#include "TFT_eSPI.h"
#include "TJpg_Decoder.h"
#include "logo.h"
#include "emo/b4.h"
#include "emo/b5.h"
#include "emo/b6.h"
#include "emo/b7.h"

// 屏幕定义开始

// 屏幕分辨率定义
 #define TFT_WIDTH  240  // 屏幕宽度
 #define TFT_HEIGHT 240  // 屏幕高度
// 屏幕引脚定义
#define TFT_MISO  -1  // 未使用，设为 -1
#define TFT_MOSI  13  // 设置 MOSI 引脚 D13
#define TFT_SCLK  14  // 设置时钟引脚 D14
#define TFT_CS    0  // 设置片选控制引脚 D0
#define TFT_DC    0  // 设置数据/命令引脚 D0
#define TFT_RST   2  // 设置复位引脚 D2
#define TFT_BL    5  // 设置背光引脚 D5

//屏幕软件定义
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite clk = TFT_eSprite(&tft);

//屏幕颜色软件常量定义
const uint16_t bgColor = TFT_BLACK;
const uint16_t txtColor = TFT_WHITE;
const uint16_t sysColor = TFT_ORANGE;

// 屏幕定义结束

// 回调函数，用于将解码后的图像数据绘制到屏幕上
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h,
                uint16_t *bitmap) {
  if (y >= tft.height())
    return false;
  tft.pushImage(x, y, w, h, bitmap);
  return true;
}

void jpg_init() {
  TJpgDec.setJpgScale(1);// 设置 JPEG 缩放比例为 1
  TJpgDec.setSwapBytes(true);// 设置字节交换为 true
  TJpgDec.setCallback(tft_output);// 设置 JPEG 回调函数为 tft_output
}

// JPG 显示函数
void jpg_xs(int x, int y, const uint8_t *jpg, size_t size) {
  TJpgDec.drawJpg(x, y, jpg, size);
}

// 屏幕背光定义
void initlight(uint8_t brightness) { 
  pinMode(TFT_BL, OUTPUT); 
  uint16_t pwmBrightness = map(brightness, 0, 100, 0, 1023);
  analogWrite(TFT_BL, pwmBrightness);
}

// 清屏函数
void clear_screen() {
  tft.fillScreen(bgColor);
}


// 通用文本显示函数
void display_xs(const char *text, int x, int y, int width, int height,
                 uint16_t bgcolor, uint16_t textcolor, uint8_t fontSize) {
  clk.setColorDepth(8);
  clk.createSprite(width, height);
  clk.fillSprite(bgcolor);
  clk.setTextDatum(CC_DATUM);
  clk.setTextColor(textcolor, bgcolor);
  clk.drawString(text, width / 2, height / 2, fontSize);
  clk.pushSprite(x, y);
  clk.deleteSprite();
}

void init_pm() {
   tft.init();// 初始化 TFT 屏幕
  jpg_init();// 初始化 JPEG 解码器
  tft.fillScreen(bgColor);// 填充屏幕背景色为 bgColor
}



// 初始化全局变量
unsigned long prevBlinkTime = 0;
int blinkState = 0;
const unsigned long BLINK_INTERVAL = 300; 

// 定义眨眼函数
void biaoqin() {
  int x = 0, y = 60;
  if (millis() - prevBlinkTime > BLINK_INTERVAL) {
    // 切换眨眼状态
    blinkState = (blinkState + 1) % 10; 
    prevBlinkTime = millis();
  }

 
  switch (blinkState) {
    case 0:
     jpg_xs( x, y, b4, sizeof(b4));
      break;
    case 1:
      jpg_xs( x, y, b4, sizeof(b4));
      break;
    case 2:
      jpg_xs( x, y, b5, sizeof(b5));
      break;
    case 3:
      jpg_xs( x, y, b4, sizeof(b4));  
      break;
    case 4:
      jpg_xs( x, y, b5, sizeof(b5));
      break;
    case 5:
      jpg_xs( x, y, b5, sizeof(b5));         
      break;
    case 6:
      jpg_xs( x, y, b6, sizeof(b6));
      break;
    case 7:
      jpg_xs( x, y, b7, sizeof(b7));
      break;
    case 8:
      jpg_xs( x, y, b7, sizeof(b7));
      break;
    case 9:
      jpg_xs( x, y, b7, sizeof(b7)); 
      break;
    default:
      Serial.println("眨眼状态错误");
      break;
  }
}


void setup() {
  Serial.begin(115200);
  init_pm();      // 初始化屏幕
  initlight(50);   // 初始化背光
  jpg_xs(80, 40, logo, sizeof(logo));
  display_xs("Hello Txdraw !", 20, 160, 200, 24, bgColor, sysColor, 4);
  display_xs("SD1-EMO", 148, 210, 66, 24, bgColor, txtColor, 2);
  delay(2000);
  clear_screen();
}

void loop() {
  // 保持程序运行
  biaoqin();//
 
}