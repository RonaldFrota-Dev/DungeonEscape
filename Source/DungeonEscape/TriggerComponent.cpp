// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (MoverActor)
	{
		Mover = MoverActor->FindComponentByClass<UMoverComponent>();
		if (Mover)
		{
			UE_LOG(LogTemp, Display, TEXT("Successfully found the mover component!"));
			
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Failed to find mover component!"));
		}
	}
	else
	{
		 UE_LOG(LogTemp, Error, TEXT("UMoverComponent is nullptr!"));
	}
	
	if (IsPressurePlate)
	{
		OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
		OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
	}
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTriggerComponent::Trigger(bool NewTriggerValue)
{
	IsTriggered = NewTriggerValue;
	if (Mover)
	{
		Mover->SetShouldMove(IsTriggered);
	}
}

void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
	{
		ActivatorCount++;
		if (!IsTriggered)
		{
			Trigger(true);
		}
	}
}

void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
	{
		ActivatorCount--;
		if (IsTriggered && ActivatorCount == 0)
		{
			Trigger(false);
		}
	}
}
