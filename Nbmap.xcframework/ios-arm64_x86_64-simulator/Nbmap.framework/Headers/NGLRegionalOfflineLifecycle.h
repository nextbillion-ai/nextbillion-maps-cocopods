#import <Foundation/Foundation.h>

#import "NGLFoundation.h"

@class NGLMapView;

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NGL_EXPORT NSNotificationName const NGLRegionalOfflineMapDidAppearNotification;
FOUNDATION_EXPORT NGL_EXPORT NSNotificationName const NGLRegionalOfflineNetworkConnectivityDidChangeNotification;

NGL_EXPORT
@interface NGLRegionalOfflineLifecycle : NSObject

+ (void)notifyMapStyleLoadFinished:(NGLMapView *)mapView;
+ (void)notifyMapStyleLoadFailed:(NGLMapView *)mapView;
+ (void)notifyMapDestroy:(NGLMapView *)mapView;

@end

NS_ASSUME_NONNULL_END
