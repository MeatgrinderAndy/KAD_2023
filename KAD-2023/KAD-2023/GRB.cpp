#include "stdafx.h"
#include "GRB.h"
#include <string.h>
#define GRB_ERROR_SERIES 600

namespace GRB
{
#define NS(n) Rule::Chain::N(n)
#define TS(n) Rule::Chain::T(n)

	Greibach greibach(NS('S'), TS('$'), 12,
		Rule(NS('S'), GRB_ERROR_SERIES + 0, //�������� ��������� ���������
			3,	// m{N}S | tfi(F){NrU;}S | ������ �������
			Rule::Chain(5, TS('m'), TS('{'), NS('N'), TS('}'), NS('S')),
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('U'), TS(';'), TS('}'), NS('S')),
			Rule::Chain()
		),

		Rule(NS('N'), GRB_ERROR_SERIES + 1, 	//��������� ��������
			5,	// tY;N |  i=E;N | wU;N | ~K{N}N | ������ �������
			Rule::Chain(4, TS('t'), NS('Y'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('w'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('~'), NS('K'), NS('Z'), NS('N')),
			Rule::Chain()
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2,		// ������ � ���������
			5, // iM | lM | (E)M | i(W)M
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('i'), TS('('), TS(')'), NS('M'))
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 2,		//	������ � ���������
			6,	// +E | -E | *E | /E | %E | ������ �������
			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(2, TS('/'), NS('E')),
			Rule::Chain(2, TS('%'), NS('E')),
			Rule::Chain()
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 3,		// ������ � ���������� ��� ����������� �������
			3, // tP | tP,F | ������ �������
			Rule::Chain(2, TS('t'), NS('P')),
			Rule::Chain(4, TS('t'), NS('P'), TS(','), NS('F')),
			Rule::Chain()
		),
		Rule(NS('P'), GRB_ERROR_SERIES + 3,		// ������ � ���������� ��� ����������� �������
			1, // pi
			Rule::Chain(2, TS('p'), TS('i'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 4,		// ������ � ���������� ��� ������ �������
			4, // i | l | i,W | l,W
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(NS('U'), GRB_ERROR_SERIES + 5, 	// ������ ������� ��� �������������
			6,	// l | i
			Rule::Chain(1, TS('l')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(2, TS('l'), NS('U')),
			Rule::Chain(2, TS('i'), NS('U')),
			Rule::Chain(3, TS('i'), TS(','), NS('U')),
			Rule::Chain(3, TS('l'), TS(','), NS('U'))
		),

		Rule(NS('Y'), GRB_ERROR_SERIES + 6, 	// ������ ��� ����������� ����������
			2,	// vi || vi = L
			Rule::Chain(2, TS('v'), TS('i')),
			Rule::Chain(4, TS('v'), TS('i'), TS('='), NS('L'))
		),


		Rule(NS('K'), GRB_ERROR_SERIES + 7, 	// ������ ��� ����������� ������� ��������
			2,	// (U<U) | (U>U)
			Rule::Chain(5, TS('('), NS('U'), TS('<'), NS('U'), TS(')')),
			Rule::Chain(5, TS('('), NS('U'), TS('>'), NS('U'), TS(')'))
		),
		Rule(NS('L'), GRB_ERROR_SERIES + 8, 	// ������ ��� ��������� �������������
			25,	//vi = l || vi = i || vi = i(i)
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(4, TS('i'), TS('('), NS('U'), TS(')')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),
			Rule::Chain(2, TS('i'), NS('L')),
			Rule::Chain(2, TS('l'), NS('L')),
			Rule::Chain(2, TS('+'), TS('i')),
			Rule::Chain(2, TS('+'), TS('l')),
			Rule::Chain(3, TS('+'), TS('i'), NS('L')),
			Rule::Chain(3, TS('+'), TS('l'), NS('L')),
			Rule::Chain(2, TS('-'), TS('i')),
			Rule::Chain(2, TS('-'), TS('l')),
			Rule::Chain(3, TS('-'), TS('i'), NS('L')),
			Rule::Chain(3, TS('-'), TS('l'), NS('L')),
			Rule::Chain(2, TS('*'), TS('i')),
			Rule::Chain(2, TS('*'), TS('l')),
			Rule::Chain(3, TS('*'), TS('i'), NS('L')),
			Rule::Chain(3, TS('*'), TS('l'), NS('L')),
			Rule::Chain(2, TS('/'), TS('i')),
			Rule::Chain(2, TS('/'), TS('l')),
			Rule::Chain(3, TS('/'), TS('i'), NS('L')),
			Rule::Chain(3, TS('/'), TS('l'), NS('L')),
			Rule::Chain(2, TS('%'), TS('i')),
			Rule::Chain(2, TS('%'), TS('l')),
			Rule::Chain(3, TS('%'), TS('i'), NS('L')),
			Rule::Chain(3, TS('%'), TS('l'), NS('L'))
		),

		Rule(NS('Z'), GRB_ERROR_SERIES + 9, 	//������ � ���� �����
			1,
			Rule::Chain(3, TS('{'), NS('N'), TS('}'))
		)

		
	);



	Rule::Chain::Chain(short size, GRBALPHABET s, ...)
	{
		nt = new GRBALPHABET[this->size = size];

		int* ptr = (int*)&s;
		for (short i = 0; i < size; i++)
			nt[i] = (GRBALPHABET)ptr[i];
	}

	Rule::Rule(GRBALPHABET nn, int iderror, short size, Chain c, ...)
	{
		this->nn = nn;
		this->iderror = iderror;
		this->chains = new Chain[this->size = size];

		Chain* ptr = &c;
		for (int i = 0; i < size; i++)
			this->chains[i] = ptr[i];
	}

	Greibach::Greibach(GRBALPHABET startN, GRBALPHABET stbottomT, short size, Rule r, ...)
	{
		this->startN = startN;
		this->stbottomT = stbottomT;
		this->rules = new Rule[this->size = size];
		Rule* ptr = &r;
		for (int i = 0; i < size; i++)
			rules[i] = ptr[i];
	}

	short Greibach::getRule(GRBALPHABET nn, Rule& rule)
	{
		short rc = -1, k = 0;

		while (k < size && rules[k].nn != nn)
			k++;

		if (k < size)
			rule = rules[rc = k];

		return rc;
	}

	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < size)
			rc = rules[n];
		return rc;
	}

	char* Rule::getCRule(char* b, short nchain)
	{
		char buf[200];
		b[0] = Chain::alphabet_to_char(nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0;
		chains[nchain].getCChain(buf);
		strcat_s(b, sizeof(buf) + 5, buf);

		return b;
	}

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;

		while (j < size && chains[j].nt[0] != t && chains[j].nt[0] != 0)
			j++;

		rc = (j < size ? j : -1);
		if (rc >= 0)
			pchain = chains[rc];
		return rc;
	}

	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < size; i++)
			b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	}

	Greibach getGreibach() { return greibach; }
}