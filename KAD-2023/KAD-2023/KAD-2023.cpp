#pragma once
#include "stdafx.h"

#include "Parm.h"	// обработка параметров
#include "In.h"		// ввод исходного файла
#include "Log.h"	// работа с протоколом
#include "Out.h"	// работа с протоколом
#include "FST.h"
#include "LT.h"
#include "IT.h"
#include "graphs.h"
#include "Error.h"
#include "LexAnalysis.h"
#include "GRB.h"
#include "MFST.h"
#include "SemanticAnalysis.h"
#include "PolishNotation.h"
#include "Generation.h"

using namespace std;

int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "rus");
	system("cls");
	Log::LOG log;
	Out::OUT out;
	try
	{
		//Получение параметров
		Parm::PARM parm = Parm::getparm(argc, argv);				
		log = Log::getlog(parm.log);								
		Log::WriteLog(log.stream);									
		Log::WriteParm(log.stream, parm);							

		In::IN in = In::getin(parm.in);								
		Log::WriteIn(log.stream, in);								

		LT::LexTable lex(LT_MAXSIZE);								
		IT::IdTable id(TI_MAXSIZE);									

		//Лексический анализ 
		LexAnalysis(in, lex, id);
		Log::WriteLine(&std::cout, "Лексический анализ завершен без ошибок.", "");
		Delete(in);

		PrintLexTable(lex, L"Table");
		PrintIdTable(id, L"Table");

		//Синтаксический анализ
		MFST_TRACE_START(log.stream)
			MFST::MFST sintaxAnaliz(lex, GRB::getGreibach());
		bool syntax_ok = sintaxAnaliz.start(log.stream);
		if (!syntax_ok)
		{
			Log::WriteLine(log.stream, "Возникли ошибки во время синтаксического анализа.", "");
			Log::WriteLine(&std::cout, "Возникли ошибки во время синтаксического анализа.\n", "Выполнение программы остановлено", "");
			return 0;
		}
		Log::WriteLine(&std::cout, "Синтаксический анализ завершен без ошибок.", "");
		sintaxAnaliz.printRules(log.stream);

		//Семантический анализ
		SM::semAnaliz(lex, id);
		Log::WriteLine(&std::cout, "Семантический анализ завершен без ошибок.", "");

		//Генерация в ассемблер
		out = Out::getout(parm.out);										// 	создание потокового вывода в выходной файл OUT
		GN::GenerationASM(out.stream, lex, id);
		PrintLexTable(lex, L"PolishNotation");
		Log::WriteLine(log.stream, "----------------------------\nПрограмма завершена успешно.", "");
		Log::WriteLine(&std::cout, "----------------------------\nПрограмма завершена успешно.", "");


		Delete(lex);
		Delete(id);
		Out::Close(out);
		Log::Close(log);
	}

	catch (Error::ERROR e)
	{
		if (e.id >= PARM_BEGIN && e.id <= PARM_END)
			cout << "!ОШИБКА!: " << e.id << ": " << e.message << endl << endl;

		else
		{
			Log::WriteError(log.stream, e);
			Log::Close(log);
			cout << e.message << endl << "Подробнее в протоколе (log файле)" << endl;
		}
	}

	return 0;
}
