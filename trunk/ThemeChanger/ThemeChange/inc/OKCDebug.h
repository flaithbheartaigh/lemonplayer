/*
 * OKCDebug.h
 *
 *  Created on: 2009-11-26
 *      Author: johnzeng
 */

#ifndef OKCDEBUG_H_
#define OKCDEBUG_H_

#ifndef DODEBUG
#define DODEBUG
#endif

#ifdef DODEBUG

#include <flogger.h>

_LIT( KLogsDir, "THCH");
_LIT( KLogFileName, "test.log");

#define __LOGSTR_TOFILE(S)     {_LIT(KTmpStr, S);RFileLogger::WriteFormat(KLogsDir(), KLogFileName(), EFileLoggingModeAppend, KTmpStr());}
#define __LOGSTR_TOFILE1(S, P) {_LIT(KTmpStr, S);RFileLogger::WriteFormat(KLogsDir(), KLogFileName(), EFileLoggingModeAppend, TRefByValue<const TDesC>(KTmpStr()),P);}
#define __LOGDES_TOFILE(S)     {RFileLogger::Write(KLogsDir(), KLogFileName(), EFileLoggingModeAppend, S);}
#else
#define __LOGSTR_TOFILE(S) ;
#define __LOGSTR_TOFILE1(S, P) ;
#define __LOGDES_TOFILE(S) ;
#endif /* DODEBUG */

#endif /* OKCDEBUG_H_ */
