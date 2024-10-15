#pragma once

#define LEXEMA_FIXSIZE	1			// ������������� ������ �������
#define	LT_MAXSIZE		4096		// ������������ ���������� ����� � ������� ������	
#define	LT_TI_NULLXDX	-1			// ��� �������� ������� ���������������	
#define	LT_V_NULL		'?'			// 


#define	LEX_SHORT		't'			// ������� ��� short
#define	LEX_STR			't'			// ������� ��� str
#define	LEX_ID			'i' 		// ������� ��� ��������������
#define	LEX_LITERAL		'l'			// ������� ��� ��������
#define	LEX_FUNCTION	'f'			// ������� ��� function
#define	LEX_PARAM		'p'			// ������� ��� param
#define	LEX_VAR			'v'			// ������� ��� var
#define	LEX_REPEAT		'~'			// ������� ��� repeat
#define	LEX_RETURN		'r'			// ������� ��� return
#define	LEX_WRITE		'w'			// ������� ��� write
#define	LEX_MAIN		'm'			// ������� ��� main
#define	LEX_SEMICOLON	';'			// ������� ��� ;
#define	LEX_COMMA		','			// ������� ��� ,
#define	LEX_LEFTBRACE	'{'			// ������� ��� {
#define	LEX_RIGHTBRACE	'}'			// ������� ��� }
#define	LEX_LEFTHESIS	'('			// ������� ��� (
#define	LEX_RIGHTHESIS	')'			// ������� ��� )
#define LEX_PLUS		'+'			//������� ��� +
#define LEX_MINUS		'-'			//������� ��� -
#define LEX_TIMES		'*'			//������� ��� *
#define LEX_DIVIDE		'/'			//������� ��� /
#define LEX_MODULE		'%'			//������� ��� %
#define	LEX_EQUAL		'='			// ������� ��� =
#define	LEX_MORE		'>'			// ������� ��� >
#define	LEX_LESS		'<'			// ������� ��� <
#define	LEX_COMPARE		'&'			// ������� ��� ==
#define	LEX_NOTEQUALS	'^'			// ������� ��� ==
#define LEX_COMMENT		'@'			// ������� ��� ������������

#define PARM_LEX_DEFAULT_LOCATION	L"D:\\KAD-2023-CP\\KAD-2023\\Debug\\Tables\\"	
#define PARM_LEX_DEFAULT_EXT		L".lex.txt" //��� ����� � ������ ������������ ������a (������� ������)

namespace LT							// ������� ������
{
	struct Entry						// ������ ������� ������
	{
		char lexema;					// �������
		char sign;						// ���� ������� v ��� LT_V_NULL
		int sn;							// ����� ������ � �������� ������
		int tn;							// ����� ������ � ������
		int idxTI;						// ������ � ������� ��������������� ��� LT_TI_NULLIDX

		Entry(char lexema, int sn, int tn, int idxTI);		// ��� �������������
		Entry(char lexema, char sign, int sn, int tn);		// ��� ����������
		Entry(char lexema, int sn, int tn);					// ��������� �������
		Entry(char lexema);
	};

	struct LexTable						// ��������� ������� ������
	{
		int maxsize;					// ������� ������� ������ < LT_MAXSIZE
		int current_size;				// ������� ������ ������� ������ < maxsize
		Entry** table;					// ������ ���������� �� ������ ������� ������

		LexTable();
		LexTable(int size);			// ������� ������� ������
	};
	void Add(LexTable& lextable, Entry* entry);						// ���������� ������
	Entry GetEntry(LexTable& lextable, int n);						// �������� ������ ������� ������
	void PrintLexTable(LexTable& lextable, const wchar_t* in);		// ����� ������ � ����
	void Delete(LexTable& lextable);								// ������� ������� ������ (���������� ������)
}