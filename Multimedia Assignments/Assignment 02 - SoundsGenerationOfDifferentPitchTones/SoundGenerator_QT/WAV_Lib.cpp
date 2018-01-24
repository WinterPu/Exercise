#include "WAV_Lib.h"

//static member definition
bool  WavFile::fm_flag = FM_FLAG;

WavFile::WavFile(int v_frequency, int v_volume, int v_durations) :
	m_samplefreq(44100), m_channels(1),m_channelbits(8),frequency(v_frequency),volume(v_volume),durations(v_durations){

	wave_header_length = sizeof(WaveHeader);
	totalLen = (m_samplefreq * m_channels * m_channelbits / 8) * durations + wave_header_length;//文件总长度=(采样率 * 通道数 * 比特数 / 8) * 持续时间(s)
	wav_data_length = totalLen - wave_header_length;

	CalcSampleFrequency();

}

WavFile::WavFile(int v_samplefreq, int v_channels, int v_channelbits, int v_frequency, int v_volume, int v_durations):
	m_samplefreq(v_samplefreq), m_channels(v_channels), m_channelbits(v_channelbits),frequency(v_frequency), volume(v_volume), durations(v_durations){
	

	wave_header_length = sizeof(WaveHeader);
	totalLen = (m_samplefreq * m_channels * m_channelbits / 8) * durations + wave_header_length;//文件总长度=(采样率 * 通道数 * 比特数 / 8) * 持续时间(s)
	wav_data_length = totalLen - wave_header_length;

	CalcSampleFrequency();
}

void WavFile::initWavFile(int v_frequency, int v_volume, int v_durations){
	
	frequency = v_frequency;
	volume = v_volume;
	durations = v_durations;

	wave_header_length = sizeof(WaveHeader);
	totalLen = (m_samplefreq * m_channels * m_channelbits / 8) * durations + wave_header_length;//文件总长度=(采样率 * 通道数 * 比特数 / 8) * 持续时间(s)
	wav_data_length = totalLen - wave_header_length;

	CalcSampleFrequency();

}

void WavFile::CalcSampleFrequency()
{
	int len = m_samplefreq * durations;
	for (int i = 0; i < len; i++)
		vec_sample_freq.push_back(GenerationFunc(i, m_samplefreq, frequency, volume, WavFile::GetFMFlag()));
}

void WavFile::MakeWaveData(WaveHeader*pHeader, char* pWaveBuffer)//采样率、频率、音量、采样点数
{
	//int flag = 0;
	//if (m_channelbits == 16)        //16位
	//{
	//	if (m_channels == 1)
	//	{
	//		for (int i = 0; i < len; i++)
	//		{
	//			INT16 v = amp / 100 * 32768 * sin(2 * MATH_PI * freq * i / rate);
	//			*(p + flag) = v & 0xFF;//低8位
	//			*(p + flag + 1) = (v >> 8) & 0xFF;//16bit量化 高8位
	//			flag += 2;
	//		}
	//	}
	//	else
	//	{
	//		for (int i = 0; i < len; i++)
	//		{
	//			INT16 vl = amp / 100 * 32768 * sin(2 * MATH_PI * freq * i / rate);
	//			INT16 vr = amp / 100 * 32768 * sin((2 * MATH_PI * freq * (i + 5)) / rate);
	//			*(p + flag) = (vl & 0xFF);
	//			*(p + flag + 1) = ((vl >> 8) & 0xFF);
	//			*(p + flag + 2) = (vr & 0xFF);
	//			*(p + flag + 3) = ((vr >> 8) & 0xFF);
	//			flag += 4;
	//		}
	//	}
	//}
	//else
	//{
	//	if (m_channels == 1)
	//	{
	//		for (int i = 0; i < len; i++)
	//		{
	//			*(p + i) = sin(i * (MATH_PI * 2) / rate * freq) * amp * 128 / 100 + 128;
	//		}
	//	}
	//	else
	//	{
	//		for (int i = 0; i < len; i++)
	//		{
	//			*(p + flag) = sin(i * (MATH_PI * 2) / rate * freq) * amp * 128 / 100 + 128;
	//			*(p + flag + 1) = sin((i + 5) * (MATH_PI * 2) / rate * freq) * amp * 128 / 100 + 128;
	//			flag += 2;
	//		}
	//	}
	//}
	CreateWaveHeader(pHeader, pWaveBuffer);
	int len = m_samplefreq * durations;
	for (int i = 0; i < len; i++)
	{
		*(pWaveBuffer + wave_header_length + i) = (char)(vec_sample_freq[i]);
	}
}

