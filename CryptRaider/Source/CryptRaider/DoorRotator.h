// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorRotator.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlaySfx);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopSfx);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UDoorRotator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorRotator();

	UPROPERTY(BlueprintAssignable)
	FOnPlaySfx OnPlaySound;
	
	UPROPERTY(BlueprintAssignable)
	FOnStopSfx OnStopSound;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldRotate(bool ShouldRotate);

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	float OpenAngle;
	
	UPROPERTY(EditAnywhere, Category = "Door Settings")
	float OpenSpeed = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	bool ShouldOpen;

	UPROPERTY(EditAnywhere, Category = "Door Settings")
	UStaticMeshComponent* DoorComponent;

	UPROPERTY(BlueprintReadOnly)
	FRotator TargetRotation;

private:
	UPROPERTY(VisibleAnywhere, Category = "Door Settings")
	FRotator InitialRotation;

	bool ShouldPlaySound;

	
	
};
