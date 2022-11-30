// Fill out your copyright notice in the Description page of Project Settings.

#include "OneSaberCube.h"
#include "Cube.h"
#include "Saber.h"


// Sets default values
AOneSaberCube::AOneSaberCube(const FObjectInitializer& OI) : Super(OI)
{
	CubeMesh->OnComponentBeginOverlap.AddDynamic(this, &AOneSaberCube::OnOverlapBegin);
}

void AOneSaberCube::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                                   class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	ASaber* Saber = Cast<ASaber>(OtherActor);
	if (Saber && OtherActor != this)
	{
		// Single point on cutter plane
		FVector BasePoint = Saber->GetActorLocation();
		// Sum of vector speeds in the moment of saber hitting the object
		FVector CollisionSummary = Saber->SaberTipCurrentFrame - Saber->SaberTipLastFrame - GetMovementDirection();
		// Derive cutter plane normal
		FVector CutterPlaneNormal = FVector::CrossProduct(CollisionSummary, Saber->SaberTipLastFrame);
		CutOccured(BasePoint, CutterPlaneNormal, 100);
	}
}
