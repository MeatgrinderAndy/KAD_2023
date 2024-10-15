#pragma once
#include "GRB.h"
#include "LT.h"
#include <stack>
#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3
typedef std::stack<short>	MFSTSTSTACK;	// ���� ��������

#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n) GRB::Rule::Chain::isN(n)

#define MFST_TRACE_START(stream) *stream << std::setw( 4)<<std::left<<"���"<<":" \
	<< std::setw(20) << std::left << "�������"  \
	<< std::setw(30) << std::left << "������� �����" \
	<< std::setw(20) << std::left << "����" \
	<< std::endl;

#define MFST_TRACE1(stream) *stream <<std::setw( 4)<<std::left<<++FST_TRACE_n<<":" \
	<< std::setw(20) << std::left << rule.getCRule(rbuf, currentRuleChain)  \
	<< std::setw(30) << std::left << getCLenta(lbuf, currentPosInLent) \
	<< std::setw(20) << std::left << getCSt(sbuf) \
	<< std::endl;

#define MFST_TRACE2(stream)    *stream <<std::setw( 4)<<std::left<<FST_TRACE_n<<":" \
	<< std::setw(20) << std::left << " "  \
	<< std::setw(30) << std::left << getCLenta(lbuf, currentPosInLent) \
	<< std::setw(20) << std::left << getCSt(sbuf) \
	<< std::endl;

#define MFST_TRACE3(stream)     *stream<<std::setw( 4)<<std::left<<++FST_TRACE_n<<":" \
	<< std::setw(20) << std::left << " "  \
	<< std::setw(30) << std::left << getCLenta(lbuf, currentPosInLent) \
	<< std::setw(20) << std::left << getCSt(sbuf) \
	<< std::endl;

#define MFST_TRACE4(stream, c) *stream<<std::setw(4)<<std::left<<++FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<std::endl;
#define MFST_TRACE5(stream, c) *stream<<std::setw(4)<<std::left<<  FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<std::endl;

#define MFST_TRACE6(stream,c,k) *stream<<std::setw(4)<<std::left<<++FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<k<<std::endl;

#define MFST_TRACE7(stream)  *stream<<std::setw(4)<<std::left<<state.posInLent<<": "\
	<< std::setw(20) << std::left << rule.getCRule(rbuf, state.nRuleChain) \
	<< std::endl;

namespace MFST
{
	struct MFSTState	// ��������� �������� (��� ����������)
	{
		short posInLent;		// ������� �� �����
		short nRule;			// ����� �������� �������
		short nRuleChain;		// ����� ������� �������, �������� �������
		MFSTSTSTACK st;	// ���� ��������

		MFSTState();
		MFSTState(short posInLent,		// ������� �� �����
			MFSTSTSTACK a_steck,		// ���� ��������
			short currentChain);		// ����� ������� �������, �������� �������

		MFSTState(short posInLent,		// ������� �� �����
			MFSTSTSTACK a_stack, 		// ���� ��������
			short currentRule, 			// ����� �������� �������
			short currentChain);		// ����� ������� �������, �������� �������

	};

	struct MFST // ���������� �������
	{
		enum RC_STEP //��� �������� ������� step
		{
			NS_OK,			// ������� ������� � �������, ������� �������� � ���� 
			NS_NORULE,		// �� ������� ������� ���������� (������ � ����������)
			NS_NORULECHAIN,	// �� ������� ��������� ������� ������� (������ � �������� ����)
			NS_ERROR,		// ���������� �������������� ������ ����������
			TS_OK,			// ���. ������ ����� == ������� �����, ������������ �����, pop �����
			TS_NOK,			// ���. ������ ����� != ������� �����, �������������� ��������� 
			LENTA_END,		// ������ ������� ����� >= lenta_size 
			SURPRISE		// ����������� ��� �������� (������ � step)
		};

		struct MFST_Diagnosis	// �����������
		{
			short	posInLent;		// ������� �� ����� 
			RC_STEP	rc_step;			// ��� ���������� ���� 
			short	ruleNum;			// ����� ������� 
			short	nrule_chain;		// ����� ������� �������
			MFST_Diagnosis();
			MFST_Diagnosis(short posInLent, RC_STEP rc_step, short ruleNum, short ruleChainNum);
		} diagnosis[MFST_DIAGN_NUMBER]; // ��������� ����� �������� ���������

		GRBALPHABET* lenta;					// ���������������� (TS/NS) ����� (�� LEX)
		short currentPosInLent;				// ������� ������� �� �����
		short currentRule;					// ����� �������� �������
		short currentRuleChain;				// ����� ������� �������, �������� �������
		short lenta_size;					// ������ �����
		GRB::Greibach grebach;				// ���������� �������
		LT::LexTable lexTable;
		MFSTSTSTACK st;						// ���� ��������
		std::stack<MFSTState> storestate;	// ���� ��� ���������� ���������

		MFST();
		MFST(const LT::LexTable& lexTable, GRB::Greibach grebach);

		char* getCSt(char* buf);								//�������� ���������� �����
		char* getCLenta(char* buf, short pos, short n = 25);	//�����: n ��������, ������� � pos
		char* getDiagnosis(short n, char* buf);					//�������� n-�� ������ ����������� ��� '\0'

		bool savestate(std::ostream* stream);	//��������� ��������� ��������
		bool resetstate(std::ostream* stream);	//������������ ��������� ��������
		bool push_chain(GRB::Rule::Chain chain);

		RC_STEP step(std::ostream* stream);		//��������� ��� ��������
		bool start(std::ostream* stream);		//��������� �������
		bool savedDiagnosis(RC_STEP prc_step);

		void printRules(std::ostream* stream);	//������� ������������������ ������

		struct Deducation		// �����
		{
			short stepsCount;			// ���������� ����� � ������
			short* nRules;				// ����� ������� ����������
			short* nChainsOfRules;		// ����� ������� ������ ����������

			Deducation()
			{
				this->stepsCount = 0;
				this->nRules = 0;
				this->nChainsOfRules = 0;
			}
		}deducation;

		bool saveoutputTree();			// ��������� ������ ������
	};
}
