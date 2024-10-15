#include "stdafx.h"
#include "Log.h"
#include "Error.h"

using namespace std;

namespace Log
{
	LOG::LOG()
	{
		memset(logfile, NULL, sizeof(wchar_t) * MAX_LEN_MESSAGE);
		stream = NULL;
	}
	// ------- �������� � �������� ���������� ������ ��������� -------
	LOG getlog(wchar_t logfile[])
	{
		LOG log;
		log.stream = new std::ofstream;
		log.stream->open(logfile);

		if (!log.stream->is_open())
			throw ERROR_THROW(106);

		wcscpy(log.logfile, logfile);

		return log;
	}

	// ------- ������ ����� ������ � �������� char -------
	void WriteLine(std::ostream* stream, const char* c, ...)
	{
		const char** ptrC = &c;
		while (*ptrC != "")
		{
			*stream << *ptrC;
			ptrC++;
		}
		*stream << endl;
	}

	// ------- ������ ����� ������ � �������� wchar_t -------
	void WriteLine(std::ostream* stream, const wchar_t* c, ...)
	{
		const wchar_t** ptrC = &c;
		char tempC[MAX_LEN_MESSAGE];

		while (*ptrC != L"")
		{
			wcstombs(tempC, *ptrC, MAX_LEN_MESSAGE);
			*stream << tempC;
			ptrC++;
		}

		*stream << endl;
	}

	// ------- ����� ��������� ��������� -------
	void WriteLog(std::ostream* stream)
	{
		char buffer[48];
		time_t rawtime;
		time(&rawtime);							// �������� ������� ����, ���������� � ��������
		tm* timeinfo = localtime(&rawtime);		// ������� ����, �������������� � ���������� �����

		strftime(buffer, 48, "����: %d.%m.%Y %A %H:%M:%S ", timeinfo);

		*stream << "----- �������� ----- " << buffer << endl << endl;
	}

	// ------- ����� � �������� ���������� � ������� ���������� -------
	void WriteParm(std::ostream* stream, Parm::PARM parm)
	{
		char* ptrIn = new char[PARM_MAX_SIZE],
			* ptrOut = new char[PARM_MAX_SIZE],
			* ptrLog = new char[PARM_MAX_SIZE];

		wcstombs(ptrIn, parm.in, PARM_MAX_SIZE);
		wcstombs(ptrOut, parm.out, PARM_MAX_SIZE);
		wcstombs(ptrLog, parm.log, PARM_MAX_SIZE);

		*stream << "----- ��������� -----" << endl <<
			"-log: " << ptrLog << endl <<
			"-out: " << ptrOut << endl <<
			"-in: " << ptrIn << endl << endl;

		delete[] ptrIn, ptrOut, ptrLog;
	}

	// ------- ����� � �������� ���������� � ����� -------
	void WriteIn(std::ostream* stream, In::IN in)
	{
		*stream << "----- �������� ������ -----" << endl <<
			"���������� ��������\t: " << in.size << endl <<
			"���������������\t\t: " << in.ignor << endl <<
			"���������� �����\t: " << in.lines << endl << endl;

		//delete[] in.text;			//����� ����������� ����� ������� ������
	}

	// ------- ����� � �������� ���������� �� ������ -------
	void WriteError(std::ostream* stream, Error::ERROR error)
	{
		if (error.inext.line == -1)
			*stream << "������ " << error.id << ": " << error.message << endl;
		else if (error.id >= 110 && error.id <= 119)
		{
			*stream << "������ ��� ������ �� �������� �����" << endl;
			*stream << "������ " << error.id << ": " << error.message << ", ������ " << error.inext.line << ", ������� " << error.inext.col << endl;
		}
		else if (error.id >= 120 && error.id <= 140)
		{
			*stream << "������ �� ����� ������������ �����������" << endl;
			*stream << "������ " << error.id << ": " << error.message << ", ������ " << error.inext.line << ", ������� " << error.inext.col << endl;
		}
		else if (error.id >= 700 && error.id <= 720)
		{
			*stream << "������ �� ����� �������������� �����������" << endl;
			if (error.inext.col == -1)
				*stream << "������ " << error.id << ": " << error.message << ", ������ " << error.inext.line << endl;
			else
				*stream << "������ " << error.id << ": " << error.message << ", ������ " << error.inext.line << ", ������� " << error.inext.col << endl;
		}
	}

	// ------- �������� ������ ������ ��������� -------
	void Close(LOG log)
	{
		log.stream->close();
		delete log.stream;
	}
}
