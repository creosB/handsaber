// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cube.h"
#include "ExplosiveCube.h"
#include "OneSaberCube.h"
#include "TwoSaberCube.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "CubeDirector.generated.h"

UENUM(BlueprintType)
enum ESpawnDirection
{
	SpawnDirectionX UMETA(Display = "X direction"),
	SpawnDirectionY UMETA(Display = "Y direction"),
	SpawnDirectionZ UMETA(Display = "Z direction")
};

/*
 * set bIsTwoSaber boolean
 * set one array which will you use array (one saber or two saber)
 * set spawn direction x,y or z for random spawn with min-max range
 * set spawn speed
 */

USTRUCT()
struct FSpawnerActorSettings
{
	GENERATED_BODY()

	/*
	 * One array can be null
	 * We will choose with bIsTwoSaber boolean which we will use
	 */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AOneSaberCube> OneSaberCubes;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATwoSaberCube> TwoSaberCubes;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AExplosiveCube> ExplosiveCube;

	/*
	 * We will set min-max value on the spawn direction
	 */
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ESpawnDirection> SpawnDirection;
	
	UPROPERTY(EditAnywhere, Category = "SpawnerSettings")
	float MinSpawnLocation;
	UPROPERTY(EditAnywhere, Category = "SpawnerSettings")
	float MaxSpawnLocation;
};


UCLASS()
class HANDSABER_API ACubeDirector : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACubeDirector(const FObjectInitializer& OI);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnActor();
	
	UPROPERTY()
	UArrowComponent* ArrowComponent;
	
	UPROPERTY(EditAnywhere, Category = "SpawnerSettings")
	TArray<FSpawnerActorSettings> SpawnSettings;

	UPROPERTY(EditAnywhere, Category = "SpawnerSettings")
	float SpawnSpeed = 1.f;
	
private: 
	FVector SpawnChoice(int element);
	AActor* SaberFinder(int element);
	UPROPERTY()
	UWorld* World;
	FTimerHandle SpawnTimerHandle;

	TMap<FString, float> Difficulty;
};
