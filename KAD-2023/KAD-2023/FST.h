#pragma once
#define MAX_LEN_CHAIN 100

namespace FST
{
	struct RELATION							// ����� :������->������� ����� ��������� ��
	{
		char symbol;						// ������ ��������
		short nnode;						// ����� ������� �������
		RELATION(
			char �,							// ������ ��������
			short ns						// ����� ���������
		);
	};
	struct NODE								// ������� ����� ���������
	{
		short n_relation;					// ���������� ������������ �����
		RELATION* relations;				// ����������� �����
		NODE();
		NODE(
			short n,						// ���������� ������������ �����
			RELATION rel, ...				// ������ �����
		);
	};
	struct FST								// ������������������� �������� �������
	{
		const char* string;					//������� (������, ���������� 0x00 ) 
		char lexema;						//�������
		short position;						//������� ������� � ������� 
		short nstates;						//���������� ��������� ��������
		NODE* nodes;						//���� ���������: [0] - ��������� ���������, [nstate-1] - ��������
		short* rstates;						//��������� ��������� �������� �� ������ �������.
		FST(
			const char* s,					//������� (������, ���������� 0x00 ) 
			const char lex,					//�������
			short ns,						//���������� ��������� �������� 
			NODE n, ...						//������ ��������� (���� ���������)
		);
	};

	bool step(FST& fst, short*& rstates);	// ���� ��� ��������

	bool execute(							// ��������� ������������� ������� 
		FST& fst							//������������������ �������� �������
	);

};
