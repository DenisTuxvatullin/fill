@echo off
fill.exe
IF ERRORLEVEL 1 GOTO err

fill.exe nofile.txt out.txt
IF NOT ERRORLEVEL 1 GOTO err

fill.exe fillWithNoStartPoints.txt out.txt
IF ERRORLEVEL 1 GOTO err
FC /B out.txt fillWithNoStartPoints_out.txt
IF ERRORLEVEL 1 GOTO err

fill.exe fillWithNoStartPoints.txt out.txt
IF ERRORLEVEL 1 GOTO err
FC /B out.txt fillWithNoStartPoints_out.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-)
pause
EXIT /B

:err
pause
ECHO Program testing failed :-(
EXIT /B