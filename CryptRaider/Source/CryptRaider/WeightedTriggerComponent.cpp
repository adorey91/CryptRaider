// Fill out your copyright notice in the Description page of Project Settings.


#include "WeightedTriggerComponent.h"

// Sets default values for this component's properties
UWeightedTriggerComponent::UWeightedTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UWeightedTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	CheckCurrentWeight();
	WeightNeeded = CurrentWeight;

	GetWorld()->GetTimerManager().SetTimer(
		WeightCheckTimerHandle, // timer handle
		this,
		&UWeightedTriggerComponent::CheckCurrentWeightLoop, // pointer to member function
		1.0f, // interval
		true, // looping
		30.0f // initial delay
	);
}


// Called every frame
void UWeightedTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeightedTriggerComponent::CheckCurrentWeight()
{
	float AddedWeight = 0;
	TArray<AActor*> OutActors;
	this->GetOverlappingActors(OutActors);

	// Loop through all actors that are overlapping
	for (AActor* OutActor : OutActors)
	{
		// Loop through all components of each actor
		for (UActorComponent* ActorComponent : OutActor->GetComponents())
		{
			// Check if the component is a UStaticMeshComponent
			UStaticMeshComponent* StaticMeshComp = Cast<UStaticMeshComponent>(ActorComponent);
			if (StaticMeshComp && StaticMeshComp->IsSimulatingPhysics())
			// Only consider components with physics simulation
			{
				AddedWeight += StaticMeshComp->GetMass(); // Add the mass of the component
			}
		}
	}

	CurrentWeight = AddedWeight; // Update the current weight
}


void UWeightedTriggerComponent::CheckCurrentWeightLoop()
{
	CheckCurrentWeight();

	// UE_LOG(LogTemp, Warning, TEXT("Checking Weight: CurrentWeight: %f, WeightNeeded: %f"), CurrentWeight, WeightNeeded);

	// If the weight doesn't match the required weight, and the door is open, close it
	if (CurrentWeight != WeightNeeded)
	{
		CloseDoor();
	}
	else
	{
		OpenDoor();
	}
}


void UWeightedTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}

void UWeightedTriggerComponent::OpenDoor()
{
	// this moves back to original position
	Mover->SetShouldClose();
	bIsOpenDoor = true; // Ensure the door state reflects the correct weight
}

void UWeightedTriggerComponent::CloseDoor()
{
	// this moves the door to the new location
	Mover->SetShouldOpen();
	bIsOpenDoor = false; // Ensure the door state reflects the weight mismatch
}
