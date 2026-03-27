#include<raylib.h>
#include<cstdlib>
#include<cmath>

const Color color = {12, 1, 56};
const int win_width = 800;
const int win_height = 800;                                        //change parameters of the simulation from here
const int no_of_balls = 100;                                        //everything in pixels
const int fps = 144;
const float radius_of_each_ball = 20;

//vector operations on the position, velocity of particles
typedef struct{
    static float magnitude(Vector2 v){   
        using std::pow;
        using std::sqrt;                                   
        return (sqrt(pow(v.x, 2) + pow(v.y, 2)));                        
    }
    static Vector2 subtract(Vector2 v2, Vector2 v1){
        return {v2.x - v1.x, v2.y - v1.y};
    }
    static Vector2 add(Vector2 v1, Vector2 v2){
        return {v1.x + v2.x, v1.y + v2.y};
    }
    static float dotproduct(Vector2 v1, Vector2 v2){
        return ((v1.x * v2.x) + (v1.y * v2.y));
    }
    static Vector2 unitvector(Vector2 v){
        float mag = magnitude(v);
        if(mag == 0) mag = 0.001f;
        return {v.x/mag, v.y/mag};
    }
    static Vector2 multiplywithscalar(float d, Vector2 v){
        return {d * v.x, d * v.y};
    }
}v;

//the particles
class ball{
    public:
        float radius;
        Color color;
        Vector2 centre, speed;

        static Color setcolor();
        ball(){
            speed.x = GetRandomValue(-500, 500) + 1;
            speed.y = GetRandomValue(-500, 500) + 1;
            radius = radius_of_each_ball;
            color = setcolor();
            centre = {0, 0};
        }
        void draw();
        void move();
        static void check_for_collisions(ball*);
};

void ball::draw(){
    DrawCircle(centre.x, centre.y, radius, color);
}

//checks for collision with the wall and reverses the velocity accordingly
//brings ball back to frame if outside
void ball::move(){
    centre.x += speed.x*GetFrameTime();
    centre.y += speed.y*GetFrameTime();
    if(centre.x <= radius){
        centre.x = radius;
        speed.x = -speed.x;
    }
    if(centre.x >= win_width - radius){
        centre.x = win_width - radius;
        speed.x = -speed.x;                                        
    }                                                              
    if(centre.y <= radius){
        centre.y = radius;
        speed.y = -speed.y;                                         
    }
    if(centre.y >= win_height - radius){
        centre.y = win_height - radius;
        speed.y = -speed.y;
    }
}

//checks collisions among balls
void ball::check_for_collisions(ball* ball){
    for(int i = 0; i < no_of_balls; ++i){
        for(int j = i + 1; j < no_of_balls; ++j){ //no duplicate pairs
            //checks if the balls are in contact or not(also when they overlap)
            if(CheckCollisionCircles(ball[i].centre, ball[i].radius, ball[j].centre, ball[j].radius)){
                
                //unit vector from ball[i] ---> ball[j]
                Vector2 unit_disp = v::unitvector(v::subtract(ball[j].centre, ball[i].centre));

                //relative velocity of ball[i] W.R.T ball[j]
                //i.e., velocity of ball[i] in a frame in which ball[j] is at rest                                  //draw a diagram in the frame of reference of
                Vector2 rel_vel = v::subtract(ball[i].speed, ball[j].speed);                                        //ball[j] to understand this function better
                
                //displacement vector from ball[i] ===> ball[j]
                float disp = v::magnitude(v::subtract(ball[j].centre, ball[i].centre));
                                                                                                    
                //calculates the component of velocity of rel_vel along unit_disp
                float bounce_vel = v::dotproduct(rel_vel, unit_disp);

                //checks if the balls overlap
                //if they do, move them outwards
                if(((ball[i].radius + ball[j].radius) - disp) > 0.0){
                    Vector2 overlap = v::multiplywithscalar(((ball[i].radius + ball[j].radius) - disp) / 2, unit_disp);
                    v::subtract(ball[i].centre, overlap);
                    v::add(ball[j].centre, overlap);
                }
                
                //if bounce_vel > 0 balls are colliding, if not theyr'e moving away
                if(bounce_vel >= 0){
                    ball[i].speed = v::subtract(ball[i].speed, v::multiplywithscalar(bounce_vel, unit_disp));
                    ball[j].speed = v::add(ball[j].speed, v::multiplywithscalar(bounce_vel, unit_disp));
                }               
            }
        }
    }
}                                                                                                                           

//a random color for every ball
Color ball::setcolor(){
    switch(GetRandomValue(0, 6)){
        case 0:
            return GREEN;
            break;
        case 1:
            return YELLOW;
            break;
        case 2:
            return BLUE;
            break;
        case 3:                                                 
            return PINK;
            break;
        case 4:
            return PURPLE;
            break;
        case 5:
            return RED;
            break;
        default:
            return BROWN;
    }
    //not setting a random color between 0-255 because it also includes the background color
}

int main(){

    InitWindow(win_width, win_height, "collisions");
    SetTargetFPS(fps);

    //allocate on heap for large no. of particles, > 100,000
    ball b[no_of_balls];

    //the event loop
    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(color);
            DrawFPS(20, 20);
            //draws and moves every circle
            for(int i = 0; i < no_of_balls; ++i){
                b[i].draw();
                if(!IsKeyDown(KEY_SPACE))
                    b[i].move();
            }
            if(!IsKeyDown(KEY_SPACE))
                ball::check_for_collisions(b);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
