// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Saber.generated.h"

UENUM(BlueprintType)
enum ESaberColor
{
	Blue = 0 UMETA("Blue"),
	Red = 1 UMETA("Red"),
};

UCLASS()
class HANDSABER_API ASaber : public AActor
{
	GENERATED_BODY()
	
public:	
	ASaber(const FObjectInitializer& OI);

protected:
	virtual void BeginPlay() override;
	void DemoToggleSaber();

public:	
	virtual void Tick(float DeltaTime) override;
	void UpdateRetractionState(float DeltaTime);
	void SetSaberRetracted(bool IsRetracted);
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY()
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* SaberMesh; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* HandleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCapsuleComponent* SaberCollision;
	
	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* SaberFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TargetSaberRetraction = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentSaberRetraction = 0.f;
	
	UPROPERTY(EditDefaultsOnly)
	float SaberRetractionMin = -100.f;

	UPROPERTY(EditDefaultsOnly)
	float SaberRetractionMax = 3000.f;

	UPROPERTY(EditDefaultsOnly)
	float SaberRetractionSpeed = 7000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ESaberColor> SaberColor = ESaberColor::Blue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsRetracted = false;

	FVector SaberTipLastFrame = FVector(0.f, 0.f, 1.f);
	FVector SaberTipCurrentFrame = FVector(0.f, 0.f, 1.f);

private: // properties
	UPROPERTY()
	UMaterialInstanceDynamic* SaberDynamicMaterial;

	FTimerHandle DemoSaberActivation;
	
};
