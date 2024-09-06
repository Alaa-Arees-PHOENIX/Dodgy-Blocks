#ifndef SCREENMANAGER_DB
#define SCREENMANAGER_DB

class ScreenManager
{
	private:
	static constexpr int SCREEN_WIDTH = 1012, SCREEN_HEIGHT = 569; // my personal screen dimensions {1366, 768} scaled down by 1.35
														// having an aspect ratio of 16:9
	int monitorWidth, monitorHeight;
	Camera2D camera = {0};
	
public:
	ScreenManager ();
	void toggle_full_screen (bool); // 1 turn it on, 0 off	
	
public: // Funtions intended to be inlined by the compiler:
	int get_default_screen_width ()		{return SCREEN_WIDTH;}
	int get_default_screen_height ()	{return SCREEN_HEIGHT;}
	int get_monitor_width ()			{return monitorWidth;}
	int get_monitor_height ()			{return monitorHeight;}
	int get_current_screen_width ()		{return IsWindowFullscreen () ? monitorWidth : SCREEN_WIDTH;}
	int get_current_screen_height ()	{return IsWindowFullscreen () ? monitorHeight : SCREEN_HEIGHT;}
	const Camera2D& get_camera ()		{return camera;}
};

#endif // SCREENMANAGER_DB