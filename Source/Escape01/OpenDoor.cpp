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
	// ...
	Door = GetOwner();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetTotalMassOnPlate() >= 80 ) {
		//UE_LOG(LogTemp, Warning, TEXT("plateOn"));
		if (!Door->GetActorRotation().Equals(FRotator(0.f, OpenAngle, 0.f))) {
			Door->SetActorRotation(Door->GetActorRotation() + FRotator(0.f, 0.1f, 0.f));
		}
		LastOpenTime = GetWorld()->GetTimeSeconds();
	}
	else {
		Door->SetActorRotation(FRotator(0.f, -90.f, 0.f));
	}
}

void UOpenDoor::SetDoor(int32 i) {
	/*if (i == 1 && !Door->GetActorRotation().Equals(FRotator(0.f, OpenAngle, 0.f))) {
		Door->SetActorRotation(Door->GetActorRotation() + FRotator(0.f, .5f, 0.f));
	}
	else {
		Door->SetActorRotation(FRotator(0.f, -90.f, 0.f));
	}*/

}

float UOpenDoor::GetTotalMassOnPlate() {
	float TotalMass = 0.f;
	//Create TArray for AActor
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto& Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s On Plate"), *Actor->GetName());
	}
	return TotalMass;
}
