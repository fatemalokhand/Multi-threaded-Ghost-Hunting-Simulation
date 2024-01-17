#include "defs.h"

// function to print out the building
void printBuilding(BuildingType *building){

    // checking if the building is empty
    if(buildingType->rooms.headNode == NULL && buildingType->rooms.tailNode == NULL){
    	printf("building is null\n");
    }
    else{

      RoomNodeType* current;
      current = buildingType->rooms.headNode;
      
      // printing out all the rooms in the building
      while(current->nextNode != NULL){
        printRoom(current->room);
        current = current->nextNode;
      }

      printRoom(current->room);
    }
}

// function to populate the rooms
void populateRooms(BuildingType* building) {
    // Creating the rooms dynamically
    building->ghost = NULL;
    RoomType* van = calloc(1, sizeof(RoomType));
    initRoom(van, "Van");
    RoomType* hallway = calloc(1, sizeof(RoomType));
    initRoom(hallway, "Hallway");
    RoomType* master_bedroom = calloc(1, sizeof(RoomType));
    initRoom(master_bedroom, "Master Bedroom");
    RoomType* boys_bedroom = calloc(1, sizeof(RoomType));
    initRoom(boys_bedroom, "Boy's Bedroom");
    RoomType* bathroom = calloc(1, sizeof(RoomType));
    initRoom(bathroom, "Bathroom");
    RoomType* basement = calloc(1, sizeof(RoomType));
    initRoom(basement, "Basement");
    RoomType* basement_hallway = calloc(1, sizeof(RoomType));
    initRoom(basement_hallway, "Basement Hallway");
    RoomType* right_storage_room = calloc(1, sizeof(RoomType));
    initRoom(right_storage_room, "Right Storage Room");
    RoomType* left_storage_room = calloc(1, sizeof(RoomType));
    initRoom(left_storage_room, "Left Storage Room");
    RoomType* kitchen = calloc(1, sizeof(RoomType));
    initRoom(kitchen, "Kitchen");
    RoomType* living_room = calloc(1, sizeof(RoomType));
    initRoom(living_room, "Living Room");
    RoomType* garage = calloc(1, sizeof(RoomType));
    initRoom(garage, "Garage");
    RoomType* utility_room = calloc(1, sizeof(RoomType));
    initRoom(utility_room, "Utility Room");

    // Creating a linked list of rooms
    RoomNodeType* van_node = calloc(1, sizeof(RoomNodeType));
    van_node->room = van;
    van_node->nextNode = NULL;

    RoomNodeType* hallway_node = calloc(1, sizeof(RoomNodeType));
    hallway_node->room = hallway;
    hallway_node->nextNode = NULL;

    RoomNodeType* master_bedroom_node = calloc(1, sizeof(RoomNodeType));
    master_bedroom_node->room = master_bedroom;
    master_bedroom_node->nextNode = NULL;

    RoomNodeType* boys_bedroom_node = calloc(1, sizeof(RoomNodeType));
    boys_bedroom_node->room = boys_bedroom;
    boys_bedroom_node->nextNode = NULL;

    RoomNodeType* bathroom_node = calloc(1, sizeof(RoomNodeType));
    bathroom_node->room = bathroom;
    bathroom_node->nextNode = NULL;

    RoomNodeType* basement_node = calloc(1, sizeof(RoomNodeType));
    basement_node->room = basement;
    basement_node->nextNode = NULL;

    RoomNodeType* basement_hallway_node = calloc(1, sizeof(RoomNodeType));
    basement_hallway_node->room = basement_hallway;
    basement_hallway_node->nextNode = NULL;

    RoomNodeType* right_storage_room_node = calloc(1, sizeof(RoomNodeType));
    right_storage_room_node->room = right_storage_room;
    right_storage_room_node->nextNode = NULL;

    RoomNodeType* left_storage_room_node = calloc(1, sizeof(RoomNodeType));
    left_storage_room_node->room = left_storage_room;
    left_storage_room_node->nextNode = NULL;

    RoomNodeType* kitchen_node = calloc(1, sizeof(RoomNodeType));
    kitchen_node->room = kitchen;
    kitchen_node->nextNode = NULL;

    RoomNodeType* living_room_node = calloc(1, sizeof(RoomNodeType));
    living_room_node->room = living_room;
    living_room_node->nextNode = NULL;

    RoomNodeType* garage_node = calloc(1, sizeof(RoomNodeType));
    garage_node->room = garage;
    garage_node->nextNode = NULL;

    RoomNodeType* utility_room_node = calloc(1, sizeof(RoomNodeType));
    utility_room_node->room = utility_room;
    utility_room_node->nextNode = NULL;

    // initializing the room list
    initRoomList(&building->rooms);
    
    // adding the rooms
    addRoom(&building->rooms, van_node);
    addRoom(&building->rooms, hallway_node);
    addRoom(&building->rooms, master_bedroom_node);
    addRoom(&building->rooms, boys_bedroom_node);
    addRoom(&building->rooms, bathroom_node);
    addRoom(&building->rooms, basement_node);
    addRoom(&building->rooms, basement_hallway_node);
    addRoom(&building->rooms, right_storage_room_node);
    addRoom(&building->rooms, left_storage_room_node);
    addRoom(&building->rooms, kitchen_node);
    addRoom(&building->rooms, living_room_node);
    addRoom(&building->rooms, garage_node);
    addRoom(&building->rooms, utility_room_node);

    // connecting the rooms together
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
}

void initBuilding(BuildingType* building)
{
  
}

void cleanupBuilding(BuildingType* building)
{
 
}
