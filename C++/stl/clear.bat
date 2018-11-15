:: clear 
cd /d %~dp0
echo clear bat
del /q /s /f *.ilk
del /q /s /f *.obj
del /q /s /f *.pdb
del /q /s /f *.exe