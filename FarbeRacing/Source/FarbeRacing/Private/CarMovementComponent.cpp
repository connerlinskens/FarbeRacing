// Fill out your copyright notice in the Description page of Project Settings.

#include "CarMovementComponent.h"


// Sets default values for this component's properties
UCarMovementComponent::UCarMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCarMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCarMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCarMovementComponent::Move(float Direction, float Distance) 
{
	UE_LOG(LogTemp, Warning, TEXT("going to: %f with direction: %f"), Distance, Direction);
}