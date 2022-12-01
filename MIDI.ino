
void setupMIDI() {
  Serial.println("MIDI: Setup midi");
  // TODO: add check if usbmidi exists here!
  usbMIDI.setHandleControlChange(onControlChange);
}

void loopMIDI() {
  
}

void onControlChange() {
  Serial.println("MIDI: got a control change");
  // TODO: add button to print all of the current values;
}