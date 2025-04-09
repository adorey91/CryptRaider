// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DoorRotator.h"
#include "RotatingTriggerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRotatingAudioStartEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRotatingAudioEndEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API URotatingTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotatingTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetDoorRotator(UDoorRotator* DoorRotator);
	
UPROPERTY(EditAnywhere)
	FName UnlockTag;

	UFUNCTION()
	void DoorRotate(AActor* Actor);

	UFUNCTION()
	void DestroyActorWithDelay(AActor* Actor, float Delay);

	UDoorRotator* DoorRotator;

	AActor* GetAcceptableActor() const;

	bool bTriggered = false;

	bool bPlayAudio	 = false;

	bool bDoorHasRotated = false;

	UPROPERTY(BlueprintAssignable)
	FRotatingAudioStartEvent StartAudioEvent;

	UPROPERTY(BlueprintAssignable)
	FRotatingAudioEndEvent EndAudioEvent;
};
