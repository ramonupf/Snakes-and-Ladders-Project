
#ifdef __WIN32
#include<windows.h>

void allow_escape_symbols_windows(){
    DWORD outMode = 0;
    HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(stdoutHandle, &outMode);
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(stdoutHandle, outMode);
}
#endif

#include "../headers/menu.h"

//#ifndef TESTING
int main() {
#ifdef __WIN32
    allow_escape_symbols_windows();
#endif

    show_menu();
    return 0;
}
//#endif