#include "raylib.h"
#include <string>
#include "raymath.h"

int player_score{0};
int player2_score{0};
int bounce{0};

Color Green = Color{38,185,154,255};
Color Blue = Color{51,151,224,88};


class Ball
{    
public:
    Rectangle pos;
    float radius;
    Vector2 speed;
protected:

private:
};

class Player
{
public:
    float speed;
    Rectangle pos;
    Vector2 target;
};


Rectangle p1_rec;

bool ChceckCollisionBall(Vector2 center, float radius,Rectangle rec)
{   // did ball enter is in rec
    if((center.x >= rec.x) && (center.x <= (rec.x + rec.width))&&
       (center.y >= rec.y) && (center.y <= (rec.y + rec.height)))
       {return true;}

       // closet point in rec to ball
       
}


int main()
{
    int windowsDimension[2];
    windowsDimension[0] = 1280;
    windowsDimension[1] = 800;

    Vector2 center {windowsDimension[0]/2,windowsDimension[1] /2};

Ball ball;
ball.pos.x = windowsDimension[0]/2;
ball.pos.y = windowsDimension[1]/2;
ball.radius = 20.f;
ball.speed.x = 10.f;
ball.speed.y = 10.f;


Player p1;
p1.pos.x =  windowsDimension[0] - 25;
p1.pos.y = windowsDimension[1]/2 - 100;
p1.pos.height = 200;
p1.pos.width = 25;
p1.speed = 10.f;

Player p2;
p2.pos.x = 0;
p2.pos.y = windowsDimension[1]/2 - 100;
p2.pos.height = 200;
p2.pos.width = 25;
p2.speed = 10.f;
p2.target.y = 0;


   


    // initilize window
    InitWindow(windowsDimension[0],windowsDimension[1],"Pong by Karol Jablonski");
    InitAudioDevice();

     // bounce sound
    Sound bounceS = LoadSound("Sounds/bounce.wav");
    Sound failS = LoadSound("Sounds/fail.wav");
    
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        DrawRectangle(0,0,windowsDimension[0]/2,windowsDimension[1],Green);
        DrawRectangle(windowsDimension[0]/2,0,windowsDimension[0]/2,windowsDimension[1],Blue);
        DrawRectangle(windowsDimension[0]/2 - 5,0,10,windowsDimension[1],WHITE);
        DrawCircleSector(center,100,0,360,4,WHITE);
        

        DrawCircle(ball.pos.x ,ball.pos.y , ball.radius ,BLACK);

        ball.pos.x += ball.speed.x ;
        ball.pos.y += ball.speed.y ;

        //Draw p1
        DrawRectangle(p1.pos.x,p1.pos.y,p1.pos.width,p1.pos.height,BLACK);
        //Draw p2
        DrawRectangle(p2.pos.x,p2.pos.y,p2.pos.width,p2.pos.height,BLACK);

       
        // p1 movement
        if(IsKeyDown(KEY_UP) && p1.pos.y > 0)
        p1.pos.y -= p1.speed;
        if(IsKeyDown(KEY_DOWN) && p1.pos.y <= (windowsDimension[1] - p1.pos.height))
        p1.pos.y += p1.speed;

        //p2 pos
        p2.pos.y = ball.pos.y - p2.pos.height/2;
        /* p2 movement
        if(IsKeyDown(KEY_W) && p2.pos.y > 0)
        p2.pos.y -= p2.speed;
        if(IsKeyDown(KEY_S) && p2.pos.y <= (windowsDimension[1] - p1.pos.height))
        p2.pos.y += p2.speed;

        */

        if(CheckCollisionCircleRec(Vector2{ball.pos.x,ball.pos.y},ball.radius,Rectangle{p1.pos.x,p1.pos.y,p1.pos.width,p1.pos.height}))
        {
            ball.speed.x *= -1;
            bounce++;
            PlaySound(bounceS);

        }
        if(CheckCollisionCircleRec(Vector2{ball.pos.x,ball.pos.y},ball.radius,Rectangle{p2.pos.x,p2.pos.y,p2.pos.width,p2.pos.height}))
        {
            ball.speed.x *= -1;
            bounce++;
            PlaySound(bounceS);
            
        }

        
        std::string p2Score = "Score: ";
        p2Score.append(std::to_string(player2_score));
        DrawText(p2Score.c_str(),windowsDimension[0] - 300,25,40,BLUE);
        std::string p1Score = "Score: ";
        p1Score.append(std::to_string(player_score));
        DrawText(p1Score.c_str(),100,25,40,GREEN);
        std::string BallBounce = "Bounce: ";
        BallBounce.append(std::to_string(bounce));
        DrawText(BallBounce.c_str(),windowsDimension[0]/2-80,25,40,BLACK);

        int tmp1 = 0;
        int tmp2 = 0;

        if(ball.pos.x >= p1.pos.x)
        {
            ball.speed.x *= -1;  
            player2_score++;
            PlaySound(failS);
            if(tmp2<player2_score)
            {
                tmp2++;
                ball.pos.x = windowsDimension[0]/2;
                ball.pos.y = windowsDimension[1]/2;
                ball.speed.x *= 1;
                bounce = 0;
            }
        }
        if (ball.pos.x <= 0)
        {
            player_score++;
            PlaySound(failS);
            if(tmp1 <player_score)
            {
                tmp1++;
                ball.pos.x = windowsDimension[0]/2;
                ball.pos.y = windowsDimension[1]/2;
                ball.speed.x *= -1;
                bounce = 0;
            }

        }
        if((player_score == 10) || (player2_score == 10))
        {
            
            player_score = 0;
            player2_score = 0;
            tmp1 = 0;
            tmp2 = 0;
        }


        if(ball.pos.x <= 0)
        ball.speed.x *= -1;        

        if(ball.pos.y <= 0)
        ball.speed.y *= -1;
        if(ball.pos.y >= windowsDimension[1])
        ball.speed.y *= -1;        

        EndDrawing();
        
    }

    UnloadSound(bounceS);
    CloseAudioDevice();
    return 0;


}
