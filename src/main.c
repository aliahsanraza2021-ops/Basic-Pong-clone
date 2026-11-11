#include "raylib.h"
// utility header for SearchAndSetResourceDir
#include "resource_dir.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PADDLE_WIDTH 20
#define PADDLE_HEIGHT 100

	
void movementPaddle1(float* rec);
void movementPaddle2(float* rec);
void wallCollision1(float* rec);
void wallCollision2(float* rec, float* acceletration);
int main ()
{


		
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,"Pong");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	Rectangle rec1= {
		0,0,PADDLE_WIDTH,PADDLE_HEIGHT};

	Rectangle rec2= {
		SCREEN_WIDTH-PADDLE_WIDTH,0,PADDLE_WIDTH,PADDLE_HEIGHT};
		
	Rectangle ball={
		SCREEN_WIDTH/2,(SCREEN_WIDTH/2)-100,4,4
	};

	int ballAccelerationx=5;
	float ballAccelerationy=-1;

	float* yaxis1;
	yaxis1 =&rec1.y;

	float* yaxis2;
	yaxis2 = &rec2.y;

	float* ballyaxis;
	ballyaxis = &ball.y;
	
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		
		movementPaddle1(yaxis1);
		
		
		movementPaddle2(yaxis2);

		

		wallCollision1(yaxis1);
		wallCollision1(yaxis2);
		wallCollision2(ballyaxis,&ballAccelerationy);
		//movement code rec2

		//collision function
		ball.x-=ballAccelerationx;
		ball.y+=ballAccelerationy;
		if(CheckCollisionRecs(rec1,ball)){
			ballAccelerationx*=-1;
			ballAccelerationy+=GetRandomValue(-2,2);
		}


		if(CheckCollisionRecs(rec2,ball)){
			ballAccelerationx*=-1;
			ballAccelerationy+=GetRandomValue(-2,2);

		}

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		DrawRectangleRec(rec1,RED);

		DrawRectangleRec(rec2,BLUE);

		DrawCircle(ball.x,ball.y,4*4,WHITE);

		EndDrawing();
	}


	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

void movementPaddle1(float* rec){

	//movement code rec1
		if(IsKeyDown(KEY_S)){
			*rec +=10;
		}

		if(IsKeyDown(KEY_W)){
			*rec-=10;
		}

}

void movementPaddle2(float* rec){

	if(IsKeyDown(KEY_DOWN)){
			*rec+=10;
	}

	if(IsKeyDown(KEY_UP)){
			*rec-=10;
	}


}

void wallCollision1(float* rec){

	if(*rec<=0){
		*rec =0;
		}

		if(*rec >=SCREEN_HEIGHT-PADDLE_HEIGHT){
			*rec =SCREEN_HEIGHT-PADDLE_HEIGHT;
		}

}

void wallCollision2(float* rec, float* acceleration){

	if(*rec<=0){
		*rec=0;
		*acceleration +=GetRandomValue(0,5);
	}

	if(*rec >=SCREEN_HEIGHT-4){

			*rec =SCREEN_HEIGHT-4;
			*acceleration -=GetRandomValue(0,5);
	}

}
