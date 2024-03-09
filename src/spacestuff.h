#define SPACESTUFF_H
#include "raylib.h"


extern int test(){

  return 1;
}

class spaceStuff{

  private:
    int mass;
    Texture2D texture;
    float textureWidth,textureHeight;
    Vector2 origin;
public: 
    struct kinematics {Vector2 acc;Vector2 vel;Vector2 pos;} myKinematics;
    struct rotation {float rot;float rotVel; float rotAcc;} myRotation;

    spaceStuff(const char *pathToFile,rotation inRotation,kinematics inKinematics){
    
    texture = LoadTexture(pathToFile);

    textureWidth = texture.width;
    textureHeight= texture.height;
    origin = { textureWidth / 2, textureHeight / 2 }; // Center of the texture
    myKinematics=inKinematics;
    myRotation=inRotation;
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

void gravity(spaceStuff & stuff,Vector2 origin){
  //origin.x=250;
  //origin.y=250;
  Vector2 delta={origin.x-stuff.myKinematics.pos.x,origin.y-stuff.myKinematics.pos.y};
  float magnitude=5/sqrt((delta.x*delta.x)+(delta.y*delta.y));
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

