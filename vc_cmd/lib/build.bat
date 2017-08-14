cl sqlite3.c -link -dll -out:sqlite3.dll
lib.exe /out:sqlite3.lib sqlite3.obj