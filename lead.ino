// // 2 types of lead, one arp, one slower.
// // Timing for slower is based on modulo 3.
// bool leadIsArp = false;

// void setupLead() {
//   Serial.print("setting up the lead");
//   leadOsc1.begin(.5, 440, WAVEFORM_PULSE);
//   // leadOsc2.begin(.5, 440, WAVEFORM_SINE);

//   leadEnv.attack(3);
//   leadEnv.decay(800);
//   leadEnv.sustain(.81);
//   leadEnv.release(400);


//   dc2.amplitude(0);

//   envelope4.attack(0);
//   envelope4.decay(50);
//   envelope4.sustain(0);
//   envelope4.release(500);


//   leadFilter.frequency(880);
//   leadFilter.resonance(3.3);

//   if (leadIsArp) {
//     leadEnv.decay(800);
//     leadFilter.frequency(2700);
//     leadFilter.resonance(5);
//   }
//   // leadMixer.setCombineMode(0);
//   lead_is_setup = true;
// }

// void setupArp() {
//   leadIsArp = true;
//   setupLead();
// }

// void playLeadNote(uint32_t tick) {
//   int current_step = (tick % 16) / 2;
//   bool should_play = (tick % 2) == 0;

//   if (leadIsArp) {
//     current_step = (tick % 3);
//   }

//   if (should_play || leadIsArp) {
//     SEQUENCER_STEP_DATA step = all_sequences[_current_lead_seq_type][current_step];



//     // leadEnv.releaseNoteOn(20);
//     // envelope4.releaseNoteOn(10);
//     // 
//     int hasNote = false;
//     for (int i = 0; i < NUM_CHANNELS; i++) {
//       if (euclid_pattern[i][euclid_index[i]] > 0) {
//         hasNote = true;
//       }
//     }

//     if (!hasNote && !endless_lead_note) {
//       leadEnv.noteOff();
//       envelope4.noteOff();
//     }
//     for (int i = 0; i < NUM_CHANNELS; i++) {

//       if (euclid_pattern[i][euclid_index[i]] > 0) {
//         leadOsc1.frequency(getFrequency(MIDI_ROOT + euclid_pattern[i][euclid_index[i]]));
//         leadEnv.noteOn();
//         envelope4.noteOn();
        
//         if(endless_lead_note) {
//           leadEnv.releaseNoteOn(0);
//         } else {
//         }
//       }

//       // leadOsc2.frequency(getFrequency(MIDI_ROOT + euclid_pattern[i][euclid_index[i]] ));
//     }
//     // sequence_two
//   }
// }