/*
 * qPlatform.h
 *
 *  Created on: 2010-7-1
 *      Author: johnzeng
 */

#ifndef QPLATFORM_H_
#define QPLATFORM_H_

#include <e32math.h>

#define qMin(a,b) ((a)<(b)?(a):(b))
#define qMax(a,b) ((a)>(b)?(a):(b))
		
typedef TReal qreal;

inline qreal qSin(const qreal& a)
	{
	qreal re;
	Math::Sin(re,a);
	return re;
	}

inline qreal qCos(const qreal& a)
	{
	qreal re;
	Math::Cos(re,a);
	return re;
	}

inline qreal qAsin(const qreal& a)
	{
	qreal re;
	Math::ASin(re,a);
	return re;
	}

inline qreal qAcos(const qreal& a)
	{
	qreal re;
	Math::ACos(re,a);
	return re;
	}

inline qreal qPow(const qreal& aSrc,const qreal& aPower)
	{
	qreal re;
	Math::Pow(re,aSrc,aPower);
	return re;
	}

inline qreal sqrt(const qreal& a)
	{
	qreal re;
	Math::Sqrt(re,a);
	return re;
	}

inline qreal qFabs(const qreal& a)
	{
	return a>0?a:-a;
	}

#endif /* QPLATFORM_H_ */
