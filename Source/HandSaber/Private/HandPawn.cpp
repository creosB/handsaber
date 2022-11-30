// Fill out your copyright notice in the Description page of Project Settings.


#include "HandPawn.h"

#include "HandSaberController.h"
#include "HandSaberGameInstance.h"
#include "HandSaberGameMode.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AHandPawn::AHandPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetVisibility(false);
	Sphere->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AHandPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void AHandPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AHandPawn::Pause);
}

// Call dead/score screen
void AHandPawn::PlayerDead()
{
	UHandSaberGameInstance* GameInstance = Cast<UHandSaberGameInstance>(GetGameInstance());
	if (!ensure(GameInstance != nullptr)) { return; }
	bCanPause = false;
	GameInstance->SaveGame();
	GameInstance->DeadScreen();
}

// call pause menu
void AHandPawn::Pause()
{
	if (bCanPause)
	{
		auto const Instance = Cast<UHandSaberGameInstance>(GetGameInstance());
		if (!ensure(Instance != nullptr)) { return; }
		if (auto const GameMode = Cast<AHandSaberGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			GameMode->PauseSong(true);
			Instance->PauseLoadMenu();
			bCanPause = false;
		}
	}
}

void AHandPawn::UnPause()
{
	if (auto const GameMode = Cast<AHandSaberGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->PauseSong(false);
		bCanPause = true;
	}
}

// add score
void AHandPawn::EarnScore(int value)
{
	UHandSaberGameInstance* GameInstance = Cast<UHandSaberGameInstance>(GetGameInstance());
	if (!ensure(GameInstance != nullptr)) { return; }
	GameInstance->AddScore(value);
}
