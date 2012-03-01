#include "PreCompiled.h"

// Returns the Base address of the player block in memory - INTERNAL
PBYTE WoWPlayer::GetPlayerBase()
{
	PBYTE plr = NULL;
	SIZE_T size = 0;

	// Retrieve the base address of the player class from the game's memory.
	if( !ReadProcessMemory(hProcess, (baseAddress + PLAYER_BASE_PTR_8606), &plr, sizeof(PBYTE), &size) )
		return NULL;

	return plr;
}

// Returns the base address of the player flags in memory - INTERNAL
PBYTE WoWPlayer::GetPlayerFlagsBase()
{
	PBYTE Plr = GetPlayerBase();
	if( Plr == NULL )
		return false;

	PBYTE FlagsPtr = NULL;
	SIZE_T size = 0;

	// Read the Player Flags pointer
	// The pointer to the player flags is located 0x1190 bytes from the player base
	if( !ReadProcessMemory(hProcess, (Plr + PLAYER_FIELDS_OFFSET_8606), &FlagsPtr, sizeof(PBYTE), &size) || size != sizeof(PBYTE) )
		return NULL;

	// Return 8 bytes past the base to be able to retrieve the player flags bitmask
	return (FlagsPtr ? (FlagsPtr  + PLAYER_FLAGS_8606) : NULL);
}

// Returns the player flags bitmask, or NULL on failure
DWORD WoWPlayer::GetFlags()
{
	PBYTE FlagsPtr = GetPlayerFlagsBase();
	DWORD PlrFlags = NULL;
	SIZE_T size = 0;

	if( !FlagsPtr )
		return NULL;

	// Read 8 bytes past the base to retrieve the player flags bitmask
	if( !ReadProcessMemory(hProcess, FlagsPtr, &PlrFlags, sizeof(DWORD), &size) || size != sizeof(DWORD) )
		return NULL;

	return PlrFlags;
}

// Checks to see if the passed bitmask exists in the player flags bitmask.
// Returns true on success.
bool WoWPlayer::HasFlags(DWORD flags) { return (GetFlags() & flags) > 0; }

// Does a bitwise OR operation on the player flags, adding whatever is passed.
// Returns true on success.
bool WoWPlayer::SetFlags(DWORD flags)
{
	PBYTE FlagsPtr = GetPlayerFlagsBase();
	DWORD PlrFlags = NULL;
	SIZE_T size = 0;

	if( !FlagsPtr )
		return false;

	// Read the player flags and do a bitwise OR on them, adding the passed flags to them
	PlrFlags = GetFlags() | flags;

	// Write the new flags back to the player flags in memory
	if( !WriteProcessMemory(hProcess, FlagsPtr, &PlrFlags, sizeof(DWORD), &size) || size != sizeof(DWORD) )
		return false;

	return true;
}

// Does a bitwise inverse OR on the player flags, removing whatever is passed.
// Returns true on success.
bool WoWPlayer::RemoveFlags(DWORD flags)
{
	PBYTE FlagsPtr = GetPlayerFlagsBase();
	DWORD PlrFlags = NULL;
	SIZE_T size = 0;

	if( !FlagsPtr )
		return false;

	// Read the player flags and do a bitwise inverse AND on them, removing the passed flags from them
	PlrFlags = GetFlags() & ~flags;

	// Write the new flags back to the player flags in memory
	if( !WriteProcessMemory(hProcess, FlagsPtr, &PlrFlags, sizeof(DWORD), &size) || size != sizeof(DWORD) )
		return false;

	return true;
}

// Returns whether or not the player is in commentator mode
bool WoWPlayer::IsInCommentatorMode()
{
	return HasFlags(PLAYER_FLAGS_COMMENTATOR|PLAYER_FLAGS_CAN_USE_COMMENTATOR_COMMANDS);
}

