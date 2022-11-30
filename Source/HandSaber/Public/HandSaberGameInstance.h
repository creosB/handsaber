// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeadScreen.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "Engine/GameInstance.h"
#include "ScoreScreen.h"
#include "SettingsDataStruct.h"
#include "HandSaber/data/SongStruct.h"
#include "HandSaberGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HANDSABER_API UHandSaberGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
public:
	UHandSaberGameInstance(const FObjectInitializer& ObjectInitializer);

	FSong ChosenSong; // only one chosen song
	// INTERFACE FUNCTIONS
	virtual void StartGame() override;
	virtual void LoadMainMenu() override;
	virtual void RestartGame() override;
	virtual void ReturnChosenSong(uint32 Index) override;
	UFUNCTION()
	virtual void AddScore(int score) override;

	// Menu Functions
	UFUNCTION()
	void LoadMenu();
	UFUNCTION()
	void PauseLoadMenu();
	UFUNCTION()
	void DeadScreen();
	UFUNCTION()
	void ReadSongList(FString FilePath);
	UFUNCTION()
	void ScoreScreenWidget();
	UFUNCTION()
	void SaveGame();
	// Save game variables
	int Score = 0;

	UPROPERTY()
	UMainMenu* Menu = nullptr;

	UFUNCTION()
	void GetSongPercent(float percent);
private:
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UUserWidget> MenuClass = nullptr;
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UUserWidget> PauseMenuClass = nullptr;
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UUserWidget> DeadScreenClass = nullptr;
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UUserWidget> ScoreScreenClass = nullptr;
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class UDataTable> SettingsDataClass = nullptr;

	UPROPERTY()
	UPauseMenu* PauseMenu = nullptr;
	UPROPERTY()
	UDeadScreen* DeadMenu = nullptr;
	UPROPERTY()
	UScoreScreen* ScoreScreen = nullptr;


	FSongStruct SongList; // all songs

	UPROPERTY()
	UHandSaberSaveGame* SaveGameSlot;
protected:
	virtual void Init() override;
};
