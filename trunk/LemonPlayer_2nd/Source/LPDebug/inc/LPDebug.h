#ifndef BWDEBUG_H
#define BWDEBUG_H

#ifndef EMULATOR
#define EMULATOR
#endif

#ifndef DODEBUG
#define DODEBUG
#endif

#ifdef DODEBUG
#include "FileLogger.h"
#define DEBUG(code) code;
#define DEBUGLOG( aFileLoggerPtr, aSentence) aFileLoggerPtr->WriteStream(aSentence);
#else
#define DEBUG(code) ;
#define DEBUGLOG( aFileLoggerPtr, aSentence ) ;
#endif


#endif//BWDEBUG_H