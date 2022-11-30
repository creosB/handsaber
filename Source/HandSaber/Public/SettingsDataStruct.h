#pragma once

#include "Engine/DataTable.h"

#include "SettingsDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FSettingsDataStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FSettingsDataStruct()
		: FullScreenMode("FullScreen")
		  , FrameLimit("60")
		  , ScreenResolution("1920x1080")
		  , AntiAliasing("Epic")
		  , ShadowQuality("Ultra")
		  , TextureQuality("Ultra")
		  , EffectQuality("Epic")
		  , VsyncQuality("on")
		  , MasterVolume(1.0f)
		  , MusicVolume(1.0f)
		  , Difficulty(1.2f)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	FString FullScreenMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	FString FrameLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	FString ScreenResolution;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	FString AntiAliasing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	FString ShadowQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	FString TextureQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	FString EffectQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	FString VsyncQuality;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	float MasterVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	float MusicVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings Data Stuct")
	float Difficulty;
};
