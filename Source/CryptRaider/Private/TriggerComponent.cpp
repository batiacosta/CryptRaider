// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	UE_LOG(LogTemp, Display, TEXT("Starting Triggercomponent"));
}
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFuntion)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFuntion);
	AActor* OverlappingActor = GetAdmittedActor();
	if (OverlappingActor == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Not acceptable"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Acepted actor is: %s"), *OverlappingActor->GetActorNameOrLabel());
	}
}
AActor* UTriggerComponent::GetAdmittedActor() const
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	for(AActor* OverlappingActor : OverlappingActors)
	{
		FString OverlappingActorName = OverlappingActor->GetName();
		if (OverlappingActor->ActorHasTag(AdmittedTag))
		{
			return OverlappingActor;
		}
	}
	return nullptr;
}

