#include <Arduboy2.h>
#include "OldMcDonald.h";
#include <ArduboyTones.h>

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
Sprites sprites;

enum facingDirection {right, left};
enum facingDirection tractorDirection = right;

const int MAX_X_POS = 103; //farthest to the left the tractor can go before it wraps around
const int MAX_Y_POS = 47; //farthest to the bottom the tractor can go before it wraps around

const byte PROGMEM tractor_left[] = {
  24, 16,
  //frame 0
  0x00, 0x40, 0xe0, 0xa0, 0xa0, 0xa0, 0xe0, 0xb8, 0xa0, 0xa0, 0xff, 0x43, 0x43, 0xc3, 0xff, 0xc3, 0xc3, 0x7f, 0x58, 0x50, 0xd0, 0xb0, 0x40, 0x80,
  0x3f, 0x0f, 0x3d, 0x66, 0x4a, 0x52, 0x66, 0x3d, 0x0f, 0x0f, 0x1f, 0x1e, 0x1e, 0x1f, 0x1f, 0x31, 0x60, 0x4a, 0x44, 0x4a, 0x60, 0x31, 0x1f, 0x00,
  //frame 1
  0x00, 0x40, 0xe0, 0xa0, 0xa0, 0xa2, 0xe4, 0xb8, 0xa0, 0xa0, 0xff, 0x43, 0x43, 0xc3, 0xff, 0xc3, 0xc3, 0x7f, 0x58, 0x50, 0xd0, 0xb0, 0x40, 0x80,
  0x3f, 0x0f, 0x3d, 0x66, 0x52, 0x4a, 0x66, 0x3d, 0x0f, 0x0f, 0x1f, 0x1e, 0x1e, 0x1f, 0x1f, 0x31, 0x60, 0x44, 0x4e, 0x44, 0x60, 0x31, 0x1f, 0x00

};

const byte PROGMEM tractor_right[] = {
  24, 16,
  //frame 0
  0x80, 0x40, 0xb0, 0xd0, 0x50, 0x58, 0x7f, 0xc3, 0xc3, 0xff, 0xc3, 0x43, 0x43, 0xff, 0xa0, 0xa0, 0xb8, 0xe0, 0xa0, 0xa0, 0xa0, 0xe0, 0x40, 0x00,
  0x00, 0x1f, 0x31, 0x60, 0x4a, 0x44, 0x4a, 0x60, 0x31, 0x1f, 0x1f, 0x1e, 0x1e, 0x1f, 0x0f, 0x0f, 0x3d, 0x66, 0x52, 0x4a, 0x66, 0x3d, 0x0f, 0x3f,

  //frame 1
  0x80, 0x40, 0xb0, 0xd0, 0x50, 0x58, 0x7f, 0xc3, 0xc3, 0xff, 0xc3, 0x43, 0x43, 0xff, 0xa0, 0xa0, 0xb8, 0xe4, 0xa2, 0xa0, 0xa0, 0xe0, 0x40, 0x00,
  0x00, 0x1f, 0x31, 0x60, 0x44, 0x4e, 0x44, 0x60, 0x31, 0x1f, 0x1f, 0x1e, 0x1e, 0x1f, 0x0f, 0x0f, 0x3d, 0x66, 0x4a, 0x52, 0x66, 0x3d, 0x0f, 0x3f
};

uint8_t previousButtonState = 0;
uint8_t currentButtonState = 0;

int tractorPositionX = 0;
int tractorPositionY = 0;
byte frame = 0;

// Needs to be called at the start of the loop function
void updateButtonState(Arduboy2 &ab)
{
  previousButtonState = currentButtonState;
  currentButtonState = ab.buttonsState();
}

// Returns if a button was just pressed
bool buttonJustPressed(uint8_t button)
{

  if (!(previousButtonState & button) && (currentButtonState & button))
  {
    return true;
  }
  return false;
}

void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.setFrameRate(15);
}

void loop() {
  bool moved = false;

  if (!(arduboy.nextFrame())) return;
  arduboy.clear();

  if (tractorDirection == right) {
    sprites.drawOverwrite(tractorPositionX, tractorPositionY, tractor_right, frame);
  }
  if (tractorDirection == left) {
    sprites.drawOverwrite(tractorPositionX, tractorPositionY, tractor_left, frame);
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
  if (arduboy.pressed(A_BUTTON)) {
    sound.tones(beepBeepSound);
  }
  if (arduboy.pressed(B_BUTTON)) {
    sound.tones(oldMcDonaldSong);
  }
  arduboy.display();
}
