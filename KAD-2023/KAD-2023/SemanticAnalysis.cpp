#include "stdafx.h"
#include "SemanticAnalysis.h"
#include "Error.h"

using namespace std;

namespace SM
{
	void semAnaliz(LT::LexTable& lextable, IT::IdTable& idtable)
	{
		for (int i = 0; i < lextable.current_size; i++)
		{
			switch (lextable.table[i]->lexema)
			{
			case LEX_DIVIDE:	// ������� �� 0
			{
				if (lextable.table[i]->sign == '/')
					if (lextable.table[i + 1]->lexema == LEX_LITERAL)
					{
						if (idtable.table[lextable.table[i + 1]->idxTI]->value.vshort == 0)
							throw ERROR_THROW_IN(700, lextable.table[i + 1]->sn, lextable.table[i + 1]->tn);
					}
				break;
			}
			case LEX_EQUAL: // ���������
			{
				if (i)
				{
					IT::IDDATATYPE lefttype = idtable.table[lextable.table[i - 1]->idxTI]->iddatatype;	// ����� �������
					bool ignore = false;

					for (int k = i + 1; lextable.table[k]->lexema != LEX_SEMICOLON; k++)
					{
						if (lextable.table[k]->idxTI != LT_TI_NULLXDX) // ���� �� - ��������� ���������� �����
						{
							if (!ignore)
							{
								IT::IDDATATYPE righttype = idtable.table[lextable.table[k]->idxTI]->iddatatype;
								if (lefttype != righttype) // ���� ������ � ��������� �� ���������
									throw ERROR_THROW_IN(701, lextable.table[k]->sn, -1);
							}
							// ���� ������� ����� ����� ������� ������ - ��� ����� �������
							if (k + 1 < lextable.current_size && lextable.table[k + 1]->lexema == LEX_LEFTHESIS && idtable.table[lextable.table[k]->idxTI]->idtype == IT::IDTYPE::F)
							{
								ignore = true;
								continue;
							}
							// ����������� ������ ����� ������ ����������
							if (ignore && lextable.table[k + 1]->lexema == LEX_RIGHTHESIS)
							{
								ignore = false;
								continue;
							}
						}
						if (lefttype == IT::IDDATATYPE::STR) // ������ ������ �������, �� ��� ����� ��������� �-���
						{
							char l = lextable.table[k]->lexema;
							if (l == LEX_PLUS || l == LEX_MINUS || l == LEX_TIMES || l == LEX_DIVIDE || l == LEX_MODULE) // ��������� �����������
								throw ERROR_THROW_IN(702, lextable.table[k]->sn, -1);
						}
					}
				}
				break;
			}
			case LEX_ID: // �������� ���� ������������� ��������  
			{
				IT::Entry* e;
				e = idtable.table[lextable.table[i]->idxTI];

				if (i && lextable.table[i - 1]->lexema == LEX_FUNCTION)	// ���������� �������
				{
					for (int k = i + 1; ; k++)
					{
						char l = lextable.table[k]->lexema;
						if (l == LEX_RETURN)
						{
							int next = lextable.table[k + 1]->idxTI; // ����. �� return
							if (idtable.table[next]->iddatatype != e->iddatatype)
								throw ERROR_THROW_IN(703, lextable.table[k + 1]->sn, -1);
							break;
						}
					}
				}
				if (lextable.table[i + 1]->lexema == LEX_LEFTHESIS && lextable.table[i - 1]->lexema != LEX_FUNCTION) // ������ �����
				{
					if (e->idtype == IT::IDTYPE::F) // ����� �������
					{
						int paramscount = NULL;
						// �������� ������������ ����������
						for (int j = i + 1; lextable.table[j]->lexema != LEX_RIGHTHESIS; j++)
						{
							// �������� ������������ ������������ ���������� ����������
							if (lextable.table[j]->lexema == LEX_ID || lextable.table[j]->lexema == LEX_LITERAL)
							{
								paramscount++;
								IT::IDDATATYPE ctype = idtable.table[lextable.table[j]->idxTI]->iddatatype;
								if (paramscount > e->params.count)
									throw ERROR_THROW_IN(705, lextable.table[i]->sn, -1);
								if (ctype != e->params.types[paramscount - 1])
									throw ERROR_THROW_IN(704, lextable.table[j]->sn, lextable.table[j]->tn);
							}
						}
						if (paramscount != e->params.count)
							throw ERROR_THROW_IN(705, lextable.table[i]->sn, -1);
					}
				}
				break;
			}
			case LEX_MORE:	case LEX_LESS:
			{
				// ����� � ������ ������� - �������� ���
				bool flag = true;
				if (lextable.table[i - 1]->idxTI != LT_TI_NULLXDX)
				{
					if (idtable.table[lextable.table[i - 1]->idxTI]->iddatatype != IT::IDDATATYPE::SHORT)
						flag = false;
				}
				if (lextable.table[i + 1]->idxTI != LT_TI_NULLXDX)
				{
					if (idtable.table[lextable.table[i + 1]->idxTI]->iddatatype != IT::IDDATATYPE::SHORT)
						flag = false;
				}
				if (!flag)
					throw ERROR_THROW_IN(706, lextable.table[i]->sn, -1);
				break;
			}
			}
		}
	}
}