@echo on
cd /d %~dp0
"C:\Program Files (x86)\MSBuild\14.0\Bin\amd64\MSBuild.exe"  TestMSBuild.vcxproj /p:PlatformToolset=v140
