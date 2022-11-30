#include "PatchNotesSlot.h"
#include "HandSaberGameInstance.h"
#include "Components/Button.h"

bool UPatchNotesSlot::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }

	if (!ensure(NotesButton != nullptr)) { return false; }
	NotesButton->OnClicked.AddDynamic(this, &UPatchNotesSlot::PatchNotesSlot);
	NotesButton->OnHovered.AddDynamic(this, &UPatchNotesSlot::HoveredAnim);
	NotesButton->OnUnhovered.AddDynamic(this, &UPatchNotesSlot::UnHoveredAnim);
	return true;
}

void UPatchNotesSlot::PatchNotesSlot()
{
	FTimerHandle Timer;
	FadeOutAnim();
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UPatchNotesSlot::OpenNotesRequest, 1.0f, false,
										   FadeOut->GetEndTime() - 0.7f);
}

void UPatchNotesSlot::OpenNotesRequest()
{
	if (auto const GameInstance = Cast<UHandSaberGameInstance>(GetGameInstance()))
	{
		GameInstance->Menu->PatchNotes();
		FadeInAnim();
	}
}


void UPatchNotesSlot::HoveredAnim()
{
	PlayAnimation(Hovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 0.9f, false);
}

void UPatchNotesSlot::UnHoveredAnim()
{
	PlayAnimation(UnHovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 0.9f, false);
}

void UPatchNotesSlot::FadeInAnim()
{
	PlayAnimation(FadeIn, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f, false);
}

void UPatchNotesSlot::FadeOutAnim()
{
	PlayAnimation(FadeOut, 0.0f, 1, EUMGSequencePlayMode::Forward, 3.f, false);
}
