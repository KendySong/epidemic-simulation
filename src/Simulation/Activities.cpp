#include "Activities.hpp"

std::string getString(Activities a)
{
	switch (a)
	{
	case Activities::Sleep:
		return "Sleep";
		break;

	case Activities::Home:
		return "Home";
		break;

	case Activities::Work:
		return "Work";
		break;

	case Activities::Entertainment:
		return "Entertainment";
		break;

	default:
	case Activities::Undefined:
		return "Undefined";
		break;
	}
}