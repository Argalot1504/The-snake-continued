// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "PlayerPawnBase.h"
#include "Interactable.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 10.f;
	LastMoveDirection = EMovementDirection::DOWN;
	bIsMoved = false;
	
	StepDelay = 2.f;
	BufferTime = 0;
	
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(5);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();

	BufferTime += DeltaTime;
	if (BufferTime >= StepDelay)
	{
		SetActorTickInterval(MovementSpeed);
		BufferTime = 0;
	}

}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	
	for (int i = 0; i < ElementsNum; ++i)
    {
		int InX = SnakeElements.Num() * ElementSize;
		if (ElementsNum == 1)
		{
			InX = SnakeElements[SnakeElements.Num() - 1]->GetActorLocation().X * ElementSize;
		}
		FVector NewLocation(InX, 0, 0);
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElement = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		NewSnakeElement->SnakeOwner = this;
		int32 ElementIndex = SnakeElements.Add(NewSnakeElement);
		
		if (ElementIndex == 0)
		{
			NewSnakeElement->SetFirstElementType();
		}
		
		
	}
}

void ASnakeBase::Move()
{
	FVector MovementVector(FVector::ZeroVector);
	FRotator NewRotator;
	

	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += ElementSize;
		break; 
	case EMovementDirection::DOWN:
		MovementVector.X -= ElementSize;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += ElementSize;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= ElementSize;
		break;
	}

	//AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleColision();
	SnakeElements[0]->SetHidden(false);
	
	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PreviousElement = SnakeElements[i - 1];
		FVector PreviousLocation = PreviousElement->GetActorLocation();
		CurrentElement->SetActorLocation(PreviousLocation);
		CurrentElement->SetHidden(false);
	}
	
	SnakeElements[0]->AddActorWorldOffset(MovementVector); 
	SnakeElements[0]->ToggleColision();
	bIsMoved = false;
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElementIndex;
		SnakeElements.Find(OverlappedElement, ElementIndex);
		const bool bIsHead = ElementIndex == 0;
        IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsHead);
		}
	}
}

