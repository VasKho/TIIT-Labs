@echo off
setlocal enabledelayedexpansion
for /L %%I in (1,1,10) do touch text%%I.txt
set /P tekst="Enter text "
forfiles /M *.txt /c "cmd /c echo @fname>@file"
set D=0
for %%N in (*.txt) do (
findstr /M "%tekst%" %%N> delf
set /p D=<delf
if !D! neq 0 del /p !D!
set D=0
)
del delf
pause