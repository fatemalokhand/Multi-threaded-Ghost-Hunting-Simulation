#include "defs.h"

/*	Function: initEvidence()
  	Purpose:  to initialize evidence
	in:  EvidenceType *evidenceType, unsigned int seed
*/
void initEvidence(EvidenceType *evidenceType, unsigned int seed){

    // generating a random number
    int random = rand() % (3 - 0) + 0;

    //randomly generate an evidenceType
    switch (random)
    {
      //evidenceType is EMF
      case 0:
          evidenceType->evidenceClassType = 0;
          evidenceType->value = randFloat(0,5);
          if((4.70 < evidenceType->value) && (evidenceType->value < 5))
          {  
          	evidenceType->isGhostly = 1; 
  	  }
          else
          { 
          	evidenceType->isGhostly = 0;
  	  }
       break;
      // evidenceType is TEMPERATURE 
      case 1:
          evidenceType->evidenceClassType = 1;
          evidenceType->value = randFloat(-10,27);
          if((-10 < evidenceType->value) && (evidenceType->value < 1))
          {  
          	evidenceType->isGhostly = 1; 
  	  }
          else
          { 
          	evidenceType->isGhostly = 0;
  	  }
        break;
      // evidenceType is FINGERPRINTS
      case 2:
          evidenceType->evidenceClassType = 2;
          if(0.5 < randFloat(0,1))
          {
             evidenceType->isGhostly = 1;
             evidenceType->value = 1;
          }
          else
          {
            evidenceType->isGhostly = 0;
            evidenceType->value = 0;
          }
        break;
      // evidenceType is SOUND
      case 3:
          evidenceType->evidenceClassType = 3;
          evidenceType->value = randFloat(40,75);
          if((65 < evidenceType->value) && (evidenceType->value < 75))
          { 
          	evidenceType->isGhostly = 1; 
  	  }
          else
          { 
          	evidenceType->isGhostly = 0;
          }
        break;
    }
}

/*	Function: printEvidence()
  	Purpose:  prints out a single Evidence
       in:  pointer to an evidence
*/
void printEvidence(EvidenceType *evidenceType){

  switch (evidenceType->evidenceClassType)
  {
      // printing the evidence types
      case 0:
          printf("evidence type %s, ", "EMF");
       break;
      case 1:
          printf("evidence type %s, ", "TEMPERATURE");
        break;
      case 2:
          printf("evidence type %s, ", "FINGERPRINTS");
        break;
      case 3:
          printf("evidence type %s, ", "SOUND");
        break;
  }

    printf("value %f", evidenceType->value);

    if(evidenceType->isGhostly == 1){
      printf(" [ghostly]");
    }

    printf("\n");
}

/*Function: initEvidenceList()
  Purpose:  initialize the EvidenceList
       in:  EvidenceList pointer
*/
void initEvidenceList(EvidenceListType *evidenceList){
    evidenceList->p_headNode = NULL;
}

/*Function: addEvidence()
  Purpose:  adds evidence to the EvidenceList
       in:  EvidenceListType* evidenveList, EvidenceType* evidence
*/
void addEvidence(EvidenceListType* evidenveList, EvidenceType* evidence){

    EvidenceNodeType* newNode;
    newNode = malloc(sizeof(EvidenceNodeType));
    newNode->data = evidence;
    newNode->nextNode = NULL;

    if(evidenveList->headNode == NULL)
    {
        evidenveList->headNode = newNode;
    }
    else{

        EvidenceNodeType* current;
        current = evidenveList->headNode;
        while(current->nextNode != NULL){
            current = current->nextNode;
        }

        current->nextNode = newNode;
    }
}

/*Function: deleteEvidence()
  Purpose:  deletes evidence form the EvidenceList
       in:  EvidenceListType* evidenveList, EvidenceType* evidence
*/
void deleteEvidence(EvidenceListType* evidenveList, EvidenceType* evidenceToDelete)
{
    if(evidenveList->headNode->data == evidenceToDelete)
    {
        if(evidenveList->headNode->nextNode != NULL)
        {
          evidenveList->headNode = evidenveList->headNode->nextNode;
        }
        else
        {
          evidenveList->headNode = NULL;
        }
    }
    else
    {
      EvidenceNodeType* previousNode = evidenveList->headNode;
      EvidenceNodeType* currentNode = evidenveList->headNode->nextNode;

      while(currentNode != NULL)
      {
          if(currentNode->data == evidenceToDelete)
          {
              if(currentNode->nextNode != NULL)
              {
                previousNode->nextNode = currentNode->nextNode;
              }
              else
              {
                  previousNode->nextNode = NULL;
              }
          }

          currentNode = currentNode->nextNode;
      }
  }
}

/*Function: printEvidenceList()
  Purpose:  prints out the EvidenceList
       in:  EvidenceListType* evidenceList
*/
void printEvidenceList(EvidenceListType* evidenceList){

    if(evidenceList->headNode == NULL)
    {
        printf("no evidence in the collection\n");
    }
    else{

        EvidenceNodeType* current;
        current = evidenceList->headNode;

        while (current->nextNode != NULL)
        {
            printEvidence(current->data);
            current = current->nextNode;
        }

        printEvidence(current->data);

    }
}
