// Fill out your copyright notice in the Description page of Project Settings.


#include "Boost.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "SnakeBase.h"

// Sets default values
ABoost::ABoost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoost::BeginPlay()
{
	Super::BeginPlay();

	IncreaseSpeed = 0.05f;
	
}

// Called every frame
void ABoost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABoost::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			Snake->BufferTime = 0;
			Snake->SetActorTickInterval(IncreaseSpeed);
			Destroy();
		}
	}
}