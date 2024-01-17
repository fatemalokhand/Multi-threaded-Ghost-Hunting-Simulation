#include "defs.h"
#include <pthread.h>

void *ghostThread(void *args)
{
  // Initialize a random seed for the random number generators
  srand(time(NULL));

  GhostType *ghost = (GhostType*)args;
  printf("ghost's Thread Started! \n");

  int i = 0;
  while(ghost->boredom > 0 && ghost->busted != 1)
  {
    sem_wait(ghost->currentRoom->mutex);
    ghostAction(ghost, (unsigned int) i);
    sem_post(ghost->currentRoom->mutex);
    i++;
  }
}

void *hunterThread(void *args)
{
    HunterType *hunter = (HunterType*)args;
    printf("%s's Thread Started! \n", hunter->name);

    while(hunter->boredom > 0 && hunter->fear < MAX_FEAR && hunter->ghostlyEvidenceCount < 3)
    {
      hunterAction(hunter);
    }
}

int main(int argc, char *argv[])
{
    // Initialize a random seed for the random number generators
    srand(time(NULL));

    // initializing the building and populating the rooms
    BuildingType building;
    initBuilding(&building);
    populateRooms(&building);

    // variables to store the hunter's names
    char hunter1Name[MAX_STR];
    char hunter2Name[MAX_STR];
    char hunter3Name[MAX_STR];
    char hunter4Name[MAX_STR];

    getNames(hunter1Name, hunter2Name,hunter3Name,hunter4Name);
    printf("\n");

    // creating the ghost and the 4 hunters
    GhostType*  ghost =    calloc(1, sizeof(GhostType));
    HunterType* hunter01 = calloc(1, sizeof(HunterType));
    HunterType* hunter02 = calloc(1, sizeof(HunterType));
    HunterType* hunter03 = calloc(1, sizeof(HunterType));
    HunterType* hunter04 = calloc(1, sizeof(HunterType));

    // initializing the ghost
    initGhost(ghost, getRandomStartingRoom(time(NULL), &building),time(NULL));

    printf("ghost initalized, here's the ghost info:\n");
    printGhost(ghost);
    printf("\n");
    
    // initializing the hunters
    initHunter(hunter01, hunter1Name, "Hunter 1", building.rooms.headNode->room, EMF,0,time(0), ghost);
    initHunter(hunter02, hunter2Name, "Hunter 2", building.rooms.headNode->room, TEMPERATURE,1, time(0), ghost);
    initHunter(hunter03, hunter3Name, "Hunter 3", building.rooms.headNode->room, FINGERPRINTS,2,time(0), ghost);
    initHunter(hunter04, hunter4Name, "Hunter 4", building.rooms.headNode->room, SOUND,3,time(0),ghost);
    
    printf("hunters initalized: \n");
    
    // printing out the hunters
    printHunter(hunter01);
    printf("\n");
    printHunter(hunter02);
    printf("\n");
    printHunter(hunter03);
    printf("\n");
    printHunter(hunter04);
    printf("\n");
    
    // array to hold the 5 threads
    pthread_t threads[5];

    // creating the threads
    pthread_create(&threads[0], NULL, ghostThread,  ghost);
    pthread_create(&threads[1], NULL, hunterThread, hunter01);
    pthread_create(&threads[2], NULL, hunterThread, hunter02);
    pthread_create(&threads[3], NULL, hunterThread, hunter03);
    pthread_create(&threads[4], NULL, hunterThread, hunter04);

    for(int i=0; i<5; i++)
    {
      // joining the threads
      pthread_join(threads[i], NULL);
    }

    // printing out the building
    printBuilding(&building);
    
    // printing out the game summary
    printf("GAME SUMMARY:\n");
    printf("\n");
    printGhost(ghost);
    printf("busted: %d\n", ghost->busted);
    printf("\n");
    printf("%s fear and boredom is %d %d\n",hunter01->name, hunter01->fear, hunter01->boredom);
    printf("Evidence collected: \n");
    printEvidenceList(&(hunter01->evidenceList));
    printf("\n");
    printf("%s fear and boredom is %d %d\n",hunter02->name, hunter02->fear, hunter02->boredom);
    printf("Evidence collected: \n");
    printEvidenceList(&(hunter02->evidenceList));
    printf("\n");
    printf("%s fear and boredom is %d %d\n", hunter03->name, hunter03->fear, hunter03->boredom);
    printf("Evidence collected: \n");
    printEvidenceList(&(hunter03->evidenceList));
    printf("\n");
    printf("%s fear and boredom is %d %d\n", hunter04->name, hunter04->fear, hunter04->boredom);
    printf("Evidence collected: \n");
    printEvidenceList(&(hunter04->evidenceList));

    // freeing all the pointers
    free(ghost);
    free(hunter01);
    free(hunter02);
    free(hunter03);
    free(hunter04);

    return 0;
}

// function to get the names of the 4 hunters
void getNames(char* h1, char* h2, char* h3, char* h4){

    // getting the name of hunter 1
    printf("Enter hunter 1 name: ");
    fgets(h1, MAX_STR, stdin);
    trim(h1);

    // getting the name of hunter 2
    printf("Enter hunter 2 name: ");
    fgets(h2, MAX_STR, stdin);
    trim(h2);

    // getting the name of hunter 3
    printf("Enter hunter 3 name: ");
    fgets(h3, MAX_STR, stdin);
    trim(h3);

    // getting the name of hunter 4
    printf("Enter hunter 4 name: ");
    fgets(h4, MAX_STR, stdin);
    trim(h4);
    printf("hunter names are %s %s %s %s\n", h1, h2, h3, h4);
}

// helper function
void trim(char* name){

  int i = strlen(name)-1;

  while (i > 0)
  {
    if(name[i] == ' ' || name[i] == '\n' || name[i] == '\t'){
      i--;
    }
    else break;
  }

  name[i+1] = '\0';
}

/*
  Function:  randInt
  Purpose:   returns a pseudo randomly generated number,
             in the range min to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [min, max-1)
*/
int randInt(int min, int max)
{
    return rand() % (max - min) + min;
}

/*
  Function:  randFloat
  Purpose:   returns a pseudo randomly generated number,
             in the range min to max, inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1)
*/
float randFloat(float a, float b) {
    // Get a percentage between rand() and the maximum
    float random = ((float) rand()) / (float) RAND_MAX;
    // Scale it to the range we want, and shift it
    return random * (b - a) + a;
}
