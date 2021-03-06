// Copyright Conner Linskens 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Floor.generated.h"


UCLASS()
class FARBERACING_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DestroyStaticMesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	APlayerController* PlayerController = nullptr;

	AActor* PlayerCar = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float DefaultSpeed = 5000;

};
