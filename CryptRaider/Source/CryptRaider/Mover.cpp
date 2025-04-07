// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	// Keeps track of original location & target location
	StartingLocation = GetOwner()->GetActorLocation();
	TargetLocation = StartingLocation + MoveOffset;
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove)
	{
		CurrentLocation = GetOwner()->GetActorLocation();
		if (!ShouldPlaySfx)
		{
			OnPlaySound.Broadcast();
			ShouldPlaySfx = true;
		}

		if (ShouldOpen)
		{
			WillOpen(DeltaTime);
		}

		if (ShouldClose)
		{
			WillClose(DeltaTime);
		}
	}
}


void UMover::SetShouldOpen()
{
	ShouldMove = true;
	ShouldOpen = true;
	ShouldClose = false;
}

void UMover::SetShouldClose()
{
	ShouldMove = true;
	ShouldOpen = false;
	ShouldClose = true;
}

void UMover::WillOpen(float DeltaTime)
{

	float Speed = FVector::Dist(StartingLocation, TargetLocation) / MoveTime;
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);
	
	if (FVector::Dist(CurrentLocation, TargetLocation) <= 1.0f)
	{
		ResetVariables();
	}
}


void UMover::WillClose(float DeltaTime)
{
	float Speed = FVector::Dist(CurrentLocation, StartingLocation) / MoveTime;
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, StartingLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);

	if (FVector::Dist(CurrentLocation, StartingLocation) <= 1.0f)
	{
		ResetVariables();
	}
}


void UMover::ResetVariables()
{
	ShouldMove = false;
	ShouldOpen = false;
	ShouldClose = false;
	ShouldPlaySfx = false;
	OnStopSound.Broadcast();
}



