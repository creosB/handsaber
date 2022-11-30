// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeDirector.h"

#include "HandSaberGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACubeDirector::ACubeDirector(const FObjectInitializer& OI) : Super(OI)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ArrowComponent = OI.CreateDefaultSubobject<UArrowComponent>(this, TEXT("ActorRootArrow"));
	SetRootComponent(ArrowComponent);
}

// Called when the game starts or when spawned
void ACubeDirector::BeginPlay()
{
	Super::BeginPlay();
	if (Difficulty.Num() <= 0)
	{
		Difficulty.Add(TEXT("Expert"), 0.7f);
		Difficulty.Add(TEXT("Medium"), 0.9f);
		Difficulty.Add(TEXT("Easy"), 1.2f);
	}

	if (auto const GameInstance = Cast<UHandSaberGameInstance>(GetGameInstance()))
	{
		SpawnSpeed = Difficulty.FindRef(GameInstance->ChosenSong.difficulty);
	}

	World = GetWorld();
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ACubeDirector::SpawnActor, SpawnSpeed, true);
}

// Called every frame
void ACubeDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACubeDirector::SpawnActor()
{
	if (World != nullptr)
	{
		int elem = UKismetMathLibrary::RandomIntegerInRange(0, SpawnSettings.Num() - 1);
		World->SpawnActor<AActor>(SaberFinder(elem)->GetClass(),
		                          SpawnChoice(elem), FRotator(30.f, 30.f, 30.f));
	}
}

AActor* ACubeDirector::SaberFinder(int element)
{
	int8 CubeType = FMath::RandRange(0, 2);
	AActor* CubeActor = nullptr;

	switch (CubeType)
	{
	case 0:
		CubeActor = SpawnSettings[element].OneSaberCubes.GetDefaultObject();
		if (CubeActor)
		{
			return CubeActor;
		}
		break;
	case 1:
		CubeActor = SpawnSettings[element].TwoSaberCubes.GetDefaultObject();
		if (CubeActor)
		{
			return CubeActor;
		}
		break;
	case 2:
		CubeActor = SpawnSettings[element].ExplosiveCube.GetDefaultObject();
		if (CubeActor)
		{
			return CubeActor;
		}
		break;
	default:
		CubeActor = SpawnSettings[0].ExplosiveCube.GetDefaultObject();
		if (CubeActor)
		{
			return CubeActor;
		}
	}


	int elem = FMath::RandRange(0, SpawnSettings.Num() - 1);
	return SaberFinder(elem);
}

FVector ACubeDirector::SpawnChoice(int element)
{
	switch (SpawnSettings[element].SpawnDirection)
	{
	case SpawnDirectionZ:
		{
			FVector SpawnerLocation = GetActorLocation();
			SpawnerLocation.Z = GetActorLocation().Z - FMath::RandRange(
				SpawnSettings[element].MinSpawnLocation,
				SpawnSettings[element].MaxSpawnLocation);
			return SpawnerLocation;
		}
	case SpawnDirectionY:
		{
			FVector SpawnerLocation = GetActorLocation();
			SpawnerLocation.Y = GetActorLocation().Y - FMath::RandRange(
				SpawnSettings[element].MinSpawnLocation,
				SpawnSettings[element].MaxSpawnLocation);
			return SpawnerLocation;
		}
	case SpawnDirectionX:
		{
			FVector SpawnerLocation = GetActorLocation();
			SpawnerLocation.X = GetActorLocation().X - FMath::RandRange(
				SpawnSettings[element].MinSpawnLocation,
				SpawnSettings[element].MaxSpawnLocation);
			return SpawnerLocation;
		}
	default:
		FVector SpawnerLocation = GetActorLocation();
		SpawnerLocation.X = GetActorLocation().X - FMath::RandRange(
			SpawnSettings[element].MinSpawnLocation,
			SpawnSettings[element].MaxSpawnLocation);
		return SpawnerLocation;
	}
}
