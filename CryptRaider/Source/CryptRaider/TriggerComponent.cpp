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

	FString ThisName = GetOwner()->GetName();

	if (Movers.Num() == 0 && !DoorRotator) // Check if Mover is null
	{
		UE_LOG(LogTemp, Error, TEXT("Mover or Door Rotator is null in UTriggerComponent! Did you forget to call SetMover? %s"),
		       *ThisName);
		return;
	}

	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if (Component != nullptr)
		{
			Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
			Component->SetSimulatePhysics(false);
		}

		if (Movers.Num() != 0)
		{
			for (UMover* Mover : Movers)
			{
				Mover->SetShouldMove(true);
			}
		}
		else
		{
			if (!PlayAudio)
			{
				StartAudioEvent.Broadcast();
				PlayAudio = true;
			}
			DoorRotator->SetShouldRotate(true);
		}
	}
	else
	{
		if (Movers.Num() != 0)
		{
			for (UMover* Mover : Movers)
			{
				Mover->SetShouldMove(false);
			}
		}
		else
		{
			DoorRotator->SetShouldRotate(false);
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
