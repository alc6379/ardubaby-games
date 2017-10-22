#include <Arduboy2.h>
#include <ArduboyTones.h>

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

int counter;
int toneIndex = 0;
const char alphabet[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
  'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
  'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};


const uint16_t alphabetSong[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_C4,
  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4
};

const uint16_t alphabetScore[] PROGMEM = {
  NOTE_C4, 500, //A
  NOTE_C4, 500, //B
  NOTE_G4, 500, //C
  NOTE_G4, 500, //D
  NOTE_A4, 500, //E
  NOTE_A4, 500, //F
  NOTE_G4, 500, //G
  NOTE_F4, 500, //H
  NOTE_F4, 500, //I
  NOTE_E4, 500, //J
  NOTE_E4, 500, //K
  NOTE_D4, 250, //L
  NOTE_D4, 250, //M
  NOTE_D4, 250, //N
  NOTE_D4, 250, //O
  NOTE_C4, 500, //P
  NOTE_G4, 500, //Q
  NOTE_G4, 500, //R
  NOTE_F4, 500, //S
  NOTE_E4, 500, //T
  NOTE_E4, 500, //U
  NOTE_D4, 500, //V
  NOTE_G4, 250, NOTE_G4, 250, NOTE_G4, 500,//W 
  NOTE_F4, 500, //X
  NOTE_E4, 500, //Y
  NOTE_E4, 500, //Z
  NOTE_D4, 500, /* now I know my abc's... */
  NOTE_C4, 500, NOTE_C4, 500, NOTE_G4, 500, NOTE_G4, 500, NOTE_A4, 500, NOTE_A4, 500, NOTE_G4, 500,
  NOTE_F4, 500, NOTE_F4, 500, NOTE_E4, 500, NOTE_E4, 500, NOTE_D4, 500, NOTE_D4, 500, NOTE_C4, 500, TONES_END
};


// Stores the button state
uint8_t previousButtonState = 0;
uint8_t currentButtonState = 0;

void playSong() {
  sound.tones(alphabetScore);
}

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
  // put your setup code here, to run once:
  arduboy.begin();
  arduboy.clear();
  playSong();
  counter = 0;
}

void loop() {
  updateButtonState(arduboy);
  // put your main code here, to run repeatedly:
  arduboy.clear();
  if ( buttonJustPressed(RIGHT_BUTTON ) || buttonJustPressed( UP_BUTTON ) == true ) {
    if (counter <= 24) {
      //Increase counter by 1
      counter = counter + 1;
    }
    else {
      counter = 0;
    }
    sound.tone(alphabetSong[counter], 500);
  }
  //Check if the DOWN_BUTTON is being pressed
  if ( buttonJustPressed(LEFT_BUTTON ) || buttonJustPressed( DOWN_BUTTON ) == true ) {
    if (counter >= 1) {
      //Decrease counter
      counter = counter - 1;
    }
    else {
      counter = 25;
    }
    sound.tone(alphabetSong[counter], 500);
  }

  if (buttonJustPressed(A_BUTTON) || buttonJustPressed(B_BUTTON) == true) {
    playSong();
  }

  arduboy.setCursor(0, 0);
  arduboy.drawChar(50, 10, alphabet[counter], WHITE, BLACK, 6);
  arduboy.display();
}
