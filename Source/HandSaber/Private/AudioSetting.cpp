#include "AudioSetting.h"
#include "HandSaberGameInstance.h"
#include "Components/Button.h"

bool UAudioSetting::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }

	if (!ensure(OpenAudioOptionButton != nullptr)) { return false; }
	OpenAudioOptionButton->OnClicked.AddDynamic(this, &UAudioSetting::OpenAudioSettings);
	OpenAudioOptionButton->OnHovered.AddDynamic(this, &UAudioSetting::HoveredAnim);
	OpenAudioOptionButton->OnUnhovered.AddDynamic(this, &UAudioSetting::UnHoveredAnim);

	return true;
}

void UAudioSetting::OpenAudioSettings()
{
	FTimerHandle Timer;
	FadeOutAnim();
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UAudioSetting::SendOpenRequest, 1.0f, false,
	                                       FadeOut->GetEndTime() - 0.7f);
}

void UAudioSetting::SendOpenRequest()
{
	if (auto const GameInstance = Cast<UHandSaberGameInstance>(GetGameInstance()))
	{
		GameInstance->Menu->AudioOptions();
	}
}


void UAudioSetting::HoveredAnim()
{
	PlayAnimation(Hovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 0.9f, false);
}

void UAudioSetting::UnHoveredAnim()
{
	PlayAnimation(UnHovered, 0.0f, 1, EUMGSequencePlayMode::Forward, 0.9f, false);
}

void UAudioSetting::FadeInAnim()
{
	PlayAnimation(FadeIn, 0.0f, 1, EUMGSequencePlayMode::Forward, 0.9f, false);
}

void UAudioSetting::FadeOutAnim()
{
	PlayAnimation(FadeOut, 0.0f, 1, EUMGSequencePlayMode::Forward, 3.f, false);
}
