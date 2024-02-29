// Copyright (c) Marcus Henriksen 2023

#pragma once

#include "CoreMinimal.h"

/**
 * Simplifies printing messages.
 */
class NEURALNETWORK_API Printer
{
public:
	Printer() = default;
	~Printer() = default;
	
	FORCEINLINE static void printLog(const FString& msg, bool printToScreen = true)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *msg);
	}

	FORCEINLINE static void printLog(float value, bool printToScreen = true)
	{
		printLog(FString::SanitizeFloat(value), printToScreen);
	}

	FORCEINLINE static void printLog(const FString& msg, float value, bool printToScreen = true)
	{
		printLog(msg + ": " + FString::SanitizeFloat(value), printToScreen);
	}


	FORCEINLINE static void printWarning(const FString& msg, bool printToScreen = true)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *msg);
		if (printToScreen)
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, msg);
	}
	FORCEINLINE static void printWarning(float value, bool printToScreen = true)
	{
		printWarning(FString::SanitizeFloat(value), printToScreen);
	}

	FORCEINLINE static void printWarning(const FString& msg, float value, bool printToScreen = true)
	{
		printWarning(msg + ": " + FString::SanitizeFloat(value), printToScreen);
	}


	FORCEINLINE static void printError(const FString& msg, bool printToScreen = true)
	{
		UE_LOG(LogTemp, Error, TEXT("%s"), *msg);
		if (printToScreen)
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, msg);
	}

	FORCEINLINE static void printError(float value, bool printToScreen = true)
	{
		printError(FString::SanitizeFloat(value), printToScreen);
	}

	FORCEINLINE static void printError(const FString& msg, float value, bool printToScreen = true)
	{
		printError(msg + ": " + FString::SanitizeFloat(value), printToScreen);
	}
};
