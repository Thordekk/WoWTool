#include "PreCompiled.h"

// Returns the Base address of the camera block in memory - INTERNAL
PBYTE Camera::GetCameraBase()
{
	PBYTE cam = NULL;
	SIZE_T size = 0;

	// Retrieve the base address of the camera class from the game's memory.
	if( !ReadProcessMemory(hProcess, (baseAddress + CAMERA_BASE_PTR_12340), &cam, sizeof(PBYTE), &size) )
		return NULL;
	if( !ReadProcessMemory(hProcess, (cam + CAMERA_CLASS_OFFSET_12340), &cam, sizeof(PBYTE), &size) )
		return NULL;

	return cam;
}

// Returns the Cameras field of view in degrees
float Camera::GetFieldOfView()
{
	PBYTE Cam = GetCameraBase();
	SIZE_T size = 0;
	float fov = 0.0f;

	if( !Cam )
		return 0.0f;

	// Read 0x40 bytes past the camera base to retrieve the field of view.
	ReadProcessMemory(hProcess, (Cam + CAMERA_FOV_OFFSET_12340), &fov, sizeof(float), &size);

	// return the result in degrees, not radians.
	return (fov * (180.0f/(float)M_PI));
}

// Sets the new field of view (passed float is degrees)
// Return true on success
bool Camera::SetFieldOfView(float newFov)
{
	PBYTE Cam = GetCameraBase();
	SIZE_T size = 0;

	if( !Cam )
		return false;

	// Convert the field of view from degrees to radians
	if( newFov < 0.1f )
		newFov = 0.1f;
	while( newFov > 180.0f )
		newFov -= 180.0f;
	newFov = newFov * ((float)M_PI/180.0f);

	// Set the new field of view
	if( !WriteProcessMemory(hProcess, (Cam + CAMERA_FOV_OFFSET_12340), &newFov, sizeof(float), &size) || size != sizeof(float) )
		return false;

	return true;
}

// Returns the camera yaw in degrees
float Camera::GetYaw()
{
	PBYTE Cam = GetCameraBase();
	SIZE_T size = 0;
	float yaw = 0.0f;

	if( !Cam )
		return 0.0f;

	// Read 104 bytes past the camera base to retrieve the camera yaw.
	if( !ReadProcessMemory(hProcess, (Cam + CAMERA_YAW_OFFSET_12340), &yaw, sizeof(float), &size) )
		return 0.0f;

	// Return the result in degrees, not radians
	return (yaw * (360.0f/(float)(M_PI*2)));
}

// Returns the camera pitch in degrees
float Camera::GetPitch()
{
	PBYTE Cam = GetCameraBase();
	SIZE_T size = 0;
	float pitch = 0.0f;

	if( !Cam )
		return 0.0f;

	// Read 10C bytes past the camera base to retrieve the camera roll.
	if( !ReadProcessMemory(hProcess, (Cam + CAMERA_PITCH_OFFSET_12340), &pitch, sizeof(float), &size) )
		return 0.0f;

	// Return the result in degrees, not radians
	return (pitch * (360.0f/(float)(M_PI*2)));
}

// Returns the camera roll in degrees
float Camera::GetRoll()
{
	PBYTE Cam = GetCameraBase();
	SIZE_T size = 0;
	float roll = 0.0f;

	if( !Cam )
		return 0.0f;

	// Read 10C bytes past the camera base to retrieve the camera roll.
	if( !ReadProcessMemory(hProcess, (Cam + CAMERA_ROLL_OFFSET_12340), &roll, sizeof(float), &size) )
		return 0.0f;

	// Return the result in degrees, not radians
	return (roll * (360.0f/(float)(M_PI*2)));
}

// Sets the camera yaw (passed float is in degrees)
// Returns true on success
bool Camera::SetYaw(float newYaw)
{
	PBYTE Cam = GetCameraBase();
	SIZE_T size = 0;

	if( !Cam )
		return false;

	while( newYaw > 360.0f )
		newYaw -= 360.0f;

	// Convert the yaw from degrees to radians
	newYaw = newYaw * ((float)(M_PI*2)/360.0f);

	// Set the new camera yaw
	if( !WriteProcessMemory(hProcess, (Cam + CAMERA_YAW_OFFSET_12340), &newYaw, sizeof(float), &size) || size != sizeof(float) )
		return false;

	return true;
}

// Sets the camera pitch (passed float is in degrees)
// Returns true on success
bool Camera::SetPitch(float newPitch)
{
	PBYTE Cam = GetCameraBase();
	SIZE_T size = 0;

	if( !Cam )
		return false;

	while( newPitch > 360.0f )
		newPitch -= 360.0f;

	// Convert the pitch from degrees to radians
	newPitch = newPitch * ((float)(M_PI*2)/360.0f);

	// Set the new camera pitch
	if( !WriteProcessMemory(hProcess, (Cam + CAMERA_PITCH_OFFSET_12340), &newPitch, sizeof(float), &size) || size != sizeof(float) )
		return false;

	return true;
}

// Sets the camera roll (passed float is in degrees)
// Returns true on success
bool Camera::SetRoll(float newRoll)
{
	PBYTE Cam = GetCameraBase();
	SIZE_T size = 0;

	if( !Cam )
		return false;

	while( newRoll > 360.0f )
		newRoll -= 360.0f;

	// Convert the roll from degrees to radians
	newRoll = newRoll * ((float)(M_PI*2)/360.0f);

	// Set the new camera roll
	if( !WriteProcessMemory(hProcess, (Cam + CAMERA_ROLL_OFFSET_12340), &newRoll, sizeof(float), &size) || size != sizeof(float) )
		return false;

	return true;
}