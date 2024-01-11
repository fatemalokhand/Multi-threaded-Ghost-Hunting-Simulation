#include "defs.h"

/* 
  Function: initHouse();
  Purpose:  initializes the fields of a given HouseType
  Params:   
    Output: HouseType *house - the house who's fields are to be intitialized

*/
void initHouse(HouseType *house){

    // initialize the rooms of the given house
    initRoomList(&(house->rooms));

}

/* 
  Function: cleanupHouse();
  Purpose:  deallocates the dynamically allocated memory in the given house type
  Params:   
    Input/Output: HouseType *house - the house who's memory will be deallocated

*/
void cleanupHouse(HouseType *house){

    // call functions to clean up all dynamically allocated elements of the building
    cleanupRoomData(&(house->rooms));
    cleanupRoomList(&(house->rooms));

}

/* 
  Function: getRandomRoom();
  Purpose:  generate a random room based off the parameter
  Params:   
    Input: NodeType *startingNode - the room in the house list where the room generation will begin from

*/
RoomType* getRandomRoom(NodeType *startingNode){

    // create a variable to store the amount of rooms
    int numRooms = 0;

    // create variables to store the current node
    NodeType *currentNode;

    // set the current node to the head of the list
    currentNode = startingNode;

    // traverse through the list
    while(currentNode != NULL){

        // incriment the number of rooms by 1
        numRooms++;

        // set the current node to the next node
        currentNode = currentNode->next;

    }

    // create an array that is the size of the number of rooms
    RoomType *houseRooms[numRooms];
    int count = 0;

    // generate a random number
    int randomNum = randInt(0, numRooms);

    // set the current node to the starting node parameter
    currentNode = startingNode;

    // traverse through the list
    while(currentNode != NULL){

        // set the current element in the house rooms array to the current linked list element
        houseRooms[count] = currentNode->data;
        count++;

        // set the current node to the next node
        currentNode = currentNode->next;

    }

    // return a random room from the house rooms array
    return houseRooms[randomNum];

}


/*
    Dynamically allocates several rooms and populates the provided house.
    Note: You may modify this as long as room names and connections are maintained.
        out: house - the house to populate with rooms. Assumes house has been initialized.
*/
void populateRooms(HouseType* house) {
    // First, create each room

    // createRoom assumes that we dynamically allocate a room, initializes the values, and returns a RoomType*
    // create functions are pretty typical, but it means errors are harder to return aside from NULL
    struct Room* van                = createRoom("Van");
    struct Room* hallway            = createRoom("Hallway");
    struct Room* master_bedroom     = createRoom("Master Bedroom");
    struct Room* boys_bedroom       = createRoom("Boy's Bedroom");
    struct Room* bathroom           = createRoom("Bathroom");
    struct Room* basement           = createRoom("Basement");
    struct Room* basement_hallway   = createRoom("Basement Hallway");
    struct Room* right_storage_room = createRoom("Right Storage Room");
    struct Room* left_storage_room  = createRoom("Left Storage Room");
    struct Room* kitchen            = createRoom("Kitchen");
    struct Room* living_room        = createRoom("Living Room");
    struct Room* garage             = createRoom("Garage");
    struct Room* utility_room       = createRoom("Utility Room");

    // This adds each room to each other's room lists
    // All rooms are two-way connections
    connectRooms(van, hallway);
    connectRooms(hallway, master_bedroom);
    connectRooms(hallway, boys_bedroom);
    connectRooms(hallway, bathroom);
    connectRooms(hallway, kitchen);
    connectRooms(hallway, basement);
    connectRooms(basement, basement_hallway);
    connectRooms(basement_hallway, right_storage_room);
    connectRooms(basement_hallway, left_storage_room);
    connectRooms(kitchen, living_room);
    connectRooms(kitchen, garage);
    connectRooms(garage, utility_room);

    // Add each room to the house's room list
    addRoom(&house->rooms, van);
    addRoom(&house->rooms, hallway);
    addRoom(&house->rooms, master_bedroom);
    addRoom(&house->rooms, boys_bedroom);
    addRoom(&house->rooms, bathroom);
    addRoom(&house->rooms, basement);
    addRoom(&house->rooms, basement_hallway);
    addRoom(&house->rooms, right_storage_room);
    addRoom(&house->rooms, left_storage_room);
    addRoom(&house->rooms, kitchen);
    addRoom(&house->rooms, living_room);
    addRoom(&house->rooms, garage);
    addRoom(&house->rooms, utility_room);
}