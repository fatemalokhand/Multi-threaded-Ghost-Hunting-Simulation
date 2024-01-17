#include "defs.h"

/*Function: initRoomList()
  Purpose:  initializes the RoomList
       in:  RoomListType* roomListType
*/
void initRoomList(RoomListType *roomListType)
{
  roomListType->headNode = NULL;
  roomListType->tailNode = NULL;

}

/*Function: addRoom()
  Purpose:  adds the Room into the room list
  in:  RoomListType *roomListType, RoomNodeType *roomToAppend
*/
void addRoom(RoomListType *roomListType, RoomNodeType *roomToAppend)
{
  if((roomListType->headNode == NULL) && (roomListType->tailNode == NULL))
  {
    roomListType->headNode = roomToAppend;
    roomListType->tailNode = roomToAppend;
  }
  else
  {
    RoomNodeType *thisNode;
    thisNode = roomListType->headNode;

    while(thisNode->nextNode != NULL)
    {
       thisNode = thisNode->nextNode;
    }

    thisNode->nextNode = roomToAppend;
    roomListType->tailNode = roomToAppend;
  }
}


/*Function: initRoom()
  Purpose:  initializing the Room
  in:  RoomType* room, char* name
*/
void initRoom(RoomType* room, char* name){
    room->mutex = malloc(sizeof(sem_t));
    sem_init(room->mutex, 0, 1);
    strcpy((room)->name,name);
    room->adjacentRooms.headNode == NULL;
    room->adjacentRooms.size = 0;
    room->ghost = NULL;
    initEvidenceList(&(room->evidenceList));

    for(int i=0; i<4; i++){
      room->hunters[i] = NULL;
    }
}

/*Function: doesRoomContainGhost()
  Purpose:  check if the ghost is in the room
  in:  RoomType *thisRoom
*/
int doesRoomContainGhost(RoomType *thisRoom)
{
   return (thisRoom->ghost != NULL);
}

/*Function: printRoom(()
  Purpose:  prints out all the rooms and what rooms they are connected to
  in:  room pinter
*/
void printRoom(RoomType *roomType)
{
  if(roomType == NULL)
  {
    printf("[Room Is NULL]\n");
  }
  else
  {
      printf("%s \n", roomType->name);

      if(doesRoomContainGhost(roomType) == 1)
      {
        printf("[Boo] \n");
      }
      else
      {
        printf("[   ] \n");
      }

      for(int i=0; i<=3; i++)
      {
        if(roomType->hunters[i] == NULL)
        {
          printf("[   ] \n");
        }
        else
        {
          printf("[%s] \n", roomType->hunters[i]->nickName);
        }
      }

      if(roomType->adjacentRooms.headNode == NULL)
      {
        printf("     <<No-Adjacent-Rooms>>\n");
      }
      else
      {
        printf("     adjacentRooms [%d]: \n", roomType->adjacentRooms.size);

        RoomNodeType* thisNode;
        thisNode = roomType->adjacentRooms.headNode;
        while(thisNode->nextNode != NULL)
        {
           printf("%s --> %s \n",  roomType->name, thisNode->room->name);
           thisNode = thisNode->nextNode;
        }
        printf("%s --> %s \n",  roomType->name, thisNode->room->name);
      }

      printEvidenceList(&(roomType->evidenceList));
  }

  printf("\n");
}

/*Function: connectOneRoom(()
  Purpose:  connecting one room to the other room
  in:  RoomType *thisRoom, RoomType *roomToConnect
*/
void connectOneRoom(RoomType *thisRoom, RoomType *roomToConnect){
  RoomNodeType* newNode;
  newNode = malloc(sizeof(RoomNodeType));
  newNode->room = roomToConnect;
  newNode->nextNode = NULL;

  if(thisRoom->adjacentRooms.headNode == NULL)
  {
    thisRoom->adjacentRooms.headNode = newNode;
  }
  else
  {
    RoomNodeType* current;
    current = thisRoom->adjacentRooms.headNode;

    while(current->nextNode != NULL)
    {
       current = current->nextNode;
    }

    current->nextNode = newNode;
  }
  thisRoom->adjacentRooms.size++;
}

/*Function: connectRooms(()
  Purpose:  connecting 2 rooms together
  in:  RoomType *roomA, RoomType *roomB
*/
void connectRooms(RoomType *roomA, RoomType *roomB)
{
  connectOneRoom(roomA, roomB);
  connectOneRoom(roomB, roomA);
}


/*Function: getNewRoom()
  Purpose:  moving things to a new room
  in:  RoomType ** currentRoom
*/
void getNewRoom(RoomType** currentRoom){
  int newRoomInt = (rand() % ((*currentRoom)->adjacentRooms.size));
  RoomNodeType *thisNode;
  thisNode = (*currentRoom)->adjacentRooms.headNode;

  for(int i=0; i<newRoomInt; i++)
  {
     thisNode = thisNode->nextNode;
  }

  *currentRoom = thisNode->room;
}

// function to get the number of hunters in the room
int getNumberOfHuntersInRoom(RoomType *roomType)
{
  int numberOfHunters = 0;

  for(int i=0; i<=3; i++)
  {
      if(roomType->hunters[i] == NULL)
      {
          numberOfHunters++;
      }
  }

  return numberOfHunters;
}
