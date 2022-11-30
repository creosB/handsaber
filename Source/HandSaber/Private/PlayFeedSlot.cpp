#include "PlayFeedSlot.h"
#include "HandSaberGameInstance.h"
#include "Components/Button.h"

bool UPlayFeedSlot::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }

	if (!ensure(OpenSongListButton != nullptr)) { return false; }
	OpenSongListButton->OnClicked.AddDynamic(this, &UPlayFeedSlot::OpenPlayFeedSlot);
	OpenSongListButton->OnHovered.AddDynamic(this, &UPlayFeedSlot::HoveredAnim);
	OpenSongListButton->OnUnhovered.AddDynamic(this, &UPlayFeedSlot::UnHoveredAnim);

	return true;
}


void UPlayFeedSlot::OpenPlayFeedSlot()
{
	FTimerHandle Timer;
	FadeOutAnim();
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UPlayFeedSlot::SendOpenRequest, 1.0f, false,
	                                       FadeOut->GetEndTime() - 0.7f);
}

void UPlayFeedSlot::SendOpenRequest()
{
	if (auto const GameInstance = Cast<UHandSaberGameInstance>(GetGameInstance()))
	{
		GameInstance->Menu->OpenSongList();
		FadeInAnim();
	}
}


void UPlayFeedSlot::HoveredAnim()
{
	PlayAnimation(Hovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 0.9f, false);
}

void UPlayFeedSlot::UnHoveredAnim()
{
	PlayAnimation(UnHovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 0.9f, false);
}

void UPlayFeedSlot::FadeInAnim()
{
	PlayAnimation(FadeIn, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f, false);
}

void UPlayFeedSlot::FadeOutAnim()
{
	PlayAnimation(FadeOut, 0.0f, 1, EUMGSequencePlayMode::Forward, 3.f, false);
}
