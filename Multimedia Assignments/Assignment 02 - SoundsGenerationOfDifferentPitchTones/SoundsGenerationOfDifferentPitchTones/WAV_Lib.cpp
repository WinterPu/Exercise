#include "WAV_Lib.h"


WavFile::WavFile(int v_frequency, int v_volume, int v_durations) :
	m_samplefreq(44100), m_channels(1),m_channelbits(8),frequency(v_frequency),volume(v_volume),durations(v_durations){

	wave_header_length = sizeof(WaveHeader);
	totalLen = (m_samplefreq * m_channels * m_channelbits / 8) * durations + wave_header_length;//�ļ��ܳ���=(������ * ͨ���� * ������ / 8) * ����ʱ��(s)
	wav_data_length = totalLen - wave_header_length;

	CreateWaveHeader();
	MakeWaveData(pHeader->pwf.wf.nSamplesPerSec, frequency, volume, pWaveBuffer + wave_header_length, m_samplefreq*durations);//��������
}

WavFile::WavFile(int v_samplefreq, int v_channels, int v_channelbits, int v_frequency, int v_volume, int v_durations):
	m_samplefreq(v_samplefreq), m_channels(v_channels), m_channelbits(v_channelbits),frequency(v_frequency), volume(v_volume), durations(v_durations){
	
	wave_header_length = sizeof(WaveHeader);
	totalLen = (m_samplefreq * m_channels * m_channelbits / 8) * durations + wave_header_length;//�ļ��ܳ���=(������ * ͨ���� * ������ / 8) * ����ʱ��(s)
	wav_data_length = totalLen - wave_header_length;
	CreateWaveHeader();

	MakeWaveData(pHeader->pwf.wf.nSamplesPerSec, frequency, volume, pWaveBuffer + wave_header_length, m_samplefreq*durations);//��������
}

void WavFile::MakeWaveData(int rate, int freq, int amp, char*p, int len)//�����ʡ�Ƶ�ʡ���������������
{
	//int flag = 0;
	//if (m_channelbits == 16)        //16λ
	//{
	//	if (m_channels == 1)
	//	{
	//		for (int i = 0; i < len; i++)
	//		{
	//			INT16 v = amp / 100 * 32768 * sin(2 * MATH_PI * freq * i / rate);
	//			*(p + flag) = v & 0xFF;//��8λ
	//			*(p + flag + 1) = (v >> 8) & 0xFF;//16bit���� ��8λ
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

	for (int i = 0; i < len; i++)
	{
		*(p + i) = GenerationFunc(i,rate,freq,amp, FM_FLAG);
	}
}

int WavFile::CreateWavFile(std::string path, std::string file_name)
{
	std::ofstream ocout;
	ocout.open(path+file_name, std::ios::out | std::ios::binary);//�Զ�������ʽ���ļ�
	if (ocout)
		ocout.write(pWaveBuffer, totalLen);
	else
	{		
		std::cout << "Fail to create the file" << std::endl;
		return 0;
	}

	ocout.close();
	std::cout << "succeed to create the file" << std::endl;
	return 1;
}


void WavFile::CreateWaveHeader()
{
	pHeader = new WaveHeader;
	pHeader->chRIFF[0] = 'R';
	pHeader->chRIFF[1] = 'I';
	pHeader->chRIFF[2] = 'F';
	pHeader->chRIFF[3] = 'F';
	pHeader->dwRIFFLen = totalLen - 8;//�ļ����ܳ���-8bits

	pHeader->chWAVE[0] = 'W';
	pHeader->chWAVE[1] = 'A';
	pHeader->chWAVE[2] = 'V';
	pHeader->chWAVE[3] = 'E';

	pHeader->chFMT[0] = 'f';
	pHeader->chFMT[1] = 'm';
	pHeader->chFMT[2] = 't';
	pHeader->chFMT[3] = ' ';

	pHeader->dwFMTLen = 0x0010;//һ�������SizeΪ16�����Ϊ18��������2���ֽڵĸ�����Ϣ
	pHeader->pwf.wf.wFormatTag = 0x0001;//���뷽ʽ
	pHeader->pwf.wf.nChannels = m_channels; //1Ϊ��ͨ����2Ϊ˫ͨ��
	pHeader->pwf.wf.nSamplesPerSec = m_samplefreq;  //=44.1KHz
	pHeader->pwf.wf.nAvgBytesPerSec = m_samplefreq * m_channels * m_channelbits / 8;//ÿ�������ֽ���
	pHeader->pwf.wf.nBlockAlign = m_channels * m_channelbits / 8;//һ���������ֽ���
	pHeader->pwf.wBitsPerSample = m_channelbits;//16λ��������PCM�ķ�ʽΪ16λ������(˫ͨ��)

	pHeader->chDATA[0] = 'd';
	pHeader->chDATA[1] = 'a';
	pHeader->chDATA[2] = 't';
	pHeader->chDATA[3] = 'a';
	pHeader->dwDATALen = totalLen - wave_header_length;//���ݵĳ��ȣ�=�ļ��ܳ���-ͷ����(44bit)

	pWaveBuffer = new char[totalLen]; //��Ƶ����
	memcpy(pWaveBuffer, pHeader, wave_header_length);
}

WavFile::~WavFile() {
	delete pHeader;
	delete pWaveBuffer;
}


double GenerationFunc(int times, int rate, int freq, int amp, bool fm_flag) {
	return sin(times * (MATH_PI * 2) / rate * freq)*amp*128.0/100.0+128;
}