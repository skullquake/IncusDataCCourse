@echo off
rem for /r ..\libs %%f in (Makefile) do @echo %%f
for /r ..\libs %%f in (Makefile) do @echo %~nxA
