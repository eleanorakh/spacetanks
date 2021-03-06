#ifndef INTRO_H
#define INTRO_H

#include "globals.h"
#include "music.h"

#define INTRO_MESSAGE_COUNT 6
#define INTRO_MESSAGE_DURATION 120

const char *introMessages[] = {
  "The year is 20XX",
  "War is beginning",
  "Dracula takes\n   to the stars",
  "Man your tank\n   for great honor",
  "...",
  "...and survival!"
};

uint8_t introMessage;
boolean introFinished;
uint8_t introFrameCount;

void initIntro() {
  introMessage = 0;
  introFinished = false;
  introFrameCount = 0;
  arduboy.setTextSize(1);
  arduboy.setTextWrap(true);

  arduboy.audio.on();
  arduboy.tunes.playScore(powerIntroMusic);
}

void exitIntro() {
  introFinished = true;
  arduboy.tunes.stopScore();
}

void drawIntro() {
  introFrameCount++;
  if(arduboy.everyXFrames(INTRO_MESSAGE_DURATION)) { introMessage++; }
  if(introMessage >= INTRO_MESSAGE_COUNT) { exitIntro(); }
  if(introFrameCount > FRAMERATE &&
      (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON))) {
    exitIntro();
  }

  if(!introFinished) {
    arduboy.setCursor(18, 20);
    arduboy.print(introMessages[introMessage]);
  }
}


#endif
