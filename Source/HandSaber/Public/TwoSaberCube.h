// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cube.h"
#include "TwoSaberCube.generated.h"

UCLASS()
class HANDSABER_API ATwoSaberCube : public ACube
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATwoSaberCube(const FObjectInitializer& OI);

private:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

	int IncrementCount();
	int DecrementCount();
	int SaberCount = 0;
	UPROPERTY()
	AActor* PreviousSaber = nullptr;
};
