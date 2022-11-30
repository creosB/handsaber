#include "GraphicSettings.h"
#include "HandSaberGameInstance.h"
#include "Components/Button.h"

bool UGraphicSettings::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }

	if (!ensure(OpenGraphicsOptionButton != nullptr)) { return false; }
	OpenGraphicsOptionButton->OnClicked.AddDynamic(this, &UGraphicSettings::OpenGraphicSettings);
	OpenGraphicsOptionButton->OnHovered.AddDynamic(this, &UGraphicSettings::HoveredAnim);
	OpenGraphicsOptionButton->OnUnhovered.AddDynamic(this, &UGraphicSettings::UnHoveredAnim);
	return true;
}


void UGraphicSettings::OpenGraphicSettings()
{
	FTimerHandle Timer;
	FadeOutAnim();
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UGraphicSettings::SendOpenRequest, 1.0f, false,
	                                       FadeOut->GetEndTime() - 0.7f);
}

void UGraphicSettings::SendOpenRequest()
{
	if (auto const GameInstance = Cast<UHandSaberGameInstance>(GetGameInstance()))
	{
		GameInstance->Menu->GraphicOptions();
	}
}


void UGraphicSettings::HoveredAnim()
{
	PlayAnimation(Hovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 0.9f, false);
}

void UGraphicSettings::UnHoveredAnim()
{
	PlayAnimation(UnHovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 0.9f, false);
}

void UGraphicSettings::FadeInAnim()
{
	PlayAnimation(FadeIn, 0.0f, 1, EUMGSequencePlayMode::Forward, 0.9f, false);
}

void UGraphicSettings::FadeOutAnim()
{
	PlayAnimation(FadeOut, 0.0f, 1, EUMGSequencePlayMode::Forward, 3.f, false);
}
