// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/K_MainPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include <EnhancedInputComponent.h>

// Sets default values
AK_MainPlayer::AK_MainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocation(FVector(0.f, 0.f, 70.f));
	springArmComp->TargetArmLength = 300.f;
	springArmComp->bUsePawnControlRotation = true;

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	cameraComp->SetupAttachment(springArmComp);
	cameraComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

}

// Called when the game starts or when spawned
void AK_MainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AK_MainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AK_MainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* inputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (inputComp)
	{
		inputComp->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AK_MainPlayer::OnPlayerMove);
		inputComp->BindAction(IA_Jump, ETriggerEvent::Started, this, &AK_MainPlayer::OnPlayerJump);
		inputComp->BindAction(IA_Attack, ETriggerEvent::Started, this, &AK_MainPlayer::OnPlayerAttack);
		inputComp->BindAction(IA_Dash, ETriggerEvent::Started, this, &AK_MainPlayer::OnPlayerDash);
	}
}

void AK_MainPlayer::OnPlayerMove(const FInputActionValue& value)
{
	FVector2D inputVector = value.Get<FVector2D>();
	FVector moveDirection(inputVector.X, inputVector.Y, 0.f);
	AddMovementInput(moveDirection);
}

void AK_MainPlayer::OnPlayerJump()
{
	Jump();
}

void AK_MainPlayer::OnPlayerAttack()
{
}

void AK_MainPlayer::OnPlayerDash()
{
}
