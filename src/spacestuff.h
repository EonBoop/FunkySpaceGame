#define SPACESTUFF_H
#include "raylib.h"
#include "string"
#include <cmath>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <math.h>
#include <iostream>
#include "json.hpp"
#include <fstream>

//class spaceStuff{

//  private:
  //  Texture2D texture;
    //float textureWidth,textureHeight;
    //Vector2 origin;
//public: 
  //  struct kinematics {Vector2 acc;Vector2 vel;Vector2 pos;} myKinematics;
   // struct rotation {float rot;float rotVel; float rotAcc;} myRotation;
    //int mass;

    //spaceStuff(const char *pathToFile,rotation inRotation,kinematics inKinematics, int inmass){
    
    //texture = LoadTexture(pathToFile);

    //textureWidth = texture.width;
    //textureHeight= texture.height;
    //origin = { textureWidth / 2, textureHeight / 2 }; // Center of the texture
    //myKinematics=inKinematics;
    //myRotation=inRotation;
    //mass=inmass;
 //};

   // void unload(){
    //UnloadTexture(texture);
    //return;
  //}
    //void draw(){

      //DrawTexturePro(texture,{0.0f,0.0f,textureWidth,textureHeight}, {myKinematics.pos.x,myKinematics.pos.y,textureWidth,textureHeight},origin,myRotation.rot , WHITE);
    //return;
  //};  
    //void animate(){
      //myKinematics.vel.x+=myKinematics.acc.x;
      //myKinematics.vel.y+=myKinematics.acc.y;
      //myKinematics.pos.x+=myKinematics.vel.x;
      //myKinematics.pos.y+=myKinematics.vel.y;
      
     // myRotation.rotVel+=myRotation.rotAcc;
      //myRotation.rot+=myRotation.rotVel;
      //return;
    //};

//};

//class background: public spaceStuff{
  
  //private:

  //public:

//};
//void gravity(spaceStuff & stuff,Vector2 origin){
//  Vector2 delta={origin.x-stuff.myKinematics.pos.x,origin.y-stuff.myKinematics.pos.y};
//  if (delta.x==0){delta.x=.1;};
  //if (delta.y==0){delta.y=.1;};
  //float magnitude=15/sqrt((delta.x*delta.x)+(delta.y*delta.y));
  //float angle=atanf(delta.x/delta.y);
  
//  if (delta.y>0){
 // stuff.myKinematics.vel.x+=magnitude*sinf(angle);
  //stuff.myKinematics.vel.y+=magnitude*cosf(angle);
  //}
  //else {
  //stuff.myKinematics.vel.x-=magnitude*sinf(angle);
  //stuff.myKinematics.vel.y-=magnitude*cosf(angle);
  //}
  
//}

//I don't think we can use pointers to pass back up the stack
nlohmann::json loadJSON (const std::string& filepath){
  //this needs error handling

  std::ifstream file(filepath,std::ios::in);
  if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filepath << std::endl;
        return nullptr;
    }

  nlohmann::json data = nlohmann::json::parse(file);
  

    if (!data.is_object()) {
        std::cerr << "Error: Invalid JSON format. Expected an object." << std::endl;

        return nullptr;
      }
  return data;
}

class spaceStuffLoaded{

  private:
    Texture2D texture;
    Vector2 origin;
    float textureWidth,textureHeight;

public: 
    struct kinematics {Vector2 acc;Vector2 vel;Vector2 pos;} myKinematics;
    struct rotation {float rot;float rotVel; float rotAcc;} myRotation;
    int mass;
    float textureRadius;

    Vector2 boundryBox[]; //boundryBox[0] should equal the number of elements in boundryBox
    spaceStuffLoaded(const nlohmann::json& jsonData){
   
    std::string pathToFile=jsonData.at("filepath");

    texture = LoadTexture(pathToFile.c_str());

    textureWidth = texture.width;
    textureHeight= texture.height;
    textureRadius = std::sqrt(textureHeight*textureHeight+textureWidth*textureWidth);
    origin = { textureWidth / 2, textureHeight / 2 }; // Center of the texture
    myKinematics={{jsonData.at("accx"),jsonData.at("accy")},{jsonData.at("velx"),jsonData.at("vely")},{jsonData.at("posx"),jsonData.at("posy")}};
    myRotation={jsonData.at("rotpos"),jsonData.at("rotvel"),jsonData.at("rotacc")};
    mass=jsonData.at("mass");
   // Vector2 fuck =jsonData.at("hitBox");
    //Vector2 hitBox[999];

      //hitBox[0]=fuck;
 };
    void unload(){
    UnloadTexture(texture);
    return;
  }
    void draw(){

      DrawTexturePro(texture,{0.0f,0.0f,textureWidth,textureHeight}, {myKinematics.pos.x,myKinematics.pos.y,textureWidth,textureHeight},origin,myRotation.rot , WHITE);
    return;
  };  
    void animate(){
      myKinematics.vel.x+=myKinematics.acc.x;
      myKinematics.vel.y+=myKinematics.acc.y;
      myKinematics.pos.x+=myKinematics.vel.x;
      myKinematics.pos.y+=myKinematics.vel.y;
      
      myRotation.rotVel+=myRotation.rotAcc;
      myRotation.rot+=myRotation.rotVel;
      return;
    };
    bool checkCollision(spaceStuffLoaded& otherObject){
    float deltax = abs(otherObject.myKinematics.pos.x-myKinematics.pos.x);
    float deltay = abs(otherObject.myKinematics.pos.y-myKinematics.pos.y);
    float delta = sqrt(deltax*deltax+deltay*deltay);
    
    if (delta<(textureRadius+otherObject.textureRadius)){
      for (int i = 0; i < boundryBox[0].x; i++) {
        if (CheckCollisionPointPoly(boundryBox[i],otherObject.boundryBox,otherObject.boundryBox[0].x)){
          return 1;
        }
      } 
    //we have the point of impact and both of their centers of mass. that can be used for directionality
    }
    return 0;
  }

};


void gravity(spaceStuffLoaded & stuff,spaceStuffLoaded & anchor){
  Vector2 delta={anchor.myKinematics.pos.x-stuff.myKinematics.pos.x,anchor.myKinematics.pos.y-stuff.myKinematics.pos.y};
  if (delta.x==0){delta.x=.1;};
  if (delta.y==0){delta.y=.1;};
  float magnitude=anchor.mass/sqrt((delta.x*delta.x)+(delta.y*delta.y)); //magnitude of acceleration not force
  float angle=atanf(delta.x/delta.y);
  
  if (delta.y>0){
  stuff.myKinematics.vel.x+=magnitude*sinf(angle);
  stuff.myKinematics.vel.y+=magnitude*cosf(angle);
  }
  else {
  stuff.myKinematics.vel.x-=magnitude*sinf(angle);
  stuff.myKinematics.vel.y-=magnitude*cosf(angle);
  }
  
}
