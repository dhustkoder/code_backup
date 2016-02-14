#include <stdio.h>
#include <stdlib.h>



// MANUAL POLYMORPHISM WITH C

typedef struct iRenderer
{
	void(*Render)(int x, int y);
	void(*Dispose)();



}iRenderer;



typedef struct iInput
{
	void(*GetKey)(struct iInput *self,int x);
	void(*Dispose)(struct iInput *self);



}iInput;


void SDL_Input_GetKey(iInput *self, int x)
{
	printf("getting key from SDL_INPUT_GETKEY, key == %i\n", x);
}
void SDL_Input_Dispose(iInput *self)
{
	printf("Disposing of SDL_Input\n");

	//free(self);
}

void GFLW_Input_GetKey(iInput *self, int x)
{
	printf("getting key from GFLW_INPUT_GETKEY, key == %i\n", x);
	
}

void GFLW_Input_Dispose(iInput *self)
{
	printf("Disposing of GFLW_Input\n");
	//free(self);
}





void Init_SDL_Input(iInput **input)
{
	(*input) = (iInput*) malloc (sizeof(iInput));
	(*input)->GetKey = &SDL_Input_GetKey;
	(*input)->Dispose = &SDL_Input_Dispose;

}


void Init_GFLW_Input(iInput **input)
{
	(*input) = (iInput*) malloc(sizeof(iInput));
	(*input)->GetKey = &GFLW_Input_GetKey;
	(*input)->Dispose = &GFLW_Input_Dispose;
}







typedef struct GAME
{
	iRenderer *renderer_;	
	iInput *input_;
	

}GAME;



int main()
{

	
	GAME game;
	begin:
	{
		Init_SDL_Input(&game.input_);	

		game.input_->GetKey(game.input_, 10);
		game.input_->Dispose(game.input_);


		Init_GFLW_Input(&game.input_);

		game.input_->GetKey(game.input_, 20);
		game.input_->Dispose(game.input_);
	}
	goto begin;





}
