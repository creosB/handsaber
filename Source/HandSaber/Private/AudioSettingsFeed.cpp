#include "AudioSettingsFeed.h"

#include "AudioDevice.h"
#include "HandSaberGameInstance.h"
#include "HandSaberSaveGame.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

bool UAudioSettingsFeed::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }

	if (!ensure(MasterVolume != nullptr)) { return false; }
	MasterVolume->OnValueChanged.AddDynamic(this, &UAudioSettingsFeed::SaveMusicSettings);
	MasterVolume->MinValue = 0.01f;
	MasterVolume->MaxValue = 1.0f;
	if (!ensure(MusicVolume != nullptr)) { return false; }
	MusicVolume->OnValueChanged.AddDynamic(this, &UAudioSettingsFeed::SaveMusicSettings);
	MusicVolume->MinValue = 0.01f;
	MusicVolume->MaxValue = 1.0f;

	return true;
}

void UAudioSettingsFeed::SaveMusicSettings(float Value)
{
	const UHandSaberGameInstance* GameInstance = Cast<UHandSaberGameInstance>(GetGameInstance());
	if (GameInstance == nullptr) return;

	if (Value != SettingsData->MasterVolume && bCanChange)
	{
		SettingsData->MasterVolume = Value;
		SetMasterVolume(Value);
		GameInstance->Menu->IsSaved = true;
	}

	if (Value != SettingsData->MusicVolume && bCanChange)
	{
		SettingsData->MusicVolume = Value;
		GameInstance->Menu->IsSaved = true;
	}
}

void UAudioSettingsFeed::SetMusicVolume(float Value)
{
	
	// Guard statement against invalid FSoftObjectPath
	if (IsValid(SoundClass))
	{
		return;
	}

	// Load object if not already loaded
	USoundClass* soundClass = LoadObject<USoundClass>(nullptr, *SoundClass->GetName());

	// Guard against unsuccessful object instantiation
	if (soundClass == nullptr) {
		return;
	}

	soundClass->Properties.Volume = Value;
}

void UAudioSettingsFeed::SetMasterVolume(float Value)
{
	const FSoftObjectPath DefaultSoundClassName = GetDefault<UAudioSettings>()->DefaultSoundClassName;

	if (!DefaultSoundClassName.IsValid())
	{
		return;
	}

	USoundClass* masterSoundClass = LoadObject<USoundClass>(nullptr, *DefaultSoundClassName.ToString());

	if (masterSoundClass == nullptr)
	{
		return;
	}

	masterSoundClass->Properties.Volume = Value + 0.0001;
}

void UAudioSettingsFeed::NativeConstruct()
{
	Super::NativeConstruct();

	if (DataTable)
	{
		const FName RowName = FName("ConfigData"); // get clean row name
		SettingsData = DataTable->FindRow<FSettingsDataStruct>(RowName, "Settings Data Stuct");
		if (SettingsData)
		{
			MasterVolume->SetValue(SettingsData->MasterVolume);
			MusicVolume->SetValue(SettingsData->MusicVolume);
			bCanChange = true;
		}
	}
}


void UAudioSettingsFeed::NativeDestruct()
{
	// SAVE SETTINGS
	MasterVolume->OnValueChanged.RemoveAll(this);
	MusicVolume->OnValueChanged.RemoveAll(this);
}
