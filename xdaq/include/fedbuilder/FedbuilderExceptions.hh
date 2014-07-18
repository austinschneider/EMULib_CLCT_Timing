#ifndef _FedbuilderExceptions_h_
#define _FedbuilderExceptions_h_

#include "xcept/Exception.h"

/* This definition is now in XDAQ:
#define XCEPT_DEFINE_EXCEPTION(NAMESPACE1 , EXCEPTION_NAME) \
namespace NAMESPACE1 { \
namespace exception { \
class EXCEPTION_NAME: public xcept::Exception \
{\
	public: \
	EXCEPTION_NAME( std::string name, std::string message, std::string module, int line, std::string function ): \
		xcept::Exception(name, message, module, line, function) \
	{}; \
	EXCEPTION_NAME( std::string name, std::string message, std::string module, int line, std::string function, xcept::Exception e ): \
		xcept::Exception(name, message, module, line, function, e) \
	{}; \
}; \
} \
}
*/

XCEPT_DEFINE_EXCEPTION( fedbuilder , Exception )

XCEPT_DEFINE_EXCEPTION( fedbuilder , SoftwareProblem )
XCEPT_DEFINE_EXCEPTION( fedbuilder , HardwareAccessFailed )
XCEPT_DEFINE_EXCEPTION( fedbuilder , IllegalStateTransition )
XCEPT_DEFINE_EXCEPTION( fedbuilder , SOAPTransitionProblem )

XCEPT_DEFINE_EXCEPTION( fedbuilder , FRLControllerDeviceCreationFailed )
XCEPT_DEFINE_EXCEPTION( fedbuilder , FRLControllerDeviceCloseDownFailed )
XCEPT_DEFINE_EXCEPTION( fedbuilder , FRLControllerDeviceInfospaceSetupFailed )
XCEPT_DEFINE_EXCEPTION( fedbuilder , FRLControllerDeviceInfospaceRemovalFailed )

XCEPT_DEFINE_EXCEPTION( fedbuilder , FRLLinkDeviceCreationFailed )
XCEPT_DEFINE_EXCEPTION( fedbuilder , FRLLinkDeviceCloseDownFailed )
XCEPT_DEFINE_EXCEPTION( fedbuilder , FRLLinkDeviceTestFailed )

XCEPT_DEFINE_EXCEPTION( fedbuilder , MyrinetError )
XCEPT_DEFINE_EXCEPTION( fedbuilder , MyrinetOpenError )
XCEPT_DEFINE_EXCEPTION( fedbuilder , MyrinetCloseError )
XCEPT_DEFINE_EXCEPTION( fedbuilder , MyrinetSyncLost )
XCEPT_DEFINE_EXCEPTION( fedbuilder , MyrinetSettingError )
XCEPT_DEFINE_EXCEPTION( fedbuilder , MyrinetConfigurationReadError )
XCEPT_DEFINE_EXCEPTION( fedbuilder , MyrinetConfigurationError )
XCEPT_DEFINE_EXCEPTION( fedbuilder , MyrinetConfigureError )
XCEPT_DEFINE_EXCEPTION( fedbuilder , MyrinetEnableError )
XCEPT_DEFINE_EXCEPTION( fedbuilder , MyrinetHaltError )

XCEPT_DEFINE_EXCEPTION( fedbuilder , MemoryPoolCreationError )
XCEPT_DEFINE_EXCEPTION( fedbuilder , RCMSNotificationError )
XCEPT_DEFINE_EXCEPTION( fedbuilder , FBOConfigFileProblem )
XCEPT_DEFINE_EXCEPTION( fedbuilder , FBOConfigurationError )
XCEPT_DEFINE_EXCEPTION( fedbuilder , MemorypoolInitializationError )
XCEPT_DEFINE_EXCEPTION( fedbuilder , DataCorruptionDetected )

#endif
