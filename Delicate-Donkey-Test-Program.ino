#include <Servo.h>
#include "Delicate-Donkey.h"


unsigned char STATE = 0;
unsigned char SUBSTATE = 0;
unsigned char MOVESTATE = 0;

#define EXPLORE 1
#define DANCE 2
#define TEST 3
#define POLICE 4
#define RANDOM 5

#define STOP 0
#define FORWARD 9
#define BACKWARD 1
#define TURNLEFT 2
#define TURNRIGHT 3
#define STUCK 4
#define FOLLOW 5
#define CRAZY 6
#define SPINLEFT 7
#define SPINRIGHT 8

unsigned char red[3] = {255, 0, 0};
unsigned char blue[3] = {0, 0, 255};

unsigned short timer = 0;
unsigned char speed = 50;
boolean accelerating = false;

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  display.setup();
  display.clear();
  display.writeDisplay();
  drive.setup();
  led.setup();
  buzzer.setup();
  Servo.setup();
  distanceSensor.setup();
  distanceSensor_2.setup();
}

void explore(){
  // Serial.println("d1:" + String(distanceSensor.get_distance()));
  // Serial.println("d2:" + String(distanceSensor.get_distance()));
  if (distanceSensor_2.get_distance() >= 20){
    MOVESTATE = BACKWARD;
  } else if (distanceSensor.get_distance() >= 20 ){
    MOVESTATE = FORWARD;
  } else {
    led.set(0, 255, 255);
    MOVESTATE = SPINLEFT;
  }
  if (timer == 50000){
    randomizeState();
  }
}


boolean song1_done = false;
boolean song2_done = false;

void dance(){
  timer++;
  if (!song1_done){
    song1();
  } else if (song1_done && timer > 3000){
    song2();
  }

 if (song2_done){
   randomizeState();
 }
  if (timer == 100) {
    speed = 200;
    MOVESTATE = SPINLEFT;
  }
  if (timer == 10000){
    speed = 200;
    MOVESTATE = SPINRIGHT;
  }
  if (timer >= 20000){
    speed = 50;
    if (timer % 1000 == 0 && random(2) == 0){
      MOVESTATE = FORWARD;
    } else {
      MOVESTATE = BACKWARD;
    }
  }
}

unsigned short melody[] = {
  NOTE_E5, NOTE_E5, 0, NOTE_E5,
  0, NOTE_C5, NOTE_E5, 0,
  NOTE_G5, 0, 0,  0,
  NOTE_G4, 0, 0, 0,
 
  NOTE_C5, 0, 0, NOTE_G4,
  0, 0, NOTE_E4, 0,
  0, NOTE_A4, 0, NOTE_B4,
  0, NOTE_ASHARP4, NOTE_A4, 0,
 
  NOTE_G4, NOTE_E5, NOTE_G5,
  NOTE_A5, 0, NOTE_F5, NOTE_G5,
  0, NOTE_E5, 0, NOTE_C5,
  NOTE_D5, NOTE_B4, 0, 0,
 
  NOTE_C5, 0, 0, NOTE_G4,
  0, 0, NOTE_E4, 0,
  0, NOTE_A4, 0, NOTE_B4,
  0, NOTE_ASHARP4, NOTE_A4, 0,
 
  NOTE_G4, NOTE_E5, NOTE_G5,
  NOTE_A5, 0, NOTE_F5, NOTE_G5,
  0, NOTE_E5, 0, NOTE_C5,
  NOTE_D5, NOTE_B4, 0, 0
};
//Mario main them tempo
unsigned char tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

unsigned short notes1[] = {       //Note of the song, 0 is a rest/pulse
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,

   NOTE_A4, NOTE_A4, 
   //Repeat of first part
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,
   //End of Repeat

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
};

unsigned short duration[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,

  250, 125,
  //Rpeat of First Part
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,
  //End of Repeat
  
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500,

  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500
};

unsigned char song_pos = 0;
unsigned short wait = 0;


