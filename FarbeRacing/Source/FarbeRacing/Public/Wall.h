// Copyright Conner Linskens 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Wall.generated.h"

UCLASS()
class FARBERACING_API AWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWall(const FObjectInitializer& objectInitializer);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* mesh = nullptr;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* collision = nullptr;

	UFUNCTION()
	void OnDelegateOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:
	APlayerController* PlayerController = nullptr;
	AActor* PlayerCar = nullptr;
	FString PlayerCarName;

	UPROPERTY(EditAnywhere)
	float DefaultSpeed = 5000;

private:
	void MoveWall();

	void EndGame();

};
