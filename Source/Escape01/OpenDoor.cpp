// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Escape01.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay() {
	Super::BeginPlay();
	// ...
	Door = GetOwner();
	ActorPlayer = GetWorld()->GetFirstPlayerController()->GetPawn();
	Timer = GetWorld()->GetTimeSeconds();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Timer = GetWorld()->GetTimeSeconds();
	if (PressurePlate->IsOverlappingActor(ActorPlayer)) {
		//UE_LOG(LogTemp, Warning, TEXT("plateOn"));
		if (!Door->GetActorRotation().Equals(FRotator(0.f, OpenAngle, 0.f))) {
			Door->SetActorRotation(Door->GetActorRotation() + FRotator(0.f, 0.1f, 0.f));
		}
		LastOpenTime = GetWorld()->GetTimeSeconds();
	}
	else {
		Door->SetActorRotation(FRotator(0.f, -90.f, 0.f));
	}
	/*	if (GetWorld()->GetTimeSeconds() - LastOpenTime > 1) {
			SetDoor(0);
		}*/
}

void UOpenDoor::SetDoor(int32 i) {
	/*if (i == 1 && !Door->GetActorRotation().Equals(FRotator(0.f, OpenAngle, 0.f))) {
		Door->SetActorRotation(Door->GetActorRotation() + FRotator(0.f, .5f, 0.f));
	}
	else {
		Door->SetActorRotation(FRotator(0.f, -90.f, 0.f));
	}*/

}
