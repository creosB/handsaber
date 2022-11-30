// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuGameMode.h"
#include "HandSaberGameInstance.h"


AMenuGameMode::AMenuGameMode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (auto const GameInstance = Cast<UHandSaberGameInstance>(GetGameInstance()))
	{
		GameInstance->LoadMenu();
		GameInstance->ReadSongList(
				"Content/Data/music.json");
	}
}

void AMenuGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


AMenuGameMode::~AMenuGameMode()
{
}
