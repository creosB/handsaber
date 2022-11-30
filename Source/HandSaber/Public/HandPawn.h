// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"

#include "HandPawn.generated.h"

UCLASS()
class HANDSABER_API AHandPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHandPawn();

	void PlayerDead();
	void Pause();
	void UnPause();
	void EarnScore(int value);
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	USphereComponent* Sphere;

	bool bCanPause = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