void song1(){
  // Serial.println("Wait: " + String(wait) + "song_pos:" + String(song_pos));
  if (song_pos >= 203){
    buzzer.turnOff();
    song_pos = 0;
    wait = 0;
    timer = 0;
    song1_done = true;
    Serial.println("Done:" + timer);
    return;
  }
  wait+=1;
  if (song_pos == 0){
    tone(BUZZER_1, notes1[song_pos], duration[song_pos] / 2);
    song_pos++;
  } else {
    if (wait <= duration[song_pos - 1] / 2){
      led.set(0, 0, 0);
      tone(BUZZER_1, notes1[song_pos], duration[song_pos]);
    }
    if (wait == duration[song_pos - 1] / 2){
      led.set(255, 0, 0);
      wait = 0;
      song_pos++;
    }
  }

}

void song2(){
  // Serial.println("Wait: " + String(wait) + "song_pos:" + String(song_pos));
  if (song_pos >= 78){
    buzzer.turnOff();
    song2_done = true;
    wait = 0;
    song_pos = 0;
    return;
  }
  wait+=1;
  if (song_pos == 0){
    tone(BUZZER_1, melody[song_pos], 5 * tempo[song_pos]);
    song_pos++;
  } else {
    if (wait <= 10 * tempo[song_pos - 1]){
      led.set(0, 0, 0);
      tone(BUZZER_1, melody[song_pos], 5 * tempo[song_pos]);
    }
    if (wait == 5 * tempo[song_pos - 1]){
      led.set(255, 0, 0);
      wait = 0;
      song_pos++;
    }
  }
}

unsigned char animation_time = 100;

void randomMove(){
  if (timer == 30000){
    randomizeState();
  }
  if (SUBSTATE == CRAZY){
    if (timer % 1000 == 0){
      speed = 255;
      switch(random(5)){
        case 0:
          MOVESTATE = FORWARD;
          break;
        case 1:
          MOVESTATE = BACKWARD;
          break;
        case 2:
          MOVESTATE = SPINLEFT;
          break;
        case 3:
          MOVESTATE = SPINRIGHT;
          break;
        case 4:
          SUBSTATE = 0;
          speed = 70;
          animation_time = 100;
          break;
      }
    }
  } else {
    if (timer % 5000 == 0){
      
      if (random(10) == 0){
        SUBSTATE = CRAZY;
        animation_time = 50;
      } else {
        SUBSTATE = 0;
        animation_time = 100;
      }
      
      switch(random(4)){
        case 0:
          accelerating = true;
          MOVESTATE = FORWARD;
          break;
        case 1:
          accelerating = true;
          MOVESTATE = BACKWARD;
          break;
        case 2:
          speed = 50;
          MOVESTATE = SPINLEFT;
          break;
        case 3:
          speed = 50;
          MOVESTATE = SPINRIGHT;
          break;
      }
    }
  }
}

void test(){
  if (timer % 10 > 5){
    led.set(255, 255, 255);
  }
  if (timer == 10){
    buzzer.playNote(500, 10);
    MOVESTATE = FORWARD;
    speed = 60;
  } else if (timer == 4000){
    buzzer.playNote(600, 10);
    MOVESTATE = BACKWARD;
    speed = 60;
  } else if (timer == 8000){
    buzzer.playNote(700, 10);
    speed = 40;
    MOVESTATE = SPINLEFT;
  } else if (timer == 12000){
    
    buzzer.playNote(800, 10);
    speed = 40;
    MOVESTATE = SPINRIGHT;
  } else if (timer == 16000){
    randomizeState();
  }
}

boolean light_red = true;
boolean siren_on = false;
boolean freq_incre = true;
unsigned short siren_freq = 200;
unsigned char siren_counter = 0;

void police(){
  // Serial.println("Freq " + String(siren_freq));
  if (timer % 500 == 0){
    if (light_red){
      led.set(255, 0, 0);
      Serial.println("Red");
      light_red = false;
    } else {
      led.set(0, 0, 255);
      light_red = true;
      Serial.println("Blue");
    }
  }
  if (timer % 10000 == 0) {
    siren_on = true;
  }
  if (siren_on){
    if (freq_incre){
      siren_freq+= 20;
    } else {
      siren_freq-= 20;
    }
    if (siren_freq == 2000){
      freq_incre = false;
    }
    if (siren_freq == 200){
      freq_incre = true;
      siren_counter++;
    }
    if (siren_counter == 10){
      siren_counter = 0;
      siren_on = false;
    }
    tone(BUZZER_1 ,siren_freq ,1);
  }
  if (timer == 50000){
    randomizeState();
  }
}

