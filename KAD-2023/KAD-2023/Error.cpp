#include "stdafx.h"
#include "Error.h"

namespace Error
{
	// ЯЕПХХ НЬХАНЙ:
	//					0 -  99 - ЯХЯРЕЛМШЕ НЬХАЙХ
	//				  100 - 104 - НЬХАЙХ БУНДМШУ ОЮПЮЛЕРПНБ
	//				  105 - 109 - НЬХАЙХ ОПХ НРЙПШРХХ ТЮИКЮ
	//				  110 - 119 - НЬХАЙХ ОПХ ВРЕМХХ ТЮИКЮ
	//				  120 - 140 - НЬХАЙХ МЮ ЩРЮОЕ КЕЙЯХВЕЯЙНЦН ЮМЮКХГЮРНПЮ
	//				  600 - 610 - НЬХАЙХ МЮ ЩРЮОЕ ЯХМРЮЙЯХВЕЯЙНЦН ЮМЮКХГЮРНПЮ
	//				  700 - 720 - НЬХАЙХ МЮ ЩРЮОЕ ЯЕЛЮМРХВЕЯЙНЦН ЮМЮКХГЮРНПЮ
	ERROR errors[ERROR_MAX_ENTRY] = // РЮАКХЖЮ НЬХАНЙ
	{
		ERROR_ENTRY(0, "мЕДНОСЯРХЛШИ ЙНД НЬХАЙХ"),
		ERROR_ENTRY(1, "яХЯРЕЛМШИ ЯАНИ"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "[ме гюдюм оюпюлерп -IN]"),
		ERROR_ENTRY(101, "[опебшьемхе дкхмш бундмнцн оюпюлерпю]"),
		ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103), ERROR_ENTRY_NODEF(104),
		ERROR_ENTRY(105, "[ньхайю опх нрйпшрхх тюикю -IN]"),
		ERROR_ENTRY(106, "[ньхайю опх нрйпшрхх тюикю - LOG]"),
		ERROR_ENTRY(107, "[ньхайю опх нрйпшрхх тюикю -OUT]"),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "[медносярхлши яхлбнк б тюике -IN]"),
		ERROR_ENTRY(111, "[меубюрйю йюбшвйх]"),
		ERROR_ENTRY_NODEF(112), ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120, "[кейяелю мепюяонгмюммю]"),
		ERROR_ENTRY(121, "[рхо дюммшу хдемрхтхйюрнпю ме нопедекем]"),
		ERROR_ENTRY(122, "[опебшьемхе пюглепю рюакхжш кейяел]"),
		ERROR_ENTRY(123, "[оепеонкмемхе рюакхжш кейяел]"),
		ERROR_ENTRY(124, "[оношрйю напюыемхъ й мегюонкмеммни ярпнйе рюакхжш кейяел]"),
		ERROR_ENTRY(125, "[опебшьемхе пюглепю кейяелш]"),
		ERROR_ENTRY(126, "[ме сдюкняэ нрйпшрэ тюик опнрнйнкю (рюакхжю кейяел)]"),
		ERROR_ENTRY(127, "[опебшьем пюглеп рюакхжш хдемрхтхйюрнпнб]"),
		ERROR_ENTRY(128, "[рюакхжю хдемрхтхйюрнпнб оепеонкмемю]"),
		ERROR_ENTRY(129, "[оношрйю напюыемхъ й мегюонкмеммни ярпнйе рюакхжш хдемрхтхйюрнпнб]"),
		ERROR_ENTRY(130, "[бшунд гю опедекш накюярх бхдхлнярх]"),
		ERROR_ENTRY(131, "[оношрйю оепенопедекемхъ оепелеммни]"),
		ERROR_ENTRY(132, "[рхо ме нопедекем]"),
		ERROR_ENTRY(133, "[нрясрярбхе MAIN]"),
		ERROR_ENTRY(134, "[намюпсфеммн меяйнкэйн рнвей бундю MAIN]"),
		ERROR_ENTRY_NODEF(135), ERROR_ENTRY_NODEF(136), ERROR_ENTRY_NODEF(137), ERROR_ENTRY_NODEF(138), ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "[мебепмюъ ярпсйрспю опнцпюллш]"),
		ERROR_ENTRY(601, "[ньханвмши ноепюрнп]"),
		ERROR_ENTRY(602, "[ньхайю б бшпюфемхх]"),
		ERROR_ENTRY(603, "[ньхайю б оюпюлерпюу опх нопедекемхх тсмйжхх]"),
		ERROR_ENTRY(604, "[ньхайю б оюпюлерпюу опх бшгнбе тсмйжхх]"),
		ERROR_ENTRY(605, "[лнфмн хяонкэгнбюрэ рнкэйн кхрепюк хкх хдемрхтхйюрнп]"),
		ERROR_ENTRY(606, "[ньхайю опх нопедекемхх оепелеммни]"),
		ERROR_ENTRY(607, "[ньхайю опх нопедекемхх сякнбхъ оепеундю]"),
		ERROR_ENTRY(608, "[ньхайю опх мювюкэмни хмхжхюкхгюжхх оепелеммни]"),
		ERROR_ENTRY(609, "[ньхайю б реке жхйкю]"),
		ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640), ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY(700, "[декемхе мю мнкэ]"),
		ERROR_ENTRY(701, "[рхош дюммшу б бшпюфемхх ме янбоюдючр]"),
		ERROR_ENTRY(702, "[медносярхлне ярпнйнбне бшпюфемхе]"),
		ERROR_ENTRY(703, "[рхо тсмйжхх х бнгбпюыюелне гмювемхе ме янбоюдючр]"),
		ERROR_ENTRY(704, "[меянбоюдемхе рхонб оюпюлерпнб]"),
		ERROR_ENTRY(705, "[йнкхвеярбн оепедюбюелшу оюпюлерпнб ме янбоюдюер я нфхдюелшл]"),
		ERROR_ENTRY(706, "[мебепмне сякнбмне бшпюфемхе]"),
		ERROR_ENTRY_NODEF(707), ERROR_ENTRY_NODEF(708), ERROR_ENTRY_NODEF(709),
		ERROR_ENTRY_NODEF10(710), ERROR_ENTRY_NODEF10(720), ERROR_ENTRY_NODEF10(730), ERROR_ENTRY_NODEF10(740), ERROR_ENTRY_NODEF10(750),
		ERROR_ENTRY_NODEF10(760), ERROR_ENTRY_NODEF10(770), ERROR_ENTRY_NODEF10(780), ERROR_ENTRY_NODEF10(790),
		ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	ERROR geterror(int id)
	{
		if (id < 0 || id > ERROR_MAX_ENTRY)
			return errors[0];
		return errors[id];
	}

	ERROR geterrorin(int id, int line = -1, int col = -1)
	{
		if (id < 0 || id > ERROR_MAX_ENTRY)
		{
			return errors[0];
		}
		errors[id].inext.line = line;
		errors[id].inext.col = col;

		if (id > 600)
		{
			return errors[id - 9];
		}
		return errors[id];
	}
}