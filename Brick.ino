void Brick() {
  //Bounce off Bricks
  // SerialUSB.print("Do Brick");
  for (int8_t row = 0; row < ROWS; row++) {
    // SerialUSB.println(" ");
    // SerialUSB.print("Row "); SerialUSB.print(row);
    for (int8_t column = 0; column < COLUMNS; column++) {
      // SerialUSB.print(type_brick[row][column]);SerialUSB.print("|");
      if (!isHit[row][column] ) {
        // Manage brick and ball collision
        if (type_brick[row][column] > 0) {
          draw_brick(type_brick[row][column], BrickWidth * column, BrickHeight * row + Ytop);
          if (balle.y <= (BrickHeight * (ROWS + 1) + Ytop)) {
            
             // Test vertical collision
              if (balle.moveY > 0) {
                 if (balle.y <= (BrickHeight * (row+1)  + Ytop - balle.BSize) && (balle.y >= (BrickHeight * row  + Ytop - balle.BSize) && (balle.x > (BrickWidth * column - 0.5*balle.BSize)) && (balle.x  < (BrickWidth * (column + 1) - 0.5 *balle.BSize))))  Y_bounce(row,column); 
              } else if (balle.y <= (BrickHeight * (row + 1) + Ytop ) && balle.y >= (BrickHeight * row  + Ytop )  && (balle.x > (BrickWidth * column - 0.5*balle.BSize)) && (balle.x  < (BrickWidth * (column + 1) - 0.5 *balle.BSize)))   Y_bounce(row,column);
              
              /* //Test hoizontal collision
              else if (balle.x <= (BrickWidth * (column + 1) - balle.moveX - 0.5*balle.BSize+1)) {
                if (balle.moveX < 0) X_bounce(row,column);
              } else if (balle.x >= (BrickWidth * column  - 0.5*balle.BSize - balle.moveX -1)) {
                if (balle.moveX > 0) X_bounce(row,column); 
              
              }  // -- End horizontal collision */
          } // -- End test Y (Ball in Brick zone)
        }  // -- End brique > 0
      }  // -- End test isHit
    } // -- End for Column
  } // --End for Row
} // -- End Brick()


// Draw the defined brick
void draw_brick(int8_t BrickType, int8_t XB, int8_t YB) {
  if (BrickType > 10) BrickType = defaultBonusBrick;
  if (BrickType > 0)  gb.display.drawImage(XB, YB, BR[BrickType - 1]);
}

void Collision(int8_t r,int8_t c ) {
  //If a collison has occured
  if (type_brick[r][c] > 1) {
         brickCount++;
         score = score + NbPointsBrick;
         SerialUSB.print("Collision => type_brick[r][c]:");
         SerialUSB.println(type_brick[r][c]);
         if(type_brick[r][c] == 11) {gb.sound.fx(SBonus); Add_bonus(type_brick[r][c],BrickWidth * c,((r+1)*BrickHeight  + Ytop));} 
         if(type_brick[r][c] == 18) {gb.sound.fx(SLostlife); Add_bonus(type_brick[r][c],BrickWidth * c,((r+1)*BrickHeight  + Ytop));}  
         isHit[r][c] = true;
  }
}

void Y_bounce(int8_t r,int8_t c) {
  //Only bounce once each ball move
  Collision(r,c);
  if (!bounced) {
    balle.moveY = - balle.moveY + random(-1, 1) / 6;
    Bounce();
  }
}

void X_bounce(int8_t r,int8_t c) {
  //Only bounce once each ball move
  Collision(r,c);
  if (!bounced) {
    balle.moveX = - balle.moveX + random(-1, 1) / 6;
    Bounce();
  }
}

void Bounce() {
    delay(5);
    bounced = true;
    gb.sound.tone(261, 200);
}

