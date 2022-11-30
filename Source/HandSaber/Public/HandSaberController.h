// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HandSaberController.generated.h"

UCLASS()
class HANDSABER_API AHandSaberController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHandSaberController();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
