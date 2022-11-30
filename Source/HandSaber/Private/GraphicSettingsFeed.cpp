#include "GraphicSettingsFeed.h"
#include "HandSaberGameInstance.h"
#include "HandSaberSaveGame.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

bool UGraphicSettingsFeed::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) { return false; }

	if (!ensure(FullScreenMode != nullptr)) { return false; }
	FullScreenMode->OnSelectionChanged.AddDynamic(this, &UGraphicSettingsFeed::SaveGraphicsSettings);
	if (!ensure(FrameLimit != nullptr)) { return false; }
	FrameLimit->OnSelectionChanged.AddDynamic(this, &UGraphicSettingsFeed::SaveGraphicsSettings);
	if (!ensure(Resolution != nullptr)) { return false; }
	Resolution->OnSelectionChanged.AddDynamic(this, &UGraphicSettingsFeed::SaveGraphicsSettings);
	if (!ensure(EffectQuality != nullptr)) { return false; }
	EffectQuality->OnSelectionChanged.AddDynamic(this, &UGraphicSettingsFeed::SaveGraphicsSettings);
	if (!ensure(AntiAliasing != nullptr)) { return false; }
	AntiAliasing->OnSelectionChanged.AddDynamic(this, &UGraphicSettingsFeed::SaveGraphicsSettings);
	if (!ensure(ShadowQuality != nullptr)) { return false; }
	ShadowQuality->OnSelectionChanged.AddDynamic(this, &UGraphicSettingsFeed::SaveGraphicsSettings);
	if (!ensure(TextureQuality != nullptr)) { return false; }
	TextureQuality->OnSelectionChanged.AddDynamic(this, &UGraphicSettingsFeed::SaveGraphicsSettings);
	if (!ensure(VsyncQuality != nullptr)) { return false; }
	VsyncQuality->OnSelectionChanged.AddDynamic(this, &UGraphicSettingsFeed::SaveGraphicsSettings);

	return true;
}

void UGraphicSettingsFeed::NativeConstruct()
{
	Super::NativeConstruct();
	if (DataTable)
	{
		const FName RowName = FName("ConfigData"); // get clean row name
		SettingsData = DataTable->FindRow<FSettingsDataStruct>(RowName, "Settings Data Stuct");
		if (SettingsData)
		{
			FullScreenMode->SetSelectedOption(SettingsData->FullScreenMode);
			FrameLimit->SetSelectedOption(SettingsData->FrameLimit);
			Resolution->SetSelectedOption(SettingsData->ScreenResolution);
			EffectQuality->SetSelectedOption(SettingsData->EffectQuality);
			AntiAliasing->SetSelectedOption(SettingsData->AntiAliasing);
			ShadowQuality->SetSelectedOption(SettingsData->ShadowQuality);
			TextureQuality->SetSelectedOption(SettingsData->TextureQuality);
			VsyncQuality->SetSelectedOption(SettingsData->VsyncQuality);
			bCanChange = true;
		}
	}
}

