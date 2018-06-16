// Copyright Conner Linskens 2018

#pragma once

#include "CoreMinimal.h"
#include "Floor.h"
#include "GameFramework/Actor.h"
#include "FloorSpawner.generated.h"

UCLASS()
class FARBERACING_API AFloorSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFloorSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AFloor>> SpawnableFloors;

	UPROPERTY(EditDefaultsOnly)
	float SpawnRate = 1.2f;

	double GeneralLastSpawnTime = 0;

	UPROPERTY(EditDefaultsOnly)
	TArray<float> SpawnLocations;

	UPROPERTY(EditDefaultsOnly)
	float FloorZPos = -210;

	UPROPERTY(EditDefaultsOnly)
	float SpawnDelay = 0.6f;

	bool bSpawnedMiddle = false;
	bool bSpawnedLeft = false;
	bool bSpawnedRight = false;

	double MiddleSpawnTime = 0;
	double LeftSpawnTime = 0;
	double RightSpawnTime = 0;

	UPROPERTY(EditDefaultsOnly)
	double DifficultyTimer = 60;

	UPROPERTY(EditDefaultsOnly)
	float DifficultyIncFactor = 0.2;

	bool bReadyForSpawning = false;

private:
	void SpawnFloor();

	int32 GetRandomSpawnLocation();

	void DifficultyIncreaser();
};
