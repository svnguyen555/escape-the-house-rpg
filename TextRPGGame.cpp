// Source File Header
// final.cpp
// Sang Nguyen CISP 360
// July 29, 2022
#include <iostream>
#include <string>
#include <cstdlib>//Used to rng encounters and damage calculations
#include <ctime>
using namespace std;

struct room//Creates the rooms
{
    string name;
    string description;
    int id;
    bool occupied;//If room is occupied by a monster or not
    int e;//Id of the room room north of the current room
    int n;//Id of the room room east of the current room
    int w;//Id of the room room west of the current room
    int s;//Id of the room room south of the current room
    bool visited;

    //Room Map (Where 1 is the center and starting position of the room)
    //       3
    // 2     1       4      6(Secret Room)
    //       5
};


// Specification A1 - Put your monsters in a Monster() class
class monster//Creates a monster
{
public:
    string name;
    string image;
    float hp;
    float attack;
};



class inventory//Creates all of the items
{
public:
    string name;
    string description;
    bool obtained;
};



class player//Player stats
{
public:
    string name;
    float armor;
    float hp;
    float punch;
    float sword;
};


//Function Prototypes
void programGreeting();
void overWorld(room, room, room, room, room, room, monster enemy[], inventory item[], player);
int callCenterRoom(room, inventory item[]);
int callNorthRoom(room, monster enemy[], inventory item[], player);
int callWestRoom(room, monster enemy[], inventory item[], player);
int callEastRoom(room, monster enemy[], inventory item[], player);
int callSouthRoom(room, monster enemy[], inventory item[], player);
int callSecretRoom(room, inventory item[]);
void getPlayerInput(room& room, inventory item[]);
void callMap(room& room);
void callBattle(room, monster enemy[], inventory item[], player& mc);
void battleScreen(monster enemy[], int& type, int enemyHP, player& mc);
void programEnder();






int main() {
    //Program Greeting
    programGreeting();

    //Game description
    cout << "You've found yourself imprisoned in a house ruled by an evil witch." << endl;
    cout << "There is only one way out of the house but it is locked..." << endl;
    cout << "In order to survive, you must discover the secrets that lie beyond the other rooms and fight your way outside!" << endl << endl << endl;

    //Author's Note
    cout << "[Author's Note]" << endl;
    cout << "This program accepts both lower and uppercase inputs" << endl;
    cout << "In this game, the player's HP resets after every battle." << endl;
    cout << "The Run Away option is a reset button for the game if needed." << endl;
    cout << "Do note that using it will completely reset all of your progress." << endl << endl << endl;
    //Spoilers: There is a secret room if you go east while inside the east room. This will grant you armor that'll allow you to easily beat the final boss.


    // Specification C2 - Player Name
    string name;
    cout << "Please enter your character's name: ";
    cin >> name;
    system("clear");


    //Constructs the 6 rooms of the game 
    //Name, Description, Room ID, Exit ID Codes, If occupied by monster encounter or not

    // Specification C1 - Five Rooms
    room centerRoom = { "[Center Room]", "This is the center room", 1, false, 4, 3, 2, 5, false };//Room id 1
    room westRoom = { "[West Room]", "This is the west room. Seems to be a laboratory full of magical chemicals. ", 2, true, 1, 0, 0, 0, false };//Room id 2
    room northRoom = { "[North Room]", "This is the north room. Seems to be an armory room full of weapons.", 3, true, 0, 0 , 0, 1, false };//Room id 3
    room eastRoom = { "[East Room]", "This is the east room. This room is mostly empty besides a suspicious empty bookshelf on the East side of the room...", 4, true, 6, 0, 1, 0, false };//Room id 4
    room southRoom = { "[South Room]", "This is the south room which leads to the exist.", 5, true, 0, 0, 0, 1, false };//Room id 5

    // Specification A2 - Add more rooms
    room secretRoom = { "[Secret Room]", "This must be a secret room! It's not shown on the map!", 6, false, 0, 0, 4, 0, false };//Room id 6



    //These are the monsters of the game
    //Name, Battle Portrait, HP Value, Attack Value
    monster catBeast = { "[Cat Beast]", "≧◉ᴥ◉≦", 30, 5 };
    monster manEatingBird = { "[Man Eating Bird]", "c( ¯ ਊ ¯ )つ", 50, 5 };
    monster zombies = { "[Zombies]", "(⊙.⊙(☉̃ₒ☉)⊙.⊙)", 80, 10 };
    monster bear = { "[Bear]", "ʕ•́ᴥ•̀ʔっ", 1, 1 };

    // Specification A3 - Add more monsters
    monster witch = { "[Witch]", "(∩｀-´)⊃━:｡･:*:･ﾟ’★,｡･:*:♪･ﾟ’☆", 200, 30 };//5th monster
    monster monsters[5] = { catBeast, manEatingBird, zombies, bear, witch };

    // Specification B3 - Add treasure
    inventory armor = { "[Armor]", "A magical armor that greatly increases your HP.", false };
    inventory sword = { "[Sword]", "A sword that does great damage during battle.", false };
    inventory potion = { "[Potion Flask]", "A magical bottle that can be used to completely restore your HP once during battle. Refills after a battle has ended.", false };
    inventory key = { "[South Door Key]", "A key that unlocks the south door.", false };
    inventory item[4] = { armor, sword, potion, key };


    //Player Stats
    player player;
    player.name = name;
    player.armor = 1;
    player.hp = 100 * player.armor;
    player.punch = 10;
    player.sword = 50;

    overWorld(centerRoom, westRoom, northRoom, eastRoom, secretRoom, southRoom, monsters, item, player);//Call the game

    programEnder();

    return 0;

}




