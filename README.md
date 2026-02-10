

 SD1-EMO_ESP8266+7789

SD1表情款

效果
![输入图片说明](00%20%E6%95%88%E6%9E%9C/SD1-EMO.jpg)

应用于8266+7789显示屏，实现文字，图片展示，是一个非常好入门的代码。

芯片  ESP8266
屏幕  1.33 1.54 IPS7789
引脚定义

开源硬件 立创开源广场 小立牌

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

效果




