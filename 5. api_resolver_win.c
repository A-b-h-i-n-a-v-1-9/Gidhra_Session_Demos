// dynamic API resolution (malware technique)
// api_resolver_win.c  (Windows only)
#ifdef _WIN32
#include <windows.h>

typedef int (WINAPI *MSGBOXA)(HWND, LPCSTR, LPCSTR, UINT);

int main(void) {
    HMODULE mod = LoadLibraryA("user32.dll");
    if (!mod) return -1;

    FARPROC fp = GetProcAddress(mod, "MessageBoxA");
    if (!fp) return -2;

    MSGBOXA msg = (MSGBOXA)fp;
    msg(NULL, "Hello from dynamically resolved API!", "API Resolver Demo", MB_OK);
    return 0;
}
#else
int main(void) { return 0; }
#endif
