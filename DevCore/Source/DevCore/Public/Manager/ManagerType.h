#pragma once
#include "CoreManager.h"

class UCoreManager;

/**
 * 
 */
struct DEVCORE_API FManagerDelegates
{
	static FSimpleMulticastDelegate OnManagerSubsystemInitialize;

	DECLARE_MULTICAST_DELEGATE_OneParam(FManagerDelegate, UCoreManager*)
	static FManagerDelegate OnManagerRegister;
	static FManagerDelegate OnManagerUnRegister;

	static FSimpleMulticastDelegate PreManagerActived;
	static FManagerDelegate OnManagerActived;
	static FSimpleMulticastDelegate PostManagerActived;

	static FSimpleMulticastDelegate PreManagerInActived;
	static FManagerDelegate OnManagerInActived;
	static FSimpleMulticastDelegate PostManagerInActived;
};

/**
 * 
 */
struct DEVCORE_API FManagerOrder
{
public:
	FManagerOrder(int32 InOrder);
	bool operator==(const int32 InOrder) const { return Order == InOrder; }

public:
	int32 Order;
	TArray<UCoreManager*> Managers;
};
