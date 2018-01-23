#include "SoundGenerator.h"

SoundGenerator::SoundGenerator():basso_tone_number(DEFAULT_BASSO_TONE),alto_tone_number(DEFAULT_ALTO_TONE), tone_duration(0),each_note_duration(DEFAULT_DURATION), delay_time(DEFAULT_DELAY_VALUE)
{
	InitializeFreMap();
}

SoundGenerator::SoundGenerator(int basso_no, int alto_no,int val_note_duration, int delay_time):basso_tone_number(basso_no), alto_tone_number(alto_no), tone_duration(0),each_note_duration(DEFAULT_DURATION), delay_time(delay_time)
{
	InitializeFreMap();
}

void SoundGenerator::InitializeFreMap()
{
	// use basso_tone_number
	// use alto_tone_number
	map_char_tonebasso.clear();
	map_char_tonealto.clear();
	map_number_tonebasso.clear();
	map_number_tonealto.clear();

	for (int i = 0; i < NUM_NOTE; i++) {

		std::pair<std::string, int> char_iterm;
		char_iterm.first = musical_notes_char[i];
		char_iterm.second = musical_note_fre_list[basso_tone_number][i];
		map_char_tonebasso.insert(char_iterm);
		char_iterm.second = musical_note_fre_list[alto_tone_number][i];
		map_char_tonealto.insert(char_iterm);


		std::pair<int, int> number_iterm;
		number_iterm.first = musical_notes_int[i];
		number_iterm.second = musical_note_fre_list[basso_tone_number][i];
		map_number_tonebasso.insert(number_iterm);
		number_iterm.second = musical_note_fre_list[alto_tone_number][i];
		map_number_tonealto.insert(number_iterm);
	}
}


bool SoundGenerator::ReadFromFile(std::string file_path)
{
	// use each_note_duration (change use this->)
	std::fstream stream_musical_notes(file_path);

	if (!stream_musical_notes.is_open())
	{
		std::cout << "Fail to open input file." << std::endl;
		return false;
	}
	std::string str;
	while (stream_musical_notes >> str) {

		std::cout << "Original " << str << std::endl;
		if (str == "-")
		{
			MusicalNote tmp(REST_NOTE_FREQUENCY, REST_NOTE_DURATION);
			melody_tonebasso.push_back(tmp);
			melody_tonealto.push_back(tmp);
			tone_duration++;
		}
		else if (isdigit(str[0]))
		{
			// 1,12,1-2,12-2
			std::map<int, int>::iterator iter;
			int number_note;
			float tmp_duration = each_note_duration;
			if (str.size() == 1 || str.size() == 2)
				number_note = atoi(str.c_str());

			else if (str[1] == '-')
			{
				int number_note = str[0] - '0';
				tmp_duration = atoi(str.substr(2, str.size() - 2).c_str());
			}
			else {
				int number_note = atoi(str.substr(0, 2).c_str());
				tmp_duration = atoi(str.substr(3, str.size() - 3).c_str());
			}

			iter = map_number_tonebasso.find(number_note);
			if (iter != map_number_tonebasso.end())
			{
				MusicalNote tmp(iter->second, tmp_duration); melody_tonebasso.push_back(tmp);
				MusicalNote tmp2(map_number_tonealto.find(number_note)->second, tmp_duration); 	melody_tonealto.push_back(tmp2);
			}
			//cannot find: wait to be handled
			tone_duration+= tmp_duration;
		}
		else {
			//A ,A#,A-2,A#-2
			std::map<std::string, int>::iterator iter;
			std::string str_note;
			float tmp_duration = each_note_duration;
			if (str.size() == 1 || str.size() == 2)
				str_note = str;

			else if (str[1] == '-')
			{
				str_note = toupper(str[0]); 
				tmp_duration = atoi(str.substr(2, str.size() - 2).c_str());
			}
			else {
				str_note = str.substr(0, 2); str_note[0] = toupper(str_note[0]);
				tmp_duration = atoi(str.substr(3, str.size() - 3).c_str());
			}

			iter = map_char_tonebasso.find(str_note);
			if (iter != map_char_tonebasso.end())
			{
				MusicalNote tmp(iter->second, tmp_duration); melody_tonebasso.push_back(tmp);
				MusicalNote tmp2(map_char_tonealto.find(str_note)->second, tmp_duration); 	melody_tonealto.push_back(tmp2);
			}
			//cannot find: wait to be handled
			tone_duration += tmp_duration;
		}
	}
	return true;


}


