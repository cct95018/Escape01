// Fill out your copyright notice in the Description page of Project Settings.

#include "Escape01.h"
#include "Grabber.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber duty"));
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	///Get player view point this tick
	FVector PlayerVPL;
	FRotator PlayerVPR;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerVPL, OUT PlayerVPR
	);
	UE_LOG(LogTemp, Warning, TEXT("%s & %s"), *PlayerVPL.ToString(), *PlayerVPR.ToString());
	FVector LineTracer = PlayerVPL + PlayerVPR.Vector() * Reach;
	///Draw red tracer
	DrawDebugLine(
		GetWorld(),
		PlayerVPL,
		LineTracer,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		1.f
	);
	
	///Ray-cast to reach distance
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerVPL,
		LineTracer,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
		UE_LOG(LogTemp, Warning, TEXT("We are pointing at %s"), *Hit.GetActor()->GetName());
}

