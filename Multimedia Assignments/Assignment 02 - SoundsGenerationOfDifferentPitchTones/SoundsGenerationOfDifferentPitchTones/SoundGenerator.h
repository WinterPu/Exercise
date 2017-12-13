#pragma once
#ifndef SOUNDGENERATOR_H
#define SOUNDGENERATOR_H

#include <vector>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include "WAV_Lib.h"
#include <cctype>

#define DEFAULT_VOLUME 100
#define DEFAULT_DURATION 1
#define REST_NOTE_DURATION 1
#define REST_NOTE_FREQUENCY 1.0

#define DEFAULT_DELAY_VALUE 1
// C C# D D# E F F# G G# A A# B
// 1,1#,2,2#,3,4,4#,5,5#,6,6#,7 ( 3,7 have no mapping #)

#define NUM_NOTE 12
const int musical_note_list_tone2[] = { 65,69,73,78,82,87,93,98,104,110,117,124 };
const int musical_note_list_tone4[] = { 262,278,294,311,330,349,370,392,415,440,466,494 };
//ALL Uppercase Letter
const std::string musical_notes_char[] = { "C","C#","D","D#","E","F","F#","G","G#","A","A#","B" };
const int musical_notes_int[] = { 1,12,2,22,3,4,42,5,52,6,62,7 };






typedef struct MusicalNote{
	float frequency;
	float duration;

	MusicalNote(float fre, float dura) :frequency(fre), duration(dura) {}
};



class SoundGenerator {

public:
	SoundGenerator();

	//rest note default duration is 1s
	void ReadFromFile(std::string file_path);


	void CreateSeperatePart();

	void synthesize();

	WavFile* GetFileLink() { return final_sound; }

	//note - -  freq
	std::map<int, int> map_number_tone2;
	std::map<std::string, int> map_char_tone2;
	std::map<int, int> map_number_tone4;
	std::map<std::string, int> map_char_tone4;

private:
	int delay_time;
	float tone_duration; //1 tone duration
	std::vector<MusicalNote> melody_tone2;
	std::vector<MusicalNote> melody_tone4;

	WavFile* basso_wave;
	WavFile* alto_wave;
	WavFile* final_sound;
};


#endif 