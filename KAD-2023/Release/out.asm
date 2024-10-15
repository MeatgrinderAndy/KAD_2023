.586							; ������� ������ (��������� Pentium)
.model flat, stdcall			; ������ ������, ���������� � �������
includelib kernel32.lib
includelib libucrt.lib
includelib StaticLib.lib

ExitProcess PROTO: dword		; �������� ������� ��� ���������� �������� Windows

EXTRN lenght: proc
EXTRN write_int: proc
EXTRN write_str : proc
EXTRN copy: proc
EXTRN getLocalTimeAndDate: proc
EXTRN random: proc
EXTRN squareOfNumber: proc
EXTRN factorialOfNumber: proc
EXTRN powNumber: proc

.stack 4096

.const							; ������� �������� - ��������
nulError byte 'error divided by zero', 0
nul sdword 0, 0

	L0 sword 5
.data							; ������� ������ - ���������� � ���������
	a_main sword 0
.code							; ������� ����

;----------- MAIN ------------
main PROC

push L0
pop a_main

push a_main
call write_short

jmp goodExit
errorExit:
push offset nulError
call write_str
goodExit:
push 0
call ExitProcess
main ENDP
end main