// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlaySound);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopSound);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetShouldOpen();
	
	void SetShouldClose();

	UPROPERTY(BlueprintAssignable)
	FOnPlaySound OnPlaySound;

	UPROPERTY(BlueprintAssignable)
	FOnStopSound OnStopSound;
	
private:
	void WillOpen(float DeltaTime);

	void WillClose(float DeltaTime);

	void ResetVariables();
	
	// Vector location
	FVector CurrentLocation;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FVector StartingLocation;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FVector TargetLocation;

	// Move Offset & Time
	UPROPERTY(EditAnywhere)
	FVector MoveOffset;

	UPROPERTY(EditAnywhere)
	float MoveTime = 4;

	bool ShouldPlaySfx;

	bool ShouldMove;

	bool ShouldOpen;
	
	bool ShouldClose;
};
