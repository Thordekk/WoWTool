#pragma once

struct Vec3
{
	float X;
	float Y;
	float Z;
};
struct Vec4
{
	float X;
	float Y;
	float Z;
	float O;
};

// Game versions
#define FINAL_TBC										8606
#define FINAL_WOTLK										12340

// Rendering flags
enum RenderingFlags
{
	RENDER_FLAG_SIMPLE_DOODADS							= 0x00000001, // 00
	RENDER_FLAG_TERRAIN									= 0x00000002, // 01
	RENDER_FLAG_UNK01									= 0x00000004, // 02
	RENDER_FLAG_UNK02									= 0x00000008, // 03
	RENDER_FLAG_UNK03									= 0x00000010, // 04
	RENDER_FLAG_TERRAIN_CULLING							= 0x00000020, // 05
	RENDER_FLAG_TERRAIN_SHADOW							= 0x00000040, // 06
	RENDER_FLAG_UNK06									= 0x00000080, // 07
	RENDER_FLAG_WMO										= 0x00000100, // 08
	RENDER_FLAG_WMO_BAKED_SHADOWS						= 0x00000200, // 09
	RENDER_FLAG_UNK07									= 0x00000400, // 10
	RENDER_FLAG_WMO_INTERIOR_TEXTURES					= 0x00000800, // 11
	RENDER_FLAG_WMO_OPENING								= 0x00001000, // 12
	RENDER_FLAG_UNK08									= 0x00002000, // 13
	RENDER_FLAG_UNK09									= 0x00004000, // 14
	RENDER_FLAG_UNK10									= 0x00008000, // 15
	RENDER_FLAG_UNK11									= 0x00010000, // 16
	RENDER_FLAG_UNK12									= 0x00020000, // 17
	RENDER_FLAG_UNK13									= 0x00040000, // 18
	RENDER_FLAG_UNK14									= 0x00080000, // 19
	RENDER_FLAG_DETAIL_DOODADS							= 0x00100000, // 20
	RENDER_FLAG_WMO_AND_TERRAIN_HIT_FACES				= 0x00200000, // 21
	RENDER_FLAG_UNK15									= 0x00400000, // 22
	RENDER_FLAG_UNK16									= 0x00800000, // 23
	RENDER_FLAG_WATER									= 0x01000000, // 24
	RENDER_FLAG_PARTICULATES							= 0x02000000, // 25
	RENDER_FLAG_TERRAIN_LOW_DETAIL						= 0x04000000, // 26
	RENDER_FLAG_UNK20									= 0x08000000, // 27
	RENDER_FLAG_UNK21									= 0x10000000, // 28
	RENDER_FLAG_WIREFRAME								= 0x20000000, // 29
	RENDER_FLAG_WMO_NORMALS								= 0x40000000, // 30
	RENDER_FLAG_UNK22									= 0x80000000, // 31
};

// Player flags
enum PlayerFlags
{
	PLAYER_FLAG_GROUP_LEADER							= 0x00000001, // 00 
	PLAYER_FLAG_AFK										= 0x00000002, // 01 
	PLAYER_FLAG_DND										= 0x00000004, // 02 
	PLAYER_FLAG_GM										= 0x00000008, // 03 
	PLAYER_FLAG_GHOST									= 0x00000010, // 04 
	PLAYER_FLAG_RESTING									= 0x00000020, // 05 
	PLAYER_FLAG_HIDE_HELM								= 0x00000400, // 10 
	PLAYER_FLAG_HIDE_CLOAK								= 0x00000800, // 11 
	PLAYER_FLAG_SANCTUARY								= 0x00010000, // 16 
	PLAYER_FLAG_TAXI_TIME_TEST							= 0x00020000, // 17 
	PLAYER_FLAG_PVP_TIMER								= 0x00040000, // 18 
	PLAYER_FLAG_COMMENTATOR								= 0x00080000, // 19 
	PLAYER_FLAG_CAN_USE_COMMENTATOR_COMMANDS			= 0x00400000, // 22 
};

// Player State
enum PlayerState
{
	PLAYER_STATE_TAXI_TIME_TEST							= 0x00100000, // 20
	PLAYER_STATE_MOUNTED								= 0x08000000, // 27
};

// Movement State
enum MovementState
{
	MOVEMENT_STATE_MOVE_FORWARD							= 0x00000100, // 08
	MOVEMENT_STATE_MOVE_BACKWARD						= 0x00000200, // 09
	MOVEMENT_STATE_MOVE_LEFT							= 0x00000400, // 10
	MOVEMENT_STATE_MOVE_RIGHT							= 0x00000800, // 11
	MOVEMENT_STATE_YAW_LEFT								= 0x00001000, // 12
	MOVEMENT_STATE_YAW_RIGHT							= 0x00002000, // 13
	MOVEMENT_STATE_PITCH_UP								= 0x00004000, // 14
	MOVEMENT_STATE_PITCH_DOWN							= 0x00008000, // 15
	MOVEMENT_STATE_WALK									= 0x00010000, // 16
	MOVEMENT_STATE_UNK									= 0x00020000, // 17
	MOVEMENT_STATE_FLYING								= 0x00040000, // 18
	MOVEMENT_STATE_DEAD									= 0x00080000, // 19
	MOVEMENT_STATE_IN_THE_AIR							= 0x00100000, // 20
	MOVEMENT_STATE_FALLING								= 0x00200000, // 21
	MOVEMENT_STATE_REBOUND_IN_AIR						= 0x00400000, // 22
	MOVEMENT_STATE_REBOUND_LANDING						= 0x00800000, // 23
	MOVEMENT_STATE_AUTO_MOVE_FORWARD					= 0x01000000, // 24
	MOVEMENT_STATE_AUTO_MOVE_BACKWARD					= 0x02000000, // 25
	MOVEMENT_STATE_AUTO_MOVE_LEFT						= 0x04000000, // 26
	MOVEMENT_STATE_AUTO_MOVE_RIGHT						= 0x08000000, // 27
	MOVEMENT_STATE_CANNOT_MOVE							= 0x10000000, // 28
	MOVEMENT_STATE_SWIMMING								= 0x20000000, // 29
	MOVEMENT_STATE_FLYING_UP							= 0x40000000, // 30
	MOVEMENT_STATE_SWIMMING_DOWN						= 0x80000000, // 31
};

// Movement Type
enum MovementType
{
	MOVEMENT_TYPE_ABLE_TO_FLY							= 0x00000001, // 00
	MOVEMENT_TYPE_FLYING								= 0x00000002, // 01
	MOVEMENT_TYPE_SKIMMING_OBJECT						= 0x00000004, // 02
	MOVEMENT_TYPE_QUEUE_MOVEMENT						= 0x00000008, // 03
	MOVEMENT_TYPE_WATERWALK								= 0x00000010, // 04
	MOVEMENT_TYPE_HOVER									= 0x00000040, // 05
	MOVEMENT_TYPE_NORMAL								= 0x00000080, // 06
};