//Functions

//Program Greeting
void programGreeting()
{
    cout << "Welcome to Sang's final assignment." << endl << endl;
}






//This function is used to control movement between rooms
void overWorld(room centerRoom, room westRoom, room northRoom, room eastRoom, room secretRoom, room southRoom, monster enemy[], inventory item[], player player)
{
    bool gameClear = false;
    int roomID = 1;//Start the player in the central room

    do
    {

        if (roomID == 1)//Moves player to center room
        {
            roomID = callCenterRoom(centerRoom, item);
            centerRoom.occupied = false;//Removes monster encounters after player clears a room
            centerRoom.visited = true;
        }
        if (roomID == 2)//Moves player to west room
        {
            roomID = callWestRoom(westRoom, enemy, item, player);
            westRoom.occupied = false;
            westRoom.visited = true;
        }
        if (roomID == 3)//Moves player to north room
        {
            roomID = callNorthRoom(northRoom, enemy, item, player);
            northRoom.occupied = false;
            northRoom.visited = true;
        }
        if (roomID == 4)//Moves player to east room
        {
            roomID = callEastRoom(eastRoom, enemy, item, player);
            eastRoom.occupied = false;
            eastRoom.visited = true;
        }
        if (roomID == 6)//Moves player to secret room
        {
            roomID = callSecretRoom(secretRoom, item);
            secretRoom.visited = true;
        }
        if (roomID == 5)//Moves player to south room
        {
            roomID = callSouthRoom(southRoom, enemy, item, player);
            southRoom.occupied = false;
            southRoom.visited = true;
            gameClear = true;
        }
    } while (gameClear == false);//Loops the game if South Room hasn't been cleared yet   
    cout << "Congratulations! You defeated the evil witch and cleared the game!!!" << endl;
}






