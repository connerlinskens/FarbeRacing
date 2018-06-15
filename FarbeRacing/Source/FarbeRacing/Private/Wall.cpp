// Copyright Conner Linskens 2018

#include "Wall.h"
#include "Kismet/GameplayStatics.h"
#include "Car.h"


// Sets default values
AWall::AWall(const FObjectInitializer& objectInitializer)
	:Super(objectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));

	RootComponent = Cast<USceneComponent>(mesh);

	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepRelative, false);

	collision->AttachToComponent(RootComponent, AttachmentTransformRules);

	RootComponent->SetRelativeRotation(FRotator(0, 90, 0));
	collision->SetRelativeLocation(FVector(200, 0, 200));
	collision->SetBoxExtent(FVector(200, 10, 200));
	collision->OnComponentBeginOverlap.AddDynamic(this, &AWall::OnDelegateOverlap);
	
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCar = GetWorld()->GetFirstPlayerController()->GetPawn();
	PlayerCarName = PlayerCar->GetName();
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWall::OnDelegateOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor->GetName() == PlayerCarName) && (OtherActor != nullptr) && (OtherComp != nullptr))
	{
		PlayerCar->GetRootComponent()->DestroyComponent();
		FTimerHandle delay;
		GetWorldTimerManager().SetTimer(delay, this, &AWall::EndGame, 2, false);
	}
}

void AWall::EndGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetMapName()));
}