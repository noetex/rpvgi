static void
rpvgi__enable_process_dpi_awareness(void)
{
	HMODULE Winuser = LoadLibraryA("user32.dll");
	void* Function = GetProcAddress(Winuser, "SetProcessDpiAwarenessContext");
	if(Function)
	{
		DECLARE_HANDLE(dpi_awareness_context);
		typedef BOOL dpi_function(dpi_awareness_context);
		dpi_function* SetProcessDpiAwarenessContext = (dpi_function*)Function;
		dpi_awareness_context PerMonitorAwareV2 = ((dpi_awareness_context)-4);
		if(!SetProcessDpiAwarenessContext(PerMonitorAwareV2))
		{
			dpi_awareness_context PerMonitorAware = ((dpi_awareness_context)-3);
			SetProcessDpiAwarenessContext(PerMonitorAware);
		}
		return;
	}
	HMODULE ShellCore = LoadLibraryA("shcore.dll");
	Function = GetProcAddress(ShellCore, "SetProcessDpiAwareness");
	if(Function)
	{
		typedef HRESULT dpi_function(enum DPI_PROCESS_AWARENESS);
		enum DPI_PROCESS_AWARENESS PROCESS_PER_MONITOR_DPI_AWARE = 2;
		dpi_function* SetProcessDpiAwareness = (dpi_function*)Function;
		SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
		return;
	}
	Function = GetProcAddress(Winuser, "SetProcessDPIAware");
	if(Function)
	{
		BOOL (*SetProcessDPIAware)(void) = Function;
		SetProcessDPIAware();
	}
}
