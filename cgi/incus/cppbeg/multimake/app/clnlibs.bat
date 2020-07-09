@echo off
for /R ..\lib %%G IN (Makefile.*) do (
	make -C "%%~dpG." clean
)
