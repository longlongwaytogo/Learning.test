echo on
cd /d %~dp0
set path=%path%;C:\Program Files (x86)\MSBuild\14.0\Bin\amd64;D:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE
devenv.com TestMSBuild.sln /build "Debug|x64" /Project TestMSBuild 