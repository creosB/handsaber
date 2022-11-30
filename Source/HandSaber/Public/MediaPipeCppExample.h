#pragma once

#include "CubeDirector.h"
#include "MediaPipePipelineComponent.h"
#include "MediaPipeLandmarkObserverComponent.h"
#include "Saber.h"
#include "MediaPipeCppExample.generated.h"

UCLASS(ClassGroup="MediaPipe")
class HANDSABER_API AMediaPipeCppExample : public AActor
{
	GENERATED_BODY()

public:
	AMediaPipeCppExample();
	void OnConstruction(const FTransform& Transform) override;
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void Tick(float DeltaSeconds) override;

	UPROPERTY()
	USceneComponent* Root = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ASaber* SaberL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ASaber* SaberR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACube> Cube;

	UPROPERTY()
	UMediaPipePipelineComponent* Pipeline = nullptr;

	UPROPERTY()
	UMediaPipeLandmarkObserverComponent* Observer = nullptr;

private:
	FVector TargetLocationL, TargetLocationR;
	FVector CurrentLocationL, CurrentLocationR;
	UPROPERTY(EditAnywhere)
	float LocationChangeSpeed = 1200.0f;
	void Movement(float DeltaTime, FVector TargetL, FVector TargetR);

	UFUNCTION(BlueprintPure, Category = "Math|Interpolation",
		meta = (Keywords = "interp vinterp vectorspringinterp lerp smoothdamp"))
	static FVector VectorSpringInterpCD(FVector Current, FVector Target, FVector Velocity, float DeltaTime,
	                                    float InterpSpeed = 10.f, float MaxVelocity = 0.f);
};