//This function is all the events that occur in the center room
int callCenterRoom(room centerRoom, inventory item[])
{
    string moveTo;
    int nextRoom;

    callMap(centerRoom);

    // Specification C4 – Abbreviated Room Description
    if (centerRoom.visited == false)//Shows room description upon first time entry to room
    {
        cout << centerRoom.name << endl;
        cout << centerRoom.description << endl << endl;
    }

    getPlayerInput(centerRoom, item);//Asks player what to do inside the room
    cin >> moveTo;//Once above function is done, allow player to input where to move to

    while ((moveTo != "n") && (moveTo != "N") && (moveTo != "w") && (moveTo != "W") && (moveTo != "e") && (moveTo != "E") && (moveTo != "s") && (moveTo != "S"))//Input validation
    {
        cout << "[Error] Invalid input detected. Please enter again: ";
        cin >> moveTo;
    }

    while (((moveTo == "s") || (moveTo == "S")) && (item[3].obtained == false))//Prevent player from going to southern door without key
    {
        cout << "The door is locked." << endl;
        cout << "Please enter a different direction: ";
        cin >> moveTo;
        while ((moveTo != "n") && (moveTo != "N") && (moveTo != "w") && (moveTo != "W") && (moveTo != "e") && (moveTo != "E") && (moveTo != "s") && (moveTo != "S"))//Input validation
        {
            cout << "[Error] Invalid input detected. Please enter again: ";
            cin >> moveTo;
        }
    }

    if ((moveTo == "n") || (moveTo == "N"))//Move north
    {
        nextRoom = centerRoom.n;
    }
    else if ((moveTo == "w") || (moveTo == "W"))//Move west
    {
        nextRoom = centerRoom.w;
    }
    else if ((moveTo == "e") || (moveTo == "E"))//Move east
    {
        nextRoom = centerRoom.e;
    }
    else if ((moveTo == "s") || (moveTo == "S"))//Move south
    {
        nextRoom = centerRoom.s;
    }
    system("clear");
    return nextRoom;
}





//This function is all the events that occur in the north room
int callNorthRoom(room northRoom, monster enemy[], inventory item[], player player)
{
    string moveTo;
    int nextRoom;
    callMap(northRoom);
    if (northRoom.visited == false)
    {
        cout << northRoom.name << endl;
        cout << northRoom.description << endl << endl;
    }
    if (northRoom.occupied == true)//Activate monster encounter upon first time entry to room
    {
        callBattle(northRoom, enemy, item, player);
        cout << "You obtained a Sword!" << endl;//Give the player an item for clearing the battle
        item[1].obtained = true;//Give player Sword
        callMap(northRoom);
    }
    getPlayerInput(northRoom, item);
    cin >> moveTo;

    while ((moveTo != "s") && (moveTo != "S"))//Prevent player from going in directions that don't have exits
    {
        cout << "The only exit in this room seems to be south..." << endl;
        cout << "Please type again: ";
        cin >> moveTo;
    }

    if ((moveTo == "s") || (moveTo == "S"))
    {
        nextRoom = northRoom.s;
    }
    system("clear");
    return nextRoom;
}//The rest of the room functions below will all be very similar but with some slight variations depending on their important. 
//Any major differences will be noted.





//This function is all of the events that occur in the west room
int callWestRoom(room westRoom, monster enemy[], inventory item[], player player)
{
    string moveTo;
    int nextRoom;
    callMap(westRoom);
    if (westRoom.visited == false)
    {
        cout << westRoom.name << endl;
        cout << westRoom.description << endl << endl;
    }
    if (westRoom.occupied == true)
    {
        callBattle(westRoom, enemy, item, player);
        cout << "You obtained a Potion Flask!" << endl << endl;
        item[2].obtained = true;//Give player Potion Flash after clearing battle
        callMap(westRoom);
    }
    getPlayerInput(westRoom, item);
    cin >> moveTo;

    while ((moveTo != "e") && (moveTo != "E"))
    {
        cout << "The only exit in this room seems to be east..." << endl;
        cout << "Please type again: ";
        cin >> moveTo;
    }

    if ((moveTo == "e") || (moveTo == "E"))
    {
        nextRoom = westRoom.e;
    }
    system("clear");
    return nextRoom;
}




