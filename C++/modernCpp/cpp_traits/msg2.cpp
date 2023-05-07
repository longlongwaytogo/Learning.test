
#include <map>
#include <string>
#include <functional>
#include <windows.h>
 
 
class WinDll {
public:
    WinDll(const char* dll) {
        mMoudle = LoadLibraryA(dll);
    }
    WinDll(const wchar_t* dll) {
        mMoudle = LoadLibraryW(dll);
    }
    ~WinDll() {
        if (mMoudle) FreeLibrary(mMoudle);
    }
    
    FARPROC RawApi(const std::string& fn) {
        auto it = mFuncCaches.find(fn);
        if (it == mFuncCaches.end()) {
            FARPROC func = GetProcAddress(mMoudle, fn.c_str());
            if (!func) throw "not found!";
            mFuncCaches[fn] = func;
            return func;
        } 
        return it->second;
    }
    
    template<typename _T>
    std::function<_T> ApiFunc(const std::string& fn) {
        return std::function<_T>(reinterpret_cast<_T*>(RawApi(fn)));
    }
    
private:
    HMODULE mMoudle;
    std::map<std::string,FARPROC> mFuncCaches;
};
 
int main()
{
    WinDll user32("user32");
    using TMessageBoxA = int(HWND,LPCTSTR,LPCTSTR,UINT);
    auto msgBox = user32.ApiFunc<TMessageBoxA>("MessageBoxA");
    msgBox(0,0,0,0);
}