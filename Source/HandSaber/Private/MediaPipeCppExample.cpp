#include "MediaPipeCppExample.h"
#include "DrawDebugHelpers.h"
#include "HandSaberGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AMediaPipeCppExample::AMediaPipeCppExample()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Pipeline = CreateDefaultSubobject<UMediaPipePipelineComponent>(TEXT("Pipeline"));
	Observer = CreateDefaultSubobject<UMediaPipeLandmarkObserverComponent>(TEXT("Observer"));

	Pipeline->PipelineName = TEXT("pipe0");
	Pipeline->GraphNodes.Add(TEXT("pose_landmarks"));

	Observer->PipelineName = TEXT("pipe0");
	Observer->StreamName = TEXT("pose_world_landmarks");
	Observer->LandmarkListType = EMediaPipeLandmarkListType::LandmarkList;
	Observer->AxisX = EMediaPipeLandmarkAxisMapping::Z;
	Observer->AxisY = EMediaPipeLandmarkAxisMapping::X;
	Observer->AxisZ = EMediaPipeLandmarkAxisMapping::NegY;
	Observer->WorldScale = FVector(100, 100, 100);
	Observer->MinVisibility = 0.5;
	Observer->MinPresence = 0.5;

	Pipeline->AddObserver(Observer);
}

void AMediaPipeCppExample::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	RegisterAllComponents();
}

void AMediaPipeCppExample::BeginPlay()
{
	Super::BeginPlay();
	Pipeline->Start();
}

void AMediaPipeCppExample::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Pipeline->Stop();
	Super::EndPlay(EndPlayReason);
}

void AMediaPipeCppExample::Tick(float DeltaSeconds)
{
	if (Observer && Observer->HaveDetections())
	{
		int ObjectId = 0;
		const auto& Landmarks = Observer->GetLandmarkList(ObjectId);
		const int Count = Landmarks.Num();

		auto* World = GetWorld();
		auto Transform = GetActorTransform();

		/*#if WITH_EDITORONLY_DATA
				for (int i = 0; i < Count; i++)
				{
					const auto& L = Landmarks[i];
					if ((L.Visibility > Observer->MinVisibility) && (L.Presence > Observer->MinPresence))
					{
						auto Pos = Transform.TransformPosition(L.Pos);
						DrawDebugPoint(World, Pos, 10.0f, FColor(255, 0, 0));
					}
				}
		#endif*/

		const auto& L = Landmarks[15];
		const auto& R = Landmarks[16];

		auto PosL = Transform.TransformPosition(L.Pos);
		auto PosR = Transform.TransformPosition(R.Pos);

		Movement(DeltaSeconds, PosL, PosR);


		/*TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Cube, FoundActors);
		float Distance;
		AActor* Target = UGameplayStatics::FindNearestActor(GetActorLocation(), FoundActors, Distance);
		if (Distance < 100 && Target)
		{
			/*UE_LOG(LogTemp, Warning, TEXT("AAAAAAAAA"));
			FRotator RotationCalculateL = UKismetMathLibrary::FindLookAtRotation(
				SaberL->GetActorLocation(), Target->GetActorLocation());
			// Getting calculated value and applying 2 between value.
			FRotator SaberRotationL = FMath::RInterpConstantTo(SaberL->GetActorRotation(), RotationCalculateL,
			                                           GetWorld()->GetDeltaSeconds(), 100.f);
			SaberL->SetActorRotation(SaberRotationL, ETeleportType::None);

			FRotator RotationCalculateR = UKismetMathLibrary::FindLookAtRotation(
				SaberR->GetActorLocation(), Target->GetActorLocation());
			// Getting calculated value and applying 2 between value.
			FRotator SaberRotationR = FMath::RInterpConstantTo(SaberR->GetActorRotation(), RotationCalculateR,
			                                           GetWorld()->GetDeltaSeconds(), 100.f);
			SaberR->SetActorRotation(SaberRotationR, ETeleportType::None);#1#
		}*/
	}
}

void AMediaPipeCppExample::Movement(float DeltaTime, FVector TargetL, FVector TargetR)
{
	//movement
	/*CurrentLocationL = SaberL->GetActorLocation();
	CurrentLocationR = SaberR->GetActorLocation();*/
	
	CurrentLocationL = VectorSpringInterpCD(SaberL->GetActorLocation(), TargetL, SaberL->GetVelocity(), DeltaTime,
											LocationChangeSpeed, 1200.f);
	CurrentLocationR = VectorSpringInterpCD(SaberR->GetActorLocation(), TargetR, SaberR->GetVelocity(), DeltaTime,
											LocationChangeSpeed, 1200.f);

	SaberL->SetActorLocation(CurrentLocationL);
	SaberR->SetActorLocation(CurrentLocationR);
}

FVector AMediaPipeCppExample::VectorSpringInterpCD(FVector Current, FVector Target, FVector Velocity, float DeltaTime, float InterpSpeed, float MaxVelocity)
{
	const FVector n1 = Velocity - (Current - Target) * (InterpSpeed * InterpSpeed * DeltaTime);
	const float n2 = 1.f + InterpSpeed * DeltaTime;

	if (MaxVelocity > 0.f)
	{
		Velocity = (n1 / (n2 * n2)).GetClampedToMaxSize(MaxVelocity);
	}
	else
	{
		Velocity = n1 / (n2 * n2);
	}

	return Current + Velocity * DeltaTime;
}