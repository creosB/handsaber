// Fill out your copyright notice in the Description page of Project Settings.


#include "HandSaberGameMode.h"

#include "HandPawn.h"
#include "HandSaberGameInstance.h"
#include "MediaPipeCppExample.h"
#include "Kismet/GameplayStatics.h"
#include "RuntimeAudioImporterLibrary.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
AHandSaberGameMode::AHandSaberGameMode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
}

// Called when the game starts or when spawned
void AHandSaberGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (auto const GameInstance = Cast<UHandSaberGameInstance>(GetGameInstance()))
	{
		// for debug
		/*GameInstance->ReadSongList(
			"Source/MediaPipeDemo/data/music.json");*/

		GameInstance->ScoreScreenWidget();
	}
	PlaySong();
}

// Called every frame
void AHandSaberGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHandSaberGameMode::PlaySong()
{
	if (auto const GameInstance = Cast<UHandSaberGameInstance>(GetGameInstance()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Song playing: %s"), *GameInstance->ChosenSong.songName);
		const FString SongName = GameInstance->ChosenSong.songName;

		RuntimeAudioImporter = URuntimeAudioImporterLibrary::CreateRuntimeAudioImporter();

		if (!IsValid(RuntimeAudioImporter))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create audio importer"));
			return;
		}

		RuntimeAudioImporter->OnProgressNative.AddWeakLambda(this, [](int32 Percentage)
		{
			UE_LOG(LogTemp, Log, TEXT("Audio importing percentage: %d"), Percentage);
		});

		RuntimeAudioImporter->OnResultNative.AddWeakLambda(
			this, [this](URuntimeAudioImporterLibrary* Importer, UImportedSoundWave* SoundWave,
			             ETranscodingStatus Status)
			{
				if (Status == ETranscodingStatus::SuccessfulImport)
				{
					ImportedSoundWave = SoundWave;
					UE_LOG(LogTemp, Warning, TEXT("Successfully imported audio with sound wave %s"),
					       *ImportedSoundWave->GetName());
					// Here you can handle ImportedSoundWave playback, like
					ImportedSoundWave->SetLooping(false);
					ImportedSoundWave->SetVolume(1.f);
					ImportedSoundWave->SetPitch(1.f);
					ImportedSoundWave->SoundClassObject = SoundClass;
					AudioComponent->SetSound(ImportedSoundWave);
					AudioComponent->OnAudioPlaybackPercent.AddDynamic(this, &AHandSaberGameMode::SongPercent);
					AudioComponent->OnAudioFinished.AddDynamic(this, &AHandSaberGameMode::StopSong);
					AudioComponent->Play();
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to import audio"));
				}

				RuntimeAudioImporter = nullptr;
			});

		RuntimeAudioImporter->ImportAudioFromFile(
			*(FPaths::ProjectDir() + TEXT("Content/Data/") + SongName + TEXT(".mp3")), EAudioFormat::Mp3);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Instance couldn't call"));
	}
}

void AHandSaberGameMode::StopSong()
{
	AudioComponent->OnAudioFinished.RemoveAll(this);
	AudioComponent->Stop();
	if (auto const Player = Cast<AHandPawn>(UGameplayStatics::GetPlayerPawn(this, 0)))
	{
		Player->PlayerDead();
	}
}

void AHandSaberGameMode::PauseSong(bool bIsPaused)
{
	AudioComponent->SetPaused(bIsPaused);
}

void AHandSaberGameMode::SongPercent(const USoundWave* PlayingSoundWave, const float PlayBackPercent)
{
	if (auto const GameInstance = Cast<UHandSaberGameInstance>(GetGameInstance()))
	{
		GameInstance->GetSongPercent(PlayBackPercent);
	}
}


AHandSaberGameMode::~AHandSaberGameMode()
{
	// AudioComponent->DestroyComponent();
}
