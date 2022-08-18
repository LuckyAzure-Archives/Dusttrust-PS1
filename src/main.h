typedef enum
{
	GameLoop_Menu,
	GameLoop_Battle
} GameLoop;

extern GameLoop gameloop;

//Error handler
extern char error_msg[0x200];
void ErrorLock();

