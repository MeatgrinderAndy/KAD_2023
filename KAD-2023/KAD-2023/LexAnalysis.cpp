#include "stdafx.h"
#include <stack>

#include "LexAnalysis.h"
#include "Error.h"
#include "FST.h"
#include "graphs.h"

using namespace std;

void LexAnalysis(In::IN& in, LT::LexTable& lex, IT::IdTable& id)
{
	IT::IDDATATYPE	iddatatype = IT::IDDATATYPE::DEF;			
	IT::IDTYPE	idtype = IT::IDTYPE::D;							
	IT::Entry* IT_ENTRY = NULL;

	IT::len.params = IT::Entry::Param{ 1, vector<IT::IDDATATYPE>{ IT::IDDATATYPE::STR} };
	IT::Add(id, &IT::len);

	IT::copy.params = IT::Entry::Param{ 3, vector<IT::IDDATATYPE>{IT::IDDATATYPE::STR, IT::IDDATATYPE::STR, IT::IDDATATYPE::SHORT} };
	IT::Add(id, &IT::copy);

	IT::time.params = IT::Entry::Param{ 0, vector<IT::IDDATATYPE>{} };
	IT::Add(id, &IT::time);

	IT::random.params = IT::Entry::Param{ 2, vector<IT::IDDATATYPE>{IT::IDDATATYPE::SHORT, IT::IDDATATYPE::SHORT} };
	IT::Add(id, &IT::random);

	ID_RESET

		char lexema[TI_STR_MAXSIZE];
	int currentRow = 1, currentLex = 0, indexIdTable = 4;
	bool lexID = true, lexShort = false, lexComment = false; int main = 0;
	stack<string> areaOfVisibility;
	areaOfVisibility.push(GLOBAL);

	while (FindLexema(in, lexema))
	{
		currentLex++;
		lexID = true; lexShort = false;

		switch (*lexema)
		{
		case LEX_NOTEQUALS:
		case LEX_COMPARE:
		case LEX_RIGHTBRACE:
		case LEX_SEMICOLON:
		case LEX_COMMA:
		case LEX_LEFTBRACE:
		case LEX_LEFTHESIS:
		case LEX_RIGHTHESIS:
		case LEX_EQUAL:
		case LEX_MORE:
		case LEX_LESS:
		{
			LT::Add(lex, new LT::Entry(*lexema, currentRow, currentLex));
			lexID = false;
			if (*lexema == LEX_RIGHTBRACE)
				areaOfVisibility.pop();
			break;
		}
		case IN_CODE_VERTICAL_LINE:
			currentRow++;
			currentLex = 0;
			lexID = false;
			if (lexComment)
			{
				lexComment = false;
			}
			break;

		case '#':
		{
			FST::FST fst_comment = FST_COMMENT(lexema);

			if (FST::execute(fst_comment))
			{
				lexComment = true;
			}
			break;
		}

		case 'f':
		{
			FST::FST fst_function = FST_FUNCTION(lexema);
			if (FST::execute(fst_function) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_FUNCTION, currentRow, currentLex));
				idtype = IT::IDTYPE::F;
				lexID = false;
			}
			break;
		}
		case 'm':
		{
			FST::FST fst_main = FST_MAIN(lexema);
			if (FST::execute(fst_main) && !lexComment)
			{
				main++;
				LT::Add(lex, new LT::Entry(LEX_MAIN, currentRow, currentLex));
				areaOfVisibility.push(lexema);
				lexID = false;
			}
			break;
		}
		case 'p':
		{
			FST::FST fst_param = FST_PARAM(lexema);
			if (FST::execute(fst_param) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_PARAM, currentRow, currentLex));
				idtype = IT::IDTYPE::P;

				if (IT_ENTRY)
				{
					IT_ENTRY->params.count++;
					IT_ENTRY->params.types.push_back(iddatatype);
				}

				lexID = false;
			}
			break;
		}

		case 'r':
		{
			FST::FST fst_return = FST_RETURN(lexema);
			if (FST::execute(fst_return) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_RETURN, currentRow, currentLex));
				lexID = false;
			}
			if (lexID)
			{
				FST::FST fst_var = FST_REPEAT(lexema);
				if (FST::execute(fst_var) && !lexComment)
				{
					char str[10];
					static int count = 0;
					sprintf(str, "%d", count++);
					LT::Add(lex, new LT::Entry(LEX_REPEAT, currentRow, currentLex));
					areaOfVisibility.push(strcat(lexema, str));
					lexID = false;
				}
			}
			break;
		}
		case 's':
		{
			FST::FST fst_string = FST_STR(lexema);
			if (FST::execute(fst_string) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_STR, currentRow, currentLex));
				iddatatype = IT::IDDATATYPE::STR;
				lexID = false;
			}
			if (lexID) {
				FST::FST fst_short = FST_SHORT(lexema);
				if (FST::execute(fst_short) && !lexComment)
				{
					LT::Add(lex, new LT::Entry(LEX_SHORT, currentRow, currentLex));
					iddatatype = IT::IDDATATYPE::SHORT;
					lexID = false;
				}
			}
			break;
		}
		case 'v':
		{
			FST::FST fst_var = FST_VAR(lexema);
			if (FST::execute(fst_var) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_VAR, currentRow, currentLex));
				idtype = IT::IDTYPE::V;
				lexID = false;
			}
			break;
		}
		case 'h':
		{
			FST::FST fst_literal_i16 = FST_LITERAL_SH16(lexema);		
			if (FST::execute(fst_literal_i16) && !lexComment)
			{
				lexID = false; lexShort = true;
				BaseToDecimal(lexema, 16);
			}
			break;
		}
		case 'b':
		{
			FST::FST fst_literal_sh2 = FST_LITERAL_SH2(lexema);		
			if (FST::execute(fst_literal_sh2) && !lexComment)
			{
				lexID = false; lexShort = true;
				BaseToDecimal(lexema, 2);
			}
			break;
		}
		case 'w':
		{
			FST::FST fst_write = FST_WRITE(lexema);
			if (FST::execute(fst_write) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_WRITE, currentRow, currentLex));
				lexID = false;
			}
			break;
		}
		
		case '+':
		{
			FST::FST fst_plus = FST_PLUS(lexema);				
				if (FST::execute(fst_plus) && !lexComment)
				{
					LT::Add(lex, new LT::Entry(LEX_PLUS, *lexema, currentRow, currentLex));
					lexID = false;
				}
			break;
		}
		case '-':
		{
			FST::FST fst_literal_minus_sh = FST_LITERAL_MINUS_SH(lexema);		
			if (FST::execute(fst_literal_minus_sh) && !lexComment)
			{
				lexID = false; lexShort = true;
			}

			if (lexID)
			{
				FST::FST fst_operator = FST_MINUS(lexema);				
				if (FST::execute(fst_operator) && !lexComment)
				{
					LT::Add(lex, new LT::Entry(LEX_MINUS, *lexema, currentRow, currentLex));
					lexID = false;
				}
			}
			break;
		}
		case '*':
		{
				FST::FST fst_times = FST_TIMES(lexema);				
				if (FST::execute(fst_times) && !lexComment)
				{
					LT::Add(lex, new LT::Entry(LEX_TIMES, *lexema, currentRow, currentLex));
					lexID = false;
				}
				break;
		}
		case '/':
		{
			{
				FST::FST fst_divide = FST_DIVIDE(lexema);				
				if (FST::execute(fst_divide) && !lexComment)
				{
					LT::Add(lex, new LT::Entry(LEX_DIVIDE, *lexema, currentRow, currentLex));
					lexID = false;
				}
				break;
			}
		}
		case '%':
		{
			FST::FST fst_module = FST_MODULE(lexema);		
			if (FST::execute(fst_module) && !lexComment)
			{
				LT::Add(lex, new LT::Entry(LEX_MODULE, *lexema, currentRow, currentLex));
				lexID = false;
			}
			break;
		}
		case '~':
		{
			FST::FST fst_literal_m_s16 = FST_LITERAL_M_SH16(lexema);		
			if (FST::execute(fst_literal_m_s16) && !lexComment)
			{
				lexID = false; lexShort = true;
				BaseToMinDecimal(lexema, 16);
			}
			if (lexID) {
				FST::FST fst_literal_m_s2 = FST_LITERAL_M_SH2(lexema);		
				if (FST::execute(fst_literal_m_s2) && !lexComment)
				{
					lexID = false; lexShort = true;
					BaseToMinDecimal(lexema, 2);
				}
			}
			break;
		}
		case IN_CODE_QUOTES: 
		{
			FST::FST fst_literal_s = FST_LITERAL_STR(lexema);
			if (FST::execute(fst_literal_s) && !lexComment)
			{
				lexID = false;
				int IsLiteralString = IT::IsLiteralString(id, lexema);
				if (IsLiteralString + 1)
					LT::Add(lex, new LT::Entry(LEX_LITERAL, currentRow, currentLex, IsLiteralString));
				else
				{
					LT::Add(lex, new LT::Entry(LEX_LITERAL, currentRow, currentLex, indexIdTable++));

					LITERAL_STR
						IT::Add(id, new IT::Entry(lex.current_size - 1, iddatatype, idtype, lexema));
					ID_RESET
				}
			}
			break;
		}
		default:
		{
			FST::FST fst_literal_i = FST_LITERAL_SH(lexema);		
			if (FST::execute(fst_literal_i))
			{
				lexID = false; lexShort = true;
			}
			break;
		}
		}

		if (lexShort && !lexComment)
		{
			int IsLiteralInt = IT::IsLiteralShort(id, lexema);	
			if (IsLiteralInt + 1)
				LT::Add(lex, new LT::Entry(LEX_LITERAL, currentRow, currentLex, IsLiteralInt));
			else
			{
				LT::Add(lex, new LT::Entry(LEX_LITERAL, currentRow, currentLex, indexIdTable++));

				LITERAL_SHORT
					IT::Add(id, new IT::Entry(lex.current_size - 1, iddatatype, idtype, lexema));
				ID_RESET
			}
		}

		if (lexID && !lexComment) 
		{

			FST::FST fst_id = FST_ID(lexema);
			if (FST::execute(fst_id))
			{
				int isId = IT::IsId(id, lexema, areaOfVisibility); 
				if (isId + 1)
				{
					if (idtype != IT::IDTYPE::D)
					{
						if (!strcmp(id.table[isId]->areaOfVisibility, areaOfVisibility.top().c_str()))
							throw ERROR_THROW_IN(131, currentRow, currentLex);
						if (iddatatype == IT::IDDATATYPE::DEF)
							throw ERROR_THROW_IN(121, currentRow, currentLex);

						LT::Add(lex, new LT::Entry(LEX_ID, currentRow, currentLex, indexIdTable++));
						IT::Add(id, new IT::Entry(lex.current_size - 1, areaOfVisibility.top(), lexema, iddatatype, idtype));

						ID_RESET
					}
					else
						LT::Add(lex, new LT::Entry(LEX_ID, currentRow, currentLex, isId));
				}
				else
				{
					if (iddatatype == IT::IDDATATYPE::DEF)
						throw ERROR_THROW_IN(121, currentRow, currentLex);
					if (idtype == IT::IDTYPE::D)
						throw ERROR_THROW_IN(132, currentRow, currentLex);

					LT::Add(lex, new LT::Entry(LEX_ID, currentRow, currentLex, indexIdTable++));
					IT::Add(id, new IT::Entry(lex.current_size - 1, areaOfVisibility.top(), lexema, iddatatype, idtype));

					if (idtype == IT::IDTYPE::F)
					{
						areaOfVisibility.push(lexema);
						IT_ENTRY = id.table[id.current_size - 1];
					}

					ID_RESET
				}
			}
			else
				throw ERROR_THROW_IN(120, currentRow, currentLex);
		}
	}

	if (main == 0)
		throw ERROR_THROW(133);
	if (main > 1)
		throw ERROR_THROW(134);
	LT::Add(lex, new LT::Entry('$', currentRow, currentLex));
}

