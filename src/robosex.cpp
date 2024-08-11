#include "raylib.h"
#include "string"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <filesystem>
#include <math.h>
#include <iostream>
#include <vector>
#include "spacestuff.h"
#include "json.hpp"

void drawgrid(){
const int spacing = 50;
const int screenWidth = 900;
const int screenHeight = 900;

  // Draw vertical lines
        for (int x = 0; x <= GetScreenWidth(); x += spacing) {
            DrawLine(x, 0, x, screenHeight, GRAY); // Vertical lines
        }

        // Draw horizontal lines
        for (int y = 0; y <= GetScreenHeight(); y += spacing) {
            DrawLine(0, y, screenWidth, y, GRAY); // Horizontal lines
        }


}

nlohmann::json readShipData(const std::string& filepath){
  //this needs error handling

  std::ifstream file(filepath);
  nlohmann::json data = nlohmann::json::parse(file);

  return data;

}



void doEverything(std::vector<spaceStuffLoaded*> spaceList,std::vector<int> options){
  //gonna add some more options lol
  //yeet this into the header file once it's semi finalized
  //
  //Want to reorder these options to accomodate any important sequencing
  for (int j = 0;j <options.size();j++){     
    for (int i =0; i<spaceList.size();i++){
      switch(options[j]){
        case 1:
          //draw shit on screen
          spaceList[i]->draw();
          break;
        case 2:
          //make physics go brrrrrrr
          spaceList[i]->animate();
          break;
        case 3:
          spaceList[i]->unload();
          break;
        case 4:
          spaceStuffLoaded& thing = *spaceList[i];
          for (int k = 0; k < spaceList.size(); k++) {
            if (k!=i) {
              spaceStuffLoaded& anchor = *spaceList[k];
              gravity(thing,anchor);
            }
          }
          //add more cases and methods to spaceStuff and doEverything as needed
       }
    };
  };
  return ;
}
   

int main(){ 
  //intialization
    InitWindow(0, 0, "Rotating Image around Center");
    SetTargetFPS(60);
    nlohmann::json shipjson = readShipData("/home/eon/fucking_around/c++/game/funkySpaceGame/objectData/yShipTestSave.json");
    std::cout << shipjson.at("filepath");
    std::vector<spaceStuffLoaded*> spaceList;
    std::string fuck=shipjson.at("filepath");

    spaceStuffLoaded fighter(shipjson);  
    spaceStuffLoaded fighter2(shipjson);
    fighter2.myKinematics.pos.x=500;
    spaceStuffLoaded rock(readShipData("/home/eon/fucking_around/c++/game/funkySpaceGame/objectData/rockTestSave.json"));
    spaceList.push_back(&fighter);
    spaceList.push_back(&fighter2);
    spaceList.push_back(&rock);
    std::vector<int> options;
    options.push_back(1);
    options.push_back(2);
    options.push_back(4);

    Camera2D camera = {0};
    camera.target = (Vector2{(float)fighter.myKinematics.pos.x+20.0f,(float)fighter.myKinematics.pos.y+20.0f});
    camera.offset = (Vector2){(float) GetScreenWidth()/2.0f,(float) GetScreenHeight()/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 01.0f;

    while (!WindowShouldClose()) {
    //main game loop
    //fighter.animate(); //animate just means change position and velocity based on acceleration and velotiy
    if (IsKeyDown(KEY_D)) fighter.myKinematics.vel.x += 0.55f;
    if (IsKeyDown(KEY_A)) fighter.myKinematics.vel.x-= 0.55f;
    if (IsKeyDown(KEY_W)) fighter.myKinematics.vel.y -= 0.55f;
    if (IsKeyDown(KEY_S)) fighter.myKinematics.vel.y  += 0.55f;

    if (IsKeyDown(KEY_E)) fighter.myRotation.rot += 5.0f;
    if (IsKeyDown(KEY_Q)) fighter.myRotation.rot -= 5.0f;
    
    if(IsKeyDown(KEY_C)) camera.zoom *= 1.1;
    if(IsKeyDown(KEY_V)) camera.zoom /=1.1;
    
    gravity(fighter,rock);
    camera.target = (Vector2{(float)fighter.myKinematics.pos.x+20.0f,(float)fighter.myKinematics.pos.y+20.0f});
    
    if(fighter.checkCollision(rock)){
      std::cout<<"CRASH OF FUCK AHH"<< std::endl;
    }

      

    BeginDrawing();
    //delete the fighter.draw please
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);
    drawgrid();
    DrawCircle(500,500, 10, BLUE);
    
    doEverything(spaceList,options);
    DrawFPS(fighter.myKinematics.pos.x-50, fighter.myKinematics.pos.y-50);
    
    EndDrawing();

  }
  fighter.unload();
  rock.unload();
  CloseWindow();
}

