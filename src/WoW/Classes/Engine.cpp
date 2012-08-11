#include "PreCompiled.h"

// Sets the speed of animations
// Default: 1000
// Returns true on success
bool Engine::SetAnimationSpeed(double speed)
{
	SIZE_T size;
	DWORD oldProtect;
	bool ret = false;

	if( VirtualProtectEx(hProcess, (baseAddress + ENGINE_SPEED_OF_ANIMATION_NEW_8606), sizeof(double), PAGE_READWRITE, &oldProtect) != 0 )
	{
		ret = (WriteProcessMemory(hProcess, (baseAddress + ENGINE_SPEED_OF_ANIMATION_NEW_8606), &speed, sizeof(double), &size) && size == sizeof(double));
		VirtualProtectEx(hProcess, (baseAddress + ENGINE_SPEED_OF_ANIMATION_NEW_8606), sizeof(double), oldProtect, &oldProtect);
	}
	return ret;
}

// Sets the game speed of the game (speed of everything from time, animations, etc)
// Default: 0.00100000004749
// Returns true on success
bool Engine::SetGameSpeed(double speed)
{
	SIZE_T size;
	return (WriteProcessMemory(hProcess, (baseAddress + ENGINE_GAME_SPEED_8606), &speed, sizeof(double), &size) && size == sizeof(double));
}

// Returns the speed of animations
// Default: 1000
double Engine::GetAnimationSpeed()
{
	SIZE_T size = 0;
	double speed = 0.0f;

	if( !ReadProcessMemory(hProcess, (baseAddress + ENGINE_SPEED_OF_ANIMATION_8606), &speed, sizeof(double), &size) || size != sizeof(double) )
		return 0.0f;

	return speed;
}

// Returns the speed of the game (speed of everything from time, animations, etc)
// Default: 0.00100000004749
double Engine::GetGameSpeed()
{
	SIZE_T size;
	double speed = 0.0f;

	if( !ReadProcessMemory(hProcess, (baseAddress + ENGINE_GAME_SPEED_8606), &speed, sizeof(double), &size) || size != sizeof(double) )
		return 0.0f;

	return speed;
}

// Returns the bitmask that the game uses to decide what and how to render the scene
// Default: 0x1F104F73
DWORD Engine::GetRenderingFlags()
{
	DWORD bitmask = 0;
	SIZE_T size = 0;

	if( !ReadProcessMemory(hProcess, (baseAddress + ENGINE_RENDERING_FLAGS_8606), &bitmask, sizeof(DWORD), &size) || size != sizeof(DWORD) )
		return NULL;

	return bitmask;
}

// Checks to see if the passed bitmask exists in the rendering flags bitmask.
// Returns true on success.
bool Engine::HasRenderingFlags(DWORD flags) { return ((GetRenderingFlags() & flags) == flags); }

// Sets the bitmask that the game uses to decide what and how to render the scene
// Returns true on success
bool Engine::SetRenderingFlags(DWORD flags)
{
	DWORD RenderingFlags = NULL;
	SIZE_T size = 0;

	// Read the rendering flags and do a bitwise OR on them, adding the passed flags to them
	RenderingFlags = GetRenderingFlags() | flags;

	// Write the new flags back to the rendering flags in memory
	if( !WriteProcessMemory(hProcess, (baseAddress + ENGINE_RENDERING_FLAGS_8606), &RenderingFlags, sizeof(DWORD), &size) || size != sizeof(DWORD) )
		return false;

	return true;
}


// Does a bitwise inverse OR on the rendering flags, removing whatever is passed.
// Returns true on success.
bool Engine::RemoveRenderingFlags(DWORD flags)
{
	DWORD RenderingFlags = NULL;
	SIZE_T size = 0;

	// Read the rendering flags and do a bitwise inverse AND on them, removing the passed flags from them
	RenderingFlags = GetRenderingFlags() & ~flags;

	// Write the new flags back to the rendering flags in memory
	if( !WriteProcessMemory(hProcess, (baseAddress + ENGINE_RENDERING_FLAGS_8606), &RenderingFlags, sizeof(DWORD), &size) || size != sizeof(DWORD) )
		return false;

	return true;
}