int WavFile::CreateWavFile(std::string file_path)
{
	//For QT
	qDebug()<<file_path.c_str();
	// (string processing) has done in QML File (in [FileDialog])
	//std::string head = "file:///";
	//file_path = file_path.substr(head.length());
	
	WaveHeader * pHeader = new WaveHeader;
	char* pWaveBuffer = new char[totalLen]; //音频数据
	MakeWaveData(pHeader,pWaveBuffer);//采样点数

	std::ofstream bin_ocout;
	bin_ocout.open(file_path, std::ios::out | std::ios::binary);//以二进制形式打开文件
	if (bin_ocout)
		bin_ocout.write(pWaveBuffer, totalLen);
	else
	{		
		std::cout << "Fail to create the file" << std::endl;
		return 0;
	}

	bin_ocout.close();
	std::cout << "succeed to create the file" << std::endl;
	return 1;
}


void WavFile::CreateWaveHeader(WaveHeader*pHeader, char* pWaveBuffer)
{
	pHeader->chRIFF[0] = 'R';
	pHeader->chRIFF[1] = 'I';
	pHeader->chRIFF[2] = 'F';
	pHeader->chRIFF[3] = 'F';
	pHeader->dwRIFFLen = totalLen - 8;//文件的总长度-8bits

	pHeader->chWAVE[0] = 'W';
	pHeader->chWAVE[1] = 'A';
	pHeader->chWAVE[2] = 'V';
	pHeader->chWAVE[3] = 'E';

	pHeader->chFMT[0] = 'f';
	pHeader->chFMT[1] = 'm';
	pHeader->chFMT[2] = 't';
	pHeader->chFMT[3] = ' ';

	pHeader->dwFMTLen = 0x0010;//一般情况下Size为16，如果为18则最后多了2个字节的附加信息
	pHeader->pwf.wf.wFormatTag = 0x0001;//编码方式
	pHeader->pwf.wf.nChannels = m_channels; //1为单通道，2为双通道
	pHeader->pwf.wf.nSamplesPerSec = m_samplefreq;  //=44.1KHz
	pHeader->pwf.wf.nAvgBytesPerSec = m_samplefreq * m_channels * m_channelbits / 8;//每秒所需字节数
	pHeader->pwf.wf.nBlockAlign = m_channels * m_channelbits / 8;//一个采样的字节数
	pHeader->pwf.wBitsPerSample = m_channelbits;//16位，即设置PCM的方式为16位立体声(双通道)

	pHeader->chDATA[0] = 'd';
	pHeader->chDATA[1] = 'a';
	pHeader->chDATA[2] = 't';
	pHeader->chDATA[3] = 'a';
	pHeader->dwDATALen = totalLen - wave_header_length;//数据的长度，=文件总长度-头长度(44bit)

	memcpy(pWaveBuffer, pHeader, wave_header_length);
}


double GenerationFunc(int times, int rate, int freq, int amp, bool fm_flag) {
	double result = sin(times * (MATH_PI * 2) / (double)rate * freq)*amp*128.0 / 100.0 + 128;
	if (fm_flag == false)
		return result;
	else
		return sin(times * (MATH_PI * 2) / (double)rate * freq)*cos(times * (MATH_PI * 2) / (double)rate * freq)*amp * 128 / 100.0 + 128;
}