#include "../include/mac/MacPermissions.h"
#include <juce_core/system/juce_TargetPlatform.h>

#if JUCE_MAC
 #import <AVFoundation/AVFoundation.h>

void MacPermissions::requestMicrophoneAccessIfNeeded()
{
    if (@available(macOS 10.14, *))
    {
        auto status = [AVCaptureDevice authorizationStatusForMediaType: AVMediaTypeAudio];
        if (status == AVAuthorizationStatusNotDetermined)
            [AVCaptureDevice requestAccessForMediaType: AVMediaTypeAudio completionHandler: ^(BOOL){ }];
    }
}
#else
void MacPermissions::requestMicrophoneAccessIfNeeded() {}
#endif
