#include<raylib.h>
#include<print>                         //needed to format string [ONLY WORKS IN C++ 23 STANDARD or above]
#include<string>

using std::string;
using std::format;

const int win_width = 800;              //sets window width and height
const int win_height = 800;

class ball{         //the ball in shm  
    public:
        float acceleration, speed, x, y, radius, shm_k;

        ball(float r, float k){
            radius = r;
            shm_k = k;
            speed = 0;
            x = win_width/2;
            y = win_height/2;
        }

        void drawball();            //draws the ball each frame
        void move_ball();           //moves the ball away from the mean pos^n  using arrow keys
        void execute_shm();         //executes shm when arrow key is released
        void bring_ball_back();     //moves the ball back to the mean position
};

void ball::drawball(){
    DrawCircle(x, y, radius, RED);
}

void ball::move_ball(){
    if(IsKeyDown(KEY_RIGHT) && x < (win_width - radius))      //key should be pressed and the balls' position should be                          
        x += 300 * GetFrameTime();       
    if(x > (win_width - radius))
        x = win_width - radius;                               //between the ends of the window
    if(IsKeyDown(KEY_LEFT) && x > radius)
        x -= 300 * GetFrameTime();  
    if(x < radius)
        x = radius;                                           //moves the ball at 300 pixels per second 
}                                                             //so it moves 300*the time spent in each frame, every frame

void ball::execute_shm(){                                   
    
    if(x <= (win_width-radius) && x >= radius){               //executes shm if ball is inside the window   
        acceleration = -(x - win_width/2) * shm_k;          
        speed += acceleration * GetFrameTime();             //computes the acceleration, speed, position in each frame
        x += speed * GetFrameTime();
    }
}

void ball::bring_ball_back(){
    if(IsKeyDown(KEY_I)){
        x = win_width/2;
        speed = 0;
    }
}

int main(){
    InitWindow(win_width, win_height, "SIMPLE HARMONIC MOTION");
    SetTargetFPS(144);   
    ball b(50, 10);                                                 //ball instatiated of radius 50 pixels, and k=10
    string str;

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        DrawFPS(10, 20);
        str = format("acceleration = k * x = {}x \nacceleration = {} \nspeed = {} \npos_x = {}", b.shm_k, b.acceleration, b.speed, b.x-win_width/2);
        DrawText(str.c_str(), 5, 50, 30,ORANGE);
        DrawText("PRESS 'I' TO BRING THE BALL TO THE INITIAL POSITION", 100, 700, 20, GRAY);
        DrawText("*Speed in pixels/second, position in pixels in x-axis", 6, win_height-20, 15, GRAY);  
        b.drawball();              //draws the ball and 
        b.move_ball();             //moves the ball to a position using arrow keys
        if(!(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT)))              //executes shm only if ball is not getting moved 
            b.execute_shm();                                            //by arrow keys
            b.bring_ball_back();
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}