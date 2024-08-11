#include "raylib.h"
#include "spacestuff.h"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>



//  "hitBox":  [
  //  {"x": 0, "y": 0},
  //  {"x": 100, "y": 0},
  //  {"x": 100, "y": 100},
  //  {"x": 0, "y": 100}
  //]
//} need to save into this format
std::string vector2String(Vector2 urmom) {
  std::stringstream ss;
  // Insert the Vector2 object into the stringstream
ss <<"{"<< urmom.x << "," << urmom.y << "}";
return ss.str();

}

int main(int argc, char* argv[]){

  std::string inputfilestring;
  std::string outputfilestring;
  switch (argc){
    case 3:
      inputfilestring = argv[1];
      outputfilestring = argv[2];
        break;
    default:
      std::cout << "give two arguments first is json to load from second is json to save to" << std::endl;
      return 0;  
  } 
  //overides for testing
//inputfilestring="/home/eon/fucking_around/c++/game/funkySpaceGame/objectData/yShip.json";
//outputfilestring="/home/eon/fucking_around/c++/game/funkySpaceGame/objectData/yShipTestSave.json";
  InitWindow(0,0,"Save Collision Box");
  SetTargetFPS(60);

  //nlohmann::json objectData=loadJSON("/home/eon/fucking_around/c++/game/funkySpaceGame/objectData/yShip.json");
  std::ifstream inputfile(inputfilestring);
  //nlohmann::json objectData = nlohmann::json::parse(inputfile);
  nlohmann::json objectData = loadJSON(inputfilestring);
  if (objectData==nullptr){return 0;}

  //changing starting position to the middle of the screen
  objectData.at("posx")=GetScreenWidth()/2;
  objectData.at("posy")=GetScreenHeight()/2;

  spaceStuffLoaded object(objectData);
  std::vector<Vector2> pointList;
  pointList.push_back({0,0}); //reserving space to put the final length of point list here later
  Vector2 mousePoint;
  Vector2 mousePoint2;


  while(!WindowShouldClose()){

    mousePoint = GetMousePosition();
    mousePoint2.x = mousePoint.x-object.myKinematics.pos.x;
    mousePoint2.y = mousePoint.y-object.myKinematics.pos.y;

    if(IsKeyPressed(KEY_ENTER)){
      pointList.push_back(mousePoint2);
    }

    if(IsKeyPressed(KEY_BACKSPACE)&&(pointList.size()>0)){
      pointList.pop_back();
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    object.draw();
    for (int i=0;i<pointList.size();i++){
      DrawCircleV({pointList[i].x+object.myKinematics.pos.x,pointList[i].y+object.myKinematics.pos.y},5,BLUE);
    }
    DrawCircleV(mousePoint,5,BLUE);
    DrawText(vector2String(mousePoint2).c_str(),100,100,200,GREEN);

    EndDrawing();
  }

  //close out tasks
  object.unload();
  CloseWindow();
  pointList[0].x = pointList.size();
  for (int i = 0;i<pointList[0].x;i++){
    objectData["hitBox"][i]=vector2String(pointList[i]);
  }
  
  std::ofstream outputFile(outputfilestring,std::ios::out);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file: " << outputfilestring  << std::endl;
    }
    else {
  outputFile << objectData;
    }
}

