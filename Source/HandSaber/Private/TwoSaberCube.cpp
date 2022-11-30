// Fill out your copyright notice in the Description page of Project Settings.

#include "TwoSaberCube.h"
#include "Saber.h"


// Sets default values
ATwoSaberCube::ATwoSaberCube(const FObjectInitializer& OI) : Super(OI)
{
	CubeMesh->OnComponentBeginOverlap.AddDynamic(this, &ATwoSaberCube::OnOverlapBegin);
}

void ATwoSaberCube::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	ASaber* Saber = Cast<ASaber>(OtherActor);
	if (Saber && Saber != PreviousSaber && OtherActor != this)
	{
		IncrementCount();
		PreviousSaber = Saber;
		if (SaberCount >= 2)
		{
			// Single point on cutter plane
			FVector BasePoint = Saber->GetActorLocation();
			// Sum of vector speeds in the moment of saber hitting the object
			FVector CollisionSummary = Saber->SaberTipCurrentFrame - Saber->SaberTipLastFrame - GetMovementDirection();
			// Derive cutter plane normal
			FVector CutterPlaneNormal = FVector::CrossProduct(CollisionSummary, Saber->SaberTipLastFrame);
			CutOccured(BasePoint, CutterPlaneNormal, 200);
		}
	}
}


int ATwoSaberCube::IncrementCount()
{
	return SaberCount++;
}

int ATwoSaberCube::DecrementCount()
{
	return SaberCount--;
}
