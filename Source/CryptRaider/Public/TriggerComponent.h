// Fill out your copyright notice in the  page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
public:
	UTriggerComponent();
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable) void SetMover(TScriptInterface<IIMover> Mover);
private:
	UPROPERTY(EditAnywhere) FName AdmittedTag;
	AActor* GetAdmittedActor() const;
	TScriptInterface<IIMover> Mover;
};

