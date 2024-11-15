// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IMover.h"
#include "Components/ActorComponent.h"
#include "RotatorIMover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API URotatorIMover : public UActorComponent, public IIMover
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotatorIMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetShouldMove(bool bShouldMove);
	UFUNCTION(BlueprintCallable) void SetDoorMesh(UStaticMeshComponent* mesh);

private:
	UPROPERTY(EditAnywhere) UStaticMeshComponent* DoorMesh;
	UPROPERTY(EditAnywhere) FRotator MoveOffset;
	UPROPERTY(EditAnywhere) bool IsReverse = false;
	UPROPERTY(EditAnywhere) float MoveTime = 4;
	bool ShouldMove = false;
	FRotator OriginalRotation;
	
};
