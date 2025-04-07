// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "DoorRotator.h"
#include "TriggerComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

	public:
	UTriggerComponent();

protected:
// Called when the game starts
virtual void BeginPlay() override;

public:	
// Called every frame
virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

UPROPERTY(BlueprintAssignable)
	FStartEvent StartAudioEvent;
	
UFUNCTION(BlueprintCallable)
void SetMover(UMover* Mover);

UFUNCTION(BlueprintCallable)
void SetMultipleMovers(TArray<UMover*> Mover);

	UFUNCTION(BlueprintCallable)
	void SetDoorRotator(UDoorRotator* DoorRotator);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Trigger")
	float WeightNeeded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Trigger")
	float CurrentWeight;

	UPROPERTY(EditAnywhere)
	bool WeightedTrigger;
private:

UPROPERTY(EditAnywhere)
FName UnlockTag;

	UPROPERTY(EditAnywhere)
	bool MovesObjects;

	UPROPERTY(EditAnywhere)
	bool RotatesDoor;


	UFUNCTION()
	void MoveObjects();

	UFUNCTION()
	void DoorRotate(AActor* Actor);

	UFUNCTION()
	void DontMove();

	TArray<UMover*> Movers;

	UDoorRotator* DoorRotator;

AActor* GetAcceptableActor() const;

	bool PlayAudio = false;

	bool Triggered = false;

	UFUNCTION()
	void DestroyActorWithDelay(AActor* Actor, float Delay);
};
