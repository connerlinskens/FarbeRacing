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

	CheckFloorSpawn();

	if (GetWorld()->GetUnpausedTimeSeconds() > DifficultyTimer) { DifficultyIncreaser(); }
}

void AFloorSpawner::CheckFloorSpawn()
{
	bool bIsReady = (GetWorld()->GetUnpausedTimeSeconds() - GeneralLastSpawnTime) > SpawnRate;
	if (SpawnableFloors[0] == nullptr) { return; }

	if (bIsReady)
	{
		int32 RandFloorIndex1 = FMath::RandRange(0, SpawnableFloors.Num() - 1);
		int32 RandomLoc1;

		while (bReadyForSpawning1 == false)
		{
			RandomLoc1 = GetRandomSpawnLocation(bReadyForSpawning1);
		}

		bReadyForSpawning1 = false;

		// randomly decides whether to spawn 1 or 2 floors
		int32 random = FMath::RandRange(1, 100);
		if (random < 25)
		{
			int32 RandomLoc2 = 0;
			while (bReadyForSpawning2 == false && RandomLoc2 != RandomLoc1)
			{
				RandomLoc2 = GetRandomSpawnLocation(bReadyForSpawning2);
			}

			bReadyForSpawning2 = false;

			int32 RandFloorIndex2 = FMath::RandRange(0, SpawnableFloors.Num() - 1);

			SpawnFloor(RandFloorIndex2, RandomLoc2);
		}

		// Regular spawn (this always spawns)
		SpawnFloor(RandFloorIndex1, RandomLoc1);

		GeneralLastSpawnTime = GetWorld()->GetUnpausedTimeSeconds();
	}	
}

int32 AFloorSpawner::GetRandomSpawnLocation(bool& ReadyForSpawning)
{
	// Gets random spawn location and checks if it isn't the same place twice
	int32 RandLocIndex;

		RandLocIndex = FMath::RandRange(0, SpawnLocations.Num() - 1);

		if (RandLocIndex == 0)
		{
			if (bSpawnedMiddle == true)
			{
				return RandLocIndex;
			}
			else
			{
				bSpawnedMiddle = true;
				MiddleSpawnTime = GetWorld()->GetUnpausedTimeSeconds();
				ReadyForSpawning = true;
			}
		}
		else if (RandLocIndex == 1)
		{
			if (bSpawnedLeft == true)
			{
				return RandLocIndex;
			}
			else
			{
				bSpawnedLeft = true;
				LeftSpawnTime = GetWorld()->GetUnpausedTimeSeconds();
				ReadyForSpawning = true;
			}
		}
		else if (RandLocIndex == 2)
		{
			if (bSpawnedRight == true)
			{
				return RandLocIndex;
			}
			else
			{
				bSpawnedRight = true;
				RightSpawnTime = GetWorld()->GetUnpausedTimeSeconds();
				ReadyForSpawning = true;
			}
		}

	if ((GetWorld()->GetUnpausedTimeSeconds() - SpawnDelay) > MiddleSpawnTime) { bSpawnedMiddle = false; }
	if ((GetWorld()->GetUnpausedTimeSeconds() - SpawnDelay) > LeftSpawnTime) { bSpawnedLeft = false; }
	if ((GetWorld()->GetUnpausedTimeSeconds() - SpawnDelay) > RightSpawnTime) { bSpawnedRight = false; }

	return RandLocIndex;
}

void AFloorSpawner::SpawnFloor(int32 RandFloorIndex, int32 RandomLocIndex)
{
	auto SpawnedFloor = GetWorld()->SpawnActor<AFloor>(
		SpawnableFloors[RandFloorIndex],
		FVector(GetActorLocation().X, SpawnLocations[RandomLocIndex], FloorZPos),
		FRotator(GetActorRotation().Pitch, 90, GetActorRotation().Roll)
		);
}

void AFloorSpawner::DifficultyIncreaser()
{
	if (SpawnRate > 0.4)
	{
		SpawnRate -= DifficultyIncFactor;
		SpawnDelay -= 0.1f;
		DifficultyTimer += 60;
	}
}