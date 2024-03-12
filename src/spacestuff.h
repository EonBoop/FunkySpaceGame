#define SPACESTUFF_H
#include "raylib.h"
#include "string"
#include <cmath>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <math.h>
#include <iostream>

class spaceStuff{

  private:
    Texture2D texture;
    float textureWidth,textureHeight;
    Vector2 origin;
public: 
    struct kinematics {Vector2 acc;Vector2 vel;Vector2 pos;} myKinematics;
    struct rotation {float rot;float rotVel; float rotAcc;} myRotation;
    int mass;

    spaceStuff(const char *pathToFile,rotation inRotation,kinematics inKinematics, int inmass){
    
    texture = LoadTexture(pathToFile);

    textureWidth = texture.width;
    textureHeight= texture.height;
    origin = { textureWidth / 2, textureHeight / 2 }; // Center of the texture
    myKinematics=inKinematics;
    myRotation=inRotation;
    mass=inmass;
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

};

class ship: public spaceStuff{
  
  private:

  public:

};

void gravity(spaceStuff & stuff,spaceStuff & anchor){
  Vector2 delta={anchor.myKinematics.pos.x-stuff.myKinematics.pos.x,anchor.myKinematics.pos.y-stuff.myKinematics.pos.y};
  if (delta.x==0){delta.x=.1;};
  if (delta.y==0){delta.y=.1;};
  float magnitude=stuff.mass*anchor.mass/sqrt((delta.x*delta.x)+(delta.y*delta.y));
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

