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

int main(){
    InitWindow(0, 0, "Rotating Image around Center");
    SetTargetFPS(60);
    
    //spaceStuff fighter("./Red_Fighter.png", {0.0,0.0,0.00}, {{0.0,0.0},{0.0,0.0},{0.0,0.0}} );
    
    spaceStuff fighter("/mnt/c/Users/0hmse/Documents/TieFighter.png", {0.0,0.0,0.00}, {{0.0,0.0},{0.0,0.0},{0.0,0.0}} );
    Camera2D camera = {0};
    camera.target = (Vector2{(float)fighter.myKinematics.pos.x+20.0f,(float)fighter.myKinematics.pos.y+20.0f});
    camera.offset = (Vector2){(float) GetScreenWidth()/2.0f,(float) GetScreenHeight()/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    while (!WindowShouldClose()) {
    fighter.animate();
    if (IsKeyDown(KEY_D)) fighter.myKinematics.vel.x += 0.55f;
    if (IsKeyDown(KEY_A)) fighter.myKinematics.vel.x-= 0.55f;
    if (IsKeyDown(KEY_W)) fighter.myKinematics.vel.y -= 0.55f;
    if (IsKeyDown(KEY_S)) fighter.myKinematics.vel.y  += 0.55f;

    if (IsKeyDown(KEY_E)) fighter.myRotation.rot += 5.0f;
    if (IsKeyDown(KEY_Q)) fighter.myRotation.rot -= 5.0f;
 //fighter.myKinematics.vel.x+=100/((250-fighter.myKinematics.pos.x)*(250-fighter.myKinematics.pos.x));
//fighter.myKinematics.vel.y+=100/((250-fighter.myKinematics.pos.y)*(250-fighter.myKinematics.pos.y));
    gravity(fighter, {500,500});
    camera.target = (Vector2{(float)fighter.myKinematics.pos.x+20.0f,(float)fighter.myKinematics.pos.y+20.0f});
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);
    drawgrid();
    DrawCircle(500,500, 10, BLUE);
    fighter.draw();
    EndDrawing();

  }
  fighter.unload();
  CloseWindow();
}

