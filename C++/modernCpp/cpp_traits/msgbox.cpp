
#include <windows.h>

template<class T> class API;
template<class RES, class... Args>
class API<RES(Args...)>
{
	public:
		API(const char* dllName,const char* funcName) {
			_module = LoadLibraryA(dllName);
			if(_module)
			{
				_func = reinterpret_cast<FUNC>(GetProcAddress(_module,funcName));
			}
		
		}
		
		~API()
		{
			if(_module)
				FreeLibrary(_module);
			_module = 0;
		}
		
		RES operator()(Args... args) const {
			 
					return _func(args...);
				 
		}
	private:
		typedef RES (*FUNC)(Args...);
		FUNC _func;
		HMODULE _module;
	
};


 
template<typename _T> class Api;
template<typename _Res, typename... _ArgTypes>
class Api<_Res(_ArgTypes...)> {
public:
    Api(const char* dllName, const char* funcName) {
        _M_module = LoadLibraryA(dllName);
        _M_func = reinterpret_cast<_Func>(GetProcAddress(_M_module, funcName));
    }
    ~Api() {
        if (_M_module) FreeLibrary(_M_module);
    }
    _Res operator()(_ArgTypes... __args) const {
        return _M_func(__args...);
    } 
private:
    typedef _Res (*_Func)(_ArgTypes...);
    _Func _M_func;
    HMODULE _M_module;
};
 
int main()
{
    Api<int(HWND,LPCTSTR,LPCTSTR,UINT)> msgbox("user32", "MessageBoxA");
   // msgbox(0,0,0,0);
   
   API<int(HWND,LPCTSTR,LPCTSTR,UINT)> msg("user32","MessageBoxA");
   msg(0,0,0,0);

}
