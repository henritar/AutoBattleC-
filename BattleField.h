#pragma once
#include "Character.h"
#include "Types.h"
#include <list>
#include <iostream>
#include "Grid.h"
//Added library so shared_prt could be used.
#include <memory>
using namespace std;
class BattleField
{
public:

	BattleField();

	Grid* grid;
	Types::GridBox* PlayerCurrentLocation;
	Types::GridBox* EnemyCurrentLocation;
	list<Character>* AllPlayers;
	shared_ptr<Character> PlayerCharacter;
	//Character* PlayerCharacter;
	//Removed pointer declaration (*).
	shared_ptr<Character> EnemyCharacter;
	int currentTurn;
	int numberOfPossibleTiles;


	void Setup();

	void GetPlayerChoice();

	void CreatePlayerCharacter(int classIndex);

	void CreateEnemyCharacter();

	void StartGame();

	void StartTurn();

	void HandleTurn();

	int GetRandomInt(int min, int max);

	void AlocatePlayers();

	void AlocatePlayerCharacter();

	void AlocateEnemyCharacter();
};


