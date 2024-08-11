#include "raylib.h"
#include "spacestuff.h"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

std::string vector2String(Vector2 urmom) {
  std::stringstream ss;
  // Insert the Vector2 object into the stringstream
ss << urmom.x << "," << urmom.y;
return ss.str();

}

int main(int argc, char* argv[]){


  switch (argc){
    case 1:
    return 0;
    case 2:
    std::cout << "give two arguments first is json to load from second is json to save to" << std::endl;
    return 0;
    default:
      //std::string inputfilestring = argv[1];
      //std::string outputfilestring = argv[2];
      break;
  } 

  InitWindow(0,0,"Save Collision Box");
  SetTargetFPS(60);

  //nlohmann::json objectData=loadJSON("/home/eon/fucking_around/c++/game/funkySpaceGame/objectData/yShip.json");
  std::ifstream inputfile("/home/eon/fucking_around/c++/game/funkySpaceGame/objectData/yShip.json");
  nlohmann::json objectData = nlohmann::json::parse(inputfile);
  objectData.at("posx")=GetScreenWidth()/2;
  objectData.at("posy")=GetScreenHeight()/2;
  spaceStuffLoaded object(objectData);
  std::vector<Vector2> pointList;
  Vector2 mousePoint;
  


  while(!WindowShouldClose()){

    mousePoint = GetMousePosition();
    if(IsKeyPressed(KEY_ENTER)){
      pointList.push_back(mousePoint);
    }

    if(IsKeyPressed(KEY_BACKSPACE)&&(pointList.size()>0)){
      pointList.pop_back();
    }
    std::cout << argc << std::endl;
    BeginDrawing();
    ClearBackground(RAYWHITE);
    object.draw();
    for (int i=0;i<pointList.size();i++){
      DrawCircleV(pointList[i],5,BLUE);
    }
    DrawCircleV(mousePoint,5,BLUE);
    DrawText(vector2String(mousePoint).c_str(),100,100,200,GREEN);

    EndDrawing();
  }
  object.unload();
  CloseWindow();
  for (int i = 0;i<pointList.size();i++){
    objectData["hitBox"][i]=vector2String(pointList[i]);
  }
  std::ofstream outputFile("/home/eon/fucking_around/c++/game/funkySpaceGame/objectData/yShipTestSave.json");
  outputFile << objectData;
}

