// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cube.h"
#include "ExplosiveCube.generated.h"

UCLASS()
class HANDSABER_API AExplosiveCube : public ACube
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AExplosiveCube(const FObjectInitializer& OI);

private:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	UMaterialParameterCollection* MaterialParameterCollection;

	int ExplosiveType;
	/*UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	           FVector NormalImpulse, const FHitResult& Hit);*/
	
};
