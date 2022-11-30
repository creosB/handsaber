// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplosiveCube.h"
#include "Cube.h"
#include "Saber.h"
#include "Kismet/KismetMaterialLibrary.h"


// Sets default values
AExplosiveCube::AExplosiveCube(const FObjectInitializer& OI) : Super(OI)
{
	CubeMesh->OnComponentBeginOverlap.AddDynamic(this, &AExplosiveCube::OnOverlapBegin);
}

void AExplosiveCube::BeginPlay()
{
	Super::BeginPlay();
	ExplosiveType = FMath::RandRange(0, 1);
	if (ExplosiveType == 0)
	{
		UMaterialInstanceDynamic* M = CubeMesh->CreateAndSetMaterialInstanceDynamic(0);

		M->SetScalarParameterValue("ColorChoice", 0);
	}
	else
	{
		UMaterialInstanceDynamic* M = CubeMesh->CreateAndSetMaterialInstanceDynamic(0);

		M->SetScalarParameterValue("ColorChoice", 1);
	}
}


void AExplosiveCube::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
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

		if (ExplosiveType == 0)
		{
			CutOccured(BasePoint, CutterPlaneNormal, -400);
		}
		else
		{
			CutOccured(BasePoint, CutterPlaneNormal, 400);
		}
	}
}
