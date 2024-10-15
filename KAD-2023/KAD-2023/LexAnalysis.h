#pragma once
#include "In.h"
#include "LT.h"
#include "IT.h"

#define ID_RESET		idtype = IT::IDTYPE::D; \
						iddatatype = IT::IDDATATYPE::DEF;

#define LITERAL_SHORT		iddatatype = IT::IDDATATYPE::SHORT; \
						idtype = IT::IDTYPE::L;

#define LITERAL_STR		iddatatype = IT::IDDATATYPE::STR; \
						idtype = IT::IDTYPE::L;


void LexAnalysis(In::IN& in, LT::LexTable& lex, IT::IdTable& id);
bool FindLexema(In::IN&, char*);
void BaseToDecimal(char*, int);
void BaseToMinDecimal(char*, int);