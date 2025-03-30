// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Actor.h"
#include "TriggerComponent.h"

#include "Math/UnitConversion.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}


void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FString ThisName = GetOwner()->GetName();
    
    if (!Mover)  // Check if Mover is null
    {
        UE_LOG(LogTemp, Error, TEXT("Mover is null in UTriggerComponent! Did you forget to call SetMover? %s"), *ThisName);
        return;
    }
    
    AActor* Actor = GetAcceptableActor();
    if(Actor != nullptr)
    {
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if(Component != nullptr)
        {
            Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
            Component->SetSimulatePhysics(false);
        }
        Mover->SetShouldMove(true);
        
    }
    else
    {
        Mover->SetShouldMove(false);
    }
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
    if (NewMover)
    {
        Movers.Add(NewMover);
    }
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    
    for(AActor* Actor : Actors)
    {
        if(Actor->ActorHasTag(UnlockTag) && !Actor->ActorHasTag("Grabbed"))
        {
            return Actor;
        }
    }

    return nullptr;
}
