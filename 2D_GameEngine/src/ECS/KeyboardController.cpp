#include "KeyboardController.h"

typedef Uint32(*SDL_NewTimerCallback)(Uint32 interval, void* param);

typedef struct
{
	SpriteComponent *sprite;
	SDL_TimerID timerId;
}ThreadData;

Uint32 WaitThreadFunc(Uint32 interval, void *data)
{
	ThreadData *tdata = (ThreadData*)data;
	tdata->sprite->play("idle");
	SDL_RemoveTimer(tdata->timerId);
	free(data);
	return 0;
}

void KeyboardController::WaitThreadCall(SpriteComponent *sprite)
{
	ThreadData *data = (ThreadData*)malloc(sizeof(ThreadData));
	data->sprite = sprite;
	data->timerId = SDL_AddTimer(1000, WaitThreadFunc, data);
}