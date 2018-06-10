// Copyright Conner Linskens 2018

#include "FloorSpawner.h"
#include "Engine/World.h"
#include "Containers/Array.h"
#include "UnrealMathUtility.h"


// Sets default values
AFloorSpawner::AFloorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFloorSpawner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFloorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnFloor();

	if (GetWorld()->GetUnpausedTimeSeconds() > DifficultyTimer) { DifficultyIncreaser(); }
}

void AFloorSpawner::SpawnFloor()
{
	bool bIsReady = (GetWorld()->GetUnpausedTimeSeconds() - GeneralLastSpawnTime) > SpawnRate;
	if (SpawnableFloors[0] == nullptr) { return; }

	if (bIsReady)
	{
		int32 RandFloorIndex = FMath::RandRange(0, SpawnableFloors.Num() - 1);

		// Gets random spawn location and checks if it isn't the same place twice
		int32 RandLocIndex;
		bool bReadyForSpawning = false;
		while (bReadyForSpawning == false)
		{ 
			RandLocIndex = FMath::RandRange(0, SpawnLocations.Num() - 1);

			if (RandLocIndex == 0)
			{
				if (bSpawnedMiddle == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Middle return!"));
					return;
				}
				else
				{
					bSpawnedMiddle = true;
					MiddleSpawnTime = GetWorld()->GetUnpausedTimeSeconds();
					bReadyForSpawning = true;
				}
			}
			else if (RandLocIndex == 1)
			{
				if (bSpawnedLeft == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Left return!"));
					return;
				}
				else
				{
					bSpawnedLeft = true;
					LeftSpawnTime = GetWorld()->GetUnpausedTimeSeconds();
					bReadyForSpawning = true;
				}
			}
			else if (RandLocIndex == 2)
			{
				if (bSpawnedRight == true)
				{
					UE_LOG(LogTemp, Warning, TEXT("Right return!"));
					return;
				}
				else
				{
					bSpawnedRight = true;
					RightSpawnTime = GetWorld()->GetUnpausedTimeSeconds();
					bReadyForSpawning = true;
				}
			}
		}

		bReadyForSpawning = false;

		// Spawns the floor
		auto SpawnedFloor = GetWorld()->SpawnActor<AFloor>(
			SpawnableFloors[RandFloorIndex],
			FVector(GetActorLocation().X, SpawnLocations[RandLocIndex], FloorZPos),
			FRotator(GetActorRotation().Pitch, 90, GetActorRotation().Roll)
			);

		GeneralLastSpawnTime = GetWorld()->GetUnpausedTimeSeconds();

		if ((GetWorld()->GetUnpausedTimeSeconds() - SpawnDelay) > MiddleSpawnTime) { bSpawnedMiddle = false; }
		if ((GetWorld()->GetUnpausedTimeSeconds() - SpawnDelay) > LeftSpawnTime) { bSpawnedLeft = false; }
		if ((GetWorld()->GetUnpausedTimeSeconds() - SpawnDelay) > RightSpawnTime) { bSpawnedRight = false; }
	}	
}

void AFloorSpawner::DifficultyIncreaser()
{
		SpawnRate -= DifficultyIncFactor;
		SpawnDelay -= 0.1f;
		DifficultyTimer += 60;
}