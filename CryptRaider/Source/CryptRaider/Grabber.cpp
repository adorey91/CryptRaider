// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "KismetTraceUtils.h"
#include "Chaos/Deformable/ChaosDeformableCollisionsProxy.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();
	
	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);


	if (HasHit)
	{
		UPrimitiveComponent *HitComponent = HitResult.GetComponent();

		// Makes sure player can only pick up grabbable things, needed this so I can block the line trace
		if (!HitResult.GetActor()->ActorHasTag("Grabbable"))
		{
			return;
		}
		
		if (HitComponent != nullptr)
		{
			HitComponent->SetSimulatePhysics(true);
			HitComponent->WakeAllRigidBodies();
			HitResult.GetActor()->Tags.Add("Grabbed");
		}
		
		// UE_LOG(LogTemp, Display, TEXT("Grabbed: %s"), *HitResult.GetActor()->GetName());
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation());
	}
}

void UGrabber::Release()
{
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();
	
	if(PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor->Tags.Remove("Grabbed");
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
}

UPhysicsHandleComponent *UGrabber::GetPhysicsHandle() const
{
	FVector Start = GetComponentLocation();
	FVector End =  Start + GetForwardVector() * MaxGrabDistance;
	// DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	UPhysicsHandleComponent *Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber Requires A Physics Handle Component"));
	}

	return Result;
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	// DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere);
}

void UGrabber::CheckForHighlight()
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance * 2;

	bool HasHit = false;
	TArray<FHitResult> HitResults;

	DrawDebugSphereTraceMulti(GetWorld(), Start, End, GrabRadius, EDrawDebugTrace::ForDuration,
	HasHit, HitResults, FColor::Blue, FColor::Red, 1.0f);
	
	if (HasHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit actor: %s"), *HitActor->GetName());
			}
		}
	}
}

