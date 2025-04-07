// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/ActorComponent.h"
#include "WinTrigger.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UWinTrigger : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWinTrigger();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Unlock")
	FName UnlockTag;

	UFUNCTION(BlueprintCallable)
	void CollectSword(AActor* Actor);
};
