::https://www.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/

cmake  -S . -B ./build/   -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE -DBUILD_SHARED_LIBS=TRUE 
