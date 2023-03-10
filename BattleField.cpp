#include "Grid.h"
#include "BattleField.h"
#include "Types.h"
#include "Character.h"
#include <iostream>
#include "BattleField.h"
#include <list>
#include <string>
#include <cstdlib>

using namespace std;

BattleField::BattleField() {
    
    grid = new Grid(5, 5);
    AllPlayers = new list<Character>();
    int currentTurn = 0;
    int numberOfPossibleTiles = grid->grids.size();
    Setup();
}

void BattleField::Setup()
{
  
   
    GetPlayerChoice();
}

void BattleField::GetPlayerChoice()
{
    //asks for the player to choose between for possible classes via console.
    printf("Choose Between One of this Classes:\n");

    printf("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer\n");
    //store the player choice in a variable
    int choice;

    cin >> choice;

    // changed useless Switch statement to if statement
    if (choice > 0 && choice < 5)
    {
    	CreatePlayerCharacter(choice);
    }
    else
    {
    	GetPlayerChoice();
    }
}

void BattleField::CreatePlayerCharacter(int classIndex)
{

	//removed pointer
	Types::CharacterClass characterClass = (Types::CharacterClass)classIndex;
    cout << "Player Class Choice: " << characterClass << endl;
    
    PlayerCharacter = std::make_shared<Character>(characterClass);
    
    PlayerCharacter->Health = 100;
    PlayerCharacter->BaseDamage = 20;
    PlayerCharacter->PlayerIndex = 0;

    CreateEnemyCharacter();

}

void BattleField::CreateEnemyCharacter()
{
    //randomly choose the enemy class and set up vital variables
    
    int randomInteger = GetRandomInt(1, 4);
    Types::CharacterClass enemyClass = (Types::CharacterClass)randomInteger;
    cout << "Enemy Class Choice: " << enemyClass << endl << endl;
    //corrected the Enemycharacter type
    EnemyCharacter = std::make_shared<Character>(enemyClass);
    EnemyCharacter->Health = 100;
    PlayerCharacter->BaseDamage = 20;
    PlayerCharacter->PlayerIndex = 1;
    StartGame();

}


//corrected attribuition and creating a new aux variable so
//the value will not be lost when updating turn player.
void BattleField::StartGame()
{
    //populates the character variables and targets
	Character* auxCharacter = EnemyCharacter->target;
    EnemyCharacter->target = PlayerCharacter->target;
    PlayerCharacter->target = auxCharacter;
    AllPlayers->push_back(*PlayerCharacter);
    AllPlayers->push_back(*EnemyCharacter);
    AlocatePlayers();
    StartTurn();

}

void BattleField::StartTurn() {

    if (currentTurn == 0)
    {
        //AllPlayers.Sort();  
    }
    std::list<Character>::iterator it;

    for (it = AllPlayers->begin(); it != AllPlayers->end(); ++it) {
        it->StartTurn(grid);
    }

    currentTurn++;
    HandleTurn();
}

void BattleField::HandleTurn()
{
    if (PlayerCharacter->Health == 0)
    {
        return;
    }
    else if (EnemyCharacter->Health == 0)
    {
        printf("\n");

        // endgame?

        printf("\n");

        return;
    }
    else
    {
    	std::string alpha;
        printf("\n");
        printf("Click on any key to start the next turn...\n");

    	//Added a getline to wait for user input
        std::getline(std::cin, alpha);

        printf("\n");

        //TODO
        //ConsoleKeyInfo key = Console.ReadKey();
        StartTurn();
    }
}

int BattleField::GetRandomInt(int min, int max)
{
	srand((unsigned) time(NULL));

    int index = rand() % max + min;
    return index;
}

void BattleField::AlocatePlayers()
{
    AlocatePlayerCharacter();

}

void BattleField::AlocatePlayerCharacter()
{
    int random = 0;
    auto l_front = grid->grids.begin();
    advance(l_front, random);
    Types::GridBox* RandomLocation = &*l_front;

    if (!RandomLocation->ocupied)
    {
        //Types::GridBox* PlayerCurrentLocation = RandomLocation;
        PlayerCurrentLocation = &*l_front;
        l_front->ocupied = true;
        PlayerCharacter->currentBox = *l_front;
        AlocateEnemyCharacter();
    }
    else
    {
        AlocatePlayerCharacter();
    }
}

void BattleField::AlocateEnemyCharacter()
{
    
    int random = 24;
    auto l_front = grid->grids.begin();
    advance(l_front, random);
    Types::GridBox* RandomLocation = &*l_front;
    
    if (!RandomLocation->ocupied)
    {
        EnemyCurrentLocation = &*l_front;
        l_front->ocupied = true;
        EnemyCharacter->currentBox = *l_front;
        grid->drawBattlefield(5, 5);
    }
    else
    {
        AlocateEnemyCharacter();
    }


}
