#include <iostream>
#include <Windows.h>
#include <time.h>
#pragma warning(disable: 4996)


	extern "C"
	{

		short write_short(short p)											//����� �����
		{
			std::cout << p << std::endl;
			return 0;
		}

		short write_str(char* str)											//����� ������
		{
			setlocale(LC_ALL, "rus");
			std::cout << str << std::endl;
			return 0;
		}

		short lenght(char* str)												//����� ������
		{
			short len = strlen(str);
			return len;
		}

		char* copy(char* str1, char* str2, short count)						//����������� ������������� ���-�� �������� �� ������ � ������
		{
			int i;
			str1 = (char*)malloc(count);
			for (i = 0; i < count; i++) {
				str1[i] = str2[i];
			}
			str1[i] = '\0';

			return str1;
		}

		//��� �������


		short random(short start, short end)
		{
			srand(time(NULL));
			short res = rand() % end + start;
			return res;
		}
	
		char* getLocalTimeAndDate()
		{
			time_t now = time(0);
			char* dt = ctime(&now);
			return dt;
		}

	
}