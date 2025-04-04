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

	void SetShouldMove(bool ShouldMove);

	bool GetShouldMove() const;

	UPROPERTY(BlueprintAssignable)
	FOnPlaySound OnPlaySound;

	UPROPERTY(BlueprintAssignable)
	FOnStopSound OnStopSound;
	
private:
	UPROPERTY(EditAnywhere)
	FVector MoveOffset;

	UPROPERTY(EditAnywhere)
	float MoveTime = 4;


	bool ShouldMove = false;

	public:
		UPROPERTY(BlueprintReadOnly)
	FVector OriginalLocation;

	UPROPERTY(BlueprintReadWrite)
	bool ShouldPlaySFX = false;

	UPROPERTY(BlueprintReadOnly)
	FVector TargetLocation;
};
