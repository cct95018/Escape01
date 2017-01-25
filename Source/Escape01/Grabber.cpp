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
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsComponent();
	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	
	if (PhyHandle->GrabbedComponent) {
		PhyHandle->SetTargetLocation(GetReachLineEnd());
	}
}

void UGrabber::FindPhysicsComponent() {
	PhyHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhyHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Physics Componemt: %s"), *GetOwner()->GetName());
	}
}
//Look for attached Input Component
void UGrabber::SetupInputComponent() {
	InputComp = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComp) {
		UE_LOG(LogTemp, Warning, TEXT("Input Componemt found"));
		InputComp->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComp->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Input Componemt: %s"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab ON"));

	///LINE TRACE ray-cast first actor with physics body channel set
	auto HitResult = GetFirstBodyInReach();
	auto Target = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	if (ActorHit) {
		PhyHandle->GrabComponent(
			Target,
			NAME_None,
			Target->GetOwner()->GetActorLocation(),
			true //allow rotation
		);
	}
}
void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab OFF"));
	PhyHandle->ReleaseComponent();
}



const FHitResult UGrabber::GetFirstBodyInReach() {
	///Draw red tracer
	DrawDebugLine(
		GetWorld(),
		GetReachLineStart(),
		GetReachLineEnd(),
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
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
		UE_LOG(LogTemp, Warning, TEXT("Target object %s"), *Hit.GetActor()->GetName());
	return Hit;
}

FVector UGrabber::GetReachLineStart() {
	FVector PlayerVPL;
	FRotator PlayerVPR;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerVPL, OUT PlayerVPR
	);
	return PlayerVPL;
}

FVector UGrabber::GetReachLineEnd() {
	FVector PlayerVPL;
	FRotator PlayerVPR;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerVPL, OUT PlayerVPR
	);
	return PlayerVPL + PlayerVPR.Vector() * Reach;
}
