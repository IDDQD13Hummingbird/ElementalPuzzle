// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"

#include "InventoryComponent.h"
#include "Core/VVInWorldElement.h"

#include "InteractionInterface.h"
#include "MyChar.generated.h"

class AVVGrid;
class UVVTile;
class UVVUIComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGridRecievedSignature);

UCLASS()
class YLIASTER_API AMyChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	// COMPONENTS


	//Character's Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* CharMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UBoxComponent* InteractionBox;

	//Character's Root Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UCapsuleComponent* CharRoot;

	// Target tile for character to move to
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Component")
	UBoxComponent* Target;
	// USE GetComponentLocation for tracking target of the character

	// Reference to inventory component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	class UInventoryComponent* InventoryReference;

	// Reference to User Interface Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	UVVUIComponent* UIComponentReference;

	// Ehich class element to spawn
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AVVInWorldElement> SpawnedElementClass;

	IInteractionInterface* Interface;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	AVVGrid* GridReference;

	UPROPERTY()
	float MovementDelta;

	UPROPERTY()
	UVVTile* CurrentTile;

	UPROPERTY()
	TArray<UVVTile*> TargetTile;


	// Input and IMC


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* TestAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* DropAction;


	// VARIABLES

	// Base movement speed of the coontrolled character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	float BaseMoveSpeed = 5.0f;

	FVector Direction;
	FVector StartLocation;
	float TotalDistance;
	float CurrentDistance;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Grid")
	FGridRecievedSignature GridRecievedDelegate;

	// FUNCTIONS


	UFUNCTION()
	FVector GetCharLocation();

	UFUNCTION()
	void CheckGrid(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void InteractOnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherbodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void InteractEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherbodyIndex);

	void InteractOnInput();

	void TestInput();

	void CallRemoveElement();

	UFUNCTION()
	void GridDetectionTest(UVVTile* FetchedTileReference, int32 X, int32 Y, FKey ButtonPressed);



};

//
//                                                         ..                                        
//                                                 (#((((#####((((((##(###((##(                       
//                                              (((((#(((((((((((#(((##############(.                 
//                                        .(((/(((((((((((##((((#####%#######%###(#####/              
//                                     (((((((((((((((((((#((((###%#######################            
//                                /#((((((((((((((((((((((((((############%%%##########((###(         
//                          *%#####(((((((((((((((((((#((((((#################################(       
//                      ###%#%########(((((((((##(#((((((((((((((((###############%%############,     
//                   #################((#((((((((#(((((((((((//(//((((#####(#####################/    
//                 ####%#############(((#((((((((((((((((((((//(//(//((#####(#################((#(*   
//              ###################(((((((((((((((((((((((((((((((/////((#((####(((###(((######((((   
//            %########(#######(((((((((((((((((((((((///(///(((((((/////((#########(####(#######(((  
//          ,##############(#((#(((((((((((((((((((((((((((((((((((//(((/((((####((#(######(#(((((((  
//         ###########%#####((##((((((((((((((#((((((((#((#((((((((/(((/////((##(((##(#(#####%###(((/ 
//       *#(#################(#####((((((#########((#####(((((#((((((((((/////(########(((((###(((((/.
//       (#(##########%##%########((((#(#########((((###((((((((((((((((((/(//(#####((####((((##((((//
//      (#%%%%%####%%%########%####((###########(##((((((((((((((((((((((///(((#####((#(((###((#(((((/
//     *###%####%%%%#%##############################(##(((((#((((((((((((((///(######(((##(((#((((((//
//    ###%%%####%#%%####%##%######((######(((((###((((#(##((#((##(((((((///(//#((((((#((((#(###((((((/
//   ##%#%%####%%###########(#####((###((((/////(((((##(((((////////////(///*((((##(##((((((#((((((///
//  ############%%#%###########(##((###(((((////((((####((///((//*///////(//////(((##(##(((((((((((///
// .########%#%%############%%###(((####(###((((((((((#((//(((((((((////(((/////(####(/(((((((((//((//
// %%%####%##%%#########%###%%###(#########(((((((((##(#(((((((((((((((((//////((###(#((((((((((/(////
//*#%####(####%#%%################################((###((((((#((((((((((/////((((#((####((((((((((////
//%###%%%###########%#%%#########################(((#(#((((((###((((((((((///(((#((((((((((((((/////**
//%###%##%#####%##%%%#####%#%######(#####(####(#(######((////((((##(((((((((/(#((((((((((((////(////, 
// *%%%%%%%%##(#%%##%#%%##############%####(#(#########((////(((((((((((((/(##((((((((((((#(////(//,  
// %%%%%%%%%#####%##%###%###%%%##################(####((((((((#(((((((///((((((((((((((//(((((/(///   
//  %%%%%%##(##########%%#%%%#%##%%########(###(((###(###(((((((((##(((((((((####(((((//(///(///(/,   
//  ,##%#######(#########%%%#####%%#%%#(#####(#((##((###((/((//((((((((((((((((#(((((((((////////*    
//   %#########(((#%############%####((################(((((((((((#(((((#(((####(((((((/(/((////*     
//   ######(((((#####(###(((#######(//(##############(#((#(##((((((((/((((((((((##(##(/(////(//*      
//    #######((#(((((((((((((##((///*(##((###############((##(((((((/*/(((((((((((((((////((///       
//     /##%#(((((##(((((((((/////*///(############(##(###(((((///(///*//////(((((((((((/(/((//.       
//      ##%##((######(((((/(////**/*/((############(((((((((////(/(///////////(/((((((/((///(*        
//      /(#########((#(((/////*/**/**(//(######((((((((((((/((((((////////////////(//((/((((/         
//       /(#%#######((((///////*//***///(((######(#(##(((((((((((/////*///////////((/(/(/////         
//         /(#########(((((/*/*******(/////(#########(##(##(((//////*/////////////((///////*,         
//          */((####(((/(///(/**///*///(((((##((((((###(##((((((/////////((////////(////////,         
//            */((######((((((////////((((((#((((((((((####(((((((((////////////(/((////////*         
//              ,/((#((((((((((((///((/(((((((((((((###((((((((((((/(/(//////////(///(//////*         
//                 *//(##((##((((((///(((((((((#(####(#####(((((((((((((((((///(//(////////*          
//                    *//##((((#((###((#(((((((((########((##((((((((((((((/(((((((////(//.           
//                       */(####(((#(#(/(#(((#(##########(((#((((((((((((((((((((((((////             
//                          ,*/(#######((/((((((##(####(((((((#(((#((((((((#((((((((////              
//                              ,/(#########((((((((((#(#(((((((#((((((((((##(((((//////              
//                                  *((##########((####(((((((((((#(#((((((((((((//////*              
//                                     ****(((##(((((###((((((((/(((((((((/(///((((////*              
//                                          .***//((#############((###((((((((/(((///(///             
//                                                   ,*/(#((############((((#(((#((((((/**            
//               