void move(){
  if (accelerating && speed + speed / 2 + 1< 256){
    // Serial.println("Accelerating");
    speed += speed / 2 + 1;
  }
  switch(MOVESTATE){
    case STOP:
      speed = 0;
      drive.stop();
      break;
    case FORWARD:
      drive.forward(speed);
      animateForward(true);
      break;
    case BACKWARD:
      drive.backward(speed);
      animateForward(false);
      break;
    case SPINLEFT:
      drive.spinRight(speed);
      animateRotation(true);
      break;
    case SPINRIGHT:
      drive.spinLeft(speed);
      animateRotation(false);
      break;
    case TURNLEFT:
      drive.forwardAndLeft(speed);
      break;
    case TURNRIGHT:
      drive.forwardAndRight(speed);
      break;
  }
}

unsigned char animate_counter = 0;

void animateForward(boolean up){
  if (timer % animation_time == 0){
    if (up){
      display.setRotation(UP);
    } else {
      display.setRotation(DOWN);
    }
    animate_counter++;
    animate_counter %= 8;
    // Serial.println("Animating" + String(animate_counter));
    switch (animate_counter){
      case 0:
        drawPic(forward1_bmp);
        break;
      case 1:
        drawPic(forward2_bmp);
        break;
      case 2:
        drawPic(forward3_bmp);
        break;
      case 3:
        drawPic(forward4_bmp);
        break;
      case 4:
        drawPic(forward5_bmp);
        break;
      case 5:
        drawPic(forward6_bmp);
        break;
      case 6:
        drawPic(forward7_bmp);
        break;
      case 7:
        drawPic(forward8_bmp);
        break;
    }
  }
}

void animateRotation(boolean left){
  if (timer % (2 * animation_time) == 0){
    if (left){
      Serial.println("Turning Left");
      display.turnCounterClockwise();
      drawPic(spinLeft_bmp);
    } else {
      Serial.println("Turning Right");
      display.turnClockwise();
      drawPic(spinRight_bmp);
    }
  }
}

void drawPic(uint8_t map[]){
  display.clear();
  display.drawBitmap(0, 0, map, 8, 8, LED_ON);
  display.writeDisplay();
}

void randomizeState(){
  Serial.println("Randomizing State");
  delay(1000);
  animate_counter =  0;
  timer = 0;
  switch(random(5)){
    case 0:
      STATE = EXPLORE;
      Serial.println("Explore Mode Started");
      break;
    case 1:
      STATE = RANDOM;
      led.set(30, 0, 30);
      Serial.println("Random Move Mode Started");
      break;
    case 2:
      STATE = DANCE;
      song1_done = false;
      song2_done = false;
      Serial.println("Dance Started");
      break;
    case 3:
      STATE = POLICE;
      Serial.println("Police Mode Started");
      break;
    case 4:
      STATE = TEST;
      Serial.println("Test Mode Started");
      break;
  }
}

void startup(){
  if (timer == 1000){
    display.setCursor(1, 0);
    display.print('3');
    display.writeDisplay();
    Serial.println("3");
  } else if (timer == 2000){
    display.clear();
    display.setCursor(2, 0);
    display.print('2');
    display.writeDisplay();
    Serial.println("2");
  } else if (timer == 3000){
    display.clear();
    display.setCursor(1, 0);
    display.print('1');
    display.writeDisplay();
    Serial.println("1");
  } else if (timer == 4000){
    display.clear();
    display.setCursor(2, 0);
    display.print('0');
    display.writeDisplay();
    Serial.println("0");
    song.playWholeSong();
    randomizeState();
  }
}

void loop()
{
  timer++;
  switch(STATE){
    case EXPLORE:
      explore();
      break;
    case DANCE:
      dance();
      break;
    case RANDOM:
      randomMove();
      break;
    case TEST:
      test();
      break;
    case POLICE:
      police();
      break;
    default:
      startup();
  }
  move();
  delay(1);
}
