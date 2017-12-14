#include "WAV_Lib.h"
#include "SoundGenerator.h"
using namespace std;


int main()
{
	string command;
	string path;
	string file_name;
	SoundGenerator sound_generator;

	cout << "Please Enter Your Command! You can use [help] to see the commands" << endl;
	while (cin >> command && command != "end")
	{
		transform(command.begin(),command.end(),command.begin(),::tolower);
		if (command == "createwav")
		{
			int val_fre, val_volume, val_duration;
			cin >> val_fre >> val_volume >> val_duration;
			WavFile tmp(val_fre, val_volume, val_duration);
			

			bool flag_use_thesamepath = false;
			if (path.size() != 0)
			{
				cout << "Do you want to use the previous path?" << endl;
				cout << "you can  key [enter] to continue" << endl;
				cout << "you can use [any other key] to go to re-type the path" << endl;
				
				cin.ignore();
				char ch;
				if ((ch = getchar()) == '\n')
					flag_use_thesamepath = true;
			}

			if (flag_use_thesamepath == false)
			{
				cout << "Please Enter Your File Saving Path!" << endl;
				cin >> path;
			}

	
			cout << "Please Enter Your [ Wav ] File Name!" << endl;
			cin >> file_name;


			cout << "Log :" << endl;
			tmp.CreateWavFile(path+file_name);
		}
		else if (command == "createsound")
		{
			string input_file_path;
			cout << "Please Enter Your Input File Path!" << endl;

			cin.ignore();
			getline(cin,input_file_path);

			bool flag_use_thesamepath = false;
			if (path.size() != 0)
			{
				cout << "Do you want to use the previous path?" << endl;
				cout << "you can  key [enter] to continue" << endl;
				cout << "you can use [any other key] to go to re-type the path" << endl;

				char ch;
				if ((ch = getchar()) == '\n')
					flag_use_thesamepath = true;
			}
			if (flag_use_thesamepath == false)
			{
				cout << "Please Enter Your File Saving Path!" << endl;
				cin >> path;
			}
			cout << "Please Enter Your [ Sound ] File Name!" << endl;
			cin >> file_name;

			cout << " Log :" << endl;
			
			if (sound_generator.SynthesizeFromFile(input_file_path))
			{
				WavFile* final_sound_ptr = sound_generator.GetFileLink();
				if(final_sound_ptr!= NULL)
					final_sound_ptr->CreateWavFile(path+file_name);
				else {
					cout << "Maybe The Output Path Is Wrong!" << endl;
				}
			}
		}
		else if (command == "setfm")
		{
			cout << "Please Enter [enable / any other key]" << endl;
			string command_FM;
			cin >> command_FM;
			if (command_FM == "enable")
				WavFile::SetFMFlag(true);
			else 
				WavFile::SetFMFlag(false);

			cout << "Completed!  The fm flag is:" << (WavFile::GetFMFlag()?"true":"false" )<< endl;
		}
		else if (command == "settone")
		{
			cout << "Please Enter basso tone & alto tone number " << endl;
			cout << "You can choose from 0~8 " << endl;
			int val_basso, val_alto;
			cin >> val_basso >> val_alto;
			sound_generator.SetToneNumber(val_basso,val_alto);
			cout << "Completed!" << endl;
			cout << "The basso tone is: " <<sound_generator.GetBassoToneNumber()<< endl;
			cout << "The alto  tone is: " <<sound_generator.GetAltoToneNumber() << endl;
		}
		else if (command == "help")
		{
			cout << "*****************************" << endl;
			cout << "*****************************" << endl;
			cout << "'createwav [fre] [volume] [dura] ----- create wav file'" << endl;
			cout << "'createsound'                    ----- load musical note to create a sound " << endl;
			cout << "'setfm'                          ----- enable FM or not" << endl;
			cout << "'settone'                        ----- set basso tone & alto tone number" << endl;
			cout << "'end'                            ----- end the program" << endl;
			cout << "*****************************" << endl;
			cout << "*****************************" << endl;
		}

		cout << endl << endl<<endl;
		cout << "**********************************************************" << endl;
		cout << "Please Enter Your Command! You can use [help] to see the commands" << endl;
	}


	return 0;
}