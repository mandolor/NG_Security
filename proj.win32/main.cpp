#include "main.h"
#include "../Sources/AppDelegate.h"

USING_NS_CC;

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func( void ) { return _iob; }
int ( WINAPIV * __vsnprintf )( char *, size_t, const char*, va_list ) = _vsnprintf;

//---------------------------------------------------------------------
int _stdcall _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
