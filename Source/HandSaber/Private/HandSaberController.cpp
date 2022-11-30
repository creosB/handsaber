// Fill out your copyright notice in the Description page of Project Settings.


#include "HandSaberController.h"


// Sets default values
AHandSaberController::AHandSaberController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHandSaberController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHandSaberController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}