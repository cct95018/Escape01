// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE01_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	float Reach = 130.f;
	UPhysicsHandleComponent* PhyHandle = nullptr;
	UInputComponent* InputComp = nullptr;

	// Ray-cast and grab in reach
	void Grab();
	void Release();
	//Look for attached Physics handle
	void FindPhysicsComponent();
	void SetupInputComponent();

	//Return hit for first physics body in reach
	const FHitResult GetFirstBodyInReach();
	FVector GetReachLineStart();
	FVector GetReachLineEnd();
};
