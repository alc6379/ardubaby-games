#include <ArduboyTones.h>

const uint16_t oldMcDonaldSong[] PROGMEM = {
  NOTE_G4, 250, //Old
  NOTE_G4, 250, NOTE_G4, 250, NOTE_D4, 250, //McDonald
  NOTE_E4, 250, //had
  NOTE_REST, 10,
  NOTE_E4, 250, //a
  NOTE_D4, 500, //farm
  NOTE_REST, 100,
  NOTE_B5, 250, //E
  NOTE_REST, 10,
  NOTE_B5, 250, //I
  NOTE_REST, 10,
  NOTE_A5, 250, //E
  NOTE_REST, 10,
  NOTE_A5, 250, //I
  NOTE_REST, 10,
  NOTE_G5, 750, //O
  TONES_END
};

const uint16_t tractorSound[] PROGMEM = {
  NOTE_G3, 100,
  NOTE_G3, 100,
  NOTE_G3, 100,
  NOTE_G3, 100,
  TONES_END
};

const uint16_t beepBeepSound[] PROGMEM = {
  NOTE_B4, 200,
  NOTE_REST, 100,
  NOTE_B4, 500,
  TONES_END
};

