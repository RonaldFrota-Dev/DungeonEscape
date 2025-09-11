// Fill out your copyright notice in the Description page of Project Settings.


#include "MoverComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	// Pointers Practice
	/*float MyFloat = 10.0f;
	float* FloatPtr = &MyFloat;

	float Result = *FloatPtr + 5.0f;
	UE_LOG(LogTemp, Warning, TEXT("Result: %f"), Result);

	*FloatPtr = 30.0f;
	UE_LOG(LogTemp, Warning, TEXT("MyFloat: %f"), MyFloat);
	UE_LOG(LogTemp, Warning, TEXT("*FloatPtr: %f"), *FloatPtr);
	
	UE_LOG(LogTemp, Warning, TEXT("FloatPtr: %p"), FloatPtr);
	UE_LOG(LogTemp, Warning, TEXT("FloatPtr: %p"), &MyFloat);

	// ---

	FVector MyVector = FVector(1.0f, 1.0f, 1.0f);
	FVector* VectorPtr = &MyVector;
	(*VectorPtr).X = 2.0f;
	VectorPtr->Y = 3.0f;
	VectorPtr->Z = 4.0f;

	UE_LOG(LogTemp, Warning, TEXT("My Vector: %s"), *MyVector.ToCompactString());*/
	
	StartLocation = GetOwner()->GetActorLocation();
	SetShouldMove(false);
}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector CurrentLocation = GetOwner()->GetActorLocation();
	
	ReachedTarget = CurrentLocation.Equals(TargetLocation);
	
	if (!ReachedTarget)
	{
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveOffset.Length() / MoveTime);
		GetOwner()->SetActorLocation(NewLocation);
	}
}

bool UMoverComponent::GetShouldMove()
{
	return ShouldMove;
}

void UMoverComponent::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;

	if (ShouldMove)
	{
		TargetLocation = StartLocation + MoveOffset;
	} else
	{
		TargetLocation = StartLocation;
	}
}

