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

bool saveBoxToJson (nlohmann::json& urmom, std::vector<Vector2> pointList){

  if(urmom.at("hitBox")!=NULL){

  }
  else {
 // urmom.insert("hitBox",pointList);
 // urmom.find()
  }
  return 1;
}
int main(){

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

    BeginDrawing();
    ClearBackground(RAYWHITE);
    object.draw();
    for (int i=0;i<pointList.size();i++){
      DrawCircleV(pointList[i],50,BLUE);
    }
    DrawCircleV(mousePoint,50,BLUE);
    DrawText(vector2String(mousePoint).c_str(),100,100,200,GREEN);

    EndDrawing();
  }
  object.unload();
  CloseWindow();
  objectData["hitBox"][0]=vector2String(pointList[0]);
    std::ofstream outputFile("/home/eon/fucking_around/c++/game/funkySpaceGame/objectData/yShipTestSave.json");
  outputFile << objectData;
}

