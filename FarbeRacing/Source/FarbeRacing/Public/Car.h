// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "Car.generated.h"

class UCarMovementComponent;

UCLASS()
class FARBERACING_API ACar : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	float CarHeight = 250;

	UPROPERTY(EditDefaultsOnly)
	float ForwardSpeed = 2500;

	UPROPERTY(EditDefaultsOnly)
	float ScoreIncrease = 1;

	float ScoreDelay = 0.1;
	double LastScoreAdd = 0;

	int32 score = 0;

private:
	void GoForward();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this pawn's properties
	ACar();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UCarMovementComponent* CarMovementComponent = nullptr;

	void DestroyStaticMesh(AActor* Car);

	UFUNCTION(BlueprintCallable, Category = "Score")
	FString GetScore(float ScoreMultiplier);

};
