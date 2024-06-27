#include "Manager/ManagerType.h"

FSimpleMulticastDelegate FManagerDelegates::OnManagerSubsystemInitialize;

FManagerDelegates::FManagerDelegate FManagerDelegates::OnManagerRegister;
FManagerDelegates::FManagerDelegate FManagerDelegates::OnManagerUnRegister;

FSimpleMulticastDelegate FManagerDelegates::PreManagerActived;
FManagerDelegates::FManagerDelegate FManagerDelegates::OnManagerActived;
FSimpleMulticastDelegate FManagerDelegates::PostManagerActived;
FSimpleMulticastDelegate FManagerDelegates::PreManagerInActived;
FManagerDelegates::FManagerDelegate FManagerDelegates::OnManagerInActived;
FSimpleMulticastDelegate FManagerDelegates::PostManagerInActived;

FManagerOrder::FManagerOrder(int32 InOrder)
	: Order(0)
{
}
