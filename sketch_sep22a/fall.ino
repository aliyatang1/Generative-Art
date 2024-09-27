#include <TFT_eSPI.h>  

TFT_eSPI tft = TFT_eSPI();  

const int numStars = 5;
int starPositions[numStars][2] = {
  {50, 70}, {200, 100}, {170, 120}, {30, 120}, {10, 110}
};  

void setup() {
  tft.init();
  tft.setRotation(1);  
  tft.fillScreen(0x0028);  

  // Draw the moon
  int moonX = tft.width()/2;  
  int moonY = 90;  
  int moonRadius = 25; 
  tft.fillCircle(moonX, moonY, moonRadius, 0xeef9);  

  // Draw craters on the moon
  drawCrater(moonX - 10, moonY - 5, 5, 0xD6B9);
  drawCrater(moonX + 5, moonY - 8, 3, 0xD6B9); 
  drawCrater(moonX, moonY + 10, 4, 0xD6B9);    

  drawStandingRabbit((tft.width()/2)+10, 20, TFT_WHITE);  
  drawStandingRabbit((tft.width()/2)-10, 20, TFT_WHITE); 

  // Draw clouds 
  drawCloud(50, 100, 15, TFT_WHITE);
  drawCloud(200, 80, 10, TFT_WHITE);  

  //draw bushes using cloud function
  drawCloud(30, 12, 7, 0x1b63);  
  drawCloud(180, 12, 5, 0x1b63);  
  drawCloud(190, 12, 8, 0x1b63); 
  drawCloud(200, 12, 5, 0x1b63); 
  
  for (int i = 0; i < numStars; i++) {
    drawStar(starPositions[i][0], starPositions[i][1], 5, TFT_YELLOW);
  }

  drawGrassWithSpecks(0, 0 , tft.width(), 10, 0x1b63, 0xFD20, 0xF800); 
}
//make the stars blink
void loop() {
  for (int i = 0; i < numStars; i++) {
    if (random(0, 10) < 5) {  
      drawStar(starPositions[i][0], starPositions[i][1], 5, 0x0028);
    } else { 
      drawStar(starPositions[i][0], starPositions[i][1], 5, TFT_YELLOW);
    }
  }
  
  delay(300);  
}

// Draw clouds
void drawCloud(int x, int y, int r, uint16_t color) {
  tft.fillCircle(x, y, r, color);          
  tft.fillCircle(x + r, y, r * 0.8, color);    
  tft.fillCircle(x - r, y, r * 0.9, color);    
  tft.fillCircle(x - (r / 2), y + r / 3, r * 0.7, color); 
  tft.fillCircle(x + (r / 2), y + r / 3, r * 0.7, color);  
  tft.fillCircle(x - r * 1.5, y - r / 4, r * 0.6, color);  
  tft.fillCircle(x + r * 1.5, y - r / 4, r * 0.6, color);  
}
 
//Draw star
void drawStar(int x, int y, int size, uint16_t color) {
  int halfSize = size / 2;
  tft.drawLine(x, y - halfSize, x, y + halfSize, color); 
  tft.drawLine(x - halfSize, y - halfSize, x + halfSize, y + halfSize, color);  
  tft.drawLine(x + halfSize, y - halfSize, x - halfSize, y + halfSize, color);  
}

// Draw craters on moon
void drawCrater(int x, int y, int r, uint16_t color) {
  tft.fillCircle(x, y, r, color); 
}

// Draw a rabbit
void drawStandingRabbit(int x, int y, uint16_t color) {
 // head
  tft.fillCircle(x, y + 10, 6, color);

  // body
  tft.fillEllipse(x, y , 10, 8, color); 

  //ears
  tft.fillEllipse(x-3, y + 15, 2, 7, color);  
  tft.fillEllipse(x+3, y + 15, 2, 7, color); 

  // legs
  tft.fillEllipse(x +6, y -5, 2, 5, color); 
  tft.fillEllipse(x -6, y - 5, 2, 5, color);  
  //tail
  tft.fillCircle(x, y -2, 2, color);
  tft.drawCircle(x, y -2, 2, TFT_BLACK);

}

//used ChatGPT to create orange and red specks in grass
void drawGrassWithSpecks(int x, int y, int width, int height, uint16_t grassColor, uint16_t orangeColor, uint16_t redColor) {
  // Fill the grass area with green
  tft.fillRect(x, y, width, height, grassColor);
  
  // Draw random orange and red specks on the grass
  for (int i = 0; i < 100; i++) {
    int speckX = x + random(0, width);
    int speckY = y + random(0, height);
    
    // Randomly choose between orange and red specks
    uint16_t speckColor = (random(0, 2) == 0) ? orangeColor : redColor;
  
    tft.drawPixel(speckX, speckY, speckColor);
  }
}