//This function is all the events that occur in the east room
int callEastRoom(room eastRoom, monster enemy[], inventory item[], player player)
{
    string moveTo;
    int nextRoom;
    callMap(eastRoom);
    if (eastRoom.visited == false)
    {
        cout << eastRoom.name << endl;
        cout << eastRoom.description << endl << endl;
    }
    if (eastRoom.occupied == true)
    {
        callBattle(eastRoom, enemy, item, player);
        cout << "You obtained the South Door Key!" << endl << endl;
        item[3].obtained = true;//Give player South Door Key after clearing battle
        callMap(eastRoom);
    }

    getPlayerInput(eastRoom, item);
    cin >> moveTo;

    while ((moveTo != "w") && (moveTo != "W") && (moveTo != "e") && (moveTo != "E"))
    {
        cout << "There is nothing in this direction..." << endl;
        cout << "Please type again: ";
        cin >> moveTo;
    }

    if ((moveTo == "w") || (moveTo == "W"))
    {
        nextRoom = eastRoom.w;
    }
    else if ((moveTo == "e") || (moveTo == "E"))//This takes the player to the secret room if they input east.
    {
        nextRoom = eastRoom.e;
    }
    system("clear");
    return nextRoom;
}





//This function is all the events that occur in the south room
int callSouthRoom(room southRoom, monster enemy[], inventory item[], player player)
{
    string moveTo;
    int nextRoom;
    callMap(southRoom);
    if (southRoom.visited == false)
    {
        cout << southRoom.name << endl;
        cout << southRoom.description << endl << endl;
        southRoom.visited = true;
        cout << "You unlocked the southern door with the key!" << endl;
        cout << "You hear a voice..." << endl << endl;
        cout << "You shall not escape from my house alive!" << endl;
    }
    if (southRoom.occupied == true)
    {
        callBattle(southRoom, enemy, item, player);
    }
    nextRoom = southRoom.n;//Once this line is ran, the end of the game will initiate.
    return nextRoom;
}





//This function is all the events that occur in the secret room
int callSecretRoom(room secretRoom, inventory item[])
{
    string moveTo;
    int nextRoom;

    callMap(secretRoom);
    if (secretRoom.visited == false)
    {
        cout << secretRoom.name << endl;
        cout << secretRoom.description << endl << endl;
        cout << "You found Magical Armor!!!" << endl << endl;
        item[0].obtained = true;//Gives player the secret item, Magical Armor
    }

    getPlayerInput(secretRoom, item);
    cin >> moveTo;

    while ((moveTo != "w") && (moveTo != "W"))
    {
        cout << "There is nothing in this direction..." << endl;
        cout << "Please type again: ";
        cin >> moveTo;
    }

    if ((moveTo == "w") || (moveTo == "W"))
    {
        nextRoom = secretRoom.w;//Moves back to room id 4, which is the east room.
    }
    system("clear");
    return nextRoom;
}


