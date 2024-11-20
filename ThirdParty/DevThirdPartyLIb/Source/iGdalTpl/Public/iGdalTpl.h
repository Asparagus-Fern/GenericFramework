#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FiGdalTplModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    /** Handle to the test dll we will load */
    void *  Geos_LibraryHandle;
    void *	Geos_C_LibraryHandle;
    void *	Proj_LibraryHandle;
    void *	Tiff_LibraryHandle;
    void *	Gdal_LibraryHandle;
};