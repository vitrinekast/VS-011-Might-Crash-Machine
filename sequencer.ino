void onStep16(uint32_t tick) {
  //Needed to make the 8step sequence:
  if (tick % 2 == 0) {
    return false;
  }

  tick = tick/2;

  int current_step = tick % MAX_STEP;


  if (DEBUG_PRINT_STEP) {
    Serial.print("Step ");
    Serial.println(tick % MAX_STEP);
  }
  // if current step = 0, calculate the sequences to be taken for all 4 instruments -> makeSequences();
  // do the actual sequences



  if ((tick % MAX_STEP) == 0) {
    makeSequences(tick / MAX_STEP);
  }

  playBassNote(current_step);
  playDrumStep(current_step);
}


// Serial.print("SEQ - tick: ");
//   Serial.print(tick);
//   Serial.print(" step: ");
//   Serial.print(tick % MAX_STEP);

//   Serial.print(" bar: ");
//   Serial.print(abs(tick / MAX_BAR));

//   Serial.print(" phrase: ");

//   Serial.println(abs(tick / (MAX_BAR * MAX_PHRASE)));

//   if (tick % MAX_STEP == 0) {
//     Serial.println("SEQ: Finish bar");
//   }

//   if (tick % (MAX_STEP * MAX_BAR) == 0) {
//     Serial.println("SEQ: Finish phrase");
//   }

//   if (tick % (MAX_STEP * MAX_BAR * MAX_PHRASE) == 0) {
//     Serial.println("SEQ: Finish song");
//   }
// // void setCurrentStep(uni) {
// // //   #define MAX_STEP 8
// // // #define MAX_BAR 4
// // // #define MAX_PHRASE 2
// // }