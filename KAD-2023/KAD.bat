@ECHO OFF
timeout 1
cd /d C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build
call vcvarsall.bat x86
cd /d D:\\KAD-2023-CP\\KAD-2023\\KAD-2023
ml /c /coff /Zi out.asm
link /OPT:NOREF /DEBUG /SUBSYSTEM:CONSOLE libucrt.lib Generated.obj 
call Generated.exe
timeout 5
pause
exit