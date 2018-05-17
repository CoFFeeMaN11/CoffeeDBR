#ifndef _BETA_FUNS_H_
#define _BETA_FUNS_H_
#include "fletcherReeves.h"
#include "polak.h"
#include "hestenes.h"
enum eBetaFunction
{
	Null,
	FletcherReeves,
	PolakRibiere,
	HestenesStiefel,
};
IBetaFunction* getBeta(eBetaFunction bf);
#endif // !_BETA_FUNS_H_

