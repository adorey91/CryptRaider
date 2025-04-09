// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mover.h"
#include "Components/BoxComponent.h"
#include "WeightedTriggerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeightedAudioStartEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeightedAudioEndEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UWeightedTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeightedTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FWeightedAudioStartEvent StartAudioEvent;

	UPROPERTY(BlueprintAssignable)
	FWeightedAudioEndEvent EndAudioEvent;

	UFUNCTION(BlueprintCallable)
	void SetMover(UMover* Mover);

	UFUNCTION(BlueprintCallable)
	void CheckCurrentWeight();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Trigger")
	float WeightNeeded = 160;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Trigger")
	float CurrentWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Trigger")
	bool CanCheckWeight;

	UMover* Mover;

	UFUNCTION()
	void OpenDoor();

	UFUNCTION()
	void CloseDoor();

	bool bPlayAudio = false;

private:
	bool bIsOpenDoor = true;

	void CheckCurrentWeightLoop();
	
	FTimerHandle WeightCheckTimerHandle;

};
