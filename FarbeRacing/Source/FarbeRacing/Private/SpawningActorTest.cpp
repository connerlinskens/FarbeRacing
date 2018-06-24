// Copyright Conner Linskens 2018

#include "SpawningActorTest.h"
#include "Engine/World.h"

// Sets default values
ASpawningActorTest::ASpawningActorTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Cast<USceneComponent>(mesh);
}

// Called when the game starts or when spawned
void ASpawningActorTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawningActorTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if ((GetWorld()->GetUnpausedTimeSeconds() - SpawnRate) > LastSpawn)
	{

		LastSpawn = GetWorld()->GetUnpausedTimeSeconds();

		// Gets a random floor 
		int32 RandFloorIndex1 = FMath::RandRange(0, SpawnableFloors.Num() - 1);

		
		int32 RandomLocIndex1 = GetRandomSpawnLocation(bReadyForSpawningFloor1);


		/** Spawns a floor everytime*/
		SpawnActor(
			RandFloorIndex1,
			FVector(GetActorLocation().X, SpawnLocations[RandomLocIndex1], GetActorLocation().Z),
			FRotator(GetActorRotation().Pitch, 90, GetActorRotation().Roll)
		);

		bReadyForSpawningFloor1 = false;


		/** Determines whether to spawn a second floor*/
		int32 random = FMath::RandRange(1, 100);
		if (random < 50)
		{
			int32 RandFloorIndex2 = FMath::RandRange(0, SpawnableFloors.Num() - 1);

			int32 RandomLocIndex2;
			do
			{
				RandomLocIndex2 = GetRandomSpawnLocation(bReadyForSpawningFloor2);
			} while (RandomLocIndex1 == RandomLocIndex2);

			SpawnActor(
				RandFloorIndex2,
				FVector(GetActorLocation().X, SpawnLocations[RandomLocIndex2], GetActorLocation().Z),
				FRotator(GetActorRotation().Pitch, 90, GetActorRotation().Roll)
			);

			bReadyForSpawningFloor2 = false;
		}
	}
}

void ASpawningActorTest::SpawnActor(int32 FloorColor, FVector spawnPos, FRotator spawnRot)
{
	auto spawnedActor = GetWorld()->SpawnActor<AActor>(
		SpawnableFloors[FloorColor],
		spawnPos,
		spawnRot);
}

// Gets random spawn location and checks if it isn't the same place twice
int32 ASpawningActorTest::GetRandomSpawnLocation(bool& ReadyForSpawning)
{
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
