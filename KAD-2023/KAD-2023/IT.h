#pragma once
#include <string>
#include <stack>
#include <vector>

using namespace std;

#define ID_MAXSIZE			21				// ������������ ���������� �������� � �������������� + '\0'
#define TI_MAXSIZE			4096			// ������������ ���������� ��-�� � ������� ��������������� 
#define TI_SHORT_DEFAULT	0x0000			// �������� �� ��������� ��� ���� short
#define TI_STR_DEFAULT		0x00			// �������� �� ��������� ��� ���� string 
#define TI_NULLIDX			0xffffffff		// ��� �������� ������� ���������������
#define GLOBAL				"global"		// ���������� ���������� ������� ���������
#define TI_STR_MAXSIZE		256				// ������������ ������ ������ + '\0'
#define FUNC_COPY			"copy"			// ������������� ������������ �������
#define FUNC_LEN			"lenght"		// ������������� ������������ �������
#define FUNC_TIME			"getLocalTimeAndDate"	// ������������� ������������ �������
#define FUNC_RANDOM			"random"				// ������������� ������������ �������


#define PARM_ID_DEFAULT_LOCATION		L"D:\\KAD-2023-CP\\KAD-2023\\Debug\\Tables\\"
#define PARM_ID_DEFAULT_EXT				L".id.txt" //��� ����� � ������ ������������ ������a(������� ��������������� � ���������)

namespace IT	// ������� �������������
{
	enum class IDDATATYPE { DEF, SHORT, STR };						// ���� ������ ���������������: �� ���������, short, string
	enum class IDTYPE { D, V, F, P, L, C };							// ���� ���������������: �� ���������, ����������, �������, ��������, �������

	struct Entry	// ������ ������� ���������������
	{
		int idxfirstLE;							// ������ ������ ������ � ������� ������
		char areaOfVisibility[ID_MAXSIZE]{};	// ������� ���������
		char id[ID_MAXSIZE]{};					// ������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE	iddatatype;					// ��� ������
		IDTYPE	idtype;							// ��� ������������
		union
		{
			short vshort;							// �������� short
			struct
			{
				unsigned char len;				// ��������� �������� � string
				char str[TI_STR_MAXSIZE];		// ������� string
			} vstr;								// �������� string
		}value;									// �������� ��������������
		struct Param
		{
			int count;							// ���������� ���������� �������
			vector<IDDATATYPE> types;			// ���� ���������� �������
		} params;
		string FullName;
		Entry(int idxfirstLE, string areaOfVisibility, const char* id, IDDATATYPE iddatatype, IDTYPE idtype);
		Entry(int idxfirstLE, IDDATATYPE iddatatype, IDTYPE idtype, char* value);
	};
	struct IdTable // ��������� ������� ���������������
	{
		int maxsize;				// ������� ������� ��������������� < TI_MAXSIZE
		int current_size;			// ������� ������ ������� ��������������� < maxsize
		Entry** table;				// ������ ���������� �� ������ ������� ���������������

		IdTable(int size);
	};

	//����������� �������
	static Entry len(0, string(GLOBAL), FUNC_LEN, IDDATATYPE::SHORT, IDTYPE::F);
	static Entry copy(0, string(GLOBAL), FUNC_COPY, IDDATATYPE::STR, IDTYPE::F);
	static Entry random(0, string(GLOBAL), FUNC_RANDOM, IDDATATYPE::SHORT, IDTYPE::F);
	static Entry time(0, string(GLOBAL), FUNC_TIME, IDDATATYPE::STR, IDTYPE::F);

	void Add(IdTable& idtable, Entry* entry);
	Entry GetEntry(IdTable& idtable, int n);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE], stack<string> areaOfVisibility);
	int IsLiteralShort(IdTable& idtable, char* lexema);
	int IsLiteralString(IdTable& idtable, char* lexema);
	void PrintIdTable(IdTable& idtable, const wchar_t* in);
	void Delete(IdTable& idtable);
}