// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Escape01.h"
#include "PosReporter.h"


// Sets default values for this component's properties
UPosReporter::UPosReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPosReporter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FString ObjName = GetOwner()->GetName();
	FString ObjPos = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("Pos report for %s at %s"), *ObjName, *ObjPos);
	
}


// Called every frame
void UPosReporter::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

