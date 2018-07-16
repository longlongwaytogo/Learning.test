rem —”≥Ÿ±‰¡ø≤‚ ‘
@echo off
rem setlocal enabledelayedexpansion
setlocal enabledelayedexpansion
set num=12

 for /l %%i in (1,1,5) do (
    
set /a num+=10

echo !num!

)


pause
