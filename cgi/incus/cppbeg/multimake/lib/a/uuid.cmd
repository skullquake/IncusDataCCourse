@echo off
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:GUID <xReturn>
:: Generate a GUID with delayed expansion.
setlocal enabledelayedexpansion

:::: Generate Random Hexidecimal GUID
:: Loop Once for each GUID Value = 32
:: 1. Check if Hyphen Insert Needed
:: 2. Generate Random Number = 0-15
:: 3. Convert Number to Hexidecimal
:: 4. Append to GUID
set "xGUID="
for /L %%n in (1,1,32) do (
	if "%%~n"=="9"  set "xGUID=!xGUID!"
	if "%%~n"=="13" set "xGUID=!xGUID!"
	if "%%~n"=="17" set "xGUID=!xGUID!"
	if "%%~n"=="21" set "xGUID=!xGUID!"
	set /a "xValue=!random! %% 16"
	if "!xValue!"=="10" set "xValue=A"
	if "!xValue!"=="11" set "xValue=B"
	if "!xValue!"=="12" set "xValue=C"
	if "!xValue!"=="13" set "xValue=D"
	if "!xValue!"=="14" set "xValue=E"
	if "!xValue!"=="15" set "xValue=F"
	set "xGUID=!xGUID!!xValue!"
)
echo H%xGUID%
endlocal & if not "%~1"=="" set "%~1=%xGUID%"
goto :eof
:: by David Ruhmann
