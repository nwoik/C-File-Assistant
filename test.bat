@echo off

set "fname=test"
set "ext=.txt"
set "inc=0"
set "dst=.\Testfolder\" 

if exist "%dst%%fname%%ext%" (echo "%dst%%fname%%ext%")

:back
set /A inc+=1
if exist "%dst%%fname%(%inc%)%ext%" goto back

move "%fname%%ext%" "%dst%%fname%(%inc%)%ext%"