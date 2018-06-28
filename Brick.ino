void Brick() {
  //Bounce off Bricks
  SerialUSB.println("Do Brick");
  for (int8_t row = 0; row < ROWS; row++) {
    for (int8_t column = 0; column < COLUMNS; column++) {
      if (!isHit[row][column] && !bounced) {
        // Manage brick and ball collision
        red = 255 - (row + 2) * 6; green = column * 10; blue = (column + row * 1.5) * 8;
        // gb.display.setColor(gb.createColor(red, green, blue));
        // gb.display.fillRect(BrickWidth * column, BrickHeight * row + Ytop, BrickWidth, BrickHeight);
        draw_brick(type_brick[row][column],BrickWidth * column, BrickHeight * row + Ytop);
        if (balle.y <= (BrickHeight * (ROWS + 1) + Ytop)) {
        //If A collison has occuRED
        if (balle.y <= (BrickHeight * (row + 1) + Ytop) && balle.y >= (BrickHeight * row - balle.BSize + Ytop) &&
            balle.x <= (BrickWidth * (column + 1)) && balle.x >= (BrickWidth * column - balle.BSize)) {
          score = score + NbPointsBrick;
          brickCount++;
          isHit[row][column] = true; 
          // Manage if the ball have to change of vertical direction to avoid crazy moves

          // Test vertical collision
          if (balle.y < (BrickHeight * row  + Ytop)  || (balle.y > (BrickHeight * (row + 1) - balle.BSize + Ytop))) {
            //Only bounce once each ball move
            if (!bounced) {
              balle.moveY = - balle.moveY;
              bounced = true;
              if (LightBrick) { gb.lights.drawPixel(0, 0, gb.createColor(red, green, blue));gb.lights.drawPixel(1, 0, gb.createColor(red, green, blue)); }
              delay(15);
              gb.sound.tone(261, 200);
            }
          }
          //Test hoizontal collision
          else if (balle.x < (BrickWidth * column ) && (balle.x > BrickWidth * (column + 1)- balle.BSize ) && !bounced ) {
            //Only bounce once brick each ball move
            if (!bounced) {
              balle.moveX = - balle.moveX;
              bounced = true;
              if (LightBrick) { gb.lights.drawPixel(0, 0, gb.createColor(red, green, blue));gb.lights.drawPixel(1, 0, gb.createColor(red, green, blue)); }
              delay(15);
              gb.sound.tone(261, 200);
            }
          }
        }
      }
     }
    }
  }
}


// Draw the defined brick
void draw_brick(int8_t BrickType, int8_t XB, int8_t YB) {
  if (BrickType > 10) BrickType = defaultBonusBrick;
  gb.display.drawImage(XB, YB, BR[BrickType-1]);
}