// Toggles commentator mode
// Returns true on success
bool WoWPlayer::SetCommentatorMode(bool bEnable)
{
	// Retrieve the player flags
	DWORD PlrFlags = GetFlags();
	SIZE_T size = 0;

	if( bEnable )
	{
		// Read the players position
		Vec4 pos = GetPosition();

		// Increase the Z axis so the camera doesn't appear at ground level
		pos.Z += 10.0f;

		// Copy the players position to the commentator camera's position, with a slight offset to Z
		if( !WriteProcessMemory(hProcess, (baseAddress + PLAYER_COMMENTATOR_X_8606), &pos.X, sizeof(float), &size) || size != sizeof(float) )
			return false;
		if( !WriteProcessMemory(hProcess, (baseAddress + PLAYER_COMMENTATOR_Y_8606), &pos.Y, sizeof(float), &size) || size != sizeof(float) )
			return false;
		if( !WriteProcessMemory(hProcess, (baseAddress + PLAYER_COMMENTATOR_Z_8606), &pos.Z, sizeof(float), &size) || size != sizeof(float) )
			return false;

		// Write the player flags back to memory, to enable commentator mode
		return SetFlags(PLAYER_FLAGS_COMMENTATOR|PLAYER_FLAGS_CAN_USE_COMMENTATOR_COMMANDS);
	}

	// Write the player flags back to memory, to disable commentator mode
	return RemoveFlags(PLAYER_FLAGS_COMMENTATOR|PLAYER_FLAGS_CAN_USE_COMMENTATOR_COMMANDS);
}

// Sets the commentator camera speed multiplier
// Returns true on success
bool WoWPlayer::SetCommentatorCameraSpeed(float speed)
{
	SIZE_T size = 0;
	if( !WriteProcessMemory(hProcess, (baseAddress + PLAYER_COMMENTATOR_SPEED_8606), &speed, sizeof(float), &size) || size != sizeof(float) )
		return false;
	return true;
}

// Returns the speed of the camera in commentator mode
float WoWPlayer::GetCommentatorCameraSpeed()
{
	SIZE_T size;
	float speed = 0.0f;

	ReadProcessMemory(hProcess, (baseAddress + PLAYER_COMMENTATOR_SPEED_8606), &speed, sizeof(float), &size);
	return speed;
}

// Sets whether or not the commentator camera will collide with terrian
// Returns true on success
bool WoWPlayer::SetCommentatorCameraCollision(bool bEnable)
{
	SIZE_T size = 0;
	if( !WriteProcessMemory(hProcess, (baseAddress + PLAYER_COMMENTATOR_COLLISION_8606), &bEnable, sizeof(bool), &size) || size != sizeof(bool) )
		return false;
	return true;
}

// Returns whether or not the commentator camera will collide with terrian
bool WoWPlayer::IsCommentatorCameraCollidable()
{
	SIZE_T size;
	bool bCollision = false;

	if( !ReadProcessMemory(hProcess, (baseAddress + PLAYER_COMMENTATOR_COLLISION_8606), &bCollision, sizeof(bool), &size) || size != sizeof(bool) )
		return false;

	return bCollision;
}

// Returns a XYZO vector of the players coordinates
Vec4 WoWPlayer::GetPosition()
{
	Vec4 pos = { NULL };
	PBYTE Plr = GetPlayerBase();
	SIZE_T size = 0;
	if( Plr == NULL )
		return pos;

	// Read the current position of the player
	ReadProcessMemory(hProcess, (Plr + PLAYER_POSITION_X_OFFSET_8606), &pos, sizeof(Vec4), &size);
	return pos;
}

// Returns the players X coordinate
float WoWPlayer::GetPosX()
{
	PBYTE Plr = GetPlayerBase();
	if( Plr == NULL )
		return false;

	float pX = 0.0f;
	SIZE_T size = 0;

	// Read the current position of the players X coordinate
	ReadProcessMemory(hProcess, (Plr + PLAYER_POSITION_X_OFFSET_8606), &pX, sizeof(float), &size);

	return pX;
}

// Returns the players Y coordinate
float WoWPlayer::GetPosY()
{
	PBYTE Plr = GetPlayerBase();
	if( Plr == NULL )
		return false;

	float pY = 0.0f;
	SIZE_T size = 0;

	// Read the current position of the players Y coordinate
	ReadProcessMemory(hProcess, (Plr + PLAYER_POSITION_Y_OFFSET_8606), &pY, sizeof(float), &size);

	return pY;
}

