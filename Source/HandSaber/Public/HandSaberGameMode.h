// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HandSaber/data/SongStruct.h"
#include "HandSaberGameMode.generated.h"

UCLASS()
class HANDSABER_API AHandSaberGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHandSaberGameMode();
	~AHandSaberGameMode();
	
	UFUNCTION()
	void PlaySong();
	UFUNCTION()
	void StopSong();
	UFUNCTION()
	void PauseSong(bool bIsPaused);

	UFUNCTION()
	void SongPercent(const class USoundWave* PlayingSoundWave, const float PlayBackPercent);

private:
	FSong SongStruct;

	UPROPERTY()
	class URuntimeAudioImporterLibrary* RuntimeAudioImporter;
	UPROPERTY()
	class UImportedSoundWave* ImportedSoundWave;
	UPROPERTY()
	class UAudioComponent* AudioComponent;

	bool bGameHasStarted;

	UPROPERTY(EditAnywhere)
	class USoundClass* SoundClass;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
