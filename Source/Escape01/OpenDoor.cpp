// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Escape01.h"
#include "OpenDoor.h"
#define OUT

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

	Door = GetOwner();
	if (!PressurePlate) {
		UE_LOG(LogTemp, Warning, TEXT("Missing Plate on "), *Door->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetTotalMassOnPlate() >= 30 ) {
		//UE_LOG(LogTemp, Warning, TEXT("plateOn"));
		OnOpen.Broadcast();
	}
	else {
		OnClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOnPlate() {
	float TotalMass = 0.f;
	//Create TArray for AActor
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto& Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("%s On Plate"), *Actor->GetName());
	}
	return TotalMass;
}
