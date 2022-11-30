// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SettingsDataStruct.h"
#include "Engine/DataTable.h"
#include "Blueprint/UserWidget.h"
#include "GraphicSettingsFeed.generated.h"

UCLASS()
class HANDSABER_API UGraphicSettingsFeed : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* FullScreenMode;
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* Resolution;
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* FrameLimit;
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* VsyncQuality;
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* TextureQuality;
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* EffectQuality;
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* ShadowQuality;
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* AntiAliasing;

	UFUNCTION()
	void SaveGraphicsSettings(FString sItem, ESelectInfo::Type seltype);

	FSettingsDataStruct* SettingsData;
	UPROPERTY(EditAnywhere)
	UDataTable* DataTable;
	bool bCanChange = false;
	
	TMap<FString, FIntPoint> Res;
	TMap<FString, int32> Effect;
	TMap<FString, int32> ScreenMode;
	TMap<FString, int32> Frame;
	TMap<FString, int32> Aliasing;
	TMap<FString, int32> Shadow;
	TMap<FString, bool> Vsync;
	
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
