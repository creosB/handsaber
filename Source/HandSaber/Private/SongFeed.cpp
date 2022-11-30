
#include "SongFeed.h"
#include "SongList.h"
#include "Components/Button.h"

bool USongFeed::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }

	if (!ensure(SongList != nullptr)) { return false; }

	return true;
}