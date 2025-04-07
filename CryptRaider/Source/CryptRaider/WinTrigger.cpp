// Fill out your copyright notice in the Description page of Project Settings.


#include "WinTrigger.h"

// Sets default values for this component's properties
UWinTrigger::UWinTrigger()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UWinTrigger::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UWinTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UWinTrigger::CollectSword(AActor* Actor)
{
	Actor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());

	Component->SetSimulatePhysics(false);
	Actor->Tags.Remove("Grabbable");
}