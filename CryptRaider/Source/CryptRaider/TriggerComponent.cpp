// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "GameFramework/Actor.h"

#include "Math/UnitConversion.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UTriggerComponent::InitAfterDelay);
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bHasInitialized) return;

	if (Movers.Num() == 0) // Check if Mover is null
		return;

	// if (WeightedTrigger && WeightNeeded != CurrentWeight)
	// {
	// 	// UE_LOG(LogTemp, Error,TEXT("Mover is Closing"));
	// 	MoveObjects();
	// 	return;
	// }
	//
	// if (WeightedTrigger && WeightNeeded == CurrentWeight)
	// {
	// 	// UE_LOG(LogTemp, Error,TEXT("Mover is Opening"));
	// 	DontMove();
	// 	return;
	// }

	AActor* Actor = GetAcceptableActor();
	if (Actor == nullptr)
		return;

	UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
	if (Component == nullptr)
		return;

	Actor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Component->SetSimulatePhysics(false);

	MoveObjects();
}

void UTriggerComponent::MoveObjects()
{
	if (Movers.Num() > 0)
	{
		for (UMover* Mover : Movers)
		{
			Mover->SetShouldOpen();
		}
	}
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	if (NewMover)
	{
		Movers.Add(NewMover);
	}
}

void UTriggerComponent::SetMultipleMovers(TArray<UMover*> NewMover)
{
	for (UMover* Mover : NewMover)
	{
		Movers.Add(Mover);
	}
}


AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		if (Actor->ActorHasTag(UnlockTag) && !Actor->ActorHasTag("Grabbed"))
		{
			return Actor;
		}
	}

	return nullptr;
}

void UTriggerComponent::InitAfterDelay()
{
	bHasInitialized = true;
}
