#include "betaFuncs.h"

IBetaFunction* getBeta(eBetaFunction bf)
{
	switch (bf)
	{
	case eBetaFunction::Null: return 0;
		break;
	case eBetaFunction::FletcherReeves: return new Fletcher;
		break;
	case eBetaFunction::PolakRibiere: return new Polak;
		break;
	case eBetaFunction::HestenesStiefel: return new Hestenes;
		break;
	}
}
