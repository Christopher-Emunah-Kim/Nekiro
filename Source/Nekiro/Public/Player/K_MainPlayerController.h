// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"

#include "K_MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NEKIRO_API AK_MainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent() override;

private:
	void OnPlayerLook(const FInputActionValue& value);

private:
	int32 gameInputPriority = 1;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NEKIRO|Input")
	TObjectPtr<class UInputMappingContext> IMC_Player;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NEKIRO|Input")
	TObjectPtr<class UInputAction> IA_Look;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NEKIRO|CameraPitch")
	float maxCameraPitch = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NEKIRO|CameraPitch")
	float minCameraPitch = -50.f;

};



