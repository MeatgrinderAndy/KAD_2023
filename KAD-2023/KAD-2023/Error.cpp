#include "stdafx.h"
#include "Error.h"

namespace Error
{
	// ����� ������:
	//					0 -  99 - ��������� ������
	//				  100 - 104 - ������ ������� ����������
	//				  105 - 109 - ������ ��� �������� �����
	//				  110 - 119 - ������ ��� ������ �����
	//				  120 - 140 - ������ �� ����� ������������ �����������
	//				  600 - 610 - ������ �� ����� ��������������� �����������
	//				  700 - 720 - ������ �� ����� �������������� �����������
	ERROR errors[ERROR_MAX_ENTRY] = // ������� ������
	{
		ERROR_ENTRY(0, "������������ ��� ������"),
		ERROR_ENTRY(1, "��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "[�� ����� �������� -IN]"),
		ERROR_ENTRY(101, "[���������� ����� �������� ���������]"),
		ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103), ERROR_ENTRY_NODEF(104),
		ERROR_ENTRY(105, "[������ ��� �������� ����� -IN]"),
		ERROR_ENTRY(106, "[������ ��� �������� ����� - LOG]"),
		ERROR_ENTRY(107, "[������ ��� �������� ����� -OUT]"),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "[������������ ������ � ����� -IN]"),
		ERROR_ENTRY(111, "[�������� �������]"),
		ERROR_ENTRY_NODEF(112), ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120, "[������� �������������]"),
		ERROR_ENTRY(121, "[��� ������ �������������� �� ���������]"),
		ERROR_ENTRY(122, "[���������� ������� ������� ������]"),
		ERROR_ENTRY(123, "[������������ ������� ������]"),
		ERROR_ENTRY(124, "[������� ��������� � ������������� ������ ������� ������]"),
		ERROR_ENTRY(125, "[���������� ������� �������]"),
		ERROR_ENTRY(126, "[�� ������� ������� ���� ��������� (������� ������)]"),
		ERROR_ENTRY(127, "[�������� ������ ������� ���������������]"),
		ERROR_ENTRY(128, "[������� ��������������� �����������]"),
		ERROR_ENTRY(129, "[������� ��������� � ������������� ������ ������� ���������������]"),
		ERROR_ENTRY(130, "[����� �� ������� ������� ���������]"),
		ERROR_ENTRY(131, "[������� ��������������� ����������]"),
		ERROR_ENTRY(132, "[��� �� ���������]"),
		ERROR_ENTRY(133, "[���������� MAIN]"),
		ERROR_ENTRY(134, "[����������� ��������� ����� ����� MAIN]"),
		ERROR_ENTRY_NODEF(135), ERROR_ENTRY_NODEF(136), ERROR_ENTRY_NODEF(137), ERROR_ENTRY_NODEF(138), ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "[�������� ��������� ���������]"),
		ERROR_ENTRY(601, "[��������� ��������]"),
		ERROR_ENTRY(602, "[������ � ���������]"),
		ERROR_ENTRY(603, "[������ � ���������� ��� ����������� �������]"),
		ERROR_ENTRY(604, "[������ � ���������� ��� ������ �������]"),
		ERROR_ENTRY(605, "[����� ������������ ������ ������� ��� �������������]"),
		ERROR_ENTRY(606, "[������ ��� ����������� ����������]"),
		ERROR_ENTRY(607, "[������ ��� ����������� ������� ��������]"),
		ERROR_ENTRY(608, "[������ ��� ��������� ������������� ����������]"),
		ERROR_ENTRY(609, "[������ � ���� �����]"),
		ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640), ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY(700, "[������� �� ����]"),
		ERROR_ENTRY(701, "[���� ������ � ��������� �� ���������]"),
		ERROR_ENTRY(702, "[������������ ��������� ���������]"),
		ERROR_ENTRY(703, "[��� ������� � ������������ �������� �� ���������]"),
		ERROR_ENTRY(704, "[������������ ����� ����������]"),
		ERROR_ENTRY(705, "[���������� ������������ ���������� �� ��������� � ���������]"),
		ERROR_ENTRY(706, "[�������� �������� ���������]"),
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