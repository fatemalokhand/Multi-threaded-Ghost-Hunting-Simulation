#include "defs.h"

/*Function: initGhost()
  Purpose:  initGhost
       in:  GhostType * p_ghostType, RoomType * p_startRoom, unsigned int seed
*/
void initGhost(GhostType * p_ghostType, RoomType * p_startRoom, unsigned int seed)
{
  p_ghostType->p_currentRoom = p_startRoom;
  p_ghostType->p_currentRoom->p_ghost = p_ghostType;
  int random = randInt(0,3);
  switch (random)
  {
    case 0:
      p_ghostType->class = 0;
      break;
    
    case 1:
      p_ghostType->class = 1;
      break;

    case 2:
      p_ghostType->class = 2;
      break;

    case 3:
      p_ghostType->class = 3;
      break;
  }
  p_ghostType->boredom = BOREDOM_MAX;
  p_ghostType->seed = seed;
}


/*Function: moveGhost()
  Purpose:  moveGhost to other room
       in:  GhostType * p_ghostType
*/
void moveGhost(GhostType * p_ghostType)
{
  p_ghostType->p_currentRoom->p_ghost = NULL;//tell the ghosts current room we are leaving


  printf("GhostMovment: %s ~~~~>", p_ghostType->p_currentRoom->name);

  //drop evidence


  getNewRoom(&(p_ghostType->p_currentRoom));


  printf(" %s \n", p_ghostType->p_currentRoom->name);


  p_ghostType->p_currentRoom->p_ghost = p_ghostType;//tell the ghosts new room we are now here
}

/*Function: printGhost()
  Purpose:  printGhost
       in:  GhostType * p_ghostType
*/
void printGhost(GhostType * p_ghostType)
{

  //ghostEnumTypeString code
  char ghostClassTypeString[MAX_STR];
  strcpy(ghostClassTypeString, "");
  switch (p_ghostType->class)
  {
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

  printf("Ghost(Room:%s, Class:%s, Boredom:%d)\n", p_ghostType->p_currentRoom->name, ghostClassTypeString, p_ghostType->boredom);
}

/*Function: ghostAction()
  Purpose:  randomly choose with ghost action
       in:  GhostType * p_ghostType, unsigned int seed
*/
void ghostAction(GhostType * p_ghostType, unsigned int seed){
  //srand(seed);
  int hunterIn = 0;
  int random;

    if(hunterIn == 0){

      random = randInt(0,3);

      switch (random){
        //move to next room
        case 0:
          moveGhost(p_ghostType);
          //printGhost(p_ghostType);
          break;
        //leave evidence
        case 1:
          //printf("seed is %d\n", seed);
          printf("ghost dropped evidence\n");
          EvidenceType *p_testEvidence = calloc(1, sizeof(EvidenceType));
          initEvidence(p_testEvidence, randInt(0,3));
          appendEvidence(&(p_ghostType->p_currentRoom->evidenceList),p_testEvidence);
          printEvidenceList(&(p_ghostType->p_currentRoom->evidenceList));
          break;
        default:
          printf("ghost decide to take no action\n");
          break;
      }

      p_ghostType->boredom--;
    }else{
      //if yes hunter ghost leave evidence/take no action
      random = rand() % (3 - 0) + 0;
      //random = roundf(seed*1);

      switch (random)
      {
      case 0:
        EvidenceType *p_testEvidence = calloc(1, sizeof(EvidenceType));
        initEvidence(p_testEvidence, randInt(0,3));
        appendEvidence(&(p_ghostType->p_currentRoom->evidenceList),p_testEvidence);
        printEvidenceList(&(p_ghostType->p_currentRoom->evidenceList));
        break;

      default:
        printf("ghost decide to take no action\n");
        break;
      }

      p_ghostType->boredom = BOREDOM_MAX;
    }

}

/*Function: getRandomStartingRoom()
  Purpose:  generate random starting room
       in:  unsigned int seed, BuildingType *p_buildingType
*/
RoomType * getRandomStartingRoom(unsigned int seed, BuildingType *p_buildingType)
{
  srand(seed);
  int newRoomInt = (rand() % 12) + 1;

  RoomNodeType *p_thisRoomNode;
  p_thisRoomNode = p_buildingType->rooms.p_headNode;

  for(int i = 0; i < newRoomInt; i++)
  {
    p_thisRoomNode = p_thisRoomNode->p_nextNode;
  }

  return p_thisRoomNode->room;
}

GhostClassType randomGhost(){

}
