#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.turnThruOff();
  Serial.begin(31250); //57600
  Serial.println("MIDI Input Test");
  
}

unsigned long t=0;

void loop() {
  midiinListen();

  //3-selector toggle SW
  //updatecheckButtonlayout(); //1.64seq/page+sound mode 2.all88pitch mode 3.tweak mode

  //rotary SW
  //updatecheckChannel();
  
  //updatecheckGate(); 
  //updatecheckPitch();
  //updatecheckVelocity();

  //updatecheckTempo();
  //updatecheckSwing();

  //gel pad SW
  //UpdatecheckSpeakorlisten(); // 1. stop (90%) 2.play 3.record

  //silence mechanical keyboard SW
  //updatecheckButton(); // of course.  
}
void midioutSpeak() {

  int note, channel;
  channel = 1;
  for (note=10; note <= 127; note++) {
    MIDI.sendNoteOn(note, 15, channel);
    delay(200);
    MIDI.sendNoteOff(note, 15, channel);
  }
  delay(200);
}


void midiinListen() {
  int type, note, notein, velocity, channel, d1, d2;

 
  
  if (MIDI.read()) {                    // Is there a MIDI message incoming ?
    byte type = MIDI.getType();
    switch (type) {
      case midi::NoteOn:
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
        if (velocity > 0) {
          Serial.println(String("Note On:  ch=") + channel + ", note=" + note + ", velocity=" + velocity);  
        } else {
          Serial.println(String("Note Off: ch=") + channel + ", note=" + note);
        }
        break;
      case midi::NoteOff:
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
        Serial.println(String("Note Off: ch=") + channel + ", note=" + note + ", velocity=" + velocity);
        break;
      default:
        d1 = MIDI.getData1();
        d2 = MIDI.getData2();
        Serial.println(String("Message, type=") + type + ", data = " + d1 + " " + d2);
    }
    t = millis();
  }
  if (millis() - t > 10000) {
    t += 10000;
    Serial.println("(inactivity)");
  }
}
