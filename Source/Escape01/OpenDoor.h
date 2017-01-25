// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPE01_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//Door
	void SetDoor(int32);

private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = 300.f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
	UPROPERTY(EditAnywhere)

	AActor* ActorPlayer;
	AActor* Door;
	float DoorCloseDelay = 1.f;
	float LastOpenTime;
	float Timer = 0.f;

};
