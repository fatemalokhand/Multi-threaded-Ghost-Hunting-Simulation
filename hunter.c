#include "defs.h"

/*Function: initHunter()
  Purpose:  initializing the hunter
       in:  HunterType* hunterType, char* name, char* nickName, RoomType* startRoom, EvidenceClassType evidenceClass, int arrayIndex, unsigned int seed, GhostType* ghostType
*/
void initHunter(HunterType* hunterType, char* name, char* nickName, RoomType* startRoom, EvidenceClassType evidenceClass, int arrayIndex, unsigned int seed, GhostType* ghostType)
{
  hunterType->currentRoom = startRoom;
  hunterType->currentRoom->hunters[arrayIndex] = hunterType;
  strcpy(hunterType->name, name);
  strcpy(hunterType->nickName, nickName);
  initEvidenceList(&(hunterType->evidenceList));
  hunterType->evidenceClassType = evidenceClass;
  hunterType->fear = 0;
  hunterType->boredom = BOREDOM;
  hunterType->arrayIndex = arrayIndex;
  hunterType->seed = seed;
  hunterType->ghost = ghostType;
  hunterType->ghostlyEvidenceCount = 0;
}

/*Function: printHunter()
  Purpose:  printing out a single Hunter
       in:  HunterType* hunterType
*/
void printHunter(HunterType* hunterType)
{
  printf("Hunter (Name:%s, NickName:%s, CurrentRoom:%s, EvidenceClassType:%d, Fear:%d, ArrayIndex:%d)", hunterType->name, hunterType->nickName, hunterType->currentRoom->name, hunterType->evidenceClassType, hunterType->fear, hunterType->arrayIndex);
}

void moveHunter(HunterType* hunterType)
{
  // the room that the hunters are leaving from 
  hunterType->currentRoom->hunters[hunterType->arrayIndex] = NULL;

  //collecting the evidence
  getNewRoom(&(hunterType->currentRoom));

  // the new room that the hunters are currently in
  hunterType->currentRoom->hunters[hunterType->arrayIndex] = hunterType;
}

/*Function: collectEvidence()
  Purpose:  collecting the Evidence
       in:  pointer to the hunter
*/
void collectEvidence(HunterType* hunterType)
{
  int found = 0;

  if(hunterType->currentRoom->evidenceList.headNode != NULL)
  {
    EvidenceNodeType* currentEvidenceNode;
    currentEvidenceNode = hunterType->currentRoom->evidenceList.headNode;

    while(currentEvidenceNode != NULL)
    {
        if(currentEvidenceNode->data->evidenceClassType == hunterType->evidenceClassType)
        {
            addEvidence(&(hunterType->evidenceList), currentEvidenceNode->data);

            if(currentEvidenceNode->data->isGhostly == 1){
              hunterType->ghostlyEvidenceCount++;
            }

            deleteEvidence(&(hunterType->currentRoom->evidenceList), currentEvidenceNode->data);
        }

        if(currentEvidenceNode->nextNode != NULL)
        {
          currentEvidenceNode = currentEvidenceNode->nextNode;
        }
        else
        {
          currentEvidenceNode = NULL;
        }
    }
  }
}

/*Function: communicateEvidence()
  Purpose:  hunters communicating about the collected Evidence
       in:  pointer to the hunter
*/
void communicateEvidence(HunterType* hunterType)
{
  printf("< CommunicateEvidence >");
}

/*Function: hunterAction()
  Purpose:  randomly choose an action for the hunter to take
       in:  pointer to the hunter
*/
void hunterAction(HunterType* hunterType)
{
  hunterType->boredom =  hunterType->boredom - 1;


  // When the hunter is in a room with the ghost
  if(doesRoomContainGhost(hunterType->currentRoom) == 1)
  {
    hunterType->fear = hunterType->fear + FEAR;
    hunterType->boredom = BOREDOM;
  }


  int actionRangeMax = 1;
  if(getNumberOfHuntersInRoom(hunterType->currentRoom) > 1){ actionRangeMax = 2; }
  int randomActionInt = (rand() % actionRangeMax);
  
  switch(randomActionInt)
  {
    //Move to a different room
    case 0:
      moveHunter(hunterType);
      break;
    //Collect evidence
    case 1:
      collectEvidence(hunterType);
      break;
    //Communicate evidence
    case 2:
        printf("hunters communitcate\n");
        communicate(hunterType);
        break;
  }

  if(hunterType->ghostlyEvidenceCount >= 3){
    hunterType->ghost->busted = 1;
  }

}

void communicate(HunterType *hunterType){

  for(int i=0; i<4; i++){

    if(hunterType->currentRoom->hunters[i] != NULL && hunterType->currentRoom->hunters[i]->evidenceList.headNode != NULL){
      addEvidence(&(hunterType->evidenceList), hunterType->currentRoom->hunters[i]->evidenceList.headNode->data);
    }
  }
}
