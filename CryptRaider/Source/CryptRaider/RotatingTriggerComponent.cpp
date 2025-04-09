// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingTriggerComponent.h"

// Sets default values for this component's properties
URotatingTriggerComponent::URotatingTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void URotatingTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void URotatingTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bDoorHasRotated)
		return;
	
	if (DoorRotator == nullptr)
		return;

	AActor* Actor = GetAcceptableActor();
	if (Actor == nullptr)
		return;

	UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
	if (Component == nullptr)
		return;

	Actor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Component->SetSimulatePhysics(false);

	DoorRotate(Actor);
	
}

void URotatingTriggerComponent :: SetDoorRotator(UDoorRotator* NewDoorRotator)
{
	DoorRotator = NewDoorRotator;
}

void URotatingTriggerComponent::DoorRotate(AActor* Actor)
{
	if (!bPlayAudio)
	{
		StartAudioEvent.Broadcast();
		bPlayAudio = true;
	}
	
	DoorRotator->SetShouldRotate(true);

	DestroyActorWithDelay(Actor, 2.0f);
	bDoorHasRotated = true;
}

void URotatingTriggerComponent::DestroyActorWithDelay(AActor* Actor, float Delay)
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


AActor* URotatingTriggerComponent :: GetAcceptableActor() const
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

