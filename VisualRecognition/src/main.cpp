
    #include <windows.h>
    import ui;

    void RunUI(HINSTANCE instance, int cmdShow);

    int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int cmdShow)
    {
        // Prefer per-monitor DPI awareness for consistent capture coordinates
        ::SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

        RunUI(instance, cmdShow);
        return 0;
    }
