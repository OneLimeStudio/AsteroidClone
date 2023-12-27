#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int SCORE = 0;

int NumberOfBullets = 1000;
int NumberOfAsteroids = 1000;


int AsteroidSpeed = 7;
int BulletSpeed = 10;


int widthAsteroid = 20;
int BulletSize = 10;
int PlayerSize = 30;


void SpawnProjectile(int , int);
typedef struct 
{
    float xPosition;
    float yPosition;
    bool active;
    Color color;

}Shoot;

typedef struct 
{
    float xPosition;
    float yPosition;
    bool active;
    Color color; 
}Asteroid;





int main(){

    Sound fire = LoadSound("fire.ogg");
    Shoot *Bullets = calloc(NumberOfBullets,sizeof(Shoot));
    Asteroid *Asteroids = calloc(NumberOfAsteroids,sizeof(Asteroid));
    int screenHeight = 400;
    int screenWidth = 600;
    
    

    InitWindow(screenWidth,screenHeight,"Game");
    SetTargetFPS(60);
    int Postion[2] = {screenWidth/2,screenHeight - 40};
    int Bool = 0;
    int counter = 0;
    int counterAsteroid = 0;
    int AsteroidCount = 0;
    while(!WindowShouldClose()){

        
        if (IsKeyDown(KEY_RIGHT)) Postion[0] += GetFrameTime() + 5.0f;
        if (IsKeyDown(KEY_LEFT)) Postion[0] -= GetFrameTime() + 5.0f;
        if (IsKeyDown(KEY_UP)) Postion[1] -= GetFrameTime() + 5.0f;
        if (IsKeyDown(KEY_DOWN)) Postion[1] += GetFrameTime() + 5.0f;
        
        //printf("%d %d", Postion[0],Postion[1]);  SpawnProjectile(Postion[0],Postion[1])
        AsteroidCount += 10;



        BeginDrawing();
            
            ClearBackground(RAYWHITE);
            
            if(Postion[1] > screenHeight -50){
                Postion[1] = screenHeight- 50;
            }else if(Postion[1] < 0 ){
                Postion[1] = 0;
            }else if(Postion[0] > screenWidth - 50){
                Postion[0] = screenWidth - 50;
            }else if(Postion[0] < 0){
                Postion[0] = 0;
            }

            if(IsKeyPressed(KEY_A)){
                //NumberOfBullets+= 10;
                //Shoot *Bullets = realloc(Bullets,(NumberOfBullets) * sizeof(Shoot));
                Bullets[counter].xPosition = Postion[0] + 25;
                Bullets[counter].yPosition = Postion[1] - 25;
                Bullets[counter].active = true;
                Bullets[counter].color = RED;
                DrawCircle(Bullets[counter].xPosition, Bullets[counter].yPosition, BulletSize,Bullets[counter].color);  
                PlaySound(fire);
                counter ++;                 

            }
           // printf("%d", Postion[0]);
            if(AsteroidCount % 150 == 0){
                int value = rand() % (screenWidth + 1);
                Asteroids[counterAsteroid].xPosition = value;
                Asteroids[counterAsteroid].yPosition = 0;
                Asteroids[counterAsteroid].active = true;
                Asteroids[counterAsteroid].color = RED;
                DrawRectangle(Asteroids[counterAsteroid].xPosition,Asteroids[counterAsteroid].yPosition,widthAsteroid,widthAsteroid,Asteroids[counterAsteroid].color);
                counterAsteroid ++;
            }
            
            
            for(int i = 0; i < counter;i++){
                
                if(Bullets[i].yPosition < -20){
                    Bullets[i].active = false;
                    
                }else{
                    Bullets[i].yPosition -= BulletSpeed;
                    //printf("%d\n",Bullets[i].xPosition);
                    DrawCircle(Bullets[i].xPosition, Bullets[i].yPosition, BulletSize, Bullets[i].color);

                }
            }
            for(int i = 0;i < counterAsteroid;i++){
                //Asteroids[i].yPosition += AsteroidSpeed;
                //DrawRectangle(Asteroids[i].xPosition,Asteroids[i].yPosition,widthAsteroid,widthAsteroid,Asteroids[i].color);
            
                if(Asteroids[i].yPosition > screenHeight+ 100){
                    Asteroids[i].active = false;
                    Asteroids[i].color = BLACK;
                }else{
                    Asteroids[i].yPosition += AsteroidSpeed;
                    //printf("%d\n",Bullets[i].xPosition);
                    DrawRectangle(Asteroids[i].xPosition,Asteroids[i].yPosition,widthAsteroid,widthAsteroid,Asteroids[i].color);
                } 
                   



            }
            
            DrawText(TextFormat("Score: %i",SCORE),0,20,25,BLACK);
            DrawRectangle(Postion[0],Postion[1],PlayerSize,PlayerSize,BLUE);
            //DrawLine(200,200,200,500,RED);
           /* 
            if(counterAsteroid == NumberOfAsteroids - 2){
                counterAsteroid = 0;
            }

        */
        for (int Bullet =0; Bullet < counter;Bullet++){
           if(Bullets[Bullet].active){
           
                for(int asteroid = 0;asteroid < counterAsteroid;asteroid++){
                    if(Asteroids[asteroid].active){
                      
                          if(CheckCollisionCircleRec((Vector2){Bullets[Bullet].xPosition,Bullets[Bullet].yPosition},BulletSize,(Rectangle){Asteroids[asteroid].xPosition,Asteroids[asteroid].yPosition,widthAsteroid,widthAsteroid})){
                                Asteroids[asteroid].color = RAYWHITE;
                                Bullets[Bullet].color = RAYWHITE;

                                printf("COLLISON\n"); 
                                Asteroids[asteroid].active = false;
                                Bullets[Bullet].active = false;
                                SCORE ++;
                        }

                    }
                }
            }
        }
        for(int asteroid = 0;asteroid < counterAsteroid;asteroid++){

            if(CheckCollisionRecs((Rectangle){Postion[0],Postion[1],PlayerSize,PlayerSize}, (Rectangle){Asteroids[asteroid].xPosition,Asteroids[asteroid].yPosition,widthAsteroid,widthAsteroid}) && Asteroids[asteroid].active == true){
                SCORE = 0;
                Asteroids[asteroid].color = RAYWHITE;
                Asteroids[asteroid].active = false;
            }


        }
        
   

        EndDrawing();

    }

    UnloadSound(fire);
    CloseWindow();
    CloseAudioDevice();
    return 0;
}

void SpawnProjectile(int x,int y){
    DrawCircle(x,y+50,10,RED);
}