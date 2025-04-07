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
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (Movers.Num() == 0 && !DoorRotator) // Check if Mover is null
	{
		// UE_LOG(LogTemp, Error,
		//        TEXT("Mover or Door Rotator is null in UTriggerComponent! Did you forget to call SetMover? %s"),
		//        *ThisName);
		return;
	}
	FString ThisName = GetOwner()->GetName();

	if (WeightedTrigger && WeightNeeded != CurrentWeight)
	{
		MoveObjects();
		return;
	}

	if (WeightedTrigger && WeightNeeded == CurrentWeight)
	{
		DontMove();
		return;
	}

	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component != nullptr)
		{
			Actor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Component->SetSimulatePhysics(false);
		}

		if (MovesObjects)
		{
			MoveObjects();
		}
		else if (RotatesDoor)
		{
			DoorRotate(Actor);
		}
	}
	else
	{
		DontMove();
	}
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

void UTriggerComponent::DoorRotate(AActor* Actor)
{
	if (!PlayAudio)
	{
		StartAudioEvent.Broadcast();
		PlayAudio = true;
	}
	DoorRotator->SetShouldRotate(true);
	// 🔹 Destroy the key after 2 seconds (adjust delay as needed)
	DestroyActorWithDelay(Actor, 2.0f);
}

void UTriggerComponent::DontMove()
{
	if (Movers.Num() != 0)
	{
		for (UMover* Mover : Movers)
		{
			Mover->SetShouldClose();
		}
	}
	else
	{
		DoorRotator->SetShouldRotate(false);
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

void UTriggerComponent::SetDoorRotator(UDoorRotator* NewDoorRotator)
{
	DoorRotator = NewDoorRotator;
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

void UTriggerComponent::DestroyActorWithDelay(AActor* Actor, float Delay)
{
	if (Actor != nullptr)
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [Actor]()
		{
			if (Actor)
			{
				Actor->Destroy();
			}
		}, Delay, false);
	}
}