void UGraphicSettingsFeed::SaveGraphicsSettings(FString sItem, ESelectInfo::Type seltype)
{
	const UHandSaberGameInstance* GameInstance = Cast<UHandSaberGameInstance>(GetGameInstance());
	if (GameInstance == nullptr || bCanChange == false) return;

	if (Resolution->IsOpen())
	{
		if (sItem != SettingsData->ScreenResolution)
		{
			if (Res.Num() <= 0)
			{
				Res.Add(TEXT("2560x1440"), FIntPoint(2560, 1440));
				Res.Add(TEXT("1920x1080"), FIntPoint(1920, 1080));
				Res.Add(TEXT("1280x720"), FIntPoint(1280, 720));
				Res.Add(TEXT("720x480"), FIntPoint(720, 480));
			}
			if (GEngine)
			{
				GEngine->GameUserSettings->SetScreenResolution(Res.FindRef(sItem));
				UE_LOG(LogTemp, Warning, TEXT("Applied SetScreenResolution"));
			}
			SettingsData->ScreenResolution = sItem;
			UE_LOG(LogTemp, Warning, TEXT("ScreenResolution %s"), *SettingsData->ScreenResolution);
			GameInstance->Menu->IsSaved = true;
		}
	}
	if (FullScreenMode->IsOpen())
	{
		if (sItem != SettingsData->FullScreenMode)
		{
			if (ScreenMode.Num() <= 0)
			{
				ScreenMode.Add(TEXT("FullScreen"), 1);
				ScreenMode.Add(TEXT("Windowed FullScreen"), 0);
			}
			if (GEngine)
			{
				if (ScreenMode.FindRef(sItem) == 0)
				{
					GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
					UE_LOG(LogTemp, Warning, TEXT("Applied SetFullscreenMode"));
				}
				else
				{
					GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
					UE_LOG(LogTemp, Warning, TEXT("Applied SetFullscreenMode"));
				}
			}
			SettingsData->FullScreenMode = sItem;
			UE_LOG(LogTemp, Warning, TEXT("FullScreen %s"), *SettingsData->FullScreenMode);
			GameInstance->Menu->IsSaved = true;
		}
	}
	else if (EffectQuality->IsOpen())
	{
		if (sItem != SettingsData->EffectQuality)
		{
			if (Effect.Num() <= 0)
			{
				Effect.Add(TEXT("Cinematic"), 4);
				Effect.Add(TEXT("Epic"), 3);
				Effect.Add(TEXT("Medium"), 2);
				Effect.Add(TEXT("Low"), 1);
			}
			if (GEngine)
			{
				GEngine->GameUserSettings->SetViewDistanceQuality(Effect.FindRef(sItem));
				UE_LOG(LogTemp, Warning, TEXT("Applied EffectQuality"));
			}
			SettingsData->EffectQuality = sItem;
			UE_LOG(LogTemp, Warning, TEXT("Effect %s"), *SettingsData->EffectQuality);
			GameInstance->Menu->IsSaved = true;
		}
	}
	else if (FrameLimit->IsOpen())
	{
		if (sItem != SettingsData->FrameLimit)
		{
			if (Frame.Num() <= 0)
			{
				Frame.Add(TEXT("Unlimited"), 0);
				Frame.Add(TEXT("60"), 60);
				Frame.Add(TEXT("30"), 30);
			}
			if (GEngine)
			{
				GEngine->GameUserSettings->SetFrameRateLimit(Frame.FindRef(sItem));
				UE_LOG(LogTemp, Warning, TEXT("Applied FrameLimit"));
			}
			SettingsData->FrameLimit = sItem;
			UE_LOG(LogTemp, Warning, TEXT("Frame %s"), *SettingsData->FrameLimit);
			GameInstance->Menu->IsSaved = true;
		}
	}
	else if (AntiAliasing->IsOpen())
	{
		if (sItem != SettingsData->AntiAliasing)
		{
			if (Aliasing.Num() <= 0)
			{
				Aliasing.Add(TEXT("Epic"), 3);
				Aliasing.Add(TEXT("High"), 2);
				Aliasing.Add(TEXT("Medium"), 1);
				Aliasing.Add(TEXT("Low"), 0);
			}
			if (GEngine)
			{
				GEngine->GameUserSettings->SetAntiAliasingQuality(Aliasing.FindRef(sItem));
				UE_LOG(LogTemp, Warning, TEXT("Applied SetAntiAliasingQuality"));
			}
			SettingsData->AntiAliasing = sItem;
			UE_LOG(LogTemp, Warning, TEXT("Antialiasing %s"), *SettingsData->AntiAliasing);
			GameInstance->Menu->IsSaved = true;
		}
	}
	else if (ShadowQuality->IsOpen())
	{
		if (sItem != SettingsData->ShadowQuality)
		{
			if (Shadow.Num() <= 0)
			{
				Shadow.Add(TEXT("Ultra"), 3);
				Shadow.Add(TEXT("High"), 2);
				Shadow.Add(TEXT("Medium"), 1);
				Shadow.Add(TEXT("Low"), 0);
			}
			if (GEngine)
			{
				GEngine->GameUserSettings->SetShadowQuality(Shadow.FindRef(sItem));
				UE_LOG(LogTemp, Warning, TEXT("Applied SetShadowQuality"));
			}
			SettingsData->ShadowQuality = sItem;
			UE_LOG(LogTemp, Warning, TEXT("ShadowQuality %s"), *SettingsData->ShadowQuality);
			GameInstance->Menu->IsSaved = true;
		}
	}
	else if (TextureQuality->IsOpen())
	{
		if (sItem != SettingsData->TextureQuality)
		{
			// same key and value with shadow quality
			if (Shadow.Num() <= 0)
			{
				Shadow.Add(TEXT("Ultra"), 3);
				Shadow.Add(TEXT("High"), 2);
				Shadow.Add(TEXT("Medium"), 1);
				Shadow.Add(TEXT("Low"), 0);
			}
			if (GEngine)
			{
				GEngine->GameUserSettings->SetTextureQuality(Shadow.FindRef(sItem));
				UE_LOG(LogTemp, Warning, TEXT("Applied TextureQuality"));
			}
			SettingsData->TextureQuality = sItem;
			UE_LOG(LogTemp, Warning, TEXT("TextureQuality %s"), *SettingsData->TextureQuality);
			GameInstance->Menu->IsSaved = true;
		}
	}
	else if (VsyncQuality->IsOpen())
	{
		if (sItem != SettingsData->VsyncQuality)
		{
			if (Vsync.Num() <= 0)
			{
				Vsync.Add(TEXT("on"), true);
				Vsync.Add(TEXT("off"), false);
			}
			if (GEngine)
			{
				GEngine->GameUserSettings->SetVSyncEnabled(Vsync.FindRef(sItem));
				UE_LOG(LogTemp, Warning, TEXT("Applied SetVSyncEnabled"));
			}
			SettingsData->VsyncQuality = sItem;
			UE_LOG(LogTemp, Warning, TEXT("VsyncQuality %s"), *SettingsData->VsyncQuality);
			GameInstance->Menu->IsSaved = true;
		}
	}
}

void UGraphicSettingsFeed::NativeDestruct()
{
	// SAVE SETTINGS
	FullScreenMode->OnSelectionChanged.RemoveAll(this);
	FrameLimit->OnSelectionChanged.RemoveAll(this);
	EffectQuality->OnSelectionChanged.RemoveAll(this);
	Resolution->OnSelectionChanged.RemoveAll(this);
	EffectQuality->OnSelectionChanged.RemoveAll(this);
	AntiAliasing->OnSelectionChanged.RemoveAll(this);
	ShadowQuality->OnSelectionChanged.RemoveAll(this);
	TextureQuality->OnSelectionChanged.RemoveAll(this);
	VsyncQuality->OnSelectionChanged.RemoveAll(this);
}