// Returns the players Z coordinate
float WoWPlayer::GetPosZ()
{
	PBYTE Plr = GetPlayerBase();
	if( Plr == NULL )
		return false;

	float pZ = 0.0f;
	SIZE_T size = 0;

	// Read the current position of the players Z coordinate
	ReadProcessMemory(hProcess, (Plr + PLAYER_POSITION_Z_OFFSET_8606), &pZ, sizeof(float), &size);

	return pZ;
}

// Returns the players orientation (Tau)
float WoWPlayer::GetPosO()
{
	PBYTE Plr = GetPlayerBase();
	if( Plr == NULL )
		return false;

	float pO = 0.0f;
	SIZE_T size = 0;

	// Read the current position of the players orientation
	ReadProcessMemory(hProcess, (Plr + PLAYER_POSITION_O_OFFSET_8606), &pO, sizeof(float), &size);

	return pO;
}

// Sets the XYZO coordinates of the player using a vector
// Returns true on success
bool WoWPlayer::SetPosition(Vec4 pos)
{
	SIZE_T size = 0;
	PBYTE Plr = GetPlayerBase();
	if( Plr == NULL )
		return false;

	// Set the current position of the player
	if( !WriteProcessMemory(hProcess, (Plr + PLAYER_POSITION_X_OFFSET_8606), &pos, sizeof(Vec4), &size) || size != sizeof(Vec4) )
		return false;

	return true;
}

// Sets the XYZ coordinates of the player using a vector
// Returns true on success
bool WoWPlayer::SetPosition(Vec3 pos)
{
	SIZE_T size = 0;
	PBYTE Plr = GetPlayerBase();
	if( Plr == NULL )
		return false;

	// Set the current position of the player
	if( !WriteProcessMemory(hProcess, (Plr + PLAYER_POSITION_X_OFFSET_8606), &pos, sizeof(Vec3), &size) || size != sizeof(Vec4) )
		return false;

	return true;
}

// Sets the XYZO coordinates of the player
// Returns true on success
bool WoWPlayer::SetPosition(float X, float Y, float Z, float O)
{
	Vec4 pos = { X, Y, Z, O };
	return SetPosition(pos);
}

// Set the Player's X coordinate
// Returns true on success
bool WoWPlayer::SetPosX(float newX)
{
	SIZE_T size = 0;
	PBYTE Plr = GetPlayerBase();
	if( Plr == NULL )
		return false;

	// Set the current position of the players X coordinate
	if( !WriteProcessMemory(hProcess, (Plr + PLAYER_POSITION_X_OFFSET_8606), &newX, sizeof(float), &size) || size != sizeof(float) )
		return false;

	return true;
}

// Set the Player's Y coordinate
// Returns true on success
bool WoWPlayer::SetPosY(float newY)
{
	SIZE_T size = 0;
	PBYTE Plr = GetPlayerBase();
	if( Plr == NULL )
		return false;

	// Set the current position of the players Y coordinate
	if( !WriteProcessMemory(hProcess, (Plr + PLAYER_POSITION_Y_OFFSET_8606), &newY, sizeof(float), &size) || size != sizeof(float) )
		return false;

	return true;
}

// Set the Player's X coordinate
// Returns true on success
bool WoWPlayer::SetPosZ(float newZ)
{
	SIZE_T size = 0;
	PBYTE Plr = GetPlayerBase();
	if( Plr == NULL )
		return false;

	// Set the current position of the players Z coordinate
	if( !WriteProcessMemory(hProcess, (Plr + PLAYER_POSITION_Z_OFFSET_8606), &newZ, sizeof(float), &size) || size != sizeof(float) )
		return false;

	return true;
}

// Set the Player's orientation (Tau)
// Returns true on success
bool WoWPlayer::SetPosO(float newO)
{
	SIZE_T size = 0;
	PBYTE Plr = GetPlayerBase();
	if( Plr == NULL )
		return false;

	// Set the current position of the players orientation
	if( !WriteProcessMemory(hProcess, (Plr + PLAYER_POSITION_O_OFFSET_8606), &newO, sizeof(float), &size) || size != sizeof(float) )
		return false;

	return true;
}