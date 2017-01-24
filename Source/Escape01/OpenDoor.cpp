// Fill out your copyright notice in the Description page of Project Settings.

#include "Escape01.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	// ...
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	// ...

	AActor* Owner = GetOwner();
	FRotator MaxRotation = FRotator(0.f, OpenAngle, 0.f);
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		if (!Owner->GetActorRotation().Equals(MaxRotation)) {
			FRotator NewRotation = Owner->GetActorRotation() + FRotator(0.f, 1.0f, 0.f);
			Owner->SetActorRotation(NewRotation);
		}
	}
	else if (!Owner->GetActorRotation().Equals(FRotator(0.f, 0.f, 0.f))) {
			FRotator NewRotation = Owner->GetActorRotation() + FRotator(0.f, -1.0f, 0.f);
			Owner->SetActorRotation(NewRotation);
		}	
}

