// Fill out your copyright notice in the Description page of Project Settings.

#include "Car.h"
#include "CarMovementComponent.h"
#include "GameFramework/Actor.h"
#include "UnrealMathUtility.h"
#include "Engine/World.h"


// Sets default values
ACar::ACar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CarMovementComponent = CreateDefaultSubobject<UCarMovementComponent>(FName("Movement Component"));

}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//GoForward();

}

// Called to bind functionality to input
void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACar::GoForward()
{
	auto ForwardDistanceChange = ForwardSpeed * GetWorld()->DeltaTimeSeconds;
	auto NewDistanceForward = GetActorLocation().X + ForwardDistanceChange;
	SetActorRelativeLocation(FVector(NewDistanceForward, GetActorLocation().Y, CarHeight));
}

void ACar::DestroyStaticMesh(AActor* Car)
{
	Car->GetRootComponent()->DestroyComponent(false);
}

// Fix this pls
FString ACar::GetScore(float ScoreMultiplier)
{
	float ScoreChange = GetWorld()->GetUnpausedTimeSeconds() * ScoreMultiplier;
	score += ScoreChange;
	return FString::FromInt(score);
}
