// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HttpRouteHandle.h"
#include "INativeAPISessionFeature.h"

class IHttpRouter;

/**
 * 
 */
class FNativeAPISession_HTTP : public INativeAPISessionFeature
{
public:
	virtual bool StartSession() override;
	virtual void EndSession() override;
	
	virtual FName GetSessionName() override
	{
		static FName SessionName(TEXT("HTTPServer"));
		return SessionName;
	}
	
private:
	TSharedPtr<IHttpRouter> HttpRouter;
	FHttpRouteHandle RouteHandle;
};
