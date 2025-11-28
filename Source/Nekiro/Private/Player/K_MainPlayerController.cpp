// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/K_MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"

void AK_MainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (subsystem)
	{
		subsystem->AddMappingContext(IMC_Player, gameInputPriority);
	}

	PlayerCameraManager->ViewPitchMin = minCameraPitch;
	PlayerCameraManager->ViewPitchMax = maxCameraPitch;
}

void AK_MainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* inputComp = Cast<UEnhancedInputComponent>(InputComponent);
	if (inputComp)
	{
		inputComp->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AK_MainPlayerController::OnPlayerLook);
	}
}

void AK_MainPlayerController::OnPlayerLook(const FInputActionValue& value)
{
	FVector2D inputVector = value.Get<FVector2D>();
	AddYawInput(inputVector.X);
	AddPitchInput(inputVector.Y);
}
