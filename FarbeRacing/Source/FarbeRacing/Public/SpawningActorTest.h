// Copyright Conner Linskens 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Floor.h"
#include "SpawningActorTest.generated.h"

UCLASS()
class FARBERACING_API ASpawningActorTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawningActorTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TArray<float> SpawnLocations;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AFloor>> SpawnableFloors;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere)
	float SpawnDelay = 0.6f;

	float SpawnRate = 1.2f;
	float LastSpawn = 0;

	bool bSpawnedMiddle = false;
	bool bSpawnedLeft = false;
	bool bSpawnedRight = false;

	double MiddleSpawnTime = 0;
	double LeftSpawnTime = 0;
	double RightSpawnTime = 0;

	bool bReadyForSpawningFloor1 = false;
	bool bReadyForSpawningFloor2 = false;

private:
	void SpawnActor(int32 FloorColor, FVector spawnPos, FRotator spawnRot);
	
	int32 GetRandomSpawnLocation(bool& ReadyForSpawning);
};