bool FindLexema(In::IN& in, char* lexema)
{
	bool s_literal = false;
	static int i = 0; int indexLexema = 0;
	for (; i < in.size && in.text[i] != IN_CODE_SPACE || s_literal; i++)
	{
		if (indexLexema >= TI_STR_MAXSIZE - 1)
			throw ERROR_THROW(125)

			lexema[indexLexema++] = in.text[i];
		if (in.text[i] == IN_CODE_QUOTES)
			s_literal = !s_literal;
	}
	lexema[indexLexema] = TI_STR_DEFAULT;
	i++;

	return indexLexema;
}

void BaseToDecimal(char* lexema, int base)
{
	int number = 0;
	int k;
	for (int i = 1; lexema[i] != '\0'; i++)
	{
		if (lexema[i] <= '9' && lexema[i] >= '0') k = lexema[i] - '0';
		else if (lexema[i] >= 'A' && lexema[i] <= 'F') k = lexema[i] - 'A' + 10;
		else if (lexema[i] >= 'a' && lexema[i] <= 'f') k = lexema[i] - 'a' + 10;
		else continue;
		number = base * number + k;
	}
	sprintf(lexema, "%d", number);
}

void BaseToMinDecimal(char* lexema, int base)
{
	int number = 0;
	int k;
	for (int i = 2; lexema[i] != '\0'; i++)
	{
		if (lexema[i] <= '9' && lexema[i] >= '0') k = lexema[i] - '0';
		else if (lexema[i] >= 'A' && lexema[i] <= 'F') k = lexema[i] - 'A' + 10;
		else if (lexema[i] >= 'a' && lexema[i] <= 'f') k = lexema[i] - 'a' + 10;
		else continue;
		number = base * number + k;
	}
	number = -number;
	sprintf(lexema, "%d", number);
}