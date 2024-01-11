#include "defs.h"

/*Function: initHunter()
  Purpose:  initHunter
       in:  HunterType * p_hunterType, char * p_name, char * p_nickName, RoomType * p_startRoom, EvidenceClassType evidenceClass, int arrayIndex, unsigned int seed, GhostType* p_ghostType
*/
void initHunter(HunterType * p_hunterType, char * p_name, char * p_nickName, RoomType * p_startRoom, EvidenceClassType evidenceClass, int arrayIndex, unsigned int seed, GhostType* p_ghostType)
{
  p_hunterType->p_currentRoom = p_startRoom;
  p_hunterType->p_currentRoom->hunters[arrayIndex] = p_hunterType;
  strcpy(p_hunterType->name, p_name);
  strcpy(p_hunterType->nickName, p_nickName);
  initEvidenceList(&(p_hunterType->evidenceList));
  p_hunterType->evidenceClassType = evidenceClass;
  p_hunterType->fear = 0;
  p_hunterType->boredom = BOREDOM_MAX;
  p_hunterType->arrayIndex = arrayIndex;
  p_hunterType->seed = seed;
  p_hunterType->p_ghost = p_ghostType;
  p_hunterType->ghostlyEvidenceCount = 0;
}

/*Function: printHunter()
  Purpose:  print single Hunter
       in:  HunterType * p_hunterType
*/
void printHunter(HunterType * p_hunterType)
{
  printf("Hunter(Name:%s, NickName:%s, CurrentRoom:%s, EvidenceClassType:%d, Fear:%d, ArrayIndex:%d)", p_hunterType->name, p_hunterType->nickName, p_hunterType->p_currentRoom->name, p_hunterType->evidenceClassType, p_hunterType->fear, p_hunterType->arrayIndex);
}

void moveHunter(HunterType * p_hunterType)
{
  p_hunterType->p_currentRoom->hunters[p_hunterType->arrayIndex] = NULL;//tell the hunters current room we are leaving


  //printf("HunterMovement: %s ====>", p_hunterType->p_currentRoom->name);

  //collect evidence

  getNewRoom(&(p_hunterType->p_currentRoom));


  printf("%s moved ====> %s \n", p_hunterType->name, p_hunterType->p_currentRoom->name);


  p_hunterType->p_currentRoom->hunters[p_hunterType->arrayIndex] = p_hunterType;//tell the hunters new room we are now here
}

/*Function: collectEvidence()
  Purpose:  collect the Evidence
       in:  pointer to the hunter
*/
void collectEvidence(HunterType * p_hunterType)
{
  //printf("Hunter Looked for Evidence ====>");
  int found = 0;

  if(p_hunterType->p_currentRoom->evidenceList.p_headNode != NULL)
  {
    EvidenceNodeType* p_currentEvidenceNode;
    p_currentEvidenceNode = p_hunterType->p_currentRoom->evidenceList.p_headNode;

    while(p_currentEvidenceNode != NULL)
    {
        if(p_currentEvidenceNode->p_data->evidenceClassType == p_hunterType->evidenceClassType)
        {
            appendEvidence(&(p_hunterType->evidenceList), p_currentEvidenceNode->p_data);

            if(p_currentEvidenceNode->p_data->isGhostly == 1){
              p_hunterType->ghostlyEvidenceCount++;
            }

            deleteEvidence(&(p_hunterType->p_currentRoom->evidenceList), p_currentEvidenceNode->p_data);
            //have the room delite the current evidence
            //p_hunterType->arrayIndex++;
        }

        if(p_currentEvidenceNode->p_nextNode != NULL)
        {
          p_currentEvidenceNode = p_currentEvidenceNode->p_nextNode;
        }
        else
        {
          p_currentEvidenceNode = NULL;
        }
    }


  }



  //printf("Hunter Looked for Evidence ====> found[%d] \n", found);
  printf("%s Looked for Evidence ====>%d \n", p_hunterType->name, found);
}

/*Function: communicateEvidence()
  Purpose:  hunters communicate Evidence
       in:  pointer to the hunter
*/
void communicateEvidence(HunterType * p_hunterType)
{
  printf("< CommunicateEvidence >");
}

/*Function: hunterAction()
  Purpose:  randomly chose hunter action
       in:  pointer to the hunter
*/
void hunterAction(HunterType * p_hunterType)
{
  p_hunterType->boredom =  p_hunterType->boredom - 1;


  //When the hunter is in a room with the ghost
  if(doseRoomContainGhost(p_hunterType->p_currentRoom) == 1)
  {
    p_hunterType->fear = p_hunterType->fear + FEAR_RATE;
    p_hunterType->boredom = BOREDOM_MAX;
  }


  int actionRangeMax = 1;
  if(getNumberOfHuntersInRoom(p_hunterType->p_currentRoom) > 1){ actionRangeMax = 2; }
  int randomActionInt = (rand() % actionRangeMax);//Note the range of newRoomInt is [0, pp_currentRoom->size]
  //int randomActionInt = 2;
  switch (randomActionInt)
  {
    case 0://Move
      moveHunter(p_hunterType);
      break;
    case 1://CollectEvidence
      collectEvidence(p_hunterType);
      break;
    case 2://CommunicateEvidence
        printf("hunters communitcate\n");
        communicate(p_hunterType);
        break;
  }

  if(p_hunterType->ghostlyEvidenceCount >= 3){
    p_hunterType->p_ghost->busted = 1;
  }

}

void communicate(HunterType *p_hunterType){

  for(int i = 0; i < 4; i++){

    if(p_hunterType->p_currentRoom->hunters[i] != NULL && p_hunterType->p_currentRoom->hunters[i]->evidenceList.p_headNode != NULL){
      appendEvidence(&(p_hunterType->evidenceList),p_hunterType->p_currentRoom->hunters[i]->evidenceList.p_headNode->p_data);
    }
  }
}
