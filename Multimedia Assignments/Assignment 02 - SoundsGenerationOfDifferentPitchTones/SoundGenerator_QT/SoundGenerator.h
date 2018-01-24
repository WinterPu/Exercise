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

#include<QObject>
#define DEFAULT_VOLUME 100
#define DEFAULT_DURATION 1
#define REST_NOTE_DURATION 1
#define REST_NOTE_FREQUENCY 1.0
#define DEFAULT_DELAY_VALUE 1



// C C# D D# E F F# G G# A A# B
// 1,1#,2,2#,3,4,4#,5,5#,6,6#,7 ( 3,7 have no mapping #)

#define NUM_TONE 9
#define NUM_NOTE 12


//ALL Uppercase Letter
const std::string musical_notes_char[] = { "C","C#","D","D#","E","F","F#","G","G#","A","A#","B" };
const int musical_notes_int[] = { 1,12,2,22,3,4,42,5,52,6,62,7 };


// 9 tone * 12 musical notes : C C# D D# E F F# G G# A A# B
const static int musical_note_fre_list[NUM_TONE][NUM_NOTE] = {
{ 16, 17, 18, 20, 21, 22, 23, 25, 26, 28, 29, 31 },// Tone 0
{ 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62 }, //Tone 1
{ 65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 124 }, //Tone 2
{ 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247 }, //Tone 3
{ 262, 278, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494 }, //Tone 4
{ 523, 554, 587, 622, 659, 699, 740, 784, 831, 880, 932, 988 }, //Tone 5
{ 1047, 1109,1175,1245,1319,1397,1475,1568,1661,1760,1865,1976 }, //Tone 6
{ 2093,2218,2349,2489,2637,2794,2960,3136,3322,3520,3729,3951 }, //Tone 7
{ 4186,4435,4699, 4978,5274, 5588, 5920, 6272, 6645,7040, 7459,7902 } //Tone 8
};


#define DEFAULT_BASSO_TONE 2
#define DEFAULT_ALTO_TONE 4

typedef struct MusicalNote{
	float frequency;
	float duration;

	MusicalNote(float fre, float dura) :frequency(fre), duration(dura) {}
};



class SoundGenerator : public QObject {

	Q_OBJECT
public:
	SoundGenerator();
	SoundGenerator(int basso_no,int alto_no,int val_note_duration,int delay_time = DEFAULT_DELAY_VALUE);
	
	
	void InitializeFreMap();
	
	//rest note default duration is 1s
	bool ReadFromFile(std::string file_path);
    void recognizeMusicialNoteFromLegalStr(std::string str);

	static WavFile* Merge(WavFile* wav1, WavFile* wav2,int delay_time =0);//Mix wav1 with wav2
	static WavFile* Combine(WavFile* wav1, WavFile* wav2);//wav1+wav2

	void CreateSeperatePart();

	bool SynthesizeFromFile(std::string file_path,int val_basso_tone = DEFAULT_BASSO_TONE,int  val_alto_tone= DEFAULT_ALTO_TONE );

	WavFile* GetFileLink() { return final_sound; }

	void SetToneNumber(int basso_no = DEFAULT_BASSO_TONE, int alto_no= DEFAULT_ALTO_TONE) { basso_tone_number = basso_no; alto_tone_number = alto_no;  InitializeFreMap();}
	int GetBassoToneNumber() { return basso_tone_number; }
	int GetAltoToneNumber() { return alto_tone_number; }



    //For Qt
    Q_INVOKABLE void createWavFileFromFile(QString input_path, QString output_path);

    Q_INVOKABLE void createWavFileFromTwoWav(int f1,int v1,int d1,int f2,int v2,int d2, QString output_path,int delay_time);

    Q_INVOKABLE void createWavFileFromText(QString context,QString output_path,int val_basso_tone,int  val_alto_tone,int delay_time);

    Q_INVOKABLE void initForQt(){InitializeFreMap();}

	~SoundGenerator();

private:
    int basso_tone_number; // 0~8
	int alto_tone_number;
	int each_note_duration;
	int delay_time;
	float tone_duration; //1 tone duration
	std::vector<MusicalNote> melody_tonebasso;
	std::vector<MusicalNote> melody_tonealto;

	WavFile* basso_wave;
	WavFile* alto_wave;
	WavFile* final_sound;


	//note - -  freq
	std::map<int, int> map_number_tonebasso;
	std::map<std::string, int> map_char_tonebasso;
	std::map<int, int> map_number_tonealto;
	std::map<std::string, int> map_char_tonealto;
};


double Merge_Function(double a, double b);

#endif 
