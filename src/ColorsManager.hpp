#ifndef COLORSMANAGER_DB
#define COLORSMANAGER_DB

#include <unordered_map>
#include <cstddef>
#include "raylib.h"

namespace std
{
    template<> struct hash<Color>
    {
        size_t operator()(Color const& c) const noexcept
        {
            return std::hash<unsigned char>() (c.r) ^
			((std::hash<unsigned char>() (c.g)) << 1) ^
			((std::hash<unsigned char>() (c.b)) << 2) ^
			((std::hash<unsigned char>() (c.a)) << 3);
        }
    };
}

bool operator== (Color c1, Color c2);

class ColorsManager
{
public:
	ColorsManager ();
	~ColorsManager ();
	Color color_mode (const Color& c1);
	Color color_mode (const Color&& c1);
	
	
	void toggle_dark_mode () {darkMode = !darkMode;}
	bool is_dark_mode_enabled () {return darkMode;}
	
private:
	bool darkMode;
	/* it is possible to get the inverse of a color with a simple function, but
		the inverse isn't always the best-looking color to have in the game, so
		this unordered_map will help customize the game more.*/
	std::unordered_map <Color, Color> darkVersionOfColor;
	
	static constexpr Color NEIL = {20, 20, 75, 255};
};

#endif // COLORSMANAGER_DB