//This function asks the player of what to do in a room
void getPlayerInput(room& room, inventory item[])
{
    string playerInput;

    do
    {
        cout << "What will you do?" << endl;
        cout << "Press L to Look Around" << endl;
        cout << "Press i to Check Inventory" << endl;
        cout << "Press M to move somewhere else" << endl << endl;
        cout << "Please enter here: ";
        cin.ignore();
        cin >> playerInput;
        cout << endl;

        // Specification C3 - Input Validation
        while ((playerInput != "l") && (playerInput != "L") && (playerInput != "i") && (playerInput != "I") && (playerInput != "m") && (playerInput != "M"))//Input validation
        {
            cout << "[Error] Invalid Input detected. Please enter again: ";
            cin >> playerInput;
            cout << endl;
        }

        // Specification C5 - Detailed Look
        if ((playerInput == "l") || (playerInput == "L"))//Reshows the room name and description is L is pressed
        {
            system("clear");
            callMap(room);
            cout << room.name << endl;
            cout << room.description << endl << endl;
        }

        // Specification B1 - Add more command options.
        else if ((playerInput == "i") || (playerInput == "I"))//Shows player their inventory is i is pressed
        {
            if (item[0].obtained == true)//Shows description of the armor
            {
                cout << item[0].name << endl;
                cout << item[0].description << endl << endl;
            }
            if (item[1].obtained == true)//Shows description of the sword
            {
                cout << item[1].name << endl;
                cout << item[1].description << endl << endl;
            }
            if (item[2].obtained == true)//Shows description of the potion flask
            {
                cout << item[2].name << endl;
                cout << item[2].description << endl << endl;
            }
            if (item[3].obtained == true)//Shows description of the key
            {
                cout << item[3].name << endl;
                cout << item[3].description << endl << endl;
            }
            if ((item[0].obtained == false) && (item[1].obtained == false) && (item[2].obtained == false) && (item[3].obtained == false))//Tell player they don't have any items
            {
                cout << "You don't have any items." << endl << endl;
            }
        }

        else if ((playerInput == "m") || (playerInput == "M"))//Ask player what direction to move in if m is pressed
        {
            cout << endl;
            cout << "Press N to move North" << endl;
            cout << "Press W to move West" << endl;
            cout << "Press E to move East" << endl;
            cout << "Press S to move South" << endl << endl;
            cout << "Enter here: ";//This function exits and goes back to the room function to ask for directional input
        }
    } while ((playerInput != "m") && (playerInput != "M"));//Loop this menu as long as the player hasn't decide to move yet.
}





//Shows player's current location via map
void callMap(room& room)
{
    const int size = 7;//The room locations are represented by their id. Secret room is not shown on map.
    string location[size] = { " ", " ", " ", " ", " ", " ", " " };
    location[room.id] = "X";
    cout << "       ---      " << endl;
    cout << "       |" << location[3] << "|      " << endl;
    cout << "       ---      " << endl;

    cout << "        |      " << endl;
    cout << "---    ---    ---" << endl;
    cout << "|" << location[2] << "|----|" << location[1] << "|----|" << location[4] << "|" << endl;
    cout << "---    ---    ---" << endl;
    cout << "        |      " << endl;

    cout << "       ---      " << endl;
    cout << "       |" << location[5] << "|      " << endl;
    cout << "       ---      " << endl;
}




