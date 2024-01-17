#include "defs.h"

/*Function: initGhost()
  Purpose:  initiliazes the ghost
       in:  GhostType* ghostType, RoomType* startRoom, unsigned int seed
*/
void initGhost(GhostType* ghostType, RoomType* startRoom, unsigned int seed)
{
  ghostType->currentRoom = startRoom;
  ghostType->currentRoom->ghost = ghostType;
  int random = randInt(0,3);
  switch(random)
  {
    case 0:
      ghostType->class = 0;
      break;
    
    case 1:
      ghostType->class = 1;
      break;

    case 2:
      ghostType->class = 2;
      break;

    case 3:
      ghostType->class = 3;
      break;
  }
  ghostType->boredom = BOREDOM;
  ghostType->seed = seed;
}


/*Function: moveGhost()
  Purpose:  moves the Ghost to other room
       in:  GhostType* ghostType
*/
void moveGhost(GhostType* ghostType)
{
  // the room that the ghost left from
  ghostType->currentRoom->ghost = NULL;

  // printing out the ghost's movement
  printf("Ghost Movement: %s ~~~~>", ghostType->currentRoom->name);

 
  getNewRoom(&(ghostType->currentRoom));
  printf(" %s \n", ghostType->currentRoom->name);

  // the new room that the ghost is now in
  ghostType->currentRoom->ghost = ghostType;
}

/*Function: printGhost()
  Purpose:  printing out the ghost
       in:  GhostType* ghostType
*/
void printGhost(GhostType* ghostType)
{

  //ghostEnumTypeString code
  char ghostClassTypeString[MAX_STR];
  strcpy(ghostClassTypeString, "");
  switch(ghostType->class)
  {
      // getting the type of the ghost as a string
      case 0:
          strcpy(ghostClassTypeString, "POLTERGEIST");
       break;
      case 1:
          strcpy(ghostClassTypeString, "BANSHEE");
        break;
      case 2:
          strcpy(ghostClassTypeString, "BULLIES");
        break;
      case 3:
          strcpy(ghostClassTypeString, "PHANTOM");
        break;
  }

  // printing out the details of the ghost
  printf("Ghost (Room:%s, Class:%s, Boredom:%d)\n", ghostType->currentRoom->name, ghostClassTypeString, ghostType->boredom);
}

/*Function: ghostAction()
  Purpose:  randomly choose an action for the ghost to perform
       in:  GhostType* ghostType, unsigned int seed
*/
void ghostAction(GhostType* ghostType, unsigned int seed){
  int hunterInRoom = 0;
  int random;
    
    // checking if the hunter is in the room
    if(hunterInRoom == 0){

      random = randInt(0,3);

      switch(random){
        // move to a connected room
        case 0:
          moveGhost(ghostType);
          break;
        // leave behind evidence
        case 1:
          EvidenceType *evidence = calloc(1, sizeof(EvidenceType));
          initEvidence(evidence, randInt(0,3));
          addEvidence(&(ghostType->currentRoom->evidenceList), evidence);
          printEvidenceList(&(ghostType->currentRoom->evidenceList));
          break;
        default:
          printf("ghost decided to take no action\n");
          break;
      }
      
      // decreasing the ghost's boredom
      ghostType->boredom--;
      
    }
    else{
      random = rand() % (3 - 0) + 0;

      switch(random)
      {
      // leaving behind evidence
      case 0:
        EvidenceType *evidence = calloc(1, sizeof(EvidenceType));
        initEvidence(evidence, randInt(0,3));
        addEvidence(&(ghostType->currentRoom->evidenceList), evidence);
        printEvidenceList(&(ghostType->currentRoom->evidenceList));
        break;
      default:
        printf("ghost decided to take no action\n");
        break;
      }

      // updating the ghost's boredom
      ghostType->boredom = BOREDOM;
    }

}

/*Function: getRandomStartingRoom()
  Purpose:  generating random starting room for the ghost
       in:  unsigned int seed, BuildingType *building
*/
RoomType* getRandomStartingRoom(unsigned int seed, BuildingType *building)
{
  srand(seed);
  int newRoomInt = (rand() % 12) + 1;

  RoomNodeType *thisRoomNode;
  thisRoomNode = building->rooms.headNode;

  for(int i=0; i<newRoomInt; i++)
  {
    thisRoomNode = thisRoomNode->nextNode;
  }

  return thisRoomNode->room;
}

GhostClassType randomGhost(){

}
