#include "defs.h"

/*Function: initRoomList()
  Purpose:  initRoomList
       in:  RoomListType *p_roomListType
*/
void initRoomList(RoomListType *p_roomListType)
{
  //might need to allocate for the two nodes
  p_roomListType->p_headNode = NULL;
  p_roomListType->p_tailNode = NULL;

}

/*Function: appendRoom()
  Purpose:  append Room
  in:  RoomListType *p_roomListType, RoomNodeType *p_roomToAppend
*/
void appendRoom(RoomListType *p_roomListType, RoomNodeType *p_roomToAppend)
{
  if((p_roomListType->p_headNode == NULL) && (p_roomListType->p_tailNode == NULL))
  {
    p_roomListType->p_headNode = p_roomToAppend;
    p_roomListType->p_tailNode = p_roomToAppend;
  }
  else
  {
    RoomNodeType *p_thisNode;
    p_thisNode = p_roomListType->p_headNode;

    while (p_thisNode->p_nextNode != NULL)
    {
       p_thisNode = p_thisNode->p_nextNode;
    }

    p_thisNode->p_nextNode = p_roomToAppend;
    p_roomListType->p_tailNode = p_roomToAppend;
  }
}



/*Function: initRoom()
  Purpose:  initRoom
  in:  RoomType* room, char* name
*/
void initRoom(RoomType* room, char* name){
    //sem_t mutex;
    room->mutex = malloc(sizeof(sem_t));
    //room->mutex = &mutex;
    sem_init(room->mutex, 0, 1);


    strcpy((room)->name,name);
    room->adjacentRooms.p_headNode == NULL;
    room->adjacentRooms.size = 0;
    room->p_ghost = NULL;
    initEvidenceList(&(room->evidenceList));

    for(int i = 0; i < 4; i++){
      room->hunters[i] = NULL;
    }
}

/*Function: doseRoomContainGhost()
  Purpose:  check if ghost is in the room
  in:  RoomType *p_thisRoom
*/
int doseRoomContainGhost(RoomType *p_thisRoom)
{
   return (p_thisRoom->p_ghost != NULL);
}

/*Function: printRoom(()
  Purpose:  print all rooms and what its connected to
  in:  room pinter
*/
void printRoom(RoomType *p_roomType)
{
  //printf("printRoom Start \n");


  if(p_roomType == NULL)
  {
    printf("[Room Is NULL]\n");
  }
  else
  {
      printf("%s \n", p_roomType->name);

      ///////////////////////////////

      //printf("Ghost[%d] \n", doseRoomContainGhost(p_roomType));
      if(doseRoomContainGhost(p_roomType) == 1)
      {
        printf("[Boo] \n");
      }
      else
      {
        printf("[   ] \n");
      }


      ///////////////////////////////

      //printf("Hunters:\n");
      for(int i = 0; i <= 3; i++)
      {
        if(p_roomType->hunters[i] == NULL)
        {
          printf("[   ] \n");
        }
        else
        {
          printf("[%s] \n", p_roomType->hunters[i]->nickName);
        }
      }

      ///////////////////////////////

      if(p_roomType->adjacentRooms.p_headNode == NULL)
      {
        printf("     <<No-Adjacent-Rooms>>\n");
      }
      else
      {
        printf("     adjacentRooms [%d]: \n", p_roomType->adjacentRooms.size);

        RoomNodeType * p_thisNode;
        p_thisNode = p_roomType->adjacentRooms.p_headNode;
        while (p_thisNode->p_nextNode != NULL)
        {
           printf("%s --> %s \n",  p_roomType->name, p_thisNode->room->name);
           p_thisNode = p_thisNode->p_nextNode;
        }
        printf("%s --> %s \n",  p_roomType->name, p_thisNode->room->name);
      }

      ///////////////////////////////

      printEvidenceList(&(p_roomType->evidenceList));
  }


    printf("\n");
    //printf("printRoom End \n");
}

/*Function: connectOneRoom(()
  Purpose:  connect one room to the other
  in:  RoomType *p_thisRoom, RoomType *p_roonToConnect
*/
void connectOneRoom(RoomType *p_thisRoom, RoomType *p_roonToConnect){
  RoomNodeType* p_newNode;
  p_newNode = malloc(sizeof(RoomNodeType));
  p_newNode->room = p_roonToConnect;
  p_newNode->p_nextNode = NULL;

  if(p_thisRoom->adjacentRooms.p_headNode == NULL)
  {
    p_thisRoom->adjacentRooms.p_headNode = p_newNode;
    //p_thisRoom->size++;
  }
  else
  {
    RoomNodeType* p_current;
    p_current = p_thisRoom->adjacentRooms.p_headNode;

    while (p_current->p_nextNode != NULL)
    {
       p_current = p_current->p_nextNode;
    }

    p_current->p_nextNode = p_newNode;
    //p_thisRoom->size++;
  }
  p_thisRoom->adjacentRooms.size++;
}

/*Function: connectRooms(()
  Purpose:  connect 2 rooms
  in:  RoomType *p_roomA, RoomType *p_roomB
*/
void connectRooms(RoomType *p_roomA, RoomType *p_roomB)
{
  connectOneRoom(p_roomA, p_roomB);
  connectOneRoom(p_roomB, p_roomA);
}


/*Function: getNewRoom()
  Purpose:  move stuff to a new room
  in:  RoomType ** pp_currentRoom
*/
void getNewRoom(RoomType ** pp_currentRoom){
  int newRoomInt = (rand() % ((*pp_currentRoom)->adjacentRooms.size));//Note the range of newRoomInt is [0, pp_currentRoom->size]
  RoomNodeType *p_thisNode;
  p_thisNode = (*pp_currentRoom)->adjacentRooms.p_headNode;

  for(int i = 0; i < newRoomInt; i++)
  {
     //printf("line 136 called\n");
     p_thisNode = p_thisNode->p_nextNode;
  }

  *pp_currentRoom = p_thisNode->room;
  

  
}

int getNumberOfHuntersInRoom(RoomType *p_roomType)
{
  int numberOfHunters = 0;

  for(int i = 0; i <= 3; i++)
  {
      if(p_roomType->hunters[i] == NULL)
      {
          numberOfHunters++;
      }
  }

  return numberOfHunters;
}