// Specification B2 - Add combat.
void callBattle(room southRoom, monster enemy[], inventory item[], player& mc)
{
    //Battle Variables
    string input;
    unsigned seed = time(0);
    srand(seed);
    int type = rand() % 3 + 0;//Randomize monster encounter
    if (southRoom.visited == true)//Forces the southern room encounter into the final boss battle
    {
        type = 4;//This is the witch
    }
    int currentEnemyHP = enemy[type].hp;//This allows enemies to reset their HPs if encountered again
    if (item[0].obtained == true)//Triple player's HP if secret item obtained
    {
        mc.hp = mc.hp * 10;
    }
    int playerCommand;

    //Battle Begins
    cout << "You encountered " << enemy[type].name << "!" << endl;
    battleScreen(enemy, type, currentEnemyHP, mc);//Show battle screen

    do
    {
        //Player's turn
        cout << "What will you do? " << endl;
        cout << "Press 1 for Punch" << endl;
        cout << "Press 2 for Run" << endl;
        if (item[1].obtained == true)//Show player option to use Sword if in inventory
        {
            cout << "Press 3 for Sword" << endl;
        }
        if (item[2].obtained == true)//Show player option to use Potion if in inventory
        {
            cout << "Press 4 for Potion" << endl;
        }
        cout << "Enter here: ";//Ask for battle input
        cin >> playerCommand;

        while ((playerCommand != 1) && (playerCommand != 2) && (playerCommand != 3) && (playerCommand != 4) || (((playerCommand == 3) && (item[1].obtained == false)) || ((playerCommand == 4) && (item[2].obtained == false))))//Input Validation
        {
            cout << "[Error] Invalid Input Detected. Please enter again: ";
            cin >> playerCommand;
        }
        system("clear");

        if (playerCommand == 1)//Use punch attack
        {
            int damageInflicted = (mc.punch) + (rand() % 10 + 1);//Calculate damage. All attacks in the game have slight damage variations
            currentEnemyHP = currentEnemyHP - damageInflicted;//Reduce enemy HP
            cout << "The enemy took " << damageInflicted << " damage!" << endl << endl;
        }
        else if (playerCommand == 2)//Run away command but in this game it is used to reset the game (basically the same as losing a battle)
        {
            system("clear");
            cout << "You ran away but get exhausted from running!" << endl;
            cout << "----------------------------------------------------------" << endl;
            mc.hp = 0;//This forces game to reset as if it were a game over.
        }
        else if ((playerCommand == 3) && (item[1].obtained == true))//Use sword attack
        {
            int damageInflicted = (mc.sword) + (rand() % 20 + 1);
            currentEnemyHP = currentEnemyHP - damageInflicted;
            cout << "You slashed the enemy with your sword!" << endl;
            cout << "The enemy took " << damageInflicted << " damage!" << endl;
        }
        else if ((playerCommand == 4) && (item[2].obtained == true))//Heal the player
        {
            mc.hp = 100;
            cout << "You fully restored your HP!" << endl;
            cout << "The potion was used up!" << endl;
            item[2].obtained = false;//Remove the ability to use the option again after using it
        }


        //Enemy's turn
        if ((currentEnemyHP > 0) && (mc.hp > 0))//Proceed to enemy's turn if they are still alive
        {
            cout << "The " << enemy[type].name << " attacked!" << endl;
            int damageTaken = (enemy[type].attack) + (rand() % 10 + 1);//Calc enemy's attack
            mc.hp = mc.hp - damageTaken;//Reduce player's hp
            cout << "You just took " << damageTaken << " damage!" << endl;
            battleScreen(enemy, type, currentEnemyHP, mc);//Update the battle screen
        }
    } while ((mc.hp > 0) && (currentEnemyHP > 0));//Loop the battle if both combatants are still alive
    if (currentEnemyHP <= 0)//Show the player won the battle
    {
        cout << "You won the battle!" << endl;
        cout << "----------------------------------------------------------" << endl;
    }
    else if (mc.hp <= 0)//Show the player lost the battle and reset the game
    {
        cout << "You blacked out!" << endl;
        cout << "You've woken back up in the center room with your memories gone!" << endl;
        cout << "----------------------------------------------------------" << endl;
        main();//Restart game
    }
}





//Shows the battle screen
void battleScreen(monster enemy[], int& type, int enemyHP, player& mc)
{
    cout << "----------------------------------------------------------" << endl;
    cout << enemy[type].name << " HP: " << enemyHP << endl << endl << endl;
    cout << "          " << enemy[type].image << endl << endl << endl;
    cout << mc.name << " HP: " << mc.hp << endl;
    cout << "----------------------------------------------------------" << endl;
}




//Program Ender
void programEnder()
{
    cout << endl;
    cout << "You have reached the end of this assignment. Goodbye.";
    int a;
    cin >> a;
}




//Program Output
//This is an example of what combat looks like

//       ---      
//       |X|      
//       ---      
//        |      
//---    ---    ---
//| |----| |----| |
//---    ---    ---
//        |      
//       ---      
//       | |      
//       ---      
//[North Room]
//This is the north room. Seems to be an armory room full of weapons.

//You encountered [Zombies]!
//----------------------------------------------------------
//[Zombies] HP: 80
//
//
//          (⊙.⊙(☉̃ₒ☉)⊙.⊙)
//
//
//SANG HP: 100
//----------------------------------------------------------
//What will you do? 
//Press 1 for Punch
//Press 2 for Run
//Enter here: 