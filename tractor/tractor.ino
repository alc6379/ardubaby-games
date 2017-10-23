#include <Arduboy2.h>
#include "OldMcDonald.h"
#include "BitMaps.h"
#include <ArduboyTones.h>

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
Sprites sprites;

enum facingDirection {right, left};
enum facingDirection tractorDirection = right;

const int MAX_X_POS = 103; //farthest to the left the tractor can go before it wraps around
const int MAX_Y_POS = 47; //farthest to the bottom the tractor can go before it wraps around
const int BEEP_COOLDOWN = 60; //delay playing "beep beep" if the kid is pressing it too quickly
const int SONG_COOLDOWN = 120;


int tractorPositionX = 0;
int tractorPositionY = 0;
int beepCount = 0;
int songCount = 0;
byte frame = 0;

void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.setFrameRate(30);
}

void loop() {
  bool moved = false;

  if (!(arduboy.nextFrame())) return;
  arduboy.clear();
  drawBackground();
  arduboy.pollButtons();

  if (tractorDirection == right) {
    sprites.drawSelfMasked(tractorPositionX, tractorPositionY, tractor_right, frame);
  }
  if (tractorDirection == left) {
    sprites.drawSelfMasked(tractorPositionX, tractorPositionY, tractor_left, frame);
  }
  if (arduboy.everyXFrames(1)) {
    if (arduboy.pressed(RIGHT_BUTTON)) {
      tractorPositionX = tractorPositionX + 3;
      if (tractorPositionX > MAX_X_POS) {
        tractorPositionX = 0;
      }
      tractorDirection = right;
      moved = true;
    }
    if (arduboy.pressed(LEFT_BUTTON)) {
      tractorPositionX = tractorPositionX - 3;
      if (tractorPositionX < 0) {
        tractorPositionX = MAX_X_POS + 1;
      }
      tractorDirection = left;
      moved = true;
    }
    if (arduboy.pressed(DOWN_BUTTON)) {
      tractorPositionY = tractorPositionY + 3;
      if (tractorPositionY > MAX_Y_POS) {
        tractorPositionY = 0;
      }
      moved = true;
    }
    if (arduboy.pressed(UP_BUTTON)) {
      tractorPositionY = tractorPositionY - 3;
      if (tractorPositionY < 0) {
        tractorPositionY = MAX_Y_POS + 1;
      }
      moved = true;
    }
  }
  if (arduboy.everyXFrames(2)) {
    frame++;
  }

  if (frame > 1) frame = 0;

  if (moved) {
    sound.tones(tractorSound);
  }
  if (arduboy.justPressed(A_BUTTON)) {
    if (beepCount == 0 || beepCount > BEEP_COOLDOWN) {
      sound.tones(beepBeepSound);
      beepCount = 1;
    }
  }
  if (beepCount > 0) {
    beepCount++;
  }
  if (arduboy.justPressed(B_BUTTON)) {
    if (songCount == 0 || songCount > SONG_COOLDOWN) {
      sound.tones(oldMcDonaldSong);
      songCount = 1;
    }
  }

  if (songCount > 0) {
    songCount++;
  }
  arduboy.display();
}

void drawBackground() {
  /* ganked background code from
      https://community.arduboy.com/t/make-your-own-arduboy-game-part-6-graphics/2440
  */
  for ( int backgroundx = 0; backgroundx < 128; backgroundx = backgroundx + 8 ) {
    //For each row in the column
    for ( int backgroundy = 0; backgroundy < 64; backgroundy = backgroundy + 16 ) {
      //Draw a background tile
      arduboy.drawBitmap( backgroundx, backgroundy, background, 8, 8, WHITE );
    }
  }
}

