// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorRotator.h"

// Sets default values for this component's properties
UDoorRotator::UDoorRotator()
{
    PrimaryComponentTick.bCanEverTick = true;
    DoorComponent = nullptr;
}



// Called when the game starts
void UDoorRotator::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
    if (Owner)
    {
        TArray<UStaticMeshComponent*> MeshComponents;
        Owner->GetComponents<UStaticMeshComponent>(MeshComponents);

        for (UStaticMeshComponent* MeshComp : MeshComponents)
        {
			if (MeshComp->GetName() == TEXT("SM_Cell_Door"))
            {
				DoorComponent = MeshComp;
				UE_LOG(LogTemp, Warning, TEXT("Found Mesh Component: %s"), *MeshComp->GetName());
                break;
            }
        }

        if (!DoorComponent)
        {
            UE_LOG(LogTemp, Error, TEXT("SM_Cell_Door NOT found! Extra components may have been created."));
        }
        else
        {
            InitialRotation = DoorComponent->GetComponentRotation();
            TargetRotation = InitialRotation + FRotator(0.0f, OpenAngle, 0.0f);
        }
    }
}

// Called every frame
void UDoorRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(ShouldOpen)
	{
		FRotator CurrentRotation = DoorComponent->GetComponentRotation();
		if (CurrentRotation.Equals(TargetRotation, 2.0f))
		{
			ShouldOpen = false;
			OnStopSound.Broadcast();
			return;
		}
		
        FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, OpenSpeed);
        DoorComponent->SetWorldRotation(NewRotation);

		if (!ShouldPlaySound)
		{
			OnPlaySound.Broadcast();
			ShouldPlaySound = true;
		}
	}
}

void UDoorRotator::SetShouldRotate(bool ShouldRotate)
{
	ShouldOpen = ShouldRotate;
}
