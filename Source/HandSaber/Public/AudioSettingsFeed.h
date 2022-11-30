// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SettingsDataStruct.h"
#include "Blueprint/UserWidget.h"
#include "AudioSettingsFeed.generated.h"

UCLASS()
class HANDSABER_API UAudioSettingsFeed : public UUserWidget
{
	GENERATED_BODY()

private:
	UFUNCTION()
	void SaveMusicSettings(float Value);
	void SetMusicVolume(float Value);
	void SetMasterVolume(float Value);

	UPROPERTY(meta = (BindWidget))
	class USlider* MasterVolume;
	UPROPERTY(meta = (BindWidget))
	class USlider* MusicVolume;

	FSettingsDataStruct* SettingsData;
	UPROPERTY(EditAnywhere)
	UDataTable* DataTable;
	bool bCanChange = false;

	virtual bool Initialize() override;
	virtual void NativeDestruct() override;
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere)
	class USoundClass* SoundClass;
};
