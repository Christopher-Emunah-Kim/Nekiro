// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "K_MainPlayer.generated.h"


class UInputAction;

UCLASS()
class NEKIRO_API AK_MainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AK_MainPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void OnPlayerMove(const FInputActionValue& value);
	void OnPlayerJump();
	void OnPlayerAttack();
	void OnPlayerDash();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NEKIRO|Components")
	TObjectPtr<class USpringArmComponent> springArmComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NEKIRO|Components")
	TObjectPtr<class UCameraComponent> cameraComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NEKIRO|Input")
	TObjectPtr<UInputAction> IA_Move;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NEKIRO|Input")
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NEKIRO|Input")
	TObjectPtr<UInputAction> IA_Dash;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NEKIRO|Input")
	TObjectPtr<UInputAction> IA_Attack;

};
