#include <Wire.h>
#include <U8g2lib.h>
#include <bitmaps.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(
  U8G2_R2,          // rotate 180°
  U8X8_PIN_NONE
);


const int leftTouch = 27;
const int middleTouch = 26;
const int rightTouch = 25;

int book = 1;
int page = 1;
int lastBook;
int lastPage;

void setup() {

  Wire.begin(21, 22);
  u8g2.begin();
  
  
  pinMode(leftTouch, INPUT);
  pinMode(middleTouch, INPUT);
  pinMode(rightTouch, INPUT);

  Serial.begin(115200);

}

void loop() {

  lastBook = book;
  lastPage = page;

  pageSelect();
  drawPage();
  
  delay(100);

}

void runGame() {
  
}

void pageSelect() {

  if ((lastBook != book) || (lastPage != page)) {
    u8g2.clearBuffer();
  }
  if (digitalRead(leftTouch) == HIGH) {
    
    book++;
    
    if (book == 3) {
      book = 1;
    }
    while (digitalRead(leftTouch) == HIGH) {
      delay(1);
    }
  }

  if (digitalRead(rightTouch) == HIGH) {
    
    page++;
    
    if (page == 4) {
      page = 1;
    }
    while (digitalRead(rightTouch) == HIGH) {
      delay(1);
    }
  }

  if (digitalRead(middleTouch) == HIGH) {

    page--;
    
    if (page == 0) {
      page = 3;
    }
    while (digitalRead(middleTouch) == HIGH) {
      delay(1);
    }
  }
}

/*
Book 1 cointains page values 1-6
*/

void drawPage() {
  switch (book) {
    case 1:
      switch (page) {
        case 1:
          u8g2.drawXBMP(0,0,128,64, hellokittyidle);
          break;
        case 2:
          u8g2.drawXBMP(0,0,128,64, hellokittyhappy);
          break;
        case 3:
          u8g2.drawXBMP(0,0,128,64, hellokittylove);
          break;
      }
    case 2:
      switch (page) { 
        case 1:
          u8g2.drawXBMP(0,0,128,64, kuromiidle);
          break;
        case 2:
          u8g2.drawXBMP(0,0,128,64, kuromismile);
          break;
        case 3:
          u8g2.drawXBMP(0,0,128,64, kuromihappy);
          break;
      }
      break;
  }
  if ((lastBook == book) && (lastPage == page)) {
    delay(1);
  }
  if ((lastBook != book) || (lastPage != page)) {
    u8g2.sendBuffer();
  }
}
