#include "psx.h"

typedef u32* IO_Data;

//IO constants
#define IO_SECT_SIZE 2048

//IO functions
void IO_Init(void);
void IO_Quit(void);
void IO_FindFile(CdlFILE *file, const char *path);
void IO_SeekFile(CdlFILE *file);
IO_Data IO_ReadFile(CdlFILE *file);
IO_Data IO_AsyncReadFile(CdlFILE *file);
IO_Data IO_Read(const char *path);
IO_Data IO_AsyncRead(const char *path);
boolean IO_IsSeeking(void);
boolean IO_IsReading(void);
