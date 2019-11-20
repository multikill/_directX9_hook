#pragma once
#include "Vector.hpp"
// Generated using ReClass 2016

class Resource;
class Player;
class GameObject;
class GameObjectData;
class GraphicObject;
class GameObjectElement;
class start;
class GameScreen;
class VictoryConditions;
class PointerList;
class PlayerData;
class Map;
class World;
class MainView;
class TerrainRenderer;

class Resource
{
public:
	float food; //0x0000 
	float wood; //0x0004 
	float stone; //0x0008 
	float gold; //0x000C 
	float popSpaceLeft; //0x0010 
	char pad_0x0014[0x4]; //0x0014
	float age; //0x0018 
	char pad_0x001C[0x10]; //0x001C
	float currentPop; //0x002C 
	char pad_0x0030[0x64]; //0x0030
	float biggestPopulation; //0x0094 
	char pad_0x0098[0x1F8]; //0x0098
	float N00000BB9; //0x0290 
	float N00000C22; //0x0294 
	float collectFood; //0x0298 
	float collectedWood; //0x029C 
	float collectedStone; //0x02A0 
	float collectedGold; //0x02A4 
	char pad_0x02A8[0xC8]; //0x02A8
	float N00000BD5; //0x0370 
	float N00000C06; //0x0374 
	float N00000BD6; //0x0378 
	float N00000C08; //0x037C 
	float goldAmount; //0x0380 
	float stoneAmount; //0x0384 
	float huntingAmount; //0x0388 
	float woodAmount; //0x038C 
	float N00000BD9; //0x0390 
	float N00000C0E; //0x0394 
	float N00000BDA; //0x0398 
	float N00000C10; //0x039C 
	float N00000BDB; //0x03A0 
	char pad_0x03A4[0x11C]; //0x03A4

}; //Size=0x04C0

class Player
{
public:
	char pad_0x0000[0x40]; //0x0000
	VictoryConditions* pVictoryConditions; //0x0040 
	PointerList* pPointerList; //0x0048 
	char pad_0x0050[0x8]; //0x0050
	PlayerData* pPlayerData; //0x0058 
	char pad_0x0060[0x8]; //0x0060
	Resource* pResource; //0x0068 
	char pad_0x0070[0x100]; //0x0070
	float camX; //0x0170 
	float camY; //0x0174 
	char pad_0x0178[0x60]; //0x0178
	GameObject* pLastSelectedObject; //0x01D8 
	GameObjectElement arrSelectedGameObject[60]; //0x01E0 
	char pad_0x03C0[0x4]; //0x03C0
	__int32 selectedUnitCount; //0x03C4 
	char pad_0x03C8[0x5C0]; //0x03C8

}; //Size=0x0988

class GameObject
{
public:
	char pad_0x0000[0x8]; //0x0000
	__int32 networkID; //0x0008 
	char pad_0x000C[0x4]; //0x000C
	GameObjectData* pGameObjectData; //0x0010 
	Player* pOwner; //0x0018 
	GraphicObject* pGraphicObject; //0x0020 
	char pad_0x0028[0x68]; //0x0028
	float health; //0x0090 
	__int16 N000005AA; //0x0094 
	__int16 isSelected; //0x0096 
	Vector3 coords; //0x0098 
	float resourceCarryingCount; //0x00A4 
	char pad_0x00A8[0x60]; //0x00A8

}; //Size=0x0108

class GameObjectData
{
public:
	char pad_0x0000[0x18]; //0x0000
	__int16 ID; //0x0018 
	__int16 CopyID; //0x001A 
	__int16 BaseID; //0x001C 
	__int16 N000007E3; //0x001E 
	GraphicObject* pStandingGraphic; //0x0020 
	char pad_0x0028[0x8]; //0x0028
	GraphicObject* pDeathGraphic; //0x0030 
	char pad_0x0038[0x8]; //0x0038
	__int16 N00000662; //0x0040 
	__int16 health; //0x0042 
	__int16 N000007F8; //0x0044 
	char pad_0x0046[0x132]; //0x0046
	char* pName; //0x0178 
	char pad_0x0180[0x20]; //0x0180
	GraphicObject* pGraphicWalk; //0x01A0 
	char pad_0x01A8[0x88]; //0x01A8
	GraphicObject* pGraphicAttack; //0x0230 
	__int16 N00000868; //0x0238 
	__int16 bonusAttack; //0x023A 
	char pad_0x023C[0x34C]; //0x023C

}; //Size=0x0588

class GraphicObject
{
public:
	char pad_0x0000[0x20]; //0x0000
	char* pDisplayName; //0x0020 
	char pad_0x0028[0x10]; //0x0028
	char* pFileName; //0x0038 
	char pad_0x0040[0x90]; //0x0040

}; //Size=0x00D0

class GameObjectElement
{
public:
	GameObject* pGameObject; //0x0000 

}; //Size=0x0008

class start
{
public:
	GameScreen* pGameScreen; //0x0000 
	char pad_0x0008[0x18]; //0x0008

}; //Size=0x0020

class GameScreen
{
public:
	char pad_0x0000[0x1F0]; //0x0000
	MainView* pMainView; //0x01F0 
	MainView* pMainView2; //0x01F8 
	char pad_0x0200[0x248]; //0x0200

}; //Size=0x0448

class VictoryConditions
{
public:
	char pad_0x0000[0x408]; //0x0000

}; //Size=0x0408

class PointerList
{
public:
	World* pWorld; //0x0000 
	Player* pCurrentPlayer; //0x0008 
	Map* pMap; //0x0010 
	char pad_0x0018[0x470]; //0x0018

}; //Size=0x0488

class PlayerData
{
public:
	Player* pCurrentPlayer; //0x0000 
	char pad_0x0008[0x20]; //0x0008

}; //Size=0x0028

class Map
{
public:
	char pad_0x0000[0x90]; //0x0000

}; //Size=0x0090

class World
{
public:
	char pad_0x0000[0x488]; //0x0000

}; //Size=0x0488

class MainView
{
public:
	char pad_0x0000[0x208]; //0x0000
	TerrainRenderer* pTerrainRenderer; //0x0208 
	World* pWorld; //0x0210 
	Player* pPlayer; //0x0218 
	Map* pMap; //0x0220 
	char pad_0x0228[0x8]; //0x0228

}; //Size=0x0230

class TerrainRenderer
{
public:
	char pad_0x0000[0x48]; //0x0000

}; //Size=0x0048

