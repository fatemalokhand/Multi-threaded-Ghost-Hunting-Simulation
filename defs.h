#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_STR            64
#define MAX_ARR            16
#define FEAR           	    1
#define BOREDOM            99
#define MAX_FEAR          100
#define MAX_HUNTERS         4
#define USLEEP_TIME     50000

typedef enum { EMF, TEMPERATURE, FINGERPRINTS, SOUND } EvidenceClassType;
typedef enum { POLTERGEIST, BANSHEE, BULLIES, PHANTOM } GhostClassType;

// declaring evidence type
typedef struct EvidenceType{
  EvidenceClassType evidenceClassType;
  float value;
  int isGhostly;
}EvidenceType;

// declaring room type
typedef struct RoomType{
  sem_t *mutex;
  char name[MAX_STR];
  EvidenceListType evidenceList;
  EdgeListType adjacentRooms;
  struct GhostType * ghost;
  struct HunterType* hunters[4];
} RoomType;

// declaring evidence list type
typedef struct EvidenceListType{
  EvidenceNodeType *headNode;
}EvidenceListType;

// declaring hunter type
typedef struct HunterType{
  char name[MAX_STR];
  char nickName[MAX_STR];
  struct RoomType * currentRoom;
  EvidenceClassType evidenceClassType;
  EvidenceListType evidenceList;
  int fear;
  int boredom;
  int arrayIndex;
  int ghostlyEvidenceCount;
  unsigned int seed;
  struct GhostType* ghost;
} HunterType;

// declaring ghost type
typedef struct GhostType{
  RoomType* currentRoom;
  GhostClassType class;
  int boredom;
  int busted;
  unsigned int seed;
}GhostType;

// declaring room node type
typedef struct RoomNodeType {
  RoomType* room;
  struct RoomNodeType* nextNode;
}RoomNodeType;

// declaring edge list type
typedef struct EdgeListType {
  struct RoomNodeType * headNode;
  int size;
} EdgeListType;

// declaring evidence node type
typedef struct EvidenceNodeType{
  EvidenceType* data;
  struct EvidenceNodeType *nextNode;
}EvidenceNodeType;

// declaring room list type
typedef struct  {
  RoomNodeType *headNode;
  RoomNodeType *tailNode;
}RoomListType;

// declaring building
typedef struct Building {
  RoomListType rooms;
  GhostType *ghost;
} BuildingType;


// function declarations

// room functions
void initRoomList(RoomListType *);
void addRoom(RoomListType  *, RoomNodeType *);
void populateRooms(BuildingType*);   
void initRoom(RoomType*, char*); 
int doesRoomContainGhost(RoomType*);
void printRoom(RoomType *);
void connectRooms(RoomType *, RoomType *);
void getNewRoom(RoomType **);
void printRoomOccupants(RoomType *, char[]);
int getNumberOfHuntersInRoom(RoomType *);

// ghost functions
void initGhost(GhostType *, RoomType *, unsigned int);
RoomType * getRandomStartingRoom(unsigned int, BuildingType *);
void moveGhost(GhostType *);
void printGhost(GhostType *);
void ghostAction(GhostType *, unsigned int);
GhostClassType randomGhost();

// hunter functions
void initHunter(HunterType *, char *, char *, RoomType *, EvidenceClassType, int, unsigned int, GhostType*);
void printHunter(HunterType *);
void moveHunter(HunterType *);
void collectEvidence(HunterType *);
void communicateEvidence(HunterType *);
void hunterAction(HunterType *);
void communicate(HunterType *);

// evidence functions
void initEvidence(EvidenceType*, unsigned int);
void printEvidence(EvidenceType*);
void initEvidenceList(EvidenceListType *);
void addEvidence(EvidenceListType*, EvidenceType*);
void deleteEvidence(EvidenceListType*, EvidenceType*);
void printEvidenceList(EvidenceListType*);

// other helper functions
int randInt(int, int);          
float randFloat(float, float);  
void getNames(char*, char*, char*, char*);
void trim(char*);

// building functions
void initBuilding(BuildingType*); 
void printBuilding(BuildingType*); 