WavFile* SoundGenerator::Merge(WavFile* pre, WavFile* rear, int delay_time)
{
	if (pre == NULL || rear == NULL)
		return nullptr;

	WavFile * new_rear;
	WavFile * new_pre;
	if (delay_time > 0)
	{
		//do delaying
		WavFile* delayed_sound = new WavFile(REST_NOTE_FREQUENCY, DEFAULT_VOLUME, delay_time);
		new_rear = SoundGenerator::Combine(delayed_sound, rear);

		//do padding
		if (pre->GetDuration() > rear->GetDuration())
		{
			//pre > rear
			WavFile* delayed_sound_pre = new WavFile(REST_NOTE_FREQUENCY, DEFAULT_VOLUME, delay_time);
			WavFile* padding_rear = new WavFile(REST_NOTE_FREQUENCY, DEFAULT_VOLUME, pre->GetDuration() - rear->GetDuration());
			new_pre = SoundGenerator::Combine(pre, delayed_sound_pre);
			WavFile* garbage = new_rear;
			new_rear = SoundGenerator::Combine(rear,padding_rear);
			delete garbage;
		}
		else if (pre->GetDuration() < rear->GetDuration())
		{
			// pre < rear
			WavFile* delayed_sound_pre = new WavFile(REST_NOTE_FREQUENCY, DEFAULT_VOLUME, delay_time+ rear->GetDuration() - pre->GetDuration());
			new_pre = SoundGenerator::Combine(pre, delayed_sound_pre);
		}
		else {
			//pre == rear
			WavFile* delayed_sound = new WavFile(REST_NOTE_FREQUENCY, DEFAULT_VOLUME, delay_time);
			new_pre = SoundGenerator::Combine(pre, delayed_sound);

		}

	}
	else
	{
		//do padding
		if (pre->GetDuration() > rear->GetDuration())
		{
			//pre > rear
			WavFile* padding_part = new WavFile(REST_NOTE_FREQUENCY, DEFAULT_VOLUME, pre->GetDuration() - rear->GetDuration());
			new_rear = SoundGenerator::Combine(rear, padding_part);
			new_pre = pre;
		}
		else if (pre->GetDuration() < rear->GetDuration())
		{
			// pre < rear
			WavFile* padding_part = new WavFile(REST_NOTE_FREQUENCY, DEFAULT_VOLUME,  rear->GetDuration() - pre->GetDuration());
			new_pre = SoundGenerator::Combine(pre, padding_part);
			new_rear = rear;
		}
		else {
			// pre == rear
			new_pre = pre;
			new_rear = rear;
		}

	}

	int duration = new_pre->GetDuration();
	WavFile* merged_file = new WavFile(1,DEFAULT_VOLUME,duration);
	for (int i = 0; i < merged_file->GetDataLength(); i++)
	{
		(*merged_file->GetDataLinker())[i]= Merge_Function((*new_pre->GetDataLinker())[i], (*new_rear->GetDataLinker())[i]);
	}
	return merged_file;
}


WavFile * SoundGenerator::Combine(WavFile * pre, WavFile * rear)
{
	if (pre == NULL || rear == NULL)
		return nullptr;

	int total_durations = pre->GetDuration() + rear->GetDuration();

	WavFile* combined_file = new WavFile(1, DEFAULT_VOLUME, total_durations);


	for (int i = 0; i < pre->GetDataLength(); i++)
	{
		(*combined_file->GetDataLinker())[i] = (*pre->GetDataLinker())[i];
	}
	for (int i = pre->GetDataLength(); i <combined_file->GetDataLength(); i++)
	{
		(*combined_file->GetDataLinker())[i] = (*rear->GetDataLinker())[i- pre->GetDataLength()];
	}

	return combined_file;
}

void SoundGenerator::CreateSeperatePart()
{

	// you can use combine to do the same thing.

	basso_wave = new WavFile(1,DEFAULT_VOLUME,tone_duration);
	alto_wave = new WavFile(1, DEFAULT_VOLUME, tone_duration);

	int num_notes = melody_tonebasso .size();
	
	int index = 0;
	for (int i = 0; i < num_notes; i++)
	{
		WavFile* tmp_wave_basso = new WavFile(melody_tonebasso[i].frequency, DEFAULT_VOLUME, melody_tonebasso[i].duration);
		WavFile* tmp_wave_alto = new WavFile(melody_tonealto[i].frequency, DEFAULT_VOLUME, melody_tonealto[i].duration);

		for (int j = 0; j < tmp_wave_basso->GetDataLength(); j++)
		{
			(*basso_wave->GetDataLinker())[index] = (*tmp_wave_basso->GetDataLinker())[j];
			(*alto_wave->GetDataLinker())[index] = (*tmp_wave_alto->GetDataLinker())[j];
			index++;
		}
	}

}

bool SoundGenerator::SynthesizeFromFile(std::string file_path, int val_basso_tone, int val_alto_tone)
{
	if (val_basso_tone != DEFAULT_BASSO_TONE || val_alto_tone != DEFAULT_ALTO_TONE)
		SetToneNumber(val_basso_tone, val_alto_tone);

	if (ReadFromFile(file_path))
	{
		CreateSeperatePart();
		final_sound = SoundGenerator::Merge(basso_wave, alto_wave, delay_time);
		return true;
	}
	else
		return false;
}


//For Qt
void SoundGenerator::createWavFileFromFile(QString input_path, QString output_path){
     std::string input_path_str = input_path.toUtf8().constData();
     std::string output_path_str= output_path.toUtf8().constData();


     std::string head = "file:///";
     input_path_str = input_path_str.substr(head.length());
    // output_path_str = output_path_str.substr(head.length());


     if (SynthesizeFromFile(input_path_str))
     {
         WavFile* final_sound_ptr = GetFileLink();
         if(final_sound_ptr!= NULL)
             final_sound_ptr->CreateWavFile(output_path_str);
         else {
             qDebug() << "Maybe The Output Path Is Wrong!\n";
         }
     }

}





SoundGenerator::~SoundGenerator()
{
    delete basso_wave;
    delete alto_wave;
    delete final_sound;
}

double Merge_Function(double a, double b)
{
	return (a+b)/2.0;
}
