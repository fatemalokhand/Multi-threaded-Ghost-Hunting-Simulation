#include "defs.h"
#include <pthread.h>

void *ghostThread(void *args)
{
  srand(time(NULL));// Initialize a random seed for the random number generators

  GhostType *p_ghost = (GhostType*)args;
  printf("ghost's Thread Started! \n");

  int i = 0;
  while (p_ghost->boredom > 0 && p_ghost->busted != 1)
  {
    sem_wait(p_ghost->p_currentRoom->mutex);
    ghostAction(p_ghost, (unsigned int) i);
    sem_post(p_ghost->p_currentRoom->mutex);
    i++;
  }
  
}

void *hunterThread(void *args)
{
    HunterType *p_hunter = (HunterType*)args;
    printf("%s's Thread Started! \n", p_hunter->name);

    while (p_hunter->boredom > 0 && p_hunter->fear < MAX_FEAR && p_hunter->ghostlyEvidenceCount < 3)
    {
      hunterAction(p_hunter);
    }
    
}


int main(int argc, char *argv[])
{
    // Initialize a random seed for the random number generators
    srand(time(NULL));

    // You may change this code; this is for demonstration purposes
    BuildingType building;
    initBuilding(&building);
    populateRooms(&building);

    
    char hunterName1[MAX_STR];
    char hunterName2[MAX_STR];
    char hunterName3[MAX_STR];
    char hunterName4[MAX_STR];

    getNames(hunterName1, hunterName2,hunterName3,hunterName4);
    printf("\n");


    GhostType *  p_ghost =    calloc(1, sizeof(GhostType));
    HunterType * p_hunter01 = calloc(1, sizeof(HunterType));
    HunterType * p_hunter02 = calloc(1, sizeof(HunterType));
    HunterType * p_hunter03 = calloc(1, sizeof(HunterType));
    HunterType * p_hunter04 = calloc(1, sizeof(HunterType));

    initGhost(p_ghost, getRandomStartingRoom(time(NULL), &building),time(NULL));//make room and ghostType Random;

    printf("ghost initalized, here's the ghost info:\n");
    printGhost(p_ghost);
    printf("\n");
    initHunter(p_hunter01, hunterName1, "Hu1", building.rooms.p_headNode->room, EMF,0,time(0), p_ghost);
    initHunter(p_hunter02, hunterName2, "Hu2", building.rooms.p_headNode->room, TEMPERATURE,1, time(0), p_ghost);
    initHunter(p_hunter03, hunterName3, "Hu3", building.rooms.p_headNode->room, FINGERPRINTS,2,time(0), p_ghost);
    initHunter(p_hunter04, hunterName4, "Hu4", building.rooms.p_headNode->room, SOUND,3,time(0),p_ghost);
    printf("hunters initalized: \n");
    printHunter(p_hunter01);
    printf("\n");
    printHunter(p_hunter02);
    printf("\n");
    printHunter(p_hunter03);
    printf("\n");
    printHunter(p_hunter04);
    printf("\n");
    
    pthread_t threads[5];

    pthread_create(&threads[0], NULL, ghostThread,  p_ghost);
    pthread_create(&threads[1], NULL, hunterThread, p_hunter01);
    pthread_create(&threads[2], NULL, hunterThread, p_hunter02);
    pthread_create(&threads[3], NULL, hunterThread, p_hunter03);
    pthread_create(&threads[4], NULL, hunterThread, p_hunter04);

    for (int i = 0; i < 5; i++)
    {
      pthread_join(threads[i], NULL);
    }


    printBuilding(&building);
    
    printf("GAME SUMMARY:\n");
    printf("\n");
    printGhost(p_ghost);
    printf("busted: %d\n", p_ghost->busted);
    printf("\n");
    printf("%s fear and boredom is %d %d\n",p_hunter01->name, p_hunter01->fear, p_hunter01->boredom);
    printf("Evidence collected: \n");
    printEvidenceList(&(p_hunter01->evidenceList));
    printf("\n");
    printf("%s fear and boredom is %d %d\n",p_hunter02->name, p_hunter02->fear, p_hunter02->boredom);
    printf("Evidence collected: \n");
    printEvidenceList(&(p_hunter02->evidenceList));
    printf("\n");
    printf("%s fear and boredom is %d %d\n", p_hunter03->name,p_hunter03->fear, p_hunter03->boredom);
    printf("Evidence collected: \n");
    printEvidenceList(&(p_hunter03->evidenceList));
    printf("\n");
    printf("%s fear and boredom is %d %d\n", p_hunter04->name,p_hunter04->fear, p_hunter04->boredom);
    printf("Evidence collected: \n");
    printEvidenceList(&(p_hunter04->evidenceList));

    
    free(p_ghost);
    free(p_hunter01);
    free(p_hunter02);
    free(p_hunter03);
    free(p_hunter04);

    return 0;
}

void getNames(char* h1, char* h2, char* h3, char* h4){

    printf("Enter hunter one name: ");
    fgets(h1, MAX_STR, stdin);
    trim(h1);

    printf("Enter hunter two name: ");
    fgets(h2, MAX_STR, stdin);
    trim(h2);

    printf("Enter hunter three name: ");
    fgets(h3, MAX_STR, stdin);
    trim(h3);

    printf("Enter hunter four name: ");
    fgets(h4, MAX_STR, stdin);
    trim(h4);
    printf("hunter names are %s %s %s %s\n", h1, h2, h3, h4);
}

void trim(char* name){

  int i = strlen(name)-1;

  while (i > 0)
  {
    if(name[i] == ' ' || name[i] == '\n' || name[i] == '\t'){
      i--;

    }else break;
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
